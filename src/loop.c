#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>

#include "interaction.h"
#include "widget.h"
#include "loop.h"
#include "draw.h"
#include "mem.h"

void
minegui_loop(struct minegui_root *root)
{
    SDL_Event event;

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

			SDL_QuitSubSystem(SDL_INIT_VIDEO);

			TTF_Quit();
			SDL_Quit();

            minegui_clean_root(root);

            exit(0);
        }

		if(root->redraw_flag == 1) {
			minegui_draw_window(root);
			root->redraw_flag = 0;
		}
    }
}
