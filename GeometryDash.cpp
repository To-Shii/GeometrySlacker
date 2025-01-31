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


void GeometryDash::Start()
{
    Super::Start();
    M_CAMERA.CreateCamera("MainCamera");
    //Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(463.0f, 260.0f) * 2.0f, "background", JPG)));

    background = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(window.getSize().x, window.getSize().y), "Background", PNG, true)));

    GenerateMap();
    GenerateMusic();

    M_CAMERA.GetCurrent()->SetTarget(player);
    M_CAMERA.GetCurrent()->Zoom(1.0f);
    M_CAMERA.GetCurrent()->SetScale(Vector2f(1905.0f, 1080.0f));
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

            // Récupération de la normale
            const Vector2f& _normal = ComputeNormal(*_intersection);

            // Vérification de la position du joueur par rapport à l'obstacle
            float _playerBottom = _playerRect.position.y + _playerRect.size.y;
            float _objectTop = _objectRect.position.y;

            if (_playerBottom <= _objectTop + 5.0f) //+5 pour eviter les lags (marge d'erreur)
            {
                // Le joueur atterrit sur l'obstacle -> il reste en vie
                player->OnCollision(_normal);
                //LOG(Display, "Touche");
            }
            else
            {
                // Le joueur touche un côté ou le dessous -> il meurt
                player->Death();
                music->Stop();
                LOG(Display, "Mort !");
            }
        }
    }

    for (MeshActor* _object : DeadlyObstacles)
    {

        Shape* _objectShape = _object->GetMesh()->GetShape()->GetDrawable();
        const FloatRect& _objectRect = _objectShape->getGlobalBounds();

        //si un spike toucher alors dead cash pistache
        if (const optional<FloatRect> _intersection = _playerRect.findIntersection(_objectRect))
        {
            // Récupération de la normale
            const Vector2f& _normal = ComputeNormal(*_intersection);

            // Le joueur atterrit sur l'obstacle -> il reste en vie
            player->OnCollision(_normal);
            player->Death();
            music->Stop();
            LOG(Display, "Mort !");
        }
    }

    return IsOver();
}

void GeometryDash::Stop()
{
    Super::Stop();
}

#pragma region MapGenerator

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
    const Vector2f& _floorSize = Vector2f(1000000000.0f, 600.0f);
    MeshActor* _floor = Level::SpawnActor(MeshActor(RectangleShapeData(_floorSize, "Floor", PNG, true)));
    const float _posX = 0.0f;
    const float _posY = window.getSize().y * 0.8f;
    _floor->SetPosition(Vector2f(_posX, _posY));
    _floor->SetTextureRect(IntRect(Vector2i(), Vector2i(512 * 3, 512)));

    player = Level::SpawnActor(Player(50.0f, "character"));

    const Vector2f& _wallSize = Vector2f(50.0f, 80.0f);
    const Vector2f& _spickSize = Vector2f(50.0f, 50.0f);

    GenerateAllSpikes();
    GenerateAllWalls();

    //MeshActor* _levelComplete = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(window.getSize().x /2, window.getSize().y / 2) * 2.0f, "levelComplete", PNG)));

    collidable.push_back(_floor);
}



void GeometryDash::GenerateAllSpike(const float _floor)
{
    GenerateSpike(Vector2f(400.0f, _floor + 8.0f));
    GenerateSpike(Vector2f(950.0f, _floor + 8.0f));
    GenerateSpike(Vector2f(1300.0f, _floor + 8.0f));

    GenerateSpike(Vector2f(3350.0f, _floor + 8.0f - 440.0f));
    GenerateSpike(Vector2f(3400.0f, _floor + 8.0f - 440.0f));
    GenerateSpike(Vector2f(3450.0f, _floor + 8.0f - 440.0f));
}

void GeometryDash::GenerateAllLowSpike(const float _floor)
{
    GenerateLowSpike(Vector2f(900.0f, _floor + 8.0f));
    GenerateLowSpike(Vector2f(3300.0f, _floor + 8.0f - 430.0f));
    GenerateLowSpike(Vector2f(3500.0f, _floor + 8.0f - 430.0f));
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
        GenerateWall(Vector2f(_x, _floor - 280.0f));
        _x += 50.0f;
    }

    _x = 3200.0f;
    for (u_int i = 0; i < 10; i++)
    {
        GenerateWall(Vector2f(_x, _floor - 240.0f));
        _x += 50.0f;
    }

    _x = 3700.0f;
    for (u_int i = 0; i < 4; i++)
    {
        GenerateWall(Vector2f(_x, _floor - 280.0f));
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
        GenerateWall(Vector2f(_x, _floor - 174.0f));
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
    _y = 400.0f;
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
        GenerateLowWall(Vector2f(_x, _floor - 80.0f));
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
    MeshActor* _spike = Level::SpawnActor(MeshActor(RectangleShapeData(_spickSize, _name)));
    _spike->SetPosition(_position);
    DeadlyObstacles.push_back(_spike);
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
