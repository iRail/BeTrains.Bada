#include "FormLiveboard.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

FormLiveboard::FormLiveboard(void) {
}

FormLiveboard::~FormLiveboard(void) {
}

bool FormLiveboard::Initialize() {
	HeaderForm::Initialize(true,false);
	this->SetSoftkeyText(SOFTKEY_0,"Search Liveboard");
	this->SetSoftkeyActionId(SOFTKEY_0,SEARCH_ACTION);
	return true;
}

result FormLiveboard::OnInitializing(void) {
	result r = E_SUCCESS;
	r = HeaderForm::OnInitializing(HEADER_ID_LIVEBOARD);
	return r;
}

result FormLiveboard::OnTerminating(void) {
	result r = E_SUCCESS;
	return r;
}

void FormLiveboard::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	HeaderForm::OnActionPerformed(source,actionId);
}

