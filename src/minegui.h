#ifndef HEADER_MINESDL
#define  HEADER_MINESDL

#include <stddef.h>
#include <SDL/SDL.h>

enum box_types {
	DISPLAY		= 0,
	TEXT_DISPLAY	= 1,
	TEXT_INPUT		= 2,
	BUTTON			= 4,
};

struct size {

	int x1, x2;
	int y1, y2;

};

struct margin {

	int top;
	int left;

};

struct minesdl_box {

	Uint16 color;
	Uint16 color_pressed; // When it is a button;

	struct size size;
	struct margin margin;

};

// TODO: Adde string, handle text and add borders
struct minesdl_widget {

	int type;

	void (*action[3])();

	struct margin margin;
	struct minesdl_box box;

};

struct minesdl_widget_list {

	int number_widget;

	struct minesdl_widget *widget;
	struct minesdl_widget **widget_sub;

};

struct minesdl_root {

	SDL_Surface *screen;

	int fullscreen;
	int v_size, h_size;
	int mode;

	int number_widget;

	struct minesdl_widget widget;
	struct minesdl_widget_list **widget_list;
};

// Creation and management
struct minesdl_root *minesdl_create_root(int v_size, int h_size,
		int mode, int fullscreen, int size);

struct minesdl_widget_list *minesdl_create_widget_list(int x1, int x2,
		int y1, int y2, int size, Uint16 color);

struct minesdl_widget *minesdl_create_widget(
		struct minesdl_widget_list *widget_list,
		int x1, int x2, int y1, int y2,
		int margin_top, int margin_left, int type,
		Uint16 color, Uint16 color_pressed);

Uint16 minesdl_create_color(SDL_PixelFormat *fmt, Uint8 red,
		Uint8 green, Uint8 blue);

int minesdl_draw_window(struct minesdl_root *root);
int minesdl_draw_widget(struct minesdl_root *root,
		struct minesdl_widget *widget);

void minesdl_clean_root(struct minesdl_root *root);

// Interaction
void minesdl_loop(struct minesdl_root *root);
void minesdl_bind_action(struct minesdl_widget *widget, int mouse, void (*action)());

#endif