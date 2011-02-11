
#include "View/PlannerForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

PlannerForm::PlannerForm()
{
	this->request = null;
}

PlannerForm::~PlannerForm(void)
{
}

void PlannerForm::update(Request* request){
	this->request = request;
	from->Clear();
	to->Clear();
	if(request != null){
		if(request->getFromStation() != null)
			from->SetText(* request->getFromStation()->getName());
		if(request->getToStation() != null)
			to->SetText(* request->getToStation()->getName());
	}
}

bool PlannerForm::Initialize()
{
	//load some components from xml file
	Form::Construct(L"PLANNER_FORM");

	from = new EditField();
	from->Construct( Rectangle(5, 5, 230, 50), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 25);
	from->SetTitleText(L"From");
	AddControl(*from);
	from->AddTouchEventListener(*this);
	from->SetEnabled(false);//prevents opening default text input

	to = new EditField();
	to->Construct( Rectangle(5, 60, 230, 50), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 25);
	to->SetTitleText(L"To");
	AddControl(*to);
	to->AddTouchEventListener(*this);
	to->SetEnabled(false);//prevents opening default text input

	//let us pick a date and time in new frame
	dateTimePicker = new DateTimePicker();
	dateTimePicker->Construct("Pick date and time");
	dateTimePicker->Set24HourNotationEnabled(true);
	dateTimePicker->SetCurrentDateTime();
	dateTimePicker->AddDateTimeChangeEventListener(*this);

	switchStationsButton = static_cast<Button*>(GetControl(L"SWITCH_STATIONS", false));
	switchStationsButton->AddTouchEventListener(*this);

	editTimeDateField = static_cast<EditField*>(GetControl(L"EDIT_DATE_TIME_FIELD", false));
	editTimeDateField->AddTouchEventListener(*this);
	editTimeDateField->SetEnabled(false);
	editTimeDateField->SetText(dateTimePicker->GetDateTime().ToString());

	departCheckButton = static_cast<CheckButton*>(GetControl(L"DEPART", false));
	departCheckButton->SetSelected(true);

	SetSoftkeyActionId(SOFTKEY_0, ACTION_SEARCH);
	AddSoftkeyActionListener(SOFTKEY_0, *this);
	SetSoftkeyActionId(SOFTKEY_1, ACTION_BACK);
	AddSoftkeyActionListener(SOFTKEY_1, *this);

	return true;
}

result PlannerForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	return r;
}

result PlannerForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	delete dateTimePicker;
	return r;
}

void PlannerForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	BeTrains* app = (BeTrains*)BeTrains::GetInstance();
	switch ( actionId ) {
		case ACTION_SEARCH:
			request->setIsDeparture(departCheckButton->IsSelected());
			if(request->getFromStation() != null and request->getToStation() !=null)
				app->getFromInternet(request);
			break;
		case ACTION_BACK:
			app->cancelCurrentRequest();
		default:
			app->showMainMenu();
	}
}

void PlannerForm::searchAction(){
	BeTrains* app = (BeTrains*)BeTrains::GetInstance();
	app->showTripList();
}

void PlannerForm::OnTouchDoublePressed (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo){}
void PlannerForm::OnTouchFocusIn (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo){}
void PlannerForm::OnTouchFocusOut (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo){}
void PlannerForm::OnTouchLongPressed (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo){}
void PlannerForm::OnTouchMoved (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo){}
void PlannerForm::OnTouchPressed (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo){
	BeTrains* app = (BeTrains*)BeTrains::GetInstance();
	if(source.Equals(*from)){
		app->showRoutePlannerStationSelector(true);
	}else if(source.Equals(*to)){
		app->showRoutePlannerStationSelector(false);
	}else if(source.Equals(*editTimeDateField)){
		 dateTimePicker->SetShowState(true);
		 dateTimePicker->Show();
	}else if(source.Equals(*switchStationsButton)){
		request->switchStation();
		update(request); //sets information right
		RequestRedraw();
	}
}

void PlannerForm::OnTouchReleased (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo){}

void PlannerForm::OnDateTimeChangeCanceled (const Osp::Ui::Control &source){
	if(request->getDateTime() != null){
		editTimeDateField->SetText(request->getDateTime()->ToString());
	}else{
		DateTime dt;
		dateTimePicker->SetCurrentDateTime();
		editTimeDateField->SetText(dateTimePicker->GetDateTime().ToString());
	}
}

void PlannerForm::OnDateTimeChanged (const Osp::Ui::Control &source, int year, int month, int day, int hour, int minute){
	DateTime dt = dateTimePicker->GetDateTime();
	DateTime *dateTime = new DateTime(dt);
	request->setDateTime(dateTime);
	if(dateTime != null){
		editTimeDateField->SetText(dateTime->ToString());
	}
}
