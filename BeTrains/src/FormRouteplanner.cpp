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
	int x = bounds.x;
	int y = 10;
	int leftMargin = 0.1 * bounds.width;
	int widthBody = 0.8 * bounds.width;

	int heightBody = int( 1.0 / 6.0 * double(bounds.height));


	fromStationEditField = new EditField();
	fromStationEditField->Construct( Rectangle(x+leftMargin, y, widthBody, heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,GROUP_STYLE_TOP);
	fromStationEditField->SetTitleText(L"From");
	AddControl(*fromStationEditField);
	//fromStationEditField->AddTouchEventListener(*this);
	fromStationEditField->SetEnabled(false);//prevents opening default text input
	fromStationEditField->BeginBlock();

	y += heightBody + 10;

	toStationEditField = new EditField();
	toStationEditField->Construct( Rectangle(x+leftMargin, y, widthBody, heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,GROUP_STYLE_BOTTOM);
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

	y += heightBody + 10;

	editTimeDateField = new EditField();
	editTimeDateField->Construct( Rectangle(x+leftMargin, y, widthBody, heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100,GROUP_STYLE_TOP);
	//editTimeDateField->AddTouchEventListener(*this);
	editTimeDateField->SetEnabled(false);
	editTimeDateField->SetText(dateTimePicker->GetDateTime().ToString());
	editTimeDateField->SetTitleText(L"Pick Time and Date");
	//editTimeDateField->AddTouchEventListener(*this);
	AddControl(*editTimeDateField);

	/*
	// Create CheckButtons
	CheckButton *__pCheckButton1 = new CheckButton();
	__pCheckButton1->Construct(Rectangle(5, 168, 230, 40), CHECK_BUTTON_STYLE_RADIO_WITH_DIVIDER, BACKGROUND_STYLE_DEFAULT, false, L"Depart",GROUP_STYLE_MIDDLE);

	CheckButton *__pCheckButton2 = new CheckButton();

	__pCheckButton2->Construct(Rectangle(5, 208, 230, 40), CHECK_BUTTON_STYLE_RADIO_WITH_DIVIDER,BACKGROUND_STYLE_DEFAULT, false, L"Arrival",GROUP_STYLE_BOTTOM);
	// Add CheckButtons to the Form.
	__parentForm->AddControl(*__pCheckButton1);
	__parentForm->AddControl(*__pCheckButton2);

	// Create a RadioGroup
	RadioGroup *__pGroup = new RadioGroup();
	__pGroup->Construct();
	// Add CheckButtons to the RadioGroup
	__pGroup->Add(*__pCheckButton1);
	__pGroup->Add(*__pCheckButton2);
	__pCheckButton1->SetSelected(true);
	*/


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
