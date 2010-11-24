#ifndef _SEARCH_STATION_NAME_H_
#define _SEARCH_STATION_NAME_H_

#include <FBase.h>
#include <FUi.h>
#include <FBaseString.h>

using namespace Osp::Base;

class Search_Station_Name: public Osp::Ui::Controls::Form {

	// Construction
public:
	Search_Station_Name(void);
	virtual ~Search_Station_Name(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

	// Implementation
protected:
	// TODO count all the stations with perl script
	String listOfStations[];
	// Generated call-back functions
public:

};


#endif
