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
	Spike(const RectangleShapeData& _data, const string& _name);
	~Spike();
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
};
