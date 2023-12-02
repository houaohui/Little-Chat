cmd_u-boot-dtb.img := ./tools/mkimage -A arm -T firmware -C none -O u-boot -a 0x81700000 -e 0x81700000 -n "U-Boot 2020.07""-g079f7ac1 for sunxi board" -d u-boot.bin u-boot-dtb.img >/dev/null 
