#pragma once
#include "MeshActor.h"
#include "CollisionComponent.h"
#include "MovementComponent.h"

class Player : public MeshActor
{
	bool canMove;
	Vector2f startPosition;
	Vector2f velocity;
	float mass;
	float gravity;
	float restitution;

	bool isGrounded;

	CollisionComponent* collisionComponent;
	MovementComponent* movementComponent;

public:
	Player(const float _size, const string& _path = "");


	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	void OnCollision(const optional<FloatRect>& _intersection);
	Vector2f GetNormal(const optional<FloatRect>& _intersection);
};

