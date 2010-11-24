/*
 * Connection.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/Connection.h"

Connection::~Connection() {
	if(timeBetween) delete timeBetween;
	if(startNode) delete startNode;
	if(endNode) delete endNode;
}

void Connection::setTimeBetween(int seconds) {

}

TimeSpan * Connection::getTimeBetween() const {
	return timeBetween;
}

void Connection::setVehicleName(String &name) {
	vehicleName = name;
}

String Connection::getVehicleName() const{
	return vehicleName;
}

void Connection::setVehicleType(String &type) {
	vehicleType = type;
}

String Connection::getVehicleType() const {
	return vehicleType;
}

void Connection::setStartNode(ConnectionNode * node){
	startNode = node;
}

ConnectionNode * Connection::getStartNode() const {
	return startNode;
}

void Connection::setEndNode(ConnectionNode * node){
	endNode = node;
}

ConnectionNode * Connection::getEndNode() const{
	return endNode;
}


bool Connection::operator==(const Connection &c2)const{
	return *endNode == *c2.getEndNode() &&
			*startNode == *c2.getStartNode();
}

Connection& Connection::operator=(const Connection &c2){
	timeBetween = new TimeSpan(*c2.getTimeBetween());
	vehicleType = c2.getVehicleType();
	vehicleName = c2.getVehicleName();
	startNode = c2.getStartNode();
	endNode = c2.getEndNode();
	return *this;
}

bool Connection::operator!=(const Connection &c2)const{
	return !((*this) == c2);
}

