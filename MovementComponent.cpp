#include "MovementComponent.h"
#include "Actor.h"

MovementComponent::MovementComponent(Actor* _owner) : Component(_owner)
{
	isGrounded = false;
	canMove = true;
	velocity = Vector2f(100.0f, 0.0f);
	speed = 1.0f;
	mass = 80.0f;
	gravity = 9.81f;
}

MovementComponent::MovementComponent(Actor* _owner, const MovementComponent* _other) : Component(_owner)
{
	isGrounded = _other->isGrounded;
	canMove = _other->canMove;
	velocity = _other->velocity;
	mass = _other->mass;
	speed = _other->speed;
	gravity = _other->gravity;
}


void MovementComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	if (!canMove) return;

	// Appliquer la gravité
	if (!isGrounded)
	{
		velocity.y += gravity * mass * _deltaTime;
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
