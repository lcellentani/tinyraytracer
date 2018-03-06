#include "util.h"
#include "rand.h"

namespace tinyraytracer
{

namespace util
{

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = (2.0f * vec3(random::get(0.0f, 1.0f), random::get(0.0f, 1.0f), random::get(0.0f, 1.0f))) - vec3(1.0f);
	} while (p.lengthSquared() >= 1.0f);
	return p;
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - (2.0f * vec3::dot(v, n) * n);
}

} // namespace util

} // namespace tinyraytracer