#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

// Include standard headers
#include <vector>
#include <string>
#include <fstream>

// Windows specific includes and defines
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif // _WIN32

// OpenGL Helper Headers
#include <GL/glew.h>	// GLEW
#include <GLFW/glfw3.h>	// GLFW
#include <glm/glm.hpp>	// GLM

#include "Singleton.h"

using namespace std;

#endif // !STANDARD_INCLUDES_H
