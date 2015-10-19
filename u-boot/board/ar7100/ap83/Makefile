include $(TOPDIR)/config.mk

LIB	= lib$(BOARD).a

#OBJS	= $(BOARD).o ../common/ar9100_pflash.o ../common/vsc8601_phy.o ../common/generic_spi.o ../common/vsc73xx.o

SWITCH_CHIP=rtl8366rb
ifeq ($(strip $(SWITCH_CHIP)),rtl8366rb)
SWITCH_CHIP_OBJS = ../common/rtl8366rb/rtl_phy.o ../common/rtl8366rb/smi.o ../common/rtl8366rb/rtl8366rb_api_compat.o
endif

ifeq ($(strip $(SWITCH_CHIP)),rtl8366sr)
SWITCH_CHIP_OBJS = ../common/rtl8366sr/rtl_phy.o ../common/rtl8366sr/smi.o ../common/rtl8366sr/rtl8366s_api_compat.o
endif

OBJS	= $(BOARD).o flash.o ../common/ar7100_flash.o $(SWITCH_CHIP_OBJS)

SOBJS	= ../common/lowlevel_init_ar9100.o

$(LIB):	.depend $(OBJS) $(SOBJS)
	$(AR) crv $@ $(OBJS) $(SOBJS)

#########################################################################

.depend:	Makefile $(SOBJS:.o=.S) $(OBJS:.o=.c)
		$(CC) -M $(CFLAGS) $(SOBJS:.o=.S) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################
