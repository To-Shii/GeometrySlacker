#pragma once
#include "MeshActor.h"
#include "CollisionComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Player : public MeshActor
{
	Vector2f startPosition;
	float size;
	Vector2f position;

	Timer<Seconds>* rotationTimer;
	int targetRotation;

	CollisionComponent* collisionComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animation;

	bool canJump;

public:
	Player(const float _size, const string& _path = "");
	Player(const Player& _other);

public:
	virtual void Construct() override;

	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	void OnCollision(const Vector2f& _normal);
	void Death();
	void SetupAnimation();


private:
	void Jump();
	void SelfRotate(const int _degrees = 90);
	void RotateInAir();
	
};