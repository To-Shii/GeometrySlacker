#include "MeshActor.h"
#include "CameraManager.h"
#include "CollisionComponent.h"
#include "ActorManager.h"


MeshActor::MeshActor(const float _radius, const size_t& _pointCount, const string& _path,
	const IntRect& _rect, const string& _name) : Actor(_name)
{
	mesh = CreateComponent<MeshComponent>(_radius, _pointCount, _path, _rect);
	renderMeshToken = -1;
}

MeshActor::MeshActor(const RectangleShapeData& _data, const string& _name, const float _lifespan) : Actor(_name, TransformData(), _lifespan)
{
	mesh = CreateComponent<MeshComponent>(_data);
	renderMeshToken = -1;
}

MeshActor::MeshActor(const MeshActor& _other) : Actor(_other)
{
	mesh = CreateComponent<MeshComponent>(_other.mesh);
	renderMeshToken = _other.renderMeshToken;
}


void MeshActor::Construct()
{
	Super::Construct();

	renderMeshToken = M_CAMERA.BindOnRenderWindow(bind(&MeshActor::RenderMesh, this, placeholders::_1));

	CollisionComponent* _collision = GetComponent<CollisionComponent>();
	if (_collision)
	{
		M_ACTOR.AddCollisionComponent(_collision);
	}

}

void MeshActor::Deconstruct()
{
	Super::Deconstruct();
	CollisionComponent* _collision = GetComponent<CollisionComponent>();
	if (_collision)
	{
		M_ACTOR.RemoveColiisionComponents(_collision);
	}
	M_CAMERA.UnbindOnRenderWindow(renderMeshToken);
}


void MeshActor::RenderMesh(RenderWindow& _window)
{
	_window.draw(*mesh->GetShape()->GetDrawable());
}