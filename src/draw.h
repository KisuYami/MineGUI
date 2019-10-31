#ifndef DRAW_H
#define DRAW_H

#include "widget.h"

int
minegui_draw_window(struct minegui_root *root);

int
minegui_draw_widget(struct minegui_root *root,
		    struct minegui_widget *widget);

void
minegui_draw_text(struct minegui_root *root,
		  struct minegui_widget *widget);

#endif /* DRAW_H */
