
#include <usb.h>

__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;
uint8_t Rxbuffer[64]; 
__IO uint32_t receive_count = 1;



void OTG_FS_WKUP_IRQHandler(void) {
	if (USB_OTG_dev.cfg.low_power) {
		*(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9;
		SystemInit();
		USB_OTG_UngateClock(&USB_OTG_dev);
	}
	EXTI_ClearITPendingBit(EXTI_Line18);
}


void OTG_FS_IRQHandler(void) {
	USBD_OTG_ISR_Handler(&USB_OTG_dev);
}


void usbEcho(void) {
	if (VCP_CheckDataReceived() != 0) {
		VCP_ReceiveData(&USB_OTG_dev,Rxbuffer, receive_count);
		if (receive_count != 0) {  
			while (VCP_CheckDataSent() == 1) {
			}
			VCP_SendData(&USB_OTG_dev, Rxbuffer, receive_count);
			receive_count = 0;
		}
	}
}

void usbInit(void) {
	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
}

