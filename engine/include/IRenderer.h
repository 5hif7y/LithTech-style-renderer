#pragma once

class IRenderer {
public:
    virtual bool Init(int width, int height) = 0;
    virtual void Shutdown() = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;


    virtual ~IRenderer() {}

  virtual void SetClearColor(float r, float g, float b, float a) = 0;
  virtual void DrawQuad(float x, float y, float w, float h, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) = 0;
  virtual void DrawSprite(float x, float y, float w, float h) = 0;
};

extern "C" {
    typedef IRenderer* (*CreateRendererFn)();
    typedef void (*DestroyRendererFn)(IRenderer*);
}

