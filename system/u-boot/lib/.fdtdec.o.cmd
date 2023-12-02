cmd_lib/fdtdec.o := arm-linux-gnueabi-gcc -Wp,-MD,lib/.fdtdec.o.d  -nostdinc -isystem /usr/lib/gcc-cross/arm-linux-gnueabi/9/include -Iinclude    -I./arch/arm/thumb1/include -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -std=gnu11 -fshort-wchar -fno-strict-aliasing -fno-PIE -Os -fno-stack-protector -fno-delete-null-pointer-checks -Wno-stringop-truncation -fmacro-prefix-map=./= -g -fstack-usage -Wno-format-nonliteral -Wno-address-of-packed-member -Wno-unused-but-set-variable -Werror=date-time -D__ARM__ -Wa,-mimplicit-it=always -mthumb -mthumb-interwork -mabi=aapcs-linux -mword-relocations -fno-pic -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float -pipe -march=armv5te -D__LINUX_ARM_ARCH__=5 -I./arch/arm/mach-sunxi/include    -DKBUILD_BASENAME='"fdtdec"'  -DKBUILD_MODNAME='"fdtdec"' -c -o lib/fdtdec.o lib/fdtdec.c

source_lib/fdtdec.o := lib/fdtdec.c

deps_lib/fdtdec.o := \
    $(wildcard include/config/dm/pci.h) \
    $(wildcard include/config/spl/build.h) \
    $(wildcard include/config/of/embed.h) \
    $(wildcard include/config/nr/dram/banks.h) \
    $(wildcard include/config/of/board.h) \
    $(wildcard include/config/of/separate.h) \
    $(wildcard include/config/spl/separate/bss.h) \
    $(wildcard include/config/of/hostfile.h) \
    $(wildcard include/config/of/prior/stage.h) \
  include/linux/kconfig.h \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
    $(wildcard include/config/spl/.h) \
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
    $(wildcard include/config/arm64.h) \
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
  include/boot_fit.h \
  include/dm.h \
  include/dm/device.h \
    $(wildcard include/config/devres.h) \
  include/dm/ofnode.h \
  include/dm/of.h \
  include/dm/uclass-id.h \
  include/linker_lists.h \
  include/dm/fdtaddr.h \
  include/dm/read.h \
    $(wildcard include/config/dm/dev/read/inline.h) \
  include/dm/uclass.h \
  include/dm/platdata.h \
  include/hang.h \
  include/init.h \
    $(wildcard include/config/efi/stub.h) \
    $(wildcard include/config/dtb/reselect.h) \
    $(wildcard include/config/vid.h) \
  include/log.h \
    $(wildcard include/config/log/max/level.h) \
    $(wildcard include/config/log/error/return.h) \
  include/malloc.h \
  include/net.h \
    $(wildcard include/config/sys/rx/eth/buffer.h) \
    $(wildcard include/config/dm/eth.h) \
    $(wildcard include/config/api.h) \
    $(wildcard include/config/bootp/dns2.h) \
    $(wildcard include/config/cmd/dns.h) \
    $(wildcard include/config/cmd/ping.h) \
    $(wildcard include/config/cmd/cdp.h) \
    $(wildcard include/config/cmd/sntp.h) \
    $(wildcard include/config/netconsole.h) \
    $(wildcard include/config/reset/phy/r.h) \
  arch/arm/include/asm/cache.h \
    $(wildcard include/config/sys/cacheline/size.h) \
  arch/arm/include/asm/system.h \
    $(wildcard include/config/armv8/psci.h) \
    $(wildcard include/config/armv7/lpae.h) \
    $(wildcard include/config/cpu/v7a.h) \
    $(wildcard include/config/sys/arm/cache/writethrough.h) \
    $(wildcard include/config/sys/arm/cache/writealloc.h) \
    $(wildcard include/config/sys/arm/cache/writeback.h) \
    $(wildcard include/config/armv7/psci.h) \
    $(wildcard include/config/sys/noncached/memory.h) \
  arch/arm/include/asm/barriers.h \
  include/env.h \
  include/compiler.h \
  /usr/lib/gcc-cross/arm-linux-gnueabi/9/include/stddef.h \
  include/linux/if_ether.h \
  include/rand.h \
  include/dm/of_extra.h \
  include/fdt_support.h \
    $(wildcard include/config/of/libfdt.h) \
    $(wildcard include/config/arch/fixup/fdt/memory.h) \
    $(wildcard include/config/usb/ehci/fsl.h) \
    $(wildcard include/config/usb/xhci/fsl.h) \
    $(wildcard include/config/sys/fsl/sec/compat.h) \
    $(wildcard include/config/sys/fdt/pad.h) \
    $(wildcard include/config/of/board/setup.h) \
    $(wildcard include/config/of/system/setup.h) \
    $(wildcard include/config/fdt/fixup/partitions.h) \
    $(wildcard include/config/fman/enet.h) \
    $(wildcard include/config/fsl/mc/enet.h) \
  include/gzip.h \
  include/mapmem.h \
    $(wildcard include/config/arch/map/sysmem.h) \
  include/serial.h \
    $(wildcard include/config/sys/post/uart.h) \
    $(wildcard include/config/arch/tegra.h) \
    $(wildcard include/config/sys/coreboot.h) \
    $(wildcard include/config/microblaze.h) \
    $(wildcard include/config/usb/tty.h) \
  include/post.h \
    $(wildcard include/config/post/external/word/funcs.h) \
    $(wildcard include/config/sys/post/word/addr.h) \
    $(wildcard include/config/arch/mpc8360.h) \
    $(wildcard include/config/sys/immr.h) \
    $(wildcard include/config/sys/mpc85xx/pic/offset.h) \
    $(wildcard include/config/sys/mpc86xx/pic/offset.h) \
    $(wildcard include/config/needs/manual/reloc.h) \
    $(wildcard include/config/sys/post/rtc.h) \
    $(wildcard include/config/sys/post/watchdog.h) \
    $(wildcard include/config/sys/post/memory.h) \
    $(wildcard include/config/sys/post/cpu.h) \
    $(wildcard include/config/sys/post/i2c.h) \
    $(wildcard include/config/sys/post/cache.h) \
    $(wildcard include/config/sys/post/ether.h) \
    $(wildcard include/config/sys/post/usb.h) \
    $(wildcard include/config/sys/post/spr.h) \
    $(wildcard include/config/sys/post/sysmon.h) \
    $(wildcard include/config/sys/post/dsp.h) \
    $(wildcard include/config/sys/post/ocm.h) \
    $(wildcard include/config/sys/post/fpu.h) \
    $(wildcard include/config/sys/post/ecc.h) \
    $(wildcard include/config/sys/post/bspec1.h) \
    $(wildcard include/config/sys/post/bspec2.h) \
    $(wildcard include/config/sys/post/bspec3.h) \
    $(wildcard include/config/sys/post/bspec4.h) \
    $(wildcard include/config/sys/post/bspec5.h) \
    $(wildcard include/config/sys/post/codec.h) \
    $(wildcard include/config/sys/post/coproc.h) \
    $(wildcard include/config/sys/post/flash.h) \
    $(wildcard include/config/sys/post/mem/regions.h) \
  arch/arm/include/asm/io.h \
  arch/arm/include/asm/memory.h \
    $(wildcard include/config/discontigmem.h) \
  include/asm-generic/io.h \
  include/iotrace.h \
    $(wildcard include/config/io/trace.h) \
  arch/arm/include/asm/sections.h \
  include/asm-generic/sections.h \
  include/linux/ctype.h \
  include/linux/lzo.h \

lib/fdtdec.o: $(deps_lib/fdtdec.o)

$(deps_lib/fdtdec.o):
