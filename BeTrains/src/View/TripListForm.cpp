
#include "View/TripListForm.h"
#include "View/ItemFactory.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;



TripListForm::TripListForm(ArrayListT<Trip *> * trips)
{
	this->trips = trips;
}

TripListForm::~TripListForm(void)
{
}

bool
TripListForm::Initialize()
{
	Form::Construct(L"TRIP_LIST_FORM");
	tripList = static_cast<CustomList*>(GetControl(L"TRIP_LIST", false));
	ItemFactory* pItemFactory = new ItemFactory();
	pItemFactory->Initialise(tripList->GetWidth());

	for(int i=0;i<trips->GetCount();i++){
		//AppLog("aantal trips : %d",test->GetCount());
		Trip* trip;
		trips->GetAt(i,trip);
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
		String startTime = formatTime(firstConn->getStartNode()->getDateTime());
		String endTime = formatTime(secondConn->getEndNode()->getDateTime());
		String times = startTime + L" - " + endTime;


		String duration = formatTime(trip->getDuration());
				//Integer::ToString(trip->getDuration()->GetHours()) + L":" + Integer::ToString(trip->getDuration()->GetMinutes());
		tripList->AddItem(*(pItemFactory->createItem(stations, times, duration,2)));
	}
	return true;
}

result
TripListForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result
TripListForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

String TripListForm::formatTime(DateTime *dateTime){
	int hour = dateTime->GetHour();
	int min = dateTime->GetMinute();
	String time = Integer::ToString(hour)+ L":";
	if(min < 10)
		time += L"0";
	time += Integer::ToString(min);
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

/*
CustomListItem* TripListForm::createItem(const String& stationNames, const String& times,const String& duration, int trains){
	return null;
}
CustomListItemFormat* TripListForm::createFormat(const int listWidth){
	return null;
}
*/

