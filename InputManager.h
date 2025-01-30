#pragma once
#include "Singleton.h"
namespace MyInput
{
	using KeyPressed = Event::KeyPressed;
	using Code = Keyboard::Scancode;

	struct InputData
	{
        set<Code> codes;
        bool isAnyKey;
        function<void()> callbacks;

        InputData(const function<void()>& _callback, const set<Code>& _codes = {}, const bool _isAnyKey = false)
        {
            callbacks = _callback;
            codes = _codes;
            isAnyKey = _isAnyKey;
        }

    public:
        bool TryToExcute(const KeyPressed* _key)
        {
            if (!isAnyKey && !ContainKey(_key->scancode)) return false;
            callbacks();
            return true;
        }

    private:
        inline bool ContainKey(const Code& _code)
        {
            return codes.contains(_code);
        }
	};

	class InputManager : public Singleton<InputManager>
	{
        vector<InputData> inputData;
    public:
        void ConsumeData(RenderWindow& _window);

        void BindAction(const set<Code>& _codes, const function<void()>& _callback);
        void BindAction(const Code& _codes, const function<void()>& _callback);
        void BindActionWithState(const Code& _codes, const function<void(bool)>& _callback, bool _state);

	};

}

using namespace MyInput;
