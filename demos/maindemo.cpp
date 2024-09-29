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

World world = World(0.0025, -9.81);

int main() {

    SetTargetFPS(200);
    InitWindow(1920, 1080, "Phyiscs Demo");

    camera.position = (Vector3){ 12.0f, 12.0f, 12.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while(!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        BeginDrawing();
            BeginMode3D(camera);

            ClearBackground(Color{35, 35, 35, 255});
            int count = 0;
            auto i = world.particles.begin();
            for (; i != world.particles.end(); i++) {
                Color color;
                switch (count % 4)
                {
                    case 0:
                    color = RED; break;
                    case 1:
                    color = BLUE; break;
                    case 2:
                    color = PURPLE; break;
                    case 3:
                    color = ORANGE; break;
                }
                DrawSphere(Convert(i->getPosition()), (i->getMass())/10, color);
                count++;
            }
            DrawGrid(10, 2);
            DrawSphere(Vector3{0,0,0}, 0.1, BLACK);
            EndMode3D();
        EndDrawing();
        world.step();
    }
    CloseWindow();
}