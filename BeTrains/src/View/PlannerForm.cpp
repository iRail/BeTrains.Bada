
#include "View/PlannerForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

PlannerForm::PlannerForm(void)
{
}

PlannerForm::~PlannerForm(void)
{
}

bool PlannerForm::Initialize()
{
	Form::Construct(L"PLANNER_FORM");
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
	return r;
}

void PlannerForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	BeTrains* app = (BeTrains*)this->GetParent();
	switch ( actionId ) {
		case ACTION_SEARCH:
			searchAction(app);
			break;
		case ACTION_BACK:
			AppLog("pressed back button");
			app->showMainMenu();
		default :
			app->showMainMenu();
	}
}

void PlannerForm::searchAction(BeTrains* app){
	EditField* from = static_cast<EditField*>(GetControl(L"FROM_FIELD"));
	EditField* to = static_cast<EditField*>(GetControl(L"TO_FIELD"));
	String from_ = from->GetText();
	String to_ = to->GetText();
	//app->showPlannerResults(from_,to_);
	//TODO
}

