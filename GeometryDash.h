#pragma once
#include "Game.h"
#include "MeshActor.h"
#include "MusicSample.h"
#include "Player.h"

class GeometryDash : public Game
{
	MeshActor* background;
	MusicSample* music;

	Player* player;

	vector<MeshActor*> collidable;

public:
	GeometryDash();

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
};
