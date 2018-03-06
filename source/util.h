#pragma once

#include "vec3.h"

namespace tinyraytracer
{
namespace util
{

vec3 random_in_unit_sphere();

vec3 reflect(const vec3& v, const vec3& n);

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted);

float schlick(float cosine, float ref_idx);

} // namespace util
} // namespace tinyraytracer