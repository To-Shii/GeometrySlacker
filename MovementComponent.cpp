#include "MovementComponent.h"
#include "Actor.h"
#include "ActorManager.h"

MovementComponent::MovementComponent(Actor* _owner) : Component(_owner)
{
	isGrounded = false;
	canMove = true;
	velocity = Vector2f(300.0f, 0.0f);
	speed = 1.0f;
	mass = 100.0f;
	gravity = 9.81f;
	IgnoreActor(owner);
}

MovementComponent::MovementComponent(Actor* _owner, const MovementComponent* _other) : Component(_owner)
{
	isGrounded = _other->isGrounded;
	canMove = _other->canMove;
	velocity = _other->velocity;
	mass = _other->mass;
	speed = _other->speed;
	gravity = _other->gravity;

	IgnoreActor(owner);
}

void MovementComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	CheckIsGrounded();
	if (!canMove) return;

	// Appliquer la gravité
	if (!isGrounded)
	{
		velocity.y += gravity * mass * _deltaTime;
	}
	else
	{
		velocity.y = 0;
	}

	// Mettre à jour la position
	Move(_deltaTime);
}

void MovementComponent::Move(const float _deltaTime)
{
	velocity.x *= speed;
	const Vector2f& _offset = velocity * _deltaTime;
	owner->Move(_offset);
}

void MovementComponent::CheckIsGrounded()
{
	HitInfo _info;
	isGrounded = Raycast(owner->GetPosition(), Vector2f(0, 1), 29.0f, _info, ignoreList, 1.0f);
}