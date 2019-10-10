#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "minegui.h"

int minesdl_draw_widget(struct minesdl_root *root,
		struct minesdl_widget *widget)
{
	int x, y;
	int offset;
	Uint16 *raw_pixels;

	SDL_LockSurface(root->screen);
	raw_pixels = (Uint16 *)root->screen->pixels;

	for(x = widget->box.size.x1 + widget->box.margin.top;
			x <= widget->box.size.x2 + widget->box.margin.top; x++) {

		for(y = widget->box.size.y1 + widget->box.margin.left;
				y <= widget->box.size.y2 + widget->box.margin.left; y++) {

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
	int i, p;

	minesdl_draw_widget(root, &root->widget);

	if(root->widget_list == NULL) {
		fprintf(stderr, "MineSDL: Widget_list in root window is uninitialized\n");
		exit(1);
	}

	for (i = 0; i < root->number_widget; ++i) {

		if(root->widget_list[i]->widget != NULL)
			minesdl_draw_widget(root, root->widget_list[i]->widget);

		else
			fprintf(stderr, "MineSDL: Widget in widget_list[%d] is uninitialized\n", i);

		for (p = 0; p < root->widget_list[i]->number_widget; ++p) {

			if(root->widget_list[i]->widget_sub[p] != NULL)
				minesdl_draw_widget(root, root->widget_list[i]->widget_sub[p]);

			else
				fprintf(stderr, "MineSDL: sub_widget[%d] in widget_list[%d] is uninitialized\n", p, i);
		}

	}

	return 0;
}
