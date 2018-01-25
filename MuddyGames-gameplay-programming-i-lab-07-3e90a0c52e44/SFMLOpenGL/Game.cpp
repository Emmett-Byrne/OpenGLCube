#include "Game.h"

bool updatable = false;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	index = glGenLists(1);
	InitVertexes();
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}


void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glTranslatef(0.0f, 0.0f, -10.0f);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	InitVertexes();
	processEvents();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!updatable)
		{
			updatable = true;
		}
		else
			updatable = false;
	}

	if (updatable)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}

	}
	
/*
	for (int i = 0; i < 8; i++)
	{
		vertex[i] = MyMatrix3::rotationZ(rotationAngle * 0.0174533) * vertex[i];
	}*/
	for (int i = 0; i < 8; i++)
	{
		vertex[i] = MyMatrix3::translation(transX, transY) * vertex[i];

		vertex[i] = MyMatrix3::rotationX(angleX * 0.0174533) * vertex[i];
		vertex[i] = MyMatrix3::rotationY(angleY * 0.0174533) * vertex[i];

		vertex[i] = MyMatrix3::scale(scaleX, scaleY) * vertex[i];
	}

	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << endl;
	glLoadIdentity();
	//glRotatef(rotationAngle, 0, 0, 1); // Rotates the camera on Y Axis

	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(vertex[0].X(), vertex[0].Y(), vertex[0].Z());
		glVertex3f(vertex[1].X(), vertex[1].Y(), vertex[1].Z());
		glVertex3f(vertex[2].X(), vertex[2].Y(), vertex[2].Z());
		glVertex3f(vertex[3].X(), vertex[3].Y(), vertex[3].Z());

		//top
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(vertex[0].X(), vertex[0].Y(), vertex[0].Z());
		glVertex3f(vertex[1].X(), vertex[1].Y(), vertex[1].Z());
		glVertex3f(vertex[5].X(), vertex[5].Y(), vertex[5].Z());
		glVertex3f(vertex[4].X(), vertex[4].Y(), vertex[4].Z());

		//bottom
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(vertex[2].X(), vertex[2].Y(), vertex[2].Z());
		glVertex3f(vertex[3].X(), vertex[3].Y(), vertex[3].Z());
		glVertex3f(vertex[7].X(), vertex[7].Y(), vertex[7].Z());
		glVertex3f(vertex[6].X(), vertex[6].Y(), vertex[6].Z());

		//Right
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(vertex[0].X(), vertex[0].Y(), vertex[0].Z());
		glVertex3f(vertex[4].X(), vertex[4].Y(), vertex[4].Z());
		glVertex3f(vertex[7].X(), vertex[7].Y(), vertex[7].Z());
		glVertex3f(vertex[3].X(), vertex[3].Y(), vertex[3].Z());

		//left
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(vertex[1].X(), vertex[1].Y(), vertex[1].Z());
		glVertex3f(vertex[5].X(), vertex[5].Y(), vertex[5].Z());
		glVertex3f(vertex[6].X(), vertex[6].Y(), vertex[6].Z());
		glVertex3f(vertex[2].X(), vertex[2].Y(), vertex[2].Z());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(vertex[4].X(), vertex[4].Y(), vertex[4].Z());
		glVertex3f(vertex[5].X(), vertex[5].Y(), vertex[5].Z());
		glVertex3f(vertex[6].X(), vertex[6].Y(), vertex[6].Z());
		glVertex3f(vertex[7].X(), vertex[7].Y(), vertex[7].Z());
	}
	glEnd();
	glEndList();

	glCallList(1);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

void Game::InitVertexes()
{
	vertex[0] = MyVector3D(1.0f, 1.0f, 1.0f); //front top right
	vertex[1] = MyVector3D(-1.0f, 1.0f, 1.0f); //front bottom right
	vertex[2] = MyVector3D(-1.0f, -1.0f, 1.0f); //front bottom left
	vertex[3] = MyVector3D(1.0f, -1.0f, 1.0f); //front top left
	vertex[4] = MyVector3D(1.0f, 1.0f, -1.0f); //back top right
	vertex[5] = MyVector3D(-1.0f, 1.0f, -1.0f); //back bottom right
	vertex[6] = MyVector3D(-1.0f, -1.0f, -1.0f); //back bottom left
	vertex[7] = MyVector3D(1.0f, -1.0f, -1.0f); //back top left
}

void Game::processEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		angleX++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		angleX--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		angleY++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		angleY--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		scaleX++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		scaleX--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		scaleY++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		scaleY--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		transX++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		transX--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		transY++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		transY--;
	}
}
