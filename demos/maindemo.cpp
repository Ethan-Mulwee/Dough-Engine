#include <iostream>
#include <raylib.h>
#include <string>
#include "simulation.hpp"

Camera camera = {0};


Vector3 Convert(dough::Vector3 Dvec) {
    return Vector3{Dvec.x, Dvec.y, Dvec.z};
}

void DebugDisplay(dough::Particle particle) {
    dough::Vector3 position = particle.getPosition();
    dough::Vector3 velocity = particle.getVelocity();
    dough::Vector3 force = particle.getAccumulatedForce();
    std::string str1 =  "position: " + std::to_string(position.x) +", "+ std::to_string(position.y) +", "+ std::to_string(position.z);
    DrawText(str1.c_str(), 10, 10, 10, BLACK);
    std::string str2 =  "velocity: " + std::to_string(velocity.x) +", "+ std::to_string(velocity.y) +", "+ std::to_string(velocity.z);
    DrawText(str2.c_str(), 10, 20, 10, BLACK);
    std::string str3 =  "force: " + std::to_string(force.x) +", "+ std::to_string(force.y) +", "+ std::to_string(force.z);
    DrawText(str3.c_str(), 10, 30, 10, BLACK);
}

void CameraControl() {

}

World world = World(0.005, -9.81);

int main() {

    SetTargetFPS(200);
    InitWindow(1920, 1080, "Phyiscs Demo");

    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while(!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_PERSPECTIVE);
        //forceGenRegist.updateForces((float)1/60);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            world.a.addForce((dough::Vector3(0,0,0)-world.a.getPosition())*world.a.getMass()*5);
        }
        Vector3 position = Vector3{world.a.getPosition().x, world.a.getPosition().y, world.a.getPosition().z};
        BeginDrawing();
            BeginMode3D(camera);

            ClearBackground(WHITE);
            DrawSphere(position, 0.5, RED);
            DrawSphere(Convert(world.b.getPosition()), 0.5, BLUE);
            DrawGrid(1000, 1);
            DrawLine3D(Convert(world.a.getPosition()), Convert(world.a.getVelocity()+world.a.getPosition()), RED);
            DrawLine3D(Convert(world.a.getPosition()), Convert(world.a.getAccumulatedForce()+world.a.getPosition()), BLACK);
            DrawSphere(Vector3{0,0,0}, 0.2, BLACK);
            EndMode3D();
            DebugDisplay(world.a);
        EndDrawing();
        world.step();
    }
    CloseWindow();
}