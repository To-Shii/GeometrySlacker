#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Actor* _owner) : Component(_owner)
{
	type = CT_NONE;

}

void CollisionComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);



}

void CollisionComponent::OnCollide(const Vector2f& _normal, Vector2f& _velocity)
{
	_velocity.y = 0.0f;
}
