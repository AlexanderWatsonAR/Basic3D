#include "HelloBasic3D.h"
#include "SecondScene.h"

int main(int argc, char* argv[])
{
	int viewportHeight = 768;
	int viewportWidth = 1024;
	Colour* red = new Colour(1.0f, 0.0f, 0.0f, 1.0f);
	Director::Initialise(argc, argv, new HelloBasic3D(), 300, 100, viewportWidth, viewportHeight, nullptr, "HelloBasic3D", 60);

	return 0;
}