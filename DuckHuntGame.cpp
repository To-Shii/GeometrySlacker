#include "DuckHuntGame.h"
#include "Level.h"
#include "TimerManager.h"
#include "AudioManager.h"
#include "CameraManager.h"

DuckHuntGame::DuckHuntGame() : Game()
{
	background = nullptr;
    music = nullptr;
	floor = nullptr;
	ball = nullptr;
}


void DuckHuntGame::Start()
{
	Super::Start();

    Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(463.0f, 260.0f) * 2.0f, "background", JPG)));
    music = M_AUDIO.PlaySample<MusicSample>("Crab_Rave", MP3, seconds(50.0f));

    const Vector2f& _floorSize = Vector2f(window.getSize().x, window.getSize().y * 0.2f);
    floor = Level::SpawnActor(MeshActor(RectangleShapeData(_floorSize, "Floor", PNG, true)));
    const float _posX = 0.0f;
    const float _posY = window.getSize().y * 0.8f;
    floor->SetPosition(Vector2f(_posX, _posY));
    floor->SetTextureRect(IntRect(Vector2i(), Vector2i(512 * 3, 512)));

    ball = Level::SpawnActor(Ball(50.0f));
    ball->SetOriginAtMiddle();
    ball->SetPosition(Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.2f));
    
    ////TODO check
    //if (MovementComponent* _movement = duck->GetComponent<MovementComponent>())
    //{
    //    _movement->SetTarget(_target);
    //}
}

bool DuckHuntGame::Update()
{
	Super::Update();

    Shape* _ballShape = ball->GetMesh()->GetShape()->GetDrawable();
    const FloatRect& _ballRect = _ballShape->getGlobalBounds();

    Shape* _floorShape = floor->GetMesh()->GetShape()->GetDrawable();
    const FloatRect& _floorRect = _floorShape->getGlobalBounds();

    if (_ballRect.findIntersection(_floorRect))
    {
        const Vector2f& _normal = Vector2f(0.0f, -1.0f);
        ball->ApplyBounce(_normal);
    }

    return IsOver();
}

void DuckHuntGame::Stop()
{
	Super::Stop();
}