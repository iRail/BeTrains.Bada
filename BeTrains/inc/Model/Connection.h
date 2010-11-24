/*
 * Connection.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <FBase.h>
#include "ConnectionNode.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

class Connection {
private:
	TimeSpan *timeBetween; //ownership
	String vehicleName;
	String vehicleType;
	ConnectionNode *startNode; //ownership
	ConnectionNode *endNode; //ownership
public:
	Connection()
		:timeBetween(new TimeSpan(0,0,0)),startNode(null),endNode(null){
	}
	virtual ~Connection();

	void setTimeBetween(int seconds);
	TimeSpan * getTimeBetween()const;
	void setVehicleName(String &name);
	//returns String copy of vehicle name
	String getVehicleName()const;
	void setVehicleType(String &type);
	//returns String copy of vehicle type
	String getVehicleType()const;
	void setStartNode(ConnectionNode * node);
	ConnectionNode * getStartNode()const;
	void setEndNode(ConnectionNode * node);
	ConnectionNode * getEndNode()const;

	bool operator==(const Connection &c2)const;
	Connection& operator=(const Connection &c2);
	bool operator!=(const Connection &c2)const;

};

#endif /* CONNECTION_H_ */
