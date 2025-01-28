#pragma once
#include "Component.h"

class MovementComponent : public Component
{ 
	float speed;
	float rotateSpeed;

	// A Remove
	Actor* target;

public:
	FORCEINLINE float GetSpeed() const
	{
		return speed;
	}

	FORCEINLINE void SetRotateSpeed(const float _rotateSpeed)
	{
		rotateSpeed = _rotateSpeed;
	}
	FORCEINLINE void SetTarget(Actor* _target)
	{
		target = _target;
	}
	FORCEINLINE void SetSpeed(const float _speed)
	{
		speed = _speed;
	}

	
public:
	MovementComponent(Actor* _owner);
	MovementComponent(Actor* _owner, const MovementComponent* _other);

protected:
	virtual void Tick(const float _deltaTime) override;

public:
	void Move(const Vector2f& _direction, const float _deltaTime);

	// A Remove
	void RotateAround(const float _deltaTime);
};