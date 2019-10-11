#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "widget.h"
#include "create.h"

struct minesdl_root *
minesdl_create_root(int v_size, int h_size,
		    int mode, int fullscreen,
		    int size)
{
    struct minesdl_root *root = NULL;
    root = malloc(sizeof(struct minesdl_root));

    if(root == NULL)
    {
        fprintf(stderr, "MineSDL: Failed to allocate memory for root window\n");
        exit(1);
    }

    *root = (struct minesdl_root)
    {

        .screen = NULL,

        .fullscreen = fullscreen,
        .mode = mode,

        .number_widget = size,
        .widget_list = NULL,

        .size = (struct SDL_Rect)
        {
            .w = v_size,
            .h = h_size,
            .x = 0,
            .y = 0,
        },

        .widget = (struct minesdl_widget)
        {

            .type = DISPLAY,

            .margin = (struct margin)
            {
                .left = 0,
                .top = 0,
            },

            .box = (struct minesdl_box)
            {

                .margin = (struct margin)
                {

                    .top = 0,
                    .left = 0,

                },

                .size = (struct size)
                {

                    .x1 = 0,
                    .x2 = v_size,
                    .y1 = 0,
                    .y2 = h_size,

                },
            },

        },

    };

    if(size > 0)
        root->widget_list = malloc(sizeof(struct minesdl_widget_list) * size);

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "MineSDL: Failed to create root window\n");
        free(root);
        exit(1);
    }

    root->screen = SDL_SetVideoMode(root->size.h, root->size.w,
                                    root->mode, root->fullscreen);

    if(!root->screen)
    {
        fprintf(stderr, "MineSDL: Failed to create root window\n");
        free(root);
        exit(1);
    }

    return root;
}

struct minesdl_widget *
minesdl_create_widget(struct minesdl_widget_list *widget_list,
		      int x1, int x2, int y1, int y2,
		      int margin_top, int margin_left,
		      int type, Uint16 color,
		      Uint16 color_pressed)
{
    struct minesdl_widget *widget;
    int final_margin_left, final_margin_top;

    if(widget_list != NULL)
    {

        widget_list->widget_sub[0] = malloc(sizeof(struct minesdl_widget));
        widget = widget_list->widget_sub[0];

        final_margin_top = margin_top + widget_list->widget->box.size.y1;
        final_margin_left = margin_left + widget_list->widget->box.size.x1;

    }
    else
    {

        widget = malloc(sizeof(struct minesdl_widget));

        final_margin_top = margin_top;
        final_margin_left = margin_left;

    }

    if(widget == NULL)
    {
        fprintf(stderr, "MineSDL: Failed to allocate memory for widget\n");
        exit(1);
    }

    *widget = (struct minesdl_widget)
    {

        .type = type,

        .box = (struct minesdl_box)
        {

            .color = color,
            .color_pressed = color_pressed,

            .margin = (struct margin)
            {

                .top = final_margin_top,
                .left = final_margin_left,

            },
            .size = (struct size)
            {

                .x1 = x1,
                .x2 = x2,
                .y1 = y1,
                .y2 = y2,

            },

        },

    };

    return widget;
}

struct minesdl_widget_list *
minesdl_create_widget_list(int x1, int x2,
			   int y1, int y2,
			   int size, Uint16 color)
{
    struct minesdl_widget_list *list;

    list = malloc(sizeof(struct minesdl_widget_list));

    if(list == NULL)
    {

        fprintf(stderr, "MineSDL: Failed to allocate memory for widget list\n");
        exit(1);

    }

    *list = (struct minesdl_widget_list)
    {

        .widget = minesdl_create_widget(NULL, x1, x2, y1, y2, 0, 0,
                                        DISPLAY, color, 0),

                  .widget_sub = NULL,
                  .number_widget = size,

    };

    if(size > 0)
        list->widget_sub = malloc(sizeof(struct minesdl_widget **) * size);

    return list;
}

Uint16
minesdl_create_color(SDL_PixelFormat *fmt, Uint8 red, Uint8 green, Uint8 blue)
{
    Uint16 value;
    value = ((red >> fmt->Rloss) << fmt->Rshift) +
            ((green >> fmt->Gloss) << fmt->Gshift) +
            ((blue >> fmt->Bloss) << fmt->Bshift);

    return value;
}

void
minesdl_create_text(struct minesdl_widget *widget,
		    int x, int y, int v_size, int h_size,
		    int font_size, int style, char *text,
		    char *font_familly, int red, int green, int blue)
{

    TTF_Init();
    struct minesdl_text final_text;

    final_text = (struct minesdl_text)
    {

        .text = text,
        .font_style = style,
        .font_size = font_size,
        .font_familly = NULL,
        .font_surface = NULL,

        .font_color = (struct SDL_Color)
        {
            .r = red,
            .g = green,
            .b = blue,
        },

        .font_rect = (struct SDL_Rect)
        {
            .x = y + widget->box.margin.left,
            .y = x + widget->box.margin.top,
            .w = h_size,
            .h = v_size,
        },

    };

    final_text.font_familly = TTF_OpenFont(font_familly, final_text.font_size);

    if(final_text.font_familly == NULL)
        fprintf(stderr, "MineGUI: %s\n", TTF_GetError());

    if(style != 0)
        TTF_SetFontStyle(final_text.font_familly, style);

    TTF_SetFontKerning(final_text.font_familly, 1);

    final_text.font_surface = TTF_RenderText_Blended(final_text.font_familly,
						     text, final_text.font_color);

    if(final_text.font_surface == NULL)
        fprintf(stderr, "MineGUI: %s\n", TTF_GetError());

    widget->text = final_text;
}

void
minesdl_change_text(struct minesdl_widget *widget, char *new_text)
{
	TTF_Init();
	SDL_FreeSurface(widget->text.font_surface);
	widget->text.font_surface = TTF_RenderText_Blended(widget->text.font_familly,
							   new_text, widget->text.font_color);
}
