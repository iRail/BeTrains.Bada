/*
 * RouteRequestManager.h
 *
 *  Created on: 8-may-2011
 *  Author: Bart Bruynooghe
 */

#ifndef LIVE_BOARD_REQUEST_MANAGER_H_
#define LIVE_BOARD_REQUEST_MANAGER_H_

#include <FNet.h>
#include "model/LiveBoardRequest.h"

class LiveBoardRequestManager:
	public Osp::Net::Http::IHttpTransactionEventListener
{
public:
	LiveBoardRequestManager();
	virtual ~LiveBoardRequestManager();

	void cancelRequest();
	void setRequest(LiveBoardRequest* req,bool addToResults_=false);

	void OnTransactionReadyToRead(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen);
	void OnTransactionAborted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, result r);
	void OnTransactionReadyToWrite(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize);
	void OnTransactionHeaderCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool rs);
	void OnTransactionCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction);
	void OnTransactionCertVerificationRequiredN(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, Osp::Base::String* pCert);

private:
	Osp::Net::Http::HttpSession* 			__pSession; 	//ownership
	Osp::Net::Http::HttpTransaction* 		__pTransaction; //ownership
	Osp::Net::Http::HttpRequest* 			__pHttpRequest;	//ownership
	LiveBoardRequest*						__pRequest; 	//no ownership
	bool 									addToResults;
};

#endif /* LIVE_BOARD_REQUEST_MANAGER_H_ */
