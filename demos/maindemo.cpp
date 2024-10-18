#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include "dough/pworld.hpp"
#include "dough/body.hpp"
#include "raylib-dough.hpp"

using namespace RaytoDoh;

Camera camera = {0};



void DebugDisplay(dough::Particle particle) {
    dough::Vector3 position = particle.getPosition();
    dough::Vector3 velocity = particle.getVelocity();
    dough::Vector3 force = particle.getAccumulatedForce();
    std::string str1 =  "position: " + std::to_string(position.x) +", "+ std::to_string(position.y) +", "+ std::to_string(position.z);
    DrawText(str1.c_str(), 10, 10, 10, WHITE);
    std::string str2 =  "velocity: " + std::to_string(velocity.x) +", "+ std::to_string(velocity.y) +", "+ std::to_string(velocity.z);
    DrawText(str2.c_str(), 10, 20, 10, WHITE);
    std::string str3 =  "force: " + std::to_string(force.x) +", "+ std::to_string(force.y) +", "+ std::to_string(force.z);
    DrawText(str3.c_str(), 10, 30, 10, WHITE);
}

void VectorDisplay(dough::Particle particle) {
    if (particle.getInverseMass() == 0) return;
    Vector3 position = ConvertToRay(particle.getPosition());
    Vector3 velocity = ConvertToRay(particle.getVelocity());
    Vector3 force = ConvertToRay(particle.getAccumulatedForce()*0.1);
    DrawLine3D(position, Vector3Add(position, force), BLACK);
}

void CameraControl() {

}

dough::World world = dough::World(((float)1/60), -9.81, 100, 4, 1);

int main() {
    SetTargetFPS(60);
    InitWindow(1280, 720, "Phyiscs Demo");

    camera.position = (Vector3){ 12.0f, 12.0f, 12.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;


    Model model;

    model = LoadModelFromMesh(GenMeshCube(1,1,1));
    Matrix transform = MatrixMultiply(MatrixIdentity(), MatrixRotateX(PI/4));
    // Quaternion quaternion = Quaternion{1,2,3,4};
    // quaternion = QuaternionNormalize(quaternion);
    // dough::Quaternion dohQuaternion = dough::Quaternion(1,2,3,4);
    // dohQuaternion.normalise(); //fix that awful s
    // Matrix transform2 = QuaternionToMatrix(ConvertToRay(dohQuaternion));
    // model.transform = transform2;
    dough::RigidBody body;
    body.setInverseMass(3);
    body.setOrientation(dough::Quaternion(1,2,3,4));

    while(!WindowShouldClose()) {
        // Ray ray = GetScreenToWorldRay(GetMousePosition(), camera);
        // RayCollision collision = GetRayCollisionMesh(ray, model.meshes[0], transform2);
        // RayCollision collision2 = GetRayCollisionQuad(ray, Vector3{-1000,0,-1000}, Vector3{-1000,0,1000}, Vector3{1000,0,1000}, Vector3{1000,0,-1000});
        body.addForce(dough::Vector3(0,-4,4));
        body.integrate(0.1);
        UpdateCamera(&camera, CAMERA_PERSPECTIVE);
        BeginDrawing();
            ClearBackground(Color{35, 35, 35, 255});
            BeginMode3D(camera);
            DrawGrid(10, 2);
            model.transform = QuaternionToMatrix(ConvertToRay(body.getOrientation()));
            DrawModel(model, ConvertToRay(body.getPosition()), 1, WHITE);
            EndMode3D();
        EndDrawing();
        world.step();
    }
    CloseWindow();
}
