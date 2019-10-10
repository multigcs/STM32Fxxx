
TARGET           := BluePill
NAME             := blink


INCLUDE += -Isrc/ssd1306
INCLUDE += -Isrc/ssd1351
INCLUDE += -Isrc/framebuffer
INCLUDE += -Isrc/timer

SRC += src/main.c
SRC += src/ssd1306/ssd1306.c

SRC += src/ssd1351/ssd1351.c
SRC += src/framebuffer/framebuffer.c

SRC += src/timer/timer.c



include targets/$(TARGET)/make.mk


