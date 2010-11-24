
#include "PlannerSearchForm.h"
#include "BetrainsPrototype.h"
#include <FUiITouchEventListener.h>

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


PlannerSearchForm::PlannerSearchForm(void)
{
}

PlannerSearchForm::~PlannerSearchForm(void)
{
}

bool
PlannerSearchForm::Initialize()
{
	Form::Construct(L"IDF_PLANNER_SEARCH_");

	// set the listener for the two fields
	EditField* to = static_cast<EditField*>(GetControl(L"PLANNER_SEARCH_TO_STATION" ));
	EditField* from = static_cast<EditField*>(GetControl(L"PLANNER_SEARCH_FROM_STATION" ));
	to->AddTouchEventListener(*this);
	from->AddTouchEventListener(*this);
	return true;
}

result
PlannerSearchForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here
	SetSoftkeyActionId(SOFTKEY_0, Constants::PLANNER_SEARCH);
	AddSoftkeyActionListener(SOFTKEY_0, *this);
	SetSoftkeyActionId(SOFTKEY_1, Constants::BACK);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	AddFocusEventListener(*this);
	AddKeyEventListener(*this);
	AddTouchEventListener(*this);
	AddTouchModeChangedEventListener(*this);
	//page controls

	return r;
}

result
PlannerSearchForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}



void
PlannerSearchForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	BetrainsPrototype* app = (BetrainsPrototype*)this->GetParent();
	EditField* to = static_cast<EditField*>(GetControl(L"PLANNER_SEARCH_TO_STATION" ));
	EditField* from = static_cast<EditField*>(GetControl(L"PLANNER_SEARCH_FROM_STATION" ));

	String to_ = to->GetText();
	String from_ = from->GetText();
	AppLog("action id is %S",Integer::ToString(actionId).GetPointer());
	switch ( actionId ) {
		case Constants::PLANNER_SEARCH:
			app->showPlannerResults(from_,to_);
			break;
		case Constants::BACK:
			app->showMenu();
		default :
			app->showMenu();
	}
}

void
PlannerSearchForm::OnFocusGained(const Osp::Ui::Control &source)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnFocusLost(const Osp::Ui::Control &source)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnKeyLongPressed(const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnKeyPressed(const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnKeyReleased(const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnTouchDoublePressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnTouchFocusIn(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnTouchFocusOut(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnTouchLongPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnTouchMoved(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnTouchPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here
	AppLog("touch is caught !!");
	BetrainsPrototype* app = (BetrainsPrototype*)this->GetParent();
	app->showSearchStationName();
}

void
PlannerSearchForm::OnTouchReleased(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
PlannerSearchForm::OnTouchModeChanged(const Osp::Ui::Control& source, bool isInTouchMode)
{
	// TODO: Add your implementation codes here

}
