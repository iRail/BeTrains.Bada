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
	TimeSpan timeBetween;
	String vehicleName;
	String vehicleType;
	ConnectionNode startNode;
	ConnectionNode endNode;
public:
	Connection()
		:timeBetween(TimeSpan(0,0,0)){
	}
	virtual ~Connection();

	void setTimeBetween(int seconds);
	TimeSpan const & getTimeBetween();
	void setVehicleName(String name);
	String const & getVehicleName();
	void setVehicleType(String type);
	String const & getVehicleType();
	void setStartNode(ConnectionNode const &node);
	ConnectionNode &getStartNode();
	void setEndNode(ConnectionNode const &node);
	ConnectionNode &getEndNode();

	//bool operator==(const Connection &c2)const;
	//Connection& operator=(const Connection &c2);
	//bool operator!=(const Connection &c2)const;

	bool operator==(const Connection &c2)const{
		return false;
		//TODO operator overloading implementation
	}

	Connection & operator=(const Connection &c2){
		//TODO operator overloading implementation
		/*
		timeBetween = c2.getTimeBetween();
		vehicleName = c2.getVehicleName();
		vehicleType = c2.getVehicleType();
		startNode = c2.getStartNode();
		endNode = c2.getEndNode();
		*/
		return *this;
	}

	bool operator!=(const Connection &c2)const{
		return true;
		//TODO operator overloading implementation
	}
};

#endif /* CONNECTION_H_ */
