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
    MeshActor* _spike = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(396.0f / 8 , 398.0f  / 7), "spike")));
    _spike->SetPosition(Vector2f(1500.0f, 820.0f));
    
    //MeshActor* _levelComplete = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(window.getSize().x /2, window.getSize().y / 2) * 2.0f, "levelComplete", PNG)));

    collidable.push_back(_floor);
    collidable.push_back(_wall);
    collidable.push_back(_wall2);
    collidable.push_back(_wall3);
    DeadlyObstacles.push_back(_spike);
    /*collidable.push_back(_wall2);
    collidable.push_back(_wall3);*/

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