#ifndef WIDGET_H
#define WIDGET_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stddef.h>

enum box_types
{

    DISPLAY		    = 0,
    TEXT_DISPLAY	= 1,
    TEXT_INPUT	    = 2,
    BUTTON		    = 4,

};

struct size
{

    int x1, x2;
    int y1, y2;

};

struct margin
{

    int top;
    int left;

};

struct minesdl_box
{

    Uint16 color;
    Uint16 color_pressed; // When it is a button;

    struct size size;
    struct margin margin;

};

struct minesdl_text
{

    char	*text;
    size_t	 font_size;

    int		     font_style;
    TTF_Font	*font_familly;
    SDL_Rect	 font_rect;
    SDL_Color	 font_color;

    SDL_Surface *font_surface;
};

// TODO: and add borders
struct minesdl_widget
{

    int type;
	int clicked;

    void (*action[3])();

    struct margin		margin;
    struct minesdl_box	box;
    struct minesdl_text	text;

};

struct minesdl_widget_list
{

    int number_widget;
    int used_widget;

    struct minesdl_widget *widget;
    struct minesdl_widget **widget_sub;

};

struct minesdl_root
{
    int volatile redraw_flag;

    int fullscreen;
    int mode;

    SDL_Surface *screen;
    SDL_Rect	 size;

    int number_widget;

    struct minesdl_widget widget;
    struct minesdl_widget_list **widget_list;
};
#endif /* WIDGET_H */
