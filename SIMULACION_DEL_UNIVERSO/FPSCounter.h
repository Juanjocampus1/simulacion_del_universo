#pragma once
#include <GLFW/glfw3.h>

class FPSCounter {
public:
    FPSCounter();
    void frameRendered();
    double getFPS() const;

private:
    int frameCount;
    double lastTime;
    double fps;
};