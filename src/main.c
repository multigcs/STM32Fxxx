
#include <main.h>
#include <stdio.h>
#include <ssd1306.h>

#include <ssd1351.h>
#include <framebuffer.h>

#include <timer.h>
#include <adc.h>


int main(void) {
	int n = 0;
	uint16_t adc = 0;
	char tmp_str[100];

	systemInit();
	timerInit();
	Adc1Init();

	ssd1306Init();
	ssd1306Puts("Hallo I2C-OLED");

	fbInit();
	ssd1351Init();
	ssd1351FillColor(255);


	while (1) {

		adc = Adc1Read(1);

		ssd1306Home();
		sprintf(tmp_str, "Hallo Loop %i %i       ", n, adc);
		ssd1306Puts(tmp_str);

		fbTextPos(1, 1);
		fbText(tmp_str, 0);
		fbTextPos(50, 50);
		fbText(tmp_str, 255);
		ssd1351Update();


//		printf("Loop: %s\r\n", "test");
		delay(100000);
		n++;
	}

}


