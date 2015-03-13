/*
   DycoLED Driver Interface
*/

/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
DycoLED Driver Usage Guide

Five Parameters to set pattern:
Color Series: color values after completion or at start of each step of pattern
Time Series: time between color transitions.
Brightness series: Brightness of the color at the same index
Resolution: No. of steps in which color transitions will occur.
Steps: Total no. of color transitions

Example:
with color series as {BLUE,RED,GREEN}
Time Series as {1000,1000,1000} --> first time is transition time in ms for BLUE -> RED
                                --> second time is for RED -> GREEN
                                --> Third time is for GREEN -> BLUE
Brightness series as {0.5,0.5,1.0}
Resolution as 10
Steps as 3

The loop of pattern will be:
first the LED will be set to HALF BRIGHT BLUE color. After
every 1000/10 milliseconds BLUE color will reduce at such
a rate that it diminishes at 1000 ms after the start of 
pattern and RED component will increase such that it increases
to HALF_BRIGHT at same time as BLUE goes to zero and similar
process will continue with RED diminishing and GREEN increases
to FULL brightness (1.0) thus completing 3 basic transitions
of loop i.e. from BLUE to RED to GREEN. The loop will until
another pattern or solid color is set.
*/
#include "DycoLED_Linux.h"

#include <stdio.h>
#include <unistd.h> //for using sleep fn
#include <sys/time.h>
DycoLEDStripDriver ubled_strip;

static led_pattern preset_pattern[22]={{{BLUE,RED},{100,100},{1.0,1.0},10,2},
                                       {{RED,BLUE,GREEN},{250,250,250},{1.0,1.0,1.0},15,3},
                                       {{BLACK,YELLOW},{250,250},{1.0,1.0},15,2},
                                       {{BLUE,YELLOW},{250,250},{1.0,1.0},15,2},
                                       {{PURPLE,YELLOW},{250,250},{1.0,1.0},15,2},
                                       {{RED,YELLOW},{250,250},{1.0,1.0},15,2},
                                       {{GREEN,GREEN},{1000,1000},{1.0,1.0},1,2},
                                       {{BLUE,BLUE},{1000,1000},{1.0,1.0},1,2},
                                       {{BLACK,YELLOW},{500,500},{1.0,1.0},15,2},
                                       {{BLACK,GREEN},{500,500},{1.0,1.0},15,2},
                                       {{BLACK,BLUE},{500,500},{1.0,1.0},31,2},
                                       {{GREEN,BLACK,GREEN,BLACK},{100,50,100,1000},{1.0,1.0,1.0,1.0},1,4},
                                       {{RED,BLACK,RED,BLACK},{100,50,100,1000},{1.0,1.0,1.0,1.0},1,4},
                                       {{BLUE,BLACK,BLUE,BLACK},{100,50,100,1000},{1.0,1.0,1.0,1.0},1,4},
                                       {{YELLOW},{200},{0.1},10,1},
                                       {{PURPLE},{200},{0.1},10,1},
                                       {{GREEN,BLACK,GREEN,BLACK},{100,50,100,100},{1.0,1.0,1.0,1.0},1,4},
                                       {{GREEN,BLUE,GREEN,BLUE},{100,100,100,100},{1.0,1.0,1.0,1.0},1,4},
                                       {{BLUE,BLACK,BLUE,BLACK},{100,50,100,1000},{1.0,1.0,1.0,1.0},1,4},
                                       {{RED,BLACK,RED,BLACK},{100,50,100,50},{1.0,1.0,1.0,1.0},1,4},
                                       {{WHITE},{200},{0.05},1,1},
                                       {{RED,RED,RED,RED},{100,100,100,100},{1.0,0.8,0.5,0.2},10,4},
                                       };  


bool DycoLED::init(uint16_t num_leds_to_init)
//bool DycoLED::init()
{
    //ubled_strip.init(MAX_NUM_LEDS);
    ubled_strip.init(num_leds_to_init);
	return true;
}

void DycoLED::set_preset_pattern(uint16_t led,uint8_t patt)
{
    ubled_strip.set_pattern(led,
                            preset_pattern[patt].color,
                            preset_pattern[patt].brightness,
                            preset_pattern[patt].time,
                            preset_pattern[patt].res,
                            preset_pattern[patt].len);
}


void DycoLED::set_leds (uint16_t number_led,uint8_t patt)
{//Use it main
 //Function that writess pattern that user has selected, generates beat for refreshing.

    for (int i=0; i<number_led; i++){
       	//printf("Writing in led %i", i);
        ubled_strip.set_pattern(i,
                             preset_pattern[patt].color,preset_pattern[patt].brightness,preset_pattern[patt].time,
                             preset_pattern[patt].res,preset_pattern[patt].len);
    }
    ubled_strip.generate_beat_pattern();

}

void DycoLED::set_single_led (uint16_t number_led,uint8_t patt)
{//Use it main
 //Function that writess pattern in a single LED that user has selected, generates beat for refreshing.

    ubled_strip.set_pattern(number_led,preset_pattern[patt].color,preset_pattern[patt].brightness,preset_pattern[patt].time,preset_pattern[patt].res,preset_pattern[patt].len);
    ubled_strip.generate_beat_pattern();

}
// update - updates led according to timed_updated.  Should be called
// at 50Hz
void DycoLED::update()
{
//    set_leds(2, 1);

}

