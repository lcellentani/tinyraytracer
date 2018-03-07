#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>
#include <limits>

#include "vec3.h"
#include "ray.h"
#include "rayhit.h"
#include "camera.h"
#include "sphere.h"
#include "rand.h"
#include "util.h"
#include "lambertian.h"
#include "metal.h"
#include "dieletric.h"

using namespace tinyraytracer;

vec3 color(const ray& r, const std::vector<std::unique_ptr<primitive>>& primitives, int32_t depth) {
	rayhit hit;
	for (auto& primitive : primitives) {
		if (primitive->raycast(r, 0.001f, std::numeric_limits<float>::max(), hit)) {
			ray scattered; vec3 attenuation;
			if (depth < 50 && hit.material->scatter(r, hit, attenuation, scattered)) {
				return attenuation * color(scattered, primitives, depth + 1);
			} else {
				return vec3(0.0f);
			}
		}
	}
	vec3 normalized_dir = r.direction().normalized();
	float t = 0.5f * (normalized_dir.y() + 1.0f);
	return ((1.0f - t) * vec3(1.0f)) + (t * vec3(0.5f, 0.7f, 1.0f));
}

void main() {
	int32_t nx = 800;
	int32_t ny = 400;
	int32_t ns = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);
	std::vector<std::unique_ptr<primitive>> primitives;
	primitives.push_back(std::make_unique<sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f, std::make_unique<lambertian>(vec3(0.1f, 0.2f, 0.5f))));
	primitives.push_back(std::make_unique<sphere>(vec3(1.0f, 0.0f, -1.0f), 0.5f, std::make_unique<metal>(vec3(0.8f, 0.6f, 0.2f), 0.3f)));
	//primitives.push_back(std::make_unique<sphere>(vec3(-1.0f, 0.0f, -1.0f), 0.5f, std::make_unique<metal>(vec3(0.8f, 0.8f, 0.8f), 1.0f)));
	primitives.push_back(std::make_unique<sphere>(vec3(-1.0f, 0.0f, -1.0f), 0.5f, std::make_unique<dieletric>(1.5f)));
	//primitives.push_back(std::make_unique<sphere>(vec3(-1.0f, 0.0f, -1.0f), -0.45f, std::make_unique<dieletric>(1.5f)));
	primitives.push_back(std::make_unique<sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f, std::make_unique<lambertian>(vec3(0.8f, 0.8f, 0.0f))));
	camera mainCamera(vec3(-2.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f), 60.0f, float(nx) / float(ny));
	for (int32_t j = ny - 1; j >= 0; j--) {
		for (int32_t i = 0; i < nx; i++) {
			vec3 c;
			for (int32_t s = 0; s < ns; s++) {
				float u = float(i + random::get(0.0f, 1.0f)) / float(nx);
				float v = float(j + random::get(0.0f, 1.0f)) / float(ny);
				ray r = mainCamera.get_ray(u, v);
				c += color(r, primitives, 0);
			}
			c /= float(ns);
			c = vec3(std::sqrt(c[0]), std::sqrt(c[1]), std::sqrt(c[2]));
			int ir = int(255.99f * c.r());
			int ig = int(255.99f * c.g());
			int ib = int(255.99f * c.b());
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
