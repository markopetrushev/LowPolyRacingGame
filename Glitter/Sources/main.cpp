// Local Headers
#include "glitter.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "model.hpp"
#include "physics.hpp"
#include <FileSystem.h>

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Headers
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;
const char *APP_NAME = "Low_poly_racing_game";

// General callback functions
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

unsigned int loadCubeMap();

// Camera controls
Camera camera(glm::vec3(0.0f, 2.5f, 8.0f), GL_FALSE);
bool cameraFollow = TRUE;
glm::vec3 cameraFollowPos(0.0f);
float cameraFollowP = 0.0f, cameraFollowY = 0.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = TRUE;
bool rotating = FALSE;
float cameraRadius = 8.0f;
bool switched = FALSE;

// Car controls
short acceleration = 0;
float steering = 0.0f;
bool handbrake = FALSE;
float maxAcceleration = 800.0f;     // engine torque
float maxVelocity = 50.0f;          // engine speed limit
bool getUp = FALSE, gotUp = FALSE;
bool jump = FALSE, jumped = FALSE;
float basePitch = 0.0f, baseYaw = 0.0f;

// Car properties
float car_mass = 1250.0f;
float tyre_mass_1 = 15.0f;          // front wheels weight
float tyre_mass_2 = 20.0f;          // rear wheels weight
float tyre_friction = 2.25f;
float tyre_stiffness = 120000.0f;   // suspension travel
float tyre_damping = 0.0000200f;    // suspension oscillation
float tyre_steering_angle = 0.5f;
float assist = 0.5f;
float lowLim = 0.0f;
float upLim = 0.1f;
const float cLinDamp = 0.02f;
const float cAngDamp = 0.4f;
const float tLinDamp = 0.01f;
const float tAngDamp = 0.2f;

// Car components
btRigidBody *car, *t1, *t2, *t3, *t4;
btGeneric6DofSpringConstraint *c1, *c2, *c3, *c4;

// Delta time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {

    // Setup OpenGL environment
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, APP_NAME, NULL, NULL);
    if (window == NULL) {
        std::cout << "ERROR: failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "ERROR: failed to initialise GLAD" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Our game
    glm::vec3 lightPos(0.0, 2.0, -1.0);

    // Car
    Shader mShader("D:\\Glitter\\Glitter\\Shaders\\car.vert",
                   "D:\\Glitter\\Glitter\\Shaders\\car.frag");
    Model mModel((char *) "D:\\Glitter\\Glitter\\Sources\\Modeli\\car\\car.obj");
    Model t1Model((char *) "D:\\Glitter\\Glitter\\Sources\\Modeli\\car\\tyref.obj");
    Model t2Model((char *) "D:\\Glitter\\Glitter\\Sources\\Modeli\\car\\tyreb.obj");

    // Terrain
    Shader tShader("D:\\Glitter\\Glitter\\Shaders\\terrain.vert",
                   "D:\\Glitter\\Glitter\\Shaders\\terrain.frag");
    Model tModel0((char *) "D:\\Glitter\\Glitter\\Sources\\Modeli\\terrain\\grass.obj");
    Model tModel1((char *) "D:\\Glitter\\Glitter\\Sources\\Modeli\\terrain\\asphalt.obj");

    // Skybox
    Shader sShader("D:\\Glitter\\Glitter\\Shaders\\skybox.vert",
                   "D:\\Glitter\\Glitter\\Shaders\\skybox.frag");
    float skyboxVertices[] = {
            // positions
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
    };
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    unsigned int cubemapTexture = loadCubeMap();

    // Physics simulation
    Physics simulation;

    maxAcceleration = 500.0f;
    maxVelocity = 50.0f;

    car_mass = 1250.0f;
    tyre_mass_1 = 20.0f;
    tyre_mass_2 = 25.0f;
    tyre_friction = 2.35f;
    tyre_stiffness = 100000.0f;
    tyre_damping = 0.0000250f;   // 0.0000250 is stable
    tyre_steering_angle = 0.5f;
    lowLim = 0.0f;
    upLim = 0.1f;

    // Terrain
    const unsigned int grid_width = 5;
    const unsigned int grid_height = 8;
    const unsigned int tiles = grid_width * grid_height;
    const unsigned int track[grid_height][grid_width] = {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0}
    };
    btRigidBody *plane[tiles];
    glm::vec3 plane_pos[tiles];
    glm::vec3 plane_size[tiles];
    const float plane_edge = 20.0f;

    for (unsigned int i = 0; i < grid_width; i++) {
        for (unsigned int j = 0; j < grid_height; j++) {
            plane_pos[i * (grid_height) + j] = glm::vec3(2 * plane_edge * i - plane_edge * (grid_width - 1),
                                                         -0.0f * (i * (grid_height) + j),
                                                         2 * plane_edge * j - plane_edge * (grid_height - 1));
            plane_size[i * (grid_height) + j] = glm::vec3(plane_edge, 0.0f, plane_edge);
            glm::vec3 plane_rot = glm::vec3(0.0f, 0.0f, 0.0f);

            if (track[j][i] == 0) {
                // Grass
                plane[i * (grid_height) + j] = simulation.createRigidBody(BOX, plane_pos[i * (grid_height) + j],
                                                                          plane_size[i * (grid_height) + j], plane_rot,
                                                                          0.0f, 0.25f, 0.25f, COLL_TERRAIN,
                                                                          COLL_EVERYTHING);
            } else if (track[j][i] == 1) {
                // Asphalt
                plane[i * (grid_height) + j] = simulation.createRigidBody(BOX, plane_pos[i * (grid_height) + j] +
                                                                               glm::vec3(0.0f, 0.05f, 0.0f),
                                                                          plane_size[i * (grid_height) + j] +
                                                                          glm::vec3(0.0f, 0.05f, 0.0f), plane_rot, 0.0f,
                                                                          0.5f, 0.5f, COLL_TERRAIN, COLL_EVERYTHING);
            }

        }
    }

    // Invisible walls
    const unsigned int walls = 4;
    float side;
    glm::vec3 wall_pos;
    glm::vec3 wall_size;
    btRigidBody *wall;

    side = plane_edge * grid_height;
    wall_size = glm::vec3(2 * side, 5.0f, 0.0f);

    wall_pos = glm::vec3(0.0f, 2.5f, -side);
    wall = simulation.createRigidBody(BOX, wall_pos, wall_size, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f,
                                      COLL_TERRAIN, COLL_EVERYTHING);
    wall_pos = glm::vec3(0.0f, 2.5f, side);
    wall = simulation.createRigidBody(BOX, wall_pos, wall_size, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f,
                                      COLL_TERRAIN, COLL_EVERYTHING);

    side = plane_edge * grid_width;
    wall_size = glm::vec3(0.0f, 5.0f, 2 * side);

    wall_pos = glm::vec3(-side, 2.5f, 0.0f);
    wall = simulation.createRigidBody(BOX, wall_pos, wall_size, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f,
                                      COLL_TERRAIN, COLL_EVERYTHING);
    wall_pos = glm::vec3(side, 2.5f, 0.0f);
    wall = simulation.createRigidBody(BOX, wall_pos, wall_size, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f,
                                      COLL_TERRAIN, COLL_EVERYTHING);

    // Camaro
    glm::vec3 spawn = glm::vec3(-40.0f, 0.0f, 0.0f);  // start position in world

    glm::vec3 car_pos = glm::vec3(0.0f, 1.0f, 0.0f) + spawn;
    glm::vec3 car_size = glm::vec3(1.0f, 0.6f, 3.0f);
    glm::vec3 car_rot = glm::vec3(0.0f, 0.0f, 0.0f);
    car = simulation.createRigidBody(BOX, car_pos, car_size, car_rot, car_mass, 1.75f, 0.2f, COLL_CHASSIS,
                                     COLL_EVERYTHING ^ COLL_CAR);
    car->setSleepingThresholds(0.0, 0.0);   // never stop simulating
    car->setDamping(cLinDamp * assist, cAngDamp * assist);

    btTransform frameA, frameB;

    glm::vec3 t1_pos = glm::vec3(-1.0f, 0.5f, -2.1f) + spawn;
    glm::vec3 t1_size = glm::vec3(0.4f, 0.35f, 0.35f);
    glm::vec3 t1_rot = glm::vec3(0.0f, 0.0f, glm::radians(-90.0f));
    t1 = simulation.createRigidBody(CYLINDER, t1_pos, t1_size, t1_rot, tyre_mass_1, tyre_friction, 0.0f, COLL_TYRE,
                                    COLL_EVERYTHING ^ COLL_CAR);
    t1->setSleepingThresholds(0.0, 0.0);    // never stop simulating
    t1->setDamping(tLinDamp * assist, tAngDamp * assist);
    frameA = btTransform::getIdentity();
    frameB = btTransform::getIdentity();
    frameA.getBasis().setEulerZYX(0, 0, 0);
    frameB.getBasis().setEulerZYX(0, 0, glm::radians(90.0f));
    frameA.setOrigin(btVector3(-1.0, -0.5, -2.1));
    frameB.setOrigin(btVector3(0.0, 0.0, 0.0));
    c1 = new btGeneric6DofSpringConstraint(*car, *t1, frameA, frameB, TRUE);
    c1->setLinearLowerLimit(btVector3(0, -lowLim, 0));
    c1->setLinearUpperLimit(btVector3(0, -upLim, 0));
    c1->setAngularLowerLimit(btVector3(1, -0.5, 0));
    c1->setAngularUpperLimit(btVector3(-1, 0.5, 0));
    c1->enableSpring(1, TRUE);
    c1->setStiffness(1, tyre_stiffness);
    c1->setDamping(1, tyre_damping);
    c1->setEquilibriumPoint();

    glm::vec3 t2_pos = glm::vec3(1.0f, 0.5f, -2.1f) + spawn;
    glm::vec3 t2_size = glm::vec3(0.4f, 0.35f, 0.35f);
    glm::vec3 t2_rot = glm::vec3(0.0f, 0.0f, glm::radians(90.0f));
    t2 = simulation.createRigidBody(CYLINDER, t2_pos, t2_size, t2_rot, tyre_mass_1, tyre_friction, 0.0f, COLL_TYRE,
                                    COLL_EVERYTHING ^ COLL_CAR);
    t2->setSleepingThresholds(0.0, 0.0);
    t2->setDamping(tLinDamp * assist, tAngDamp * assist);
    frameA = btTransform::getIdentity();
    frameB = btTransform::getIdentity();
    frameA.getBasis().setEulerZYX(0, 0, 0);
    frameB.getBasis().setEulerZYX(0, 0, glm::radians(-90.0f));
    frameA.setOrigin(btVector3(1.0, -0.5, -2.1));
    frameB.setOrigin(btVector3(0.0, 0.0, 0.0));
    c2 = new btGeneric6DofSpringConstraint(*car, *t2, frameA, frameB, TRUE);
    c2->setLinearLowerLimit(btVector3(0, -lowLim, 0));
    c2->setLinearUpperLimit(btVector3(0, -upLim, 0));
    c2->setAngularLowerLimit(btVector3(1, -0.5, 0));
    c2->setAngularUpperLimit(btVector3(-1, 0.5, 0));
    c2->enableSpring(1, TRUE);
    c2->setStiffness(1, tyre_stiffness);
    c2->setDamping(1, tyre_damping);
    c2->setEquilibriumPoint();

    glm::vec3 t3_pos = glm::vec3(-1.0f, 0.5f, 1.6f) + spawn;
    glm::vec3 t3_size = glm::vec3(0.45f, 0.4f, 0.4f);
    glm::vec3 t3_rot = glm::vec3(0.0f, 0.0f, glm::radians(-90.0f));
    t3 = simulation.createRigidBody(CYLINDER, t3_pos, t3_size, t3_rot, tyre_mass_2, tyre_friction, 0.0f, COLL_TYRE,
                                    COLL_EVERYTHING ^ COLL_CAR);
    t3->setSleepingThresholds(0.0, 0.0);
    t3->setDamping(tLinDamp * assist, tAngDamp * assist);
    frameA = btTransform::getIdentity();
    frameB = btTransform::getIdentity();
    frameA.getBasis().setEulerZYX(0, 0, 0);
    frameB.getBasis().setEulerZYX(0, 0, glm::radians(90.0f));
    frameA.setOrigin(btVector3(-1.0, -0.5, 1.6));
    frameB.setOrigin(btVector3(0.0, 0.0, 0.0));
    c3 = new btGeneric6DofSpringConstraint(*car, *t3, frameA, frameB, TRUE);
    c3->setLinearLowerLimit(btVector3(0, -lowLim, 0));
    c3->setLinearUpperLimit(btVector3(0, -upLim, 0));
    c3->setAngularLowerLimit(btVector3(1, 0, 0));
    c3->setAngularUpperLimit(btVector3(-1, 0, 0));
    c3->enableSpring(1, TRUE);
    c3->setStiffness(1, tyre_stiffness);
    c3->setDamping(1, tyre_damping);
    c3->setEquilibriumPoint();

    glm::vec3 t4_pos = glm::vec3(1.0f, 0.5f, 1.6f) + spawn;
    glm::vec3 t4_size = glm::vec3(0.45f, 0.4f, 0.4f);
    glm::vec3 t4_rot = glm::vec3(0.0f, 0.0f, glm::radians(90.0f));
    t4 = simulation.createRigidBody(CYLINDER, t4_pos, t4_size, t4_rot, tyre_mass_2, tyre_friction, 0.0f, COLL_TYRE,
                                    COLL_EVERYTHING ^ COLL_CAR);
    t4->setSleepingThresholds(0.0, 0.0);
    t4->setDamping(tLinDamp * assist, tAngDamp * assist);
    frameA = btTransform::getIdentity();
    frameB = btTransform::getIdentity();
    frameA.getBasis().setEulerZYX(0, 0, 0);
    frameB.getBasis().setEulerZYX(0, 0, glm::radians(-90.0f));
    frameA.setOrigin(btVector3(1.0, -0.5, 1.6));
    frameB.setOrigin(btVector3(0.0, 0.0, 0.0));
    c4 = new btGeneric6DofSpringConstraint(*car, *t4, frameA, frameB, TRUE);
    c4->setLinearLowerLimit(btVector3(0, -lowLim, 0));
    c4->setLinearUpperLimit(btVector3(0, -upLim, 0));
    c4->setAngularLowerLimit(btVector3(1, 0, 0));
    c4->setAngularUpperLimit(btVector3(-1, 0, 0));
    c4->enableSpring(1, TRUE);
    c4->setStiffness(1, tyre_stiffness);
    c4->setDamping(1, tyre_damping);
    c4->setEquilibriumPoint();

    simulation.dynamicsWorld->addConstraint(c1);
    simulation.dynamicsWorld->addConstraint(c2);
    simulation.dynamicsWorld->addConstraint(c3);
    simulation.dynamicsWorld->addConstraint(c4);

    GLfloat maxSecPerFrame = 1.0f / 50.0f;


    // Game loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);

        btMatrix3x3 rot = car->getWorldTransform().getBasis();
        short braking = 1;

        // Acceleration
        float linearVelocity = car->getLinearVelocity().length();
        if (acceleration < 0 && linearVelocity > maxVelocity / 10) {
            braking = 0;
        } else {
            if (linearVelocity < maxVelocity / (1 + 9 * (acceleration < 0))) {
                float torque = -maxAcceleration * acceleration * (1 - (abs(steering) * (linearVelocity > 10)) / 2);
                t1->applyTorque(rot * btVector3(torque, 0, 0));
                t2->applyTorque(rot * btVector3(torque, 0, 0));
                if (!handbrake) {
                    t3->applyTorque(rot * btVector3(torque, 0, 0));
                    t4->applyTorque(rot * btVector3(torque, 0, 0));
                }
            }
        }

        // Braking / steering
        c1->setAngularLowerLimit(btVector3(braking, tyre_steering_angle * steering, 0));
        c1->setAngularUpperLimit(btVector3(-braking, tyre_steering_angle * steering, 0));
        c2->setAngularLowerLimit(btVector3(braking, tyre_steering_angle * steering, 0));
        c2->setAngularUpperLimit(btVector3(-braking, tyre_steering_angle * steering, 0));

        // Handbrake
        if (handbrake) {
            c3->setAngularLowerLimit(btVector3(0, 0, 0));
            c3->setAngularUpperLimit(btVector3(0, 0, 0));
            c4->setAngularLowerLimit(btVector3(0, 0, 0));
            c4->setAngularUpperLimit(btVector3(0, 0, 0));
        } else {
            c3->setAngularLowerLimit(btVector3(braking, 0, 0));
            c3->setAngularUpperLimit(btVector3(-braking, 0, 0));
            c4->setAngularLowerLimit(btVector3(braking, 0, 0));
            c4->setAngularUpperLimit(btVector3(-braking, 0, 0));
        }


        // Reset
        if (getUp) {
            car->applyTorqueImpulse(rot * btVector3(0, 0, 12000));
        }

        // Jump
        if (jump) {
            car->applyCentralImpulse(btVector3(0, 10000, 0));
        }

        // Step physics forward
        simulation.dynamicsWorld->stepSimulation((deltaTime < maxSecPerFrame ? deltaTime : maxSecPerFrame), 10);

        // Update camera position
        if (cameraFollow) {
            btTransform temp;
            btVector3 newPos;

            car->getMotionState()->getWorldTransform(temp);
            float aVelocity = -car->getAngularVelocity().y();
            newPos = temp.getBasis() * btVector3(
                    glm::cos(glm::radians(-10 * glm::sqrt(glm::abs(steering)) * aVelocity + 90 + baseYaw / 4)) *
                    cameraRadius, 0,
                    glm::sin(glm::radians(-10 * glm::sqrt(glm::abs(steering)) * aVelocity + 90 + baseYaw / 4)) *
                    cameraRadius);

            cameraFollowPos.x = temp.getOrigin().getX() + newPos.x();
            cameraFollowPos.y = temp.getOrigin().getY() - glm::sin(glm::radians(camera.Pitch)) * cameraRadius + 1.5;
            cameraFollowPos.z = temp.getOrigin().getZ() + newPos.z();

            camera.Position = cameraFollowPos;
            camera.LookAt(-newPos.x(), newPos.y(), -newPos.z());
        }

        // Transforms
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 10000.0f);
        glm::mat4 view = camera.GetViewMatrix();

        // Terrain
        tShader.Use();
        tShader.setMat4("projection", projection);
        tShader.setMat4("view", view);
        tShader.setVec3("viewPos", camera.Position);

        tShader.setVec3("light.direction", 1.0f, -0.5f, -0.5f);
        tShader.setVec3("light.ambient", 0.473f, 0.428f, 0.322f);

        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 planeModelMatrix = glm::mat4(1.0f);
        for (unsigned int i = 0; i < grid_width; i++) {
            for (unsigned int j = 0; j < grid_height; j++) {
                planeModelMatrix = glm::translate(planeModelMatrix, plane_pos[i * (grid_height) + j]);
                glUniformMatrix4fv(glGetUniformLocation(tShader.Program, "model"), 1, GL_FALSE,
                                   glm::value_ptr(planeModelMatrix));

                if (track[j][i] == 0) {
                    // Grass
                    tShader.setFloat("material.shininess", 4.0f);
                    tShader.setVec3("light.diffuse", 1.195f, 1.105f, 0.893f);
                    tShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
                    tModel0.Draw(tShader);
                } else if (track[j][i] == 1) {
                    // Asphalt
                    tShader.setFloat("material.shininess", 16.0f);
                    tShader.setVec3("light.diffuse", 0.945f, 0.855f, 0.643f);
                    tShader.setVec3("light.specular", 2.75f, 2.75f, 2.75f);
                    tModel1.Draw(tShader);
                }

                planeModelMatrix = glm::mat4(1.0f);
            }
        }

        // Car
        mShader.Use();
        mShader.setMat4("projection", projection);
        mShader.setMat4("view", view);

        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(0.0f, 1.0f, 0.0f)); // translate at the center of the scene

        glm::mat4 objModelMatrix;
        glm::mat3 objNormalMatrix;

        GLfloat matrix[16];
        btTransform transform;

        glm::vec3 obj_size(1.0f);
        Model *objectModel;

        int num_cobjs = simulation.dynamicsWorld->getNumCollisionObjects();

        for (unsigned int i = tiles + walls; i < num_cobjs; i++) {
            switch (i) {
                case tiles + walls:
                    objectModel = &mModel;
                    break;
                case tiles + walls + 1:
                case tiles + walls + 2:
                    objectModel = &t1Model;
                    break;
                case tiles + walls + 3:
                case tiles + walls + 4:
                    objectModel = &t2Model;
                    break;
                default:
                    return (EXIT_FAILURE);
            }
            // taking the Collision Object from the list
            btCollisionObject *obj = simulation.dynamicsWorld->getCollisionObjectArray()[i];
            btRigidBody *body = btRigidBody::upcast(obj);

            // transformation matrix of the rigid body, as calculated by the physics engine
            body->getMotionState()->getWorldTransform(transform);

            //Bullet matrix (transform) to an array of floats
            transform.getOpenGLMatrix(matrix);

            //GLM transformation matrix
            objModelMatrix = glm::make_mat4(matrix) * glm::scale(objModelMatrix, obj_size);
            objNormalMatrix = glm::transpose(glm::inverse(glm::mat3(objModelMatrix)));

            //normal matrix
            glUniformMatrix4fv(glGetUniformLocation(mShader.Program, "model"), 1, GL_FALSE,
                               glm::value_ptr(objModelMatrix));
            glUniformMatrix3fv(glGetUniformLocation(mShader.Program, "normal"), 1, GL_FALSE,
                               glm::value_ptr(objNormalMatrix));

            mShader.setVec3("lightColor", glm::vec3(1.0));
            mShader.setVec3("lightPos", lightPos);
            mShader.setVec3("viewPos", camera.Position);

            mShader.setFloat("material.shininess", 128.0f);

            mShader.setVec3("light.direction", 1.0f, -0.5f, -0.5f);
            mShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
            mShader.setVec3("light.diffuse", 0.945f, 0.855f, 0.643f);
            mShader.setVec3("light.specular", 4.0f, 4.0f, 4.0f);

            glActiveTexture(GL_TEXTURE3);
            mShader.setInt("skybox", 3);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

            objectModel->Draw(mShader);

            objModelMatrix = glm::mat4(1.0f);
            objNormalMatrix = glm::mat4(1.0f);
        }

        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));

        // Skybox
        glDepthFunc(GL_LEQUAL);
        sShader.Use();
        sShader.setMat4("projection", projection);
        sShader.setMat4("view", view);
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return EXIT_SUCCESS;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !switched) {
        cameraFollow = !cameraFollow;
        switched = TRUE;
        if (cameraFollow) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) {
        switched = FALSE;
    }

    if (!cameraFollow) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    float steering_limit = 1.0f;
    float steering_speed = 0.05f;

    // Car controls - steering
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (steering > -steering_limit)
            steering -= steering_speed;
    } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (steering < steering_limit)
            steering += steering_speed;
    } else {
        steering -= steering_speed * ((steering > 0) - (steering < 0));
        if (steering < steering_speed && steering > -steering_speed)
            steering = 0.0f;
    }

    // Car controls - acceleration
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        acceleration = 1;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        acceleration = -1;
    } else {
        acceleration = 0;
        handbrake = TRUE;
    }

    // Car controls - handbrake
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        handbrake = TRUE;
    } else {
        handbrake = FALSE;
    }

    // Car controls - reset
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !gotUp) {
        getUp = TRUE;
        gotUp = TRUE;
    } else {
        getUp = FALSE;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
        gotUp = FALSE;
    }

    // Car controls - jump upwards
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !jumped) {
        jump = TRUE;
        jumped = TRUE;
    } else {
        jump = FALSE;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE) {
        jumped = FALSE;
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = FALSE;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    if (!cameraFollow) {
        camera.ProcessMouseMovement(xoffset, yoffset);
    } else if (rotating) {
        baseYaw += xoffset;
        basePitch += yoffset;
        if (basePitch > 89.0f)
            basePitch = 89.0f;
        if (basePitch < -89.0f)
            basePitch = -89.0f;
        camera.ProcessMouseMovement(0, yoffset);
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mod) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        rotating = TRUE;
    else
        rotating = FALSE;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    cameraRadius -= yoffset / 2;
    if (basePitch > 20.0f)
        basePitch = 20.0f;
    if (basePitch < 0.0f)
        basePitch = 0.0f;
}

unsigned int loadCubeMap() {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, channels;
    unsigned char *data;
    std::vector<std::string> txt_faces;
    txt_faces.push_back("D:\\Glitter\\Glitter\\Texture\\clouds1_east.bmp");
    txt_faces.push_back("D:\\Glitter\\Glitter\\Texture\\clouds1_west.bmp");
    txt_faces.push_back("D:\\Glitter\\Glitter\\Texture\\clouds1_up.bmp");
    txt_faces.push_back("D:\\Glitter\\Glitter\\Texture\\clouds1_down.bmp");
    txt_faces.push_back("D:\\Glitter\\Glitter\\Texture\\clouds1_north.bmp");
    txt_faces.push_back("D:\\Glitter\\Glitter\\Texture\\clouds1_south.bmp");
    for (unsigned int i = 0; i < 6; i++) {
        data = stbi_load(txt_faces[i].c_str(), &width, &height, &channels, 0);
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
        );
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}