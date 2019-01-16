
#include <usbd_cdc_core_loopback.h>
#include <usbd_usr.h>
#include <usbd_desc.h>
#include <usbd_cdc_vcp.h>


extern USB_OTG_CORE_HANDLE USB_OTG_dev;
extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);



void usbInit(void);
void usbEcho(void);

