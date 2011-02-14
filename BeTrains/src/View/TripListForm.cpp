
#include "View/TripListForm.h"
#include "View/ItemFactory.h"
#include "View/Constants.h"
#include "View/TextItem.h"
#include "View/BeTrains.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

TripListForm::TripListForm()
{
	request = null;
}

TripListForm::~TripListForm(void)
{
}

bool
TripListForm::Initialize()
{
	Form::Construct(L"TRIP_LIST_FORM");
	//this->createFormat(tripList->GetWidth());
	tripList = static_cast<CustomList*>(GetControl(L"TRIP_LIST", false));
	SetSoftkeyActionId(SOFTKEY_1, ACTION_BACK);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	tripList->AddCustomItemEventListener(*this);
	return true;
}

void TripListForm::update(Request *request){
	this->request = request;
	if(tripList != null) tripList->RemoveAllItems();
	if(request != null){
		ItemFactory* pItemFactory = new ItemFactory();
		pItemFactory->Initialise(tripList->GetWidth());
		for(int i=0;i<request->getResults()->GetCount();i++){
			Trip* trip;
			request->getResults()->GetAt(i,trip);
			/*
			 * we werken met connections, dus om start en einde van de trip te weten :  from van het eerste station, en to van het laatste station
			 * laatste kan natuurlijk == zijn eerste connection
			 */
			Connection* firstConn;
			Connection* secondConn;
			ArrayListT<Connection*>* connections = trip->getConnections();
			connections->GetAt(0,firstConn);
			connections->GetAt(connections->GetCount()-1,secondConn);
			String stations;

			stations += *firstConn->getStartNode()->getStation()->getName();
			stations += L" - ";
			stations += *secondConn->getEndNode()->getStation()->getName();
			String startTime = formatTime(firstConn->getStartNode()->getDateTime(),firstConn->getStartNode()->getDelay());
			String endTime = formatTime(secondConn->getEndNode()->getDateTime(),secondConn->getEndNode()->getDelay());
			String times = startTime + L" - " + endTime;

			String duration = formatTime(trip->getDuration());
			tripList->AddItem(*(pItemFactory->createItem(stations, times, duration,trip->getConnections()->GetCount())));
		}
	}
}

result
TripListForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	return r;
}

result
TripListForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

String TripListForm::formatTime(DateTime *dateTime,TimeSpan* delay){
	int hour = dateTime->GetHour();
	int min = dateTime->GetMinute();
	String time = Integer::ToString(hour)+ L":";
	if(min < 10)
		time += L"0";
	time += Integer::ToString(min);
	if(delay != null){
		time += " +";
		int minutes = delay->GetMinutes();
		if(minutes<10) time += "0";
		time += Integer::ToString(minutes) + "\"";
	}
	return time;
}

String TripListForm::formatTime(TimeSpan *timeSpan){
	int hour = timeSpan->GetHours();
	int min = timeSpan->GetMinutes();
	String time = Integer::ToString(hour)+ L":";
	if(min < 10)
		time += L"0";
	time += Integer::ToString(min);
	return time;
}

void TripListForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId){
	BeTrains* app = (BeTrains*)BeTrains::GetInstance();
	switch ( actionId ) {
		case ACTION_BACK:
			app->showRoutePlanner();
	}
}

void TripListForm::OnItemStateChanged (const Osp::Ui::Control &source, int index, int itemId, int elementId, Osp::Ui::ItemStatus status){}
void TripListForm::OnItemStateChanged (const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status){
	if(status == Osp::Ui::ITEM_SELECTED){
		Trip* selectedTrip; //pass back to app
		request->getResults()->GetAt(index,selectedTrip);
		BeTrains* app = (BeTrains*)BeTrains::GetInstance();
		app->showRouteDetails(selectedTrip);
	}
}

