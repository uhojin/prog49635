# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a C++ OpenGL graphics application project built using Visual Studio 2022 (v143 toolset). The project demonstrates 3D rendering with mesh loading, shader management, lighting, textures, and camera systems.

## Build System

**Visual Studio Solution**: `InitOpenGL.sln`
**Main Project**: `OpenGL/OpenGL.vcxproj`

### Build Commands

Build using MSBuild from command line:
```bash
# Debug build (x64)
msbuild InitOpenGL.sln /p:Configuration=Debug /p:Platform=x64

# Release build (x64)
msbuild InitOpenGL.sln /p:Configuration=Release /p:Platform=x64

# Debug build (Win32)
msbuild InitOpenGL.sln /p:Configuration=Debug /p:Platform=Win32
```

Or build directly in Visual Studio IDE (recommended).

### Build Configuration

- Platform Toolset: v143 (Visual Studio 2022)
- Supported Configurations: Debug|Release
- Supported Platforms: Win32|x64
- Note: Win32 Debug configuration has CLR support enabled

### Pre-build Steps

The project automatically copies required DLLs to the output directory:
- `glew32d.dll` (Debug) from `External/glew-2.1.0/bin/`
- `glfw3.dll` from `External/glfw-3.3.4/lib-vc2019/`

## External Dependencies

The project uses statically linked external libraries located in `External/`:

- **GLEW 2.1.0** (`External/glew-2.1.0/`) - OpenGL extension loading
- **GLFW 3.3.4** (`External/glfw-3.3.4/`) - Window and input management
- **GLM** (`External/glm/`) - Mathematics library for graphics
- **stb_image** (`External/stb/`) - Image loading
- **OBJ_Loader** (`External/obj_loader/`) - OBJ model file loading

Include directories and library paths are pre-configured in the vcxproj file.

## Architecture Overview

### Core Design Pattern: Singleton

The application uses the Singleton pattern (defined in `Singleton.h`) for manager classes:
- `GameController` - Main game loop and scene management
- `WindowController` - GLFW window lifecycle management

### Application Flow

1. **Entry Point** (`main.cpp:3-8`): Initializes and runs the GameController singleton
2. **Initialization** (`GameController::Initialize`):
   - Creates GLFW window via WindowController
   - Initializes GLEW
   - Sets up OpenGL state (depth testing, clear color)
   - Creates default perspective camera
3. **Game Loop** (`GameController::RunGame`):
   - Loads shaders (Color, Diffuse)
   - Creates mesh objects from OBJ files
   - Runs render loop until ESC key or window close
   - Cleans up resources

### Key Components

**GameController** (`GameController.h/cpp`)
- Central controller managing the application lifecycle
- Owns shaders, camera, and mesh collections
- Maintains separate collections for regular meshes (`m_meshBoxes`) and light meshes (`Mesh::Lights` static vector)
- Handles the main render loop

**WindowController** (`WindowController.h/cpp`)
- Manages GLFW window creation and lifecycle
- Provides window resolution information
- Singleton pattern ensures single window instance

**Shader** (`Shader.h/cpp`)
- Loads and compiles vertex and fragment shaders from files
- Provides uniform setters: `SetVec3()`, `SetMat4()`, `SetFloat()`, `SetTextureSampler()`
- Manages shader attributes (vertices, colors, normals, texture coordinates)
- Shader files use `.vertexshader` and `.fragmentshader` extensions

**Mesh** (`Mesh.h/cpp`)
- Represents a 3D object loaded from OBJ files
- Stores vertex data (positions, normals, UVs) and index data
- Manages transform (position, rotation, scale) and calculates world matrix
- Supports multiple textures (m_texture, m_texture2)
- Handles lighting parameters (light position, light color, camera position)
- Static `Mesh::Lights` vector stores all light objects globally
- Renders using a shader and projection-view matrix

**Camera** (`Camera.h/cpp`)
- Creates perspective projection matrix
- Manages view matrix and camera position
- Initialized with screen resolution

**Texture** (`Texture.h/cpp`)
- Loads images using stb_image
- Creates OpenGL textures
- Provides texture ID for binding

### Rendering Pipeline

1. Shaders are loaded from `OpenGL/` directory (e.g., `Color.vertexshader`, `Diffuse.fragmentshader`)
2. Meshes load OBJ models from `../Assets/Models/` (relative to executable location)
3. Each frame:
   - Clear color and depth buffers
   - Render all meshes in `m_meshBoxes` with camera projection-view matrix
   - Render all light meshes from `Mesh::Lights` static vector
   - Swap buffers and poll events

### Asset Locations

- **Models**: `Assets/Models/` - OBJ files (e.g., `teapot.obj`)
- **Textures**: `Assets/Textures/` - Image files
- **Shaders**: `OpenGL/` directory - `.vertexshader` and `.fragmentshader` files

### Standard Includes

The project uses `standardincludes.h` which provides:
- STL headers (vector, string, fstream)
- Windows-specific includes and `M_ASSERT` macro for debug output
- OpenGL headers (GLEW, GLFW, GLM)
- Common project headers (Resolution.h, Singleton.h)
- `using namespace std;`

### Lighting System

Lighting is managed through a dual approach:
- Light objects are stored in the static `Mesh::Lights` vector
- Regular meshes receive lighting information via `SetLightPosition()`, `SetLightColor()`, and `SetCameraPosition()`
- Light meshes typically use the Color shader (unlit)
- Regular meshes use the Diffuse shader (lit)

## Working Directory

When debugging/running from Visual Studio, the working directory is typically `OpenGL/` (where the vcxproj is located). This is why asset paths use `../Assets/` to go up one level from the executable location.
