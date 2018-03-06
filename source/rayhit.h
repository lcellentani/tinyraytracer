#pragma once

#include "vec3.h"

namespace tinyraytracer
{

class material;

struct rayhit {
	float t;
	vec3 point;
	vec3 normal;
	material* material;
};

} // namespace tinyraytracer