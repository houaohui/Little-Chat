cmd_spl/drivers/built-in.o :=  arm-linux-gnueabi-ld.bfd     -r -o spl/drivers/built-in.o spl/drivers/gpio/built-in.o spl/drivers/mmc/built-in.o spl/drivers/mtd/built-in.o spl/drivers/serial/built-in.o spl/drivers/power/built-in.o spl/drivers/power/pmic/built-in.o spl/drivers/power/regulator/built-in.o spl/drivers/block/built-in.o spl/drivers/soc/built-in.o 
