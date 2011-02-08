
#include "View/MainForm.h"
#include "View/BeTrains.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Media;


MainForm::MainForm(void)
{
}

MainForm::~MainForm(void)
{
}

bool
MainForm::Initialize()
{
	Form::Construct(L"MAIN_FORM");
	SetSoftkeyActionId(SOFTKEY_1, ACTION_EXIT);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	addItem(L"Route Planner",L"/Home/btn_planner.png",MENU_ITEM_PLANNER);
	addItem(L"Map",L"/Home/btn_map.png",MENU_ITEM_MAP);
	addItem(L"Chat",L"/Home/btn_chat.png",MENU_ITEM_CHAT);
	addItem(L"Traffic",L"/Home/btn_traffic.png",MENU_ITEM_TRAFFIC);
	addItem(L"Starred",L"/Home/btn_starred.png",MENU_ITEM_STARRED);
	List* mainlist = static_cast<List*>(GetControl(L"MAIN_LIST"));
	mainlist->AddItemEventListener(*this);
	return true;
}

result
MainForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	return r;
}

result
MainForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

void MainForm::addItem(const Osp::Base::String& text,const Osp::Base::String& iconpath,const int id){
	List* mainlist = static_cast<List*>(GetControl(L"MAIN_LIST" ));
	Image* dummyimage = new Image;
	Bitmap* bitmap = null;
	dummyimage -> Construct();
	bitmap = dummyimage->DecodeN(iconpath, BITMAP_PIXEL_FORMAT_ARGB8888, 84, 56);
	delete dummyimage;
	mainlist->AddItem(&text, null, bitmap, null, id);
}

void MainForm::OnItemStateChanged(const Control &source, int index, int itemId, ItemStatus status){
	if(status == Osp::Ui::ITEM_SELECTED){
		//BeTrains* app = (BeTrains*)this->GetParent();
		BeTrains* app = (BeTrains*)BeTrains::GetInstance();
		//AppLog("app pointer : %d",app);
		switch ( itemId ) {
		  case MENU_ITEM_PLANNER:
			  app->showRoutePlanner();
			  break;
		  case MENU_ITEM_MAP:
			  app->showMap();
			  break;
		  default :
			  AppLog("default");
			  app->showMainMenu();
		}
	}
}

void MainForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	switch ( actionId ) {
		case ACTION_EXIT:
			Application::GetInstance()->Terminate();
			break;
		default :
			AppLog("default");
	}
}
