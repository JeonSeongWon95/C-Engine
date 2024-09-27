#pragma once
#include "includeHeader.h"


namespace Won
{
	class WUIManager
	{

	public:
		static void Initialize();
		static void OnLoad(eUIType type);
		static void Update();
		static void LateUpdate();
		static void Render(HDC NewDC);
		static void OnCompleted(class WUIBase* UI);
		static void OnFail();
		static void Release();

		static void Push(eUIType type);
		static void Pop(eUIType type);

	private:
		static WUIBase* mActiveUI;
		static std::unordered_map<eUIType, WUIBase*> AllUIs;
		static std::stack<WUIBase*> mPresentUIs;
		static std::queue<eUIType> mRequestUIs;
	
	};
}

