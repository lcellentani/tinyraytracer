#pragma once

#include "vec3.h"

namespace tinyraytracer
{
namespace util
{

vec3 random_in_unit_sphere();

vec3 reflect(const vec3& v, const vec3& n);

} // namespace util
} // namespace tinyraytracer