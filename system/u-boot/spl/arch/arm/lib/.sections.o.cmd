cmd_spl/arch/arm/lib/sections.o := arm-linux-gnueabi-gcc -Wp,-MD,spl/arch/arm/lib/.sections.o.d  -nostdinc -isystem /usr/lib/gcc-cross/arm-linux-gnueabi/9/include -Ispl/include -Iinclude    -I./arch/arm/thumb1/include -I./arch/arm/include -include ./include/linux/kconfig.h -D__KERNEL__ -D__UBOOT__ -DCONFIG_SPL_BUILD -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -std=gnu11 -fshort-wchar -fno-strict-aliasing -fno-PIE -Os -fno-stack-protector -fno-delete-null-pointer-checks -Wno-stringop-truncation -fmacro-prefix-map=./= -g -fstack-usage -Wno-format-nonliteral -Wno-address-of-packed-member -Wno-unused-but-set-variable -Werror=date-time -ffunction-sections -fdata-sections -D__ARM__ -Wa,-mimplicit-it=always -mthumb -mthumb-interwork -mabi=aapcs-linux -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float -pipe -march=armv5te -D__LINUX_ARM_ARCH__=5 -I./arch/arm/mach-sunxi/include    -DKBUILD_BASENAME='"sections"'  -DKBUILD_MODNAME='"sections"' -c -o spl/arch/arm/lib/sections.o arch/arm/lib/sections.c

source_spl/arch/arm/lib/sections.o := arch/arm/lib/sections.c

deps_spl/arch/arm/lib/sections.o := \
  include/linux/kconfig.h \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
    $(wildcard include/config/spl/.h) \
    $(wildcard include/config/spl/build.h) \
    $(wildcard include/config/tpl/build.h) \
    $(wildcard include/config/tpl/.h) \
    $(wildcard include/config/spl/foo.h) \
    $(wildcard include/config/tpl/foo.h) \

spl/arch/arm/lib/sections.o: $(deps_spl/arch/arm/lib/sections.o)

$(deps_spl/arch/arm/lib/sections.o):
