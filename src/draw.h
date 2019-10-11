#ifndef DRAW_H
#define DRAW_H

#include "widget.h"

int
minesdl_draw_window(struct minesdl_root *root);

int
minesdl_draw_widget(struct minesdl_root *root,
		    struct minesdl_widget *widget);

void
minesdl_draw_text(struct minesdl_root *root,
		  struct minesdl_widget *widget);

#endif /* DRAW_H */
