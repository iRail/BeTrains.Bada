/*
 * IRailAPI.h
 *
 *  Created on: 11-dec-2010
 *  Author: Bart Bruynooghe
 */

#ifndef IRAILAPI_H_
#define IRAILAPI_H_
#include <FXml.h>
#include <FIo.h>
#include"Model/Station.h"
#include"Model/Trip.h"
#include"Model/Connection.h"
#include"Model/ConnectionNode.h"
#include "Model/LiveBoardResult.h"

using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Xml;
using namespace Osp::Io;
using namespace Osp::Base::Collection;

class IRailAPI {
public:
	IRailAPI();
	virtual ~IRailAPI();
	//creates a List with stations from an xml buffer(stream from site)
	ArrayListT<Station *> * createStationsList(ByteBuffer* buf);
	//creates a list with trips
	ArrayListT<Trip *> * createTripList(ByteBuffer* buf);
	//ArrayListT<Station *> * getStations();
	//getStation returns null if station is not found
	//Station * getStation(String &stationName);
	//Station * getStationById(String &stationId); //This is the best way to find stations because there can be name differences
	ArrayListT<Trip *> * testRoutePlanner();

	//all ownership is givin over, except of the stations
	ArrayListT<LiveBoardResult*> * createLiveBoardList(ByteBuffer* buf);
	LiveBoardResult* createDeparture(xmlNodePtr departure);
private:
	Station* createStation(xmlNodePtr station);
	Trip * createTrip(xmlNodePtr connection);
	ConnectionNode * createConnectionNode(xmlNodePtr xmlNode,Connection* conn);
	void createVia(xmlNodePtr via,ArrayListT<Connection*>* connections);

	int getInt(xmlChar * xmlchar); 					//returns integer from an xmlchar
	String getString(const xmlChar *& xmlchar); 	//returns an string from an xml Node content
	String getString(xmlChar * xmlchar);
	String* getStringN(const xmlChar *& xmlchar); 	//returns an string from an xml Node content
	String* getStringN(xmlChar * xmlchar);
	DateTime getDateTime(String &s);
	TimeSpan getTimeSpan(int seconds);
	DateTime getTimeAttribute(xmlNodePtr xmlNode);

	String * country;
protected:
	ArrayListT<Station *> *stations;
};

#endif /* IRAILAPI_H_ */
