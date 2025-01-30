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

    collidables = vector<MeshActor*>();
    DeadlyObstacles = vector<MeshActor*>(); // spike ou autre 
}


void GeometryDash::Start()
{
    Super::Start();

    //Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(463.0f, 260.0f) * 2.0f, "background", JPG)));

    music = M_AUDIO.PlaySample<MusicSample>("StereoMadness");
    music->SetLoop(true);
    music->SetVolume(5.0f);
    
    MeshActor* _bg = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(window.getSize().x, window.getSize().y), "Background", PNG, true)));
    
    const Vector2f& _floorSize = Vector2f(window.getSize().x, window.getSize().y * 0.2f);
    MeshActor* _floor = Level::SpawnActor(MeshActor(RectangleShapeData(_floorSize, "Floor", PNG, true)));
    const float _posX = 0.0f;
    const float _posY = window.getSize().y * 0.8f;
    _floor->SetPosition(Vector2f(_posX, _posY));
    _floor->SetTextureRect(IntRect(Vector2i(), Vector2i(512 * 3, 512)));


    player = Level::SpawnActor(Player(50.0f, "character"));
    player->SetOriginAtMiddle();
    player->SetPosition(Vector2f(window.getSize().x * 0.20f, window.getSize().y * 0.5f));

    const Vector2f& _wallSize = Vector2f(50,50);
    MeshActor* _wall = Level::SpawnActor(MeshActor(RectangleShapeData(_wallSize, "block")));
    _wall->SetPosition(Vector2f(window.getSize().x * 0.6f, window.getSize().y * 0.8f - _wallSize.y));

    MeshActor* _wall2 = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_wallSize.x * 2, _wallSize.y), "block")));
    _wall2->SetPosition(Vector2f(window.getSize().x * 0.6f + _wallSize.x * 2 , window.getSize().y * 0.8f - _wallSize.y * 2));

    MeshActor* _levelComplete = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(window.getSize().x /2, window.getSize().y / 2) * 2.0f, "levelComplete", PNG)));

    collidables.push_back(_floor);
    collidables.push_back(_wall);
    collidables.push_back(_wall2);
}

bool GeometryDash::Update()
{
    Super::Update();

    Shape* _playerShape = player->GetMesh()->GetShape()->GetDrawable();
    const FloatRect& _playerRect = _playerShape->getGlobalBounds();

    for (MeshActor* _object : collidables) 
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
                LOG(Display, "Touche");
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
       //si un spike toucher alors dead cash pistache

        /*player->Death();
        music->Stop();
        LOG(Display, "Mort !");*/
    }



    return IsOver();
}

void GeometryDash::Stop()
{
    Super::Stop();
}