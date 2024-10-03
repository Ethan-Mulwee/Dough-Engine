#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include "simulation.hpp"

Camera camera = {0};

Vector3 ConvertRay(dough::Vector3 Dvec) {
    return Vector3{Dvec.x, Dvec.y, Dvec.z};
}

dough::Vector3 ConvertDough(Vector3 Rvec) {
    return dough::Vector3(Rvec.x, Rvec.y, Rvec.z);
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

void VectorDisplay(dough::Particle particle) {
    Vector3 position = ConvertRay(particle.getPosition());
    Vector3 velocity = ConvertRay(particle.getVelocity());
    Vector3 force = ConvertRay(particle.getAccumulatedForce()*0.1);
    DrawLine3D(position, Vector3Add(position, force), BLACK);
}

void CameraControl() {

}

World world = World(((float)1/60), -9.81, 100, 4);

int main() {
    SetTargetFPS(60);
    InitWindow(1280/2, 720/2, "Phyiscs Demo");

    camera.position = (Vector3){ 12.0f, 12.0f, 12.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while(!WindowShouldClose()) {
        Ray ray = GetScreenToWorldRay(GetMousePosition(), camera);
        RayCollision collision = GetRayCollisionQuad(ray, Vector3{-1000,0,-1000}, Vector3{-1000,0,1000}, Vector3{1000,0,1000}, Vector3{1000,0,-1000});
        UpdateCamera(&camera, CAMERA_PERSPECTIVE);
        world.updateForces();
        auto j = world.particles.begin();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            for (; j != world.particles.end(); j++) {
                dough::Vector3 point = ConvertDough(collision.point);
                j->addForce((point-j->getPosition())); //*mass to get equal acceleration on all particles
            }
        }
        BeginDrawing();
            ClearBackground(Color{35, 35, 35, 255});
            BeginMode3D(camera);
            DrawGrid(10, 2);
            DrawSphere(collision.point, 0.5, WHITE);
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
                DrawSphere(ConvertRay(i->getPosition()), 0.5, color); //(i->getMass())/10
                VectorDisplay(*i.base());
                count++;
            }
            EndMode3D();
        EndDrawing();
        world.checkCollisions();
        world.step();
    }
    CloseWindow();
}
