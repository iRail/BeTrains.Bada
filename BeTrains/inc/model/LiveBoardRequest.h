/*
 * LiveBoardRequest.h
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#ifndef LIVEBOARDREQUEST_H_
#define LIVEBOARDREQUEST_H_

#include <FBase.h>
#include "Model/Station.h"
#include "Model/LiveBoardResult.h"

class LiveBoardRequest {
public:
	LiveBoardRequest();
	virtual ~LiveBoardRequest();

	//METHODS
	void clearResults();

    void setStation(Station *station);
    void setTime(Osp::Base::DateTime time);

    Station*& getStation();
    Osp::Base::DateTime getTime() const;
    Osp::Base::Collection::ArrayListT<LiveBoardResult*>* getResults();

private:
    Osp::Base::DateTime _time;
    Station *_station;
    Osp::Base::Collection::ArrayListT<LiveBoardResult*> results; //ownership over all liveboardresults
};

#endif /* LIVEBOARDREQUEST_H_ */
