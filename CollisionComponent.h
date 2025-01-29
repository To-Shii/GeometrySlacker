#pragma once
#include "Component.h"

enum CollisionType
{
	CT_NONE,
	CT_OVERLAP,
	CT_BLOCK
};

enum LayerType
{
	LT_STATIC,
	LT_DYNAMIC,

	// =========== \\


};

class CollisionComponent : public Component
{
	LayerType layer;
	CollisionType type;

public:
	FORCEINLINE CollisionType GetCollisionType() const
	{
		return type;
	}
	FORCEINLINE void SetCollisionType(CollisionType _type)
	{
		type = _type;
	}

public:
	CollisionComponent(Actor* _owner);
	CollisionComponent(Actor* _owner, const CollisionComponent* _other);

	virtual void Tick(const float _deltaTime) override;


public:
	void OnCollide(const Vector2f& _normal, Vector2f& _velocity);


};