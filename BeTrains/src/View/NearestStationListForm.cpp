/*
 * NearestStationListForm.cpp
 *
 *  Created on: 16-feb-2011
 *      Author: B
 */
#include <FBase.h>
#include "View/NearestStationListForm.h"
#include "View/BeTrains.h"
#include "Model/Station.h"
#include "Model/DistanceAndStation.h"
#include "Model/DistanceSort.h"

using namespace Osp::Base::Utility;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Locations;


NearestStationListForm::NearestStationListForm() {
	nearestStationsList=null;
	format=null;
	try_times_gps_location = 10;
}

NearestStationListForm::~NearestStationListForm() {
	delete format;
}

bool NearestStationListForm::Initialize(){
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_INDICATOR|FORM_STYLE_SOFTKEY_0|FORM_STYLE_SOFTKEY_1);

	format = new CustomListItemFormat();
	format->Construct();
	format->AddElement(STATIONNAME, Rectangle(3,3,150,20),20, Color::COLOR_BLACK, Color::COLOR_WHITE);
	format->AddElement(DISTANCE, 	Rectangle(155,3,65,20),12, Color::COLOR_GREY, Color::COLOR_WHITE);

	nearestStationsList = new CustomList();
	nearestStationsList->Construct(Rectangle(0,0,240,400-20),CUSTOM_LIST_STYLE_NORMAL ,true);
	nearestStationsList->SetTextOfEmptyList(L"Waiting for GPS signal..");
	AddControl(*nearestStationsList);

	locProvider = new LocationProvider();
	locProvider->Construct(LOC_METHOD_GPS);

	SetSoftkeyActionId(SOFTKEY_1, BACK);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	this->SetSoftkeyText(SOFTKEY_1,L"Back");

	SetSoftkeyActionId(SOFTKEY_0, REFRESH);
	AddSoftkeyActionListener(SOFTKEY_0, *this);
	this->SetSoftkeyText(SOFTKEY_0,L"Refresh");

	return true;
}

void NearestStationListForm::update(){
	try_times_gps_location = 10;
	locProvider->RequestLocationUpdates(*this, 7, false);
	nearestStationsList->RemoveAllItems();
}

void NearestStationListForm::addDistanceAndStation(DistanceAndStation* das){
	CustomListItem* newItem = new CustomListItem();
	newItem->Construct(26);
	newItem->SetItemFormat(*format);
	newItem->SetElement(STATIONNAME,*das->getStation()->getName());
	newItem->SetElement(DISTANCE,Double::ToString(das->getDistance()));
	nearestStationsList->AddItem(*newItem);
}

void NearestStationListForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId){
	BeTrains* app = (BeTrains*)BeTrains::GetInstance();
	switch ( actionId ) {
		case BACK:
			app->showMainMenu();
		case REFRESH:
			update();
			RequestRedraw();
	}
}

void NearestStationListForm::OnLocationUpdated(Location& location)
{
    if(location.GetQualifiedCoordinates()!=null)
    {
        const QualifiedCoordinates *q = location.GetQualifiedCoordinates();
        double longitude = q->GetLongitude();
        double latitude = q->GetLatitude();
        DistanceSort<DistanceAndStation*> dist_sort;
        BeTrains* app = (BeTrains*)BeTrains::GetInstance();
        ArrayListT<Station*>* stations = app->getStationList();
        ArrayListT<DistanceAndStation*> distanceList; //TODO ownership over all das'es
        distanceList.Construct(stations->GetCount());
        distanceList.Sort(dist_sort);

        for(int i=0;i<stations->GetCount();i++){
        	Station* st;
        	stations->GetAt(i,st);
        	DistanceAndStation* das = new DistanceAndStation(st,longitude,latitude);
        	distanceList.Add(das);
        	addDistanceAndStation(das);
        }
        nearestStationsList->RequestRedraw();
        locProvider->CancelLocationUpdates();
    }else{
    	try_times_gps_location--;
    	if(try_times_gps_location<0){
    		locProvider->CancelLocationUpdates(); //cancels more new locations.
    		nearestStationsList->SetTextOfEmptyList(L"Waiting for GPS signal..");
    		try_times_gps_location=10;
    	}
    	AppLog("did not found a connection");
    }
}

void NearestStationListForm::OnProviderStateChanged(LocProviderState newState){}

result NearestStationListForm::OnInitializing(void){
	return E_SUCCESS;
}

result NearestStationListForm::OnTerminating(void){
	return E_SUCCESS;
}
