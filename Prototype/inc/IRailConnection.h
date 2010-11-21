/*
 * IRailConnection.h
 *
 *  Created on: 31-okt-2010
 *      Author: B
 */

#ifndef IRAILCONNECTION_H_
#define IRAILCONNECTION_H_
#include <FNet.h>
#include <FBase.h>
#include "TrainsResultsForm.h"

using namespace Osp::Base;
using namespace Osp::Net::Http;
using namespace Osp::Base::Collection;

class IRailConnection:
	public Osp::Net::Http::IHttpTransactionEventListener {
public:
	String getTrip(String &from,String &to,TrainsResultsForm *pTrainsResultsForm);
	IRailConnection();
	virtual ~IRailConnection();

	void OnTransactionReadyToRead(HttpSession& httpSession, HttpTransaction& httpTransaction, int availableBodyLen);
	void OnTransactionAborted(HttpSession& httpSession, HttpTransaction& httpTransaction, result r);
	void OnTransactionReadyToWrite(HttpSession& httpSession, HttpTransaction& httpTransaction, int recommendedChunkSize);
	void OnTransactionHeaderCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction, int headerLen, bool bAuthRequired);
	void OnTransactionCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction);
	void OnTransactionCertVerificationRequiredN(HttpSession& httpSession, HttpTransaction& httpTransaction, String* pCert);
private:
	TrainsResultsForm *pTrainsResultsForm;

};

#endif /* IRAILCONNECTION_H_ */
