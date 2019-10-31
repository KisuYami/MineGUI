#include <SDL/SDL.h>
#include "minegui.h"

void
minegui_bind_action(struct minegui_widget *widget, int mouse,
		    void (*action)(struct minegui_root *root))
{
    widget->action[mouse] = action;
}

void
minegui_check_button_click(struct minegui_root *root,
						   SDL_Event *mouse)
{
    int i, p;

    for (i = 0; i < root->number_widget; ++i)
    {
        for (p = 0; p < root->widget_list[i]->number_widget; ++p)
        {
            if(root->widget_list[i]->widget_sub[i]->type | MINEGUI_BUTTON)
            {
                struct minegui_box *position = &root->widget_list[i]->widget_sub[p]->box;

                if((mouse->button.x >= position->size.y1 + position->margin.left) &&
				   (mouse->button.x <= position->size.y2 + position->margin.left) &&
				   (mouse->button.y >= position->size.x1 + position->margin.top)  &&
				   (mouse->button.y <= position->size.x2 + position->margin.top))
				{
                    if(root->widget_list[i]->widget_sub[p]->action[mouse->button.button - 1] != NULL)
					{
						root->widget_list[i]->widget_sub[p]->clicked = 1;
						root->widget_list[i]->widget_sub[p]->action[mouse->button.button - 1](root);
						root->widget_list[i]->widget_sub[p]->clicked = 0;
					}
				}
            }
        }
    }
}
