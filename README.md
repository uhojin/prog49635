# InitOpenGL

An OpenGL graphics project featuring 3D rendering with skybox, post-processing effects, and mesh loading capabilities.

## Features

- 3D mesh rendering with OBJ file support
- Skybox rendering
- Post-processing effects
- Camera controls
- Texture mapping (diffuse, normal, specular)
- Mouse and game controller input support
- Procedural geometry generation

## Requirements

- **Visual Studio 2022** (Platform Toolset v143)
- **Windows 10 SDK**
- **32-bit (Win32) build configuration** (x86 architecture required)
- OpenGL 3.3+ compatible graphics card

## Build Instructions

### Using Visual Studio

1. **Open the Solution**
   - Open `InitOpenGL.sln` in Visual Studio 2022

2. **Select Build Configuration**
   - Set the build configuration to **Debug** or **Release**
   - **Important**: Set the platform to **Win32** (x86)
     - Use the dropdown in the toolbar or Configuration Manager
     - This project is configured for 32-bit builds only

3. **Build the Project**
   - Build menu → Build Solution (or press `Ctrl+Shift+B`)
   - The executable will be generated in the `Debug/` or `Release/` folder

4. **Run the Application**
   - Debug menu → Start Debugging (`F5`) or Start Without Debugging (`Ctrl+F5`)

## Project Structure

```
InitOpenGL/
├── OpenGL/                 # Main project directory
│   ├── main.cpp           # Application entry point
│   ├── Shader.cpp/h       # Shader management
│   ├── Camera.cpp/h       # Camera system
│   ├── Mesh.cpp/h         # 3D mesh rendering
│   ├── Skybox.cpp/h       # Skybox rendering
│   ├── PostProcessor.cpp/h # Post-processing effects
│   ├── Texture.cpp/h      # Texture loading and management
│   └── ...
├── Assets/                 # Game assets
│   ├── Textures/          # Texture files
│   ├── Models/            # 3D model files (.obj)
│   └── Fonts/             # Font files
├── FinalProjectAssets/     # Additional project assets
├── External/               # External dependencies (GLEW, GLFW, etc.)
└── Shaders/               # GLSL shader files

```

## Testing

1. **Verify the Build**
   - Ensure the project builds without errors
   - Check the Output window for any warnings

2. **Run the Application**
   - The application window should open and display the 3D scene
   - Test camera controls with mouse/keyboard
   - Verify that models, textures, and skybox render correctly

3. **Check Post-Processing**
   - Post-processing effects should be visible in the rendered scene

## Dependencies

The project uses the following external libraries (included in `External/` folder):
- GLEW (OpenGL Extension Wrangler)
- GLFW (Window and input handling)
- GLM (OpenGL Mathematics)
- FreeType (Font rendering)

## Troubleshooting

### Build Errors

- **"Cannot open include file"**: Ensure all paths in Project Properties → C/C++ → General → Additional Include Directories are correct
- **Linker errors**: Verify Project Properties → Linker → General → Additional Library Directories points to the correct library paths
- **Platform mismatch**: Ensure you're building for **Win32 (x86)**, not x64

### Runtime Errors

- **DLL not found**: Make sure all required DLLs are in the same directory as the executable or in your system PATH
- **Shader compilation errors**: Check the console output for shader error messages
- **Asset loading failures**: Verify asset file paths are correct relative to the executable location

## Notes

- This project is configured for **32-bit (Win32) builds only**
- Make sure to select the Win32 platform in Visual Studio before building
- Asset paths may need adjustment depending on your working directory

## License

Educational project for graphics programming coursework.
