/*
 * RouteRequestManager.h
 *
 *  Created on: 28-apr-2011
 *  Author: Bart Bruynooghe
 */

#ifndef ROUTEREQUESTMANAGER_H_
#define ROUTEREQUESTMANAGER_H_

#include <FNet.h>
#include "Model/Request.h"

class RouteRequestManager:
	public Osp::Net::Http::IHttpTransactionEventListener
{
public:
	RouteRequestManager();
	virtual ~RouteRequestManager();

	void cancelRequest();
	void setRequest(Request* req,bool addToResults_=false);

	void OnTransactionReadyToRead(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen);
	void OnTransactionAborted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, result r);
	void OnTransactionReadyToWrite(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize);
	void OnTransactionHeaderCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool rs);
	void OnTransactionCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction);
	void OnTransactionCertVerificationRequiredN(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, Osp::Base::String* pCert);
	int getRoutePlannerRegistryIndex(); //returns current index of history
private:
	Osp::Net::Http::HttpSession* 			__pSession; 	//ownership
	Osp::Net::Http::HttpTransaction* 		__pTransaction; //ownership
	Osp::Net::Http::HttpRequest* 			__pHttpRequest;	//ownership
	Request*								__pRequest; 	//no ownership
	bool 									addToResults;	//do we add results to all the results or clear them first
};

#endif /* ROUTEREQUESTMANAGER_H_ */
