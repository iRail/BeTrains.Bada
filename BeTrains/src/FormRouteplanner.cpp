#include "FormRouteplanner.h"
#include "Controller.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

FormRouteplanner::FormRouteplanner(void) {
	toStation=null;
	fromStation=null;
}

FormRouteplanner::~FormRouteplanner(void) {
	delete dateTimePicker;
}

bool FormRouteplanner::Initialize() {
	this->RemoveAllControls();
	HeaderForm::Initialize(true, true); //enables left and right softkey
	this->SetSoftkeyText(SOFTKEY_0, "Search");
	this->SetSoftkeyActionId(SOFTKEY_0, SEARCH_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_0,*this);

	this->SetSoftkeyText(SOFTKEY_1, "Clear");
	this->SetSoftkeyActionId(SOFTKEY_1, CLEAR_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_1,*this);

	/*
	 * Calculate sizes for all controls
	 */
	Rectangle bounds = this->GetClientAreaBounds();
	//int x = bounds.x;
	int y = 10;
	int border = 0.05 * bounds.width;
	int widthBody = 0.9 * bounds.width;

	int heightBody = int( 1.0 / 6.0 * double(bounds.height));

	int stationWidth = 0.85 * widthBody;
	int switchButtonWidth = 0.15 * widthBody;
	/*
	 * Make From Station Edit Field
	 */
	fromStationEditField = new EditField();
	fromStationEditField->Construct( Rectangle(border, y, stationWidth, heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,GROUP_STYLE_TOP);
	fromStationEditField->SetTitleText(L"From");
	AddControl(*fromStationEditField);
	fromStationEditField->AddTouchEventListener(*this);
	fromStationEditField->SetEnabled(false);//prevents opening default text input
	fromStationEditField->BeginBlock();
	/*
	 * Make Switch Button
	 */
	switchStationsButton = new Button();
	switchStationsButton->Construct(Rectangle(border+stationWidth, y, switchButtonWidth, heightBody*2));
	switchStationsButton->SetActionId(SWITCH_ACTION);
	switchStationsButton->SetText(L"Sw"); //Switch Stations
	AddControl(*switchStationsButton);
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
	toStationEditField->Construct( Rectangle(border, y, stationWidth, heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,GROUP_STYLE_BOTTOM);
	toStationEditField->SetTitleText(L"To");
	AddControl(*toStationEditField);
	toStationEditField->AddTouchEventListener(*this);
	toStationEditField->SetEnabled(false);//prevents opening default text input
	toStationEditField->BeginBlock();

	/*
	 * Make a DateTimePicker element, this will give us an extra form to pick the date and time
	 * Carefull, this dateTimePicker must be destroyed in Destructor
	 */
	dateTimePicker = new DateTimePicker();
	dateTimePicker->Construct("Pick date and time");
	dateTimePicker->Set24HourNotationEnabled(true);
	dateTimePicker->AddDateTimeChangeEventListener(*this);

	/*
	 * DateTime Picker Edit Field. this element is also disabled, and when clicked it gives you the dateTimePicker
	 */
	y += heightBody + border; // cumulate y
	editTimeDateField = new EditField();
	editTimeDateField->Construct( Rectangle(border, y, widthBody, heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,GROUP_STYLE_TOP);
	editTimeDateField->SetEnabled(false);
	editTimeDateField->SetText(dateTimePicker->GetDateTime().ToString());
	editTimeDateField->SetTitleText(L"Pick Time and Date");
	editTimeDateField->AddTouchEventListener(*this);
	AddControl(*editTimeDateField);


	/*
	 * Make a group of Radio Buttons with on Depart and on arrival
	 * A radio group makes the buttons exclusive, if the one is selected, the other cant be
	 */
	y += heightBody; // cumulate y
	isDepart = new CheckButton();
	isDepart->Construct(Rectangle(border, y, widthBody, heightBody), CHECK_BUTTON_STYLE_RADIO_WITH_DIVIDER, BACKGROUND_STYLE_DEFAULT, false, L"Depart",GROUP_STYLE_MIDDLE);

	AddControl(*isDepart);
	y += heightBody;
	isArrivial = new CheckButton();
	isArrivial->Construct(Rectangle(border, y, widthBody, heightBody), CHECK_BUTTON_STYLE_RADIO_WITH_DIVIDER,BACKGROUND_STYLE_DEFAULT, false, L"Arrival",GROUP_STYLE_BOTTOM);
	AddControl(*isArrivial);
	// Create the RadioGroup
	RadioGroup *radioGroup = new RadioGroup();
	radioGroup->Construct();
	radioGroup->Add(*isDepart);
	radioGroup->Add(*isArrivial);
	//default must me set after the group is set
	isDepart->SetSelected(true); //default is alwayls on arrival
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
void FormRouteplanner::OnActionPerformed(const Osp::Ui::Control& source,int actionId) {
	HeaderForm::OnActionPerformed(source,actionId);
	if(actionId == SEARCH_ACTION){
		AppLog("Clicked FormRoutePlanner::search");
	}else if(actionId == CLEAR_ACTION){
		AppLog("Clicked FormRoutePlanner::clear");
	}else if(actionId == SWITCH_ACTION){
		AppLog("Clicked FormRoutePlanner::switch");
	}
}


/*
 * IDateTime Event Listener methods
 */
void FormRouteplanner::OnDateTimeChanged(const Osp::Ui::Control & source, int year, int month, int day, int hour, int minute)
{
	//TODO update
}

void FormRouteplanner::OnDateTimeChangeCanceled(const Osp::Ui::Control & source){
	//TODO reset time
}
/*
 * ITouch Event Listerer methods
 */
void FormRouteplanner::OnTouchMoved(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormRouteplanner::OnTouchLongPressed(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormRouteplanner::OnTouchReleased(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormRouteplanner::OnTouchFocusIn(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormRouteplanner::OnTouchDoublePressed(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormRouteplanner::OnTouchFocusOut(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormRouteplanner::OnTouchPressed(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{
	Controller* controller = Controller::GetInstance();
	if(source.Equals(*fromStationEditField)){
		AppLog("Clicked FormRoutePlanner::fromStationEditField");
		controller->selectStation(fromStation);
	}else if(source.Equals(*toStationEditField)){
		AppLog("Clicked FormRoutePlanner::toStationEditField");
		controller->selectStation(toStation);
	}else if(source.Equals(*editTimeDateField)){
		AppLog("Clicked FormRoutePlanner::EditDateTimeField");
		dateTimePicker->SetShowState(true);
		dateTimePicker->Show();
	}
}

/*
 * Setters //TODO this will be replaced and deleted all, it will be a request
 */
void FormRouteplanner::setFromStation(Station* fromStation_){
	this->fromStation = fromStation_;
}
void FormRouteplanner::setToStation(Station* toStation_){
	this->toStation = toStation_;
}

void FormRouteplanner::setDateTime(DateTime dateTime_){
	this->dateTime = dateTime_;
}

void FormRouteplanner::setIsSearchDeparture(bool isSearchDeparture_){
	this->isSearchDeparture = isSearchDeparture_;
}

void FormRouteplanner::RequestRedraw (bool show) const{
	AppLog("FormRouteplanner::RequestRedraw");
	if(toStation != null){
		toStationEditField->SetText(toStation->getName());
	}
	if(fromStation != null){
		fromStationEditField->SetText(fromStation->getName());
	}
	Form::RequestRedraw(show);
}
