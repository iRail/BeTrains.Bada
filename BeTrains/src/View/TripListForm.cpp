
#include "View/TripListForm.h"
#include "View/ItemFactory.h"
#include "View/Constants.h"
#include "View/TextItem.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;



TripListForm::TripListForm(ArrayListT<Trip *> * trips)
{
	this->trips = trips;
	AppLog("debugtest");
	//defaultFont->Construct(Osp::Graphics::FONT_STYLE_PLAIN,20);
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
		tripList->AddItem(*(pItemFactory->createItem(stations, times, duration,trip->getConnections()->GetCount())));
		//this->addItem(stations,times,duration,2);
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
void TripListForm::createFormat(const int listWidth){
	format.Construct();
	const int INDENT = 23;
	format.AddElement(Constants::LIST_STATIONS, Rectangle(0, 0, listWidth-INDENT, 25));
	format.AddElement(Constants::LIST_TRAINS, Rectangle(listWidth-INDENT, 0, INDENT-10, 25));
	format.AddElement(Constants::LIST_TIMES, Rectangle(0, 25, listWidth/2, 25));
	format.AddElement(Constants::LIST_DURATION, Rectangle(listWidth/2, 25, listWidth/2-10, 25));
}

void TripListForm::addItem(const String& stationNames, const String& times, const String& duration, int trains){
	CustomListItem item;
	item.Construct(50); //50= row height
	item.SetItemFormat(format);
	//item.SetElement(Constants::LIST_STATIONS,stationNames);
	//item.SetElement(Constants::LIST_TRAINS,stationNames);
	item.SetElement(Constants::LIST_STATIONS,createTextItem(stationNames, TextItem::LEFT ));
	item.SetElement(Constants::LIST_TRAINS,createTextItem(L"# " + Integer::ToString(trains),TextItem::RIGHT ));
	item.SetElement(Constants::LIST_TIMES,createTextItem( times, TextItem::LEFT));
	item.SetElement(Constants::LIST_DURATION,createTextItem(duration, TextItem::RIGHT));
	tripList->AddItem(item);
}

TextItem TripListForm::createTextItem(const String& text, const TextItem::Align alignment)
{
    return TextItem(text, defaultFont,alignment);
}
*/
