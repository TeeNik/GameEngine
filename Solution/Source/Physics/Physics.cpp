#include "Physics/Physics.hpp"
#include "ObjectSystem/Collision/BoxComponent.hpp"
#include "Physics/Collision.hpp"
#include <algorithm>

Physics::Physics(Engine* e) : engine(e)
{

}

Physics::~Physics()
{

}

void Physics::AddBox(BoxComponent* box)
{
	boxes.emplace_back(box);
}

void Physics::RemoveBox(BoxComponent* box)
{
	auto iter = std::find(boxes.begin(), boxes.end(), box);
	if (iter != boxes.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, boxes.end() - 1);
		boxes.pop_back();
	}
}

bool Physics::SegmentCast(const LineSegment& l, CollisionInfo& outColl)
{
	bool isCollided = false;
	float closestT = Math::Infinity;
	Vector3 normal;
	for (auto box : boxes)
	{
		float t;
		if (Intersect(l, box->GetWorldBox(), t, normal)) 
		{
			if (t < closestT) 
			{
				outColl.point = l.PointOnSegment(t);
				outColl.normal = normal;
				outColl.box = box;
				outColl.actor = box->GetOwner();
				isCollided = true;
			}
		}
	}
	return isCollided;
}

void Physics::TestPairwise(std::function<void(Actor*, Actor*)> func)
{
	for (size_t i = 0; i < boxes.size(); ++i)
	{
		for (size_t j = i + 1; j < boxes.size(); ++j)
		{
			BoxComponent* a = boxes[i];
			BoxComponent* b = boxes[j];
			if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				func(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void Physics::TestSweepAndPrune(std::function<void(Actor*, Actor*)> func)
{
	std::sort(boxes.begin(), boxes.end(),
		[](BoxComponent* a, BoxComponent* b) {
			return a->GetWorldBox().min.x < b->GetWorldBox().min.x;
		});

	for (size_t i = 0; i < boxes.size(); ++i)
	{
		BoxComponent* a = boxes[i];
		float max = a->GetWorldBox().max.x;
		for (size_t j = i + 1; j < boxes.size(); ++j)
		{
			BoxComponent* b = boxes[j];
			if (b->GetWorldBox().min.x > max)
			{
				break;
			}
			if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				func(a->GetOwner(), b->GetOwner());
			}
		}
	}
}
