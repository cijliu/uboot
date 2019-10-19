#ifndef __HISILICON_I2C_DRIVER_HEADER__
#define __HISILICON_I2C_DRIVER_HEADER__

void hibvt_i2c_init(void);
int i2c_read(unsigned char chip, unsigned int addr, int alen, unsigned char *buffer, int len);
int i2c_write(unsigned char chip, unsigned int addr, int alen, unsigned char *buffer, int len);

#endif
