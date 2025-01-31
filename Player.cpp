#include "Player.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "AudioManager.h"

#define JUMP_HIGH 500

Player::Player(const float _size, const string& _path) : MeshActor(RectangleShapeData({ _size,_size }, _path))
{
    size = _size;
    SetName("Player");
    startPosition = Vector2f();
    movementComponent = CreateComponent<MovementComponent>();
    collisionComponent = CreateComponent<CollisionComponent>();
    deathAnimation = CreateComponent<AnimationComponent>();

    canJump = true;
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
    canJump = true;
}

void Player::Death()
{
    movementComponent->SetCanMove(false);
    Move(Vector2f(-2.0f, 0.0));
    M_AUDIO.PlaySample<SoundSample>("death", MP3);

    //TODO Animation : Abandon mb

    /*GetMesh()->GetShape()->InitRectangle(RectangleShapeData({ size, size }, "death", PNG));

    const float _timeBetween = 0.01f;
    const Vector2i& _spriteSize = Vector2i(166, 166);
    const vector<SpriteData>& _spritesData =
    {
        { _timeBetween, Vector2i(0, 0),_spriteSize},
        { _timeBetween, Vector2i(167, 0), _spriteSize},
        { _timeBetween, Vector2i(333, 0), _spriteSize},
        { _timeBetween, Vector2i(0, 167), _spriteSize},
        { _timeBetween, Vector2i(167, 167), _spriteSize},
        { _timeBetween, Vector2i(333, 167), _spriteSize },
        { _timeBetween, Vector2i(0, 333), _spriteSize},
        { _timeBetween, Vector2i(127, 333), _spriteSize},
        { _timeBetween, Vector2i(333, 333),_spriteSize},

    };
    AnimationData _animationData = AnimationData(2.0f, _spritesData);

    deathAnimation->AddAnimation(new Animation("Default", GetMesh()->GetShape(), _animationData));
    deathAnimation->SetCurrentAnimation("Default");
    deathAnimation->StartAnimation();*/

}

void Player::Jump()
{
    if (!canJump) return;
    canJump = false;
    Vector2f& _velocity = movementComponent->GetVelocity();
    _velocity.y -= JUMP_HIGH;
    Rotate(degrees(90));
}
