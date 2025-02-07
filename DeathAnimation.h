#pragma once
#include "MeshActor.h"
#include "AnimationComponent.h"

class DeathAnimation : public MeshActor
{
    AnimationComponent* animation;

public:
    DeathAnimation(const RectangleShapeData& _data);
    DeathAnimation(const DeathAnimation& _other);

    virtual void Construct() override;
    virtual void Deconstruct() override;

public:
    virtual void BeginPlay() override;
    virtual void Tick(const float _deltaTime) override;
};