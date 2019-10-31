#ifndef INTERACTION_H
#define INTERACTION_H
#include "widget.h"

void
minegui_bind_action(struct minegui_widget *, int,
					void (*)(struct minegui_root *));

void
minegui_check_button_click(struct minegui_root *,
						   SDL_Event *);

#endif /* INTERACTION_H */
