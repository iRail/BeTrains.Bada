
#include "View/StationSelectForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


StationSelectForm::StationSelectForm(void)
{
}

StationSelectForm::~StationSelectForm(void)
{
}

bool
StationSelectForm::Initialize()
{
	Form::Construct(L"StationSelectForm");
	return true;
}

result
StationSelectForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	//2
	vpScrollPanel = static_cast<ScrollPanel *> (GetControl(L"IDN_PANEL2", false));
	vpEditFiled = static_cast<EditField *>(GetControl(L"EditFieldInput",true));

	//3
	vpEditFiled->AddActionEventListener(*this);
	vpEditFiled ->AddScrollPanelEventListener(*this);
	//4
	vpEditFiled ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_LEFT, L"Done", ID_BUTTON_EDITFIELD_DONE);
	vpEditFiled ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_RIGHT, L"Close", ID_BUTTON_EDITFIELD_CLOSE);

	vpEditFiled->Show();
	vpEditFiled->SetKeypadEnabled(true);
	return r;
}

void StationSelectForm::setKeyboard(){
	vpEditFiled->ShowKeypad();
}

result
StationSelectForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

void StationSelectForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	/*
	switch (actionId) {
		case ID_BUTTON_EDITFIELD_DONE: {
				vpScrollPanel->CloseOverlayWindow();
				vpEditFiled->Draw();
				vpEditFiled->Show();
		}break;
		case ID_BUTTON_EDITFIELD_CLOSE:
			vpScrollPanel->CloseOverlayWindow();
			vpEditFiled->Draw();
			vpEditFiled->Show();
		break;
		default:
			break;
		}
	*/
}

//6
void StationSelectForm::OnOverlayControlCreated(const Osp::Ui::Control& source) {
	vpEditFiled->ShowKeypad();
}

void StationSelectForm::OnOverlayControlOpened(const Osp::Ui::Control& source) {

}

void StationSelectForm::OnOverlayControlClosed(const Osp::Ui::Control& source) {

 SetFocus();
}

void StationSelectForm::OnOtherControlSelected(const Osp::Ui::Control& source) {

}

