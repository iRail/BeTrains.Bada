#include "view/LiveBoardResults.h"
#include "controller/Controller.h"
#include "model/AppData.h"
#include "view/Utils.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

LiveBoardResults::LiveBoardResults(void):
		liveBoardRequest(null)
{

}

LiveBoardResults::~LiveBoardResults(void) {
}

bool LiveBoardResults::Initialize() {
	RemoveAllControls();

	/*
	 * I18N
	 */
	String refresh = "Refresh";
	String back = "Back";
	String empty = "Empty list";
	String saveToCalendar = "Save to calendar";
	AppResource* appRes = Application::GetInstance()->GetAppResource();
	appRes->GetString(L"LB_RES_REFRESH", refresh);
	appRes->GetString(L"LB_RES_BACK", back);
	appRes->GetString(L"LB_RES_EMPTY",empty);


	HeaderForm::Initialize(true, true); //enables left and right softkey
	/*
	 * get Data from current request from appdata
	 */
	liveBoardRequest = AppData::GetInstance()->getCurrentLiveBoardRequest(); // no ownership offcourse


	SetSoftkeyText(SOFTKEY_0, refresh);
	SetSoftkeyActionId(SOFTKEY_0, REFRESH_ACTION);
	AddSoftkeyActionListener(SOFTKEY_0,*this);

	SetSoftkeyText(SOFTKEY_1, back);
	SetSoftkeyActionId(SOFTKEY_1, BACK_ACTION);
	AddSoftkeyActionListener(SOFTKEY_1,*this);

	/*
	 * Calculate sizes for all controls
	 */
	Rectangle bounds = GetClientAreaBounds();

	/*
	 * Construct a ListView
	 */
	list = new ListView();
	list->Construct(Rectangle(0, 0, bounds.width, bounds.height), true, false);
	list->SetTextOfEmptyList(empty);
	list->SetItemProvider(*this);
	list->AddListViewItemEventListener(*this);
	AddControl(*list);

	return true;
}

/*
 * implements IListViewItemEventListener
 */
void LiveBoardResults::OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status){
	if(elementId == MORE){
		//MORE BUTTON PRESSED
		Controller::GetInstance()->getMoreLiveBoardResults();
	}
}

void LiveBoardResults::OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction){}

void LiveBoardResults::OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus state){}


/*
 * implements IListViewItemProvider
 */
Osp::Ui::Controls::ListItemBase*
LiveBoardResults::CreateItem(int index, int itemWidth)
{
	Rectangle bounds = GetClientAreaBounds();
	int itemHeight = bounds.height/8;
	if(bounds.width>bounds.height)
		itemHeight = bounds.width /8;
	CustomItem* item = new CustomItem();

	//normal elements
	if(index < liveBoardRequest->getResults()->GetCount()){

		/*
		 * Get the trip from the index id
		 */
		LiveBoardResult* result;
		liveBoardRequest->getResults()->GetAt(index, result);
		/*
		 * Get trip data
		 */
		String time = Utils::formatTime(result->getDateTime());
		String delay = Utils::formatDelay(result->getDelay());
		String station = result->getStation()->getName();
		String platform = result->getPlatform();

		//create custom item with right size, height is calculated with amount of connections

		item->Construct(Osp::Graphics::Dimension(itemWidth,itemHeight), LIST_ANNEX_STYLE_NORMAL); //+itemHeight*amountConnections
		item->AddElement(Rectangle(0				, 0					, itemWidth*0.75	, 0.5*itemHeight), STATION		, station	, 0.5*itemHeight	, Color::COLOR_WHITE	, Color::COLOR_WHITE	, Color::COLOR_WHITE);
		item->AddElement(Rectangle(0				, 0.5*itemHeight	, itemWidth*0.75	, 0.5*itemHeight), TIME			, time		, 0.5*itemHeight	, Color::COLOR_WHITE	, Color::COLOR_WHITE	, Color::COLOR_WHITE);
		item->AddElement(Rectangle(itemWidth*0.75	, 0					, itemWidth*0.25	, 0.5*itemHeight), PLATFORM		, platform	, 0.5*itemHeight	, Color::COLOR_WHITE	, Color::COLOR_BLUE		, Color::COLOR_BLUE);
		item->AddElement(Rectangle(itemWidth*0.75	, 0.5*itemHeight	, itemWidth*0.25	, 0.5*itemHeight), DELAY		, delay  	, 0.5*itemHeight	, Color::COLOR_RED		, Color::COLOR_BLUE		, Color::COLOR_BLUE);

	}else{
		//MORE ELEMENT
		item->Construct(Osp::Graphics::Dimension(itemWidth,itemHeight), LIST_ANNEX_STYLE_NORMAL); //+itemHeight*amountConnections
		//item->AddElement(Rectangle(0, 0, itemWidth,itemHeight), MORE, "more..", 0.7*itemHeight, Color::COLOR_WHITE	, Color::COLOR_WHITE	, Color::COLOR_WHITE);
		EnrichedText* moreText = new EnrichedText();
		moreText->Construct(Dimension(itemWidth,itemHeight));
		moreText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
		moreText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
		String more= "More...";
		AppResource* appRes = Application::GetInstance()->GetAppResource();
		appRes->GetString(L"LB_RES_MORE", more);
		TextElement* textElement = new TextElement();
		textElement->Construct(more);
		textElement->SetTextColor(Color::COLOR_WHITE);
		moreText->Add(*textElement);
		item->AddElement(Rectangle(0,0,itemWidth,itemHeight),MORE,*moreText);
	}
	return item;
}

bool
LiveBoardResults::DeleteItem(int index, Osp::Ui::Controls::ListItemBase* item, int itemWidth)
{
    delete item; item = null; return true;
}

int
LiveBoardResults::GetItemCount(void)
{
	return liveBoardRequest->getResults()->GetCount()+1; //for the more element
}

result LiveBoardResults::OnInitializing(void) {
	result r = E_SUCCESS;
	r = HeaderForm::OnInitializing(HEADER_ID_LIVEBOARD);
	return r;
}

result LiveBoardResults::OnTerminating(void) {
	result r = E_SUCCESS;
	return r;
}

/*
 * IAction Event Listener
 */
void LiveBoardResults::OnActionPerformed(const Osp::Ui::Control& source,int actionId) {
	HeaderForm::OnActionPerformed(source,actionId);
	if(actionId == REFRESH_ACTION){
		//AppLog("Clicked LiveBoardResults::refresh");
		Controller::GetInstance()->retrieveLiveBoardResults();
	}else if(actionId == BACK_ACTION){
		//AppLog("Clicked LiveBoardResults::back");
		Controller::GetInstance()->setPreviousForm();
	}
}

void LiveBoardResults::RequestRedraw(bool show) {
	//AppLog("LiveBoardResults::RequestRedraw");
	liveBoardRequest = AppData::GetInstance()->getCurrentLiveBoardRequest();
	list->UpdateList();
	Form::RequestRedraw(show);
}

void LiveBoardResults::recalculateComponents(){
	Rectangle bounds = GetClientAreaBounds();
	list->SetBounds(0,0,bounds.width,bounds.height);
	Form::RequestRedraw();
}

