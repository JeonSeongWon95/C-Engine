#include "WUIManager.h"
#include "WUIBase.h"

Won::WUIBase* Won::WUIManager::mActiveUI = nullptr;
std::unordered_map<Won::eUIType, Won::WUIBase*> Won::WUIManager::AllUIs = {};
std::stack<Won::WUIBase*> Won::WUIManager::mPresentUIs = {};
std::queue<Won::eUIType> Won::WUIManager::mRequestUIs = {};

void Won::WUIManager::Initialize()
{
}

void Won::WUIManager::OnLoad(eUIType type)
{
	std::unordered_map<Won::eUIType, Won::WUIBase*>::iterator iter = AllUIs.find(type);

	if (iter == AllUIs.end())
	{
		OnFail();
		return;
	}

	OnCompleted(iter->second);
}

void Won::WUIManager::Update()
{
	std::stack<WUIBase*> CopyPresentUIs = mPresentUIs;

	while(!CopyPresentUIs.empty())
	{
		WUIBase* UI = CopyPresentUIs.top();
		if (UI)
		{
			UI->Update();
			CopyPresentUIs.pop();
		}
	}

	if(mRequestUIs.size() > 0)
	{
		eUIType NewType = mRequestUIs.front();
		mRequestUIs.pop();
		OnLoad(NewType);
	}

}

void Won::WUIManager::LateUpdate()
{
	std::stack<WUIBase*> CopyPresentUIs = mPresentUIs;

	while (!CopyPresentUIs.empty())
	{
		WUIBase* UI = CopyPresentUIs.top();
		if (UI)
		{
			UI->LateUpdate();
			CopyPresentUIs.pop();
		}
	}
}

void Won::WUIManager::Render(HDC NewDC)
{
	std::stack<WUIBase*> CopyPresentUIs = mPresentUIs;

	while (!CopyPresentUIs.empty())
	{
		WUIBase* UI = CopyPresentUIs.top();
		if (UI)
		{
			UI->Render(NewDC);
			CopyPresentUIs.pop();
		}
	}
}

void Won::WUIManager::OnCompleted(WUIBase* UI)
{
	if (UI == nullptr) 
		return;

	UI->Active();

	if(UI->IsFullScreen())
	{
		std::stack<WUIBase*> CopyPresentUIs = mPresentUIs;

		while (!CopyPresentUIs.empty())
		{
			WUIBase* UI = CopyPresentUIs.top();
			if (UI)
			{
				UI->IsActive();
				CopyPresentUIs.pop();
			}
		}
	}

	mPresentUIs.push(UI);
	mActiveUI = UI;
}

void Won::WUIManager::OnFail()
{
}

void Won::WUIManager::Push(eUIType type)
{
	mRequestUIs.push(type);
}

void Won::WUIManager::Pop(eUIType type)
{

}
