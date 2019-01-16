
#ifndef __USB_CONF__H__
#define __USB_CONF__H__

#include "stm32f4xx.h"

#define USB_OTG_FS_CORE


#define RX_FIFO_FS_SIZE                          128
#define TX0_FIFO_FS_SIZE                          64
#define TX1_FIFO_FS_SIZE                         128
#define TX2_FIFO_FS_SIZE                          0
#define TX3_FIFO_FS_SIZE                          0
#define USE_DEVICE_MODE
//#define VBUS_SENSING_ENABLED

#define __ALIGN_BEGIN
#define __ALIGN_END   


#if defined (__CC_ARM)         /* ARM Compiler */
  #define __packed    __packed
#elif defined (__ICCARM__)     /* IAR Compiler */
  #define __packed    __packed
#elif defined   ( __GNUC__ )   /* GNU Compiler */ 
#ifdef __packed
#undef __packed
#endif
  #define __packed    __attribute__ ((__packed__))
#elif defined   (__TASKING__)  /* TASKING Compiler */
  #define __packed    __unaligned
#endif /* __CC_ARM */



#endif /*__USB_CONF__H__*/

