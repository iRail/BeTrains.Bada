#include "view/FormRouteplanner.h"
#include "controller/Controller.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

FormRouteplanner::FormRouteplanner(void) :
	request(null)
{
}

FormRouteplanner::~FormRouteplanner(void) {
}

bool FormRouteplanner::Initialize() {
	this->RemoveAllControls();
	HeaderForm::Initialize(true, true); //enables left and right softkey

	/*
	 * get Data from current request from appdata
	 */
	request = AppData::GetInstance()->getCurrentRequest(); // no ownership offcourse

	/*
	 * I18N
	 */
	String search = "zoekt";
	String clear = "wis";
	String from = "van";
	String to = "naar";
	String pickTime = "kies tijd en datum";
	String depart = "vertrek";
	String arrival = "aankomst";
	AppResource* appRes = Application::GetInstance()->GetAppResource();
	appRes->GetString(L"RP_SEARCH", search);
	appRes->GetString(L"RP_CLEAR", clear);
	appRes->GetString(L"RP_FROM", from);
	appRes->GetString(L"RP_TO", to);
	appRes->GetString(L"RP_PICK_TIME", pickTime);
	appRes->GetString(L"RP_DEPARTURE", depart);
	appRes->GetString(L"RP_ARRIVAL", arrival);

	/*
	 * Set soft keys
	 */
	this->SetSoftkeyText(SOFTKEY_0, search);
	this->SetSoftkeyActionId(SOFTKEY_0, SEARCH_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_0, *this);

	this->SetSoftkeyText(SOFTKEY_1, clear);
	this->SetSoftkeyActionId(SOFTKEY_1, CLEAR_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_1, *this);

	Rectangle bounds = this->GetClientAreaBounds();

	scrollPanel = new ScrollPanel();
	scrollPanel->Construct(Rectangle(0,0,bounds.width,bounds.height));
	/*
	 * Calculate sizes for all controls
	 */

	//int x = bounds.x;
	int y = 10;
	int border = 0.05 * bounds.width;
	int widthBody = 0.9 * bounds.width;

	int heightBody = int(1.0 / 6.0 * double(bounds.height));

	int stationWidth = 0.85 * widthBody;
	int switchButtonWidth = 0.15 * widthBody;

	/*
	 * Make From Station Edit Field
	 */
	fromStationEditField = new EditField();
	fromStationEditField->Construct(Rectangle(border, y, stationWidth,
			heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true,
			100, GROUP_STYLE_TOP);
	fromStationEditField->SetTitleText(from);
	scrollPanel->AddControl(*fromStationEditField);
	fromStationEditField->AddTouchEventListener(*this);
	fromStationEditField->SetEnabled(false);//prevents opening default text input
	fromStationEditField->BeginBlock();

	/*
	 * Make Switch Button
	 */
	switchStationsButton = new Button();
	switchStationsButton->Construct(Rectangle(border + stationWidth, y,
			switchButtonWidth, heightBody * 2));
	switchStationsButton->SetActionId(SWITCH_ACTION);
	switchStationsButton->SetText(L"Sw"); //Switch Stations
	scrollPanel->AddControl(*switchStationsButton);
	switchStationsButton->AddActionEventListener(*this);
	//Osp::Graphics::Bitmap* switchIcon = Utils::GetBitmapN(L"Icons/Switch.png");
	//switchStationsButton->SetNormalBackgroundBitmap(*switchIcon);
	//switchStationsButton->SetPressedBackgroundBitmap(*switchIcon);
	//switchStationsButton->SetNormalBitmap(Osp::Graphics::Point(0,0),*__pSwitchIcon);
	//switchStationsButton->SetPressedBitmap(Osp::Graphics::Point(0,0),*__pSwitchIcon);
	//delete switchIcon;

	/*
	 * Make To Station Edit Field
	 */
	y += heightBody; // cumulate y
	toStationEditField = new EditField();
	toStationEditField->Construct(
			Rectangle(border, y, stationWidth, heightBody),
			EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,
			GROUP_STYLE_BOTTOM);
	toStationEditField->SetTitleText(to);
	scrollPanel->AddControl(*toStationEditField);
	toStationEditField->AddTouchEventListener(*this);
	toStationEditField->SetEnabled(false);//prevents opening default text input
	toStationEditField->BeginBlock();

	/*
	 * Make a DateTimePicker element, this will give us an extra form to pick the date and time
	 * Carefull, this dateTimePicker must be destroyed in Destructor
	 */
	dateTimePicker = new DateTimePicker();
	dateTimePicker->Construct(pickTime);
	dateTimePicker->Set24HourNotationEnabled(true);
	dateTimePicker->AddDateTimeChangeEventListener(*this);

	/*
	 * DateTime Picker Edit Field. this element is also disabled, and when clicked it gives you the dateTimePicker
	 */
	y += heightBody + border; // cumulate y
	editTimeDateField = new EditField();
	editTimeDateField->Construct(Rectangle(border, y, widthBody, heightBody),
			EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,
			GROUP_STYLE_TOP);
	editTimeDateField->SetEnabled(false);
	editTimeDateField->SetText(dateTimePicker->GetDateTime().ToString());
	editTimeDateField->SetTitleText(pickTime);
	editTimeDateField->AddTouchEventListener(*this);
	scrollPanel->AddControl(*editTimeDateField);

	/*
	 * Make a group of Radio Buttons with on Depart and on arrival
	 * A radio group makes the buttons exclusive, if the one is selected, the other cant be
	 */
	y += heightBody; // cumulate y
	isDepart = new CheckButton();
	isDepart->Construct(Rectangle(border, y, widthBody, heightBody),
			CHECK_BUTTON_STYLE_RADIO_WITH_DIVIDER, BACKGROUND_STYLE_DEFAULT,
			false, depart, GROUP_STYLE_MIDDLE);
	isDepart->AddActionEventListener(*this);
	isDepart->SetActionId(IS_DEPARTURE, UNCHECKED, IS_DEPARTURE);
	scrollPanel->AddControl(*isDepart);
	y += heightBody;
	isArrivial = new CheckButton();
	isArrivial->Construct(Rectangle(border, y, widthBody, heightBody),
			CHECK_BUTTON_STYLE_RADIO_WITH_DIVIDER, BACKGROUND_STYLE_DEFAULT,
			false, arrival, GROUP_STYLE_BOTTOM);
	isArrivial->AddActionEventListener(*this);
	isArrivial->SetActionId(IS_ARRIVAL, UNCHECKED, IS_ARRIVAL);
	scrollPanel->AddControl(*isArrivial);
	// Create the RadioGroup
	RadioGroup *radioGroup = new RadioGroup();
	radioGroup->Construct();
	radioGroup->Add(*isDepart);
	radioGroup->Add(*isArrivial);
	//default must me set after the group is set
	isDepart->SetSelected(true); //default is alwayls on arrival

	AddControl(*scrollPanel);

	return true;
}

result FormRouteplanner::OnInitializing(void) {
	result r = E_SUCCESS;
	r = HeaderForm::OnInitializing(HEADER_ID_ROUTE_PLANNER);
	return r;
}

result FormRouteplanner::OnTerminating(void) {
	result r = E_SUCCESS;
	return r;
}

/*
 * IAction Event Listener
 */
void FormRouteplanner::OnActionPerformed(const Osp::Ui::Control& source,
		int actionId) {
	HeaderForm::OnActionPerformed(source, actionId);
	if (actionId == SEARCH_ACTION) {
		AppLog("Clicked FormRoutePlanner::search");
		Controller::GetInstance()->retrieveRoutePlannerResults();
	} else if (actionId == CLEAR_ACTION) {
		AppLog("Clicked FormRoutePlanner::clear");
		Controller::GetInstance()->clearRoutePlanner();
	} else if (actionId == SWITCH_ACTION) {
		AppLog("Clicked FormRoutePlanner::switch");
		Controller::GetInstance()->switchRequestStations();
	} else if (actionId == IS_ARRIVAL) {
		AppLog("The request must be on arrival time.");
		Controller::GetInstance()->setIsDeparture(false);
	} else if (actionId == IS_DEPARTURE) {
		AppLog("The request must be on departure time.");
		Controller::GetInstance()->setIsDeparture(true);
	}
}

/*
 * IDateTime Event Listener methods
 */
void FormRouteplanner::OnDateTimeChanged(const Osp::Ui::Control & source,
		int year, int month, int day, int hour, int minute) {
	DateTime newDate = dateTimePicker->GetDateTime();
	Controller::GetInstance()->setRoutePlannerTime(newDate);
}

void FormRouteplanner::OnDateTimeChangeCanceled(const Osp::Ui::Control & source) {

}
/*
 * ITouch Event Listerer methods
 */
void FormRouteplanner::OnTouchMoved(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormRouteplanner::OnTouchLongPressed(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormRouteplanner::OnTouchReleased(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormRouteplanner::OnTouchFocusIn(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormRouteplanner::OnTouchDoublePressed(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormRouteplanner::OnTouchFocusOut(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormRouteplanner::OnTouchPressed(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
	Controller* controller = Controller::GetInstance();
	if (source.Equals(*fromStationEditField)) {
		AppLog("Clicked FormRoutePlanner::fromStationEditField");

		//Station* from =  request->getFromStation();
		controller->selectStation(request->getFromStation());
	} else if (source.Equals(*toStationEditField)) {
		AppLog("Clicked FormRoutePlanner::toStationEditField");
		controller->selectStation(request->getToStation());
	} else if (source.Equals(*editTimeDateField)) {
		AppLog("Clicked FormRoutePlanner::EditDateTimeField");
		dateTimePicker->SetShowState(true);
		dateTimePicker->Show();
	}
}

void FormRouteplanner::RequestRedraw(bool show) const {
	AppLog("FormRouteplanner::RequestRedraw");
	Station* from = (request->getFromStation());
	Station* to = (request->getToStation());
	if (from != null) {
		fromStationEditField->SetText(from->getName());
	} else {
		fromStationEditField->SetText("");
	}
	if (to != null) {
		toStationEditField->SetText(to->getName());
	} else {
		toStationEditField->SetText("");
	}

	DateTime* time = (request->getDateTime());

	if (time != null) {
		dateTimePicker->SetDateTime(*time);
	} else {
		dateTimePicker->SetCurrentDateTime();
	}

	editTimeDateField->SetText(dateTimePicker->GetDateTime().ToString());
	Form::RequestRedraw(show);
}

void FormRouteplanner::recalculateComponents() {
	AppLog("Recalculate components!!");
	/*
	 * Calculate sizes for all controls
	 */
	Rectangle bounds = this->GetClientAreaBounds();
	scrollPanel->SetBounds(Rectangle(0,0,bounds.width,bounds.height));
	AppLog("width: %S", Integer::ToString(bounds.width).GetPointer());
	AppLog("width: %S", Integer::ToString(bounds.height).GetPointer());

	//int x = bounds.x;
	int y = 10;
	int border = 0.05 * bounds.width;
	int widthBody = 0.9 * bounds.width;

	int heightBody = bounds.height / 6;
	if (bounds.width > bounds.height)
		heightBody = bounds.width / 6;

	int stationWidth = 0.85 * widthBody;
	int switchButtonWidth = 0.15 * widthBody;


	/*
	 * Adjust bounds of the components
	 */
	fromStationEditField->SetBounds(Rectangle(border, y, stationWidth,heightBody));
	switchStationsButton->Construct(Rectangle(border + stationWidth, y,
					switchButtonWidth, heightBody * 2));
	switchStationsButton->SetBounds(Rectangle(border + stationWidth, y,switchButtonWidth, heightBody * 2));
	y += heightBody; // cummulate y
	toStationEditField->SetBounds(Rectangle(border, y, stationWidth, heightBody));
	//dateTimePicker->SetBound

	y += heightBody + border; // cummulate y
	editTimeDateField->SetBounds(Rectangle(border, y, widthBody, heightBody));

	y += heightBody+10; // cummulate y
	isDepart->SetBounds(Rectangle(border, y, widthBody, heightBody));
	y += heightBody;
	isArrivial->SetBounds(Rectangle(border, y, widthBody, heightBody));

	this->RequestRedraw(true);
}

