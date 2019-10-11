
#include <main.h>
#include <stdio.h>
#include <systick.h>
#include <i2c.h>

void i2cStart(uint8_t address) {
	uint16_t timeout = 0;
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB) && timeout < 100) {
		delay(10);
		timeout++;
	}
	if (timeout >= 100) {
		printf("i2cStart: bussy\r\n");
	}
	I2C_Send7bitAddress(I2C1, address<<1, I2C_Direction_Transmitter);
	timeout = 0;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) && timeout < 100) {
		delay(10);
		timeout++;
	}
	if (timeout >= 100) {
		printf("i2cStart: not in transmitter mode\r\n");
	}
}

void i2cStop(void) {
	uint16_t timeout = 0;
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && timeout < 100) {
		delay(10);
		timeout++;
	}
	if (timeout >= 100) {
		printf("i2cStop: bussy\r\n");
	}
	I2C_GenerateSTOP(I2C1, ENABLE);
	timeout = 0;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && timeout < 100) {
		delay(10);
		timeout++;
	}
	if (timeout >= 100) {
		printf("i2cStop: not transmitted\r\n");
	}
}

void i2cSendByte(uint8_t byte) {
	uint16_t timeout = 0;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) && timeout < 100) {
		delay(10);
		timeout++;
	}
	if (timeout >= 100) {
		printf("i2cSendByte: busy\r\n");
	}
	I2C_SendData(I2C1, byte);
}

void i2cInit(void) {
#ifdef STM32F10X_MD
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure;

	I2C_Cmd(I2C1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	//I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;
	I2C_InitStructure.I2C_ClockSpeed = 400000;
	I2C_Init(I2C1, &I2C_InitStructure);
#else
#endif
}



