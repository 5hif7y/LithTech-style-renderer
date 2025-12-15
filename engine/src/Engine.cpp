#include "IRenderer.h"
#include <iostream>

#if _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

static IRenderer* renderer = nullptr;
static void* libHandle = nullptr;

bool Engine_LoadRenderer(const char* dllName)
{
#if _WIN32
    libHandle = LoadLibraryA(dllName);
    if (!libHandle) return false;
    auto createFn = (CreateRendererFn)GetProcAddress((HMODULE)libHandle, "CreateRenderer");
#else
    libHandle = dlopen(dllName, RTLD_NOW);
    if (!libHandle) {
        std::cout << "dlopen falló: " << dlerror() << std::endl;
        return false;
    }

    // Limpia errores previos
    dlerror();

    auto createFn = (CreateRendererFn)dlsym(libHandle, "CreateRenderer");
    char* error = dlerror();
    if (error != nullptr) {
        std::cout << "dlsym falló: " << error << std::endl;
        return false;
    }
#endif
    if (!createFn) return false;

    renderer = createFn();
    return true;
}

IRenderer* Engine_GetRenderer()
{
    return renderer;
}

