#pragma once

#include "particles.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include <vector>
#include <cmath>

class Effects {
    
    public :
    // Constructor
    Effects(glm::vec2 _position, float _radius, float _velocity, glm::vec4 _color) {
        position = _position;
        radius = _radius;
        velocity = _velocity;
        color = _color;
    }

    
    virtual void affectParticles(std::vector<Particles>& particles) = 0 ;
    glm::vec2 position;
    glm::vec4 color;
    float radius;
    
    // Only accessible by Wind and Gravity
    protected:
    float velocity;

};

class Wind : public Effects {
    
    public :
    // Constructor
    Wind(glm::vec2 _position, float _strength): Effects(_position, 5, _strength, {0, 0, 1, 1}) {
        
    };
    
    void affectParticles(std::vector<Particles>& particles) override {
    
        //float differanceX, differanceY;
               
               for(size_t i = 0; i < particles.size(); i++) {
                   
                    // Stronger wind the further away from the position
                       particles[i].velocity.x -= velocity * 0.01f;
                       particles[i].velocity.y -= velocity * 0.01f;
               }
            
    }
};

class Gravity : public Effects {
    public :
    // Constructor
    Gravity(glm::vec2 _position, float _gravity): Effects(_position, 10, _gravity, {0, 1, 1, 1}) {
        
    };
    
    void affectParticles(std::vector<Particles>& particles) override {
        
        for(size_t i = 0; i < particles.size(); i++){
            // Pythagoras for visualization
            float distance = sqrt(pow(position.x - particles[i].position.x, 2) + pow(position.y - particles[i].position.y, 2));
            // Calculate angle using two sides of the triangle, to consider only the diagonal. Distance = hypotenuse
            float angle = acos((position.x - particles[i].position.x)/distance);
            // If the angle is on the negative side, move it to the positive side
            if(position.y < particles[i].position.y)
                angle *= -1;
            
            // Formula for gravity, depending on the force * angle. Attracted to the "black hole".
            particles[i].velocity.x += velocity * cos(angle) * pow(distance,2) * 0.01;
            particles[i].velocity.y += velocity * sin(angle) * pow(distance,2) * 0.01;
            
        }
    }
   
    private:
    
};

