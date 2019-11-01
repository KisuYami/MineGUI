#ifndef CREATE_H
#define CREATE_H

/******************************************************************************
 * File:             create.h
 *
 * Author:           Reberti Cavalho Soares  
 * Created:          13/10/2019
 * Description:      This functions shall be used to initialize structs
 *****************************************************************************/

#include <stddef.h>
#include "widget.h"

struct minegui_widget_list *
minegui_create_widget_list(int, int, int, int, int, Uint16);

MineGUI_widget *
minegui_create_widget(struct minegui_widget_list *,
					  int, int, int, int, int, int,
					  int, Uint16, Uint16);

MineGUI_root *
minegui_create_root(int, int, int, int, int, int);

Uint16
minegui_create_color(SDL_PixelFormat *, Uint8, Uint8, Uint8);

TTF_Font *
minegui_create_font(char *, int, int);

void
minegui_create_text(TTF_Font *, MineGUI_widget *,
					int, int, int, int,
					char *, int, int, int);

void
minegui_change_text(struct minegui_widget *, char *);
#endif /* CREATE_H */
