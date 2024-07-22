#include "color.h"
#include <cstdlib>

// void InitFrameBuffer(unsigned int _w, unsigned int _h);
// void CleanFrameBuffer();

int main(int args, char** argv)
{
	float aspectRatio = 16.0/9.0;
	unsigned int imageWidth = 400;
	unsigned int imageHeight = imageWidth / aspectRatio;
	imageHeight = imageHeight < 1 ? 1 : imageHeight;
	if(args > 1)
	{
		imageWidth = (unsigned)atoi(argv[1]);
		imageHeight = imageWidth / aspectRatio;
		imageHeight = imageHeight < 1 ? 1 : imageHeight;
	}
	InitFrameBuffer(imageWidth, imageHeight);
	RenderPPM(imageWidth, imageHeight);
	// memcpy(framebuffer, render, sizeof(color3) * imageWidth * imageHeight);
	CleanFrameBuffer();
	return 1;
}