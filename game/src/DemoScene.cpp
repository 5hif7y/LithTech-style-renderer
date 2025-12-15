#include "DemoScene.h"
#include "IRenderer.h"  // Ruta relativa o include path

void DemoScene::Update(float deltaTime) {
    // Por ahora nada; más adelante: animar quad, etc.
}

void DemoScene::Render(IRenderer* renderer) {
    renderer->SetClearColor(0.1f, 0.1f, 0.15f, 1.0f);  // Fondo azul oscuro
    renderer->DrawQuad(-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);  // Quad blanco centrado
}
