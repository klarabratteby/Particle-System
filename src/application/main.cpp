#include <tracy/Tracy.hpp>
#include <rendering/window.h>
#include <particlesystem/particlesystem.h>
#include "particles.h"
//#include "effects.h"
//#include "emitter.h"

#include <cmath>
#include <cstdlib>
#include <vector>

#include <fmt/format.h>

int main(int, char**) try {
    rendering::Window window("Particle System v0.0.1 pre-release alpha", 850, 850);

    double prevTime = 0.0;
    float speed = 1.0f; // simulation speed
    float angle;
    //float amount;
    float gravity;
    float x, y;
    bool running = true;
    
    Particlesystem particleSystem{};
    
    // Main application loop
    while (running) {
        window.beginFrame(); // Begin rendering frame

        const double t = window.time(); 
        const double dt = t - prevTime; // Time since last frame

        prevTime = t;

        // Clear screen with color
        window.clear({0, 0, 0, 1});

        // Draw particles
        particleSystem.update(dt * speed);
        particleSystem.draw(window, x, y, angle);

        // UI
        {
            window.beginGuiWindow("UI");
            window.text("I'm text!");
            window.sliderFloat("Speed", speed, 0.001f, 10.0f);
            window.sliderFloat("X", x, -1.0, 1.0);
            window.sliderFloat("Y", y, -1.0, 1.0);
            //Emitter
            
            //Directional
            window.sliderFloat("Angle:",angle,0.0, float(2*3.14));
            if (window.button("New directional emitter")) {
                       window.sliderFloat("Select angle, 0-2*pi", angle, 0.0f, float(2 * 3.14));
                       particleSystem.emitters.push_back(new Directional({x, y}, 10.0f, angle));
            }
            //Uniform
            if (window.button("New uniform emitter")) {
                particleSystem.emitters.push_back(new Uniform({x,y},10,10));
            }
            
            //Ang
            //Uniform
            if (window.button("Original emitter")) {
                particleSystem.emitters.push_back(new Org({x,y},10,10));
            }
            //Effects
            
            //Gravity
            window.sliderFloat("Select gravity", gravity, 0.0, 10);
            
            if (window.button("New Gravity effect")) {
                particleSystem.effects.push_back(new Gravity({x,y}, gravity));
            }
            //Wind
            
            if (window.button("New Wind effect")) {
                particleSystem.effects.push_back(new Wind({x,y}, gravity));
            }
            
            if (window.button("Close application")) {
                running = false;
            }
            window.endGuiWindow();
        }

        window.endFrame();
        running = running && !window.shouldClose();
    }

    return EXIT_SUCCESS;
} catch (const std::exception& e) {
    fmt::print("{}", e.what());
    return EXIT_FAILURE;
}


