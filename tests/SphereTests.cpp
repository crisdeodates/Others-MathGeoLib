#include "../src/Math/myassert.h"
#include "../src/MathGeoLib.h"
#include "../tests/TestRunner.h"
#include "../tests/TestData.h"

MATH_IGNORE_UNUSED_VARS_WARNING

using namespace TestData;

static Sphere s(vec(1.f,2.f,3.f, 1.f), 5.f);

BENCHMARK(Sphere_RandomPointOnSurface, "Sphere::RandomPointOnSurface")
{
	v[i] = s.RandomPointOnSurface(rng);
}
BENCHMARK_END;
 
// Implement an alternative method for generating a random point on the surface of a Sphere that uses
// a closed formula for uniform geometric distribution instead of rejection sampling, which Sphere::RandomPointOnSurface uses.
// See here: http://mathworld.wolfram.com/SpherePointPicking.html
vec Sphere_RandomPointOnSurface2(const Sphere &s, LCG &lcg)
{
	float a = lcg.Float(0.f, 2.f*pi);
	float i = Acos(lcg.Float(-1.f, 1.f));
	vec v;
	v.SetFromSphericalCoordinates(a, i);
	return s.pos + v * s.r;
}

// Which version is faster? Rejection sampling or closed formula?
// On Macbook Air 2012 model running Win7:
// Benchmark 'Sphere_RandomPointOnSurface': Sphere::RandomPointOnSurface
//    Best: 89.146 nsecs / 151.97 ticks, Avg: 98.525 nsecs, Worst: 163.836 nsecs
// Benchmark 'Sphere_RandomPointOnSurface_ClosedFormula': Sphere_RandomPointOnSurface_ClosedFormula
//    Best: 369.836 nsecs / 629.126 ticks, Avg: 403.007 nsecs, Worst: 535.479 nsecs
BENCHMARK(Sphere_RandomPointOnSurface_ClosedFormula, "Sphere_RandomPointOnSurface_ClosedFormula")
{
	v[i] = Sphere_RandomPointOnSurface2(s, rng);
}
BENCHMARK_END;
