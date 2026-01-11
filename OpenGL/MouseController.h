#ifndef MOUSE_CONTROLLER_H
#define MOUSE_CONTROLLER_H

#include "standardincludes.h"

class MouseController
{
public:
    // Mouse state
    static bool LeftButtonClicked;
    static bool MiddleButtonClicked;
    static glm::vec2 ClickPosition;
    static glm::vec2 MovementDirection;
    static float MovementSpeed;
    static glm::vec2 CurrentMousePosition;
    static glm::vec2 PreviousMousePosition;
    static glm::vec2 MouseDelta;

    // Methods
    static void Initialize(GLFWwindow* window);
    static void ProcessClick(GLFWwindow* window, double xpos, double ypos);
    static void ResetMovement();
    static void Update(GLFWwindow* window);
    static glm::vec2 GetNormalizedPosition();

private:
    static void CalculateQuadrantMovement(double xpos, double ypos, int windowWidth, int windowHeight);
};

#endif // MOUSE_CONTROLLER_H
