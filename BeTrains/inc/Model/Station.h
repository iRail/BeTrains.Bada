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
	double latitude;
	double longtitude;
	String *country;
	String *name;
public:
	Station(int latitude_,int longtitude_,String country_,String name_)
		:latitude(latitude_),longtitude(longtitude_),country(new String(country_)),name(new String(name_)){}
	Station(){}
	virtual ~Station();
	//returns a copy of latitude
	double getLatitude() const;
	//returns a copy of longtitude
	double getLongtitude() const;
	//returns a copy of country
	String getCountry() const;
	//returns a copy of name
	String getName() const;

	bool operator==(const Station &c2) const;

	Station & operator=(const Station &c2);

	bool operator!=(const Station &c2) const;
};

#endif /* STATION_H_ */
