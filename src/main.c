
#include <main.h>
#include <stdio.h>
#include <ssd1306.h>
#include <ssd1351.h>
#include <framebuffer.h>
#include <timer.h>





int main(void) {
	systemInit();
	timerInit();
	fbInit();
	ssd1351Init();

	// draw lines
	fbLine(64, 64, 128, 75, 255);
	fbLine(64, 64, 0, 75, 255);
	// draw circle
	fbCircle(64, 64, 40, 0, 255);
	fbCircle(64, 64, 50, 0, 255);
	fbCircle(64, 64, 30, 1, 255);
	// draw rect
	fbRect(0, 64, 20, 100, 1, 255);
	fbRect(0, 100, 20, 127, 0, 255);
	// draw text
	fbTextPos(0, 0);
	fbText("Hello World", 255);
	// draw text with linebreak
	fbTextPos(0, 20);
	fbText("0123456789012345678901234567890123456789", 255);
	// draw text align right
	fbTextPos(DISPLAY_WIDTH - fbTextWidth("Rechts-Unten"), DISPLAY_HEIGHT - 8);
	fbText("Rechts-Unten", 255);
	// update display
	ssd1351Update();


//	ssd1306Init();
//	ssd1306Puts("Hallo I2C-OLED");


	int ret = 0;
	while (1) {

//		ssd1306Home();
//		ssd1306Puts("Hallo Loop");

		printf("Loop: %s\r\n", "test");
		delay(500000);

	}

}


