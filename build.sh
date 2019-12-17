make ARCH=arm CROSS_COMPILE=arm-himix100-linux- hi3516ev200_config
make ARCH=arm CROSS_COMPILE=arm-himix100-linux- 
cp reg_info.bin .reg
make ARCH=arm CROSS_COMPILE=arm-himix100-linux- u-boot-z.bin

