#include "util.h"
#include "rand.h"
#include <cmath>

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

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
	vec3 uv = v.normalized();
	float dt = vec3::dot(uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
	if (discriminant > 0.0f) {
		refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
		return true;
	}
	return false;
}

float schlick(float cosine, float ref_idx) {
	float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * pow((1 - cosine), 5.0f);
}

} // namespace util

} // namespace tinyraytracer