#pragma once
#include "MeshActor.h"
#include "CollisionComponent.h"
#include "MovementComponent.h"

class Player : public MeshActor
{
	Vector2f startPosition;

	CollisionComponent* collisionComponent;
	MovementComponent* movementComponent;

public:
	Player(const float _size, const string& _path = "");
	Player(const Player& _other);

public:
	virtual void Construct() override;

	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	void OnCollision(const Vector2f& _normal);
private:
	void Jump();
};

