#pragma once
class IRenderer;  // Forward declare

class DemoScene {
public:
    void Update(float deltaTime);  // Para futuro animaciones, por ahora vacío
    void Render(IRenderer* renderer);
};
