#pragma once
typedef struct
{
	int v[2];
} i2d;

typedef struct
{
	int x, y, z;
} i3d;

float lerp(float _a, float _b, float _alpha)
{
	return (1-_alpha) * _a + _alpha * _b;
}