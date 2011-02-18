/*
 * NearestStationListForm.h
 *
 *  Created on: 16-feb-2011
 *      Author: B
 */

#ifndef NEARESTSTATIONLISTFORM_H_
#define NEARESTSTATIONLISTFORM_H_

#include <FUi.h>
#include <FLocations.h>
#include "Model/Station.h"
#include "Model/DistanceAndStation.h"

class NearestStationListForm:
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Locations::ILocationListener
{
public:
	NearestStationListForm();
	virtual ~NearestStationListForm();
	void update();
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
private:
	int try_times_gps_location;
	enum ListItems{STATIONNAME,DISTANCE};
	enum Actions{BACK,REFRESH};
	Osp::Locations::LocationProvider* locProvider;
	void OnActionPerformed(const Osp::Ui::Control &source, int actionId);
	Osp::Base::Collection::ArrayListT<Station*> nearestStations;
	Osp::Ui::Controls::CustomList * nearestStationsList;
	Osp::Ui::Controls::CustomListItemFormat* format;
	void addDistanceAndStation(DistanceAndStation* das);
	void OnLocationUpdated(Osp::Locations::Location& location);
	void OnProviderStateChanged(Osp::Locations::LocProviderState newState);
};

#endif /* NEARESTSTATIONLISTFORM_H_ */
