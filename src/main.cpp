/*
 * Itchy.cpp
 *
 *  Created on: Sep 14, 2012
 *      Author: lolzballs
 */

#include <SDL/SDL.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "Itchy++";

int main(int argc, char **argv)
{
   SDL_Init( SDL_INIT_VIDEO );
   SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
   SDL_WM_SetCaption( WINDOW_TITLE, 0 );

   //Load the background
   SDL_Surface* bitmap = SDL_LoadBMP("background.bmp");
   //Won't work with just background.bmp :/

   // Part of the background we want to draw
   SDL_Rect source;
   source.x = 0;
   source.y = 0;
   source.w = 48;
   source.h = 48;

   // Part of the screen we want to draw the sprite to
   SDL_Rect destination;
   destination.x = 0;
   destination.y = 0;
   destination.w = 640;
   destination.h = 480;
   SDL_Event event;

   bool gameRunning = true;

   while (gameRunning)
   {
      if (SDL_PollEvent(&event))
      {
         if (event.type == SDL_QUIT)
         {
            gameRunning = false;
         }
      }

      SDL_BlitSurface(bitmap, &source, screen, &destination);
      SDL_Flip(screen);
   }
   SDL_FreeSurface(bitmap);
   SDL_Quit();
   return 0;
}