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
	vector<MeshActor*> DeadlyObstacles;

	Vector2f spikeSize;
	Vector2f wallSize;
public:
	GeometryDash();

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;

private:
#pragma region Generate
	void GenerateMusic();
	void GenerateMap();
#pragma region Spikes
	void GenerateAllSpikes();
	void GenerateAllSpike(const float _floor);
	void GenerateAllLowSpike(const float _floor);
	void GenerateAllLongSpike(const float _floor);
	void GenerateSpike(const Vector2f& _position);
	void GenerateLowSpike(Vector2f _position);
	void GenerateLongSpike(Vector2f _position);
	void GenerateSpike(const Vector2f& _position, const Vector2f& _spickSize, const string& _name);
#pragma endregion

#pragma region Wall
	void GenerateAllWalls();
	void GenerateAllWall(const float _floor);
	void GenerateAllLowWall(const float _floor);
	void GenerateWall(const Vector2f& _position);
	void GenerateLowWall(Vector2f _position);
	void GenerateWall(const Vector2f& _position, const Vector2f& _wallSize, const string& _name);
#pragma endregion

#pragma endregion
};
