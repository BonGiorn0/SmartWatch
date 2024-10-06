#include <stdlib.h>
#include <string.h>

#include "st7735.h"
#include "PulseData.h"
#include "assets.h"




#define MIN_Y 10
#define MAX_X 115
#define MIN_X 5

void drawPulseGraphDot(uint16_t raw_adc){
	static int x = MIN_X;
	static int erase_x = MIN_X + 10;
	static int prev_x = MIN_X;
	static int prev_y = 40;

	int y = 60 - (raw_adc - 2000) / 3 + MIN_Y;
	//ST7735_DrawPixel(x, y, ST7735_RED);
	ST7735_DrawLine(prev_x, prev_y, x, y, ST7735_RED);
	prev_y = y;
	prev_x = x;

	ST7735_DrawFastVLine(erase_x, 0, ST7735_GetHeight(), ST7735_BLACK);
	x++;
	erase_x++;
	if(x > MAX_X){
		x = MIN_X;
		prev_x = MIN_X;
	}

	if(erase_x > MAX_X)
		erase_x = MIN_X;

}

void drawHeart(){
	uint16_t *image = malloc(sizeof(uint16_t) * 33 * 33);
	imagify(bpm_heart_map, sizeof(bpm_heart_map), image);
	ST7735_DrawImage(130, MIN_Y, 20, 20, image);
	free(image);
}

void drawBPM(uint8_t bpm){
	char str[4] = "";
	if(bpm < 100)
		sprintf(str, "%d ", bpm);
	else
		sprintf(str, "%d", bpm);
	if(bpm == 255)
		ST7735_DrawString(123, MIN_Y + 25, "--", Font_11x18, ST7735_RED, ST7735_BLACK);
	else
		ST7735_DrawString(123, MIN_Y + 25, str, Font_11x18, ST7735_RED, ST7735_BLACK);

}
