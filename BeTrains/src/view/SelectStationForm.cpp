/*
 * SelectStationForm.cpp
 *
 *  Created on: 10 sep. 2011
 *      Author: Bart
 */

#include "view/SelectStationForm.h"
#include "controller/Controller.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

SelectStationForm::SelectStationForm(void) {
	AppLog("SelectStation constructor");
	selectedStation = null;
}

SelectStationForm::~SelectStationForm(void) {
}

//station must be pointer to a pointer (*& or **) so that we fill in the value in correctly
bool SelectStationForm::Initialize() {
	this->RemoveAllControls();
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_INDICATOR);
	this->SetOrientation(ORIENTATION_AUTOMATIC);
	this->AddOrientationEventListener(*this);
	/*
	* Calculate sizes for all controls
	*/
	Rectangle bounds = this->GetClientAreaBounds();
	int itemHeight = bounds.height/10;
	if(bounds.width>bounds.height)
		itemHeight = bounds.width /10;
	//AppLog("height:%S",Integer::ToString(bounds.height).GetPointer());
	/*
	 * create SCROLLPANEL
	 */
	scrollPanel = new ScrollPanel();
	scrollPanel->Construct(Rectangle(0, 0, bounds.width, bounds.height));
	//scrollPanel->SetBackgroundColor(Color::COLOR_GREEN);
	AddControl(*scrollPanel);

	/*
	 * Create EditField, here the users input station names
	 */
	editField = new EditField();
	editField->Construct(Rectangle(0,0,bounds.width,itemHeight),EDIT_FIELD_STYLE_NORMAL,INPUT_STYLE_OVERLAY,false,60,GROUP_STYLE_NONE);
	editField->AddActionEventListener(*this);
	editField->AddTextEventListener(*this);
	editField->BeginBlock();
	scrollPanel->AddControl(*editField);
	editField ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_LEFT, L"Cancel", CANCEL_ACTION);
	editField->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_RIGHT,L"Clear",CLEAR_ACTION);
	editField->SetKeypadEnabled(true);
	//AppLog("editfieldheight %S",Integer::ToString(editField->GetHeight()).GetPointer());
	/*
	 * Create a list of all stations
	 */
	stations = AppData::GetInstance()->getStationList();

	/*
	 * Suggestion List
	 */
	stationSuggestionList = new ListView ();
	stationSuggestionList->Construct(Rectangle(0,editField->GetHeight(),bounds.width,bounds.height-itemHeight),true,false);
	stationSuggestionList->SetTextOfEmptyList("empty list");
	//stationSuggestionList->Construct(Rectangle(0,itemHeight,bounds.width,bounds.height-itemHeight),LIST_STYLE_NORMAL,LIST_ITEM_SINGLE_TEXT,35,0,240,0);

	stationSuggestionList->SetItemProvider(*this);
	stationSuggestionList->AddListViewItemEventListener(*this);
	scrollPanel->AddControl(*stationSuggestionList);
	updateList();

	return true;
}

void
SelectStationForm::setStation(Station* &selectStation_){
	editField->SetText("");
	updateList();
	selectedStation = &selectStation_;
}


result SelectStationForm::OnInitializing() {
	result r = E_SUCCESS;
	this->editField->ShowKeypad();
	this->RequestRedraw(true);
	AppLog("SelectStationForm::OnInitializing()");
	return r;
}

result SelectStationForm::OnTerminating(void) {
	result r = E_SUCCESS;
	return r;
}

//implement IActionEventListener
void SelectStationForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId){
	if( actionId == CLEAR_ACTION){
		editField->SetText(L"");
		updateList();
		editField->RequestRedraw(true);
	}
	else if( actionId == CANCEL_ACTION){
		selectedStation = null;
		Controller::GetInstance()->setPreviousForm();
	}
}

/*
 * ITextValueChangedListener
 */
void  SelectStationForm::OnTextValueChangeCanceled (const Osp::Ui::Control &source){}

void  SelectStationForm::OnTextValueChanged (const Osp::Ui::Control &source){
	//AppLog("text value changed");
	updateList();
}

//this method fires when we select an listitem
void
SelectStationForm::OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status)
{
	//AppLog("SelectStationForm::OnListViewItemStateChanged index:%S",Integer::ToString(index).GetPointer());
	Station* selectedStation_;
	suggestionStations.GetAt(index,selectedStation_);
	AppLog("Select Station %S",selectedStation_->getNameN()->GetPointer());
	*selectedStation = selectedStation_;
	Controller::GetInstance()->GetInstance()->setPreviousForm();
}

void
SelectStationForm::OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction)
{
	//AppLog("SelectStationForm::OnListViewItemSwept index:%S",Integer::ToString(index).GetPointer());
}

void
SelectStationForm::OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus state)
{
	//AppLog("SelectStationForm::OnListViewContextItemStateChanged index:%S",Integer::ToString(index).GetPointer());
}

int
SelectStationForm::GetItemCount(void)
{
	return suggestionStations.GetCount();
}

Osp::Ui::Controls::ListItemBase*
SelectStationForm::CreateItem(int index, int itemWidth)
{
	Rectangle bounds = this->GetClientAreaBounds();
	int itemHeight = bounds.height* 0.105;
	if(bounds.width>bounds.height)
		itemHeight = bounds.width * 0.105;

	SimpleItem* item = new SimpleItem();
    item->Construct(Osp::Graphics::Dimension(itemWidth,itemHeight), LIST_ANNEX_STYLE_NORMAL);
    Station* station;
    suggestionStations.GetAt(index,station);
    String stationName = station->getName();
    item->SetElement(stationName);
    return item;
}

bool
SelectStationForm::DeleteItem(int index, Osp::Ui::Controls::ListItemBase* pItem, int itemWidth)
{
    delete pItem;
    pItem = null;
    return true;
}

/*
 * Loads all stations, that begin with the text in the editField
 * also loads when the text is empty
 * then it redraws the list
 */
void SelectStationForm::updateList()
{
	String inputText = editField->GetText();
	inputText.ToLower();
	suggestionStations.RemoveAll();
	if(! inputText.IsEmpty()){
		for(int i=0;i<stations->GetCount();i++){
			Station *station=null;
			stations->GetAt(i,station);
			String stationName;
			station->getName().ToLower(stationName);
			if(stationName.StartsWith(inputText,0)){
				suggestionStations.Add(station);
			}
		}
		//TODO make performance better by checking size and see if you can prune suggestion list, is much better then copy full table each time
	}else{
		suggestionStations.AddItems(*stations);
	}
	stationSuggestionList->UpdateList();
	stationSuggestionList->Draw();
	stationSuggestionList->Show();
}


//implement IOrientationEventListener
void SelectStationForm::OnOrientationChanged(const Control& source, OrientationStatus orientationStatus){
	/*
	* Calculate sizes for all controls
	*/
	Rectangle bounds = this->GetClientAreaBounds();
	int itemHeight = bounds.height/11;
	if(bounds.width>bounds.height)
		itemHeight = bounds.width /11;
	scrollPanel->SetBounds(0, 0, bounds.width, bounds.height);
	editField->SetBounds(0,0,bounds.width,itemHeight);
	stationSuggestionList->SetBounds(0,editField->GetHeight(),bounds.width,bounds.height-itemHeight);
	this->RequestRedraw(true);
}
