#pragma once
#include "Component.h"
#include "MeshComponent.h"
#include "MovementComponent.h"

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

enum CollisionLocation
{
	CL_Top,
	CL_Bottom,
	CL_Left,
	CL_Right,

	CL_None
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
	FORCEINLINE void SetCollisionType(const CollisionType& _type)
	{
		type = _type;
	}

public:
	CollisionComponent(Actor* _owner);
	CollisionComponent(Actor* _owner, const CollisionComponent* _other);

	virtual void Tick(const float _deltaTime) override;


public:
	void OnCollide(Vector2f& _velocity);


	template <typename PlayerType, typename CollidableType>
	void CheckCollision(PlayerType _player,const vector<CollidableType>& _collidables, const CollisionLocation& _where, function<void()> _IfCallback, function<void()> _ElseCallback)
	{
		Shape* _playerShape = _player->GetMesh()->GetShape()->GetDrawable();
		const FloatRect& _playerRect = _playerShape->getGlobalBounds();

		const vector<function<bool(const FloatRect&)>> _locationCallback =
		{
			[&](const FloatRect& _objectRect) {
				float _playerBottom = _playerRect.position.y + _playerRect.size.y;
				float _objectTop = _objectRect.position.y;

				return _playerBottom <= _objectTop + 5.0f;
			},

			[&](const FloatRect& _objectRect) {
				return true;
			},

			[&](const FloatRect& _objectRect) {
				return true;
			},

			[&](const FloatRect& _objectRect) {
				return true;
			}
		};


		for (CollidableType _object : _collidables)
		{
			Shape* _objectShape = _object->GetMesh()->GetShape()->GetDrawable();
			const FloatRect& _objectRect = _objectShape->getGlobalBounds();

			if (const optional<FloatRect> _intersection = _playerRect.findIntersection(_objectRect))
			{
				const Vector2f& _normal = ComputeNormal(*_intersection);
				_player->OnCollision(_normal);

				if (_where == CL_None)
				{
					_IfCallback();
					return;
				}

				if (_locationCallback[_where](_objectRect))
				{
					_IfCallback();
				}
				else
				{
					_ElseCallback();
				}
			}
		}
	}
};
