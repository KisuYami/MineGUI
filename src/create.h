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

struct minesdl_widget_list *
minesdl_create_widget_list(int x1, int x2,
			   int y1, int y2,
			   int size, Uint16 color);

struct minesdl_widget *
minesdl_create_widget(struct minesdl_widget_list *widget_list,
		      int x1, int x2, int y1, int y2,
		      int margin_top, int margin_left,
		      int type, Uint16 color, Uint16 color_pressed);

struct minesdl_root *
minesdl_create_root(int v_size, int h_size,
		    int mode, int fullscreen,
		    int size);

Uint16
minesdl_create_color(SDL_PixelFormat *fmt, Uint8 red,
		     Uint8 green, Uint8 blue);

void
minesdl_create_text(struct minesdl_widget *widget,
		    int x, int y, int v_size, int h_size, int font_size,
		    int style, char *text, char *font_familly,
		    int red, int green, int blue);

void
minesdl_change_text(struct minesdl_widget *widget, char *new_text);
#endif /* CREATE_H */
