#include "IRenderer.h"
#include <SDL2/SDL.h>  // Necesario para SDL_Event y SDL_QUIT
#include "DemoScene.h"
#include <iostream>

bool Engine_LoadRenderer(const char* name);
IRenderer* Engine_GetRenderer();

int main()
{
    if (!Engine_LoadRenderer("./libOGL4REN.so"))
    {
        std::cout << "No pude cargar el renderer\n";
        return 1;
    }

    IRenderer* r = Engine_GetRenderer();
    if (!r->Init(800, 600))
    {
        std::cout << "Fallo al inicializar el renderer\n";
        return 1;
    }

    DemoScene scene;
    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
            // Puedes añadir teclas aquí más adelante, ej: ESC
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        r->BeginFrame();
        //r->DrawSprite(-0.5f, -0.5f, 1.0f, 1.0f);  // Cuadrado blanco centrado que ocupa casi toda la pantalla
	scene.Render(r);
        r->EndFrame();
    }

    r->Shutdown();
    return 0;
}
