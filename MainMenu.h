#pragma once
#include "CoreMinimal.h"
#include "MeshActor.h"
#include "Button.h"

class MainMenu
{


	enum MenuType
	{
		MT_START,
		MT_MAIN,
		MT_OPTION
	};

	class Menu
	{
		MenuType type;

	protected:
		vector<SubclassOf<MeshActor>> allShape;
		vector<Button*> allButton;

	public:
		FORCEINLINE MenuType GetType() const
		{
			return type;
		}
		FORCEINLINE void SetType(const MenuType& _type)
		{
			type = _type;
		}



	public:
		Menu();

	public:
		virtual void Open(RenderWindow& _window) = 0;
		virtual void Close();

	};


};

