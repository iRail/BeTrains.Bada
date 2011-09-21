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

	/*
	 * I18N
	 */
	String previous = "Previous";
	String next = "Next";
	String empty = "Empty list";
	String saveToCalendar = "Save to calendar";
	AppResource* appRes = Application::GetInstance()->GetAppResource();
	appRes->GetString(L"LB_RES_PREV", previous);
	appRes->GetString(L"LB_RES_NEXT", next);
	appRes->GetString(L"LB_RES_EMPTY",empty);

	this->RemoveAllControls();
	HeaderForm::Initialize(true, true); //enables left and right softkey
	/*
	 * get Data from current request from appdata
	 */
	liveBoardRequest = AppData::GetInstance()->getCurrentLiveBoardRequest(); // no ownership offcourse

	this->SetSoftkeyText(SOFTKEY_0, previous);
	this->SetSoftkeyActionId(SOFTKEY_0, PREVIOUS_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_0, *this);

	this->SetSoftkeyText(SOFTKEY_1, next);
	this->SetSoftkeyActionId(SOFTKEY_1, NEXT_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_1, *this);

	/*
	 * Calculate sizes for all controls
	 */
	Rectangle bounds = this->GetClientAreaBounds();

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
void LiveBoardResults::OnListViewItemStateChanged(
		Osp::Ui::Controls::ListView &listView, int index, int elementId,
		Osp::Ui::Controls::ListItemStatus status) {
}

void LiveBoardResults::OnListViewItemSwept(
		Osp::Ui::Controls::ListView &listView, int index,
		Osp::Ui::Controls::SweepDirection direction) {
}

void LiveBoardResults::OnListViewContextItemStateChanged(
		Osp::Ui::Controls::ListView &listView, int index, int elementId,
		Osp::Ui::Controls::ListContextItemStatus state) {
	//TODO make context menu to add to calendar
}

/*
 * implements IListViewItemProvider
 */
Osp::Ui::Controls::ListItemBase*
LiveBoardResults::CreateItem(int index, int itemWidth) {
	Rectangle bounds = this->GetClientAreaBounds();
	int itemHeight = bounds.height / 8;
	if (bounds.width > bounds.height)
		itemHeight = bounds.width / 8;

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
	CustomItem* item = new CustomItem();
	item->Construct(Osp::Graphics::Dimension(itemWidth, itemHeight),
			LIST_ANNEX_STYLE_NORMAL); //+itemHeight*amountConnections
	item->AddElement(Rectangle(0, 0, itemWidth * 0.75, 0.5 * itemHeight),
			STATION, station, 0.5 * itemHeight, Color::COLOR_WHITE,
			Color::COLOR_WHITE, Color::COLOR_WHITE);
	item->AddElement(Rectangle(0, 0.5 * itemHeight, itemWidth * 0.75, 0.5
			* itemHeight), TIME, time, 0.5 * itemHeight, Color::COLOR_WHITE,
			Color::COLOR_WHITE, Color::COLOR_WHITE);
	item->AddElement(Rectangle(itemWidth * 0.75, 0, itemWidth * 0.25, 0.5
			* itemHeight), PLATFORM, platform, 0.5 * itemHeight,
			Color::COLOR_WHITE, Color::COLOR_BLUE, Color::COLOR_BLUE);
	item->AddElement(Rectangle(itemWidth * 0.75, 0.5 * itemHeight, itemWidth
			* 0.25, 0.5 * itemHeight), DELAY, delay, 0.5 * itemHeight,
			Color::COLOR_RED, Color::COLOR_BLUE, Color::COLOR_BLUE);

	/*
	 * I18N
	 */
	String saveToCalendar = "Save to calendar";
	AppResource* appRes = Application::GetInstance()->GetAppResource();
	appRes->GetString(L"LB_RES_TO_CAL",saveToCalendar);

	/*
	 * create context menu
	 */
	ListContextItem* itemContext = new ListContextItem();
	itemContext->Construct();
	itemContext->AddElement(SAVE_CALENDAR_ACTION, saveToCalendar);
	item->SetContextItem(itemContext);

	return item;
}

bool LiveBoardResults::DeleteItem(int index,
		Osp::Ui::Controls::ListItemBase* item, int itemWidth) {
	delete item;
	item = null;
	return true;
}

int LiveBoardResults::GetItemCount(void) {
	return liveBoardRequest->getResults()->GetCount();
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
void LiveBoardResults::OnActionPerformed(const Osp::Ui::Control& source,
		int actionId) {
	HeaderForm::OnActionPerformed(source, actionId);
	if (actionId == NEXT_ACTION) {
		AppLog("Clicked LiveBoardResults::search");
		Controller::GetInstance()->retrieveLiveBoardResults();
	} else if (actionId == PREVIOUS_ACTION) {
		AppLog("Clicked LiveBoardResults::clear");
	}
}

void LiveBoardResults::RequestRedraw(bool show) const {
	AppLog("LiveBoardResults::RequestRedraw");
	Form::RequestRedraw(show);
}
