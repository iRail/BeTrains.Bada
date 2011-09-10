#include "model/AppData.h"

AppData* AppData::__pInstance = null;
bool AppData::__instanceFlag = false;

AppData::AppData():
	__pDtFormatter(null),
	_currentLiveBoardRequest(null)
{
	_stations.Construct(600);
}

AppData::~AppData()
{
	if (__pDtFormatter)
	{
		delete __pDtFormatter;
		__pDtFormatter = null;
	}
	Station* st;
	for(int i=0;i<_stations.GetCount();i++){
		_stations.GetAt(i,st);

		delete st;
	}
	if(_currentLiveBoardRequest){
		delete _currentLiveBoardRequest;
		_currentLiveBoardRequest = null;
	}

}

result
AppData::Construct(void)
{
	AppLogDebug("Called AppData::Construct");
	//create station List
	initialiseStations();
	Station* st;
	for(int i=0;i<_stations.GetCount();i++){
		_stations.GetAt(i,st);
		//AppLogDebug("%S",st->getName().GetPointer());
	}
	return E_SUCCESS;
}

AppData*
AppData::GetInstance(void)
{
	if(!__instanceFlag)
	{
		__pInstance = new AppData();
		__pInstance->Construct();
		__instanceFlag = true;
	}
	return __pInstance;
}

void
AppData::DistroyInstance(void)
{
	AppLogDebug("Called AppData::DestroyInstance");
	if(__pInstance != null)
	{
		AppLogDebug("Destroying instance of AppData");
		delete __pInstance;
		__pInstance = null;
	}
}

result AppData::initialiseStations(){
	result r = E_SUCCESS;
	String fileName(L"/Res/Files/nl.xml");
	File *file = new File();
	FileAttributes sourcefilemeta;
	File::GetAttributes(fileName, sourcefilemeta);
	int filesize = sourcefilemeta.GetFileSize();
	ByteBuffer buffer;
	buffer.Construct(filesize);
	r = file->Construct(fileName, L"r"); //for write: w or w+
	r = file->Read(buffer); //to write: file->Write *beware of the permission w instead of r
	delete file; //closes the file, there is no default close method for files, its gets closed when its scope is closed
	buffer.SetPosition(0);
	IRailAPI api;
	_stations.AddItems(*api.createStationsList(&buffer));
	return r;
}

Station* AppData::getStationById(const String& id){
	Station *found = null;
	int i=0;
	while(!found && i<_stations.GetCount()){
		Station* st;
		_stations.GetAt(i,st);
		if(st->getId().Equals(id,false)){
			found = st;
		}
		i++;
	}
	if(found == null){
		AppLog("Station not found id: %S",id.GetPointer());
	}
	return found;
}

ArrayListT<Station*>* AppData::getStationList(){
	return &_stations;
}

Request* AppData::getCurrentRequest(){
	return &_currentRequest;
}

void AppData::clearTripListFromCurrentRequest(){
	_currentRequest.clearTrips();
}

LiveBoardRequest* AppData::getCurrentLiveBoardRequest(){
	if(!_currentLiveBoardRequest)
		_currentLiveBoardRequest = new LiveBoardRequest();
	return _currentLiveBoardRequest;
}

void AppData::clearLiveBoardResults(){
	_currentLiveBoardRequest->clearResults();
}
