#include "Physics/Physics.hpp"
#include "ObjectSystem/Collision/BoxComponent.hpp"
#include "Physics/Collision.hpp"
#include <algorithm>
#include "ObjectSystem/Actor.hpp"

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

void Physics::Update(float deltaTime)
{
	TestSweepAndPrune();
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

void Physics::TestSweepAndPrune()
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

			auto aType = a->GetObjectType();
			auto bType = b->GetObjectType();
			if (aType == Static && bType == Dynamic || aType == Dynamic && bType == Static)
			{
				if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
				{
					if (aType == Dynamic) {
						FixCollision(b, a);
					}
					else {
						FixCollision(a, b);
					}
				}
			}
		}
	}
}

/*void Physics::TestSweepAndPrune(std::function<void(Actor*, Actor*)> func)
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
}*/

void Physics::FixCollision(BoxComponent * staticBox, BoxComponent * dynamicBox)
{
	auto sb = staticBox->GetWorldBox();
	auto db = dynamicBox->GetWorldBox();

	float dx1 = sb.max.x - db.min.x;
	float dx2 = sb.min.x - db.max.x;
	float dy1 = sb.max.y - db.min.y;
	float dy2 = sb.min.y - db.max.y;
	float dz1 = sb.max.z - db.min.z;
	float dz2 = sb.min.z - db.max.z;

	// Set dx to whichever of dx1/dx2 have a lower abs
	float dx = Math::Abs(dx1) < Math::Abs(dx2) ?
		dx1 : dx2;
	// Ditto for dy
	float dy = Math::Abs(dy1) < Math::Abs(dy2) ?
		dy1 : dy2;
	// Ditto for dz
	float dz = Math::Abs(dz1) < Math::Abs(dz2) ?
		dz1 : dz2;

	auto pos = dynamicBox->GetOwner()->GetActorPosition();

	// Whichever is closest, adjust x/y position
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		pos.x += dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		pos.y += dy;
	}
	else
	{
		pos.z += dz;
	}

	// Need to set position and update box component
	dynamicBox->GetOwner()->SetActorPosition(pos);
	dynamicBox->Update(0);
}
