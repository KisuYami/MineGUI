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

/* Create a new Root window */
MineGUI_root *
minegui_create_root(int v_size, int h_size,
					int mode, int fullscreen,
					int size, int font_number);

/* Create a new widget */
struct minegui_widget *
minegui_create_widget(struct minegui_widget_list *widget_list,
					  int x1, int x2, int y1, int y2,
					  int margin_top, int margin_left,
					  int type, Uint16 color,
					  Uint16 color_border);

/* Create a new widget list */
struct minegui_widget_list *
minegui_create_widget_list(int x1, int x2,
						   int y1, int y2,
						   int size, Uint16 color);

/* Create a new RGB color and return it's value */
Uint16
minegui_create_color(SDL_PixelFormat *fmt,
                     Uint8 red, Uint8 green, Uint8 blue);

/* Create a new TTF_Font */
TTF_Font *
minegui_create_font(char *font_name, int font_size, int font_style);

/* Create a surface with text */
void
minegui_create_text(TTF_Font *font, MineGUI_widget *widget,
					int x, int y, int v_size, int h_size,
					char *text, int red, int green, int blue);

/* Change the text from a already initialized minegui_text */
void
minegui_change_text(struct minegui_widget *widget, char *new_text);
#endif /* CREATE_H */
