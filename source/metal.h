#pragma once

#include "material.h"
#include "util.h"
#include <algorithm>

namespace tinyraytracer
{

class metal : public material {
public:
	metal(const vec3& a, float f) : mAlbedo(a), mFuzziness(std::min(f, 1.0f)) {};

	bool scatter(const ray& r, const rayhit& hit, vec3& attenuation, ray& scattered) const override {
		vec3 reflected(util::reflect(r.direction(), hit.normal).normalized());
		scattered = ray(hit.point, reflected + (mFuzziness * util::random_in_unit_sphere()));
		attenuation = mAlbedo;
		return vec3::dot(scattered.direction(), hit.normal) > 0.0f;
	}

private:
	vec3 mAlbedo;
	float mFuzziness;
};

} // namespace tinyraytracer