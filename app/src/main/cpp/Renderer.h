#ifndef ANDROIDGLINVESTIGATIONS_RENDERER_H
#define ANDROIDGLINVESTIGATIONS_RENDERER_H

#include <EGL/egl.h>
#include <memory>
#include <vector>

#include "Model.h"
#include "Shader.h"
#include "GameEngine.h"

struct android_app;

class Renderer {
public:
    inline Renderer(android_app *pApp) :
            app_(pApp),
            display_(EGL_NO_DISPLAY),
            surface_(EGL_NO_SURFACE),
            context_(EGL_NO_CONTEXT),
            width_(0),
            height_(0),
            shaderNeedsNewProjectionMatrix_(true),
            lastFrameTime_(0.0) {
        initRenderer();
        gameEngine_ = std::make_unique<GameEngine>(1080, 1920);
    }

    virtual ~Renderer();

    void handleInput();
    void render();

private:
    void initRenderer();
    void updateRenderArea();
    void createModels();

    android_app *app_;
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLint width_;
    EGLint height_;

    bool shaderNeedsNewProjectionMatrix_;
    double lastFrameTime_;

    std::unique_ptr<Shader> shader_;
    std::vector<Model> models_;
    std::unique_ptr<GameEngine> gameEngine_;
};

#endif //ANDROIDGLINVESTIGATIONS_RENDERER_H
