#include <iostream>
#include <raylib.h>
#include "dough/particle.hpp"

Camera camera = {0};

Vector3 Convert(dough::Vector3 Dvec) {
    return Vector3{Dvec.x, Dvec.y, Dvec.z};
}

int main() {
    dough::Particle particle = dough::Particle(dough::Vector3(0,0,0), dough::Vector3(0.0,2.0,-2.0), 0.999, 1);

    SetTargetFPS(60);
    InitWindow(800, 800, "test");

    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while(!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_PERSPECTIVE);
        //Gravity
        particle.addForce(dough::Vector3(0,-9.81,0)*particle.getMass());
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            particle.addForce((dough::Vector3(0,0,0)-particle.getPosition())*particle.getMass()*5);
        }
        Vector3 position = Vector3{particle.getPosition().x, particle.getPosition().y, particle.getPosition().z};
        BeginDrawing();
            BeginMode3D(camera);

            ClearBackground(WHITE);
            DrawCube(position, 1.0, 1.0, 1.0, RED);
            DrawCubeWires(position, 1.0, 1.0, 1.0, MAROON);
            DrawGrid(10, 1);
            Ray ray1 = {Convert(particle.getPosition()), Convert(particle.getVelocity())};
            Ray ray2 = {Convert(particle.getPosition()), Convert(particle.getAccumulatedForce())};
            DrawRay(ray1, RED);
            DrawRay(ray2, BLACK);
            EndMode3D();
        EndDrawing();
        particle.integrate((float)1/60);
    }
    CloseWindow();
}