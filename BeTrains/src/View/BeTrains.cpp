/**
 * Name        : BeTrains
 * Version     : 
 * Vendor      : iRail Betrains
 * Description : 
 * Author	   : Bart Bruynooghe
 */


#include "View/BeTrains.h"
#include "Model/Connection.h"
#include "Model/Trip.h"
#include "Controller/Controller.h"
#include "View/TripListForm.h"


using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Net::Http;

BeTrains::BeTrains()
{
	// initialize variables , a list of request is forseen with a default capacity of 5
	stationSelectForm = null;
	plannerForm = null;
	tripListForm = null;
	testTripList = null;
	currentRequest = null;
	previousRequests.Construct(10);

	//TODO demo files, can be removed later
	String fileName(L"/Home/test.xml");
	File *file = new File();
	FileAttributes sourcefilemeta;
	File::GetAttributes(fileName, sourcefilemeta);
	int filesize = sourcefilemeta.GetFileSize();
	ByteBuffer buffer;
	buffer.Construct(filesize);
	file->Construct(fileName, L"r");
	file->Read(buffer);
	delete file;
	buffer.SetPosition(0);
	testTripList = controller.createTripList(&buffer);
}

BeTrains::~BeTrains()
{
}

Application* BeTrains::CreateInstance(void)
{
	return new BeTrains();
}

bool BeTrains::OnAppInitializing(AppRegistry& appRegistry)
{
	frame = Application::GetInstance()->GetAppFrame()->GetFrame();
	//create all Forms
	mainForm = new MainForm();
	stationSelectForm = new StationSelectForm();
	plannerForm = new PlannerForm();
	tripListForm = new TripListForm;

	//initiate forms
	mainForm->Initialize();
	stationSelectForm->Initialize();
	plannerForm->Initialize();
	tripListForm->Initialize();

	//add forms to frame
	frame->AddControl(*mainForm);
	frame->AddControl(*stationSelectForm);
	frame->AddControl(*plannerForm);
	frame->AddControl(*tripListForm);

	//load mainform on front
	showMainMenu();
	return true;
}

void BeTrains::showMainMenu(){
	frame->SetCurrentForm(*mainForm);
	frame->RequestRedraw();
}

void BeTrains::showMap(){
	showTripList();
}

void BeTrains::showRoutePlanner(){
	plannerForm->update(currentRequest);
	frame->SetCurrentForm(*plannerForm);
	frame->RequestRedraw();
}

void BeTrains::showTripList(){
	tripListForm->update(currentRequest);


	//DUMMY ITEMS
	//Request * r = new Request();
	//r->getResults()->AddItems(*testTripList);
	//tripListForm->update(r);
	//END DUMMY ITEMS

	frame->SetCurrentForm(*tripListForm);
	frame->RequestRedraw();
}

void BeTrains::cancelCurrentRequest(){
	if(currentRequest != null){
		delete currentRequest;
		currentRequest=null;
	}
	showMainMenu();
}

void BeTrains::routePlannerSelectStation(bool isFromStation,Station* selectedStation){
	if(currentRequest == null)
		currentRequest = new Request();
	if(isFromStation){
		currentRequest->setFromStation(selectedStation);
	}else{
		currentRequest->setToStation(selectedStation);
	}
	plannerForm->update(currentRequest);
	frame->SetCurrentForm(*plannerForm);
	frame->RequestRedraw();
}

void BeTrains::update(){
	//AppLog("Update method invocation");
}

void BeTrains::showRoutePlannerStationSelector(bool isFromStation){
	stationSelectForm->update(isFromStation);
	frame->SetCurrentForm(*stationSelectForm);
	frame->RequestRedraw();
	stationSelectForm->setKeyboard();
}

void BeTrains::showRoutePlannerResults(){
	//TODO : implement
}

bool
BeTrains::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	return true;
}

ArrayListT<Station*> * BeTrains::getStationList(){
	return controller.getStations();
}

Controller* const BeTrains::getController(){
	return &controller;
}

void BeTrains::getFromInternet(const String* const from,const String* const to){
	result r = E_SUCCESS;
	String hostAddr = L"http://api.irail.be";
	String hostAddr2(L"http://api.irail.be/connections/?to=");
	hostAddr2.Append(*to);
	hostAddr2.Append(L"&from=");
	hostAddr2.Append(*from);
	HttpSession* pSession = null;
	HttpTransaction* pTransaction = null;
	hostAddr2.Replace(L" ","%20");
	AppLog("go to site: %S",hostAddr2.GetPointer());
	pSession = new HttpSession();
	r = pSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, null ,hostAddr,null);
	if (IsFailed(r))
	{
		AppLog("Construct Session failed. (%s)\n", GetErrorMessage(r));
	}
	pTransaction = pSession->OpenTransactionN();
	if (null == pTransaction)
	{
		AppLog("Construct Session failed. \n");
	}
	r = pTransaction->AddHttpTransactionListener(*this);
	if (IsFailed(r))
	{
		AppLog("AddHttpTransactionListener Session failed.\n");
	}
	HttpRequest* pRequest = pTransaction->GetRequest();
	if(pRequest == null)
	{
		AppLog("GetRequest failed. \n");
	}

	r = pRequest->SetUri(hostAddr2);
	if(IsFailed(r))
	{
		AppLog("SetUri failed. (%s)\n", GetErrorMessage(r));
	}

	r = pRequest->SetMethod(NET_HTTP_METHOD_GET);
	if(IsFailed(r))
	{
		AppLog("SetMethod failed. (%s)\n", GetErrorMessage(r));
	}
	r = pTransaction->Submit();
	if(IsFailed(r))
	{
		AppLog("Submit failed. (%s)\n", GetErrorMessage(r));
	}
}

void BeTrains::OnTransactionReadyToRead(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen){
	HttpResponse* resp = httpTransaction.GetResponse();
	ByteBuffer* buf = (resp->ReadBodyN());
	if(currentRequest != null){
		currentRequest->getResults()->AddItems(* controller.createTripList(buf));
	}
	this->showTripList();
}
void BeTrains::OnTransactionAborted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, result r){}
void BeTrains::OnTransactionReadyToWrite(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize){}
void BeTrains::OnTransactionHeaderCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool rs){}
void BeTrains::OnTransactionCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction){}
void BeTrains::OnTransactionCertVerificationRequiredN(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, Osp::Base::String* pCert){}
