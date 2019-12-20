#ifndef WIDGET_H
#define WIDGET_H

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>

#include <stddef.h>

/* Print a debug message with the function, 
file and line from where it's used */
#define error(from, message)                                        \
    fprintf(stderr, "minegui_%s: <%s> <%s:%d>: %s\n",               \
            from, __func__, __FILE__, __LINE__, message);           \

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

/* Information about how a widget should be rendered */
struct minegui_box
{
    Uint16 color;
    Uint16 color_border; // When it is a button;

    struct size size;
    struct margin margin;
};

/* Information about how a widget text should be rendered */
struct minegui_text
{
    char	*text;

    TTF_Font	*font_familly;
    SDL_Rect	 font_rect;
    SDL_Color	 font_color;

    SDL_Surface *font_surface;
};

/* Contain information about a widget */
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

/* The main APP window shall keep information about the window size,
 mode, the fonts used and the widgets presents in the APP */
struct minegui_root
{
    int redraw_flag;

    int fullscreen;
    int mode;

    SDL_Surface *screen;
    SDL_Rect	 size;

    int number_widget;
    int number_font;

	TTF_Font **font_list;

    struct minegui_widget widget;
    struct minegui_widget_list **widget_list;
};

typedef struct minegui_root MineGUI_root;
typedef struct minegui_widget MineGUI_widget;

#endif /* WIDGET_H */
