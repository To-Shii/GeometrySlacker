#include "Player.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "AudioManager.h"

#define JUMP_HIGH 500

Player::Player(const float _size, const string& _path) : MeshActor(RectangleShapeData({ _size,_size }, _path))
{
    size = _size;
    startPosition = Vector2f();
    movementComponent = CreateComponent<MovementComponent>();
    collisionComponent = CreateComponent<CollisionComponent>("Player", IS_ALL, CT_OVERLAP);
    canJump = false;
    targetRotation = 0;
    rotationTimer = nullptr;
    SetLayer(Layer::LayerType::PLAYER);
    SetupAnimation();

    vector<pair<string, CollisionType>> _responsesPlayer = { {"Block", CT_BLOCK}, {"Spike", CT_BLOCK}, {"Floor", CT_BLOCK} };
    collisionComponent->AddResponses(_responsesPlayer);
}

Player::Player(const Player& _other) : MeshActor(_other)
{
    startPosition = _other.startPosition;
    collisionComponent = CreateComponent<CollisionComponent>(*_other.collisionComponent);
    targetRotation = _other.targetRotation;
    movementComponent = CreateComponent<MovementComponent>(_other.movementComponent);
    rotationTimer = nullptr;
    SetLayer(_other.GetLayer());

    SetupAnimation();
}

void Player::Construct()
{
    Super::Construct();

    M_INPUT.BindAction({ Code::Space,Code::Up }, bind(&Player::Jump, this));
    SetOriginAtMiddle();
    SetPosition(Vector2f(0.0f, 780.0f));
}

void Player::BeginPlay()
{
    Super::BeginPlay();

    startPosition = GetPosition();
}

void Player::Tick(const float _deltaTime)
{
    RotateInAir();

    Super::Tick(_deltaTime);
}

void Player::OnCollision(const Vector2f& _normal)
{
    Move(-_normal * 0.1f);

    canJump = true;
}

void Player::Death()
{
    movementComponent->SetCanMove(false);
    canJump = false;
    Move(Vector2f(-2.0f, 0.0));
    M_AUDIO.PlaySample<SoundSample>("death", MP3);

    //M_TEXTURE.Load(GetMesh()->GetShape(), "death", { {0,0},{295,368} });
    M_TEXTURE.Load(GetMesh()->GetShape(), "death", IntRect());
    animation->SetCurrentAnimation("death");
    animation->StartAnimation();

}

void Player::Jump()
{
    if (!canJump) return;
    canJump = false;
    Vector2f& _velocity = movementComponent->GetVelocity();
    _velocity.y -= JUMP_HIGH;
    
    if (rotationTimer) return;
    
    SelfRotate(180);
}

void Player::SelfRotate(const int _degrees)
{
    const auto _normalizeDegrees = [](const float _degrees) -> int
    {
            return CAST(int, _degrees)%360;
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
    }, seconds(0.005f), true, true);
}

void Player::RotateInAir()
{
    if(!movementComponent->IsGrounded() && !rotationTimer)
    {
        SelfRotate(30);
    }
}

void Player::CollisionEnter(const CollisionData& _data)
{
    if (_data.response == CT_BLOCK)
    {
        //_data.other->GetLayer() == 
    }
}

void Player::CollisionUpdate(const CollisionData& _data)
{

}

void Player::CollisionExit(const CollisionData& _data)
{

}

void Player::SetupAnimation()
{
    animation = CreateComponent<AnimationComponent>();

    vector<SpriteData> _deathFrames;
    for (int _i = 0; _i < 9; _i++)
    {
        _deathFrames.push_back(SpriteData(0.05f, {_i*295,0}, {295, 368}));
    }

    AnimationData _deathData = AnimationData(1.0f, _deathFrames, false, false, RD_ROW);
    Animation* _deathAnimation = new Animation("death", GetMesh()->GetShape(), _deathData);
    animation->AddAnimation(_deathAnimation);
}
