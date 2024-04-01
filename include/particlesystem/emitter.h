#pragma once

#include <cmath>
#include <vector>
#include <glm/glm.hpp>



class Emitter {
   
    public :
    // Constructor
    Emitter(glm::vec2 _position, float _radius, float _delay, glm::vec4 _color)  {
        position = _position;
        radius = _radius;
        delay = _delay;
        color = _color;
    }
    // Same for all emitters, time-dependent.
    // dt = time since the last frame
    bool update(float dt) {
        time += dt;
        if (time > delay) {
            time = 0; // reset if time exceeds delay
            return true;
            
        }
        return false;
    }
        
    virtual void createNewParticles(std::vector<Particles>& particles)  = 0;
    glm::vec2 position;
    float radius;
    glm::vec4 color;
    
    private :
    float time= 0, delay;
   
};

class Directional : public Emitter {
    
    public:
    // Constructor
    Directional(glm::vec2 _position, float _size, float _angle):
    Emitter(_position,_size, .1, {1, 0, 0, 1}), angle(_angle) {
        
    };
       
    void createNewParticles(std::vector<Particles>& particles) override {
        particles.push_back(Particles(position, {cos(angle), sin(angle)}, radius, {1, 0, 0, 1}));
            
    }
    private :
    float angle;
};

class Uniform : public Emitter {
    
    public:
    // Constructor
    Uniform(glm::vec2 _position, float _size, int _amount) :
    Emitter(_position, _size, 1, {1, 0, 1, 1}),amount(_amount) {
        
    };
        
    void createNewParticles(std::vector<Particles>& particles) override {
    for (int i = 0; i < amount; ++i) {
        float angle = i * 2 * 3.14/amount; // Full circle
            particles.push_back(Particles(position, {cos(angle), sin(angle)}, radius, {.6,1,.4,1}));
          }
            
    }
    private :
    int amount;
    
};

class Org : public Emitter {
    public:
    //Constructor
    Org(glm::vec2 _position, float _size, int _amount) :
    Emitter(_position, _size, 1, {1, 0, 1, 1}),amount(_amount) {
    
    };
    
    void createNewParticles(std::vector<Particles>& particles) override {
      
    for (int i = 0; i < amount; ++i) {
        float ang = 1/amount;  // Full circle
            particles.push_back(Particles(position, {cos(ang), sin(ang)}, 10, {.6,1,.4,1}));
    }
        
    }

    int amount;

};





