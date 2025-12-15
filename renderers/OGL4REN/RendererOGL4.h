#pragma once
#include "IRenderer.h"
#include <SDL2/SDL.h>

class RendererOGL4 : public IRenderer {
public:
    bool Init(int width, int height) override;
    void Shutdown() override;

    void BeginFrame() override;
    void EndFrame() override;

    void DrawSprite(float x, float y, float w, float h) override;
	void SetClearColor(float r, float g, float b, float a);
	void DrawQuad(float x, float y, float w, float h, float r, float g, float b, float a);

private:
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;

    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int shader = 0;
};

