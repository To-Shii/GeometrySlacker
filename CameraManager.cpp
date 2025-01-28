#include "CameraManager.h"

CameraManager::CameraManager()
{
	onRenderWindow = map<u_int, OnRenderWindow>();
	allCameras = map<string, CameraActor*>();
	current = nullptr;
}


void CameraManager::RenderAllCameras(RenderWindow& _window)
{
	// pour chaque cam�ra
	for (const pair<string, CameraActor*> _pair : allCameras)
	{
		// je set sa view
		_window.setView(*_pair.second->GetView());

		// je draw tous les �l�ments que je veux
		for (const pair<u_int, OnRenderWindow>& _renderPair : onRenderWindow)
		{
			_renderPair.second(_window);
		}
	}

	// Je reset la view
	_window.setView(_window.getDefaultView());

	// Si je n'ai pas de cam�ra
	if (allCameras.empty())
	{
		// je draw tous les �l�ments que je veux
		for (const pair<u_int, OnRenderWindow>& _renderPair : onRenderWindow)
		{
			_renderPair.second(_window);
		}
	}
}