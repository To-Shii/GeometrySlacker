#pragma once
#include "MeshActor.h"
#include "CollisionComponent.h"

class Spike : public MeshActor
{
	CollisionComponent* collisionComponent;

public:
	Spike(const RectangleShapeData& _data, const string& _name);
	Spike(const Spike& _other);

	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;
};
