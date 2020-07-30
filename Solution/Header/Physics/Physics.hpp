#pragma once
#include <vector>
#include <functional>
#include "Math/Math.h"

class Engine;
class BoxComponent;
class Actor;
struct LineSegment;

struct CollisionInfo
{
	Vector3 point;
	Vector3 normal;
	BoxComponent* box;
	Actor* actor;
};

class Physics
{
public:
	Physics(Engine* engine);
	~Physics();

	void AddBox(BoxComponent* box);
	void RemoveBox(BoxComponent* box);

	bool SegmentCast(const LineSegment& l, CollisionInfo& outCol);
	void TestPairwise(std::function<void(Actor*, Actor*)> func);
	void TestSweepAndPrune(std::function<void(Actor*, Actor*)> func);

private:
	std::vector<BoxComponent*> boxes;
	Engine* engine;
};