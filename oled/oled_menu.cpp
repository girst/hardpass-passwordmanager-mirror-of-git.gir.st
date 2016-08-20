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

void print_box (char* text, int active) {
	if (active) {
		display.setTextColor(BLACK, WHITE); // 'inverted' text
		display.printf ("%-21s", text);
		display.setTextColor(WHITE, BLACK);
	} else {
		display.setTextColor(WHITE, BLACK); // 'normal' text
		display.printf ("%-21s", text);
		display.setTextColor(BLACK, WHITE);
	}
}

void disp_menu (char* title, char* i1, char* i2, char* i3, char* i4, char* i5, char* i6, char* i7, int active, float bar) {
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.print (title);
	display.drawLine(0, 8, display.width()-1, 8, WHITE);

	display.setCursor(0,10);
	print_box (i1, active==0); if (i2 == NULL) goto no_more_elems;
	print_box (i2, active==1); if (i3 == NULL) goto no_more_elems;
	print_box (i3, active==2); if (i4 == NULL) goto no_more_elems;
	print_box (i4, active==3); if (i5 == NULL) goto no_more_elems;
	print_box (i5, active==4); if (i6 == NULL) goto no_more_elems;
	print_box (i6, active==5); if (i7 == NULL) goto no_more_elems;
	print_box (i7, active==6);
	no_more_elems:

	//display a scrollbar if bar is set >=0
	if (bar >= 0) {
		int bar_length = 6;
		int scroll_max = display.height()-1 - bar_length/2;
		int scroll_min = 10 + bar_length/2;
		float scroll_p = bar;
		display.drawLine (display.width()-1, scroll_min+scroll_p*(scroll_max-scroll_min)-bar_length/2, display.width()-1, scroll_min+scroll_p*(scroll_max-scroll_min)+bar_length/2, WHITE); //draw a scrollbar
	}
	display.display();
}

int the_menu (char* title, char** items, int max_items) {
	int active_item = 0;
	int old_item = -1;
	int offset = 0;

		system  ("/bin/stty raw");//send keystrokes immediately, not just after enter key
	while (1) {
		if (old_item != active_item) {
			if (active_item == 0) offset = 0;
			if (active_item == max_items-1) offset = max_items-6;
			if (active_item > offset+3 && active_item < max_items-2) { //end of menu
				offset++; //scroll down
			} else if (active_item < offset+3 && active_item > 2) {
				offset--; //scroll up
			}
			if (offset < 0) offset = 0; // for when <6 elements available

			float scroll_p = (float)active_item / (float)(max_items-1);
			/*if (active_item >= max_items - 3) { //scrolled to the bottom - don't display another half item as there is none
			disp_menu (title, 
				items [offset + 0], 
				items [offset + 1], 
				items [offset + 2], 
				items [offset + 3], 
				items [offset + 4], 
				items [offset + 5], 
				"",  //offset+6 won't exist
				active_item - offset, scroll_p);
			} else {*/
			disp_menu (title, 
				items [offset + 0], 
				items [offset + 1], 
				items [offset + 2], 
				items [offset + 3], 
				items [offset + 4], 
				items [offset + 5], 
				items [offset + 6], 
				active_item - offset, scroll_p);
			//}
			//display.display();
			old_item = active_item;
		}
		switch (getchar()) {
		case 'j':
			active_item = (active_item+1) % max_items;
			break;
		case 'k':
			active_item = (active_item-1+max_items) % max_items;
			break;
		case ' ':
			system ("/bin/stty cooked");//return to normal mode
			return active_item;
			break;
		}
/*
		if (getchar () == 'j') { //down
			active_item = (active_item+1) % max_items;
			// debounce TODO
		}
		if (getchar () == 'k') { //up
		active_item = (active_item-1+max_items) % max_items;
			// debounce TODO
		}
		if (getchar () == ' ') { //ok
			//debounce TODO
		printf ("%d\n", active_item);
			return (active_item);
		}
*/
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

	argv = &(argv[1]);
	return the_menu ("Hardpass", argv, argc-1) + 1;
	//############

	display.close(); // Free PI GPIO ports
}


