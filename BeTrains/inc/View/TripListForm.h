
#ifndef _TRIPLISTFORM_H_
#define _TRIPLISTFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "Model/Trip.h"
#include "View/TextItem.h"
#include "Model/Request.h"

class TripListForm :
	public Osp::Ui::Controls::Form
{

// Construction
public:
	TripListForm();
	void update(Request *request);
	//TODO this needs an Request wich includes the trip arraylist so he can directly make a previous/next request
	virtual ~TripListForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
private:
	//datamembers
	Request* request; //no ownership, triplist is inside
	Osp::Ui::Controls::CustomList * tripList;

	//methods
	String formatTime(DateTime *dateTime);
	String formatTime(TimeSpan *timeSpan);
};

#endif
