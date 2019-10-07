#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "minesdl.h"

int minesdl_draw_widget(struct minesdl_root *root,
		struct minesdl_widget *widget)
{
	int x, y;
	int offset;
	Uint16 *raw_pixels;

	SDL_LockSurface(root->screen);
	raw_pixels = (Uint16 *)root->screen->pixels;

	for(x = widget->box.size.x1 + widget->box.margin.left;
			x <= widget->box.size.x2 + widget->box.margin.left; x++) {

		for(y = widget->box.size.y1 + widget->box.margin.top;
				y <= widget->box.size.y2 + widget->box.margin.top; y++) {

			offset = (root->screen->pitch / 2 * x + y);
			raw_pixels[offset] = widget->box.color;
		}
	}
	SDL_UnlockSurface(root->screen);
	SDL_Flip(root->screen);

	return 0;
}

int minesdl_draw_window(struct minesdl_root *root)
{
	struct minesdl_widget_list *tmp_list = NULL;

	minesdl_draw_widget(root, &root->widget);

	if(root->widget_list == NULL) {
		fprintf(stderr, "MineSDL: Widget_list in root window is uninitialized\n");
		return 1;
	}

	tmp_list = root->widget_list;

	while(tmp_list != NULL) {

		minesdl_draw_widget(root, tmp_list->widget);
		minesdl_draw_widget(root, tmp_list->widget_element);
		tmp_list = tmp_list->next_widget;
	}

	return 0;
}

