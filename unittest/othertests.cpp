#include "particlesystem.h"
#include "particles.h"
#include "emitter.h"
#include <catch2/catch_all.hpp>
#include <glm/glm.hpp>

// Unit test
// Constructorn
TEST_CASE("Uniform Emitter") {

Uniform u({0,0}, 5, 1);
    
}

// Kollar om partikelsystemet tar bort partiklar efter bestämd lifetime
TEST_CASE("Particles have finite lifetime", "[particles]") {

    Particlesystem ps;

    Particles myParticles(glm::vec2(0, 0), glm::vec2(0, 0), 1.0f, glm::vec4(1, 1, 1, 1));
    myParticles.lifetime = 1;

    ps.particles.push_back(myParticles);

    float dt = float(0.1); //tidssteg

    for (int i = 0; i < 10; i++) {
        ps.update(dt);
    }

    for (auto& p : ps.particles) {
        REQUIRE(p.lifetime < 3.0f); //Tröskelvärde
    }
}

TEST_CASE("New particles are added with orginal properties", "[emitter]") {
    //Given
    Org u({0, 0}, 10, 5);
    
    std::vector<Particles> particles; //Tom vektor
    
    WHEN("createNewParticles is called with an amount of u") {
        u.createNewParticles(particles);
        
        // Kollar att det angivna amount stämmer
        THEN("particles are added with expected properties") {
            REQUIRE(particles.size() == u.amount);

            for (const auto& particle : particles) {
                REQUIRE(particle.color.r == Catch::Approx(0.6));
                REQUIRE(particle.color.g == Catch::Approx(1.0));
                REQUIRE(particle.color.b == Catch::Approx(0.4));
                REQUIRE(particle.color.a == Catch::Approx(1.0));

                REQUIRE(particle.radius == Catch::Approx(10));

                
                REQUIRE(particle.velocity.x == Catch::Approx(cos(1/u.amount)));
                REQUIRE(particle.velocity.y == Catch::Approx(sin(1/u.amount)));
            }
        }
    }
}





