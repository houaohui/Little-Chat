// SPDX-License-Identifier: GPL-2.0

#include <stdint.h>
#include "resctrl.h"

struct read_format {
	__u64 nr;			/* The number of events */
	struct {
		__u64 value;		/* The value of the event */
	} values[2];
};

static struct perf_event_attr pea_llc_miss;
static struct read_format rf_cqm;
static int fd_lm;
char llc_occup_path[1024];

static void initialize_perf_event_attr(void)
{
	pea_llc_miss.type = PERF_TYPE_HARDWARE;
	pea_llc_miss.size = sizeof(struct perf_event_attr);
	pea_llc_miss.read_format = PERF_FORMAT_GROUP;
	pea_llc_miss.exclude_kernel = 1;
	pea_llc_miss.exclude_hv = 1;
	pea_llc_miss.exclude_idle = 1;
	pea_llc_miss.exclude_callchain_kernel = 1;
	pea_llc_miss.inherit = 1;
	pea_llc_miss.exclude_guest = 1;
	pea_llc_miss.disabled = 1;
}

static void ioctl_perf_event_ioc_reset_enable(void)
{
	ioctl(fd_lm, PERF_EVENT_IOC_RESET, 0);
	ioctl(fd_lm, PERF_EVENT_IOC_ENABLE, 0);
}

static int perf_event_open_llc_miss(pid_t pid, int cpu_no)
{
	fd_lm = perf_event_open(&pea_llc_miss, pid, cpu_no, -1,
				PERF_FLAG_FD_CLOEXEC);
	if (fd_lm == -1) {
		perror("Error opening leader");
		ctrlc_handler(0, NULL, NULL);
		return -1;
	}

	return 0;
}

static int initialize_llc_perf(void)
{
	memset(&pea_llc_miss, 0, sizeof(struct perf_event_attr));
	memset(&rf_cqm, 0, sizeof(struct read_format));

	/* Initialize perf_event_attr structures for HW_CACHE_MISSES */
	initialize_perf_event_attr();

	pea_llc_miss.config = PERF_COUNT_HW_CACHE_MISSES;

	rf_cqm.nr = 1;

	return 0;
}

static int reset_enable_llc_perf(pid_t pid, int cpu_no)
{
	int ret = 0;

	ret = perf_event_open_llc_miss(pid, cpu_no);
	if (ret < 0)
		return ret;

	/* Start counters to log values */
	ioctl_perf_event_ioc_reset_enable();

	return 0;
}

/*
 * get_llc_perf:	llc cache miss through perf events
 * @cpu_no:		CPU number that the benchmark PID is binded to
 *
 * Perf events like HW_CACHE_MISSES could be used to validate number of
 * cache lines allocated.
 *
 * Return: =0 on success.  <0 on failure.
 */
static int get_llc_perf(unsigned long *llc_perf_miss)
{
	__u64 total_misses;

	/* Stop counters after one span to get miss rate */

	ioctl(fd_lm, PERF_EVENT_IOC_DISABLE, 0);

	if (read(fd_lm, &rf_cqm, sizeof(struct read_format)) == -1) {
		perror("Could not get llc misses through perf");

		return -1;
	}

	total_misses = rf_cqm.values[0].value;

	close(fd_lm);

	*llc_perf_miss = total_misses;

	return 0;
}

/*
 * Get LLC Occupancy as reported by RESCTRL FS
 * For CQM,
 * 1. If con_mon grp and mon grp given, then read from mon grp in
 * con_mon grp
 * 2. If only con_mon grp given, then read from con_mon grp
 * 3. If both not given, then read from root con_mon grp
 * For CAT,
 * 1. If con_mon grp given, then read from it
 * 2. If con_mon grp not given, then read from root con_mon grp
 *
 * Return: =0 on success.  <0 on failure.
 */
static int get_llc_occu_resctrl(unsigned long *llc_occupancy)
{
	FILE *fp;

	fp = fopen(llc_occup_path, "r");
	if (!fp) {
		perror("Failed to open results file");

		return errno;
	}
	if (fscanf(fp, "%lu", llc_occupancy) <= 0) {
		perror("Could not get llc occupancy");
		fclose(fp);

		return -1;
	}
	fclose(fp);

	return 0;
}

/*
 * print_results_cache:	the cache results are stored in a file
 * @filename:		file that stores the results
 * @bm_pid:		child pid that runs benchmark
 * @llc_value:		perf miss value /
 *			llc occupancy value reported by resctrl FS
 *
 * Return:		0 on success. non-zero on failure.
 */
static int print_results_cache(char *filename, int bm_pid,
			       unsigned long llc_value)
{
	FILE *fp;

	if (strcmp(filename, "stdio") == 0 || strcmp(filename, "stderr") == 0) {
		printf("Pid: %d \t LLC_value: %lu\n", bm_pid,
		       llc_value);
	} else {
		fp = fopen(filename, "a");
		if (!fp) {
			perror("Cannot open results file");

			return errno;
		}
		fprintf(fp, "Pid: %d \t llc_value: %lu\n", bm_pid, llc_value);
		fclose(fp);
	}

	return 0;
}

int measure_cache_vals(struct resctrl_val_param *param, int bm_pid)
{
	unsigned long llc_perf_miss = 0, llc_occu_resc = 0, llc_value = 0;
	int ret;

	/*
	 * Measure cache miss from perf.
	 */
	if (!strcmp(param->resctrl_val, "cat")) {
		ret = get_llc_perf(&llc_perf_miss);
		if (ret < 0)
			return ret;
		llc_value = llc_perf_miss;
	}

	/*
	 * Measure llc occupancy from resctrl.
	 */
	if (!strcmp(param->resctrl_val, "cqm")) {
		ret = get_llc_occu_resctrl(&llc_occu_resc);
		if (ret < 0)
			return ret;
		llc_value = llc_occu_resc;
	}
	ret = print_results_cache(param->filename, bm_pid, llc_value);
	if (ret)
		return ret;

	return 0;
}

/*
 * cache_val:		execute benchmark and measure LLC occupancy resctrl
 * and perf cache miss for the benchmark
 * @param:		parameters passed to cache_val()
 *
 * Return:		0 on success. non-zero on failure.
 */
int cat_val(struct resctrl_val_param *param)
{
	int malloc_and_init_memory = 1, memflush = 1, operation = 0, ret = 0;
	char *resctrl_val = param->resctrl_val;
	pid_t bm_pid;

	if (strcmp(param->filename, "") == 0)
		sprintf(param->filename, "stdio");

	bm_pid = getpid();

	/* Taskset benchmark to specified cpu */
	ret = taskset_benchmark(bm_pid, param->cpu_no);
	if (ret)
		return ret;

	/* Write benchmark to specified con_mon grp, mon_grp in resctrl FS*/
	ret = write_bm_pid_to_resctrl(bm_pid, param->ctrlgrp, param->mongrp,
				      resctrl_val);
	if (ret)
		return ret;

	if ((strcmp(resctrl_val, "cat") == 0)) {
		ret = initialize_llc_perf();
		if (ret)
			return ret;
	}

	/* Test runs until the callback setup() tells the test to stop. */
	while (1) {
		if (strcmp(resctrl_val, "cat") == 0) {
			ret = param->setup(1, param);
			if (ret) {
				ret = 0;
				break;
			}
			ret = reset_enable_llc_perf(bm_pid, param->cpu_no);
			if (ret)
				break;

			if (run_fill_buf(param->span, malloc_and_init_memory,
					 memflush, operation, resctrl_val)) {
				fprintf(stderr, "Error-running fill buffer\n");
				ret = -1;
				break;
			}

			sleep(1);
			ret = measure_cache_vals(param, bm_pid);
			if (ret)
				break;
		} else {
			break;
		}
	}

	return ret;
}