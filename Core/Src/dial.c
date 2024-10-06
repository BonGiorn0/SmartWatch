#include "dial.h"
#include "st7735.h"
#include <math.h>

#define DIAL_COLOR 0xbdf7
#define DIAL_OUTER_RADIUS ST7735_GetHeight() / 2
#define DIAL_INNER_RADIUS DIAL_OUTER_RADIUS - 3
#define LINE_LENGTH 3

#define SEC_HAND_RADIUS 30
#define MIN_HAND_RADIUS 28
#define HOUR_HAND_RADIUS 20
#define SEC_HAND_COLOR DIAL_COLOR
#define MIN_HAND_COLOR DIAL_COLOR
#define HOUR_HAND_COLOR 0xf800

void drawClockDial(uint32_t time_in_seconds){
	ST7735_FillCircle(ST7735_GetWidth() / 2, ST7735_GetHeight() / 2, DIAL_OUTER_RADIUS, DIAL_COLOR);
	ST7735_FillCircle(ST7735_GetWidth() / 2, ST7735_GetHeight() / 2, DIAL_INNER_RADIUS, ST7735_BLACK);
	redrawClockHands(time_in_seconds);
}

void redrawClockHands(uint32_t time_in_seconds){
	ST7735_FillCircle(ST7735_GetWidth() / 2, ST7735_GetHeight() / 2,
			SEC_HAND_RADIUS + 1, ST7735_BLACK);
	float sec_angle = (float)time_in_seconds * 6 * M_PI / 180 - M_PI_2;
	float min_angle = (float)time_in_seconds * 0.1 * M_PI / 180 - M_PI_2;
	float hour_angle = (float)time_in_seconds * 0.0083 * M_PI / 180 - M_PI_2;
	float x0, x1,  y0, y1;
	int r = DIAL_INNER_RADIUS - 2;
	for(float i = 0; i < M_PI * 2; i += M_PI / 6){
	  x0 = r * cos(i) + ST7735_GetWidth() / 2;
	  y0 = r * sin(i) + ST7735_GetHeight() / 2;
	  x1 = (r - LINE_LENGTH) * cos(i) + ST7735_GetWidth() / 2;
	  y1 = (r - LINE_LENGTH) * sin(i) + ST7735_GetHeight() / 2;
	  ST7735_DrawLine(x0, y0, x1, y1, 0xbdf7);
	}
	x0 = ST7735_GetWidth() / 2;
	y0 = ST7735_GetHeight() / 2;
	x1 = (20) * cos(hour_angle) + ST7735_GetWidth() / 2;
	y1 = (20) * sin(hour_angle) + ST7735_GetHeight() / 2;
	ST7735_DrawLine(x0, y0, x1, y1, 0xbdf7);
	x1 = (28) * cos(min_angle) + ST7735_GetWidth() / 2;
	y1 = (28) * sin(min_angle) + ST7735_GetHeight() / 2;
	ST7735_DrawLine(x0, y0, x1, y1, 0xbdf7);
	x1 = (30) * cos(sec_angle) + ST7735_GetWidth() / 2;
	y1 = (30) * sin(sec_angle) + ST7735_GetHeight() / 2;
	ST7735_DrawLine(x0, y0, x1, y1, 0xf800);

}
