#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "MyMath.h"
#include "Vector3.h"
#include <glm\glm.hpp>

#define x_resistant 3

struct GameObject
{
    enum GAMEOBJECT_TYPE
    {
        GO_NONE = 0,
        GO_TEXT,
        GO_BALL,
        GO_CUBE,
        GO_CAN,
        GO_TABLE,
        GO_FLOOR,
        GO_BULLET,
        GO_WALL,
        GO_ALIEN,  // aliens
        GO_TOTAL, //must be last
    };
    GAMEOBJECT_TYPE type;
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 scale;
    glm::vec3 normal;
    glm::vec3 force;
    glm::vec3 dir;
    glm::vec3 torque;
    bool slowdown;
    int timeScale;
    void fixedUpdate(double dt);
    bool CheckSSCollision(GameObject* that);
    void CollisionResponse(GameObject* that);
    bool CheckLineCollision(GameObject* that);
    void WallCollisionResponse(GameObject* that);
    bool CheckCSCollision(GameObject* that);
    bool CheckCCCollision(GameObject* that);
    void setDirection(const glm::vec3& vec, float radian);
    bool active;
    bool collidingWithTable;
    float mass;
    float momentOfInertia;
    float anglularVelocity;
    float multiplier;
    bool touched;
    double despawnTimer;
    

    GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
    ~GameObject();
};
#endif