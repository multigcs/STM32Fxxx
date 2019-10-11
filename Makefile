
TARGET           := BluePill
NAME             := blink


SRC += src/main.c

include Libraries/framebuffer/make.mk
include Libraries/ili9163/make.mk
include Libraries/timer/make.mk


include targets/$(TARGET)/make.mk


