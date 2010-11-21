/*
 * Station.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#ifndef STATION_H_
#define STATION_H_

#include <FBase.h>
using namespace Osp::Base;
using namespace Osp::Base::Collection;

class Station {
private:
	int latitude;
	int longtitude;
	String country;
	String name;
public:
	Station(int latitude_,int longtitude_,String country_,String name_)
		:latitude(latitude_),longtitude(longtitude_),country(country_),name(name_){}
	Station(){}
	virtual ~Station();
	int getLatitude() const;
	int getLongtitude() const;
	String const &getCountry() const;
	String const &getName() const;

	bool operator==(const Station &c2) const {
		return false;
		//TODO operator overloading implementation
	}

	Station & operator=(const Station &c2) {
		//TODO operator overloading implementation
		return *this;
	}

	bool operator!=(const Station &c2) const {
		return true;
		//TODO operator overloading implementation
	}

};

#endif /* STATION_H_ */
