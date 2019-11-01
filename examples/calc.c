#include <SDL/SDL.h>
#include <minegui/minegui.h>
#include <time.h>

// -*- compile-command: "gcc -Wall -lSDL -lSDL_ttf -lminegui -o test.c test" -*-

int STRING_INDEX; // XXX
char DISPLAY_STRING[20];

const char number_list[] = {'7', '8', '9', '4', '5', '6', '1', '2', '3', '.', '0', ','};
const char symbol_list[] = {'-', '+', '/', '*', '%', 'B', 'C', '='};

void
display_handler(struct minegui_root *root);

void
display_symbol(struct minegui_root *root);

void
display_clean(struct minegui_root *root);

void
display_eval(struct minegui_root *root);

// Handle numpad
void
display_handler(struct minegui_root *root)
{

	int i;
	for(i = 0; i < 13; ++i) {

		if (root->widget_list[1]->widget_sub[i]->clicked == 1)
			break;
	}

	if(STRING_INDEX < 13)
	{
		DISPLAY_STRING[STRING_INDEX++] = symbol_list[i];
		DISPLAY_STRING[STRING_INDEX] = '\0';
	}

	else 
		return;

	minegui_change_text(root->widget_list[0]->widget_sub[0], DISPLAY_STRING);

	minegui_draw_widget(root, root->widget_list[0]->widget);
	minegui_draw_text(root, root->widget_list[0]->widget_sub[0]);

	SDL_Flip(root->screen);

	return;
}

// Handle symbol pad
void
display_symbol(struct minegui_root *root)
{
	int i;
	for(i = 0; i < 7; ++i)
	{
		if(root->widget_list[2]->widget_sub[i]->clicked == 1)
			break;
	}

	if(5 == i)
	{
		DISPLAY_STRING[--STRING_INDEX] = '\0';
		if(STRING_INDEX < 0)
			STRING_INDEX = 0;
	}

	else
	{
		if(STRING_INDEX < 13)
		{
			DISPLAY_STRING[STRING_INDEX++] = symbol_list[i];
			DISPLAY_STRING[STRING_INDEX] = '\0';
		}

		else 
			return;
	}

	minegui_change_text(root->widget_list[0]->widget_sub[0], DISPLAY_STRING);

	minegui_draw_widget(root, root->widget_list[0]->widget);
	minegui_draw_text(root, root->widget_list[0]->widget_sub[0]);

	SDL_Flip(root->screen);
	return;
}

void
display_eval(struct minegui_root *root)
{
	char command[36];
	FILE *fp;

	sprintf(command, "lua -e \"print(%s)\"", DISPLAY_STRING);

	fp = popen(command, "r");

	STRING_INDEX = 0;
	memset(DISPLAY_STRING, 0, 19);

	fscanf(fp, "%s", DISPLAY_STRING);

	STRING_INDEX = strlen(DISPLAY_STRING);
	minegui_change_text(root->widget_list[0]->widget_sub[0], DISPLAY_STRING);

	minegui_draw_widget(root, root->widget_list[0]->widget);
	minegui_draw_text(root, root->widget_list[0]->widget_sub[0]);

	SDL_Flip(root->screen);
	pclose(fp);
	return;
}

void
display_clean(struct minegui_root *root)
{
	
	STRING_INDEX = 0;
	memset(DISPLAY_STRING, 0, 19);

	minegui_change_text(root->widget_list[0]->widget_sub[0], DISPLAY_STRING);

	minegui_draw_widget(root, root->widget_list[0]->widget);
	minegui_draw_text(root, root->widget_list[0]->widget_sub[0]);

	SDL_Flip(root->screen);
	return;
}

int
main(void)
{
	struct minegui_root *root;
	char number;

	Uint16 background, foreground, button, button_border;

	root = minegui_create_root(256, 256, 16, 0, 3, 1);

	background	  = minegui_create_color(root->screen->format, 30, 30, 30);
	foreground	  = minegui_create_color(root->screen->format, 50, 50, 50);
	button		  = minegui_create_color(root->screen->format, 20, 20, 20);
	button_border = minegui_create_color(root->screen->format, 10, 10, 10);

	root->widget.box.color = background;

	root->font_list[0] = minegui_create_font("/usr/share/fonts/truetype/Roboto-Regular.ttf", 30, 0);

	/* START: Number Display */

	root->widget_list[0] = minegui_create_widget_list(10, 70, 10, 246,
													  1, foreground);

	minegui_create_widget(root->widget_list[0], 0, 35, 0, 0, 13, 2,
						  MINEGUI_TEXT_DISPLAY, foreground, foreground);

	minegui_create_text(root->font_list[0], root->widget_list[0]->widget_sub[0],
						1, 2, 25, 45, "0.00", 255, 255, 255);

	/* END: Number Display */

	/* START: Number Pad */
	root->widget_list[1] = minegui_create_widget_list(80, 246, 10, 135,
													  12, foreground);

	int p = 5, w = 5;

	for (int i = 0; i < 12; ++i) {

		sprintf(&number, "%c", number_list[i]);

		minegui_create_widget(root->widget_list[1], 0, 35, 0, 35, p, w,
							  MINEGUI_BUTTON | MINEGUI_BORDER | MINEGUI_RADIUS | MINEGUI_TEXT_DISPLAY,
							  button, button_border);

		minegui_create_text(root->font_list[0], root->widget_list[1]->widget_sub[i],
							1, 9, 25, 45, &number, 255, 255, 255);

		minegui_bind_action(root->widget_list[1]->widget_sub[i], 0, display_handler);
		w += 40;

		if(i == 2 || i == 5 || i == 8) {
			p += 40;
			w = 5;
		}

	}

	/* END: Number Pad */

	/* START: Math Symbols */
	root->widget_list[2] = minegui_create_widget_list(80, 246, 145, 247,
													  8, foreground);

	p = 5;
	w = 5;

	for (int i = 0; i < 8; ++i) {

		sprintf(&number, "%c", symbol_list[i]);

		if(i % 2)
		{
			minegui_create_widget(root->widget_list[2], 0, 35, 0, 43, p, 54,
								  MINEGUI_BUTTON | MINEGUI_RADIUS | MINEGUI_TEXT_DISPLAY,
								  button, button_border);
		}
		else
		{
			minegui_create_widget(root->widget_list[2], 0, 35, 0, 43, p, w,
								  MINEGUI_BUTTON | MINEGUI_RADIUS | MINEGUI_TEXT_DISPLAY,
								  button, button_border);
		}

		minegui_create_text(root->font_list[0], root->widget_list[2]->widget_sub[i],
							1, 12, 25, 45, &number, 255, 255, 255);
		
		minegui_bind_action(root->widget_list[2]->widget_sub[i], 0, display_symbol);

		if(i == 1 || i == 3 || i == 5) {
			p += 40;
			w = 5;
		}

	}

	minegui_bind_action(root->widget_list[2]->widget_sub[6], 0, display_clean);
	minegui_bind_action(root->widget_list[2]->widget_sub[7], 0, display_eval);
	/* END: Math Symbols */

	STRING_INDEX = 0;

	minegui_loop(root);
	minegui_clean_root(root);

	return 0;
}
