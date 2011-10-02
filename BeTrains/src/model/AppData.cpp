#include "model/AppData.h"
using namespace Osp::Locales;

AppData* AppData::__pInstance = null;
bool AppData::__instanceFlag = false;

AppData::AppData():
	__pDtFormatter(null),
	_currentRequest(null),
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
	if(_currentRequest){
		delete _currentRequest;
		_currentRequest = null;
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
	String languageCode;
	r = SettingInfo::GetValue(L"Language", languageCode);
	String lang = "en"; //DEFAULT
	//AppLog("language: %S",languageCode.GetPointer());
	//dont know how to use this enumerator LANGUAG_XXX
	/*
	if(languageCode.Equals(LANGUAGE_NLD))
		lang = "nl";
	else if(languageCode.Equals(LANGUAGE_FRA))
		lang = "fr";
	else if(languageCode.Equals(LANGUAGE_DEU))
		lang = "fr";
	*/

	if(languageCode.Equals("NLD",false))
		lang = "nl";
	else if(languageCode.Equals("FRA",false))
		lang = "fr";
	else if(languageCode.Equals("DEU",false))
		lang = "fr";

	String fileName(L"/Res/Files/"+lang+".xml");
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
	/*
	if(found == null){
		AppLog("Station not found id: %S",id.GetPointer());
	}
	*/
	return found;
}

ArrayListT<Station*>* AppData::getStationList(){
	return &_stations;
}

Request* AppData::getCurrentRequest(){
	if(!_currentRequest)
		_currentRequest = new Request();
	return _currentRequest;
}

void AppData::clearTripListFromCurrentRequest(){
	_currentRequest->clearTrips();
}

void AppData::newRequest(){
	if(_currentRequest != null)
		delete _currentRequest;
	_currentRequest = new Request();
}


LiveBoardRequest* AppData::getCurrentLiveBoardRequest(){
	if(!_currentLiveBoardRequest)
		_currentLiveBoardRequest = new LiveBoardRequest();
	return _currentLiveBoardRequest;
}

void AppData::clearLiveBoardResults(){
	_currentLiveBoardRequest->clearResults();
}

void AppData::newLiveboardRequest(){
	if(_currentLiveBoardRequest != null)
		delete _currentLiveBoardRequest;
	_currentLiveBoardRequest = new LiveBoardRequest();
}
