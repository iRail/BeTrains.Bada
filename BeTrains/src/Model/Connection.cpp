/*
 * Connection.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/Connection.h"

Connection::~Connection() {
}

void Connection::setTimeBetween(int seconds) {

}

TimeSpan const & Connection::getTimeBetween() {
	return timeBetween;
}

void Connection::setVehicleName(String name) {

}
String const & Connection::getVehicleName() {
	return vehicleName;
}
void Connection::setVehicleType(String type) {

}
String const & Connection::getVehicleType() {
	return vehicleType;
}

void Connection::setStartNode(ConnectionNode const &node){
	startNode = node;
}
ConnectionNode &Connection::getStartNode(){
	return startNode;
}
void Connection::setEndNode(ConnectionNode const &node){
	endNode = node;
}
ConnectionNode &Connection::getEndNode(){
	return endNode;
}
/*
	TimeSpan timeBetween;
	String vehicleName;
	String vehicleType;
	ConnectionNode startNode;
	ConnectionNode endNode;
*/

