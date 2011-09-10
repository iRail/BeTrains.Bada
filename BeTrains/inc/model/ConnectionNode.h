/*
 * ConnectionNode.h
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#ifndef CONNECTIONNODE_H_
#define CONNECTIONNODE_H_

#include <FBase.h>
#include "Model/Station.h"

class ConnectionNode {
public:
	ConnectionNode();
	virtual ~ConnectionNode();

	//setters
	void setDateTime(Osp::Base::DateTime dateTime);
	void setDelay(Osp::Base::TimeSpan delay);
	void setPlatform(Osp::Base::String platform);
	void setStation(Station* station);

	//getters
	Osp::Base::DateTime getDateTime() const;
	Osp::Base::TimeSpan getDelay() const;
	Osp::Base::String getPlatform() const;
	Station* getStation() const;

private:
	Osp::Base::DateTime _dateTime;
	Osp::Base::TimeSpan _delay;
	Osp::Base::String _platform;
	Station* _station; //no ownership
};

#endif /* CONNECTIONNODE_H_ */
