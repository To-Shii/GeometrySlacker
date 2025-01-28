#include "Player.h"
#include "TimerManager.h"

Player::Player(const float _size, const string& _path) : MeshActor(RectangleShapeData({ _size,_size }, _path))
{
    canMove = true;
    startPosition = Vector2f();
    velocity = Vector2f(-100.0f,0.0f);
    mass = 80.0f;
    gravity = 9.81f;
    restitution = 0.85f;

    isGrounded = false;

    SetOriginAtMiddle();
}

void Player::BeginPlay()
{
    Super::BeginPlay();

    collisionComponent = new CollisionComponent(this);
    collisionComponent->SetCollisionType(CollisionType::CT_BLOCK);
    AddComponent(collisionComponent);

    movementComponent = new MovementComponent(this);
    AddComponent(movementComponent);

    startPosition = GetPosition();
}

void Player::Tick(const float _deltaTime)
{
    Super::Tick(_deltaTime);

    if (!canMove) return;

    // Appliquer la gravité
    if (!isGrounded)
    {
        velocity.y += gravity * mass * _deltaTime;
    }

    // Mettre à jour la position
    movementComponent->Move(velocity, _deltaTime);
}

void Player::OnCollision(const optional<FloatRect>& _intersection)
{
    const Vector2f _normal = GetNormal(_intersection);
    Move(_normal * 0.1f);

    GetComponent<CollisionComponent>()->OnCollide(_normal, velocity);
    isGrounded = true;
    cout << _normal.x << "  :  " << _normal.y << endl;
}

Vector2f Player::GetNormal(const optional<FloatRect>& _intersection)
{

    Vector2f _collisionNormal;




    _collisionNormal.x = -_intersection->size.y;
    _collisionNormal.y = -_intersection->size.x;

    const float _norme = sqrtf(pow(_collisionNormal.x, 2) + pow(_collisionNormal.y, 2));

    return _collisionNormal / _norme;
}
