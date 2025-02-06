#pragma once
#include "Singleton.h"
#include "Actor.h"

class CollisionComponent;

class ActorManager : public Singleton<ActorManager>
{
	set<Actor*> allActors;
	multimap<string, Actor*> actorsID;
	set<CollisionComponent*> AllcollisionComponents;

public:
	FORCEINLINE set<Actor*> GetAllActors() const
	{
		return allActors;
	}
	FORCEINLINE void AddActor(Actor* _actor)
	{
		allActors.insert(_actor);
		actorsID.insert({ _actor->GetName(), _actor });
		_actor->BeginPlay();
	}
	FORCEINLINE void RemoveActor(Actor* _actor)
	{
		allActors.erase(_actor);

		const string& _actorName = _actor->GetName();
		using Iterator = multimap<string, Actor*>::iterator;
		pair<Iterator, Iterator> _results = actorsID.equal_range(_actorName);

		for (Iterator _it = _results.first; _it != _results.second; )
		{
			if (_it->second == _actor)
			{
				_it = actorsID.erase(_it);
			}
			else
			{
				++_it;
			}
		}

		_actor->BeginDestroy();
	}

	FORCEINLINE string GetAvailableName(const string& _name, const int _index = 1)
	{
		// Je rajoute "_index" au nom actuel
		const string& _fullName = _name + (_index == 0 ? "" : "_" + to_string(_index));

		// Je parcours tous les Actors qui possèdent le même nom 
		using Iterator = multimap<string, Actor*>::iterator;
		const pair<Iterator, Iterator>& _results = actorsID.equal_range(_name);
		if (actorsID.empty() || _results.first == _results.second) return _name;
		bool _isFindSameName = false;
		for (Iterator _it = _results.first; _it != _results.second; ++_it)
		{
			// Si c'est le même
			if (_it->second->GetDisplayName() == _fullName)
			{
				_isFindSameName = true;
				break;
			}
		}
		if (!_isFindSameName)
		{
			// Si aucun n'a le même nom, ce sera son nom
			return _fullName;
		}
		// Je reteste avec l'index suivant
		return GetAvailableName(_name, _index + 1);
	}

	FORCEINLINE void AddCollisionComponent(CollisionComponent* _component)
	{
		AllcollisionComponents.insert(_component);
	}

	FORCEINLINE void RemoveColiisionComponents(CollisionComponent* _component)
	{
		AllcollisionComponents.erase(_component);
	}

	FORCEINLINE set<CollisionComponent*> GetAllCollisionComponents() const
	{
		return AllcollisionComponents;
	}

public:
	~ActorManager();

	void BeginPlay();
	void Tick(const float _deltaTime);
	void BeginDestroy();
};