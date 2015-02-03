
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

#include "DycoLEDDriver.h"
#include "GPIO_basic.h"
#include "GPIO_BBB.h"

#define MAX_NUM_LEDS    35
#define MAX_PATTERN_STEPS 16

class DycoLED
{
public:
    // init - initialised the LED
    //bool init();
    bool init(uint16_t num_leds_to_init);

    // update - updates led according to timed_updated.  Should be
    // called at 50Hz
    void update();

    //SET_LEDS function: writes back/front colors and status leds depending on
    //quantity of leds and number of arms, status leds is the first led in each arm.
    void set_leds(uint16_t led, uint8_t patt);

//protected:
    void set_preset_pattern(uint16_t led,uint8_t patt);

};

struct led_pattern
{
    uint16_t color[MAX_PATTERN_STEPS];
    uint16_t time[MAX_PATTERN_STEPS];
    float brightness[MAX_PATTERN_STEPS];
    uint8_t res;
    uint8_t len;
};

