/*
 * RouteRequestManager.cpp
 *
 *  Created on: 28-apr-2011
 *  Author: Bart Bruynooghe
 */

#include "controller/RouteRequestManager.h"

#include "Model/Trip.h"
#include "model/IRailAPI.h"
#include "model/AppData.h"
#include "controller/controller.h"

using namespace Osp::Net::Http;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Io;

RouteRequestManager::RouteRequestManager():
	__pSession(null),
	__pTransaction(null),
	__pRequest(null)
	//TODO set all null pointers
{
}

RouteRequestManager::~RouteRequestManager() {
	cancelRequest();
}

void RouteRequestManager::cancelRequest(){
	if(__pTransaction){
			__pTransaction->RemoveHttpTransactionListener(*this);
			delete __pTransaction;
			__pTransaction = null;
	}
	if(__pSession){
		__pSession->CloseAllTransactions();
		delete __pSession;
		__pSession = null;
	}
}

void RouteRequestManager::setRequest(Request* req){

	__pRequest = req;
	String hostAddr = L"http://api.irail.be";

	result r = E_SUCCESS;
	__pSession = new HttpSession();
	r = __pSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, null ,hostAddr,null);
	if (IsFailed(r))
		AppLogDebug("Construct Session failed. (%s)\n", GetErrorMessage(r));


	__pTransaction = __pSession->OpenTransactionN();
	if (null == __pTransaction)
		AppLogDebug("Construct Session failed. \n");

	r = __pTransaction->AddHttpTransactionListener(*this);
	if (IsFailed(r))
		AppLogDebug("AddHttpTransactionListener Session failed.\n");

	__pHttpRequest = __pTransaction->GetRequest();
	if(__pHttpRequest == null)
		AppLogDebug("GetRequest failed. \n");

	String hostAddr2(L"http://api.irail.be/connections/?to=");
	hostAddr2.Append(*req->getToStation()->getNameN());
	hostAddr2.Append(L"&from=");
	hostAddr2.Append(*req->getFromStation()->getNameN());
	hostAddr2.Replace(L" ","-");
	hostAddr2.Append(L"&typeOfTransport=train");
	DateTime* dt = req->getDateTime();
	if(dt){
		//LocaleManager localeManager;
		//localeManager.Construct();
		//TimeZone timeZone = localeManager.GetSystemTimeZone();
		//DateTime utcDateTime = timeZone.WallTimeToUtcTime(*req->getDateTime());
		hostAddr2.Append(L"&date=");
		if(dt->GetDay()<10)
			hostAddr2.Append(L"0");
		hostAddr2.Append(Integer::ToString(dt->GetDay()));
		if(dt->GetMonth()<10)
			hostAddr2.Append(L"0");
		hostAddr2.Append(Integer::ToString(dt->GetMonth()));
		String year;
		Integer::ToString(dt->GetYear()).SubString(2,year);
		hostAddr2.Append(year);

		hostAddr2.Append(L"&time=");
		if(dt->GetHour()<10)
			hostAddr2.Append(L"0");
		hostAddr2.Append(Integer::ToString(dt->GetHour()));
		if(dt->GetMinute()<10)
			hostAddr2.Append(L"0");
		hostAddr2.Append(Integer::ToString(dt->GetMinute()));
	}

	AppLog("request link: %S",hostAddr2.GetPointer());

	r = __pHttpRequest->SetUri(hostAddr2);
	if(IsFailed(r))
		AppLog("SetUri failed. (%s)\n", GetErrorMessage(r));

	r = __pHttpRequest->SetMethod(NET_HTTP_METHOD_GET);
	if(IsFailed(r))
		AppLog("SetMethod failed. (%s)\n", GetErrorMessage(r));

	// Header Setting
	HttpHeader* pHttpHeader = null;
	pHttpHeader = __pHttpRequest->GetHeader();
	if (null == pHttpHeader){
		r = GetLastResult();
		AppLog("Uri Setting failed. (%s)\n", GetErrorMessage(r));
		r = pHttpHeader->AddField(L"Content-Length", L"1024");
		if (IsFailed(r))AppLog("Header Setting failed. (%s)\n", GetErrorMessage(r));
	}

	r = __pTransaction->Submit();
	if(IsFailed(r))
		AppLogDebug("Submit failed. (%s)\n", GetErrorMessage(r));
	//AppLog("request sended");

	//TODO delete __pHttpRequest
	//TODO delete pHttpHeader
}

void RouteRequestManager::OnTransactionReadyToRead(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen){
	AppLogDebug("http ready called");
	HttpResponse* resp = httpTransaction.GetResponse();
	//String status = resp->GetStatusText();
	//AppLog("status: %S",status);

	ByteBuffer* buffer = (resp->ReadBodyN());
	char data[buffer->GetLimit()+1];
	buffer->SetPosition(0);
	buffer->GetArray((byte*)data, 0, buffer->GetLimit());
	data[buffer->GetLimit()] ='\0';
	String test(data);
	AppLogDebug("%S",test.GetPointer());
	AppLogDebug("\n\n");

	ArrayListT<Trip*>* trips=null;
	IRailAPI h;
	if(AppData::GetInstance()->getCurrentRequest() != null){
		trips = h.createTripList(buffer);
	}
	if(trips != null){
		AppData::GetInstance()->getCurrentRequest()->getTrips()->AddItems(*trips);
		AppLog("parsing succesfull");
		Controller::GetInstance()->switchToRoutePlannerResults();
	}
	else{
		AppLog("parsing failed");
	}
	//write to file
	/*
	File f;
	int fileIndex = getRoutePlannerRegistryIndex();
	f.Construct(L"/Home/history/RP"+ Integer::ToString(fileIndex) + ".xml",L"w+",false);
	f.Write(*buffer);
	*/
}

int RouteRequestManager::getRoutePlannerRegistryIndex(){
    Registry reg;
    String regPathName(L"/Home/register.ini");

    // section name
    String historySection(L"history");

    //entries
    String routePlannerAmountEntry(L"RPA");
    String liveBoardAmountEntry("LBA");

    int routePlannerAmount=-1;
    result r = E_SUCCESS;

    r = reg.Construct(regPathName, true); // create a new registry if not exists
    if(IsFailed(r)){
        AppLog("failed create registry");
    	goto CATCH;
    }

    // create sections
    r = reg.AddSection(historySection);

    r = reg.GetValue(historySection,routePlannerAmountEntry , routePlannerAmount);
    if(IsFailed(r)){
    	AppLog("get val failed/ prob creating new one");
    	r = reg.AddValue(historySection,routePlannerAmountEntry,0);
    	if(IsFailed(r)){
    		AppLog("creating entry failed");
    	}
    	//routePlannerAmount=-1; //perhaps no value is here
    }
    //routePlannerAmount++;
    //routePlannerAmount = routePlannerAmount%AppData::HISTORY_AMOUNT;

    r = reg.SetValue(historySection, routePlannerAmountEntry, routePlannerAmount);
    if(IsFailed(r)){
    	AppLog("set value failed");
    	goto CATCH;
    }

    // write to the register
    r = reg.Flush();
    if(IsFailed(r)){
        AppLog("flushing failed");
    	goto CATCH;
    }
    return routePlannerAmount;

    CATCH:
		// Do some error handling
		return 0;
}

void RouteRequestManager::OnTransactionAborted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, result r){}
void RouteRequestManager::OnTransactionReadyToWrite(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize){}
void RouteRequestManager::OnTransactionHeaderCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool rs){}
void RouteRequestManager::OnTransactionCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction){}
void RouteRequestManager::OnTransactionCertVerificationRequiredN(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, Osp::Base::String* pCert){}
