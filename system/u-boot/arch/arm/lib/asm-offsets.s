	.arch armv5te
	.eabi_attribute 20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute 21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute 23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute 24, 1	@ Tag_ABI_align8_needed
	.eabi_attribute 25, 1	@ Tag_ABI_align8_preserved
	.eabi_attribute 26, 2	@ Tag_ABI_enum_size
	.eabi_attribute 30, 4	@ Tag_ABI_optimization_goals
	.eabi_attribute 34, 0	@ Tag_CPU_unaligned_access
	.eabi_attribute 18, 2	@ Tag_ABI_PCS_wchar_t
	.file	"asm-offsets.c"
@ GNU C11 (Ubuntu 9.4.0-1ubuntu1~20.04.2) version 9.4.0 (arm-linux-gnueabi)
@	compiled by GNU C version 9.4.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22.1-GMP

@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed:  -nostdinc -I include -I ./arch/arm/thumb1/include
@ -I ./arch/arm/include -I ./arch/arm/mach-sunxi/include
@ -imultiarch arm-linux-gnueabi -D __KERNEL__ -D __UBOOT__ -D __ARM__
@ -D __LINUX_ARM_ARCH__=5 -D DO_DEPS_ONLY -D KBUILD_BASENAME="asm_offsets"
@ -D KBUILD_MODNAME="asm_offsets"
@ -isystem /usr/lib/gcc-cross/arm-linux-gnueabi/9/include
@ -include ./include/linux/kconfig.h -MD arch/arm/lib/.asm-offsets.s.d
@ arch/arm/lib/asm-offsets.c -mthumb -mthumb-interwork -mabi=aapcs-linux
@ -mword-relocations -mfloat-abi=soft -mtls-dialect=gnu -march=armv5te
@ -auxbase-strip arch/arm/lib/asm-offsets.s -g -Os -Wall
@ -Wstrict-prototypes -Wno-format-security -Wno-stringop-truncation
@ -Wno-format-nonliteral -Wno-address-of-packed-member
@ -Wno-unused-but-set-variable -Werror=date-time -std=gnu11 -fno-builtin
@ -ffreestanding -fshort-wchar -fno-strict-aliasing -fno-stack-protector
@ -fno-delete-null-pointer-checks -fmacro-prefix-map=./= -fstack-usage
@ -fno-pic -ffunction-sections -fdata-sections -fno-common -ffixed-r9
@ -fverbose-asm
@ options enabled:  -faggressive-loop-optimizations -fassume-phsa
@ -fauto-inc-dec -fbranch-count-reg -fcaller-saves -fcode-hoisting
@ -fcombine-stack-adjustments -fcompare-elim -fcprop-registers
@ -fcrossjumping -fcse-follow-jumps -fdata-sections -fdefer-pop
@ -fdevirtualize -fdevirtualize-speculatively -fdwarf2-cfi-asm
@ -fearly-inlining -feliminate-unused-debug-types -fexpensive-optimizations
@ -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse
@ -ffunction-sections -fgcse -fgcse-lm -fgnu-runtime -fgnu-unique
@ -fguess-branch-probability -fhoist-adjacent-loads -fident -fif-conversion
@ -fif-conversion2 -findirect-inlining -finline -finline-atomics
@ -finline-functions -finline-functions-called-once
@ -finline-small-functions -fipa-bit-cp -fipa-cp -fipa-icf
@ -fipa-icf-functions -fipa-icf-variables -fipa-profile -fipa-pure-const
@ -fipa-reference -fipa-reference-addressable -fipa-sra
@ -fipa-stack-alignment -fipa-vrp -fira-hoist-pressure
@ -fira-share-save-slots -fira-share-spill-slots
@ -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
@ -fleading-underscore -flifetime-dse -flra-remat -flto-odr-type-merging
@ -fmath-errno -fmerge-constants -fmerge-debug-strings
@ -fmove-loop-invariants -fomit-frame-pointer -foptimize-sibling-calls
@ -fpartial-inlining -fpeephole -fpeephole2 -fplt -fprefetch-loop-arrays
@ -freg-struct-return -freorder-blocks -freorder-functions
@ -frerun-cse-after-loop -fsched-critical-path-heuristic
@ -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
@ -fsched-last-insn-heuristic -fsched-pressure -fsched-rank-heuristic
@ -fsched-spec -fsched-spec-insn-heuristic -fsched-stalled-insns-dep
@ -fschedule-insns2 -fsection-anchors -fsemantic-interposition
@ -fshow-column -fshrink-wrap -fshrink-wrap-separate -fsigned-zeros
@ -fsplit-ivs-in-unroller -fsplit-wide-types -fssa-backprop -fssa-phiopt
@ -fstdarg-opt -fstore-merging -fstrict-volatile-bitfields -fsync-libcalls
@ -fthread-jumps -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp
@ -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
@ -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
@ -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-if-convert
@ -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
@ -ftree-parallelize-loops= -ftree-phiprop -ftree-pre -ftree-pta
@ -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-sra
@ -ftree-switch-conversion -ftree-tail-merge -ftree-ter -ftree-vrp
@ -funit-at-a-time -fvar-tracking -fvar-tracking-assignments -fverbose-asm
@ -fzero-initialized-in-bss -mbe32 -mglibc -mlittle-endian
@ -mpic-data-is-text-relative -msched-prolog -mthumb
@ -mvectorize-with-neon-quad -mword-relocations

	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.startup.main,"ax",%progbits
	.align	1
	.global	main
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	main, %function
main:
.LFB102:
	.file 1 "arch/arm/lib/asm-offsets.c"
	.loc 1 24 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 208 2 view .LVU1
@ arch/arm/lib/asm-offsets.c:209: }
	.loc 1 209 1 is_stmt 0 view .LVU2
	movs	r0, #0	@,
	@ sp needed	@
	bx	lr
	.cfi_endproc
.LFE102:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "include/asm-generic/int-ll64.h"
	.file 3 "include/linux/types.h"
	.file 4 "include/errno.h"
	.file 5 "include/linux/string.h"
	.file 6 "./arch/arm/include/asm/u-boot-arm.h"
	.file 7 "include/linux/libfdt_env.h"
	.file 8 "include/linux/../../scripts/dtc/libfdt/fdt.h"
	.file 9 "include/linux/libfdt.h"
	.file 10 "include/fdtdec.h"
	.file 11 "include/env_internal.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x259
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0xc
	.4byte	.LASF41
	.4byte	.LASF42
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF14
	.byte	0x4
	.byte	0xb
	.byte	0xc
	.4byte	0x31
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x4
	.4byte	0x5b
	.4byte	0x48
	.uleb128 0x5
	.4byte	0x4d
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	0x38
	.uleb128 0x7
	.byte	0x4
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x7
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x6
	.4byte	0x54
	.uleb128 0x8
	.4byte	.LASF43
	.byte	0x4
	.byte	0x19
	.byte	0x13
	.4byte	0x48
	.ascii	"\000"
	.uleb128 0x7
	.byte	0x4
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x7
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x7
	.byte	0x4
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x9
	.byte	0x4
	.4byte	0x54
	.uleb128 0x7
	.byte	0x8
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x7
	.byte	0x1
	.byte	0x6
	.4byte	.LASF6
	.uleb128 0xa
	.4byte	.LASF9
	.byte	0x2
	.byte	0x13
	.byte	0x17
	.4byte	0xa2
	.uleb128 0x7
	.byte	0x1
	.byte	0x8
	.4byte	.LASF7
	.uleb128 0x6
	.4byte	0xa2
	.uleb128 0x7
	.byte	0x2
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0xa
	.4byte	.LASF10
	.byte	0x2
	.byte	0x19
	.byte	0x16
	.4byte	0x4d
	.uleb128 0x7
	.byte	0x8
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0xb
	.ascii	"u8\000"
	.byte	0x2
	.byte	0x24
	.byte	0xf
	.4byte	0x96
	.uleb128 0xa
	.4byte	.LASF12
	.byte	0x3
	.byte	0x5b
	.byte	0x18
	.4byte	0x6d
	.uleb128 0xa
	.4byte	.LASF13
	.byte	0x3
	.byte	0x90
	.byte	0x19
	.4byte	0xb5
	.uleb128 0x2
	.4byte	.LASF15
	.byte	0x5
	.byte	0xb
	.byte	0xf
	.4byte	0x82
	.uleb128 0x2
	.4byte	.LASF16
	.byte	0x6
	.byte	0x12
	.byte	0xe
	.4byte	0xd3
	.uleb128 0x2
	.4byte	.LASF17
	.byte	0x6
	.byte	0x13
	.byte	0xe
	.4byte	0xd3
	.uleb128 0x2
	.4byte	.LASF18
	.byte	0x6
	.byte	0x14
	.byte	0xe
	.4byte	0xd3
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x6
	.byte	0x15
	.byte	0xe
	.4byte	0xd3
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0x6
	.byte	0x16
	.byte	0xe
	.4byte	0xd3
	.uleb128 0x2
	.4byte	.LASF21
	.byte	0x6
	.byte	0x17
	.byte	0xe
	.4byte	0xd3
	.uleb128 0x2
	.4byte	.LASF22
	.byte	0x6
	.byte	0x18
	.byte	0xe
	.4byte	0xd3
	.uleb128 0xa
	.4byte	.LASF23
	.byte	0x7
	.byte	0x12
	.byte	0x10
	.4byte	0xdf
	.uleb128 0xc
	.4byte	.LASF44
	.byte	0x28
	.byte	0x8
	.byte	0xc
	.byte	0x8
	.4byte	0x1e7
	.uleb128 0xd
	.4byte	.LASF24
	.byte	0x8
	.byte	0xd
	.byte	0xa
	.4byte	0x14b
	.byte	0
	.uleb128 0xd
	.4byte	.LASF25
	.byte	0x8
	.byte	0xe
	.byte	0xa
	.4byte	0x14b
	.byte	0x4
	.uleb128 0xd
	.4byte	.LASF26
	.byte	0x8
	.byte	0xf
	.byte	0xa
	.4byte	0x14b
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF27
	.byte	0x8
	.byte	0x10
	.byte	0xa
	.4byte	0x14b
	.byte	0xc
	.uleb128 0xd
	.4byte	.LASF28
	.byte	0x8
	.byte	0x11
	.byte	0xa
	.4byte	0x14b
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF29
	.byte	0x8
	.byte	0x12
	.byte	0xa
	.4byte	0x14b
	.byte	0x14
	.uleb128 0xd
	.4byte	.LASF30
	.byte	0x8
	.byte	0x13
	.byte	0xa
	.4byte	0x14b
	.byte	0x18
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0x8
	.byte	0x16
	.byte	0xa
	.4byte	0x14b
	.byte	0x1c
	.uleb128 0xd
	.4byte	.LASF32
	.byte	0x8
	.byte	0x19
	.byte	0xa
	.4byte	0x14b
	.byte	0x20
	.uleb128 0xd
	.4byte	.LASF33
	.byte	0x8
	.byte	0x1c
	.byte	0xa
	.4byte	0x14b
	.byte	0x24
	.byte	0
	.uleb128 0x2
	.4byte	.LASF34
	.byte	0x9
	.byte	0xb
	.byte	0x1b
	.4byte	0x1f3
	.uleb128 0x9
	.byte	0x4
	.4byte	0x157
	.uleb128 0x4
	.4byte	0xc8
	.4byte	0x204
	.uleb128 0xe
	.byte	0
	.uleb128 0x2
	.4byte	.LASF35
	.byte	0xa
	.byte	0x72
	.byte	0xb
	.4byte	0x1f9
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0xa
	.byte	0x73
	.byte	0xb
	.4byte	0x1f9
	.uleb128 0x7
	.byte	0x1
	.byte	0x2
	.4byte	.LASF37
	.uleb128 0x7
	.byte	0x8
	.byte	0x4
	.4byte	.LASF38
	.uleb128 0x4
	.4byte	0xa9
	.4byte	0x235
	.uleb128 0xe
	.byte	0
	.uleb128 0x6
	.4byte	0x22a
	.uleb128 0x2
	.4byte	.LASF39
	.byte	0xb
	.byte	0x72
	.byte	0x1c
	.4byte	0x235
	.uleb128 0xf
	.4byte	.LASF45
	.byte	0x1
	.byte	0x17
	.byte	0x5
	.4byte	0x31
	.4byte	.LFB102
	.4byte	.LFE102-.LFB102
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB102
	.4byte	.LFE102-.LFB102
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB102
	.4byte	.LFE102
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF43:
	.ascii	"error_message\000"
.LASF44:
	.ascii	"fdt_header\000"
.LASF37:
	.ascii	"_Bool\000"
.LASF10:
	.ascii	"__u32\000"
.LASF36:
	.ascii	"__dtb_dt_spl_begin\000"
.LASF14:
	.ascii	"errno\000"
.LASF26:
	.ascii	"off_dt_struct\000"
.LASF23:
	.ascii	"fdt32_t\000"
.LASF24:
	.ascii	"magic\000"
.LASF28:
	.ascii	"off_mem_rsvmap\000"
.LASF16:
	.ascii	"IRQ_STACK_START\000"
.LASF7:
	.ascii	"unsigned char\000"
.LASF33:
	.ascii	"size_dt_struct\000"
.LASF2:
	.ascii	"long unsigned int\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF17:
	.ascii	"FIQ_STACK_START\000"
.LASF13:
	.ascii	"__be32\000"
.LASF15:
	.ascii	"___strtok\000"
.LASF9:
	.ascii	"__u8\000"
.LASF40:
	.ascii	"GNU C11 9.4.0 -mthumb -mthumb-interwork -mabi=aapcs"
	.ascii	"-linux -mword-relocations -mfloat-abi=soft -mtls-di"
	.ascii	"alect=gnu -march=armv5te -g -Os -std=gnu11 -fno-bui"
	.ascii	"ltin -ffreestanding -fshort-wchar -fno-strict-alias"
	.ascii	"ing -fno-stack-protector -fno-delete-null-pointer-c"
	.ascii	"hecks -fstack-usage -fno-pic -ffunction-sections -f"
	.ascii	"data-sections -fno-common -ffixed-r9\000"
.LASF34:
	.ascii	"working_fdt\000"
.LASF21:
	.ascii	"_datarelro_start_ofs\000"
.LASF29:
	.ascii	"version\000"
.LASF12:
	.ascii	"ulong\000"
.LASF0:
	.ascii	"unsigned int\000"
.LASF18:
	.ascii	"_datarel_start_ofs\000"
.LASF11:
	.ascii	"long long unsigned int\000"
.LASF45:
	.ascii	"main\000"
.LASF35:
	.ascii	"__dtb_dt_begin\000"
.LASF22:
	.ascii	"IRQ_STACK_START_IN\000"
.LASF5:
	.ascii	"long long int\000"
.LASF39:
	.ascii	"default_environment\000"
.LASF41:
	.ascii	"arch/arm/lib/asm-offsets.c\000"
.LASF1:
	.ascii	"char\000"
.LASF42:
	.ascii	"/home/hah/linux/f1c2000/u-boot\000"
.LASF8:
	.ascii	"short int\000"
.LASF32:
	.ascii	"size_dt_strings\000"
.LASF30:
	.ascii	"last_comp_version\000"
.LASF27:
	.ascii	"off_dt_strings\000"
.LASF20:
	.ascii	"_datarellocal_start_ofs\000"
.LASF4:
	.ascii	"long int\000"
.LASF38:
	.ascii	"long double\000"
.LASF6:
	.ascii	"signed char\000"
.LASF19:
	.ascii	"_datarelrolocal_start_ofs\000"
.LASF31:
	.ascii	"boot_cpuid_phys\000"
.LASF25:
	.ascii	"totalsize\000"
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",%progbits
