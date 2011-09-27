/*
 * LiveBoardRequest.h
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#ifndef LIVEBOARDREQUEST_H_
#define LIVEBOARDREQUEST_H_

#include <FBase.h>
#include <FApp.h>
#include "Model/Station.h"
#include "Model/LiveBoardResult.h"

class LiveBoardRequest {
public:
	LiveBoardRequest();
	virtual ~LiveBoardRequest();

	//METHODS
	void clearResults();
	void clearTime();
	void clear();
	bool validate();	//returns false if not correct

    void setStation(Station *station);
    void setDateTime(Osp::Base::DateTime time);

    Station*& getStation();
    Osp::Base::DateTime getTime() const;
    Osp::Base::DateTime* getDateTime() const;
    Osp::Base::Collection::ArrayListT<LiveBoardResult*>* getResults();
    Osp::Base::Collection::ArrayListT<Osp::Base::String>* getErrors();

private:
    Osp::Base::DateTime* 								_time;
    Station *											_station;
    Osp::Base::Collection::ArrayListT<LiveBoardResult*> results; //ownership over all liveboardresults
    Osp::Base::Collection::ArrayListT<Osp::Base::String> _errors;
};

#endif /* LIVEBOARDREQUEST_H_ */
