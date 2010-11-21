/*
 * IRailConnection.cpp
 *
 *  Created on: 31-okt-2010
 *      Author: B
 */

#include "IRailConnection.h"
#include <FXml.h>
#include "Connection.h"
#include "TrainsResultsForm.h"

using namespace Osp::Net::Http;
using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Xml;
using namespace Osp::Base::Collection;

IRailConnection::IRailConnection() {
}

IRailConnection::~IRailConnection() {
}

String IRailConnection::getTrip(String &from, String &to,TrainsResultsForm *pTrainsResultsForm) {
	this->pTrainsResultsForm = pTrainsResultsForm;
	result r = E_SUCCESS;
	String* pProxyAddr = null;
	String hostAddr = L"http://api.irail.be";
	String hostAddr2(L"http://api.irail.be/connections/?to=");
	hostAddr2.Append(to);
	hostAddr2.Append(L"&from=");
	hostAddr2.Append(from);
	HttpSession* pSession = null;
	HttpTransaction* pTransaction = null;

	pSession = new HttpSession();
	r = pSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, pProxyAddr ,hostAddr,null);
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
	return hostAddr;
}

void IRailConnection::OnTransactionReadyToRead(HttpSession& httpSession,
		HttpTransaction& httpTransaction, int availableBodyLen) {
	//LEZEN werkt !
	ArrayListT<Connection> connections;
	connections.Construct(10);
	HttpResponse* resp = httpTransaction.GetResponse();
	ByteBuffer* buf = (resp->ReadBodyN());
	xmlDocPtr doc =
			xmlParseMemory((char*) (buf->GetPointer()), buf->GetLimit());
	if (doc != null) {
		xmlNodePtr connection = null;
		xmlNodePtr pRoot = xmlDocGetRootElement(doc);
		for (connection = pRoot->children; connection; connection
				= connection->next) {
			xmlNodePtr child = null;
			Connection con;
			for (child = connection->children; child; child = child->next) {
				if (child->type == XML_ELEMENT_NODE) {

					String nodeName;
					Osp::Base::Utility::StringUtil::Utf8ToString(
							(char*) child->name, nodeName);
					if (nodeName.CompareTo("departure") == 0) {
						xmlNodePtr child1 = null;
						for (child1 = child->children; child1; child1
								= child1->next) {
							if (child1->type == XML_ELEMENT_NODE) {
								String nodeName1;
								Osp::Base::Utility::StringUtil::Utf8ToString(
										(char*) child1->name, nodeName1);
								if (nodeName1.CompareTo("time") == 0) {
									xmlAttrPtr isoTime = child1->properties;
									if (isoTime != null && isoTime->type
											== XML_ATTRIBUTE_NODE) {
										String time;
										Osp::Base::Utility::StringUtil::Utf8ToString(
												(char*) isoTime->children->content,
												time);
										con.setFromTime(time);
									}
								} else if (nodeName1.CompareTo("station") == 0) {
									String station;
									Osp::Base::Utility::StringUtil::Utf8ToString(
											(char*) child1->children->content,
											station);
									con.setFromStation(station);
								}
							}
						}
					} else if (nodeName.CompareTo("arrival") == 0) {
						xmlNodePtr child1 = null;
						for (child1 = child->children; child1; child1
								= child1->next) {
							if (child1->type == XML_ELEMENT_NODE) {
								String nodeName1;
								Osp::Base::Utility::StringUtil::Utf8ToString(
										(char*) child1->name, nodeName1);
								if (nodeName1.CompareTo("time") == 0) {
									xmlAttrPtr isoTime = child1->properties;
									if (isoTime != null && isoTime->type
											== XML_ATTRIBUTE_NODE) {
										String time;
										Osp::Base::Utility::StringUtil::Utf8ToString(
												(char*) isoTime->children->content,
												time);
										con.setToTime(time);
									}
								} else if (nodeName1.CompareTo("station") == 0) {
									String station;
									Osp::Base::Utility::StringUtil::Utf8ToString(
											(char*) child1->children->content,
											station);
									con.setToStation(station);
								}
							}
						}
					} else if (nodeName.CompareTo("duration") == 0) {
						String duration_;
						Osp::Base::Utility::StringUtil::Utf8ToString(
								(char*) child->children->content, duration_);
						int duration;
						AppLog("duration is : %S",duration_.GetPointer());
						Integer::Parse(duration_, duration);

						con.setDuration(duration);
					}
				}
			}
			if(con != null) {
				connections.Add(con);
			}
		}
		xmlFreeDoc(doc);
		this->pTrainsResultsForm->setConnections(connections);
	} else {
		AppLog("parsing internet file failed");
	}
}

void IRailConnection::OnTransactionAborted(HttpSession& httpSession,
		HttpTransaction& httpTransaction, result r) {
	AppLog("OnTransactionAborted\n");
}

void IRailConnection::OnTransactionReadyToWrite(HttpSession& httpSession,
		HttpTransaction& httpTransaction, int recommendedChunkSize) {
	AppLog("OnTransactionReadyToWrite\n");
}

void IRailConnection::OnTransactionHeaderCompleted(HttpSession& httpSession,
		HttpTransaction& httpTransaction, int headerLen, bool bAuthRequired) {
	AppLog("OnTransactionHeaderCompleted\n");
}

void IRailConnection::OnTransactionCompleted(HttpSession& httpSession,
		HttpTransaction& httpTransaction) {
	AppLog("OnTransactionCompleted\n");
}

void IRailConnection::OnTransactionCertVerificationRequiredN(
		HttpSession& httpSession, HttpTransaction& httpTransaction,
		String* pCert) {
	AppLog("OnTransactionCertVerificationRequiredN\n");
}
