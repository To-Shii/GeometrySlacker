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
    DeadlyObstacles = vector<MeshActor*>();
}

GeometryDash::~GeometryDash()
{
    for (MeshActor* _mesh : DeadlyObstacles)
    {
        delete _mesh;
    }
}


void GeometryDash::Start()
{
    Super::Start();
    M_CAMERA.CreateCamera("MainCamera");
    //Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(463.0f, 260.0f) * 2.0f, "background", JPG)));

    music = M_AUDIO.PlaySample<MusicSample>("StereoMadness");
    music->SetLoop(true);
    music->SetVolume(10.0f);

    background = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(window.getSize().x, window.getSize().y), "Background", PNG, true)));

    const Vector2f& _floorSize = Vector2f(window.getSize().x, window.getSize().y * 0.2f);
    MeshActor* _floor = Level::SpawnActor(MeshActor(RectangleShapeData(_floorSize, "Floor", PNG, true)));
    const float _posX = 0.0f;
    const float _posY = window.getSize().y * 0.8f;
    _floor->SetPosition(Vector2f(_posX, _posY));
    _floor->SetTextureRect(IntRect(Vector2i(), Vector2i(512 * 3, 512)));

    player = Level::SpawnActor(Player(50.0f, "character"));
    player->SetOriginAtMiddle();
    player->SetPosition(Vector2f(window.getSize().x * 0.2f, window.getSize().y * 0.2f));
    M_CAMERA.GetCurrent()->SetTarget(player);
    M_CAMERA.GetCurrent()->Zoom(1.5f);


    const Vector2f& _wallSize = Vector2f(50.0f, 80.0f);
    MeshActor* _wall = Level::SpawnActor(MeshActor(RectangleShapeData(_wallSize, "Block")));
    _wall->SetPosition(Vector2f(1000.0f, 790.0f));
    MeshActor* _wall2 = Level::SpawnActor(MeshActor(RectangleShapeData(_wallSize, "Block")));
    _wall2->SetPosition(Vector2f(1150.0f, 790.0f));
    MeshActor* _wall3 = Level::SpawnActor(MeshActor(RectangleShapeData(_wallSize, "Block")));
    _wall3->SetPosition(Vector2f(1150.0f, 720.0f));
    Spike* _spike = Level::SpawnActor(Spike(RectangleShapeData(Vector2f(396.0f / 8 , 398.0f  / 7), "spike"), "Spike"));
    _spike->SetPosition(Vector2f(1500.0f, 820.0f));
    
    //MeshActor* _levelComplete = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(window.getSize().x /2, window.getSize().y / 2) * 2.0f, "levelComplete", PNG)));

    collidable.push_back(_floor);
    collidable.push_back(_wall);
    collidable.push_back(_wall2);
    collidable.push_back(_wall3);
    DeadlyObstacles.push_back(_spike->GetSpikeCollision());
    /*collidable.push_back(_wall2);
    collidable.push_back(_wall3);*/

}

bool GeometryDash::Update()
{
    Super::Update();
    CollisionComponent* _collComp = player->GetComponent<CollisionComponent>();

    _collComp->CheckCollision<Player*, MeshActor*>(player, collidable, CL_Top,
        [&](){
            
        },
        [&]() { 
            player->Death();
            music->Stop();
            LOG(Display, "Mort !");
        });

    _collComp->CheckCollision<Player*, MeshActor*>(player, DeadlyObstacles, CL_None,
        [&]() {
            player->Death();
            music->Stop();
            LOG(Display, "Mort !");
        },
        [&]() {
            
        });

    return IsOver();
}

void GeometryDash::Stop()
{
    Super::Stop();
}