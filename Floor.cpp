#include "Floor.h"
#include "Player.h"

Floor::Floor(const Vector2f& _size, const string& _path) : MeshActor(RectangleShapeData(_size, _path))
{
    collisionComponent = CreateComponent<CollisionComponent>("Floor", IS_ALL, CT_OVERLAP);
    SetLayer(Layer::LayerType::WORLD_STATIC);

    vector<pair<string, CollisionType>> _responsesPlayer = { {"Block", CT_BLOCK}, {"Spike", CT_BLOCK}, {"Player", CT_OVERLAP} };
    collisionComponent->AddResponses(_responsesPlayer);
}

Floor::Floor(const Floor& _other) : MeshActor(_other)
{
    collisionComponent = CreateComponent<CollisionComponent>(*_other.collisionComponent);
    SetLayer(_other.GetLayer());
}

void Floor::CollisionEnter(const CollisionData& _data)
{
    if (_data.response == CT_OVERLAP)
    {
        if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
        {
            Player* _player = Cast<Player>(_data.other);
            if (_player)
            {
                _player->SetCanJump(true);
            }
        }
    }
}

void Floor::CollisionUpdate(const CollisionData& _data)
{
    if (_data.response == CT_OVERLAP)
    {
        if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
        {
            
        }
    }
}

void Floor::CollisionExit(const CollisionData& _data)
{
    if (_data.response == CT_OVERLAP)
    {
        if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
        {
            Player* _player = Cast<Player>(_data.other);
            if (_player)
            {
                _player->GetComponent<MovementComponent>()->SetIsGrounded(false);
            }
        }
    }
}