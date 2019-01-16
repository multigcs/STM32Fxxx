
#include "usbd_cdc_vcp.h"

__IO uint32_t  data_sent;
__IO uint32_t receive_flag=0;
extern __IO uint32_t receive_count;

static uint16_t VCP_DataTx   (void);
static uint16_t VCP_DataRx   (uint32_t Len);

CDC_IF_Prop_TypeDef VCP_fops = {
  VCP_DataTx,
  VCP_DataRx
};

static uint16_t VCP_DataTx (void) { 
  data_sent =1;
  return USBD_OK;
}

static uint16_t VCP_DataRx (uint32_t Len) { 
  receive_count = Len;
  return USBD_OK;
}

void VCP_SendData( USB_OTG_CORE_HANDLE *pdev, uint8_t* pbuf, uint32_t  buf_len) {
  data_sent =0; 
  DCD_EP_Tx (pdev, CDC_IN_EP, pbuf , buf_len );
}

uint32_t VCP_CheckDataSent (void) {
  if (data_sent) return 1;
  return 0;
}

void VCP_ReceiveData(USB_OTG_CORE_HANDLE *pdev, uint8_t  *pbuf, uint32_t   buf_len) {
    receive_flag = 0;
    DCD_EP_PrepareRx(pdev, CDC_OUT_EP, pbuf, buf_len);
}

uint32_t VCP_CheckDataReceived(void) {
  data_sent =0; 
  return receive_count;
}

