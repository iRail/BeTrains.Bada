
#include "View/DetailsListForm.h"
#include "View/BeTrains.h"
#include "View/TextItem.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

DetailsListForm::DetailsListForm(void)
{
}

DetailsListForm::~DetailsListForm(void)
{
}

bool
DetailsListForm::Initialize()
{
	Form::Construct(L"DETAILS_LIST_FORM");
	connectionList = static_cast<CustomList*>(GetControl(L"DETAILS_TRIP_LIST", false));
	SetSoftkeyActionId(SOFTKEY_1, ACTION_BACK);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	//create format
	int listWidth = connectionList->GetWidth();
	format = new CustomListItemFormat();
	format->Construct();
	format->AddElement(LIST_NAME, Rectangle(0, 0, listWidth-40, 25));
	format->AddElement(LIST_IN_OUT, Rectangle(listWidth-40, 0, 40, 25));
	format->AddElement(LIST_PLATFORM, Rectangle(listWidth/2,25, listWidth/2 , 25));
	format->AddElement(LIST_TIME, Rectangle(0, 25,listWidth/2, 25));
	defaultFont = new Font();
	defaultFont->Construct(Osp::Graphics::FONT_STYLE_PLAIN,20);
	return true;
}

void DetailsListForm::update(Trip *trip){
	this->trip = trip;
	if(connectionList != null) connectionList->RemoveAllItems();
	if(trip != null){
		for(int i=0;i<trip->getConnections()->GetCount();i++){
			Connection* conn;
			trip->getConnections()->GetAt(i,conn);
			createItem(conn->getStartNode(),true);
			createItem(conn->getEndNode(),false);
		}
	}
}

void DetailsListForm::createItem(ConnectionNode* node,bool in){
	CustomListItem* item = new CustomListItem();
	item->Construct(50);
	item->SetItemFormat(*format);

	const String* const stationName = node->getStation()->getName();
	String time = formatTime(node->getDateTime());
	String platform = L"Platform: "+ *node->getPlatform();
	String inout;
	if(in) inout = L"in";
	else   inout = L"out";
	item->SetElement(LIST_NAME,	*(new TextItem(*stationName,defaultFont, TextItem::LEFT )));
	item->SetElement(LIST_IN_OUT,	*(new TextItem(inout,defaultFont, TextItem::RIGHT )));
	item->SetElement(LIST_TIME,	*(new TextItem(time,defaultFont, TextItem::LEFT )));
	item->SetElement(LIST_PLATFORM,	*(new TextItem(platform,defaultFont, TextItem::RIGHT )));
	connectionList->AddItem(*item);
}

result
DetailsListForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result
DetailsListForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void DetailsListForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId){
	BeTrains* app = (BeTrains*)BeTrains::GetInstance();
	switch ( actionId ) {
		case ACTION_BACK:
			app->showTripList();
	}
}

String DetailsListForm::formatTime(DateTime *dateTime){
	int hour = dateTime->GetHour();
	int min = dateTime->GetMinute();
	String time = Integer::ToString(hour)+ L":";
	if(min < 10)
		time += L"0";
	time += Integer::ToString(min);
	return time;
}
