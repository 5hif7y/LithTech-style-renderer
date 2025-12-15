#include "RendererOGL4.h"
#include <glad/gl.h>
#include <fstream>
#include <iostream>

static std::string LoadFile(const char* path)
{
    std::ifstream f(path);
    return std::string((std::istreambuf_iterator<char>(f)),
                       std::istreambuf_iterator<char>());
}

bool RendererOGL4::Init(int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("OGL4REN",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_OPENGL);

    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    //gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    // --- QUAD ---
    float quad[] = {
        0, 0,
        1, 0,
        1, 1,
        0, 1
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);

    // --- SHADER (LearnOpenGL style) ---
    auto vsSrc = LoadFile("shaders/sprite.vert");
    auto fsSrc = LoadFile("shaders/sprite.frag");

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    const char* v = vsSrc.c_str();
    glShaderSource(vs, 1, &v, NULL);
    glCompileShader(vs);

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* f = fsSrc.c_str();
    glShaderSource(fs, 1, &f, NULL);
    glCompileShader(fs);

    shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return true;
}

void RendererOGL4::BeginFrame()
{
    //glClearColor(0.1, 0.1, 0.15, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RendererOGL4::DrawSprite(float x, float y, float w, float h)
{
    glUseProgram(shader);

    int locPos  = glGetUniformLocation(shader, "uPos");
    int locSize = glGetUniformLocation(shader, "uSize");

    glUniform2f(locPos,  x, y);
    glUniform2f(locSize, w, h);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void RendererOGL4::EndFrame()
{
    SDL_GL_SwapWindow(window);
}

void RendererOGL4::Shutdown()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void RendererOGL4::SetClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void RendererOGL4::DrawQuad(float x, float y, float w, float h, float r, float g, float b, float a) {
    glUseProgram(shader);

    // Uniforms existentes para pos/size
    int locPos = glGetUniformLocation(shader, "uPos");
    int locSize = glGetUniformLocation(shader, "uSize");
    glUniform2f(locPos, x, y);
    glUniform2f(locSize, w, h);

    // Nuevo uniform para color (agrega en sprite.frag: uniform vec4 uColor; FragColor = uColor;)
    int locColor = glGetUniformLocation(shader, "uColor");
    glUniform4f(locColor, r, g, b, a);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}


extern "C" IRenderer* CreateRenderer() { return new RendererOGL4(); }
extern "C" void DestroyRenderer(IRenderer* r) { delete r; }

