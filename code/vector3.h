#pragma once
#include <cmath>
#include <iostream>
namespace math
{
	struct vec3
	{
		double v[3];
		vec3() :v{ 0.f,0.f,0.f } {}
		vec3(double _x, double _y, double _z) : v{ _x, _y, _z } {}
		vec3(double _c) : v{ _c, _c, _c } {}
		double X() const { return v[0]; }
		double Y() const { return v[1]; }
		double Z() const { return v[2]; }

		vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
		double operator[](int _i) const { return v[_i]; }
		double operator[](int _i) { return v[_i]; }

		vec3& operator+=(const vec3& _v)
		{
			v[0] += _v.v[0];
			v[1] += _v.v[1];
			v[2] += _v.v[2];
			return *this;
		}
		vec3& operator*=(double _i)
		{
			v[0] *= _i;
			v[1] *= _i;
			v[2] *= _i;
			return *this;
		}
		vec3& operator/=(double _i) { return *this *= 1 / _i; }

		double length() const { return std::sqrt(length_sq()); }
		double length_sq() const
		{
			return v[0] * v[0] + v[1] * v[1] +
				v[2] * v[2];
		}

		void print()
		{
			fprintf(stdout, "%.f \t%.f \t%.f \n",v[0], v[1], v[2]);
		}
	};
	using double3 = vec3;
	
	inline 
	std::ostream& operator<<(std::ostream& out, const vec3& _v)
	{
		return out << _v.v[0] + '\t' + _v.v[1] + '\t' + _v.v[2] + '\n';
	}
	
	inline 
	vec3 operator+(const vec3& _u, const vec3& _v)
	{
		return vec3(_u.v[0] + _v.v[0], _u.v[1] + _v.v[1], _u.v[2] + _v.v[2]);
	}

	inline 
	vec3 operator-(const vec3& _u, const vec3& _v)
	{
		return vec3(_u.v[0] - _v.v[0], _u.v[1] - _v.v[1], _u.v[2] - _v.v[2]);
	}

	inline 
	vec3 operator*(const vec3& _u, const vec3& _v)
	{
		return vec3(_u.v[0] * _v.v[0], _u.v[1] * _v.v[1], _u.v[2] * _v.v[2]);
	}

	inline 
	vec3 operator*(double _c, const vec3& _v)
	{
		return vec3(_c * _v.v[0], _c * _v.v[1], _c * _v.v[2]);
	}

	inline 
	vec3 operator*(const vec3& _v,double _c)
	{
		return _c * _v;
	}

	inline 
	vec3 operator/(const vec3& _u, double _c)
	{
		return 1/_c * _u;
	}

	inline
	double dot(const vec3& _u, const vec3& _v)
	{
		return _u.v[0] * _v.v[0] 
			+ _u.v[1] * _v.v[1] 
			+ _u.v[2] * _v.v[2];
	}

	inline
	vec3 cross(const vec3& _u, const vec3& _v)
	{
		return vec3(_u.v[0] * _v.v[0] 
				, _u.v[1] * _v.v[1] 
				, _u.v[2] * _v.v[2]);
	}

	inline
	vec3 unit_vector(const vec3& _v)
	{
		return _v / _v.length();
	}
}