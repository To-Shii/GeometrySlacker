#include "MovementComponent.h"
#include "Actor.h"

MovementComponent::MovementComponent(Actor* _owner) : Component(_owner)
{
	speed = 1.0f;
	rotateSpeed = 30.0f;
	target = nullptr;
}

MovementComponent::MovementComponent(Actor* _owner, const MovementComponent* _other) : Component(_owner)
{
	speed = _other->speed;
	rotateSpeed = _other->rotateSpeed;
	target = _other->target;
}


void MovementComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

}


void MovementComponent::Move(const Vector2f& _direction, const float _deltaTime)
{
	const Vector2f& _offset = _direction * speed * _deltaTime ;
	owner->Move(_offset);
}

// A Remove
void MovementComponent::RotateAround(const float _deltaTime)
{
	if (!target) return;

	const Vector2f& _center = target->GetPosition();
	const Vector2f& _relativePos = owner->GetPosition() - _center;
	const float _radAngle = DegToRad(rotateSpeed * _deltaTime);

	const float _newPosX = _relativePos.x * cos(_radAngle) - _relativePos.y * sin(_radAngle);
	const float _newPosY = _relativePos.x * sin(_radAngle) + _relativePos.y * cos(_radAngle);
	const Vector2f& _newPosition = _center + Vector2f(_newPosX, _newPosY);

	owner->SetPosition(_newPosition);
}