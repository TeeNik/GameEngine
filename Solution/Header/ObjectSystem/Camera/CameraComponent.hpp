#pragma once
#include "ObjectSystem/Component.hpp"
#include "Math/Math.h"

class CameraComponent : public Component {
public:
	CameraComponent(Actor* o);

protected:
	void SetViewMatrix(const Matrix4& view);

};