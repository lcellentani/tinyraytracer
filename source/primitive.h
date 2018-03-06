#pragma once

#include "ray.h"
#include "rayhit.h"
namespace tinyraytracer
{
	
class primitive {
public:
	virtual bool raycast(const ray& r, float minDistance, float maxDistance, rayhit& hit) = 0;
};

} // namespace tinyraytracer