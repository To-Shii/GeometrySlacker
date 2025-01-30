#include "Player.h"
#include "TimerManager.h"
#include "InputManager.h"

#define JUMP_HIGH 400

Player::Player(const float _size, const string& _path) : MeshActor(RectangleShapeData({ _size,_size }, _path))
{
    SetName("Player");
    startPosition = Vector2f();
    movementComponent = CreateComponent<MovementComponent>();
    collisionComponent = CreateComponent<CollisionComponent>();
}

Player::Player(const Player& _other) : MeshActor(_other)
{
    startPosition = _other.startPosition;
    collisionComponent = CreateComponent<CollisionComponent>(_other.collisionComponent);
    movementComponent = CreateComponent<MovementComponent>(_other.movementComponent);
}

void Player::Construct()
{
    Super::Construct();

    SetOriginAtMiddle();
    collisionComponent->SetCollisionType(CollisionType::CT_BLOCK);
    M_INPUT.BindAction({ Code::Space,Code::Up }, bind(&Player::Jump, this));
}

void Player::BeginPlay()
{
    Super::BeginPlay();

    startPosition = GetPosition();
}

void Player::Tick(const float _deltaTime)
{
    Super::Tick(_deltaTime);

   
}

void Player::OnCollision(const Vector2f& _normal)
{
    Move(-_normal * 0.1f);

    collisionComponent->OnCollide(_normal, movementComponent->GetVelocity());
    movementComponent->SetIsGrounded();
}



void Player::Jump()
{
    if (!movementComponent->IsGrounded()) return;
     movementComponent->SetIsGrounded(false);
     Rotate(degrees(90));
    Vector2f& _velocity = movementComponent->GetVelocity();
    _velocity.y -= JUMP_HIGH;
}
