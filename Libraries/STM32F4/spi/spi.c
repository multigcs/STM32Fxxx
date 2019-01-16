
#include <main.h>
#include <spi.h>


uint8_t spiRxBuff[SPI_RX_MAX];
static volatile int spiRxCount = 0;


void SPI1_IRQHandler(void) {
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
	spiRxBuff[spiRxCount]= SPI_I2S_ReceiveData(SPI1);
	spiRxCount++;
	if (spiRxCount >= SPI_RX_MAX) {
		spiRxCount = 0;
	}
}


void spiWrite(uint8_t *data, uint16_t len) {
	int i = 0;
	for (i = 0; i < len; i++) {
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
		SPI_I2S_SendData(SPI1, data[i]);
	}
}

void spiInit(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStruct; 

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	SPI_StructInit(&SPI_InitStruct);
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI1, &SPI_InitStruct); 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	SPI_Cmd(SPI1, ENABLE);

	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);

	return;
}


