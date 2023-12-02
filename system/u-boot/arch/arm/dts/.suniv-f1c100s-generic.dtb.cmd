cmd_arch/arm/dts/suniv-f1c100s-generic.dtb := mkdir -p arch/arm/dts/ ; (cat arch/arm/dts/suniv-f1c100s-generic.dts; echo '$(pound)include "sunxi-u-boot.dtsi"') > arch/arm/dts/.suniv-f1c100s-generic.dtb.pre.tmp; arm-linux-gnueabi-gcc -E -Wp,-MD,arch/arm/dts/.suniv-f1c100s-generic.dtb.d.pre.tmp -nostdinc -I./arch/arm/dts -I./arch/arm/dts/include -Iinclude -I./include -I./arch/arm/include -include ./include/linux/kconfig.h -D__ASSEMBLY__ -undef -D__DTS__ -x assembler-with-cpp -o arch/arm/dts/.suniv-f1c100s-generic.dtb.dts.tmp arch/arm/dts/.suniv-f1c100s-generic.dtb.pre.tmp ; ./scripts/dtc/dtc -O dtb -o arch/arm/dts/suniv-f1c100s-generic.dtb -b 0 -i arch/arm/dts/  -Wno-unit_address_vs_reg -Wno-unit_address_format -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-graph_port -Wno-unique_unit_address -Wno-simple_bus_reg -Wno-pci_device_reg -Wno-pci_bridge -Wno-pci_device_bus_num   -Wno-unit_address_vs_reg -Wno-unit_address_format -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-graph_port -Wno-unique_unit_address -Wno-simple_bus_reg -Wno-pci_device_reg -Wno-pci_bridge -Wno-pci_device_bus_num  -d arch/arm/dts/.suniv-f1c100s-generic.dtb.d.dtc.tmp arch/arm/dts/.suniv-f1c100s-generic.dtb.dts.tmp || (echo "Check /home/hah/linux/f1c2000/u-boot/arch/arm/dts/.suniv-f1c100s-generic.dtb.pre.tmp for errors" && false) ; cat arch/arm/dts/.suniv-f1c100s-generic.dtb.d.pre.tmp arch/arm/dts/.suniv-f1c100s-generic.dtb.d.dtc.tmp > arch/arm/dts/.suniv-f1c100s-generic.dtb.d ; sed -i "s:arch/arm/dts/.suniv-f1c100s-generic.dtb.pre.tmp:arch/arm/dts/suniv-f1c100s-generic.dts:" arch/arm/dts/.suniv-f1c100s-generic.dtb.d

source_arch/arm/dts/suniv-f1c100s-generic.dtb := arch/arm/dts/suniv-f1c100s-generic.dts

deps_arch/arm/dts/suniv-f1c100s-generic.dtb := \
  include/linux/kconfig.h \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
    $(wildcard include/config/spl/.h) \
    $(wildcard include/config/spl/build.h) \
    $(wildcard include/config/tpl/build.h) \
    $(wildcard include/config/tpl/.h) \
    $(wildcard include/config/spl/foo.h) \
    $(wildcard include/config/tpl/foo.h) \
  arch/arm/dts/suniv-f1c100s.dtsi \
  arch/arm/dts/suniv.dtsi \
  arch/arm/dts/include/dt-bindings/clock/suniv-ccu.h \
  arch/arm/dts/include/dt-bindings/reset/suniv-ccu.h \
  arch/arm/dts/include/dt-bindings/gpio/gpio.h \
  arch/arm/dts/sunxi-u-boot.dtsi \
    $(wildcard include/config/spl/pad/to.h) \
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

arch/arm/dts/suniv-f1c100s-generic.dtb: $(deps_arch/arm/dts/suniv-f1c100s-generic.dtb)

$(deps_arch/arm/dts/suniv-f1c100s-generic.dtb):
