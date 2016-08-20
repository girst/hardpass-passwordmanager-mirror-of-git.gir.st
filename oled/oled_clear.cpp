#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"

#include <getopt.h>
#include <stdio.h>

#define ERR_FAIL 0
//yes, this is irritating to unix users, but a return val >= 1 will mean nth item selected
ArduiPi_OLED display; // Instantiate the display

// Config Option
struct s_opts {
	int oled;
	int verbose;
} ;

// default options values
s_opts opts = {
	3,	// my .96" oled
	false	// Not verbose
};

int main(int argc, char **argv)
{
	if ( !display.init(OLED_I2C_RESET,opts.oled) ) {
		return ERR_FAIL;
	}

	display.begin();
	
	display.clearDisplay();   // clears the screen  buffer
	display.display();   		// display it (clear display)

	display.close(); // Free PI GPIO ports
}


