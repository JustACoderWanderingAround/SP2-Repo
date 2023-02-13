#ifndef CAMERA_FPS_H
#define CAMERA_FPS_H
#include "Camera.h"

class CameraFPS :
    public Camera
{
public:

    CameraFPS();
    ~CameraFPS();
    glm::vec3 yawView;
    glm::vec3 rotatedView;
    glm::vec3 pitchView;
    void Init(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up, bool mouseControl = true, bool keyBoardControl = true);
    void Reset();
    void Update(double dt);
    float fieldOfView;
private:
    bool keyBoardControl;
    bool mouseControl;
    void Refresh();
};

#endif

