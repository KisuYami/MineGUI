#include <stdlib.h>
#include <SDL/SDL.h>
#include "widget.h"
#include "mem.h"

void
minegui_clean_root(struct minegui_root *root)
{

    for(int i = 0; i < root->number_widget; ++i)
    {
        for(int p = 0; p < root->widget_list[i]->number_widget; ++p)
        {
            if(root->widget_list[i]->widget_sub[p]->type | MINEGUI_TEXT_DISPLAY)
                SDL_FreeSurface(root->widget_list[i]->widget_sub[p]->text.font_surface);

            free(root->widget_list[i]->widget_sub[p]);
        }

        free(root->widget_list[i]->widget);
        free(root->widget_list[i]->widget_sub);
        free(root->widget_list[i]);
    }

	for (int i = 0; i < root->number_font; ++i)
		TTF_CloseFont(root->font_list[i]);

    SDL_FreeSurface(root->screen);

    free(root->widget_list);
	free(root->font_list);
    free(root);
}
