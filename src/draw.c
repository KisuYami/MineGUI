#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "widget.h"
#include "create.h"
#include "draw.h"

#define BORDER_SIZE 1
#define BORDER_RADIUS 1
/*********************************************************/
/* When any of the functions below is mannually called,  */
/*   YOU need to flip the scren(SDL_Flip(root->screen)); */
/*********************************************************/

int
minegui_draw_widget(struct minegui_root *root,
					struct minegui_widget *widget)
{
    int x, y;
	int comp_x1, comp_x2, comp_y1, comp_y2;

    int offset;
    Uint16 *raw_pixels;

    SDL_LockSurface(root->screen);
    raw_pixels = (Uint16 *)root->screen->pixels;

	comp_x1 = widget->box.size.x1 + widget->box.margin.top;
	comp_x2 = widget->box.size.x2 + widget->box.margin.top;

    for(x = comp_x1; x <= comp_x2; x++)
    {
		comp_y1 = widget->box.size.y1 + widget->box.margin.left;
		comp_y2 = widget->box.size.y2 + widget->box.margin.left;

        for(y = comp_y1; y <= comp_y2; y++)
        {
            offset = root->screen->pitch / 2 * x + y;

			// This is a design decision, tea cup like borders
			if(widget->type & MINEGUI_RADIUS)
			{
				if((x > comp_x1 + BORDER_RADIUS || y > comp_y1 + BORDER_RADIUS) &&
				   (x > comp_x1 + BORDER_RADIUS || y < comp_y2 - BORDER_RADIUS) &&
				   (x < comp_x2 - BORDER_RADIUS || y < comp_y2 - BORDER_RADIUS))
				{
#if 0
					// TODO: Add teacup with borders
					// Draw borders
					if(widget->type & MINEGUI_BORDER)
					{
						if((x < comp_x1 + BORDER_SIZE || y < comp_y1 + BORDER_SIZE) ||
						   (x > comp_x2 - BORDER_SIZE || y > comp_y2 - BORDER_SIZE))
							raw_pixels[offset] = widget->box.color_border;

						else
							raw_pixels[offset] = widget->box.color;
					}
					// Normal tea cup draw
					else
						raw_pixels[offset] = widget->box.color;
#else
					raw_pixels[offset] = widget->box.color;
#endif

				}
			}

			// Draw borders only
			else if(widget->type & MINEGUI_BORDER)
			{
				if((x < comp_x1 + BORDER_SIZE || y < comp_y1 + BORDER_SIZE) ||
				   (x > comp_x2 - BORDER_SIZE || y > comp_y2 - BORDER_SIZE))
					raw_pixels[offset] = widget->box.color_border;

				else
					raw_pixels[offset] = widget->box.color;
			}

			// No special options
			else
				raw_pixels[offset] = widget->box.color;
        }
    }

    SDL_UnlockSurface(root->screen);
    SDL_Flip(root->screen);

    return 0;
}

void
minegui_draw_text(struct minegui_root *root, struct minegui_widget *widget)
{
    SDL_BlitSurface(widget->text.font_surface, NULL, root->screen,
                    &widget->text.font_rect);
}

int
minegui_draw_window(struct minegui_root *root)
{

    int i, p;
    minegui_draw_widget(root, &root->widget);

    if(root->widget_list == NULL)
    {
        fprintf(stderr, "MineSDL: Widget_list in root window is uninitialized\n");
		return 1;
    }

    for (i = 0; i < root->number_widget; ++i)
    {

        if(root->widget_list[i]->widget != NULL)
            minegui_draw_widget(root, root->widget_list[i]->widget);

        else
            fprintf(stderr, "MineSDL: Widget in widget_list[%d] is uninitialized\n", i);

        for (p = 0; p < root->widget_list[i]->number_widget; ++p)
        {

            if(root->widget_list[i]->widget_sub[p] != NULL)
            {
                minegui_draw_widget(root, root->widget_list[i]->widget_sub[p]);

                if(root->widget_list[i]->widget_sub[p]->type | MINEGUI_TEXT_DISPLAY)
                {
					if(root->widget_list[i]->widget_sub[p]->text.text != NULL)
						minegui_draw_text(root, root->widget_list[i]->widget_sub[p]);

					else
						fprintf(stderr, "MineSDL: text from sub_widget[%d] in widget_list[%d] is uninitialized\n", p, i);
                }
            }

            else
                fprintf(stderr, "MineSDL: sub_widget[%d] in widget_list[%d] is uninitialized\n", p, i);
        }

    }

    return 0;
}
