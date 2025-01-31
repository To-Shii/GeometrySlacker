#pragma once
#include "Component.h"

class MovementComponent : public Component
{ 
	bool canMove;
	bool isGrounded;

	Vector2f velocity;
	float mass;
	float speed;
	float gravity;


public:
	FORCEINLINE Vector2f& GetVelocity()
	{
		return velocity;
	}
	FORCEINLINE void SetIsGrounded(const bool _isGrounded = true)
	{
		isGrounded = _isGrounded;
	}
	FORCEINLINE bool IsGrounded() const
	{
		return isGrounded;
	}
	FORCEINLINE void SetCanMove(const bool _canMove)
	{
		canMove = _canMove;
	}

public:
	MovementComponent(Actor* _owner);
	MovementComponent(Actor* _owner, const MovementComponent* _other);

protected:
	virtual void Tick(const float _deltaTime) override;

public:
	void Move(const float _deltaTime);
};