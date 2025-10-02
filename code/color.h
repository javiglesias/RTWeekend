#pragma once
#include "sphere.h"
#include "xServer.h"
typedef vec3 color3;

void RenderPixel(color3 _v)
{
	fprintf(stdout, "%.f \t%.f \t%.f \n",_v.v[0] * 255.f, _v.v[1] * 255.f, 
					_v.v[2] * 255.f);
}
