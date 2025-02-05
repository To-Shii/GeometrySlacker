#include "CollisionComponent.h"
#include "ActorManager.h"

CollisionStep CollisionComponent::ComputeOthersStep(Actor* _other, const CollisionStep& _step)
{
	if (othersStep.contains(_other) && othersStep[_other] == CS_ENTER || othersStep[_other] == CS_UPDATE)
	{
		othersStep[_other] = CS_UPDATE;
	}
	else
	{
		othersStep[_other] = _step;
	}
	return othersStep[_other];

}

CollisionComponent::CollisionComponent(Actor* _owner, string _channelName, int _status, CollisionType _type) : Component(_owner)
{
	channelName = _channelName;
	type = _type;
	status = _status;
}

CollisionComponent::CollisionComponent(Actor* _owner, const CollisionComponent& _other) : Component(_owner)
{
	channelName = _other.channelName;
	type = _other.type;
	status = _other.status;
	responses = _other.responses;
}

void CollisionComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	CheckCollision();
}

void CollisionComponent::CheckCollision()
{
	if (!(status & IS_PHYSIC)) return;

	const set<Actor*>& _allActors = M_ACTOR.GetAllActors();
	const FloatRect& _ownerRect = Cast<MeshActor>(owner)->GetHitbox();

	for (Actor* _other : _allActors)
	{
		if (CollisionComponent* _otherCollision = _other->GetComponent<CollisionComponent>())
		{
			const string& _otherName = _otherCollision->GetChannelName();
			if (!responses.contains(_otherName)) continue;

			const CollisionType& _response = responses.at(_otherName);
			if (_response == CT_NONE) continue;

			const FloatRect& _otherRect = Cast<MeshActor>(_other)->GetHitbox();
			if (const optional<FloatRect> _intersection = _ownerRect.findIntersection(_otherRect))
			{
				const CollisionData& _data = { _other, _response, *_intersection, ComputeOthersStep(_other, CS_ENTER) };
				if (_data.step == CS_ENTER)
				{
					owner->CollisionEnter(_data);
					_other->CollisionEnter(_data);
					continue;
				}
				else if (_data.step == CS_UPDATE)
				{
					owner->CollisionUpdate(_data);
					_other->CollisionUpdate(_data);
					continue;
				}
			}
			else
			{
				if (othersStep.contains(_other))
				{
					const CollisionData& _data = { _other, _response, {}, ComputeOthersStep(_other, CS_EXIT) };
					owner->CollisionExit(_data);
					_other->CollisionExit(_data);
					othersStep.erase(_other);
				}
			}
		}
	}
}
