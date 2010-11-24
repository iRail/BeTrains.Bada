#include "SearchStationName.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

SearchStationName::SearchStationName(void) {
}

SearchStationName::~SearchStationName(void) {
}

bool SearchStationName::Initialize() {
	Form::Construct(L"IDF_FORM2");

	pScrollPanel = static_cast<ScrollPanel *> (GetControl(L"IDC_SCROLLPANEL1",false));
	 pEditField = static_cast<EditField *>(GetControl(L"IDPC_EDITFIELD1",true));

	//3
	 pEditField->AddActionEventListener(*this);
	 pEditField ->AddScrollPanelEventListener(*this);
	//4
	 pEditField ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_LEFT, L"Done", ID_BUTTON_EDITFIELD_DONE);
	 pEditField ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_RIGHT, L"Close", ID_BUTTON_EDITFIELD_CLOSE);



	//AppLog("hmm %S",stations[0]);
	return true;
}

result SearchStationName::OnInitializing(void) {
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result SearchStationName::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void SearchStationName::OnActionPerformed(const Osp::Ui::Control& source,
		int actionId) {

	switch (actionId) {
	case ID_BUTTON_EDITFIELD_DONE: {
		pScrollPanel->CloseOverlayWindow();
		pEditField->Draw();
		pEditField->Show();

	}
		break;
	case ID_BUTTON_EDITFIELD_CLOSE:
		pScrollPanel->CloseOverlayWindow();
		pEditField->Draw();
		pEditField->Show();
		break;

	default:
		break;
	}
}

//6
void SearchStationName::OnOverlayControlCreated(const Osp::Ui::Control& source) {

}

void SearchStationName::OnOverlayControlOpened(const Osp::Ui::Control& source) {

}

void SearchStationName::OnOverlayControlClosed(const Osp::Ui::Control& source) {

	SetFocus();
}

void SearchStationName::OnOtherControlSelected(const Osp::Ui::Control& source) {

}

