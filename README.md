# WFH-ProMax
 
A lightweight Windows mouse idler application that simulates continuous mouse movement to prevent system idle timeout. The application moves the mouse left and right until a keyboard key is pressed.
 
## How It Works
   
### Mouse Input Mechanism
 
- **Mouse Input Events**: The Windows API sends genuine mouse motion events that the operating system processes as if real hardware movement occurred. This means:
  - The system registers actual mouse activity (useful for idle prevention)
  - Applications monitoring mouse input detect the movement
  - Third-party software sees legitimate mouse events
  - The behavior is identical to physical mouse movement from a system perspective


## Building
 
This project uses **CMake**, a meta-build system that generates platform-specific build files.
 
## Troubleshooting
 
| Issue | Solution |
|-------|----------|
| CMake not found | Install CMake from [cmake.org](https://cmake.org/download/) and add to PATH |
| Build fails with "user32" not found | Ensure Windows SDK is installed with Visual Studio |
| Mouse not moving | Run with administrator privileges if needed |
| Application doesn't exit on keypress | Check keyboard input detection implementation |
