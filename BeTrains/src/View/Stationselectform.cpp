
#include "View/StationSelectForm.h"
#include "View/BeTrains.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base::Collection;

StationSelectForm::StationSelectForm(ArrayListT<Station *> * stations,Station* &selectedStation){
	this->stations = stations;
	this->selectedStation = selectedStation;
	suggestionStations.Construct(700);
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
	stationSuggestionList = static_cast<List *>(GetControl(L"StationSuggestionList",true));

	//3
	vpEditFiled->AddActionEventListener(*this);
	vpEditFiled->AddScrollPanelEventListener(*this);
	vpEditFiled->AddTextEventListener(*this);
	stationSuggestionList->AddItemEventListener(*this);
	//4
	vpEditFiled ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_LEFT, L"Done", ID_BUTTON_EDITFIELD_DONE);
	vpEditFiled ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_RIGHT, L"Close", ID_BUTTON_EDITFIELD_CLOSE);

	for(int i=0;i<stations->GetCount();i++){
		Station *station=null;
		stations->GetAt(i,station);
		stationSuggestionList->AddItem(station->getName(),null,null,null);
	}
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
	switch (actionId) {
		case ID_BUTTON_EDITFIELD_DONE:
			AppLog("Done");
		break;
		case ID_BUTTON_EDITFIELD_CLOSE:
			AppLog("Close");
		break;
		default:
		break;
	}
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

void StationSelectForm::StationSelectForm::OnTextValueChangeCanceled (const Osp::Ui::Control &source){

}

void StationSelectForm::StationSelectForm::OnTextValueChanged (const Osp::Ui::Control &source){
	String inputText = vpEditFiled->GetText();
	inputText.ToLower();
	stationSuggestionList->RemoveAllItems();
	suggestionStations.RemoveAll();
	for(int i=0;i<stations->GetCount();i++){
		Station *station=null;
		stations->GetAt(i,station);
		String stationName;
		station->getName()->ToLower(stationName);
		if(stationName.StartsWith(inputText,0)){
			stationSuggestionList->AddItem(station->getName(),null,null,null);
			suggestionStations.Add(station);
		}
	}
	stationSuggestionList->RequestRedraw();
}

void StationSelectForm::OnItemStateChanged(const Control &source, int index, int itemId, ItemStatus status){
	if(status == Osp::Ui::ITEM_SELECTED){
		BeTrains* app = (BeTrains*)this->GetParent();
		suggestionStations.GetAt(index,selectedStation);
		AppLog("station selected: %S",selectedStation->getName()->GetPointer());
		app->showMainMenu();
	}

}
