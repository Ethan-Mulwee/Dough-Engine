#include <iostream>
#include <raylib.h>
#include "dough/particle.hpp"

Camera camera = {0};

int main() {
    dough::Particle particle = dough::Particle(dough::Vector3(0,0,0), dough::Vector3(0.0,2.0,-2.0), 0.999, 3);

    SetTargetFPS(60);
    InitWindow(800, 800, "test");

    camera.position = (Vector3){ 10.0f, 0.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while(!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_PERSPECTIVE);
        particle.setAcceleration(dough::Vector3(0,-2,0));
        particle.integrate((float)1/60);
        particle.clearAcceleration();
        Vector3 position = Vector3{particle.getPosition().x, particle.getPosition().y, particle.getPosition().z};
        BeginDrawing();
            BeginMode3D(camera);

            ClearBackground(BLACK);
            DrawSphere(position, 0.5, WHITE);
            EndMode3D();
        EndDrawing();
    }
    CloseWindow();
}