#ifndef DRAW_H
#define DRAW_H

#include "widget.h"

/* Render the full APP */
int
minegui_draw_window(struct minegui_root *root);

/* Render a widget in the selected root */
int
minegui_draw_widget(struct minegui_root *root,
		    struct minegui_widget *widget);

/* Render text from a widget */
void
minegui_draw_text(struct minegui_root *root,
		  struct minegui_widget *widget);

#endif /* DRAW_H */
