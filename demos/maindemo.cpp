#include <iostream>
#include <raylib.h>
#include <string>
#include "dough/pfgen.hpp"

Camera camera = {0};
//dough::ParticleForceRegistry forceGenRegist;
//dough::ParticleGravity gravityFG = dough::ParticleGravity(dough::Vector3(0,-9.81,0));

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

int main() {
    dough::Particle particle = dough::Particle(dough::Vector3(0,0,0), dough::Vector3(0.0,2.0,-2.0), 0.999, 1);
    particle.setAcceleration(dough::Vector3(0,-9.81,0));
    //forceGenRegist.add(&particle, &gravityFG);

    SetTargetFPS(60);
    InitWindow(1920, 1080, "Phyiscs Demo");

    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while(!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_PERSPECTIVE);
        //Gravity
        // particle.addForce(dough::Vector3(0,-9.81,0)*particle.getMass());
        //forceGenRegist.updateForces((float)1/60);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            particle.addForce((dough::Vector3(0,0,0)-particle.getPosition())*particle.getMass()*5);
        }
        Vector3 position = Vector3{particle.getPosition().x, particle.getPosition().y, particle.getPosition().z};
        BeginDrawing();
            BeginMode3D(camera);

            ClearBackground(WHITE);
            DrawSphere(position, 0.5, RED);
            DrawGrid(1000, 1);
            Ray ray1 = {Convert(particle.getPosition()), Convert(particle.getVelocity())};
            DrawLine3D(Convert(particle.getPosition()), Convert(particle.getVelocity()+particle.getPosition()), RED);
            DrawLine3D(Convert(particle.getPosition()), Convert(particle.getAccumulatedForce()+particle.getPosition()), BLACK);
            DrawSphere(Vector3{0,0,0}, 0.2, BLACK);
            EndMode3D();
            DebugDisplay(particle);
        EndDrawing();
        particle.integrate((float)1/60);
    }
    CloseWindow();
}