#include "Wall.h"
#include "Player.h"

Wall::Wall(const Vector2f& _size, const string& _path) : MeshActor(RectangleShapeData(_size, _path))
{
    collisionComponent = CreateComponent<CollisionComponent>("Block", IS_ALL, CT_OVERLAP);
    SetLayer(Layer::LayerType::WORLD_STATIC);

    vector<pair<string, CollisionType>> _responsesPlayer = { {"Floor", CT_BLOCK}, {"Spike", CT_BLOCK}, {"Player", CT_OVERLAP} };
    collisionComponent->AddResponses(_responsesPlayer);
}

Wall::Wall(const Wall& _other) : MeshActor(_other)
{
    collisionComponent = CreateComponent<CollisionComponent>(*_other.collisionComponent);
    SetLayer(_other.GetLayer());
}

void Wall::CollisionEnter(const CollisionData& _data)
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

void Wall::CollisionUpdate(const CollisionData& _data)
{
    if (_data.response == CT_OVERLAP)
    {
        if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
        {

        }
    }
}

void Wall::CollisionExit(const CollisionData& _data)
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
