#include <stdlib.h>
#include <SDL/SDL.h>
#include "minegui.h"

void minesdl_clean_root(struct minesdl_root *root)
{
	int i, p;

    SDL_FreeSurface(root->screen);

	for (i = 0; i < root->number_widget; ++i) {

		for (p = 0; p < root->widget_list[i]->number_widget; ++p)
            free(root->widget_list[i]->widget_sub[p]);

        free(root->widget_list[i]->widget);
        free(root->widget_list[i]);

    }

	free(root->widget_list);
    free(root);
}
