#pragma once
#include "Game.h"
#include "MeshActor.h"
#include "MusicSample.h"
#include "Duck.h"
#include "Ball.h"

class DuckHuntGame : public Game
{
	MeshActor* background;
	MusicSample* music;

	// Ball
	Ball* ball;
	MeshActor* floor;

public:
	DuckHuntGame();

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
};