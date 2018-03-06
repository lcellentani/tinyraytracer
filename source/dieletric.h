#pragma once

#include "material.h"
#include "util.h"

namespace tinyraytracer
{

class dieletric : public material {
public:
	dieletric(float ri) : mRefractiveIndex(ri), mInvRefractiveIndex(ri != 0 ? (1.0f / ri) : 0.0f) {};

	bool scatter(const ray& r, const rayhit& hit, vec3& attenuation, ray& scattered) const override {
		float NdotD = vec3::dot(r.direction(), hit.normal);

		vec3 outward_normal = hit.normal;
		float ni_over_nt = mInvRefractiveIndex;
		float cosine = -NdotD / r.direction().length();
		if (NdotD > 0) {
			outward_normal = -hit.normal;
			ni_over_nt = mRefractiveIndex;
			//cosine = mRefractiveIndex * NdotD / r.direction().length();
			cosine = NdotD / r.direction().length();
			cosine = sqrt(1 - mRefractiveIndex * mRefractiveIndex * (1.0f - cosine * cosine));
		}
		
		vec3 refracted;
		float reflect_prob = 1.0;
		if (util::refract(r.direction(), outward_normal, ni_over_nt, refracted)) {
			reflect_prob = util::schlick(cosine, mRefractiveIndex);
		}
		vec3 reflected = util::reflect(r.direction(), hit.normal);

		float rv = random::get(0.0f, 1.0f);
		scattered = ray(hit.point, (rv < reflect_prob) ? reflected : refracted);
		attenuation = vec3(1.0, 1.0, 1.0);
		return true;
	}

private:
	float mRefractiveIndex;
	float mInvRefractiveIndex;
};

} // namespace tinyraytracer