#include "Spike.h"
Spike::Spike(const RectangleShapeData& _data, const string& _name) : MeshActor(_data, _name)
{
	collision = new MeshActor(_data, _name);
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

void Spike::SetCollision(const Vector2f& _position)
{
	collision->SetScale(Vector2f(0.33f, 0.33f));
	collision->SetPosition(GetPosition() + (Vector2f(50.0f,50.0f) *0.33f));

	AddChild(collision, AT_SNAP_TO_TARGET);
}
