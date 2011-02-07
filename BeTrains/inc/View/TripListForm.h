
#ifndef _TRIPLISTFORM_H_
#define _TRIPLISTFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "Model/Trip.h"

class TripListForm :
	public Osp::Ui::Controls::Form
{

// Construction
public:
	TripListForm(Osp::Base::Collection::ArrayListT<Trip *> * trips);
	//TODO this needs an Request wich includes the trip arraylist so he can directly make a previous/next request
	virtual ~TripListForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
private:
	Osp::Base::Collection::ArrayListT<Trip *> * trips;
	Osp::Ui::Controls::CustomList * tripList;
	String formatTime(DateTime *dateTime);
	String formatTime(TimeSpan *timeSpan);
	/*
	CustomListItem* createItem(
				const String& stationNames, const String& times,
				const String& duration, int trains);
	CustomListItemFormat* createFormat(const int listWidth);
	*/
};

#endif
