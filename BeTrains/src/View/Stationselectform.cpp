
#include "View/Stationselectform.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


Stationselectform::Stationselectform(void)
{
}

Stationselectform::~Stationselectform(void)
{
	editField = null;
	list = null;
	scrollPanel = null;
}

bool
Stationselectform::Initialize()
{
	Form::Construct(L"StationSelectForm");
	editField = static_cast<EditField *>(GetControl(L"StationEditField",true));
	list = static_cast<List *> (GetControl(L"StationSugestionList", false));
	scrollPanel = static_cast<ScrollPanel *> (GetControl(L"IDN_PANEL1", false));
	editField->AddTextEventListener(*this);
	return true;
}

result
Stationselectform::OnInitializing(void)
{
	result r = E_SUCCESS;
	//Keypad * keypad = new Keypad();
	//keypad->Construct(KEYPAD_STYLE_NORMAL, KEYPAD_MODE_ALPHA);
	//keypad->AddTextEventListener(*this);

	//keypad->SetShowState(true);
	//keypad->Show();
	// TODO: Add your initialization code here

	return r;
}

result
Stationselectform::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

void Stationselectform::OnTextValueChangeCanceled (const Osp::Ui::Control &source){
	String t = editField->GetText();
	AppLog("text value canceled: %S", t.GetPointer());
}
void Stationselectform::OnTextValueChanged (const Osp::Ui::Control &source){
	AppLog("value changed");
	String t = editField->GetText();
	AppLog("text value changed: %S", t.GetPointer());
}

