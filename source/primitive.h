#pragma once

#include "ray.h"

namespace tinyraytracer
{
	
class primitive {
public:
	virtual bool raycast(const ray& ray, float minDistance, float maxDistance, ray::hitinfo& hitinfo) = 0;
};

} // namespace tinyraytracer