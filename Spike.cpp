#include "Spike.h"
Spike::Spike(const RectangleShapeData& _data, const string& _name) : MeshActor(_data, _name)
{
	collision = new MeshActor(_data, _name);
	collision->SetScale(Vector2f(0.33f, 0.33f));
	collision->SetPosition(Vector2f(1500.0f + _data.size.x * 0.33f, 820.0f + _data.size.y * 0.33f));
	AddChild(collision, AT_SNAP_TO_TARGET);
}

Spike::~Spike()
{

}

void Spike::BeginPlay()
{
	Super::BeginPlay();
}

void Spike::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}