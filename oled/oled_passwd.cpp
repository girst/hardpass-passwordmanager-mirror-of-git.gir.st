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

void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    //if ((i > 0) && (i % 21 == 0))
      //display.print("\n");
  }    
  display.display();
}


void disp_login (char* title, int ast_n) {
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.print (title);
	display.drawLine(0, 8, display.width()-1, 8, WHITE);

	display.setCursor(0,10);
	display.printf ("Enter GPG Passphrase:\n");
	for (int i = 0; i < ast_n; i++) {
		display.printf ("*");
	}

	display.display();
}

int the_login (char* title) {
	int asterisks_num = 0;
	system  ("/bin/stty raw");//send keystrokes immediately, not just after enter key
	while (1) {
		disp_login (title, asterisks_num);

		switch (getchar()) {
		case 'j':
			asterisks_num--;
			break;
		case 'k':
			asterisks_num++;
			break;
		case ' ':
			system ("/bin/stty cooked");//return to normal mode
			return asterisks_num;
			break;
		}
	}
}


int main(int argc, char **argv)
{
	if ( !display.init(OLED_I2C_RESET,opts.oled) ) {
		return ERR_FAIL;
	}

	display.begin();
	
	//display.clearDisplay();   // clears the screen  buffer
	//display.display();   		// display it (clear display)

	display.clearDisplay();

	// draw the first ~12 characters in the font
	//testdrawchar();
	//display.display();
	//sleep(2);
	//display.clearDisplay();

	//#####mystuff

	return the_login ("Hardpass");
	//############

	display.close(); // Free PI GPIO ports
}


