
#include "View/PlannerForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

PlannerForm::PlannerForm(Request* request)
{
	this->request = request;
}

PlannerForm::~PlannerForm(void)
{
}

bool PlannerForm::Initialize()
{
	Form::Construct(L"PLANNER_FORM");
	from = static_cast<EditField*>(GetControl(L"FROM_FIELD"));
	to = static_cast<EditField*>(GetControl(L"TO_FIELD"));
	if(request->getFromStation() != null)
		from->SetText(* request->getFromStation()->getName());
	if(request->getToStation() != null)
		to->SetText(* request->getToStation()->getName());
	SetSoftkeyActionId(SOFTKEY_0, ACTION_SEARCH);
	AddSoftkeyActionListener(SOFTKEY_0, *this);
	SetSoftkeyActionId(SOFTKEY_1, ACTION_BACK);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	from->AddTouchEventListener(*this);
	to->AddTouchEventListener(*this);
	from->SetEnabled(false);
	to->SetEnabled(false);
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
	return r;
}

void PlannerForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	BeTrains* app = (BeTrains*)BeTrains::GetInstance();
	switch ( actionId ) {
		case ACTION_SEARCH:
			searchAction();
			break;
		case ACTION_BACK:
			AppLog("pressed back button");
			app->showMainMenu();
		default:
			app->showMainMenu();
	}
}

void PlannerForm::searchAction(){
	BeTrains* app = (BeTrains*)BeTrains::GetInstance();
	String from_ = from->GetText();
	String to_ = to->GetText();
	app->showMap();
	//TODO
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
	}
	//TODO
}
void PlannerForm::OnTouchReleased (const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo){}

