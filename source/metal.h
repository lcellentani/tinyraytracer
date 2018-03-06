#pragma once

#include "material.h"
#include "util.h"

namespace tinyraytracer
{

class metal : public material {
public:
	metal(const vec3& a) : mAlbedo(a) {};

	bool scatter(const ray& r, const rayhit& hit, vec3& attenuation, ray& scattered) const override {
		vec3 reflected(util::reflect(r.direction(), hit.normal).normalized());
		scattered = ray(hit.point, reflected);
		attenuation = mAlbedo;
		return vec3::dot(scattered.direction(), hit.normal) > 0.0f;
	}

private:
	vec3 mAlbedo;
};

} // namespace tinyraytracer