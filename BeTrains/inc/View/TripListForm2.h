/*
 * TripListForm2.h
 *
 *  Created on: 12-feb-2011
 * 	Author: Bart Bruynooghe
 */

#ifndef TRIPLISTFORM2_H_
#define TRIPLISTFORM2_H_

#include <FUi.h>
#include "Model/Request.h"
#include "Model/Trip.h"

class TripListForm2:
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IExpandableItemEventListener
{
public:
	TripListForm2();
	virtual ~TripListForm2();
	void update(Request *request);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
private:
	//DATA MEMBERS
	const static int MORE = 999; //high number because it cant interact with other list items
	enum Constants{ACTION_BACK};
	enum LIST_ITEMS{LIST_ITEM_STATIONS,LIST_ITEM_TIMES,LIST_ITEM_DELAYS,LIST_ITEM_DURATION,LIST_ITEM_VEHICLE_TYPE,LIST_ITEM_VEHICLE_NAME,LIST_ITEM_NUMBER_CONNECTIONS};
	enum SUB_LIST_ITEMS{SUBLIST_FROM_TIME,SUBLIST_TO_TIME,SUBLIST_FROM_STATION,SUBLIST_TO_STATION,SUBLIST_FROM_PLATFORM,SUBLIST_TO_PLATFORM};
	Osp::Ui::Controls::ExpandableList* expandableList;
	Request* request; //no ownership, triplist is inside
	Osp::Ui::Controls::CustomListItemFormat* format; //ownership
	Osp::Ui::Controls::CustomListItemFormat* moreFormat; //ownership
	Osp::Ui::Controls::CustomListItemFormat* subListFormat; //ownership
	//METHODS
	void OnActionPerformed(const Osp::Ui::Control &source, int actionId);
	void OnItemStateChanged(const Osp::Ui::Control &source, int mainIndex, int subIndex, int itemId, int elementId, Osp::Ui::ItemStatus status);
	void OnItemStateChanged(const Osp::Ui::Control &source, int mainIndex, int subIndex, int itemId, Osp::Ui::ItemStatus status);


	void addTrip(Trip* trip);
	String formatTime(Osp::Base::DateTime *dateTime);
	String formatDelay(Osp::Base::TimeSpan* delay);
	String formatTime(Osp::Base::TimeSpan *timeSpan);
};

#endif /* TRIPLISTFORM2_H_ */
