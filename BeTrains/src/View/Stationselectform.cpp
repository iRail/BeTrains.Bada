
#include "View/StationSelectForm.h"
#include "View/BeTrains.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base::Collection;

StationSelectForm::StationSelectForm(){
	BeTrains* app = (BeTrains*)BeTrains::GetInstance();
	stations = app->getStationList();
	suggestionStations.Construct(700);
}

void StationSelectForm::update(bool isFromStation){
	this->isFromStation = isFromStation;
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
	scrollPanel = static_cast<ScrollPanel *> (GetControl(L"IDN_PANEL2", false));
	editField = static_cast<EditField *>(GetControl(L"EditFieldInput",true));
	stationSuggestionList = static_cast<List *>(GetControl(L"StationSuggestionList",true));

	editField->AddActionEventListener(*this);
	editField->AddScrollPanelEventListener(*this);
	editField->AddTextEventListener(*this);
	stationSuggestionList->AddItemEventListener(*this);

	editField ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_LEFT, L"Done", ID_BUTTON_EDITFIELD_DONE);
	editField ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_RIGHT, L"Close", ID_BUTTON_EDITFIELD_CLOSE);

	for(int i=0;i<stations->GetCount();i++){
		Station *station=null;
		stations->GetAt(i,station);
		stationSuggestionList->AddItem(station->getName(),null,null,null);
		suggestionStations.Add(station);
	}
	return r;
}

void StationSelectForm::setKeyboard(){
	editField->ShowKeypad();
}

result StationSelectForm::OnTerminating(void){
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


void StationSelectForm::OnOverlayControlCreated(const Osp::Ui::Control& source) {
	editField->ShowKeypad();
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
	String inputText = editField->GetText();
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
		Station* selectedStation; //pass back to app
		suggestionStations.GetAt(index,selectedStation);
		//AppLog("station selected: %S",selectedStation->getName()->GetPointer());
		BeTrains* app = (BeTrains*)BeTrains::GetInstance();
		app->routePlannerSelectStation(isFromStation,selectedStation);
	}

}
