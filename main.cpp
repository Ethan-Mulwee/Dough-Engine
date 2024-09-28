#include <iostream>
#include "dough/particle.hpp"
#include <raylib.h>


int main() {
    dough::Particle particle = dough::Particle(dough::Vector3(1,1,1), dough::Vector3(2,5,0), 0.999, 3);
    SetTargetFPS(60);
    InitWindow(800, 800, "test");
    while(!WindowShouldClose()) {
        //std::cout << particle.getPosition().x << std::endl;
        particle.integrate(0.1);
        Vector3 position = Vector3{particle.getPosition().x, particle.getPosition().y, particle.getPosition().z};
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(position.x, position.y, 6, WHITE);
        EndDrawing();
    }
    CloseWindow();
}