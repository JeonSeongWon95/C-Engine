#include "WUIManager.h"
#include "WUIBase.h"
#include "WButton.h"
#include "WHUD.h"

Won::WUIBase* Won::WUIManager::mActiveUI = nullptr;
std::unordered_map<Won::eUIType, Won::WUIBase*> Won::WUIManager::AllUIs = {};
std::stack<Won::WUIBase*> Won::WUIManager::mPresentUIs = {};
std::queue<Won::eUIType> Won::WUIManager::mRequestUIs = {};

void Won::WUIManager::Initialize()
{
	WButton* NewButton = new WButton();
	AllUIs.insert(std::make_pair(eUIType::Button, NewButton));

	WHUD* NewHUD = new WHUD();
	AllUIs.insert(std::make_pair(eUIType::HUD, NewHUD));
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

	UI->OnInit();
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

void Won::WUIManager::Release()
{
	for(auto& iter : AllUIs)
	{
		delete iter.second;
		iter.second = nullptr;
	}

	while(mRequestUIs.size() > 0)
	{
		mRequestUIs.pop();
	}

	while(mPresentUIs.size() > 0)
	{
		mPresentUIs.pop();
	}

}

void Won::WUIManager::Push(eUIType type)
{
	mRequestUIs.push(type);
}

void Won::WUIManager::Pop(eUIType type)
{
	if (mPresentUIs.empty())
		return;

	std::stack<WUIBase*> CopyStack = {};

	while (!mPresentUIs.empty())
	{
		WUIBase* UI = mPresentUIs.top();
		mPresentUIs.pop();

		if (UI->GetUIType() == type)
		{
			if(UI->IsFullScreen())
			{
				std::stack<WUIBase*> CopyPresentUIs = mPresentUIs;

				while (!CopyPresentUIs.empty())
				{
					WUIBase* UB = CopyPresentUIs.top();

					if (UB)
					{
						UB->IsActive();
						CopyPresentUIs.pop();
					}
				}

			}

			UI->UIClear();
			break;
		}

		CopyStack.push(UI);
	}

	while (!CopyStack.empty())
	{
		WUIBase* UI = CopyStack.top();
		mPresentUIs.push(UI);
		CopyStack.pop();
	}
}
