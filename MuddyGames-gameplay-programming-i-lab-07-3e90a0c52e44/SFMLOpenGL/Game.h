#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "MyMatrix3.h"

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:

	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();

	void InitVertexes();
	void processEvents();
	GLuint index;
	Clock clock;
	Time elapsed;

	float rotationAngle = 0.0f;
	float angleX = 0.0f;
	float angleY = 0.0f;

	float scaleX = 100;
	float scaleY = 100;

	float transX = 0.0f;
	float transY = 0.0f;

	MyVector3D vertex[7];
};