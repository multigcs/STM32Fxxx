
#ifndef __USBD_CDC_VCP_H
#define __USBD_CDC_VCP_H

#include "usbd_cdc_core_loopback.h"
#include "string.h"
void VCP_SendData(USB_OTG_CORE_HANDLE *pdev, uint8_t* pbuf, uint32_t buf_len);
uint32_t VCP_CheckDataSent (void);
void VCP_ReceiveData(USB_OTG_CORE_HANDLE *pdev, uint8_t *pbuf, uint32_t buf_len);
uint32_t VCP_CheckDataReceived(void);

#endif /* __USBD_CDC_VCP_H */

