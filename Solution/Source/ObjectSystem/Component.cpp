#include "ObjectSystem\Component.hpp"
#include "ObjectSystem\Actor.hpp"

Component::Component(Actor* o) : owner(o), updateOrder(100) 
{
	//owner->AddComponent(this); 
}