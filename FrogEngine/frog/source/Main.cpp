//FrogEngine framework created by Sarah Watts.
#include <iostream>
#include "Application.h"

//The Game to include
#include "MyGame.h"

int main(void)
{
	Application* app = new Application(new MyGame());
	app->run();
	delete app;
	return 0;
}