
#include <main.h>
#include <serial.h>

/*
PA3
	USART2_RX
PA2
	USART2_TX

*/

void serialInit(void) { 
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	// TX-Pin
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

	// RX-Pin
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_Init(&NVIC_InitStructure);


	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);

}


void serialWrite(char *ptr) {
	int n = 0;
	int len = strlen(ptr);
	for (n = 0; n < len; n++) {
		USART_SendData(USART2, ptr[n]);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {}
	}
}




void USART2_IRQHandler(void) {
/*
	if (USART_GetITStatus(USART2, USART_IT_TXE) == SET) {
		USART_ClearITPendingBit(USART2, USART_IT_TXE);
		USART_SendData(USART2, TxBuffer[TxCounter++]);
		if (TxCounter == NbrOfDataToTransfer) {
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
			NbrOfDataToTransfer = 0;
			TxCounter = 0;
		}
	}
*/
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
		uint8_t rxc = USART_ReceiveData(USART2);
		USART_SendData(USART2, rxc);
	}
}




