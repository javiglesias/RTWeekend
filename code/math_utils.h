#pragma once

namespace math
{
	inline
	float lerp(float _a, float _b, float _alpha)
	{
		return (1-_alpha) * _a + _alpha * _b;
	}
}