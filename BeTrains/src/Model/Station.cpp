/*
 * Station.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/Station.h"

Station::~Station() {
	delete name;
}

float Station::getLatitude() const {
	return latitude;
}
float Station::getLongtitude() const {
	return longtitude;
}

const String * const Station::getName() const {
	return name;
}

const String * const Station::getCountry() const{
	return country;
}

bool Station::operator==(const Station &c2) const {
	return this == &c2;
	/* all stations are made in the init of the application, there are no doubles so pointers can be compared
	return country->Equals(c2.getCountry()) &&
			name->Equals(c2.getName()) &&
			latitude == c2.getLatitude() &&
			longtitude == c2.getLongtitude();
			*/
}

Station & Station::operator=(const Station &c2) {
	latitude = c2.getLatitude();
	longtitude = c2.getLongtitude();
	country = new String(*c2.getCountry());
	name = new String(*c2.getName());
	return *this;
}

bool Station::operator!=(const Station &c2) const {
	return !((*this) == c2);
}
