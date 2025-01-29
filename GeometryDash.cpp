#include "GeometryDash.h"
#include "Level.h"
#include "TimerManager.h"
#include "AudioManager.h"
#include "CameraManager.h"
#include "MovementComponent.h"

GeometryDash::GeometryDash() : Game()
{
    background = nullptr;
    music = nullptr;
    player = nullptr;

    collidable = vector<MeshActor*>();
}


void GeometryDash::Start()
{
    Super::Start();

    //Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(463.0f, 260.0f) * 2.0f, "background", JPG)));

    const Vector2f& _floorSize = Vector2f(window.getSize().x, window.getSize().y * 0.2f);
    MeshActor* floor = Level::SpawnActor(MeshActor(RectangleShapeData(_floorSize, "Floor", PNG, true)));
    const float _posX = 0.0f;
    const float _posY = window.getSize().y * 0.8f;
    floor->SetPosition(Vector2f(_posX, _posY));
    floor->SetTextureRect(IntRect(Vector2i(), Vector2i(512 * 3, 512)));

    
    player = Level::SpawnActor(Player(50.0f, "block"));
    player->SetPosition(Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.5f));

    const Vector2f& _wallSize = Vector2f(window.getSize().x * 0.2f, window.getSize().y);
    MeshActor* wall = Level::SpawnActor(MeshActor(RectangleShapeData(_wallSize)));
    wall->SetPosition(Vector2f(window.getSize().x * 0.8f, 0.0f));

    MeshActor* wall2 = Level::SpawnActor(MeshActor(RectangleShapeData(_wallSize)));
    wall2->SetPosition(Vector2f(0.0f, 0.0f));

    MeshActor* wall3 = Level::SpawnActor(MeshActor(RectangleShapeData(_floorSize)));
    wall3->SetPosition(Vector2f(0.0f, 0.0f));

    collidable.push_back(floor);
    collidable.push_back(wall);
    collidable.push_back(wall2);
    collidable.push_back(wall3);
}

bool GeometryDash::Update()
{
    Super::Update();

    Shape* _playerShape = player->GetMesh()->GetShape()->GetDrawable();
    const FloatRect& _playerRect = _playerShape->getGlobalBounds();


    for (MeshActor* _object : collidable)
    {
        Shape* _objectShape = _object->GetMesh()->GetShape()->GetDrawable();
        const FloatRect& _objectRect = _objectShape->getGlobalBounds();

        if (const optional<FloatRect> _intersection = _playerRect.findIntersection(_objectRect))
        {
            const Vector2f& _normal = ComputeNormal(*_intersection);
            player->OnCollision(_normal);
        }
    }

    

    return IsOver();
}

void GeometryDash::Stop()
{
    Super::Stop();
}