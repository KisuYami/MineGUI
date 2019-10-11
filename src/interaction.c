#include <SDL/SDL.h>
#include "minegui.h"

void
minesdl_bind_action(struct minesdl_widget *widget, int mouse,
		    void (*action)(struct minesdl_root *root))
{
    widget->action[mouse] = action;
}
