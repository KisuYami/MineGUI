#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "minesdl.h"

struct minesdl_root *minesdl_create_root(int v_size, int h_size, int mode,
		int fullscreen, Uint16 background_color)
{
	struct minesdl_root *root = NULL;
	root = malloc(sizeof(struct minesdl_root));

	if(root == NULL) {
		fprintf(stderr, "MineSDL: Failed to allocate memory for root window\n");
		exit(1);
	}

	*root = (struct minesdl_root) {

		.screen = NULL,
		.v_size = v_size,
		.h_size = h_size,

		.mode = mode,
		.fullscreen = fullscreen,

		.widget = (struct minesdl_widget) {

			.type = DISPLAY,

			.margin = (struct margin) {
				.left = 0,
				.top = 0,
			},

			.box = (struct minesdl_box) {

				.margin = (struct margin) {

					.top = 0,
					.left = 0,

				},

				.size = (struct size) {

					.x1 = 0,
					.x2 = v_size,
					.y1 = 0,
					.y2 = h_size,

				},
			},

		},

		.widget_list = NULL,
	};

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "MineSDL: Failed to create root window\n");
		free(root);
		exit(1);
	}

	root->screen = SDL_SetVideoMode(root->v_size, root->h_size,
			root->mode, root->fullscreen);

	if(!root->screen) {
		fprintf(stderr, "MineSDL: Failed to create root window\n");
		free(root);
		exit(1);
	}

	atexit(SDL_Quit);
	return root;
}

struct minesdl_widget *minesdl_create_widget(
		struct minesdl_widget_list *widget_list,
		int x1, int x2, int y1, int y2,
		int margin_top, int margin_left, int type,
		Uint16 color, Uint16 color_pressed)
{
	struct minesdl_widget *widget;
	int final_margin_left, final_margin_top;

	widget = malloc(sizeof(struct minesdl_widget));

	if(widget == NULL) {
		fprintf(stderr, "MineSDL: Failed to allocate memory for widget\n");
		exit(1);
	}

	if(widget_list != NULL) {
		final_margin_top = margin_top + widget_list->widget->box.size.y1;
		final_margin_left = margin_left + widget_list->widget->box.size.x1;
	} else {
		final_margin_top = margin_top;
		final_margin_left = margin_left;
	}

	*widget = (struct minesdl_widget) {

		.type = type,
		.next_element = NULL,

		.box = (struct minesdl_box) {

			.color = color,
			.color_pressed = color_pressed,

			.margin = (struct margin) {

				.top = final_margin_top,
				.left = final_margin_left,

			},
			.size = (struct size) {

				.x1 = x1,
				.x2 = x2,
				.y1 = y1,
				.y2 = y2,

			},

		},

	};

	return widget;
}

struct minesdl_widget_list *minesdl_create_widget_list(int x1, int x2,
		int y1, int y2, Uint16 color)
{
	struct minesdl_widget_list *list;

	list = malloc(sizeof(struct minesdl_widget_list));

	if(list == NULL) {

		fprintf(stderr, "MineSDL: Failed to allocate memory for widget list\n");
		exit(1);

	}

	*list = (struct minesdl_widget_list) {

		.widget = minesdl_create_widget(NULL, x1, x2, y1, y2, 0, 0,
				DISPLAY, color, 0),

		.widget_element = NULL,
		.next_widget = NULL,

	};

	return list;
}

Uint16 minesdl_create_color(SDL_PixelFormat *fmt, Uint8 red, Uint8 green, Uint8 blue)
{
	Uint16 value;
	value = ((red >> fmt->Rloss) << fmt->Rshift) +
			((green >> fmt->Gloss) << fmt->Gshift) +
			((blue >> fmt->Bloss) << fmt->Bshift);

	return value;
}
