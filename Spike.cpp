#include "Spike.h"
Spike::Spike(const RectangleShapeData& _data, const string& _name) : MeshActor(_data, _name)
{
	collision = new MeshActor(_data, _name);
	collision->SetScale(Vector2f(0.33f, 0.33f));
	collision->SetPosition(Vector2f(1500.0f + _data.size.x * 0.33f, 820.0f + _data.size.y * 0.33f));

	collisionComponent = CreateComponent<CollisionComponent>("Spike", IS_ALL, CT_OVERLAP);
	vector<pair<string, CollisionType>> _responsesPlayer = { {"Player", CT_BLOCK} };
	collisionComponent->AddResponses(_responsesPlayer);
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