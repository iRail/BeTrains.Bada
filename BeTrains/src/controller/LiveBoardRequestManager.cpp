/*
 * RouteRequestManager.cpp
 *
 *  Created on: 28-apr-2011
 *  Author: Bart Bruynooghe
 */

#include "controller/LiveBoardRequestManager.h"

#include "Model/Trip.h"
#include "model/IRailAPI.h"
#include "model/AppData.h"
<<<<<<< HEAD
#include "controller/controller.h"
=======
#include "controller/Controller.h"
>>>>>>> 84df178bf1f69ad621e514bc2e620facdb652e6c

using namespace Osp::Net::Http;
using namespace Osp::Base;
using namespace Osp::Base::Collection;

LiveBoardRequestManager::LiveBoardRequestManager():
	__pSession(null),
	__pTransaction(null),
	__pRequest(null),
	addToResults(false)
{
}

LiveBoardRequestManager::~LiveBoardRequestManager() {
	cancelRequest();
}

void LiveBoardRequestManager::cancelRequest(){
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

void LiveBoardRequestManager::setRequest(LiveBoardRequest* req,bool addToResults_){
	addToResults = addToResults_;
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

	String hostAddr2(L"http://api.irail.be/liveboard/?id=");
	hostAddr2.Append(req->getStation()->getId());

	DateTime* dt = req->getDateTime();
	if(dt){
		//LocaleManager localeManager;
		//localeManager.Construct();
		//TimeZone timeZone = localeManager.GetSystemTimeZone();
		//DateTime utcDateTime = timeZone.WallTimeToUtcTime(*req->getDateTime());

		hostAddr2.Append(L"&time=");
		if(dt->GetHour()<10)
			hostAddr2.Append(L"0");
		hostAddr2.Append(Integer::ToString(dt->GetHour()));
		if(dt->GetMinute()<10)
			hostAddr2.Append(L"0");
		hostAddr2.Append(Integer::ToString(dt->GetMinute()));
	}

	AppLogDebug("request link: %S",hostAddr2.GetPointer());

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
		AppLogDebug("Uri Setting failed. (%s)\n", GetErrorMessage(r));
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


void LiveBoardRequestManager::OnTransactionReadyToRead(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen){
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

	ArrayListT<LiveBoardResult*>* results=null;
	IRailAPI h;
	if(AppData::GetInstance()->getCurrentRequest() != null){
		results = h.createLiveBoardList(buffer);
	}
	if(results != null){
<<<<<<< HEAD
		AppLog("parsing live board successfull");
=======
		if(!addToResults)
			AppData::GetInstance()->getCurrentLiveBoardRequest()->clearResults();
		AppLog("parsing live board successfull. #%S",Integer::ToString(results->GetCount()).GetPointer());
>>>>>>> 84df178bf1f69ad621e514bc2e620facdb652e6c
		AppData::GetInstance()->getCurrentLiveBoardRequest()->getResults()->AddItems(*results);
		Controller::GetInstance()->switchToLiveBoardResults();
	}else{
		AppLog("parsing failed liveboards");
	}
}

void LiveBoardRequestManager::OnTransactionAborted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, result r){}
void LiveBoardRequestManager::OnTransactionReadyToWrite(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize){}
void LiveBoardRequestManager::OnTransactionHeaderCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool rs){}
void LiveBoardRequestManager::OnTransactionCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction){}
void LiveBoardRequestManager::OnTransactionCertVerificationRequiredN(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, Osp::Base::String* pCert){}
