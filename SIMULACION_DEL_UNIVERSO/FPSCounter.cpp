#include "FPSCounter.h"
#include <iostream>

FPSCounter::FPSCounter() : frameCount(0), lastTime(glfwGetTime()), fps(0.0) {}

void FPSCounter::frameRendered() {
    ++frameCount;
    double currentTime = glfwGetTime();
    if (currentTime - lastTime >= 1.0) {
        fps = frameCount / (currentTime - lastTime);
        frameCount = 0;
        lastTime = currentTime;

        // Imprimir FPS por consola
        std::cout << "FPS: " << fps << std::endl;
    }
}

double FPSCounter::getFPS() const {
    return fps;
}