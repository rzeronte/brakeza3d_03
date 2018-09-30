#include <iostream>
#include <SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

struct point2d {
    float x;
    float y;
};


float degreesToRadians(float angleDegrees)
{
    return angleDegrees * (float) M_PI / (float) 180.0;;
}

point2d rotaVertice(point2d o, point2d p, float angulo)
{
    float r = sqrtf( powf( (p.x-o.x), 2) + powf( (p.y-o.y), 2) );

    float a = sinf(degreesToRadians(angulo)) * r;
    float b = cosf(degreesToRadians(angulo)) * r;

    point2d p2;
    p2.x = b + o.x;
    p2.y = a + o.y;

    return p2;
}

int main() {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    // Limpiamos la pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    point2d center;
    center.x = WINDOW_WIDTH/2;
    center.y = WINDOW_HEIGHT/2;

    point2d p;
    p.x = (WINDOW_WIDTH/2) + 100;
    p.y = (WINDOW_HEIGHT/2) + 100;

    for (int i = 0; i<=360; i+=1) {
        point2d rotated_point = rotaVertice(center, p, (float) i);
        SDL_RenderDrawPoint(renderer, rotated_point.x, rotated_point.y);
    }
    SDL_RenderPresent(renderer);

    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
