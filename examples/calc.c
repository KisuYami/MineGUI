#include <SDL/SDL.h>
#include <minegui/minegui.h>

static int STRING_INDEX; // XXX
static char DISPLAY_STRING[20];

// -*- compile-command: "gcc -Wall -lSDL -lSDL_ttf -lminegui -o test.c test" -*-
void display_handler(struct minesdl_root *root)
{
	char number;

	for(int i = 0; i <= 12; ++i) {

		if (root->widget_list[1]->widget_sub[i]->clicked == 1) {
			if(i == 9)
				number = '.';
			else if(i == 11)
				number = ',';
			else
				sprintf(&number, "%d", abs(i-9));

			break;
		}
	}

	if(STRING_INDEX < 13)
		DISPLAY_STRING[STRING_INDEX++] = number;

	else {
		STRING_INDEX = 0;
		memset(DISPLAY_STRING, 0, 19);
	}

	minesdl_change_text(root->widget_list[0]->widget_sub[0], DISPLAY_STRING);

	minesdl_draw_widget(root, root->widget_list[0]->widget);
	minesdl_draw_text(root, root->widget_list[0]->widget_sub[0]);

	SDL_Flip(root->screen);

	return;
}

int
main(void)
{
	struct minesdl_root *root;
	Uint16 background, foreground, button;

	root = minesdl_create_root(256, 256, 16, 0, 2);

	background	= minesdl_create_color(root->screen->format, 30, 30, 30);
	foreground	= minesdl_create_color(root->screen->format, 50, 50, 50);
	button		= minesdl_create_color(root->screen->format, 20, 20, 20);

	root->widget.box.color = background;

	/* START: Number Display */

	root->widget_list[0] = minesdl_create_widget_list(10, 70, 10, 246,
													  1, foreground);

	minesdl_create_widget(root->widget_list[0], 0, 35, 0, 0, 13, 2,
						BUTTON | TEXT_DISPLAY, foreground, foreground);

	minesdl_create_text(root->widget_list[0]->widget_sub[0],
						1, 2, 25, 45, 30, 0,
						"0.00", "/usr/share/fonts/truetype/Hack-Regular.ttf",
						255, 255, 255);

	/* END: Number Display */

	/* START: Number Pad */
	root->widget_list[1] = minesdl_create_widget_list(80, 246, 10, 246,
													  12, foreground);

	int p = 5, w = 5, z = 10;
	char number[5];

	for (int i = 0; i < 12; ++i) {

		if(i == 9)
			*number = '.';
		else if(i == 11)
			*number = ',';
		else
			sprintf(number, "%d", --z);

		minesdl_create_widget(root->widget_list[1], 0, 35, 0, 35, p, w,
							  BUTTON | TEXT_DISPLAY, button, button);

		minesdl_create_text(root->widget_list[1]->widget_sub[i],
							1, 9, 25, 45, 30, 0,
							number, "/usr/share/fonts/truetype/Hack-Regular.ttf",
							255, 255, 255);

		minesdl_bind_action(root->widget_list[1]->widget_sub[i], 0, display_handler);
		w += 40;

		if(i == 2 || i == 5 || i == 8) {
			p += 40;
			w = 5;
		}

	}

	/* END: Number Pad */

	STRING_INDEX = 0;

	minesdl_loop(root);
	minesdl_clean_root(root);

	return 0;
}
