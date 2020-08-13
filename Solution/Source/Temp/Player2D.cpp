#include "Temp/Player2D.hpp"
#include "ObjectSystem/SpriteRendererComponent.hpp"
#include "ObjectSystem/AnimSpriteComponent.hpp"
#include "Utils/Utils.hpp"

Player2D::Player2D(Engine * e) : Actor(e)
{
	auto anim = AddComponent<AnimSpriteComponent>();
	//anim->SetTexture(Utils::ContructPath("player.png"));
	anim->SetSourceImage(Utils::ContructPath("girl.png"), 9, 5);
	anim->SetSize(anim->GetSize() * .1f);
}