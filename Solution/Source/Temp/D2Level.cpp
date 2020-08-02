#include "Temp/D2Level.hpp"
#include "Engine/Engine.hpp"
#include "ObjectSystem/ObjectManager.hpp"
#include "Temp/Player2D.hpp"


D2Level::D2Level(Engine * e) : Level(e)
{
}

void D2Level::Load()
{
	auto ECS = engine->GetObjectManager();
	Player2D* player = ECS->SpawnActor<Player2D>();
}

void D2Level::Unload()
{
}
