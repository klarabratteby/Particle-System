#pragma once
#include <glm/glm.hpp>

class Particles {
    public :
    
    Particles(glm::vec2 _position, glm::vec2 _velocity, float _radius,glm::vec4 _color) : position(_position), velocity(_velocity), radius(_radius), color(_color) {
        
    }
    void update(float dt) {
        
        lifetime += dt;
        position += velocity * dt;
    }
    
    bool alive() {
        if(lifetime >= 5) {
            return false;
        }
        // Screen coordinates range from -1 to 1
        else if (position.x > 1 || position.x < -1 || position.y > 1 || position.y < -1)
            return false;
        
        return true;
    }
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec4 color;
    
    float lifetime = 0;
    float radius;

};



