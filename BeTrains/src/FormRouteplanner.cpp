#include "FormRouteplanner.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

FormRouteplanner::FormRouteplanner(void) {
}

FormRouteplanner::~FormRouteplanner(void) {
}

bool FormRouteplanner::Initialize() {
	HeaderForm::Initialize(true, false);
	this->SetSoftkeyText(SOFTKEY_0, "Search Route");
	this->SetSoftkeyActionId(SOFTKEY_0, SEARCH_ACTION);
	//Form::Draw();
	return true;
}

result FormRouteplanner::OnInitializing(void) {
	result r = E_SUCCESS;
	return r;
}

result FormRouteplanner::OnTerminating(void) {
	result r = E_SUCCESS;
	return r;
}

void FormRouteplanner::OnActionPerformed(const Osp::Ui::Control& source,int actionId) {
	HeaderForm::OnActionPerformed(source,actionId);
}

