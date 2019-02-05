

#include "usb_bsp.h"

/*

	OTG_FS_SOF = PA8
	OTG_FS_VBUS = PA9
	OTG_FS_ID = PA10
	OTG_FS_DM = PA11
	OTG_FS_DP = PA12

*/


void delay(uint32_t delay);


void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE *pdev) {
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA , ENABLE);  

	GPIO_InitTypeDef GPIO_InitStructure;   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	delay(1000);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_OTG1_FS) ; 
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_OTG1_FS); 
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_OTG1_FS);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE);
}


void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE *pdev) {
	NVIC_InitTypeDef NVIC_InitStructure; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  
}

void USB_OTG_BSP_uDelay (const uint32_t usec) {
	uint32_t count = 0;
	const uint32_t utime = (120 * usec / 7);
	do {
		if ( ++count > utime ) {
			return ;
		}
	}
	while (1);
}

void USB_OTG_BSP_mDelay (const uint32_t msec) {
	USB_OTG_BSP_uDelay(msec * 1000);   
}

