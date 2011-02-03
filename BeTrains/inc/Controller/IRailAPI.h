/*
 * IRailAPI.h
 *
 *  Created on: 11-dec-2010
 *      Author: B
 */

#ifndef IRAILAPI_H_
#define IRAILAPI_H_
#include <FXml.h>
#include <FIo.h>
#include"Model/Station.h"
#include"Model/Trip.h"
#include"Model/Connection.h"
#include"Model/ConnectionNode.h"

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
	ArrayListT<Station *> * getStations();
	//getStation returns null if station is not found
	Station * getStation(String &stationName); //TODO perhaps this method should be private
private:
	int getInt(xmlChar * xmlchar); //returns integer from an xmlchar
	String getString(const xmlChar *& xmlchar); //returns an string from an xml Node content
	String getString(xmlChar * xmlchar);
	String* getStringN(const xmlChar *& xmlchar); //returns an string from an xml Node content
	String* getStringN(xmlChar * xmlchar);
	DateTime* getDateTime(String &s);
	TimeSpan* getTimeSpan(int seconds);
	Trip * createTrip(xmlNodePtr connection);
	ConnectionNode * createConnectionNode(xmlNodePtr xmlNode,Connection* conn);
	DateTime* getTimeAttribute(xmlNodePtr xmlNode);
	void createVia(xmlNodePtr via,ArrayListT<Connection*>* connections);
	void initialiseStations();
protected:
	ArrayListT<Station *> *stations;
	void testRoutePlanner();

};

#endif /* IRAILAPI_H_ */
