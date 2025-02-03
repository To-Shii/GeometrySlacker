#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Actor* _owner) : Component(_owner)
{
	type = CT_NONE;

}

CollisionComponent::CollisionComponent(Actor* _owner, const CollisionComponent* _other)
	: Component(_owner)
{
	layer = _other->layer;
	type = _other->type;
}

void CollisionComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);



}

void CollisionComponent::OnCollide(Vector2f& _velocity)
{
	if (type == CT_NONE) return;
	if (type == CT_BLOCK)
	{
		_velocity.y -= _velocity.y;
	}
}
