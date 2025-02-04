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
    _wall3->SetPosition(Vector2f(1350.0f, 720.0f));
	
    Spike* _spike = Level::SpawnActor(Spike(RectangleShapeData(Vector2f(396.0f / 8 , 398.0f  / 7), "spike"), "Spike"));
    _spike->SetPosition(Vector2f(1800.0f, 820.0f));
    _spike->SetCollision(Vector2f(1800.0f, 820.0f));
    deadlyObstacles.push_back(_spike->GetSpikeCollision());

    //MeshActor* _levelComplete = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(window.getSize().x /2, window.getSize().y / 2) * 2.0f, "levelComplete", PNG)));

    /*collidable.push_back(_floor);
    collidable.push_back(_floor2);
    collidable.push_back(_wall);
    collidable.push_back(_wall2);
    collidable.push_back(_wall3);
    collidable.push_back(_wall2);
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
        });

    return IsOver();
}

void GeometryDash::Stop()
{
    Super::Stop();
}

void GeometryDash::GenerateMusic()
{
    const vector<string>& _allMusic =
    {
        "AirborneRobots",
        "BackOnTrackFull",
        "BaseAfterBaseFull",
        "ClubStepFull",
        "DryOutFull",
        "ElectromanAdventuresFull",
        "FingerbangFull",
        "PayloadFull",
        "PolargeistFull",
        "PressStartFull",
        "SpacePiratesFull",
        "StereoMadness",
        "The7SeasFull",
        "TheoryOfEverything2Full",
        "TimeMachineFull",
        "XStepFull",
    };

    const u_int& _musicIndex = GetRandomNumberInRange(0, CAST(int, _allMusic.size() - 1));

    music = M_AUDIO.PlaySample<MusicSample>(_allMusic[_musicIndex]);
    music->SetLoop(true);
    music->SetVolume(10.0f);
}

void GeometryDash::GenerateMap()
{
    const Vector2f& _floorSize = Vector2f(window.getSize().x * 2, window.getSize().y * 0.5f);
    MeshActor* _floor = Level::SpawnActor(MeshActor(RectangleShapeData(_floorSize, "Floor", PNG, true)));
    const float _posX = 0.0f;
    const float _posY = window.getSize().y * 0.8f;
    _floor->SetPosition(Vector2f(_posX, _posY));
    _floor->SetTextureRect(IntRect(Vector2i(), Vector2i(512 * 3, 512)));

    //GenerateAllWalls();
    //GenerateAllSpikes();

    collidable.push_back(_floor);
    MeshActor* _levelComplete = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(1200.0f, 300.0f), "levelComplete", PNG)));
    _levelComplete->SetPosition(Vector2f(8200.0f, 400.0f));
    //collidable.push_back(_levelComplete);
}


void GeometryDash::GenerateAllSpike(const float _floor)
{
    GenerateSpike(Vector2f(400.0f, _floor + 8.0f));
    GenerateSpike(Vector2f(950.0f, _floor + 8.0f));
    GenerateSpike(Vector2f(1300.0f, _floor + 8.0f));

    GenerateSpike(Vector2f(3350.0f, _floor - 383.0f));
    GenerateSpike(Vector2f(3400.0f, _floor - 383.0f));
    GenerateSpike(Vector2f(3450.0f, _floor - 383.0f));
}

void GeometryDash::GenerateAllLowSpike(const float _floor)
{
    GenerateLowSpike(Vector2f(900.0f, _floor + 8.0f));
    GenerateLowSpike(Vector2f(3300.0f, _floor - 382.0f));
    GenerateLowSpike(Vector2f(3500.0f, _floor - 382.0f));
    float _x = 6845.0f;
    for (u_int _index = 0; _index < 3; _index++)
    {
        GenerateLowSpike(Vector2f(_x, _floor - 68.0f));
        _x += 400.0f;
    }
}

void GeometryDash::GenerateAllLongSpike(const float _floor)
{
    float _posX = 1030.0f;
    for (u_int _index = 0; _index < 5; _index++)
    {
        GenerateLongSpike(Vector2f(_posX, _floor + 8.0f));
        _posX += 49;
    }

    _posX = 2050.0f;
    for (u_int _index = 0; _index < 20; _index++)
    {
        GenerateLongSpike(Vector2f(_posX, _floor + 8.0f));
        _posX += 49;
    }

    _posX = 4500.0f;
    for (u_int _index = 0; _index < 30; _index++)
    {
        GenerateLongSpike(Vector2f(_posX, _floor + 8.0f));
        _posX += 49;
    }
}

void GeometryDash::GenerateAllWall(const float _floor)
{
    float _x = 3000.0f;

    GenerateWall(Vector2f(1000.0f, _floor));
    GenerateWall(Vector2f(1250.0f, _floor));
    GenerateWall(Vector2f(1250.0f, _floor - 50.0f));

    for (u_int i = 0; i < 4; i++)
    {
        GenerateWall(Vector2f(_x, _floor - 278.0f));
        _x += 50.0f;
    }

    _x = 3200.0f;
    for (u_int i = 0; i < 9; i++)
    {
        GenerateWall(Vector2f(_x, _floor - 240.0f));
        _x += 50.0f;
    }

    for (u_int i = 0; i < 4; i++)
    {
        GenerateWall(Vector2f(_x, _floor - 278.0f));
        _x += 50.0f;
    }

    _x = 4925.0f;
    for (u_int i = 0; i < 5; i++)
    {
        GenerateWall(Vector2f(_x, _floor - 280.0f));
        _x += 300.0f;
    }

    _x += 420.0f;
    for (u_int _index = 0; _index < 3; _index++)
    {
        GenerateWall(Vector2f(_x, _floor));
        //GenerateWall(Vector2f(_x, _floor - 175.0f));
        _x += 400.0f;
    }
}

void GeometryDash::GenerateAllLowWall(const float _floor)
{
    float _x = 2000.0f;
    float _y = 40.0f;
    for (u_int i = 0; i < 4; i++)
    {
        GenerateLowWall(Vector2f(_x, _floor - _y));
        _x += 250.0f;
        _y += 80.0f;
    }

    _x = 3300.0f;
    _y = 365.0f;
    for (u_int i = 0; i < 5; i++)
    {
        GenerateLowWall(Vector2f(_x, _floor - _y));
        _x += 50.0f;
    }

    _y = 280.0f;
    _x = 3950.0f;
    for (u_int i = 0; i < 5; i++)
    {
        GenerateLowWall(Vector2f(_x, _floor - _y));
        _x += 150.0f;
        _y -= 40.0f;
    }

    _x += 225.0f;
    for (u_int i = 0; i < 5; i++)
    {
        GenerateLowWall(Vector2f(_x, _floor - _y));
        _x += 300.0f;
    }

    _x += 420.0f;
    for (u_int _index = 0; _index < 3; _index++)
    {
        GenerateLowWall(Vector2f(_x, _floor - 50.0f));
        _x += 400.0f;
    }
}



#pragma region GeneratorSpike

void GeometryDash::GenerateAllSpikes()
{
    const float _floor = (window.getSize().y * 0.8f) - (398.0f / 7);
    GenerateAllSpike(_floor);
    GenerateAllLowSpike(_floor);
    GenerateAllLongSpike(_floor);
}

void GeometryDash::GenerateSpike(const Vector2f& _position)
{
    const Vector2f& _spickSize = Vector2f(50.0f, 50.0f);
    GenerateSpike(_position, _spickSize, "spike");
}

void GeometryDash::GenerateLowSpike(Vector2f _position)
{
    const float _y = 50.0f / 2;
    const Vector2f& _spickSize = Vector2f(50, _y);
    _position.y += _y;
    GenerateSpike(_position, _spickSize, "spike");
}

void GeometryDash::GenerateLongSpike(Vector2f _position)
{
    const Vector2f& _spickSize = Vector2f(50.0f, 50.0f);
    GenerateSpike(_position, _spickSize, "longSpike");
}

void GeometryDash::GenerateSpike(const Vector2f& _position, const Vector2f& _spickSize, const string& _name)
{
    Spike* _spike = Level::SpawnActor(Spike(RectangleShapeData(_spickSize, _name), "Spike"));
    _spike->SetPosition(_position);
    _spike->SetCollision(_position);
    deadlyObstacles.push_back(_spike->GetSpikeCollision());
}

#pragma endregion

#pragma region GeneratorWall

void GeometryDash::GenerateAllWalls()
{
    const float _floor = (window.getSize().y * 0.8f) - 50.0f;
    GenerateAllWall(_floor);
    GenerateAllLowWall(_floor);
}

void GeometryDash::GenerateWall(const Vector2f& _position)
{
    const Vector2f& _spickSize = Vector2f(50.0f, 50.0f);
    GenerateWall(_position, _spickSize, "Block");
}

void GeometryDash::GenerateLowWall(Vector2f _position)
{
    const float _y = 50.0f / 2;
    const Vector2f& _spickSize = Vector2f(50.0f, _y);
    _position.y += _y;
    GenerateWall(_position, _spickSize, "Block");
}

void GeometryDash::GenerateWall(const Vector2f& _position, const Vector2f& _wallSize, const string& _name)
{
    MeshActor* _wall = Level::SpawnActor(MeshActor(RectangleShapeData(_wallSize, _name)));
    _wall->SetPosition(_position);
    collidable.push_back(_wall);
}

#pragma endregion

#pragma endregion
