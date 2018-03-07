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
#include "timing.h"

using namespace tinyraytracer;

bool trace(const std::vector<std::unique_ptr<primitive>>& primitives, const ray& r, float minDistance, float maxDistance, rayhit& hit) {
	rayhit temp_hit;
	bool hit_anything = false;
	float closest_so_far = maxDistance;
	for (auto& p : primitives) {
		if (p->raycast(r, minDistance, closest_so_far, temp_hit)) {
			hit_anything = true;
			closest_so_far = temp_hit.t;
			hit = temp_hit;
		}
	}
	return hit_anything;
}

vec3 color(const ray& r, const std::vector<std::unique_ptr<primitive>>& primitives, int32_t depth) {
	rayhit hit;
	if (trace(primitives, r, 0.001f, std::numeric_limits<float>::max(), hit)) {
		ray scattered; vec3 attenuation;
		if (depth < 50 && hit.material->scatter(r, hit, attenuation, scattered)) {
			return attenuation * color(scattered, primitives, depth + 1);
		}
		return vec3(0.0f);
	}
	vec3 normalized_dir = r.direction().normalized();
	float t = 0.5f * (normalized_dir.y() + 1.0f);
	return ((1.0f - t) * vec3(1.0f)) + (t * vec3(0.5f, 0.7f, 1.0f));
}

void create_random_scene(std::vector<std::unique_ptr<primitive>>& primitives) {
	primitives.push_back(std::make_unique<sphere>(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, std::make_unique<lambertian>(vec3(0.5f, 0.5f, 0.5f))));
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = random::get(0.0f, 1.0f);
			vec3 center(a + 0.9f * random::get(0.0f, 1.0f), 0.2f, b + 0.9f * random::get(0.0f, 1.0f));
			if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
				if (choose_mat < 0.8f) {  // diffuse
					vec3 c(random::get(0.0f, 1.0f) * random::get(0.0f, 1.0f), random::get(0.0f, 1.0f) * random::get(0.0f, 1.0f), random::get(0.0f, 1.0f) * random::get(0.0f, 1.0f));
					primitives.push_back(std::make_unique<sphere>(center, 0.2f, std::make_unique<lambertian>(c)));
				} else if (choose_mat < 0.95f) { // metal
					vec3 c((1.0f + random::get(0.0f, 1.0f)) * 0.5f, (1.0f + random::get(0.0f, 1.0f)) * 0.5f, (1.0f + random::get(0.0f, 1.0f)) * 0.5f);
					primitives.push_back(std::make_unique<sphere>(center, 0.2f, std::make_unique<metal>(c, 0.5f * random::get(0.0f, 1.0f))));
				} else {  // glass
					primitives.push_back(std::make_unique<sphere>(center, 0.2f, std::make_unique<dieletric>(1.5f)));
				}
			}
		}
	}

	primitives.push_back(std::make_unique<sphere>(vec3(0.0f, 1.0f, 0.0f), 1.0f, std::make_unique<dieletric>(1.5f)));
	primitives.push_back(std::make_unique<sphere>(vec3(-4.0f, 1.0f, 0.0f), 1.0f, std::make_unique<lambertian>(vec3(0.4f, 0.2f, 0.1f))));
	primitives.push_back(std::make_unique<sphere>(vec3(4.0f, 1.0f, 0.0f), 1.0f, std::make_unique<metal>(vec3(0.7f, 0.6f, 0.5f), 0.0f)));
}

void main() {
	int32_t nx = 1200;
	int32_t ny = 800;
	int32_t ns = 50;

	std::vector<std::unique_ptr<primitive>> primitives;
	//primitives.push_back(std::make_unique<sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f, std::make_unique<lambertian>(vec3(0.1f, 0.2f, 0.5f))));
	//primitives.push_back(std::make_unique<sphere>(vec3(1.0f, 0.0f, -1.0f), 0.5f, std::make_unique<metal>(vec3(0.8f, 0.6f, 0.2f), 0.3f)));
	//primitives.push_back(std::make_unique<sphere>(vec3(-1.0f, 0.0f, -1.0f), 0.5f, std::make_unique<metal>(vec3(0.8f, 0.8f, 0.8f), 1.0f)));
	//primitives.push_back(std::make_unique<sphere>(vec3(-1.0f, 0.0f, -1.0f), 0.5f, std::make_unique<dieletric>(1.5f)));
	//primitives.push_back(std::make_unique<sphere>(vec3(-1.0f, 0.0f, -1.0f), -0.45f, std::make_unique<dieletric>(1.5f)));
	//primitives.push_back(std::make_unique<sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f, std::make_unique<lambertian>(vec3(0.8f, 0.8f, 0.0f))));
	create_random_scene(primitives);

	vec3 lookfrom(13.0f, 2.0f, 3.0f);
	vec3 lookat(0.0f, 0.0f, 0.0f);
	camera mainCamera(lookfrom, lookat, vec3(0.0f, 1.0f, 0.0f), 20.0f, float(nx) / float(ny), 0.1f, 10.0f);
	
#ifndef NDEBUG
	int64_t t0 = GetTime();
#endif

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
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

#ifndef NDEBUG
	int64_t t1 = GetTime();
	float elapsed = ((float)(t1 - t0) / (float)GetFrequency()) * 1000.0f;
	std::cerr << elapsed << std::endl;
#endif
}
