#include "Spike.h"
#include "Player.h"

Spike::Spike(const RectangleShapeData& _data, const string& _name) : MeshActor(_data, _name)
{
	collisionComponent = CreateComponent<CollisionComponent>("Spike", IS_ALL, CT_OVERLAP);
    SetLayer(Layer::LayerType::WORLD_STATIC);

	vector<pair<string, CollisionType>> _responsesPlayer = { {"Player", CT_BLOCK} };
	collisionComponent->AddResponses(_responsesPlayer);
}

Spike::Spike(const Spike& _other) : MeshActor(_other)
{
    collisionComponent = CreateComponent<CollisionComponent>(*_other.collisionComponent);
    SetLayer(_other.GetLayer());
}

void Spike::BeginPlay()
{
	Super::BeginPlay();
}

void Spike::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void Spike::CollisionEnter(const CollisionData& _data)
{
    if (_data.response == CT_OVERLAP)
    {
        if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
        {
            Player* _player = Cast<Player>(_data.other);
            if (_player)
            {
                _player->SetToDelete();
            }
        }
    }
}

void Spike::CollisionUpdate(const CollisionData& _data)
{

}

void Spike::CollisionExit(const CollisionData& _data)
{

}