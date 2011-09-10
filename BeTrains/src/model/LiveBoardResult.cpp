/*
 * LiveBoardResult.cpp
 *
 *  Created on: 24-apr-2011
 *  Author: Bart Bruynooghe
 */

#include "Model/LiveBoardResult.h"

using namespace Osp::Base;

LiveBoardResult::LiveBoardResult():
	_delay(TimeSpan(0)),
	_vehicle(null),
	_station(null)
{}

LiveBoardResult::~LiveBoardResult() {
	if(_vehicle)
		delete _vehicle;
}


void LiveBoardResult::setDateTime(DateTime dateTime){
	_dateTime = dateTime;
}

void LiveBoardResult::setDelay(TimeSpan delay){
	_delay = delay;
}

void LiveBoardResult::setPlatform(String platform){
	_platform = platform;
}

void LiveBoardResult::setVehicle(Vehicle* vehicle){
	if(_vehicle)
		delete _vehicle;
	_vehicle = vehicle;
}

void LiveBoardResult::setStation(Station* station){
	_station = station;
}

DateTime LiveBoardResult::getDateTime() const{
	return _dateTime;
}

TimeSpan LiveBoardResult::getDelay() const{
	return _delay;
}

String LiveBoardResult::getPlatform() const{
	return _platform;
}

Vehicle* LiveBoardResult::getVehicle() const{
	return _vehicle;
}

Station* LiveBoardResult::getStation() const{
	return _station;
}
