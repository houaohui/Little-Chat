cmd_arch/arm/lib/bootm.o := arm-linux-gnueabi-gcc -Wp,-MD,arch/arm/lib/.bootm.o.d  -nostdinc -isystem /usr/lib/gcc-cross/arm-linux-gnueabi/9/include -Iinclude    -I./arch/arm/thumb1/include -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -std=gnu11 -fshort-wchar -fno-strict-aliasing -fno-PIE -Os -fno-stack-protector -fno-delete-null-pointer-checks -Wno-stringop-truncation -fmacro-prefix-map=./= -g -fstack-usage -Wno-format-nonliteral -Wno-address-of-packed-member -Wno-unused-but-set-variable -Werror=date-time -D__ARM__ -Wa,-mimplicit-it=always -mthumb -mthumb-interwork -mabi=aapcs-linux -mword-relocations -fno-pic -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float -pipe -march=armv5te -D__LINUX_ARM_ARCH__=5 -I./arch/arm/mach-sunxi/include    -DKBUILD_BASENAME='"bootm"'  -DKBUILD_MODNAME='"bootm"' -c -o arch/arm/lib/bootm.o arch/arm/lib/bootm.c

source_arch/arm/lib/bootm.o := arch/arm/lib/bootm.c

deps_arch/arm/lib/bootm.o := \
    $(wildcard include/config/armv7/nonsec.h) \
    $(wildcard include/config/sys/bootmapsz.h) \
    $(wildcard include/config/nr/dram/banks.h) \
    $(wildcard include/config/bootstage/fdt.h) \
    $(wildcard include/config/bootstage/report.h) \
    $(wildcard include/config/usb/device.h) \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/of/libfdt.h) \
    $(wildcard include/config/armv7/boot/sec/default.h) \
    $(wildcard include/config/armv8/switch/to/el1.h) \
    $(wildcard include/config/armv8/psci.h) \
    $(wildcard include/config/cpu/v7m.h) \
    $(wildcard include/config/bootm/vxworks.h) \
  include/linux/kconfig.h \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
    $(wildcard include/config/spl/.h) \
    $(wildcard include/config/spl/build.h) \
    $(wildcard include/config/tpl/build.h) \
    $(wildcard include/config/tpl/.h) \
    $(wildcard include/config/spl/foo.h) \
    $(wildcard include/config/tpl/foo.h) \
  include/common.h \
  include/config.h \
    $(wildcard include/config/boarddir.h) \
  include/config_defaults.h \
  include/config_uncmd_spl.h \
    $(wildcard include/config/spl/dm.h) \
    $(wildcard include/config/dm/serial.h) \
    $(wildcard include/config/dm/i2c.h) \
    $(wildcard include/config/dm/spi.h) \
    $(wildcard include/config/dm/warn.h) \
    $(wildcard include/config/dm/stdio.h) \
  include/configs/suniv.h \
  include/configs/sunxi-common.h \
    $(wildcard include/config/old/sunxi/kernel/compat.h) \
    $(wildcard include/config/mach/type/compat/rev.h) \
    $(wildcard include/config/sys/bootm/len.h) \
    $(wildcard include/config/sys/ns16550/serial.h) \
    $(wildcard include/config/mach/suniv.h) \
    $(wildcard include/config/sys/ns16550/clk.h) \
    $(wildcard include/config/sys/ns16550/reg/size.h) \
    $(wildcard include/config/sys/ns16550/com1.h) \
    $(wildcard include/config/sys/ns16550/com2.h) \
    $(wildcard include/config/sys/ns16550/com3.h) \
    $(wildcard include/config/sys/ns16550/com4.h) \
    $(wildcard include/config/sys/ns16550/com5.h) \
    $(wildcard include/config/mach/sun9i.h) \
    $(wildcard include/config/sys/sdram/base.h) \
    $(wildcard include/config/sys/load/addr.h) \
    $(wildcard include/config/spl/stack/r/addr.h) \
    $(wildcard include/config/spl/bss/start/addr.h) \
    $(wildcard include/config/spl/bss/max/size.h) \
    $(wildcard include/config/sys/init/ram/addr.h) \
    $(wildcard include/config/sunxi/sram/address.h) \
    $(wildcard include/config/sys/init/ram/size.h) \
    $(wildcard include/config/sys/init/sp/offset.h) \
    $(wildcard include/config/sys/init/sp/addr.h) \
    $(wildcard include/config/ahci.h) \
    $(wildcard include/config/sys/64bit/lba.h) \
    $(wildcard include/config/setup/memory/tags.h) \
    $(wildcard include/config/cmdline/tag.h) \
    $(wildcard include/config/initrd/tag.h) \
    $(wildcard include/config/serial/tag.h) \
    $(wildcard include/config/nand/sunxi.h) \
    $(wildcard include/config/sys/nand/max/eccpos.h) \
    $(wildcard include/config/sys/nand/onfi/detection.h) \
    $(wildcard include/config/sys/max/nand/device.h) \
    $(wildcard include/config/mmc.h) \
    $(wildcard include/config/mmc/sunxi/slot.h) \
    $(wildcard include/config/env/is/in/mmc.h) \
    $(wildcard include/config/env/offset.h) \
    $(wildcard include/config/sys/mmcsd/raw/mode/u/boot/sector.h) \
    $(wildcard include/config/board/size/limit.h) \
    $(wildcard include/config/mmc/sunxi/slot/extra.h) \
    $(wildcard include/config/sys/mmc/env/dev.h) \
    $(wildcard include/config/sys/mmc/max/device.h) \
    $(wildcard include/config/mach/sun8i/v3s.h) \
    $(wildcard include/config/sys/malloc/len.h) \
    $(wildcard include/config/env/size.h) \
    $(wildcard include/config/sys/cbsize.h) \
    $(wildcard include/config/sys/pbsize.h) \
    $(wildcard include/config/standalone/load/addr.h) \
    $(wildcard include/config/sys/monitor/len.h) \
    $(wildcard include/config/spl/board/load/image.h) \
    $(wildcard include/config/spl/max/size.h) \
    $(wildcard include/config/spl/stack.h) \
    $(wildcard include/config/spl/pad/to.h) \
    $(wildcard include/config/axp152/power.h) \
    $(wildcard include/config/axp209/power.h) \
    $(wildcard include/config/sy8106a/power.h) \
    $(wildcard include/config/i2c0/enable.h) \
    $(wildcard include/config/i2c1/enable.h) \
    $(wildcard include/config/i2c2/enable.h) \
    $(wildcard include/config/i2c3/enable.h) \
    $(wildcard include/config/i2c4/enable.h) \
    $(wildcard include/config/r/i2c/enable.h) \
    $(wildcard include/config/sys/i2c/mvtwsi.h) \
    $(wildcard include/config/sys/i2c.h) \
    $(wildcard include/config/sys/i2c/speed.h) \
    $(wildcard include/config/sys/i2c/slave.h) \
    $(wildcard include/config/video/lcd/panel/i2c.h) \
    $(wildcard include/config/sys/i2c/soft.h) \
    $(wildcard include/config/sys/i2c/soft/speed.h) \
    $(wildcard include/config/sys/i2c/soft/slave.h) \
    $(wildcard include/config/soft/i2c/gpio/sda.h) \
    $(wildcard include/config/soft/i2c/gpio/scl.h) \
    $(wildcard include/config/video/lcd/i2c/bus.h) \
    $(wildcard include/config/sys/spd/bus/num.h) \
    $(wildcard include/config/axp221/power.h) \
    $(wildcard include/config/axp818/power.h) \
    $(wildcard include/config/require/serial/console.h) \
    $(wildcard include/config/cons/index.h) \
    $(wildcard include/config/mach/sun5i.h) \
    $(wildcard include/config/mach/sun8i.h) \
    $(wildcard include/config/video/sunxi.h) \
    $(wildcard include/config/sunxi/max/fb/size.h) \
    $(wildcard include/config/video/logo.h) \
    $(wildcard include/config/video/std/timings.h) \
    $(wildcard include/config/i2c/edid.h) \
    $(wildcard include/config/usb/ehci/hcd.h) \
    $(wildcard include/config/usb/ohci/new.h) \
    $(wildcard include/config/sys/usb/ohci/max/root/ports.h) \
    $(wildcard include/config/usb/storage.h) \
    $(wildcard include/config/cmd/pxe.h) \
    $(wildcard include/config/cmd/dhcp.h) \
    $(wildcard include/config/usb/keyboard.h) \
    $(wildcard include/config/video.h) \
    $(wildcard include/config/dm/video.h) \
    $(wildcard include/config/mtdids/default.h) \
    $(wildcard include/config/mtdparts/default.h) \
    $(wildcard include/config/default/device/tree.h) \
    $(wildcard include/config/extra/env/settings.h) \
  arch/arm/include/asm/arch/cpu.h \
    $(wildcard include/config/mach/sun50i/h6.h) \
  arch/arm/include/asm/arch/cpu_sun4i.h \
    $(wildcard include/config/mach/sun8i/a83t.h) \
    $(wildcard include/config/mach/sunxi/h3/h5.h) \
    $(wildcard include/config/sunxi/gen/sun4i.h) \
    $(wildcard include/config/mach/sun50i.h) \
    $(wildcard include/config/sunxi/gen/sun6i.h) \
    $(wildcard include/config/mach/sun7i.h) \
    $(wildcard include/config/mach/sun8i/r40.h) \
    $(wildcard include/config/mach/sun6i.h) \
    $(wildcard include/config/mach/sun8i/h3.h) \
    $(wildcard include/config/mach/sun50i/h5.h) \
  include/linux/stringify.h \
  include/config_distro_bootcmd.h \
    $(wildcard include/config/cmd/mmc.h) \
    $(wildcard include/config/sandbox.h) \
    $(wildcard include/config/cmd/ubifs.h) \
    $(wildcard include/config/efi/loader.h) \
    $(wildcard include/config/arm.h) \
    $(wildcard include/config/x86/run/32bit.h) \
    $(wildcard include/config/x86/run/64bit.h) \
    $(wildcard include/config/arch/rv32i.h) \
    $(wildcard include/config/arch/rv64i.h) \
    $(wildcard include/config/sata.h) \
    $(wildcard include/config/nvme.h) \
    $(wildcard include/config/scsi.h) \
    $(wildcard include/config/ide.h) \
    $(wildcard include/config/dm/pci.h) \
    $(wildcard include/config/cmd/usb.h) \
    $(wildcard include/config/cmd/virtio.h) \
    $(wildcard include/config/x86.h) \
    $(wildcard include/config/bootcommand.h) \
  arch/arm/include/asm/config.h \
    $(wildcard include/config/lmb.h) \
    $(wildcard include/config/sys/boot/ramdisk/high.h) \
    $(wildcard include/config/arch/ls1021a.h) \
    $(wildcard include/config/cpu/pxa27x.h) \
    $(wildcard include/config/cpu/monahans.h) \
    $(wildcard include/config/cpu/pxa25x.h) \
    $(wildcard include/config/fsl/layerscape.h) \
  include/linux/kconfig.h \
  include/config_fallbacks.h \
    $(wildcard include/config/spl.h) \
    $(wildcard include/config/sys/baudrate/table.h) \
    $(wildcard include/config/cmd/kgdb.h) \
    $(wildcard include/config/sys/prompt.h) \
    $(wildcard include/config/sys/maxargs.h) \
  include/errno.h \
    $(wildcard include/config/errno/str.h) \
  include/linux/errno.h \
  include/time.h \
  include/linux/typecheck.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  arch/arm/include/asm/posix_types.h \
  arch/arm/include/asm/types.h \
    $(wildcard include/config/phys/64bit.h) \
    $(wildcard include/config/dma/addr/t/64bit.h) \
  include/asm-generic/int-ll64.h \
  /usr/lib/gcc-cross/arm-linux-gnueabi/9/include/stdbool.h \
  include/linux/printk.h \
    $(wildcard include/config/loglevel.h) \
  include/stdio.h \
    $(wildcard include/config/tpl/serial/support.h) \
    $(wildcard include/config/spl/serial/support.h) \
  /usr/lib/gcc-cross/arm-linux-gnueabi/9/include/stdarg.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/kasan.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/gcov/kernel.h) \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  include/linux/string.h \
  arch/arm/include/asm/string.h \
  include/linux/linux_string.h \
  include/linux/kernel.h \
  arch/arm/include/asm/u-boot.h \
  include/asm-generic/u-boot.h \
    $(wildcard include/config/mpc8xx.h) \
    $(wildcard include/config/e500.h) \
    $(wildcard include/config/mpc86xx.h) \
    $(wildcard include/config/m68k.h) \
    $(wildcard include/config/mpc83xx.h) \
    $(wildcard include/config/cpm2.h) \
    $(wildcard include/config/extra/clock.h) \
    $(wildcard include/config/has/eth1.h) \
    $(wildcard include/config/has/eth2.h) \
    $(wildcard include/config/has/eth3.h) \
    $(wildcard include/config/has/eth4.h) \
    $(wildcard include/config/has/eth5.h) \
  arch/arm/include/asm/u-boot-arm.h \
  arch/arm/include/asm/global_data.h \
    $(wildcard include/config/fsl/esdhc.h) \
    $(wildcard include/config/fsl/esdhc/imx.h) \
    $(wildcard include/config/u/qe.h) \
    $(wildcard include/config/at91family.h) \
    $(wildcard include/config/sys/mem/reserve/secure.h) \
    $(wildcard include/config/resv/ram.h) \
    $(wildcard include/config/arch/omap2plus.h) \
    $(wildcard include/config/fsl/lsch3.h) \
    $(wildcard include/config/sys/fsl/has/dp/ddr.h) \
    $(wildcard include/config/arch/imx8.h) \
  include/asm-generic/global_data.h \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/lcd.h) \
    $(wildcard include/config/post.h) \
    $(wildcard include/config/board/types.h) \
    $(wildcard include/config/dm.h) \
    $(wildcard include/config/timer.h) \
    $(wildcard include/config/of/live.h) \
    $(wildcard include/config/trace.h) \
    $(wildcard include/config/pci/bootdelay.h) \
    $(wildcard include/config/console/record.h) \
    $(wildcard include/config/bootstage.h) \
    $(wildcard include/config/log.h) \
    $(wildcard include/config/translation/offset.h) \
  include/fdtdec.h \
    $(wildcard include/config/of/prior/stage.h) \
    $(wildcard include/config/of/board.h) \
    $(wildcard include/config/of/separate.h) \
  include/linux/libfdt.h \
  include/linux/libfdt_env.h \
  arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/byteorder/swab.h \
  include/linux/byteorder/generic.h \
  include/vsprintf.h \
    $(wildcard include/config/panic/hang.h) \
  include/linux/../../scripts/dtc/libfdt/libfdt.h \
  include/linux/../../scripts/dtc/libfdt/libfdt_env.h \
  include/linux/../../scripts/dtc/libfdt/fdt.h \
  include/pci.h \
    $(wildcard include/config/sys/pci/64bit.h) \
    $(wildcard include/config/pci/indirect/bridge.h) \
    $(wildcard include/config/dm/pci/compat.h) \
    $(wildcard include/config/pci/fixup/dev.h) \
    $(wildcard include/config/mpc85xx.h) \
    $(wildcard include/config/pcie/imx.h) \
  include/pci_ids.h \
  include/dm/pci.h \
  include/membuff.h \
  include/linux/list.h \
  include/linux/poison.h \
  include/display_options.h \
  include/bootstage.h \
    $(wildcard include/config/show/boot/progress.h) \
  include/command.h \
    $(wildcard include/config/sys/help/cmd/width.h) \
    $(wildcard include/config/sys/longhelp.h) \
    $(wildcard include/config/auto/complete.h) \
    $(wildcard include/config/cmd/run.h) \
    $(wildcard include/config/cmd/memory.h) \
    $(wildcard include/config/cmd/i2c.h) \
    $(wildcard include/config/cmd/itest.h) \
    $(wildcard include/config/cmd/pci.h) \
    $(wildcard include/config/cmd/setexpr.h) \
    $(wildcard include/config/cmd/bootd.h) \
    $(wildcard include/config/cmd/bootm.h) \
    $(wildcard include/config/cmd/nvedit/efi.h) \
    $(wildcard include/config/cmdline.h) \
    $(wildcard include/config/needs/manual/reloc.h) \
  include/env.h \
  include/compiler.h \
  /usr/lib/gcc-cross/arm-linux-gnueabi/9/include/stddef.h \
  include/linker_lists.h \
  include/cpu_func.h \
  include/dm.h \
  include/dm/device.h \
    $(wildcard include/config/devres.h) \
  include/dm/ofnode.h \
  include/dm/of.h \
  include/dm/uclass-id.h \
  include/dm/fdtaddr.h \
  include/dm/read.h \
    $(wildcard include/config/dm/dev/read/inline.h) \
  include/dm/uclass.h \
  include/dm/platdata.h \
  include/hang.h \
  include/lmb.h \
  include/log.h \
    $(wildcard include/config/log/max/level.h) \
    $(wildcard include/config/log/error/return.h) \
  include/dm/root.h \
  include/image.h \
    $(wildcard include/config/fit/verbose.h) \
    $(wildcard include/config/fit/enable/rsassa/pss/support.h) \
    $(wildcard include/config/fit/enable/sha256/support.h) \
    $(wildcard include/config/sha1.h) \
    $(wildcard include/config/sha256.h) \
    $(wildcard include/config/spl/crc32/support.h) \
    $(wildcard include/config/spl/md5/support.h) \
    $(wildcard include/config/spl/sha1/support.h) \
    $(wildcard include/config/spl/sha256/support.h) \
    $(wildcard include/config/sys/boot/get/cmdline.h) \
    $(wildcard include/config/of/board/setup.h) \
    $(wildcard include/config/of/system/setup.h) \
    $(wildcard include/config/timestamp.h) \
    $(wildcard include/config/cmd/date.h) \
    $(wildcard include/config/legacy/image/format.h) \
    $(wildcard include/config/sys/boot/get/kbd.h) \
    $(wildcard include/config/fit/signature.h) \
    $(wildcard include/config/fit/best/match.h) \
    $(wildcard include/config/fit/cipher.h) \
    $(wildcard include/config/fit.h) \
    $(wildcard include/config/android/boot/image.h) \
    $(wildcard include/config/spl/fit/image/post/process.h) \
    $(wildcard include/config/fit/image/post/process.h) \
  include/compiler.h \
  include/hash.h \
  include/fdt_support.h \
    $(wildcard include/config/arch/fixup/fdt/memory.h) \
    $(wildcard include/config/usb/ehci/fsl.h) \
    $(wildcard include/config/usb/xhci/fsl.h) \
    $(wildcard include/config/sys/fsl/sec/compat.h) \
    $(wildcard include/config/sys/fdt/pad.h) \
    $(wildcard include/config/fdt/fixup/partitions.h) \
    $(wildcard include/config/fman/enet.h) \
    $(wildcard include/config/fsl/mc/enet.h) \
  include/u-boot/zlib.h \
  include/mapmem.h \
    $(wildcard include/config/arch/map/sysmem.h) \
  arch/arm/include/asm/bootm.h \
    $(wildcard include/config/revision/tag.h) \
  arch/arm/include/asm/secure.h \
    $(wildcard include/config/armv7/secure/base.h) \
    $(wildcard include/config/armv8/secure/base.h) \
  include/bootm.h \
  include/vxworks.h \
  include/efi_api.h \
  include/efi.h \
    $(wildcard include/config/efi/stub/64bit.h) \
    $(wildcard include/config/x86/64.h) \
  include/linux/linkage.h \
  arch/arm/include/asm/linkage.h \
  include/charset.h \
  include/pe.h \
  include/asm-generic/pe.h \
  arch/arm/include/asm/cache.h \
    $(wildcard include/config/sys/cacheline/size.h) \
  arch/arm/include/asm/system.h \
    $(wildcard include/config/armv7/lpae.h) \
    $(wildcard include/config/cpu/v7a.h) \
    $(wildcard include/config/sys/arm/cache/writethrough.h) \
    $(wildcard include/config/sys/arm/cache/writealloc.h) \
    $(wildcard include/config/sys/arm/cache/writeback.h) \
    $(wildcard include/config/armv7/psci.h) \
    $(wildcard include/config/sys/noncached/memory.h) \
  arch/arm/include/asm/barriers.h \
  arch/arm/include/asm/setup.h \

arch/arm/lib/bootm.o: $(deps_arch/arm/lib/bootm.o)

$(deps_arch/arm/lib/bootm.o):
