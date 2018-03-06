#pragma once

#include "ray.h"
#include "rayhit.h"

namespace tinyraytracer
{

class material {
public:
	virtual bool scatter(const ray& r, const rayhit& hit, vec3& attenuation, ray& scattered) const = 0;
};

} // namespace tinyraytracer