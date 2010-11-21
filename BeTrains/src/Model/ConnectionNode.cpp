/*
 * ConnectionNode.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/ConnectionNode.h"

ConnectionNode::~ConnectionNode() {
}

void ConnectionNode::setStation(Station const &station){
	this->station = station;
}
Station ConnectionNode::getStation() const{
	return station;
}

void ConnectionNode::setPlatform(int platform){

}
int ConnectionNode::getPlatform(){
	return platform;
}

void ConnectionNode::setDelay(int seconds){

}
TimeSpan ConnectionNode::getDelay(){
	return delay;
}

void ConnectionNode::setDateTime(int seconds){

}
DateTime ConnectionNode::getDateTime(){
	return dateTime;
}
