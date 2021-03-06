/*
 * IRailAPI.cpp
 *
 *  Created on: 11-dec-2010
 *  Author: Bart Bruynooghe
 */

#include "model/IRailAPI.h"
#include <FLclTimeZone.h>
#include <FLocales.h>
#include "model/AppData.h"

using namespace Osp::Locales;

IRailAPI::IRailAPI() {
	//country = new String(L"BE"); //TODO this is not yet in the irail api
	//initialiseStations();
	//testRoutePlanner();
}

IRailAPI::~IRailAPI() {}
/*
 *	CREATES LIST FROM STATIONS from a char buffer (thas like a string)
 *	transfroms the char buffer to an xml document
 *	takes all the station info from the xml and transforms into homebrew infrastructure
 *	WORKED AND CHECKED
 */

ArrayListT<Station *> * IRailAPI::createStationsList(ByteBuffer* buf){
	ArrayListT<Station *> * stationList = new ArrayListT<Station*>();
	//TODO pointer to string country: nobody is owner yet thought:(it should be destructed when the stationList is destroyed) memoryleak
	stationList->Construct(570);
	xmlDocPtr doc =	xmlParseMemory((char*) (buf->GetPointer()), buf->GetLimit());
	if (doc != null) {
		xmlNodePtr station = null;
		xmlNodePtr stations = xmlDocGetRootElement(doc);
		for (station = stations->children; station; station=station->next){
			if(station->type == XML_ELEMENT_NODE){
				stationList->Add(createStation(station));
			}
		}
	}
	//AppLog("completed stationList");
	return stationList;
}

Station* IRailAPI::createStation(xmlNodePtr station){
	String stationName = getString(station->children->content);
	double latitude;
	double longitude;
	String stationId;
	xmlAttrPtr attr = null;
	for(attr = station->properties; attr; attr=attr->next){
		if (attr != null && attr->type== XML_ATTRIBUTE_NODE) {
			String attrName = getString(attr->name);
			String attrValue = getString(attr->children->content);
			if(attrName == "locationX"){
				if(attrValue == "") attrValue ="0.0";
				Double::Parse(attrValue,longitude);
			}else if(attrName == "locationY"){
				if(attrValue == "") attrValue ="0.0";
				Double::Parse(attrValue,latitude);
			}else if(attrName == "id"){
				stationId = getString(attr->children->content);
			}
		}
	}
	return new Station(latitude,longitude,stationName,stationId);
}

/*
 * Creates a list of trips: you give a xml buffer stream to it, with the requested info in
 *
 *
 */
ArrayListT<Trip *> * IRailAPI::createTripList(ByteBuffer* buf){
	//Carefull: we don't use the same naming as irail and that can be confusing:
	//every xml node is named as the irail
	//all the model elements are named as we use in bada
	ArrayListT<Trip *> * trips = new ArrayListT<Trip *>();
	trips->Construct(10);
	xmlDocPtr doc =	xmlParseMemory((char*) (buf->GetPointer()), buf->GetLimit());
	if (doc != null) {
		xmlNodePtr connection = null;
		xmlNodePtr root = xmlDocGetRootElement(doc);
		String nodeName = getString(root->name);
		if (nodeName == "connections"){
			for(connection=root->children; connection; connection=connection->next){
				//xml:connection = badamodel:Trip
				trips->Add(createTrip(connection));
			}
		}else{ //error
			AppLogDebug("error");
			delete trips;
			return null;
		}

	}
	return trips;
}

Trip * IRailAPI::createTrip(xmlNodePtr connection){
	Trip * trip = new Trip();
	Connection * conn = new Connection();
	trip->getConnections()->Add(conn);
	ConnectionNode * dep=null;
	ConnectionNode * arr=null;
	xmlNodePtr child = null;
	for (child = connection->children; child; child = child->next) {
		if (child->type == XML_ELEMENT_NODE) {
			String nodeName = getString(child->name);
			if (nodeName == "departure"){
				dep = createConnectionNode(child,conn);
				conn->setStartNode(dep);
			}else if(nodeName == "arrival"){
				arr = createConnectionNode(child,conn);
			}else if(nodeName == "duration"){
				int seconds = getInt(child->children->content);
				trip->setDuration(getTimeSpan(seconds));
			}else if(nodeName == "vias"){
				xmlNodePtr via=null;
				for (via = child->children; via; via = via->next) {
					if(via->type == XML_ELEMENT_NODE){
						createVia(via,trip->getConnections());
					}
				}
			}
		}
	}
	//add arr ConnectionNode to the last ConnectionNode of the list
	Connection* last;
	trip->getConnections()->GetAt(trip->getConnections()->GetCount()-1,last);
	last->setEndNode(arr);
	return trip;
}

void IRailAPI::createVia(xmlNodePtr via,ArrayListT<Connection*>* connections){
	Connection* last;
	//gets last connection from the arrayList
	connections->GetAt(connections->GetCount()-1,last);
	//new connection added
	Connection* conn = new Connection;
	connections->Add(conn);
	xmlNodePtr child = null;
	ConnectionNode *departure=null;
	ConnectionNode *arrival=null;
	Station* viaStation=null;
	for (child = via->children; child; child = child->next){
		if (child->type == XML_ELEMENT_NODE) {
			String nodeName = getString(child->name);
			//AppLog("%S",nodeName.GetPointer());
			if (nodeName == "arrival"){
				arrival = createConnectionNode(child,null);
				last->setEndNode(arrival);
			}else if(nodeName == "departure"){
				departure = createConnectionNode(child,null);
				conn->setStartNode(departure);
			}else if(nodeName == "station"){
				String stationId;
				for(xmlAttrPtr attr = child->properties; attr; attr=attr->next){
					if (attr != null && attr->type== XML_ATTRIBUTE_NODE) {
						String attrName = getString(attr->name);
						if(attrName == "id")
							stationId = getString(attr->children->content);
					}
				}
				viaStation = AppData::GetInstance()->getStationById(stationId);
				if(viaStation == null){
					viaStation = createStation(child);
					AppData::GetInstance()->getStationList()->Add(viaStation);
				}
			}else if(nodeName == "vehicle"){
				String ve = getString(child->children->content);
				ve.Replace(L".",L" ");
				Vehicle* vehicle = new Vehicle(ve);
				conn->setVehicle(vehicle);
			}else if(nodeName == "timeBetween"){
				//int timeBetween = getInt(child->children->content);
				//conn->setTimeBetween(getTimeSpan(timeBetween));
			}
		}
	}
	departure->setStation(viaStation);
	arrival->setStation(viaStation);
}

ConnectionNode * IRailAPI::createConnectionNode(xmlNodePtr xmlNode,Connection* conn){//connection should be passed so vehicle name can be inserted
	ConnectionNode * cn = new ConnectionNode();
	xmlNodePtr child=null;
	//get children
	for(child=xmlNode->children;child;child=child->next){
		String tagName = getString(child->name);
		if(tagName == "time"){
			cn->setDateTime(getTimeAttribute(child));
		}else if(tagName == "platform"){
			if(child->children){
				cn->setPlatform(getString(child->children->content));
			}else{
				cn->setPlatform(L"-");
			}
		}else if(tagName == "vehicle"){
			if(child->children){
				String ve = getString(child->children->content);
				ve.Replace(L".",L" ");
				Vehicle* vehicle = new Vehicle(ve);
				conn->setVehicle(vehicle);
				//conn->setVehicleName(getStringN(child->children->content));
			}
		}else if(tagName == "station"){
			String stationId;
			for(xmlAttrPtr attr = child->properties; attr; attr=attr->next){
				if (attr != null && attr->type== XML_ATTRIBUTE_NODE) {
					String attrName = getString(attr->name);
					if(attrName == "id")
						stationId = getString(attr->children->content);
				}
			}
			Station* st = AppData::GetInstance()->getStationById(stationId);
			if(st == null){
				st = createStation(child);
				AppData::GetInstance()->getStationList()->Add(st);
			}
			cn->setStation(st);
		}
	}
	//get attributes
	xmlAttrPtr attr = null;
	for(attr = xmlNode->properties; attr; attr=attr->next){
		if (attr != null && attr->type== XML_ATTRIBUTE_NODE) {
			String attrName = getString(attr->name);
			String attrValue = getString(attr->children->content);
			if(attrName == "delay"){
				int delay;
				Integer::Parse(attrValue,delay);
				if(delay > 1){
					TimeSpan del = getTimeSpan(delay);
					cn->setDelay(del);
				}
			}
		}
	}
	return cn;
}
/*
ArrayListT<Station *> * IRailAPI::getStations(){
	return stations;
}

Station * IRailAPI::getStation(String &stationName){
	Station *found = null;
	int i=0;
	while(!found && i<stations->GetCount()){
		Station* st;
		stations->GetAt(i,st);
		if(st->getName().Equals(stationName,false)){
			found = st;
		}
		i++;
	}
	return found;
}

Station * IRailAPI::getStationById(String &stationId){
	Station *found = null;
	int i=0;
	while(!found && i<stations->GetCount()){
		Station* st;
		stations->GetAt(i,st);
		if(st->getId().Equals(stationId,false)){
			found = st;
		}
		i++;
	}
	if(found == null){

		AppLog("Station not found id: %S",stationId.GetPointer());
	}
	return found;
}

void IRailAPI::initialiseStations(){
	result r = E_SUCCESS;
	String fileName(L"/Res/Files/nl.xml");
	File *file = new File();
	FileAttributes sourcefilemeta;
	File::GetAttributes(fileName, sourcefilemeta);
	int filesize = sourcefilemeta.GetFileSize();
	ByteBuffer buffer;
	buffer.Construct(filesize);
	//AppLog("Read buffer size %d", buffer.GetLimit());
	r = file->Construct(fileName, L"r"); //for write: w or w+

	switch (r) {
		case E_SUCCESS:
			AppLog("E_SUCCESS");
			break;
		case E_INVALID_STATE:
			AppLog("E_INVALID_STATE");
			break;
		case E_INVALID_ARG:
			AppLog("E_INVALID_ARG");
			break;
		case E_ILLEGAL_ACCESS:
			AppLog("E_ILLEGAL_ACCESS");
			break;
		case E_FILE_NOT_FOUND:
			AppLog("E_FILE_NOT_FOUND");
			break;
		case E_MAX_EXCEEDED:
			AppLog("E_MAX_EXCEEDED");
			break;
		case E_STORAGE_FULL:
			AppLog("E_STORAGE_FULL");
			break;
		case E_IO:
			AppLog("E_IO");
			break;
		default :
			AppLog("default");
	}

	r = file->Read(buffer); //to write: file->Write *beware of the permission w instead of r

	switch (r) {
		case E_SUCCESS:
			AppLog("E_SUCCESS");
			break;
		case E_INVALID_STATE:
			AppLog("E_INVALID_STATE");
			break;
		case E_INVALID_ARG:
			AppLog("E_INVALID_ARG");
			break;
		case E_ILLEGAL_ACCESS:
			AppLog("E_ILLEGAL_ACCESS");
			break;
		case E_END_OF_FILE:
			AppLog("E_END_OF_FILE");
			break;
		case E_IO:
			AppLog("E_IO");
			break;
		default:
			AppLog("default");
	}

	delete file; //closes the file, there is no default close method for files, its gets closed when its scope is closed
	buffer.SetPosition(0);
	stations = createStationsList(&buffer);
}
*/

ArrayListT<LiveBoardResult*> * IRailAPI::createLiveBoardList(ByteBuffer* buf){
	ArrayListT<LiveBoardResult*>* results=new ArrayListT<LiveBoardResult*>();
	results->Construct(10);

	xmlDocPtr doc =	xmlParseMemory((char*) (buf->GetPointer()), buf->GetLimit());
	if (doc != null) {
		xmlNodePtr child = null;
		xmlNodePtr departure =null;
		xmlNodePtr root = xmlDocGetRootElement(doc);
		String nodeName = getString(root->name);
		//AppLogDebug("nodename= %S",nodeName.GetPointer());
		if (nodeName == "liveboard"){
			//int x=0;
			for(child=root->children; child; child=child->next){
				String nodeNameChild = getString(child->name);
				//AppLogDebug("nodename= %S",nodeNameChild.GetPointer());
				if(nodeNameChild == "departures"){
					for(departure=child->children;departure;departure=departure->next){
						results->Add(createDeparture(departure));
						//x++;
					}
				}
			}
			//AppLogDebug("#departures = %S",Integer::ToString(x).GetPointer());
		}else{ //error
			AppLogDebug("error");
			delete results;
			return null;
		}

	}

	//AppLog("done parsing liveboard xml");
	return results;
}

LiveBoardResult* IRailAPI::createDeparture(xmlNodePtr departure){
	LiveBoardResult* result = new LiveBoardResult();
	xmlNodePtr child = null;
	for (child = departure->children; child; child = child->next) {
		if (child->type == XML_ELEMENT_NODE) {
			String nodeName = getString(child->name);
			//AppLogDebug("departure child: %S",nodeName.GetPointer());
			if (nodeName == "station"){
				String stationId;
				for(xmlAttrPtr attr = child->properties; attr; attr=attr->next){
					if (attr != null && attr->type== XML_ATTRIBUTE_NODE) {
						String attrName = getString(attr->name);
						//AppLogDebug("station attr: %S",attrName.GetPointer());
						if(attrName == "id"){
							stationId = getString(attr->children->content);
							//AppLogDebug("station id = %S",stationId.GetPointer());
						}
					}
				}
				Station* station = AppData::GetInstance()->getStationById(stationId);
				if(station == null){
					//AppLogDebug("no station found");
					station = createStation(child);
					AppData::GetInstance()->getStationList()->Add(station);
				}//else AppLogDebug("station found: %S",station->getNameN()->GetPointer());
				result->setStation(station);
			}else if(nodeName == "time"){
				result->setDateTime(getTimeAttribute(child));
				//AppLogDebug("datetime: %S",result->getDateTime().ToString().GetPointer());
			}else if(nodeName == "platform"){
				if(child->children)
					result->setPlatform(getString(child->children->content));
				else
					result->setPlatform(L"-");
				//AppLogDebug("platform %S", result->getPlatform().GetPointer());
			}
		}
	}
	xmlAttrPtr attr = null;
	for (attr = departure->properties; attr; attr = attr->next) {
		if (attr != null && attr->type == XML_ATTRIBUTE_NODE) {
			String attrName = getString(attr->name);
			if (attrName == "delay") {
				int delay = getInt(attr->children->content);
				//AppLogDebug("delay: %S",Integer::ToString(delay).GetPointer() );
				result->setDelay(getTimeSpan(delay));
			}
		}
	}
	return result;

}

ArrayListT<Trip *> * IRailAPI::testRoutePlanner(){
	result r = E_SUCCESS;
	String fileName(L"/Home/2.xml");
	File *file = new File();
	FileAttributes sourcefilemeta;
	File::GetAttributes(fileName, sourcefilemeta);
	int filesize = sourcefilemeta.GetFileSize();
	ByteBuffer buffer;
	buffer.Construct(filesize);
	//AppLog("Read buffer size %d", buffer.GetLimit());
	r = file->Construct(fileName, L"r"); //for write: w or w+
	r = file->Read(buffer); //to write: file->Write *beware of the permission w instead of r
	delete file; //closes the file, there is no default close method for files, its gets closed when its scope is closed
	buffer.SetPosition(0);
	ArrayListT<Trip *> * test = createTripList(&buffer);
	//AppLog("completed trips");
	return test;
}

int IRailAPI::getInt(xmlChar * xmlchar){
	int number;
	String s = getString(xmlchar);
	Integer::Parse(s, number);
	return number;
}

String IRailAPI::getString(const xmlChar *& xmlchar){
	String value;
	Osp::Base::Utility::StringUtil::Utf8ToString((char*) xmlchar, value);
	return value;
}

String IRailAPI::getString(xmlChar * xmlchar){
	String value;
	Osp::Base::Utility::StringUtil::Utf8ToString((char*) xmlchar, value);
	return value;
}

String* IRailAPI::getStringN(const xmlChar *& xmlchar){
	String val;
	Osp::Base::Utility::StringUtil::Utf8ToString((char*) xmlchar, val);
	String *value = new String(val);
	return value;
}

String* IRailAPI::getStringN(xmlChar * xmlchar){
	String val;
	Osp::Base::Utility::StringUtil::Utf8ToString((char*) xmlchar, val);
	String *value = new String(val);
	return value;
}

DateTime IRailAPI::getDateTime(String &isoTime){
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
	DateTime dt;
	dt.SetValue(year, month, day, hours, minutes);

	//NO NEED FOR Localisation here
	/*
	LocaleManager localeManager;
	localeManager.Construct();
	TimeZone t= localeManager.GetSystemTimeZone();
	int utcDifference = t.GetRawOffset();
	dt->AddMinutes(utcDifference);
	*/
	return dt;
}

TimeSpan IRailAPI::getTimeSpan(int seconds){
	return TimeSpan(seconds * 1000);
}

DateTime IRailAPI::getTimeAttribute(xmlNodePtr xmlNode){
	xmlAttrPtr attr = null;
	for(attr = xmlNode->properties; attr; attr=attr->next){
		if (attr != null && attr->type== XML_ATTRIBUTE_NODE) {
			String attrName = getString(attr->name);
			if(attrName == "formatted"){
				String value = getString(attr->children->content);
				return getDateTime(value);
			}
		}
	}
	return DateTime();
}
