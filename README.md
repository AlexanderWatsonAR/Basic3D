# Basic3D

## Description
Basic3D is a library that simplifies creating a 3D application. The purpose of this library to create graphically low intensive 3D scenes with easy to manage scene properties. Basic3D uses Legacy OpenGL (OpenGL 3.0 to be precise); this is namely because rendering and transforming objects is simple and using advanced graphical functions is not the intent of this project. 

## Features
1. One Function creation of OpenGL Context Window
2. Image Loading & Texture Binding
3. Model Loading & Material Library Loading
4. Lighting
5. Rendering Models
6. Rendering 3D & 2D Text
7. Scene Graph
8. Axis Aligned Bounding box & Bounding Spheres.
9. Input State Control.

## Usage
**Note: This has only been used and tested inside Visual Studio 2015!**

A test application called *'HelloBasic3D'* is available for viewing. The directory and source code should provide and insight into its usage, however, this section will describe how to set up an application to use our library, from scratch. 

1. Firstly, in visual studio create a new project. This will be a Visual C++, Win32 Console Application. Give it an appropriate title, if you are creating a game, here are some suggested titles: *'GTA X: Space Jacking'*,  '*Devil May Laugh*' or '*HL3*'.

2. Next, we want our main entry function defined. We need argv & argc as parameters because they will be required when we initialise GLUT. I suggest you create a source file called main.cpp and write your function in there. We will leave the braces blank for the moment and create our scene class.

3. Add a new class to the project. This class will be a scene, so all of our game logic will be contained here. Give the scene an appropriate name, I will refer to the scene as *'TestScene'*. *'TestScene'* will inherit from scene. 

4. Next we want to be able to use the Basic3D library. To do this requires multiple steps. First, we want to open up the library. To ensure the library will build we first want to clean the solution. After that we want to build the solution.

5. After that, open file explorer and navigate to the top level of the Basid3D directory. Go into the the *'Debug*' folder and select the *'application extension'* & the *'object file library*' files. These two files need to be copied and placed inside your game project directory.

6. Now we need to go into the source directory of the Basic3D library. To use the library we need the header files as an entry point. Copy all the header files, apart from *'stdafx.h'* and *'targetver.h'*, create a new folder in your game source directory, call it *"Basic3D"* and paste the header files in there. You also want to copy and paste the *'SOIL'* and *'GL'* folders inside this new folder as well. Finally, for this stage, we want to copy *'freeglut.dll'*, *'freeglut.lib'* and *'SOIL.lib'* and paste them into the game directory.

7. Okay, so now we have all of the files required to use Basic3D, we can go back to our game project. Inside *'TestGame.h'* include the file Basic3D.h. This will make the library functionality available. The library uses namespace accessors and all functionality is contained within the Basic3D namespace at the top level. So adding *'using namespace Basic3D;'* is advisible for small projects.

8. Scene has two abstract functions that need to be overrided. So, add under public: *'void LoadContent();'* and *void Update(int timeStep)'*. The draw function isn't required for drawing as drawing is done internally. However a virtual function exists within scene that you can overload. If you do you write your own OpenGL draw code.

9. Now, to create a new window with our scene we need to go back to main. Add a line to include the test scene header. All we need now is call the initialise method inside the director namespace. The method has multiple parameters these being: argc, argv, initialScene, windowXPosition, windowYPosition, viewportWidth, viewportHeight, clearColour, windowTitle and preferredFPS. Most of this should be fairly self explanatory. A reference of pointer is required passing through the scene and the clear colour can be set to a null pointer, in which case, the clear colour is set as sky blue.

10. Hit Debug! The application should build and run. You shouldn't see much, a terminal and window should open, with the window being set to whatever colour you allocated. To Add models, cameras, textures and more view the library or view the HelloBasic3D application for example code. 
