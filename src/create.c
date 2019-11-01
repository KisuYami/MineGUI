#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "widget.h"
#include "create.h"

MineGUI_root *
minegui_create_root(int v_size, int h_size,
					int mode, int fullscreen,
					int size, int font_number)
{
    struct minegui_root *root = NULL;
    root = malloc(sizeof(struct minegui_root));

    if(!root)
    {
        fprintf(stderr, "MineSDL: Failed to allocate memory for root window\n");
        exit(1);
    }

    *root = (struct minegui_root)
    {

        .screen = NULL,

        .fullscreen = fullscreen,
        .mode = mode,

        .number_widget = size,
        .number_font = font_number,

        .widget_list = NULL,
		.font_list = NULL, // TODO: Handle freeing

        .size = (struct SDL_Rect)
        {
            .w = v_size,
            .h = h_size,
            .x = 0,
            .y = 0,
        },

        .widget = (struct minegui_widget)
        {

            .type = MINEGUI_DISPLAY,

            .margin = (struct margin)
            {
                .left = 0,
                .top = 0,
            },

            .box = (struct minegui_box)
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
        root->widget_list = malloc(sizeof(struct minegui_widget_list) * size);

    if(font_number > 0)
        root->font_list = malloc(sizeof(TTF_Font **) * font_number);

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "MineGUI: Failed to create root window\n");
        free(root);
        exit(1);
    }

    root->screen = SDL_SetVideoMode(root->size.h, root->size.w,
                                    root->mode, root->fullscreen);

    if(!root->screen)
    {
        fprintf(stderr, "MineGUI: Failed to create root window\n");
        free(root);
        exit(1);
    }

	if(!root->font_list)
	{
		fprintf(stderr, "MineGUI: Failed to alocate memory for font_list");
		exit(1);
	}

    return root;
}

struct minegui_widget *
minegui_create_widget(struct minegui_widget_list *widget_list,
					  int x1, int x2, int y1, int y2,
					  int margin_top, int margin_left,
					  int type, Uint16 color,
					  Uint16 color_border)
{
    struct minegui_widget *widget;
    int final_margin_left, final_margin_top;

    if(widget_list)
    {

		widget_list->widget_sub[widget_list->used_widget] = malloc(sizeof(struct minegui_widget));
		widget = widget_list->widget_sub[widget_list->used_widget];

        final_margin_top = margin_top + widget_list->widget->box.size.x1;
        final_margin_left = margin_left + widget_list->widget->box.size.y1;

		widget_list->used_widget++;

    } else {

        widget = malloc(sizeof(struct minegui_widget));

        final_margin_top = margin_top;
        final_margin_left = margin_left;

    }

    if(!widget)
    {
        fprintf(stderr, "MineSDL: Failed to allocate memory for widget\n");
        exit(1);
    }

    *widget = (struct minegui_widget)
    {

        .type = type,

        .box = (struct minegui_box)
        {

            .color = color,
            .color_border = color_border,

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

struct minegui_widget_list *
minegui_create_widget_list(int x1, int x2,
						   int y1, int y2,
						   int size, Uint16 color)
{
    struct minegui_widget_list *list;

    list = malloc(sizeof(struct minegui_widget_list));

    if(!list)
    {

        fprintf(stderr, "MineSDL: Failed to allocate memory for widget list\n");
        exit(1);

    }

    *list = (struct minegui_widget_list)
    {

        .widget = minegui_create_widget(NULL, x1, x2, y1, y2, 0, 0,
                                        MINEGUI_DISPLAY, color, 0),

		.widget_sub = NULL,
		.number_widget = size,
		.used_widget = 0,

    };

    if(size > 0)
        list->widget_sub = malloc(sizeof(struct minegui_widget **) * size);

    return list;
}

Uint16
minegui_create_color(SDL_PixelFormat *fmt, Uint8 red, Uint8 green, Uint8 blue)
{
    Uint16 value;
    value = ((red >> fmt->Rloss) << fmt->Rshift) +
            ((green >> fmt->Gloss) << fmt->Gshift) +
            ((blue >> fmt->Bloss) << fmt->Bshift);

    return value;
}

TTF_Font *
minegui_create_font(char *font_name, int font_size, int font_style)
{
	if(!TTF_WasInit() && TTF_Init() == -1)
	{
		printf("MineGUI: %s\n", TTF_GetError());
		return NULL;
	}

    TTF_Font *font_familly = TTF_OpenFont(font_name, font_size);

    if(!font_familly)
        fprintf(stderr, "MineGUI: %s\n", TTF_GetError());

    if(font_style != 0)
        TTF_SetFontStyle(font_familly, font_style);

    TTF_SetFontKerning(font_familly, 1);

	return font_familly;
}


/* If you want to use this to change a already 
   created text_surface, free the surface and 
   the text struct */

void
minegui_create_text(TTF_Font *font, MineGUI_widget *widget,
					int x, int y, int v_size, int h_size,
					char *text, int red, int green, int blue)
{
	if(!TTF_WasInit() && TTF_Init() == -1)
	{
		printf("MineGUI: %s\n", TTF_GetError());
		return;
	}

    struct minegui_text final_text;

    final_text = (struct minegui_text)
    {

        .text = text,
        .font_familly = font,
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

	if(!font)
	{
		printf("MineGUI: font wanst opened\n");
		return;
	}

    final_text.font_surface = TTF_RenderText_Blended(final_text.font_familly,
													 text, final_text.font_color);

    if(!final_text.font_surface)
        fprintf(stderr, "MineGUI: %s\n", TTF_GetError());

    widget->text = final_text;
}

void
minegui_change_text(struct minegui_widget *widget, char *new_text)
{

	SDL_Surface *text_surface = NULL;

	if(!TTF_WasInit() && TTF_Init() == -1)
	{
		fprintf(stderr, "MineGUI: %s\n", TTF_GetError());
		return;
	}

	if(!widget->text.font_familly)
	{
		fprintf(stderr, "MineGUI: widget->text.font_familly was not initialized\n");
		return;
	}

	text_surface = TTF_RenderText_Blended(widget->text.font_familly,
							   new_text, widget->text.font_color);

	if(!text_surface)
	{
		fprintf(stderr, "MineGUI: failed to change text: %s", TTF_GetError());
		return;
	}

	SDL_FreeSurface(widget->text.font_surface);
	widget->text.font_surface = text_surface;
}
