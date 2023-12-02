CONFIG_MMC_SUNXI_SLOT=0
CONFIG_IS_MODULE(option)="config_enabled(CONFIG_VAL(option ##_MODULE))"
CONFIG_SYS_LOAD_ADDR=0x81000000
CONFIG_SYS_INIT_RAM_ADDR=$(CONFIG_SUNXI_SRAM_ADDRESS)
CONFIG_SYS_CBSIZE=1024
CONFIG_SYS_MONITOR_LEN="(768 << 10)"
CONFIG_SYS_SPD_BUS_NUM=0
CONFIG_INITRD_TAG=y
CONFIG_SPL_BUILD=y
CONFIG_SYS_MALLOC_LEN="(CONFIG_ENV_SIZE + (1 << 20))"
CONFIG_IS_BUILTIN(option)="config_enabled(CONFIG_VAL(option))"
CONFIG_SYS_NS16550_SERIAL=y
CONFIG_SYS_MAXARGS=16
CONFIG_SPL_BOARD_LOAD_IMAGE=y
CONFIG_SYS_PBSIZE=1024
CONFIG_BOARDDIR="board/sunxi"
CONFIG_SPL_STACK="LOW_LEVEL_SRAM_STACK"
CONFIG_STANDALONE_LOAD_ADDR=$(CONFIG_SYS_LOAD_ADDR)
CONFIG_SYS_NS16550_CLK=100000000
CONFIG_SYS_INIT_RAM_SIZE=0x8000
CONFIG_SYS_BAUDRATE_TABLE="{ 9600, 19200, 38400, 57600, 115200 }"
CONFIG_SYS_NS16550_COM1="SUNXI_UART0_BASE"
CONFIG_SYS_NS16550_COM2="SUNXI_UART1_BASE"
CONFIG_SYS_NS16550_COM3="SUNXI_UART2_BASE"
CONFIG_SYS_NS16550_COM4="SUNXI_UART3_BASE"
CONFIG_SYS_NS16550_COM5="SUNXI_R_UART_BASE"
CONFIG_VAL(option)="config_val(option)"
CONFIG_SYS_SDRAM_BASE=0x80000000
CONFIG_VIDEO_LCD_I2C_BUS=-1
CONFIG_SYS_BOOT_RAMDISK_HIGH=y
CONFIG_SYS_INIT_SP_OFFSET="(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)"
CONFIG_SPL_BSS_MAX_SIZE=0x00080000
CONFIG_SPL_BSS_START_ADDR=0x81f80000
CONFIG_SPL_PAD_TO=32768
CONFIG_EXTRA_ENV_SETTINGS=y
CONFIG_SYS_INIT_SP_ADDR="(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)"
CONFIG_CMDLINE_TAG=y
CONFIG_SYS_NS16550_REG_SIZE=-4
CONFIG_SPL_MAX_SIZE=0x5fa0
CONFIG_SETUP_MEMORY_TAGS=y
CONFIG_MACH_TYPE_COMPAT_REV=y
CONFIG_LMB=y
CONFIG_IS_ENABLED(option)="(config_enabled(CONFIG_VAL(option)) || config_enabled(CONFIG_VAL(option ##_MODULE)))"
CONFIG_SERIAL_TAG=y
