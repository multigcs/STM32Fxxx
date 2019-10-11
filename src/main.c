
#include <main.h>
#include <stdio.h>
#include <string.h>
#include <ili9163.h>
#include <framebuffer.h>
#include <timer.h>
#include <adc.h>





int main(void) {

	systemInit();
	timerInit();
	Adc1Init();


	ili9163Init();
	fbInit();
	fbClear();

	fbTextPos(10, 10);
	fbText("Hallo", fb_COLOR_FG);
	ili9163Update();


	while (1) {


//		printf("Hallo\r\n");

		delay(1000);
	}

}


