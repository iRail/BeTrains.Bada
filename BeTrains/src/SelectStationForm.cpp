/*
 * SelectStationForm.cpp
 *
 *  Created on: 10 sep. 2011
 *      Author: Bart
 */

#include "SelectStationForm.h"
#include "Controller.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

SelectStationForm::SelectStationForm(void) {
	AppLog("SelectStation constructor");
}

SelectStationForm::~SelectStationForm(void) {
}

bool SelectStationForm::Initialize() {
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_INDICATOR);
	this->SetOrientation(ORIENTATION_AUTOMATIC);
	/*
	* Calculate sizes for all controls
	*/
	Rectangle bounds = this->GetClientAreaBounds();
	int height = bounds.height /9;
	AppLog("height:%S",Integer::ToString(bounds.height).GetPointer());
	/*
	 * create SCROLLPANEL
	 */
	scrollPanel = new ScrollPanel();
	scrollPanel->Construct(Rectangle(0, 0, bounds.width, bounds.height));
	//scrollPanel->SetBackgroundColor(Color::COLOR_GREEN);
	AddControl(*scrollPanel);
	/*
	 * Create EditField, here the users input stationnames
	 */
	editField = new EditField();
	editField->Construct(Rectangle(0,0,bounds.width,height),EDIT_FIELD_STYLE_NORMAL,INPUT_STYLE_OVERLAY,false,60,GROUP_STYLE_NONE);
	//editField->AddActionEventListener(*this);
	//editField->AddScrollPanelEventListener(*this);
	//editField->AddTextEventListener(*this);
	scrollPanel->AddControl(*editField);
	//editField->BeginBlock();
	editField ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_LEFT, L"Cancel", CANCEL_ACTION);
	editField->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_RIGHT,L"Clear",CLEAR_ACTION);
	editField->SetKeypadEnabled(true);
	//editField->ShowKeypad();
	//editField->SetShowState(true);
	//editField->SetFocus();

	/*
	 * Create a list of all stations
	 */
	stations = AppData::GetInstance()->getStationList();

	/*
	 * Suggestion List
	 */
	stationSuggestionList = new ListView ();
	stationSuggestionList->Construct(Rectangle(0,height,bounds.width,bounds.height-height),true,false);
	stationSuggestionList->SetTextOfEmptyList("empty list");
	//stationSuggestionList->Construct(Rectangle(0,height,bounds.width,bounds.height-height),LIST_STYLE_NORMAL,LIST_ITEM_SINGLE_TEXT,35,0,240,0);

	stationSuggestionList->SetItemProvider(*this);
	stationSuggestionList->AddListViewItemEventListener(*this);
	scrollPanel->AddControl(*stationSuggestionList);

	return true;
}

result SelectStationForm::OnInitializing() {
	result r = E_SUCCESS;
	this->editField->SetFocus();
	this->editField->ShowKeypad();
	this->RequestRedraw(true);
	/*
	 * set OrientationListener
	 */
	//this->SetOrientation(ORIENTATION_AUTOMATIC);
	//this->AddOrientationEventListener(*this);

	return r;
}

result SelectStationForm::OnTerminating(void) {
	result r = E_SUCCESS;

	return r;
}

/*
void SelectStationForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId){

}

void SelectStationForm::OnOrientationChanged(const Control& source, OrientationStatus orientationStatus){

}
*/
/*
 * ITextValueChangedListener
 */

void  SelectStationForm::OnTextValueChangeCanceled (const Osp::Ui::Control &source){
	AppLog("text value canceled");
}
void  SelectStationForm::OnTextValueChanged (const Osp::Ui::Control &source){
	AppLog("text value changed");
}

void
SelectStationForm::OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status)
{
}

void
SelectStationForm::OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction)
{
}

void
SelectStationForm::OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus state)
{
}

int
SelectStationForm::GetItemCount(void)
{
	return stations->GetCount();
}

Osp::Ui::Controls::ListItemBase*
SelectStationForm::CreateItem(int index, int itemWidth)
{
	SimpleItem* item = new SimpleItem();
    item->Construct(Osp::Graphics::Dimension(itemWidth,60), LIST_ANNEX_STYLE_NORMAL);
    Station* station;
    stations->GetAt(index,station);
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

