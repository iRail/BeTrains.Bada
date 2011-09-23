#include "view/RoutePlannerResults.h"
#include "controller/Controller.h"
#include "model/AppData.h"
#include "view/Utils.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

RoutePlannerResults::RoutePlannerResults(void) :
	request(null), format(null), subListFormat(null) {
}

RoutePlannerResults::~RoutePlannerResults(void) {
	delete format;
	delete subListFormat;
}

bool RoutePlannerResults::Initialize() {

	/*
	 * I18N
	 */
	String refresh = "Refresh";
	String back = "Back";
	String empty = "Empty List";
	String saveToCalendar = "Save to calendar";
	String direct = "Direct";
	String more = "More";
	AppResource* appRes = Application::GetInstance()->GetAppResource();
	appRes->GetString(L"RP_RES_REFRESH", refresh);
	appRes->GetString(L"RP_RES_BACK", back);
	appRes->GetString(L"RP_RES_EMPTY", empty);
	appRes->GetString(L"RP_RES_SAVE_TO_CAL", saveToCalendar);
	appRes->GetString(L"RP_RES_MORE", more);

	this->RemoveAllControls();
	HeaderForm::Initialize(true, true); //enables left and right softkey
	this->request = AppData::GetInstance()->getCurrentRequest();
	/*
	 * get Data from current request from appdata
	 */
	request = AppData::GetInstance()->getCurrentRequest(); // no ownership offcourse

	this->SetSoftkeyText(SOFTKEY_0, refresh);
	this->SetSoftkeyActionId(SOFTKEY_0, REFRESH_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_0, *this);

	this->SetSoftkeyText(SOFTKEY_1, back);
	this->SetSoftkeyActionId(SOFTKEY_1, BACK_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_1, *this);

	/*
	 * Calculate sizes for all controls
	 */
	Rectangle bounds = this->GetClientAreaBounds();
	int titleHeight = bounds.height / 12;
	int height = bounds.height / 7;
	if (bounds.width > bounds.height)
		height = bounds.width / 7;
	int width = bounds.width;

	/*
	 * Construct title label
	 */
	titleLabel = new Label();
	titleLabel->Construct(Rectangle(0, 0, bounds.width, titleHeight),
			L"station - station");
	AddControl(*titleLabel);


	/*
	 * scrollpanel
	 */
	ScrollPanel* scrollPanel = new ScrollPanel();
	scrollPanel->Construct(Rectangle(0, titleHeight, bounds.width, bounds.height- titleHeight));
	AddControl(*scrollPanel);
	/*
	 * More Button
	 */
	Button* moreButton = new Button();
	moreButton->Construct(Rectangle(0,bounds.height - 2*titleHeight,bounds.width,titleHeight),more);
	moreButton->SetActionId(MORE_ACTION);
	moreButton->AddActionEventListener(*this);
	scrollPanel->AddControl(*moreButton);

	/*
	 * Construct a ListView
	 */
	list = new ExpandableList();
	list->Construct(Rectangle(0, 0, bounds.width, bounds.height - 2*titleHeight), CUSTOM_LIST_STYLE_NORMAL, true);
	//list->Construct(Rectangle(0,0,bounds.width,bounds.height),CUSTOM_LIST_STYLE_NORMAL,true);
	list->SetTextOfEmptyList(empty);
	list->AddTouchEventListener(*this);
	scrollPanel->AddControl(*list);

	/*
	 * Create context menu
	 */
	contextMenu = new ContextMenu;
	contextMenu->Construct(Point(50, 50), CONTEXT_MENU_STYLE_LIST);
	contextMenu->AddItem(saveToCalendar, SAVE_CALENDAR_ACTION);
	contextMenu->AddActionEventListener(*this);

	//CREATE FORMAT
	format = new CustomListItemFormat();
	format->Construct();
	format->AddElement(LIST_ITEM_TIMES, Rectangle(0, 0, 0.6 * width, 0.5
			* height), 0.5 * height, Color::COLOR_WHITE, Color::COLOR_WHITE);
	//DELAY ELEMENT
	format->AddElement(LIST_ITEM_DELAYS, Rectangle(0.6 * width, 0, 0.4 * width,
			0.5 * height), 0.5 * height, Color::COLOR_RED, Color::COLOR_RED);
	//date
	format->AddElement(LIST_ITEM_DATE, Rectangle(0.35 * width, 0.5 * height,
			0.4 * width, 0.5 * height), 0.35 * height, Color::COLOR_GREY,
			Color::COLOR_GREY);
	//DURATION
	format->AddElement(LIST_ITEM_DURATION, Rectangle(0, 0.5 * height, 0.35
			* width, 0.5 * height), 0.5 * height, Color::COLOR_WHITE,
			Color::COLOR_WHITE);
	//Number of trains
	format->AddElement(LIST_ITEM_NUMBER_CONNECTIONS, Rectangle(0.75 * width,
			0.5 * height, 0.25 * width, 0.5 * height), 0.35 * height,
			Color::COLOR_WHITE, Color::COLOR_WHITE);

	//CREATE SUBLISTFORMAT
	subListFormat = new CustomListItemFormat();
	Color timeColor = Color::COLOR_GREEN;
	Color delayColor = Color::COLOR_RED;
	Color stationColor = Color::COLOR_WHITE;
	Color platformColor = Color::COLOR_WHITE;
	Color vehicleColor = Color::COLOR_GREY;

	subListFormat->Construct();
	subListFormat->AddElement(SUBLIST_FROM_TIME, Rectangle(0, 0, 0.2 * width,
			0.33 * height), 0.33 * height, timeColor, timeColor);
	subListFormat->AddElement(SUBLIST_FROM_DELAY, Rectangle(0.2 * width, 0, 0.2
			* width, 0.33 * height), 0.33 * height, delayColor, delayColor);
	subListFormat->AddElement(SUBLIST_FROM_STATION, Rectangle(0.4 * width, 0,
			0.50 * width, 0.33 * height), 0.33 * height, stationColor,
			stationColor);
	subListFormat->AddElement(SUBLIST_FROM_PLATFORM, Rectangle(0.9 * width, 0,
			0.1 * width, 0.33 * height), 0.33 * height, platformColor,
			platformColor);

	subListFormat->AddElement(SUBLIST_VEHICLE, Rectangle(0.2 * width, 0.33
			* height, 0.8 * width, 0.33 * height), 0.33 * height, vehicleColor,
			vehicleColor);

	subListFormat->AddElement(SUBLIST_TO_TIME, Rectangle(0, 0.66 * height, 0.2
			* width, 0.33 * height), 0.33 * height, timeColor, timeColor);
	subListFormat->AddElement(SUBLIST_TO_DELAY, Rectangle(0.2 * width, 0.66
			* height, 0.2 * width, 0.33 * height), 0.33 * height, delayColor,
			delayColor);
	subListFormat->AddElement(SUBLIST_TO_STATION, Rectangle(0.4 * width, 0.66
			* height, 0.50 * width, 0.33 * height), 0.33 * height,
			stationColor, stationColor);
	subListFormat->AddElement(SUBLIST_TO_PLATFORM, Rectangle(0.9 * width, 0.66
			* height, 0.1 * width, 0.33 * height), 0.33 * height,
			platformColor, platformColor);

	return true;
}

result RoutePlannerResults::OnInitializing(void) {
	result r = E_SUCCESS;
	r = HeaderForm::OnInitializing(HEADER_ID_ROUTE_PLANNER);
	return r;
}

result RoutePlannerResults::OnTerminating(void) {
	result r = E_SUCCESS;
	return r;
}

/*
 * IAction Event Listener
 */
void RoutePlannerResults::OnActionPerformed(const Osp::Ui::Control& source,
		int actionId) {
	HeaderForm::OnActionPerformed(source, actionId);
	if (actionId == REFRESH_ACTION) {
		AppLog("Clicked RoutePlannerResults::refresh");

		//show waiting popup with cancel interaction -> that then should go back to previous results
		//when the results got back succesfull, only then the old results must be deleted and replaced by new
		//this makes sure if we press cancel, we remain the previous results
		Controller::GetInstance()->retrieveRoutePlannerResults();
	} else if (actionId == BACK_ACTION) {
		//goes back to the request. so we could edit the form we already made.
		//in contrary to pressing on the header button route planner, that should give an empty form
		AppLog("Clicked RoutePlannerResults::back");
		Controller::GetInstance()->setPreviousForm();
	}else if(actionId == MORE_ACTION){

		AppLog("Clicked RoutePlannerResults::More");
		Controller::GetInstance()->getMoreResults();
	}
}

void RoutePlannerResults::RequestRedraw(bool show) const {
	AppLog("RoutePlannerResults::RequestRedraw");
	//load data
	titleLabel->SetText(request->getFromStation()->getName() + " - "
			+ request->getToStation()->getName());

	ArrayListT<Trip*>* trips =
			AppData::GetInstance()->getCurrentRequest()->getTrips();
	Trip* trip = null;
	list->RemoveAllItems();
	for (int i = 0; i < trips->GetCount(); i++) {
		trips->GetAt(i, trip);
		addTrip(trip);
	}

	Form::RequestRedraw(show);
}

void RoutePlannerResults::addTrip(Trip* trip) const {
	//GETTING THE DATA FROM THE TRIP
	Connection* firstConn;
	Connection* lastConn;
	ArrayListT<Connection*>* connections = trip->getConnections();
	connections->GetAt(0, firstConn);
	connections->GetAt(connections->GetCount() - 1, lastConn);
	//Station names
	/*
	 String stations;
	 stations += *firstConn->getStartNode()->getStation()->getName();
	 stations += L" - ";
	 stations += *lastConn->getEndNode()->getStation()->getName();
	 */
	//Times
	String times = Utils::formatTime(
			firstConn->getStartConnectionNode()->getDateTime());
	times += L" - " + Utils::formatTime(
			lastConn->getEndConnectionNode()->getDateTime());
	//DELAY
	String delay = " ";
	//if(firstConn->getStartConnectionNode()->getDelay() != null)
	delay = Utils::formatDelay(firstConn->getStartConnectionNode()->getDelay());
	//String delay = L"+0H25";
	//DURATION
	String duration = Utils::formatTime(trip->getDuration());
	//DATE
	String date = Utils::formatDate(
			firstConn->getStartConnectionNode()->getDateTime());

	//number of trains
	String numberOfTrains;
	String direct = "Direct";
	AppResource* appRes = Application::GetInstance()->GetAppResource();
	appRes->GetString(L"RP_RES_DIRECT", direct);

	if (trip->getConnections()->GetCount() == 0)
		numberOfTrains = direct;
	else
		numberOfTrains = L"#" + Integer::ToString(
				trip->getConnections()->GetCount());
	//CREATING ELEMENT
	Rectangle bounds = this->GetClientAreaBounds();
	int height = bounds.height / 7;
	if (bounds.width > bounds.height)
		height = bounds.width / 7;
	CustomListItem * newItem = new CustomListItem();
	newItem->Construct(height);
	newItem->SetItemFormat(*format);
	//newItem->SetElement(LIST_ITEM_STATIONS, stations);
	newItem->SetElement(LIST_ITEM_TIMES, times);
	newItem->SetElement(LIST_ITEM_DELAYS, delay);
	newItem->SetElement(LIST_ITEM_DURATION, duration);
	newItem->SetElement(LIST_ITEM_NUMBER_CONNECTIONS, numberOfTrains);
	newItem->SetElement(LIST_ITEM_DATE, date);
	int itemNumber = list->GetItemCount();
	list->AddItem(*newItem, itemNumber);

	for (int i = 0; i < trip->getConnections()->GetCount(); i++) {
		Connection* conn = null;
		trip->getConnections()->GetAt(i, conn);

		String fromTime = Utils::formatTime(
				conn->getStartConnectionNode()->getDateTime());
		String toTime = Utils::formatTime(
				conn->getEndConnectionNode()->getDateTime());
		String fromDelay = Utils::formatDelay(
				conn->getStartConnectionNode()->getDelay());
		String toDelay = Utils::formatDelay(
				conn->getEndConnectionNode()->getDelay());

		String fromStation = String(
				conn->getStartConnectionNode()->getStation()->getName());
		String toStation = String(
				conn->getEndConnectionNode()->getStation()->getName());
		String fromPlatform = String(
				conn->getStartConnectionNode()->getPlatform());
		String toPlatform = String(conn->getEndConnectionNode()->getPlatform());

		//SUBLIST_FROM_TIME,SUBLIST_TO_TIME,SUBLIST_FROM_STATION,SUBLIST_TO_STATION,SUBLIST_FROM_PLATFORM,SUBLIST_TO_PLATFORM
		CustomListItem* subItem = new CustomListItem();
		subItem->Construct(height);
		subItem->SetItemFormat(*subListFormat);
		subItem->SetElement(SUBLIST_FROM_TIME, fromTime);
		subItem->SetElement(SUBLIST_FROM_DELAY, fromDelay);
		subItem->SetElement(SUBLIST_FROM_STATION, fromStation);
		subItem->SetElement(SUBLIST_FROM_PLATFORM, fromPlatform);
		subItem->SetElement(SUBLIST_VEHICLE, conn->getVehicle()->getName());
		subItem->SetElement(SUBLIST_TO_TIME, toTime);
		subItem->SetElement(SUBLIST_TO_STATION, toStation);
		subItem->SetElement(SUBLIST_TO_PLATFORM, toPlatform);
		list->AddSubItem(itemNumber, *subItem, i);
	}
}

void RoutePlannerResults::ShowContextMenu(bool show) {
	contextMenu->SetShowState(show);
	if (show == true)
		contextMenu->Show();
	else
		//Call Show of the form -> this makes sure the context menu is removed again when needed
		Show();
}

/*
 * ITouchEventListener
 */
void RoutePlannerResults::OnTouchDoublePressed(const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo) {
}
void RoutePlannerResults::OnTouchFocusIn(const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo) {
}
void RoutePlannerResults::OnTouchFocusOut(const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo) {
}
void RoutePlannerResults::OnTouchLongPressed(const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo) {
	if (&source == list) {
		contextMenu->SetPosition(currentPosition.x, currentPosition.y
				+ contextMenu->GetBounds().y);
		ShowContextMenu(true);
		int sub = -1;
		int mainIndex = -1;
		list->GetItemIndexFromPosition(currentPosition, mainIndex, sub);
		if (mainIndex >= 0)
			Controller::GetInstance()->saveToCalendar(mainIndex);
		//AppLog("RoutePlannerResults::OnTouchLongPressed mainitem:%S",Integer::ToString(mainIndex).GetPointer());
	}
}
void RoutePlannerResults::OnTouchMoved(const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo) {
}
void RoutePlannerResults::OnTouchPressed(const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo) {
}
void RoutePlannerResults::OnTouchReleased(const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo) {
}

