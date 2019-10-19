
obj-y += jpegd_entry.o
obj-y += jpegd.o
obj-y += jpegd_drv.o
obj-y += jpegd_image.o

ifeq ($(CONFIG_PRODUCTNAME), "hi3559av100")
ccflags-y  += -DCHIP_HI3559AV100
else ifeq ($(CONFIG_PRODUCTNAME), "hi3519av100")
ccflags-y  += -DCHIP_HI3519AV100
else ifeq ($(CONFIG_PRODUCTNAME), "hi3516dv300")
ccflags-y  += -DCHIP_HI3516CV500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3516av300")
ccflags-y  += -DCHIP_HI3516CV500
endif


