#include "Physics/Collision.hpp"
#include <algorithm>
#include <array>

LineSegment::LineSegment(const Vector3& start, const Vector3& end) : start(start), end(end)
{
}

Vector3 LineSegment::PointOnSegment(float t) const
{
	return start + (end - start) * t;
}

float LineSegment::MinDistSq(const Vector3& point) const
{
	// Construct vectors
	Vector3 ab = end - start;
	Vector3 ba = -1.0f * ab;
	Vector3 ac = point - start;
	Vector3 bc = point - end;

	// Case 1: C projects prior to A
	if (Vector3::Dot(ab, ac) < 0.0f)
	{
		return ac.LengthSq();
	}
	// Case 2: C projects after B
	else if (Vector3::Dot(ba, bc) < 0.0f)
	{
		return bc.LengthSq();
	}
	// Case 3: C projects onto line
	else
	{
		// Compute p
		float scalar = Vector3::Dot(ac, ab)
			/ Vector3::Dot(ab, ab);
		Vector3 p = scalar * ab;
		// Compute length squared of ac - p
		return (ac - p).LengthSq();
	}
}

float LineSegment::MinDistSq(const LineSegment& s1, const LineSegment& s2)
{
	Vector3   u = s1.end - s1.start;
	Vector3   v = s2.end - s2.start;
	Vector3   w = s1.start - s2.start;
	float    a = Vector3::Dot(u, u);         // always >= 0
	float    b = Vector3::Dot(u, v);
	float    c = Vector3::Dot(v, v);         // always >= 0
	float    d = Vector3::Dot(u, w);
	float    e = Vector3::Dot(v, w);
	float    D = a * c - b * b;        // always >= 0
	float    sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
	float    tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

								   // compute the line parameters of the two closest points
	if (Math::NearZero(D)) { // the lines are almost parallel
		sN = 0.0;         // force using point P0 on segment S1
		sD = 1.0;         // to prevent possible division by 0.0 later
		tN = e;
		tD = c;
	}
	else {                 // get the closest points on the infinite lines
		sN = (b * e - c * d);
		tN = (a * e - b * d);
		if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d < 0.0)
			sN = 0.0;
		else if (-d > a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) < 0.0)
			sN = 0;
		else if ((-d + b) > a)
			sN = sD;
		else {
			sN = (-d + b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (Math::NearZero(sN) ? 0.0f : sN / sD);
	tc = (Math::NearZero(tN) ? 0.0f : tN / tD);

	// get the difference of the two closest points
	Vector3   dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

	return dP.LengthSq();   // return the closest distance squared
}

Plane::Plane(const Vector3& normal, float d)
	:normal(normal)
	, d(d)
{
}

Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c)
{
	// Compute vectors from a to b and a to c
	Vector3 ab = b - a;
	Vector3 ac = c - a;
	// Cross product and normalize to get normal
	normal = Vector3::Cross(ab, ac);
	normal.Normalize();
	// d = -P dot n
	d = -Vector3::Dot(a, normal);
}

float Plane::SignedDist(const Vector3& point) const
{
	return Vector3::Dot(point, normal) - d;
}

Sphere::Sphere(const Vector3& center, float radius)
	:center(center)
	, radius(radius)
{
}

bool Sphere::Contains(const Vector3& point) const
{
	// Get distance squared between center and point
	float distSq = (center - point).LengthSq();
	return distSq <= (radius * radius);
}

AABB::AABB(const Vector3& min, const Vector3& max)
	: min(min)
	, max(max)
{
}

void AABB::UpdateMinMax(const Vector3& point)
{
	// Update each component separately
	min.x = Math::Min(min.x, point.x);
	min.y = Math::Min(min.y, point.y);
	min.z = Math::Min(min.z, point.z);

	max.x = Math::Max(max.x, point.x);
	max.y = Math::Max(max.y, point.y);
	max.z = Math::Max(max.z, point.z);
}

void AABB::Rotate(const Quaternion& q)
{
	// Construct the 8 points for the corners of the box
	std::array<Vector3, 8> points;
	// Min point is always a corner
	points[0] = min;
	// Permutations with 2 min and 1 max
	points[1] = Vector3(max.x, min.y, min.z);
	points[2] = Vector3(min.x, max.y, min.z);
	points[3] = Vector3(min.x, min.y, max.z);
	// Permutations with 2 max and 1 min
	points[4] = Vector3(min.x, max.y, max.z);
	points[5] = Vector3(max.x, min.y, max.z);
	points[6] = Vector3(max.x, max.y, min.z);
	// Max point corner
	points[7] = Vector3(max);

	// Rotate first point
	Vector3 p = Vector3::Transform(points[0], q);
	// Reset min/max to first point rotated
	min = p;
	max = p;
	// Update min/max based on remaining points, rotated
	for (size_t i = 1; i < points.size(); i++)
	{
		p = Vector3::Transform(points[i], q);
		UpdateMinMax(p);
	}
}

bool AABB::Contains(const Vector3& point) const
{
	bool outside = point.x < min.x ||
		point.y < min.y ||
		point.z < min.z ||
		point.x > max.x ||
		point.y > max.y ||
		point.z > max.z;
	// If none of these are true, the point is inside the box
	return !outside;
}

float AABB::MinDistSq(const Vector3& point) const
{
	// Compute differences for each axis
	float dx = Math::Max(min.x - point.x, 0.0f);
	dx = Math::Max(dx, point.x - max.x);
	float dy = Math::Max(min.y - point.y, 0.0f);
	dy = Math::Max(dy, point.y - max.y);
	float dz = Math::Max(min.z - point.z, 0.0f);
	dz = Math::Max(dy, point.z - max.z);
	// Distance squared formula
	return dx * dx + dy * dy + dz * dz;
}

Capsule::Capsule(const Vector3& start, const Vector3& end, float radius)
	:segment(start, end)
	, radius(radius)
{
}

Vector3 Capsule::PointOnSegment(float t) const
{
	return segment.PointOnSegment(t);
}

bool Capsule::Contains(const Vector3& point) const
{
	// Get minimal dist. sq. between point and line segment
	float distSq = segment.MinDistSq(point);
	return distSq <= (radius * radius);
}

bool ConvexPolygon::Contains(const Vector2& point) const
{
	float sum = 0.0f;
	Vector2 a, b;
	for (size_t i = 0; i < vertices.size() - 1; i++)
	{
		// From point to first vertex
		a = vertices[i] - point;
		a.Normalize();
		// From point to second vertex
		b = vertices[i + 1] - point;
		b.Normalize();
		// Add angle to sum
		sum += Math::Acos(Vector2::Dot(a, b));
	}
	// Have to add angle for last vertex and first vertex
	a = vertices.back() - point;
	a.Normalize();
	b = vertices.front() - point;
	b.Normalize();
	sum += Math::Acos(Vector2::Dot(a, b));
	// Return true if approximately 2pi
	return Math::NearZero(sum - Math::TwoPi);
}

bool Intersect(const Sphere& a, const Sphere& b)
{
	float distSq = (a.center - b.center).LengthSq();
	float sumRadii = a.radius + b.radius;
	return distSq <= (sumRadii * sumRadii);
}

bool Intersect(const AABB& a, const AABB& b)
{
	bool no = a.max.x < b.min.x ||
		a.max.y < b.min.y ||
		a.max.z < b.min.z ||
		b.max.x < a.min.x ||
		b.max.y < a.min.y ||
		b.max.z < a.min.z;
	// If none of these are true, they must intersect
	return !no;
}

bool Intersect(const Capsule& a, const Capsule& b)
{
	float distSq = LineSegment::MinDistSq(a.segment,
		b.segment);
	float sumRadii = a.radius + b.radius;
	return distSq <= (sumRadii * sumRadii);
}

bool Intersect(const Sphere& s, const AABB& box)
{
	float distSq = box.MinDistSq(s.center);
	return distSq <= (s.radius * s.radius);
}

bool Intersect(const LineSegment& l, const Sphere& s, float& outT)
{
	// Compute X, Y, a, b, c as per equations
	Vector3 X = l.start - s.center;
	Vector3 Y = l.end - l.start;
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float c = Vector3::Dot(X, X) - s.radius * s.radius;
	// Compute discriminant
	float disc = b * b - 4.0f * a * c;
	if (disc < 0.0f)
	{
		return false;
	}
	else
	{
		disc = Math::Sqrt(disc);
		// Compute min and max solutions of t
		float tMin = (-b - disc) / (2.0f * a);
		float tMax = (-b + disc) / (2.0f * a);
		// Check whether either t is within bounds of segment
		if (tMin >= 0.0f && tMin <= 1.0f)
		{
			outT = tMin;
			return true;
		}
		else if (tMax >= 0.0f && tMax <= 1.0f)
		{
			outT = tMax;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Intersect(const LineSegment& l, const Plane& p, float& outT)
{
	// First test if there's a solution for t
	float denom = Vector3::Dot(l.end - l.start,
		p.normal);
	if (Math::NearZero(denom))
	{
		// The only way they intersect is if start
		// is a point on the plane (P dot N) == d
		if (Math::NearZero(Vector3::Dot(l.start, p.normal)
			- p.d))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float numer = -Vector3::Dot(l.start, p.normal) -
			p.d;
		outT = numer / denom;
		// Validate t is within bounds of the line segment
		if (outT >= 0.0f && outT <= 1.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool TestSidePlane(float start, float end, float negd, const Vector3& norm,
	std::vector<std::pair<float, Vector3>>& out)
{
	float denom = end - start;
	if (Math::NearZero(denom))
	{
		return false;
	}
	else
	{
		float numer = -start + negd;
		float t = numer / denom;
		// Test that t is within bounds
		if (t >= 0.0f && t <= 1.0f)
		{
			out.emplace_back(t, norm);
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Intersect(const LineSegment& l, const AABB& b, float& outT,
	Vector3& outNorm)
{
	// Vector to save all possible t values, and normals for those sides
	std::vector<std::pair<float, Vector3>> tValues;
	// Test the x planes
	TestSidePlane(l.start.x, l.end.x, b.min.x, Vector3::NegUnitX,
		tValues);
	TestSidePlane(l.start.x, l.end.x, b.max.x, Vector3::UnitX,
		tValues);
	// Test the y planes
	TestSidePlane(l.start.y, l.end.y, b.min.y, Vector3::NegUnitY,
		tValues);
	TestSidePlane(l.start.y, l.end.y, b.max.y, Vector3::UnitY,
		tValues);
	// Test the z planes
	TestSidePlane(l.start.z, l.end.z, b.min.z, Vector3::NegUnitZ,
		tValues);
	TestSidePlane(l.start.z, l.end.z, b.max.z, Vector3::UnitZ,
		tValues);

	// Sort the t values in ascending order
	std::sort(tValues.begin(), tValues.end(), [](
		const std::pair<float, Vector3>& a,
		const std::pair<float, Vector3>& b) {
			return a.first < b.first;
		});
	// Test if the box contains any of these points of intersection
	Vector3 point;
	for (auto& t : tValues)
	{
		point = l.PointOnSegment(t.first);
		if (b.Contains(point))
		{
			outT = t.first;
			outNorm = t.second;
			return true;
		}
	}

	//None of the intersections are within bounds of box
	return false;
}

bool SweptSphere(const Sphere& P0, const Sphere& P1,
	const Sphere& Q0, const Sphere& Q1, float& outT)
{
	// Compute X, Y, a, b, and c
	Vector3 X = P0.center - Q0.center;
	Vector3 Y = P1.center - P0.center -
		(Q1.center - Q0.center);
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float sumRadii = P0.radius + Q0.radius;
	float c = Vector3::Dot(X, X) - sumRadii * sumRadii;
	// Solve discriminant
	float disc = b * b - 4.0f * a * c;
	if (disc < 0.0f)
	{
		return false;
	}
	else
	{
		disc = Math::Sqrt(disc);
		// We only care about the smaller solution
		outT = (-b - disc) / (2.0f * a);
		if (outT >= 0.0f && outT <= 0.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}