#ifndef __AP_HAL_LINUX_DYCO_LED_DRIVER_H__
#define __AP_HAL_LINUX_DYCO_LED_DRIVER_H__
#endif

//#include <AP_HAL_Linux.h>


#define DYCOCLK 50
#define DYCODOUT 51

#define CLK_PERIOD 200          //200ns

#define BLACK       0
#define RED         1
#define ORANGE      2
#define AMBER       3
#define YELLOW      4
#define GREEN       5
#define BLUE        6
#define PURPLE      7
#define WHITE       8

#include "stdint.h"

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#include "GPIO_basic.h"
#include "GPIO_BBB.h"

//DycoLEDDriver: this class is used for setting up of parameters
//related to a single DycoLED.
class DycoLEDDriver
{
private:
    uint32_t clk_prev_time;
    uint32_t clk_pulse_count;
    uint16_t data_hold;
    uint16_t data_buf;
    //pattern parameters
    uint16_t _iter;
	uint8_t _step;
	uint8_t _res;
	uint8_t _step_cnt;
	uint16_t* _pattern_color;
	uint16_t* _pattern_time;
    uint32_t _prev_time;
	float* _brightness;
    void set_rgb(uint16_t red, uint16_t green, uint16_t blue);
    
    struct timespec _sketch_start_time;

public:
    DycoLEDDriver();
    void set_solid_color(uint8_t color);
    bool pop_data();
    void reset();
    //pattern functions
    void pattern_step();
	void set_pattern(uint16_t color_series[],float bright_series[],uint16_t time_series[],uint8_t res, uint8_t step_cnt);
};

//DycoLEDStripDriver: this class is used for controling each and every
//LED which are a part of LED Strip.
class DycoLEDStripDriver
{
private:
    uint32_t clk_pulse_count;
	uint8_t _length;
	bool _init;
    bool _commcomp;
    bool clk_pin;
    uint16_t _strip_cnt;
    static DycoLEDDriver* _led;

public:
    DycoLEDStripDriver();
    void generate_beat_pattern();
    bool update();
	void set_solid_color(uint8_t led_num, uint8_t color);
	void set_pattern(uint16_t led_num,uint16_t color_series[],float bright_series[],uint16_t time_series[],uint8_t res, uint8_t step_cnt);
    void init(uint16_t length);

    uint64_t millis64();
};


//#endif
