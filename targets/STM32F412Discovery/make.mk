
BUILDDIR         := build/$(TARGET)
OPTLVL           := s
TOOLCHAIN_PREFIX := /opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi
OPENOCDCFG        = /usr/share/openocd/scripts/board/stm32f429discovery.cfg
AS                = $(TOOLCHAIN_PREFIX)-as
AR                = $(TOOLCHAIN_PREFIX)-ar
CC                = $(TOOLCHAIN_PREFIX)-gcc
LD                = $(TOOLCHAIN_PREFIX)-gcc
GDB               = $(TOOLCHAIN_PREFIX)-gdb
SIZE              = $(TOOLCHAIN_PREFIX)-size
OBJCOPY           = $(TOOLCHAIN_PREFIX)-objcopy
EXTLIBS          := Libraries
MISCLIB          := $(EXTLIBS)/STM32F4
CMSIS            := $(EXTLIBS)/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/Libraries/CMSIS
DSPLIB           := $(CMSIS)/DSP_Lib
STD_PERIPH       := $(EXTLIBS)/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/Libraries/STM32F4xx_StdPeriph_Driver
USB_LIB          := $(EXTLIBS)/STM32_USB_OTG_Driver

INCLUDE += -I$(STD_PERIPH)/inc
INCLUDE += -I$(MISCLIB)
INCLUDE += -I$(CMSIS)/Include
INCLUDE += -I$(CMSIS)/Device/ST/STM32F4xx/Include
INCLUDE += -I$(EXTLIBS)/STM32_USB_OTG_Driver/inc
INCLUDE += -I$(EXTLIBS)/STM32_USB_Device_Library/Core/inc
INCLUDE += -I$(EXTLIBS)/STM32_USB_Device_Library/Class/cdc/inc

INCLUDE += -I$(CURDIR)/src
INCLUDE += -Itargets/$(TARGET)
INCLUDE += -I$(MISCLIB)/usb
INCLUDE += -I$(MISCLIB)/serial
INCLUDE += -I$(MISCLIB)/i2c
INCLUDE += -I$(MISCLIB)/spi
INCLUDE += -I$(MISCLIB)/systick

STM_SRC  = 
STM_SRC += $(STD_PERIPH)/src/misc.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_adc.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_can.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_crc.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_dma.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_i2c.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_pwr.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_rcc.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_rng.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_rtc.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_sai.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_spi.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_tim.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_gpio.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_hash.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_exti.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_iwdg.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_ltdc.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_sdio.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_wwdg.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_flash.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_usart.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_syscfg.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_dbgmcu.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_hash_md5.c
STM_SRC += $(STD_PERIPH)/src/stm32f4xx_hash_sha1.c
STM_SRC += $(DSPLIB)/Source/SupportFunctions/arm_fill_f32.c
STM_SRC += $(DSPLIB)/Source/SupportFunctions/arm_copy_f32.c
STM_SRC += $(DSPLIB)/Source/StatisticsFunctions/arm_std_f32.c
STM_SRC += $(DSPLIB)/Source/BasicMathFunctions/arm_scale_f32.c
STM_SRC += $(DSPLIB)/Source/MatrixFunctions/arm_mat_mult_f32.c
STM_SRC += $(DSPLIB)/Source/MatrixFunctions/arm_mat_init_f32.c
STM_SRC += $(DSPLIB)/Source/MatrixFunctions/arm_mat_trans_f32.c
STM_SRC += $(DSPLIB)/Source/MatrixFunctions/arm_mat_inverse_f32.c
STM_SRC += $(MISCLIB)/system_stm32f4xx.c
STM_SRC += targets/$(TARGET)/syscalls.c
STM_SRC += targets/$(TARGET)/system.c

STM_SRC += $(EXTLIBS)/STM32_USB_Device_Library/Class/cdc/src/usbd_cdc_core_loopback.c
STM_SRC += $(EXTLIBS)/STM32_USB_Device_Library/Core/src/usbd_core.c
STM_SRC += $(EXTLIBS)/STM32_USB_Device_Library/Core/src/usbd_ioreq.c
STM_SRC += $(EXTLIBS)/STM32_USB_Device_Library/Core/src/usbd_req.c
STM_SRC += $(EXTLIBS)/STM32_USB_OTG_Driver/src/usb_core.c
STM_SRC += $(EXTLIBS)/STM32_USB_OTG_Driver/src/usb_dcd.c
STM_SRC += $(EXTLIBS)/STM32_USB_OTG_Driver/src/usb_dcd_int.c

STM_SRC += $(MISCLIB)/usb/usb_bsp.c
STM_SRC += $(MISCLIB)/usb/usbd_cdc_vcp.c
STM_SRC += $(MISCLIB)/usb/usbd_desc.c
STM_SRC += $(MISCLIB)/usb/usbd_usr.c
STM_SRC += $(MISCLIB)/usb/usb.c
STM_SRC += $(MISCLIB)/systick/systick.c
STM_SRC += $(MISCLIB)/serial/serial.c
STM_SRC += $(MISCLIB)/i2c/i2c.c
STM_SRC += $(MISCLIB)/spi/spi.c



MCUFLAGS  = -mcpu=cortex-m4 -mthumb -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard
MCUFLAGS += -fsingle-precision-constant -Wall -finline-functions
MCUFLAGS += -Wdouble-promotion -std=c99 -fno-dwarf2-cfi-asm  -mno-thumb-interwork
MCUFLAGS += -ffunction-sections -fdata-sections -fno-common -fmessage-length=0

CDEFS = -DUSE_STDPERIPH_DRIVER -D__FPU_USED -D__FPU_PRESENT=1 -D__SIZEOF_WCHAR_T=4 -D__ARM_ARCH_7EM__
CDEFS += -D__FPU_PRESENT=1 -DARM_MATH_CM4 -D__THUMB -DNESTED_INTERRUPTS -DCTL_TASKING
CDEFS += -DUSE_USB_OTG_FS



STMTYPE        = STM32F412xG
RCC_OPT        = -DHSE_VALUE=8000000 -DPLL_M=8
LINKER_SCRIPT  = $(MISCLIB)/STM32F412ZGTx_FLASH.ld
ASM_SRC        = $(MISCLIB)/startup_stm32f40_41xxx.s


COMMONFLAGS = -O$(OPTLVL) -g -Wall
CFLAGS      = $(COMMONFLAGS) $(MCUFLAGS) $(INCLUDE) $(CDEFS) $(RCC_OPT) -D$(STMTYPE)
LDLIBS      = -lm -lc -lg
LDFLAGS     = $(COMMONFLAGS) $(MCUFLAGS) -fno-exceptions -ffunction-sections -fdata-sections -nostartfiles -Wl,-T,$(LINKER_SCRIPT)
LDFLAGS    += -Wl,--gc-sections -Wl,--Map=$(BUILDDIR)/$(NAME).map
OBJ         = $(STM_SRC:%.c=$(BUILDDIR)/%.o) $(SRC:%.c=$(BUILDDIR)/%.o) $(ASM_SRC:%.s=$(BUILDDIR)/%.o)

all: $(OBJ)
	$(CC) -o $(BUILDDIR)/$(NAME).elf $(LDFLAGS) $(OBJ) $(LDLIBS)
	$(OBJCOPY) --remove-section .ccm -O ihex   $(BUILDDIR)/$(NAME).elf $(BUILDDIR)/$(NAME).hex
	$(OBJCOPY) --remove-section .ccm -O binary $(BUILDDIR)/$(NAME).elf $(BUILDDIR)/$(NAME).bin

clean:
	rm -f $(OBJ)
	rm -f $(BUILDDIR)/$(NAME).elf
	rm -f $(BUILDDIR)/$(NAME).hex
	rm -f $(BUILDDIR)/$(NAME).bin
	rm -f $(BUILDDIR)/$(NAME).map

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $^

flash: $(BUILDDIR)/$(NAME).bin
	st-flash write $(BUILDDIR)/$(NAME).bin 0x8000000


monitor:
	sleep .5
	gtkterm --port /dev/ttyACM0 --speed 115200

