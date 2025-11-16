#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

// Include standard headers
#include <vector>
#include <string>
#include <map>
#include <iostream>
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
#include <glm/ext.hpp>	// OpenGL Experimental to_string
#include <glm/gtc/matrix_transform.hpp>	// View / Projection

// Font includes
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Resolution.h"	
#include "Singleton.h"

using namespace std;

#endif // !STANDARD_INCLUDES_H
