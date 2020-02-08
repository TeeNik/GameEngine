#include "ObjectSystem\Component.hpp"
#include "ObjectSystem\Actor.hpp"

Component::Component(Actor* o, int updateOrd) : owner(o), updateOrder(updateOrd) 
{
	owner->AddComponent(this); 
}