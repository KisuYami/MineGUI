#include <SDL/SDL.h>
#include "minegui.h"

static void minesdl_check_button_click(struct minesdl_root *root,
		SDL_Event *mouse)
{
	int i, p;

	for (i = 0; i < root->number_widget; ++i) {

		for (p = 0; p < root->widget_list[i]->number_widget; ++p) {
			if(root->widget_list[i]->widget_sub[i]->type | BUTTON) {

				// XXX
				struct minesdl_box *position = &root->widget_list[i]->widget_sub[i]->box;

				if( (mouse->button.x >= position->size.y1 + position->margin.left)	&&
					(mouse->button.x <= position->size.y2 + position->margin.left)	&&
                    (mouse->button.y >= position->size.x1 + position->margin.top)  &&
					(mouse->button.y <= position->size.x2 + position->margin.top))
                    if(root->widget_list[i]->widget_sub[i]->action[mouse->button.button - 1] != NULL)
                        root->widget_list[i]->widget_sub[i]->action[mouse->button.button - 1]();

			}

		}

    }

}

// TODO: Handle redraw
void minesdl_loop(struct minesdl_root *root)
{
	SDL_Event event;
	minesdl_draw_window(root);

	while(SDL_WaitEvent(&event) != 0) {
		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				minesdl_check_button_click(root, &event);
				break;

			case SDL_QUIT:
				minesdl_clean_root(root);
				exit(0);

				break;
		}
	}
}