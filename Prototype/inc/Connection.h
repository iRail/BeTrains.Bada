/*
 * Connection.h
 *
 *  Created on: 16-nov-2010
 *      Author: B
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <FBase.h>

using namespace Osp::Base;

class Connection {
private:
	String fromStation;
	String toStation;
	DateTime fromTime;
	DateTime toTime;
	int trains;
	TimeSpan duration;
public:
	Connection():duration(TimeSpan(0,0,0)),trains(1){
	}

	virtual ~Connection();

	String getFromStation() const;

	DateTime getFromTime() const;

	String getToStation() const;

	DateTime getToTime() const;

	int getTrains() const;

	TimeSpan getDuration() const;

	void setFromStation(String fromStation);

	void setFromTime(String isoTime);

	void setToStation(String toStation);

	void setToTime(String isoTime);

	void setTrains(int trains);

	void setDuration(int seconds);

	bool operator==(const Connection &c2)const {
			return  fromStation == c2.getFromStation() &&
					toStation == c2.getToStation() &&
					duration == c2.getDuration() &&
					fromTime == c2.getFromTime() &&
					toTime == c2.getToTime();
		}

	Connection& operator=(const Connection &c2) {
		fromStation = c2.getFromStation();
		toStation = c2.getToStation();
		duration = c2.getDuration();
		fromTime = c2.getFromTime();
		toTime = c2.getToTime();
		trains = c2.getTrains();
		return *this;
	}

	bool operator!=(const Connection &c2)const {
		return !(fromStation == c2.getFromStation() &&
				toStation == c2.getToStation() &&
				duration == c2.getDuration() &&
				fromTime == c2.getFromTime() &&
				toTime == c2.getToTime());
	}

	bool operator!=(const Object)const{
		return true;
	}

	bool operator!=(const int)const{
		return true;
	}
};

#endif /* CONNECTION_H_ */
