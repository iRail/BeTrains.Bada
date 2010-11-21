
#include "MainOptionList.h"
#include "FGraphics.h"
#include "FSystem.h"
#include "FMediaImage.h"
#include "Constants.h"
#include "BetrainsPrototype.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Media;

//constructor
MainOptionList::MainOptionList(void)
{
}


//destructor
MainOptionList::~MainOptionList(void)
{
}

void MainOptionList::addItem(const Osp::Base::String& text,const Osp::Base::String& iconpath,const int id){
	List* mainlist = static_cast<List*>(GetControl(L"IDC_OPTION_LIST" ));
	Image* dummyimage = new Image;
	Bitmap* bitmap = null;
	dummyimage -> Construct();
	bitmap = dummyimage->DecodeN(iconpath, BITMAP_PIXEL_FORMAT_ARGB8888, 144, 96);
	delete dummyimage;
	mainlist->AddItem(&text, null, bitmap, null, id);
}

bool
MainOptionList::Initialize()
{
	Form::Construct(L"IDF_MAINFORM");
	//SetOptionkeyActionId(Constants::MENU_ITEM_OPTIONS);
	//AddOptionkeyActionListener(*this);
	addItem(L"Route Planner",L"/Home/home_btn_planner_default.png",Constants::MENU_ITEM_PLANNER);
	addItem(L"Map",L"/Home/home_btn_map_default.png",Constants::MENU_ITEM_MAP);
	addItem(L"Chat",L"/Home/home_btn_chat_default.png",Constants::MENU_ITEM_CHAT);
	addItem(L"Traffic",L"/Home/home_btn_traffic_default.png",Constants::MENU_ITEM_TRAFFIC);
	addItem(L"Starred",L"/Home/home_btn_starred_default.png",Constants::MENU_ITEM_STARRED);
	List* mainlist = static_cast<List*>(GetControl(L"IDC_OPTION_LIST" ));
	mainlist->AddItemEventListener(*this);
	return true;
}

result
MainOptionList::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result
MainOptionList::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}


void
MainOptionList::OnActionPerformed(const Control& source, int actionId)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnFocusGained(const Control &source)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnFocusLost(const Control &source)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnKeyLongPressed(const Control &source, KeyCode keyCode)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnKeyPressed(const Control &source, KeyCode keyCode)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnKeyReleased(const Control &source, KeyCode keyCode)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnTouchDoublePressed(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnTouchFocusIn(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnTouchFocusOut(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnTouchLongPressed(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnTouchMoved(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnTouchPressed(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnTouchReleased(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
MainOptionList::OnItemStateChanged(const Control &source, int index, int itemId, ItemStatus status)
{
	if(status == Osp::Ui::ITEM_SELECTED){
		BetrainsPrototype* app = (BetrainsPrototype*)this->GetParent();
		switch ( itemId ) {
		  case Constants::MENU_ITEM_PLANNER:
			  app->showRoutePlanner();
			  break;
		  case Constants::MENU_ITEM_MAP:
			  app->showMap();
			  break;
		  default :
			  app->showMenu();
		}
	}
}

