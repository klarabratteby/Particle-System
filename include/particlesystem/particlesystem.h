#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <rendering/window.h>
#include "particlesystem.h"
#include "particles.h"
#include "effects.h"
#include "emitter.h"

class Particlesystem {
    public :
    // Constructor, fills window with particles
    Particlesystem() {
        //Test
        //emitters.push_back(new Directional({0,0},10,10));
        // for (int i = 0; i < 50; i++) {
            // particles.push_back(Particle{0,0}, {.1,.1}, 30, {1,0,0,1})));
        //}
        
        //effects.push_back(new Gravity({0,1},10,10));
        
    }
    void update(float dt) {
        // Remove dead particles
        for(int i = 0; i < particles.size(); ++i) {
            if(!particles[i].alive()) {
                particles.erase(particles.begin() + i);
            }
        }
        // Update particle positions
        for(Particles& p : particles ) {
            p.update(dt);
        }
        
        // Update emitters and create new particles
        for(Emitter* e : emitters) {
            if(e->update(dt)) {
                e->createNewParticles(particles);
            }
        }
        // Apply effects to particles
        for(Effects* e : effects) {
            e->affectParticles(particles);
        }
    }
    // Draw particles, emitters, and effects
    void draw(rendering::Window& window, float x, float y, float angle) {
        
        window.drawPoint({x, y}, 20, {1, 1, 1, 1});
        
        window.drawPoint({x + 0.04* cos(angle), y + 0.04 * sin(angle)}, 15, {1, 1, 1, 1});
        
        for(const Particles& p : particles ) {
            window.drawPoint(p.position, p.radius, p.color);
        }
        for(Emitter* e : emitters ) {
            window.drawPoint(e->position, e->radius, e->color);
        }
        for(Effects* e : effects ) {
            window.drawPoint(e->position, e->radius, e->color);
        }
    }
    
    std::vector<Particles> particles; // Holds instances of Particle class
    std::vector<Emitter*> emitters;  // Holds pointers to instances of classes derived from Emitter (abstract class)
    std::vector<Effects*> effects; // Holds pointers to instances of classes derived from Effects (abstract class)
    
};
