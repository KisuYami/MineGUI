#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "interaction.h"
#include "widget.h"
#include "loop.h"
#include "draw.h"
#include "mem.h"

void
minegui_loop(struct minegui_root *root)
{
    SDL_Event event;

    atexit(SDL_Quit);
    atexit(TTF_Quit);

    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    minegui_draw_window(root);

    while(SDL_WaitEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            minegui_check_button_click(root, &event);
            break;

        case SDL_QUIT:
            minegui_clean_root(root);
            TTF_Quit();
            exit(0);
            break;
        }

	if(root->redraw_flag == 1) {
	    minegui_draw_window(root);
	    root->redraw_flag = 0;
	}
    }
}
