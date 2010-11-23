/*
 * Station.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/Station.h"

Station::~Station() {
}

double Station::getLatitude() const {
	return latitude;
}
double Station::getLongtitude() const {
	return longtitude;
}
String Station::getCountry() const {
	return String(*country);
}
String Station::getName() const {
	return String(*name);
}

bool Station::operator==(const Station &c2) const {
	return country->Equals(c2.getCountry()) &&
			name->Equals(c2.getName()) &&
			latitude == c2.getLatitude() &&
			longtitude == c2.getLongtitude();
}

Station & Station::operator=(const Station &c2) {
	latitude = c2.getLatitude();
	longtitude = c2.getLongtitude();
	country = new String(c2.getCountry());
	name = new String(c2.getName());
	return *this;
}

bool Station::operator!=(const Station &c2) const {
	return !((*this) == c2);
}
