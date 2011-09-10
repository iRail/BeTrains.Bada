#include "FormRouteplanner.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

FormRouteplanner::FormRouteplanner(void) {
}

FormRouteplanner::~FormRouteplanner(void) {
}

bool FormRouteplanner::Initialize() {
	HeaderForm::Initialize(true, false);
	this->SetSoftkeyText(SOFTKEY_0, "Search Route");
	this->SetSoftkeyActionId(SOFTKEY_0, SEARCH_ACTION);

	Rectangle bounds = this->GetClientAreaBounds();
	//int x = bounds.x;
	int y = 10;
	int border = 0.05 * bounds.width;
	int widthBody = 0.9 * bounds.width;

	int heightBody = int( 1.0 / 6.0 * double(bounds.height));


	fromStationEditField = new EditField();
	fromStationEditField->Construct( Rectangle(border, y, widthBody, heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,GROUP_STYLE_TOP);
	fromStationEditField->SetTitleText(L"From");
	AddControl(*fromStationEditField);
	//fromStationEditField->AddTouchEventListener(*this);
	fromStationEditField->SetEnabled(false);//prevents opening default text input
	fromStationEditField->BeginBlock();

	y += heightBody;

	toStationEditField = new EditField();
	toStationEditField->Construct( Rectangle(border, y, widthBody, heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,GROUP_STYLE_BOTTOM);
	toStationEditField->SetTitleText(L"To");
	AddControl(*toStationEditField);
	//toStationEditField->AddTouchEventListener(*this);
	toStationEditField->SetEnabled(false);//prevents opening default text input
	toStationEditField->BeginBlock();

	//let us pick a date and time in new frame
	dateTimePicker = new DateTimePicker();
	dateTimePicker->Construct("Pick date and time");
	dateTimePicker->Set24HourNotationEnabled(true);
	//dateTimePicker->AddDateTimeChangeEventListener(*this);

	/*
	switchStationsButton = new Button();
	switchStationsButton->Construct(Rectangle(240-25,35,20,50));
	switchStationsButton->SetActionId(IDC_SWITCH);
	//switchStationsButton->SetText(L"Switch Stations");
	AddControl(*switchStationsButton);
	switchStationsButton->AddActionEventListener(*this);
	Osp::Graphics::Bitmap* switchIcon = Utils::GetBitmapN(L"Icons/Switch.png");
	switchStationsButton->SetNormalBackgroundBitmap(*switchIcon);
	switchStationsButton->SetPressedBackgroundBitmap(*switchIcon);
	//switchStationsButton->SetNormalBitmap(Osp::Graphics::Point(0,0),*__pSwitchIcon);
	//switchStationsButton->SetPressedBitmap(Osp::Graphics::Point(0,0),*__pSwitchIcon);
	delete switchIcon;
	*/

	y += heightBody + border;

	editTimeDateField = new EditField();
	editTimeDateField->Construct( Rectangle(border, y, widthBody, heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,GROUP_STYLE_TOP);
	//editTimeDateField->AddTouchEventListener(*this);
	editTimeDateField->SetEnabled(false);
	editTimeDateField->SetText(dateTimePicker->GetDateTime().ToString());
	editTimeDateField->SetTitleText(L"Pick Time and Date");
	//editTimeDateField->AddTouchEventListener(*this);
	AddControl(*editTimeDateField);

	y += heightBody;
	// Create CheckButtons
	isDepart = new CheckButton();
	isDepart->Construct(Rectangle(border, y, widthBody, heightBody), CHECK_BUTTON_STYLE_RADIO_WITH_DIVIDER, BACKGROUND_STYLE_DEFAULT, false, L"Depart",GROUP_STYLE_MIDDLE);
	y += heightBody;
	isArrivial = new CheckButton();
	isArrivial->Construct(Rectangle(border, y, widthBody, heightBody), CHECK_BUTTON_STYLE_RADIO_WITH_DIVIDER,BACKGROUND_STYLE_DEFAULT, false, L"Arrival",GROUP_STYLE_BOTTOM);
	// Add CheckButtons to the Form.
	AddControl(*isDepart);
	AddControl(*isArrivial);

	// Create a RadioGroup
	RadioGroup *radioGroup = new RadioGroup();
	radioGroup->Construct();
	// Add CheckButtons to the RadioGroup
	radioGroup->Add(*isDepart);
	radioGroup->Add(*isArrivial);
	isDepart->SetSelected(true);

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

void FormRouteplanner::OnActionPerformed(const Osp::Ui::Control& source,int actionId) {
	HeaderForm::OnActionPerformed(source,actionId);
}

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
