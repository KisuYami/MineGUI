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

#if 0 // TODO: Add teacup with borders
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
#else // For now we use this
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
	if(!root)
	{
        fprintf(stderr, "MineSDL: root window is uninitialized\n");
		return 1;
	}
	else
		minegui_draw_widget(root, &root->widget);
		

    if(!root->widget_list)
    {
        fprintf(stderr, "MineSDL: Widget_list in root window is uninitialized\n");
		return 1;
    }

    for (i = 0; i < root->number_widget; ++i)
    {

        if(root->widget_list[i]->widget)
            minegui_draw_widget(root, root->widget_list[i]->widget);

        else
            fprintf(stderr, "MineSDL: Widget in widget_list[%d] is uninitialized\n", i);

        for (p = 0; p < root->widget_list[i]->number_widget; ++p)
        {

			MineGUI_widget *widget = root->widget_list[i]->widget_sub[p];

			/* Widget itself */
            if(widget)
                minegui_draw_widget(root, widget);

            else
                fprintf(stderr, "MineSDL: sub_widget[%d] in widget_list[%d] is uninitialized\n", p, i);

			/* Text on widget */
			if(widget->text.font_surface && widget->type & MINEGUI_TEXT_DISPLAY)
				minegui_draw_text(root, widget);
			
			else if(!widget->text.font_surface)
				fprintf(stderr, "MineSDL: font_surface from sub_widget[%d] in widget_list[%d] is uninitialized\n", p, i);

        }

    }

	SDL_Flip(root->screen);

    return 0;
}
