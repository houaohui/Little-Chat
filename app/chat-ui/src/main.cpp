#include "TXT_Viewer.h"
#include <iostream>
#include <memory.h>
#include <signal.h>
#include <unistd.h>
#include "mqtt-client.h"
#include "freetype_draw.h"
#include <termios.h>
#include <fcntl.h>
#include <iconv.h>
#include <queue>
#include <mutex>
#include <sys/time.h>
#include <termios.h>
#include <fcntl.h>
#include <iconv.h>
#include <queue>
#include <mutex>
#include <sys/time.h>
#include <linux/input.h>
#include <wchar.h>
#include <locale.h>


using namespace std;

// 定义输入事件设备文件路径
#define INPUT_EVENT_DEVICE "/dev/input/event0"  // 请替换X为正确的事件设备号
// 上箭头：KEY_UP，对应键码是103  对应编码 (int)1
// 下箭头：KEY_DOWN，对应键码是108 对应编码 (int)2
// 左箭头：KEY_LEFT，对应键码是105 对应编码 (int)3
// 右箭头：KEY_RIGHT，对应键码是106 对应编码 (int)4


// 硬编码的映射表，根据键盘布局调整
static char key_map_lower[256] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3',
    '0', '.', 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 4, 0, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static char key_map_upper[256] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ',
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3',
    '0', '.', 0, 0
};

std::deque<std::wstring> myQueue;
std::mutex mtx;

/**
 * @brief 退出
 * 
 */
static int global_done = false;
static void catch_sig(int signum)
{
    (void)signum;
    global_done = 1;
}

static float cpuUsage = 0;

// cpu 使用统计线程
void* getCpuUsage(void* arg) {
    while (!global_done) {

        FILE* file = fopen("/proc/stat", "r");
        if (file == NULL) {
            perror("Error opening /proc/stat");
            exit(1);
        }

        char line[128];
        unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
        unsigned long long prev_idle, prev_total, total_diff, idle_diff;

        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice) == 10) {
                prev_idle = idle;
                prev_total = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
                break;
            }
        }
        fclose(file);

        // Do some work that you want to measure CPU usage for.
        sleep(2);

        // After the work is done, read /proc/stat again.
        file = fopen("/proc/stat", "r");
        if (file == NULL) {
            perror("Error opening /proc/stat");
            exit(1);
        }

        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice) == 10) {
                total_diff = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice - prev_total;
                idle_diff = idle - prev_idle;
                double cpu_usage = 100.0 * (1.0 - (double)idle_diff / total_diff);
                // printf("CPU Usage: %.2f%%\n", cpu_usage);
                cpuUsage = cpu_usage;
                break;
            }
        }
        fclose(file);
    }

    return NULL;
}



/**
 * @brief MQTT回调函数
 * 
 * @param context 
 * @param topicName 
 * @param topicLen 
 * @param message 
 * @return int 
 */
static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("Message arrived\n");
    // printf("     topic: %s\n", topicName);
    // printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
    std::string ui_txt = (char *)message->payload;

    // 将字符串连接并转换
    std::string concatenatedStr = ui_txt + "\n";

    size_t in_len = concatenatedStr.length();

    size_t out_len = in_len * sizeof(wchar_t);

    // 分配输出缓冲区的内存并初始化为零
    wchar_t *out_str = (wchar_t *)calloc(out_len, 1);

    iconv_t cd = iconv_open("wchar_t","UTF-8");
    if(cd == (iconv_t)-1) {
        printf("iconv open failed !\n");
    }

    //转化
    std::wstring ui_wtxt;
    char * in_buf = (char *)concatenatedStr.c_str();
    char *out_buf = (char *)out_str;

    if(iconv(cd, &in_buf, &in_len, &out_buf, &out_len) == (size_t)-1) {
        // 转化失败
        printf("iconv failed!\n");
        wchar_t buffer[50];
        // 使用swprintf进行格式化
        swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"iconv %d:%d\n", in_len, out_len);

        ui_wtxt = buffer;
    } else {
        // 转化成功
        ui_wtxt = out_str; 
    }

    if (!ui_wtxt.empty())
    {
        std::lock_guard<std::mutex> lock(mtx);
        myQueue.push_back(ui_wtxt);
    }

   
    // free(wtxt);
    iconv_close(cd);
    free(out_str);

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return 1;
}

void *key_reader(void *arg) {
    int fd;
    struct input_event ev;
    wchar_t wc;

    // 打开输入事件设备文件
    if ((fd = open(INPUT_EVENT_DEVICE, O_RDONLY)) == -1) {
        perror("无法打开输入事件设备");
        return NULL;
    }

    int ctrl_pressed = 0;  // 用于跟踪Ctrl键是否按下
    int shift_pressed = 0;

    char *current_key_map = key_map_lower;  // 默认使用小写映射

    // 设置本地化环境以处理多字节字符
    // setlocale(LC_CTYPE, "");

    while (1) {
        if (read(fd, &ev, sizeof(struct input_event)) == sizeof(struct input_event)) {
        
            if (ev.code == KEY_LEFTCTRL || ev.code == KEY_RIGHTCTRL) {
                if (ev.value == 1) {
                    ctrl_pressed = 1;  // Ctrl键按下
                } else {
                    ctrl_pressed = 0;  // Ctrl键释放
                }
                // 忽略ctrl键值
                continue;
            } else if (ctrl_pressed && ev.value >= 1) {
                static int mode_index = 1;
                printf("ctrl + %c\n", ev.code);
                if (ev.code == 2) { // ctrl + 1
                    switch (mode_index) {
                        case 0: txtViewer_changeProcessMode(&txtViewer,NORMAL);         mode_index++; break;
                        case 1: txtViewer_changeProcessMode(&txtViewer,AUTO_BREAKLINE); mode_index++; break;
                        case 2: txtViewer_changeProcessMode(&txtViewer,CONSOLE_PRINT);  mode_index = 0; break;
                    }
                }

                static int win_size_index = 1;
                if (ev.code == 3) { // ctrl + 2
                    switch (win_size_index) {
                        case 0: txtViewer_setWindow(&txtViewer, 240,240); win_size_index++;break;
                        case 1: txtViewer_setWindow(&txtViewer, 240,480); win_size_index++;break;
                        case 2: txtViewer_setWindow(&txtViewer, 480,480); win_size_index=0;break;
                    }
                }

                if (shift_pressed == 0) {  // ctrl + 移动 窗口移动
                    if (ev.code == 103) {  // 窗口向上
                        txtViewer.window_y--;
                    } else if (ev.code == 108) {// 窗口向下
                        txtViewer.window_y++;
                    } else if (ev.code == 105) {// 窗口向左
                        txtViewer.window_x--;
                    } else if (ev.code == 106) {// 窗口向右
                        txtViewer.window_x++;
                    }
                } else { //  ctrl + shift + 移动 文本偏移 只适用于NORMAL解析器
                    if (ev.code == 103) {  // 窗口向上
                        txtViewer.txt_ofsetY--;
                    } else if (ev.code == 108) {// 窗口向下
                        txtViewer.txt_ofsetY++;
                    } else if (ev.code == 105) {// 窗口向左
                        txtViewer.txt_ofsetX--;
                    } else if (ev.code == 106) {// 窗口向右
                        txtViewer.txt_ofsetX++;
                    } 

                }
                continue;
            }

            // 普通按键检测
            if (ev.type == EV_KEY) {

                if (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT) {
                    // 切换映射表
                    if (ev.value == 1) {
                        current_key_map = key_map_upper;  // 切换到大写映射
                        shift_pressed = 1;
                    } else {
                        current_key_map = key_map_lower;  // 切换回小写映射
                        shift_pressed = 0;
                    }
                } else {

                    // 按键按下  >= 1 支持长按
                    if (ev.value >= 1) {

                        printf("key down: %d\n", ev.code);
                        char character = current_key_map[ev.code];

                        if (character != 0) {
                            printf("char: %c:%d\n", character,character);
                            if (character == 'p') {
                                txtViewer_getChar(&txtViewer, L'文');
                                continue;
                            }
                            // 输入字符 宽字符中普通字符也兼容ASCII字符编码 这是因为ASCII 字符在 Unicode 编码中有对应的代码点，并且其高位字节为0，与单字节编码相同
                            txtViewer_getChar(&txtViewer, (wchar_t)character);
                        }
                       
                    }
                }
            }

        }
    }

    close(fd);
    return NULL;
}


/**
 * @brief 控制帧率刷新函数
 * 
 * @param frameRate 设定帧率
 */
void updateFrame(int frameRate) {
    struct timeval currentTime, lastTime;
    long long frameTimeMicros = 1000000 / frameRate;

    gettimeofday(&lastTime, NULL);

    do {
        gettimeofday(&currentTime, NULL);

        long long elapsedTimeMicros = (currentTime.tv_sec - lastTime.tv_sec) * 1000000 +
            (currentTime.tv_usec - lastTime.tv_usec);

        if (elapsedTimeMicros < frameTimeMicros) {
            long long sleepTimeMicros = frameTimeMicros - elapsedTimeMicros;
            usleep(sleepTimeMicros); // 睡眠以控制帧率
        }

        static u8 follow_speech_flag = 0;
        static int target_scroll_pixel = 0;

        // 刷新屏幕
        do{
            std::lock_guard<std::mutex> lock(mtx);
            if (!myQueue.empty()) {
                std::wstring &new_wtxt = myQueue.back(); // 只读取队列的末尾数据
                txtViewer.printf(&txtViewer, (wchar_t *)new_wtxt.c_str());
                // txtViewer.scroll_enable = false; // 关闭滚动 我们需要获取音频时长自动滚动
                // follow_speech_flag = true;  // 开启语音跟随
                myQueue.pop_back();    // 只删除队列的末尾数据
            }
        } while(0);

        // 这里控制窗口跟随语音,独立出来降低耦合
        if(follow_speech_flag) {
            if(txtViewer.scroll_enable)
                follow_speech_flag = false;
            int delt = abs(target_scroll_pixel - txtViewer.scroll_pixel);
			if (delt > 1)
				txtViewer.scroll_pixel += target_scroll_pixel - txtViewer.scroll_pixel > 0 ? 1 : -1;
        }

        // 解析
        txtViewer.run(&txtViewer);
        
        freetype_show_cpu_usage(cpuUsage);
        freetype_fill_screen();
        freetype_clean_screen();

        gettimeofday(&lastTime, NULL);

    } while(!global_done);
}

int main(int argc, char **argv)
{

    if (signal(SIGINT, catch_sig) == SIG_ERR)
        printf("Failed to set SIGINT handler");
    
    MQTTCLIENT *mqttClient = new MQTTCLIENT();
    mqttClient->subscribe("/test/ui",msgarrvd);

    freetype_test_init();
    // freetype_test_draw();

    // 关闭tty1输出到fb0上
    system("echo 0 > /sys/class/vtconsole/vtcon1/bind");
    
    txtViewer_init(&txtViewer,1024,0,0,CONSOLE_PRINT);

    // 获取CPU信息
    pthread_t thread;
    if (pthread_create(&thread, NULL, getCpuUsage, NULL) != 0) {
        perror("Error creating thread");
        return 1;
    }
    
    // 创建按键读取线程
    pthread_t tid;
    if (pthread_create(&tid, NULL, key_reader, NULL) != 0) {
        perror("无法创建线程");
        return 1;
    }

    #define FRAME_RATE  (30)

    while(!global_done)
    {
        updateFrame(FRAME_RATE);
    }

    // 打开tty1输出到fb0上
    system("echo 1 > /sys/class/vtconsole/vtcon1/bind");

    freetype_test_close();
    
    delete mqttClient;
    return 0;
}



