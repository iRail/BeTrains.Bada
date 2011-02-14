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

//TODO place in Betrains.cpp and Betrains.h in controller folder
BeTrains::BeTrains()
{
	// initialize variables , a list of request is forseen with a default capacity of 5
	stationSelectForm = null;
	plannerForm = null;
	tripListForm = null;
	currentRequest = null;
	detailsListForm = null;
	tripListForm = null;
	previousRequests.Construct(10);
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
	tripListForm = new TripListForm();
	detailsListForm = new DetailsListForm();
	tripListForm2 = new TripListForm2();

	//initiate forms
	mainForm->Initialize();
	stationSelectForm->Initialize();
	plannerForm->Initialize();
	tripListForm->Initialize();
	detailsListForm->Initialize();
	tripListForm2->Initialize();

	//add forms to frame
	frame->AddControl(*mainForm);
	frame->AddControl(*plannerForm);
	frame->AddControl(*tripListForm);
	frame->AddControl(*stationSelectForm);
	frame->AddControl(*detailsListForm);
	frame->AddControl(*tripListForm2);

	//load mainform on front
	showMainMenu();
	return true;
}

void BeTrains::showMainMenu(){
	frame->SetCurrentForm(*mainForm);
	frame->RequestRedraw();
}

void BeTrains::showMap(){
	tripListForm2->update(currentRequest);
	tripListForm2->RequestRedraw();
	frame->SetCurrentForm(*tripListForm2);
	frame->RequestRedraw();
}

void BeTrains::showRoutePlanner(){
	if(currentRequest == null)
		currentRequest = new Request();
	else{ //currentRequest != null
		if(currentRequest->getResults() != null){
			//if there are already results: move request to request list (history)
			//and make a new request
			//copy from and to, to the new request
			//previousRequests.Add(currentRequest);
			Request* previousRequest = currentRequest;
			currentRequest = new Request();
			currentRequest->setFromStation(previousRequest->getFromStation());
			currentRequest->setToStation(previousRequest->getToStation());
			//TODO copy time from old to new
		}
	}
	plannerForm->update(currentRequest);
	frame->SetCurrentForm(*plannerForm);
	frame->RequestRedraw();
}

void BeTrains::showTripList(){
	tripListForm->update(currentRequest);
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

void BeTrains::showRouteDetails(Trip* trip){
	detailsListForm->update(trip);
	frame->SetCurrentForm(*detailsListForm);
	frame->RequestRedraw();
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

//TODO, request in place of 2 strings
void BeTrains::getFromInternet(Request* request){
	result r = E_SUCCESS;
	String hostAddr = L"http://api.irail.be";
	String hostAddr2(L"http://api.irail.be/connections/?to=");
	hostAddr2.Append(*request->getToStation()->getName());
	hostAddr2.Append(L"&from=");
	hostAddr2.Append(*request->getFromStation()->getName());
	hostAddr2.Replace(L" ","-");
	hostAddr2.Append(L"&typeOfTransport=train");
	//AppLog("go to site: %S",hostAddr2.GetPointer());
	//TODO if datetime is not null add this to the link also departure/arrival
	//&date=311210&time=2359&timeSel=arrive
	if(request->getDateTime() != null){
		hostAddr2 += L"&date=" + request->parseDate();
		hostAddr2 += L"&time=" + request->parseTime();
		if(request->isDeparture())
			hostAddr2 += L"timeSel=depart";
		else
			hostAddr2 += L"timeSel=arrive";
 	}

	AppLog("request site: %S",hostAddr2.GetPointer());
	HttpSession* pSession = null;
	HttpTransaction* pTransaction = null;
	pSession = new HttpSession();

	r = pSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, null ,hostAddr,null);
	if (IsFailed(r)) AppLog("Construct Session failed. (%s)\n", GetErrorMessage(r));

	pTransaction = pSession->OpenTransactionN();
	if (null == pTransaction) AppLog("Construct Session failed. \n");

	r = pTransaction->AddHttpTransactionListener(*this);
	if (IsFailed(r)) AppLog("AddHttpTransactionListener Session failed.\n");

	HttpRequest* pRequest = pTransaction->GetRequest();
	if(pRequest == null) AppLog("GetRequest failed. \n");

	r = pRequest->SetUri(hostAddr2);
	if(IsFailed(r))	AppLog("SetUri failed. (%s)\n", GetErrorMessage(r));

	r = pRequest->SetMethod(NET_HTTP_METHOD_GET);
	if(IsFailed(r)) AppLog("SetMethod failed. (%s)\n", GetErrorMessage(r));

	// Header Setting
	HttpHeader* pHttpHeader = null;
	pHttpHeader = pRequest->GetHeader();
	if (null == pHttpHeader){
		r = GetLastResult();
		AppLog("Uri Setting failed. (%s)\n", GetErrorMessage(r));
		r = pHttpHeader->AddField(L"Content-Length", L"1024");
		if (IsFailed(r))AppLog("Header Setting failed. (%s)\n", GetErrorMessage(r));
	}

	r = pTransaction->Submit();
	if(IsFailed(r)) AppLog("Submit failed. (%s)\n", GetErrorMessage(r));
	//AppLog("request sended");
}

void BeTrains::OnTransactionReadyToRead(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen){
	HttpResponse* resp = httpTransaction.GetResponse();
	//String status = resp->GetStatusText();
	//AppLog("status: %S",status);
	ByteBuffer* buf = (resp->ReadBodyN());
	if(currentRequest != null){
		currentRequest->getResults()->AddItems(* controller.createTripList(buf));
	}
	showMap();
}

void BeTrains::OnTransactionAborted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, result r){}
void BeTrains::OnTransactionReadyToWrite(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize){}
void BeTrains::OnTransactionHeaderCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool rs){}
void BeTrains::OnTransactionCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction){}
void BeTrains::OnTransactionCertVerificationRequiredN(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, Osp::Base::String* pCert){}
