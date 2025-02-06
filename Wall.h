#pragma once
#include "MeshActor.h"
#include "CollisionComponent.h"

class Wall : public MeshActor
{
	CollisionComponent* collisionComponent;

public:
	Wall(const Vector2f& _size, const string& _path);
	Wall(const Wall& _other);

	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;
};

