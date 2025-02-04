#pragma once
#include "MeshActor.h"


class Spike : public MeshActor
{
	MeshActor* collision;

public:
	FORCEINLINE MeshActor* GetSpikeCollision() const
	{
		return collision;
	}

public:
	Spike(const RectangleShapeData& _data, const string& _name);
	~Spike();

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

	void SetCollision(const Vector2f& _position);

};

