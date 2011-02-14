/*
 * TripListForm2.cpp
 *
 *  Created on: 12-feb-2011
 *  Author: Bart Bruynooghe
 */

#include "View/TripListForm2.h"
#include "View/BeTrains.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

TripListForm2::TripListForm2() {
	expandableList = null;
	request = null;
	format = null;
}

TripListForm2::~TripListForm2() {
	delete format;
}

bool TripListForm2::Initialize(){
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_INDICATOR|FORM_STYLE_SOFTKEY_1);

	//CREATE EXPANDABLE LIST
	expandableList = new ExpandableList();
	expandableList->Construct(Rectangle(0, 0, 240, 400-20),CUSTOM_LIST_STYLE_NORMAL ,true);
	expandableList->SetTextOfEmptyList(L"Searching...");
	expandableList->AddExpandableItemEventListener(*this);
	AddControl(*expandableList);

	//SOFTKEY Back
	SetSoftkeyActionId(SOFTKEY_1, ACTION_BACK);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	this->SetSoftkeyText(SOFTKEY_1,L"Back");

	//CREATE FORMAT
	format = new CustomListItemFormat();
	format->Construct();
	//STATION NAMES ELEMENT
	format->AddElement(LIST_ITEM_STATIONS, Rectangle(3,3,177,16),16, Color::COLOR_BLACK, Color::COLOR_WHITE);
	//TIMES ELEMENT
	format->AddElement(LIST_ITEM_TIMES,Rectangle(3,19,180,20),20,Color::COLOR_BLUE,Color::COLOR_WHITE);
	//DELAY ELEMENT
	//format->AddElement(LIST_ITEM_DELAYS,Rectangle(0,36,180,15),15,Color::COLOR_RED,Color::COLOR_RED);
	//DURATION
	format->AddElement(LIST_ITEM_DURATION,Rectangle(180,3,50,15),15,Color::COLOR_BLACK,Color::COLOR_WHITE);
	//Number of trains
	format->AddElement(LIST_ITEM_NUMBER_CONNECTIONS,Rectangle(180,18,50,15),15,Color::COLOR_BLACK,Color::COLOR_WHITE);

	//CREATE SUBLISTFORMAT
	subListFormat = new CustomListItemFormat();
	subListFormat->Construct();
	//subListFormat->AddElement(1,Rectangle(3,3,190,16),16,Color::COLOR_BLACK,Color::COLOR_WHITE);
	subListFormat->AddElement(SUBLIST_FROM_TIME,Rectangle(3,3,40,16),16,Color::COLOR_BLUE,Color::COLOR_WHITE);
	subListFormat->AddElement(SUBLIST_FROM_STATION,Rectangle(43,3,120,16),16,Color::COLOR_BLACK,Color::COLOR_WHITE);
	subListFormat->AddElement(SUBLIST_FROM_PLATFORM,Rectangle(163,3,40,16),16,Color::COLOR_BLACK,Color::COLOR_WHITE);
	subListFormat->AddElement(SUBLIST_TO_TIME,Rectangle(3,19,40,16),16,Color::COLOR_BLUE,Color::COLOR_WHITE);
	subListFormat->AddElement(SUBLIST_TO_STATION,Rectangle(43,19,120,16),16,Color::COLOR_BLACK,Color::COLOR_WHITE);
	subListFormat->AddElement(SUBLIST_TO_PLATFORM,Rectangle(163,19,40,16),16,Color::COLOR_BLACK,Color::COLOR_WHITE);
	return true;
}

void TripListForm2::update(Request *request){
	this->request = request;
	if(expandableList != null) expandableList->RemoveAllItems();
	if(request != null){
		for(int i=0;i<request->getResults()->GetCount();i++){
			Trip* trip;
			request->getResults()->GetAt(i,trip);
			addTrip(trip);
		}
	}
}

void TripListForm2::addTrip(Trip* trip)
{
	//GETTING THE DATA FROM THE TRIP
	Connection* firstConn;
	Connection* lastConn;
	ArrayListT<Connection*>* connections = trip->getConnections();
	connections->GetAt(0,firstConn);
	connections->GetAt(connections->GetCount()-1,lastConn);
	//Station names
	String stations;
	stations += *firstConn->getStartNode()->getStation()->getName();
	stations += L" - ";
	stations += *lastConn->getEndNode()->getStation()->getName();
	//Times
	String times=formatTime(firstConn->getStartNode()->getDateTime());
	times += L" - " + formatTime(lastConn->getEndNode()->getDateTime());
	//DELAY
	//TODO delay
	//DURATION
	String duration= formatTime(trip->getDuration());
	//number of trains
	String numberOfTrains;
	if(trip->getConnections()->GetCount() == 0) numberOfTrains= L"direct";
	else numberOfTrains = L"#" + Integer::ToString(trip->getConnections()->GetCount());

	//CREATING ELEMENT
	CustomListItem * newItem = new CustomListItem();
	newItem->Construct(3+16+20+3);
	newItem->SetItemFormat(*format);
	newItem->SetElement(LIST_ITEM_STATIONS, stations);
	newItem->SetElement(LIST_ITEM_TIMES, times);
	//newItem->SetElement(LIST_ITEM_DELAYS, delay);
	newItem->SetElement(LIST_ITEM_DURATION, duration);
	newItem->SetElement(LIST_ITEM_NUMBER_CONNECTIONS, numberOfTrains);

	int itemNumber = expandableList->GetItemCount();
	expandableList->AddItem(*newItem,itemNumber);

	for(int i=0;i<trip->getConnections()->GetCount();i++){
		Connection* conn = null;
		trip->getConnections()->GetAt(i,conn);

		String fromTime = formatTime(conn->getStartNode()->getDateTime());
		String toTime = formatTime(conn->getEndNode()->getDateTime());
		String fromStation = String(*conn->getStartNode()->getStation()->getName());
		String toStation = String(*conn->getEndNode()->getStation()->getName());
		String fromPlatform = String(*conn->getStartNode()->getPlatform());
		String toPlatform = String(*conn->getEndNode()->getPlatform());

		//SUBLIST_FROM_TIME,SUBLIST_TO_TIME,SUBLIST_FROM_STATION,SUBLIST_TO_STATION,SUBLIST_FROM_PLATFORM,SUBLIST_TO_PLATFORM
		CustomListItem* subItem = new CustomListItem();
		subItem->Construct(3+19+19+3);
		subItem->SetItemFormat(*subListFormat);
		subItem->SetElement(SUBLIST_FROM_TIME,fromTime);
		subItem->SetElement(SUBLIST_FROM_STATION,fromStation);
		subItem->SetElement(SUBLIST_FROM_PLATFORM,fromPlatform);
		subItem->SetElement(SUBLIST_TO_TIME,toTime);
		subItem->SetElement(SUBLIST_TO_STATION,toStation);
		subItem->SetElement(SUBLIST_TO_PLATFORM,toPlatform);
		expandableList->AddSubItem(itemNumber,*subItem,i);
	}
}

void TripListForm2::OnItemStateChanged(const Osp::Ui::Control &source, int mainIndex, int subIndex, int itemId, int elementId, Osp::Ui::ItemStatus status){}
void TripListForm2::OnItemStateChanged(const Osp::Ui::Control &source, int mainIndex, int subIndex, int itemId, Osp::Ui::ItemStatus status){

}


result TripListForm2::OnInitializing(void){
	return E_SUCCESS;
}

result TripListForm2::OnTerminating(void){
	return E_SUCCESS;
}

void TripListForm2::OnActionPerformed(const Osp::Ui::Control &source, int actionId){
	BeTrains* app = (BeTrains*)BeTrains::GetInstance();
	switch ( actionId ) {
		case ACTION_BACK:
			app->showRoutePlanner();
	}
}

String TripListForm2::formatTime(DateTime *dateTime){
	int hour = dateTime->GetHour();
	int min = dateTime->GetMinute();
	String time;
	if(hour<10) time += L"0";
	time += Integer::ToString(hour)+ L":";
	if(min < 10) time += L"0";
	time += Integer::ToString(min);
	return time;
}

String TripListForm2::formatDelay(TimeSpan* delay){
	int hour = delay->GetHours();
	int min = delay->GetMinutes();
	String time = Integer::ToString(hour)+ L":";
	if(min < 10) time += L"0";
	time += Integer::ToString(min);
	return time;
}

String TripListForm2::formatTime(TimeSpan *timeSpan){
	int hour = timeSpan->GetHours();
	int min = timeSpan->GetMinutes();
	String time;
	if(hour<10) time += L"0";
	time += Integer::ToString(hour)+ L":";
	if(min < 10) time += L"0";
	time += Integer::ToString(min);
	return time;
}
