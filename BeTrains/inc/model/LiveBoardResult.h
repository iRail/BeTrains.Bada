/*
 * LiveBoardResult.h
 *
 *  Created on: 24-apr-2011
 *  Author: Bart Bruynooghe
 */

#ifndef LIVEBOARDRESULT_H_
#define LIVEBOARDRESULT_H_

#include <FBase.h>
#include "Model/Vehicle.h"
#include "Model/Station.h"

class LiveBoardResult {
public:
	LiveBoardResult();
	virtual ~LiveBoardResult();

	//setters
	void setDateTime(Osp::Base::DateTime dateTime);
	void setDelay(Osp::Base::TimeSpan delay);
	void setPlatform(Osp::Base::String platform);
	void setVehicle(Vehicle* vehicle);
	void setStation(Station* station);

	//getters
	Osp::Base::DateTime getDateTime() const;
	Osp::Base::TimeSpan getDelay() const;
	Osp::Base::String getPlatform() const;
	Vehicle* getVehicle() const;
	Station* getStation() const;

private:
	Osp::Base::DateTime 	_dateTime;
	Osp::Base::TimeSpan 	_delay;
	Osp::Base::String 		_platform;
	Vehicle*				_vehicle; //ownership
	Station*				_station; //no ownership
};

#endif /* LIVEBOARDRESULT_H_ */
