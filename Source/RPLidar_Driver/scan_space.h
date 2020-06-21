#ifndef __SCAN_SPACE_H
#define __SCAN_SPACE_H


#include "RPLidar.h"


/*
 * @bref Coordinates Barrier TypeDef
 */

typedef struct __CoordinatesBarrier_TypeDef_t
{
	float x_pos;
	float y_pos;
	float _r;
}CoBarrier_TypeDef;



typedef struct __Field_TypeDef_t
{
	uint16_t angle_range;
	uint32_t border_width;
	uint32_t border_height;
	uint32_t rate_field;
}Field_TypeDef;


typedef struct __outdata_t
{
	uint8_t sst;
	unsigned long curtTicks;
}outdata_t;



#define LED_CLK 					 	 RCC_APB2Periph_GPIOA
#define LED_PIN 					 	 GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6
#define LED_PORT					 	 GPIOA


#define LED_DANGER 					 	 			 PAout(6) //RED
#define LED_WARRING 					 	 		 PAout(5) //YELLOW
#define LED_SAFETY 					 	 		 	 PAout(4) //GREEN

#define ANGLE_RANGE     30
#define BORDER_WIDTH    400 		//khoang cach bao quanh
#define RIGHT_MARGIN    200   	// ben phai
#define LEFT_MARGIN     (BORDER_WIDTH - RIGHT_MARGIN)

#define D_DANGER        150  //mm
#define D_WARNING       180

#define RATE_OF_DANGER  5
#define RATE_OF_WARNING 0


void led_alert_init(void);
void get_pos(CoBarrier_TypeDef* brr, float _r, float ang);
uint8_t barrier_in_field(Field_TypeDef* field, CoBarrier_TypeDef* brr);
uint8_t is_angle_in_field(Field_TypeDef* field, float angle);
void scan_danger_space(float distance, float angle, uint8_t quality);
void scan_warring_space(float distance, float angle, uint8_t quality);
void parseData(void);
uint8_t out_data(outdata_t* output, uint8_t flag, uint16_t dlyTicks);
void scan_space(void);
void lidar_scanning(void);
void lidar_init(void);
void save_data(uint8_t key);
#endif
