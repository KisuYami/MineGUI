#ifndef INTERACTION_H
#define INTERACTION_H
#include "widget.h"

void
minesdl_bind_action(struct minesdl_widget *widget, int mouse,
		    void (*action)(struct minesdl_root *root));

#endif /* INTERACTION_H */
