#include "MouseController.h"
#include "WindowController.h"

// Initialize static variables
bool MouseController::LeftButtonClicked = false;
glm::vec2 MouseController::ClickPosition = glm::vec2(0.0f, 0.0f);
glm::vec2 MouseController::MovementDirection = glm::vec2(0.0f, 0.0f);
float MouseController::MovementSpeed = 0.0f;

// GLFW mouse button callback
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            MouseController::ProcessClick(window, xpos, ypos);
        }
        else if (action == GLFW_RELEASE)
        {
            MouseController::ResetMovement();
        }
    }
}

void MouseController::Initialize(GLFWwindow* window)
{
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void MouseController::ProcessClick(GLFWwindow* window, double xpos, double ypos)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    ClickPosition = glm::vec2((float)xpos, (float)ypos);
    LeftButtonClicked = true;

    CalculateQuadrantMovement(xpos, ypos, width, height);
}

void MouseController::CalculateQuadrantMovement(double xpos, double ypos, int windowWidth, int windowHeight)
{
    // Convert screen coordinates to normalized coordinates (-1 to 1)
    float normalizedX = (float)(xpos / windowWidth) * 2.0f - 1.0f;
    float normalizedY = -((float)(ypos / windowHeight) * 2.0f - 1.0f); // Flip Y axis

    // Determine quadrant and calculate direction
    glm::vec2 sceneCenter(0.0f, 0.0f);
    glm::vec2 quadrantCenter;

    // Determine which quadrant
    if (xpos < windowWidth / 2.0f)
    {
        // Left side
        if (ypos < windowHeight / 2.0f)
        {
            // Top-left quadrant
            quadrantCenter = glm::vec2(-0.5f, 0.5f);
        }
        else
        {
            // Bottom-left quadrant
            quadrantCenter = glm::vec2(-0.5f, -0.5f);
        }
    }
    else
    {
        // Right side
        if (ypos < windowHeight / 2.0f)
        {
            // Top-right quadrant
            quadrantCenter = glm::vec2(0.5f, 0.5f);
        }
        else
        {
            // Bottom-right quadrant
            quadrantCenter = glm::vec2(0.5f, -0.5f);
        }
    }

    // Calculate direction from scene center to quadrant center
    MovementDirection = glm::normalize(quadrantCenter - sceneCenter);

    // Calculate speed based on distance from quadrant center to click point
    glm::vec2 clickNormalized(normalizedX, normalizedY);
    float distanceFromQuadrantCenter = glm::length(clickNormalized - quadrantCenter);

    // Speed increases with distance from quadrant center
    // Multiply by a constant to make movement noticeable
    MovementSpeed = distanceFromQuadrantCenter * 0.5f;
}

void MouseController::ResetMovement()
{
    LeftButtonClicked = false;
    MovementDirection = glm::vec2(0.0f, 0.0f);
    MovementSpeed = 0.0f;
}
