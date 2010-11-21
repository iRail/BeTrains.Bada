/*
 * Trip.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/Trip.h"


Trip::~Trip() {
}

TimeSpan Trip::getDuration(){
	return duration;
}

void Trip::setDuration(int seconds){}

void Trip::addConnection(Connection &conn){
	//TODO
}
