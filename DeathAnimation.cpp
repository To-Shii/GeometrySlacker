#include "DeathAnimation.h"

DeathAnimation::DeathAnimation(const RectangleShapeData& _data) : MeshActor(_data, "death")
{
    SetLifeSpan(0.2f);
    animation = CreateComponent<AnimationComponent>();
}

DeathAnimation::DeathAnimation(const DeathAnimation& _other) : MeshActor(_other)
{
    SetLifeSpan(0.2f);
    animation = CreateComponent<AnimationComponent>();

}

void DeathAnimation::Construct()
{
    Super::Construct();

    const float _timeBetween = 0.0125f;
    const Vector2i& _spriteSize = Vector2i(258, 258);
    const vector<SpriteData>& _spritesData =
    {
        { _timeBetween, Vector2i(46, 21),Vector2i(11, 7)},
        { _timeBetween, Vector2i(99, 19), Vector2i(16, 9)},
    };

    const AnimationData& _animationData = AnimationData(2.0f, _spritesData, true, false);


    animation->AddAnimation(new Animation("Default", GetMesh()->GetShape(), _animationData));
    animation->SetCurrentAnimation("Default");
    animation->StartAnimation();
}

void DeathAnimation::Deconstruct()
{
    Super::Deconstruct();
    animation->StopAnimation();


}

void DeathAnimation::BeginPlay()
{
    Super::BeginPlay();
}

void DeathAnimation::Tick(const float _deltaTime)
{
    Super::Tick(_deltaTime);
}