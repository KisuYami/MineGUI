#include <stdlib.h>
#include <SDL/SDL.h>
#include "minegui.h"

void minesdl_clean_root(struct minesdl_root *root)
{
    SDL_FreeSurface(root->screen);

	for(int i = 0; i < root->number_widget; ++i) {

		for(int p = 0; p < root->widget_list[i]->number_widget; ++p) {
			if(root->widget_list[i]->widget_sub[p]->type | TEXT_DISPLAY) {
				TTF_CloseFont(root->widget_list[i]->widget_sub[p]->text.font_familly);
				SDL_FreeSurface(root->widget_list[i]->widget_sub[p]->text.font_surface);
			}
            free(root->widget_list[i]->widget_sub[p]);
		}

        free(root->widget_list[i]->widget);
        free(root->widget_list[i]);

    }

	free(root->widget_list);
    free(root);
}
