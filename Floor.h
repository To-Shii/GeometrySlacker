#pragma once
#include "MeshActor.h"
#include "CollisionComponent.h"

class Floor : public MeshActor
{
	CollisionComponent* collisionComponent;

public:
	Floor(const Vector2f& _size, const string& _path);
	Floor(const Floor& _other);

	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;
};

