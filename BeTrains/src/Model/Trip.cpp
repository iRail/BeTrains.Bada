/*
 * Trip.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/Trip.h"


Trip::~Trip() {
	delete duration;
	int size = connections.GetCount();
	for(int i=size-1;i>=0;i--){
		Connection* conn;
		connections.GetAt(i,conn);
		connections.RemoveAt(i);
		delete conn;
	}
}

TimeSpan * Trip::getDuration() const{
	return duration;
}

void Trip::setDuration(int seconds){
	if(duration != null){
		delete duration;
	}
	duration = new TimeSpan(seconds*1000);
	//TODO check if this method sets delay correctly
}

ArrayListT<Connection*> * Trip::getConnections(){
	return &connections;
}

bool Trip::operator==(const Trip &c2) const {
	return this == &c2; //checks if pointers are equal
	//return duration.Equals(c2.getDuration());
	//checks only duration wich is actualy very wrong
}

Trip & Trip::operator=(const Trip &c2) {
	duration = new TimeSpan(*c2.getDuration());
	//TODO copy constructor connections
	return *this;
}

bool Trip::operator!=(const Trip &c2) const {
	return !((*this) == c2);
}
