//
// Created by roussierenoa on 3/27/25.
//

#ifndef SDLENCAPSULATION_HPP
#define SDLENCAPSULATION_HPP

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class SDLEncapsulation {
private:
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
public:

	SDLEncapsulation();
	~SDLEncapsulation();
};



#endif //SDLENCAPSULATION_HPP
