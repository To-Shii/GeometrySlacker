#include "Player.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Level.h"

#define JUMP_HIGH 500

Player::Player(const float _size, const string& _path) : MeshActor(RectangleShapeData({ _size, _size }, _path))
{
    size = _size;
    startPosition = Vector2f();
    movementComponent = CreateComponent<MovementComponent>();
    collisionComponent = CreateComponent<CollisionComponent>();
    canJump = false;
    targetRotation = 0;
    rotationTimer = nullptr;
    SetName("Player");

    canJump = true;
    animation = new DeathAnimation(RectangleShapeData({ 50.0f,50.0f }));
}

Player::Player(const Player& _other) : MeshActor(_other)
{
    startPosition = _other.startPosition;
    collisionComponent = CreateComponent<CollisionComponent>(_other.collisionComponent);
    movementComponent = CreateComponent<MovementComponent>(_other.movementComponent);
    targetRotation = _other.targetRotation;
    rotationTimer = nullptr;
    animation = new DeathAnimation(RectangleShapeData({ 50.0f,50.0f }));
}

void Player::Construct()
{
    Super::Construct();

    SetOriginAtMiddle();
    collisionComponent->SetCollisionType(CollisionType::CT_BLOCK);
    M_INPUT.BindAction({ Code::Space,Code::Up }, bind(&Player::Jump, this));
    SetOriginAtMiddle();
    SetPosition(Vector2f(0.0f, 864.0f - 50.0f));
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
    canJump = true;
}

void Player::Death()
{
    movementComponent->SetCanMove(false);
    Move(Vector2f(-2.0f, 0.0));
    M_AUDIO.PlaySample<SoundSample>("death", MP3);

    GetMesh()->GetShape()->InitRectangle(RectangleShapeData({ size, size }, "death", PNG));

    animation->GetComponent<AnimationComponent>()->StartAnimation();
}

void Player::Jump()
{
    if (!canJump) return;
    canJump = false;
    Vector2f& _velocity = movementComponent->GetVelocity();
    _velocity.y -= JUMP_HIGH;
    SelfRotate(270.0f);
}

void Player::SelfRotate(const int _degrees)
{
    const auto _normalizeDegrees = [](const float _degrees) -> int
        {
            return CAST(int, _degrees) % 360;
        };

    targetRotation += _degrees;
    targetRotation = _normalizeDegrees(targetRotation);
    if (rotationTimer) return;

    rotationTimer = new Timer<Seconds>([&]()
        {
            Rotate(degrees(1));
            targetRotation--;
            const int _currentRotation = _normalizeDegrees(GetRotation().asDegrees());
            if (targetRotation == 0)
            {
                rotationTimer->Stop();
                rotationTimer = nullptr;
            }
        }, seconds(0.0005f), true, true);
}

void Player::RotateInAir()
{
    if (!movementComponent->IsGrounded() && !rotationTimer)
    {
        SelfRotate(30);
    }
}