sinclude $(TOPDIR)/config.mk

#LIB := $(obj)libao.a

ifeq ($(CONFIG_PRODUCTNAME), "hi3516ev200")
	cflags-y  += -DAO_PRODUCT_HI3516EV200
else ifeq ($(CONFIG_PRODUCTNAME), "hi3516ev300")
	cflags-y  += -DAO_PRODUCT_HI3516EV300
else ifeq ($(CONFIG_PRODUCTNAME), "hi3518ev300")
	cflags-y  += -DAO_PRODUCT_HI3518EV300
else ifeq ($(CONFIG_PRODUCTNAME), "hi3516dv200")
	cflags-y  += -DAO_PRODUCT_HI3516DV200
endif

ccflags-y  += $(cflags-y)
HOSTCFLAGS += $(cflags-y)
CPPFLAGS   += $(cflags-y)

obj-y += amp.o
obj-y += aiao_hal.o
obj-y += ao.o

#COBJS	:= $(COBJS-y)
#SRCS	:= $(COBJS:.o=.c)
#OBJS	:= $(addprefix $(obj),$(COBJS))

#all:	$(LIB)

#$(LIB):	$(obj).depend $(OBJS)
#	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
#include $(SRCTREE)/rules.mk

#sinclude $(obj).depend

#########################################################################

