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
	float latitude;
	float longtitude;
	String * country; //ownership
	String * name; //no ownership: because there are +- 600 stations for 1 country
	String * id;//ownership
public:
	Station(int latitude_,int longtitude_,String* country_,String* name_,String* id_)
		:latitude(latitude_),longtitude(longtitude_),country(country_),name(name_),id(id_){}
	Station():country(null),name(null){}
	virtual ~Station();
	//returns a copy of latitude
	float getLatitude() const;
	//returns a copy of longtitude
	float getLongtitude() const;
	const String * const getCountry() const;
	const String * const getName() const;
	const String * const getID() const;

	bool operator==(const Station &c2) const;

	Station & operator=(const Station &c2);

	bool operator!=(const Station &c2) const;
};

#endif /* STATION_H_ */
