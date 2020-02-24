if [ $1 == "nand" ] 
then
echo "#define DOPI_SPI_NAND ">include/configs/dopi.h
make ARCH=arm CROSS_COMPILE=arm-himix100-linux-  hi3516ev200_config
echo "DOPI_SPI_NAND=y">>./.config
make ARCH=arm CROSS_COMPILE=arm-himix100-linux- 
cp reg_info.bin .reg
make ARCH=arm CROSS_COMPILE=arm-himix100-linux- u-boot-z.bin
    echo " build spi nand flash version"
else
	echo "build spi nor flash version"
echo "#define DOPI_SPI_NOR ">include/configs/dopi.h
make ARCH=arm CROSS_COMPILE=arm-himix100-linux- hi3516ev200_config
make ARCH=arm CROSS_COMPILE=arm-himix100-linux- 
cp reg_info.bin .reg
make ARCH=arm CROSS_COMPILE=arm-himix100-linux- u-boot-z.bin
fi

