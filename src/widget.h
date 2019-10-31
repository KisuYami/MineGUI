#ifndef WIDGET_H
#define WIDGET_H

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>

#include <stddef.h>

enum box_types
{
    MINEGUI_DISPLAY		    = 0,
    MINEGUI_TEXT_DISPLAY	= 1,
    MINEGUI_TEXT_INPUT	    = 2,
    MINEGUI_BUTTON		    = 4,
	MINEGUI_BORDER          = 8,
	MINEGUI_RADIUS          = 16,
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

struct minegui_box
{
    Uint16 color;
    Uint16 color_border; // When it is a button;

    struct size size;
    struct margin margin;
};

struct minegui_text
{
    char	*text;
    size_t	 font_size;

    int		     font_style;
    TTF_Font	*font_familly;
    SDL_Rect	 font_rect;
    SDL_Color	 font_color;

    SDL_Surface *font_surface;
};

// TODO: add borders
struct minegui_widget
{
    int type;
	int clicked;

    void (*action[3])();

    struct margin		margin;
    struct minegui_box	box;
    struct minegui_text	text;
};

struct minegui_widget_list
{
    int number_widget;
    int used_widget;

    struct minegui_widget *widget;
    struct minegui_widget **widget_sub;
};

struct minegui_root
{
    int volatile redraw_flag;

    int fullscreen;
    int mode;

    SDL_Surface *screen;
    SDL_Rect	 size;

    int number_widget;

    struct minegui_widget widget;
    struct minegui_widget_list **widget_list;
};

// Some typedefs for who will use the API
typedef struct minegui_root MineGUI_root;
typedef struct minegui_widget MineGUI_widget;

#endif /* WIDGET_H */
