#ifndef MOUSE_CONTROLLER_H
#define MOUSE_CONTROLLER_H

#include "standardincludes.h"

class MouseController
{
public:
    // Mouse state
    static bool LeftButtonClicked;
    static glm::vec2 ClickPosition;
    static glm::vec2 MovementDirection;
    static float MovementSpeed;

    // Methods
    static void Initialize(GLFWwindow* window);
    static void ProcessClick(GLFWwindow* window, double xpos, double ypos);
    static void ResetMovement();

private:
    static void CalculateQuadrantMovement(double xpos, double ypos, int windowWidth, int windowHeight);
};

#endif // MOUSE_CONTROLLER_H
