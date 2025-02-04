#pragma once
#include "Component.h"
#include "Kismet.h"

class MovementComponent : public Component
{ 
	bool canMove;
	bool isGrounded;

	Vector2f velocity;
	float mass;
	float speed;
	float gravity;

	set<Actor*> ignoreList;

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
	FORCEINLINE void IgnoreActor(Actor* _actor)
	{
		ignoreList.insert(_actor);
	}

public:
	MovementComponent(Actor* _owner);
	MovementComponent(Actor* _owner, const MovementComponent* _other);

protected:
	virtual void Tick(const float _deltaTime) override;

public:
	void Move(const float _deltaTime);

private:
	void CheckIsGrounded();
};