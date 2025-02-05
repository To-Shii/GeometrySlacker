#include "GeometryDash.h"
#include "Level.h"
#include "TimerManager.h"
#include "AudioManager.h"
#include "CameraManager.h"
#include "MovementComponent.h"
#include "Player.h"
#include "Floor.h"

GeometryDash::GeometryDash() : Game()
{
    background = nullptr;
    music = nullptr;
    player = nullptr;

    collidable = vector<MeshActor*>();
    deadlyObstacles = vector<MeshActor*>();
}

GeometryDash::~GeometryDash()
{
    for (MeshActor* _mesh : deadlyObstacles)
    {
        delete _mesh;
    }
}

void GeometryDash::Start()
{
    Super::Start();
    M_CAMERA.CreateCamera("MainCamera");

    background = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(1905.0f * 2, 1080.0f), "Background")));
    
    GenerateMusic();
    GenerateMap();

    player = Level::SpawnActor(Player(50.0f, "Marguerite"));
    //player->SetOriginAtMiddle();
    //player->SetPosition(Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.5f));
    player->GetComponent<MovementComponent>()->IgnoreActor(background);

    /*MeshActor* _floor2 = Level::SpawnActor(MeshActor(RectangleShapeData(_floorSize, "Floor", PNG, true)));
    _floor2->SetPosition(Vector2f(_posX + _floorSize.x, _posY));
    _floor2->SetTextureRect(IntRect(Vector2i(), Vector2i(512 * 3, 512)));*/

    M_CAMERA.GetCurrent()->SetTarget(player);
    M_CAMERA.GetCurrent()->Zoom(1.0f);
    M_CAMERA.GetCurrent()->SetScale(Vector2f(1905.0f, 1080.0f));
}

bool GeometryDash::Update()
{
    Super::Update();

    /*CollisionComponent* _collComp = player->GetComponent<CollisionComponent>();

    _collComp->CheckCollision();*/

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
    Floor* _floor = Level::SpawnActor(Floor(_floorSize, "Floor"));
    const float _posX = 0.0f;
    const float _posY = window.getSize().y * 0.8f;
    _floor->SetPosition(Vector2f(_posX, _posY));
    _floor->SetTextureRect(IntRect(Vector2i(), Vector2i(512 * 3, 512)));
    _floor->AddComponent(new CollisionComponent(_floor, "Floor", IS_ALL, CT_BLOCK));

    GenerateAllSpikes();
    GenerateAllWalls();

    //player = Level::SpawnActor(Player(50.0f, "Marguerite"));

    //GenerateAll();

    collidable.push_back(_floor);
    MeshActor* _levelComplete = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(1020.0f, 881.0f), "levelComplete", PNG)));
    _levelComplete->SetPosition(Vector2f(8200.0f, 200.0f));
    //collidable.push_back(_levelComplete);
}

//void GeometryDash::GenerateAll()
//{
//    GenerateAllWalls();
//    GerenerateAllSpike();
//}
//
//void GeometryDash::GenerateAllWalls()
//{
//    const Vector2f& _wallSize = Vector2f(50.0f, 50.0f);
//    const float _wallPosY = 820.0f;
//    const float _wallOnTopOfAnotherPosY = 770.0f; //720.0f
//
//    GenerateWall(_wallSize, Vector2f(1200.0f, _wallPosY), WL_MEDIUM);
//    GenerateWall(_wallSize, Vector2f(1350.0f, _wallPosY), WL_MEDIUM);
//    GenerateWall(_wallSize, Vector2f(1350.0f, _wallOnTopOfAnotherPosY), WL_MEDIUM);
//    GenerateWall(_wallSize, Vector2f(1500.0f, _wallPosY), WL_LONG);
//    GenerateWall(_wallSize, Vector2f(1550.0f, _wallPosY), WL_LONG);
//    GenerateWall(_wallSize, Vector2f(1600.0f, _wallPosY), WL_LONG);
//    GenerateWall(_wallSize, Vector2f(1650.0f, _wallPosY), WL_LONG);
//    GenerateWall(_wallSize, Vector2f(1700.0f, _wallPosY), WL_LONG);
//    GenerateWall(_wallSize, Vector2f(1750.0f, _wallPosY), WL_MEDIUM);
//    GenerateWall(_wallSize, Vector2f(1900.0f, _wallPosY), WL_MEDIUM);
//    GenerateWall(_wallSize, Vector2f(1900.0f, _wallOnTopOfAnotherPosY), WL_MEDIUM);
//}
//
//void GeometryDash::GerenerateAllSpike()
//{
//    const Vector2f& _spikeSize = Vector2f(396.0f / 8, 398.0f / 7);
//    const float _spikePosY = 810.0f;
//
//    GenerateSpike(_spikeSize, Vector2f(1150.0f, _spikePosY), WL_MEDIUM);
//    GenerateSpike(_spikeSize, Vector2f(1450.0f, _spikePosY), WL_LONG);
//    GenerateSpike(_spikeSize, Vector2f(1400.0f, _spikePosY), WL_LONG);
//    GenerateSpike(_spikeSize, Vector2f(1430.0f, _spikePosY), WL_LONG);
//}
//
//void GeometryDash::GenerateWall(const Vector2f& _wallSize, const Vector2f& _position, const WidthLevel& _widthLevel)
//{
//    if (_widthLevel == WL_MEDIUM)
//    {
//        MeshActor* _wall = Level::SpawnActor(MeshActor(RectangleShapeData(_wallSize, "Block")));
//        _wall->SetPosition(_position);
//
//        collidable.push_back(_wall);
//    }
//    else if (_widthLevel == WL_LONG)
//    {
//        MeshActor* _rectangleWall = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f( 65.0f, 32.0f), "Rectangle")));
//        _rectangleWall->SetPosition(_position);
//
//        collidable.push_back(_rectangleWall);
//    }
//}
//
//void GeometryDash::GenerateSpike(const Vector2f& _spikeSize, const Vector2f& _position,const WidthLevel& _widthLevel)
//{
//    if (_widthLevel == WL_MEDIUM)
//    {
//        Spike* _spike = Level::SpawnActor(Spike(RectangleShapeData(_spikeSize, "spike"), "Spike"));
//        _spike->SetPosition(_position);
//
//        deadlyObstacles.push_back(_spike->GetSpikeCollision());
//    }
//    else if (_widthLevel == WL_LONG)
//    {
//        Spike* _lowSpike = Level::SpawnActor(Spike(RectangleShapeData(_spikeSize, "longSpike"), "Spike"));
//        _lowSpike->SetPosition(_position);
//
//        deadlyObstacles.push_back(_lowSpike->GetSpikeCollision());
//    }
//}

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
    Spike* _spike = Level::SpawnActor(Spike(RectangleShapeData(_spickSize, _name, PNG), "spike"));
    _spike->SetPosition(_position);
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
