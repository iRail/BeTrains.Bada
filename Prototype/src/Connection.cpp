/*
 * Connection.cpp
 *
 *  Created on: 16-nov-2010
 *      Author: B
 */

#include "Connection.h"

using namespace Osp::Base;

Connection::~Connection() {
	// TODO Auto-generated destructor stub
}

String Connection::getFromStation() const {
	return this->fromStation;
}

DateTime Connection::getFromTime() const {
	return this->fromTime;
}

String Connection::getToStation() const {
	return this->toStation;
}

DateTime Connection::getToTime() const {
	return this->toTime;
}

int Connection::getTrains() const {
	return this->trains;
}

TimeSpan Connection::getDuration() const {
	return this->duration;
}

void Connection::setFromStation(String fromStation) {
	this->fromStation = fromStation;
}

void Connection::setFromTime(String isoTime) {
	//TODO seconds
	String year_, month_, day_, hours_, minutes_, seconds_;
	int year, month, day, hours, minutes;
	//substrings
	isoTime.SubString(0, 4, year_);
	isoTime.SubString(5, 2, month_);
	isoTime.SubString(8, 2, day_);
	isoTime.SubString(11, 2, hours_);
	isoTime.SubString(14, 2, minutes_);
	//parsing
	Integer::Parse(year_, year);
	Integer::Parse(month_, month);
	Integer::Parse(day_, day);
	Integer::Parse(hours_, hours);
	Integer::Parse(minutes_, minutes);
	this->fromTime.SetValue(year, month, day, hours, minutes);
}

void Connection::setToStation(String toStation) {
	this->toStation = toStation;
}

void Connection::setToTime(String isoTime) {
	String year_, month_, day_, hours_, minutes_, seconds_;
	int year, month, day, hours, minutes;
	//substrings
	isoTime.SubString(0, 4, year_);
	isoTime.SubString(5, 2, month_);
	isoTime.SubString(8, 2, day_);
	isoTime.SubString(11, 2, hours_);
	isoTime.SubString(14, 2, minutes_);
	//parsing
	Integer::Parse(year_, year);
	Integer::Parse(month_, month);
	Integer::Parse(day_, day);
	Integer::Parse(hours_, hours);
	Integer::Parse(minutes_, minutes);
	this->toTime.SetValue(year, month, day, hours, minutes);
}

void Connection::setTrains(int trains) {
	this->trains = trains;
}

void Connection::setDuration(int seconds) {
	TimeSpan t(seconds * 1000);
	this->duration = t;
}
