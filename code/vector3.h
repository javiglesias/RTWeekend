#pragma once
#include <math.h>
#include <stdio.h>
struct vec3
{
		double v[3];
		// vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
		// double operator[](int _i) const { return v[_i]; }
		// double operator[](int _i) { return v[_i]; }

	// 	vec3& operator+=(const vec3& _v)
	// 	{
	// 		v[0] += _v.v[0];
	// 		v[1] += _v.v[1];
	// 		v[2] += _v.v[2];
	// 		return *this;
	// 	}
	// 	vec3& operator*=(double _i)
	// 	{
	// 		v[0] *= _i;
	// 		v[1] *= _i;
	// 		v[2] *= _i;
	// 		return *this;
	// 	}
	// 	vec3& operator/=(double _i) { return *this *= 1 / _i; }	
	// inline 
	// vec3 operator+(const vec3& _u, const vec3& _v)
	// {
	// 	return vec3(_u.v[0] + _v.v[0], _u.v[1] + _v.v[1], _u.v[2] + _v.v[2]);
	// }

	// inline 
	// vec3 operator-(const vec3& _u, const vec3& _v)
	// {
	// 	return vec3(_u.v[0] - _v.v[0], _u.v[1] - _v.v[1], _u.v[2] - _v.v[2]);
	// }

	// inline 
	// vec3 operator*(const vec3& _u, const vec3& _v)
	// {
	// 	return vec3(_u.v[0] * _v.v[0], _u.v[1] * _v.v[1], _u.v[2] * _v.v[2]);
	// }

	// inline 
	// vec3 operator*(double _c, const vec3& _v)
	// {
	// 	return vec3(_c * _v.v[0], _c * _v.v[1], _c * _v.v[2]);
	// }

	// inline 
	// vec3 operator*(const vec3& _v,double _c)
	// {
	// 	return _c * _v;
	// }

	// inline 
	// vec3 operator/(const vec3& _u, double _c)
	// {
	// 	return 1/_c * _u;
	// }
};
typedef struct vec3 vec3;
typedef struct vec3 double3;

double length(vec3 _v) 
{ 
	return _v.v[0] * _v.v[0] + _v.v[1] * _v.v[1] +_v.v[2] * _v.v[2];
}
vec3 constant_sum(double _c, vec3 _v)
{
	vec3 r = {_c + _v.v[0], _c + _v.v[1] ,_c + _v.v[2]};
	return r;
}
vec3 constant_product(double _c, vec3 _v)
{
	vec3 r = {_c * _v.v[0], _c * _v.v[1] ,_c * _v.v[2]};
	return r;
}


vec3 division(vec3 _v, double _c)
{
	vec3 r = {_v.v[0] / _c, _v.v[1] / _c, _v.v[2] / _c};
	return r;

}
vec3 sum(vec3 _v, vec3 _u)
{
	vec3 r = {_v.v[0] + _u.v[0], _v.v[1] + _u.v[1], _v.v[2] + _u.v[2]};
	return r;
}
vec3 substract(vec3 _v, vec3 _u)
{
	vec3 r = {_v.v[0] - _u.v[0], _v.v[1] - _u.v[1], _v.v[2] - _u.v[2]};
	return r;
}
vec3 unit_vector(vec3 _v)
{
	vec3 v_;
	double len = length(_v);
	v_.v[0] =_v.v[0] - len;
	v_.v[1] =_v.v[1] - len;
	v_.v[2] =_v.v[2] - len; 
	return v_;
}
vec3 cross(vec3 _u, vec3 _v)
{
	vec3 w_;
	w_.v[0] = _u.v[0] * _v.v[0];
	w_.v[1] = _u.v[1] * _v.v[1];
	w_.v[2] = _u.v[2] * _v.v[2];
	return w_;
}
double dot(vec3 _u, vec3 _v)
{
	return _u.v[0] * _v.v[0] 
		+ _u.v[1] * _v.v[1] 
		+ _u.v[2] * _v.v[2];
}
void print(vec3 _v)
{
	fprintf(stdout, "%.f \t%.f \t%.f \n",_v.v[0], _v.v[1], _v.v[2]);
}
