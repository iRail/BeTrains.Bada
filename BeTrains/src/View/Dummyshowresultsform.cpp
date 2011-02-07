#include "View/Dummyshowresultsform.h"
#include "View/BeTrains.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

Dummyshowresultsform::Dummyshowresultsform(void) {
	pItemFactory = new ItemFactory();
}

Dummyshowresultsform::~Dummyshowresultsform(void) {
}

bool Dummyshowresultsform::Initialize() {
	Form::Construct(L"DummyShowResultsForm");
	return true;
}

result Dummyshowresultsform::OnInitializing(void) {
	result r = E_SUCCESS;
	Fill();
	// TODO: Add your initialization code here


	return r;
}

result Dummyshowresultsform::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void Dummyshowresultsform::Fill(){

	/*
	 * some dummycode, to fill up a list with results by using the model
	 */

	BeTrains* app = (BeTrains*)this->GetParent();
	//AppLog("app pointer in Fill methode : %d",app);
	result r = E_SUCCESS;
	String fileName(L"/Home/test.xml");
	File *file = new File();
	FileAttributes sourcefilemeta;
	File::GetAttributes(fileName, sourcefilemeta);
	int filesize = sourcefilemeta.GetFileSize();
	ByteBuffer buffer;
	buffer.Construct(filesize);
	AppLog("Read buffer size %d", buffer.GetLimit());
	r = file->Construct(fileName, L"r"); //for write: w or w+
	r = file->Read(buffer); //to write: file->Write *beware of the permission w instead of r
	delete file; //closes the file, there is no default close method for files, its gets closed when its scope is closed
	buffer.SetPosition(0);
	Controller* c = app->getController();
	//AppLog("controller pointer is : %d",c);
	ArrayListT<Trip *> * test = c->createTripList(&buffer);

	/*
	 * put the dummy data in the list
	 */

	SlidableList* list = static_cast<SlidableList*>(GetControl(L"SlideableList", false));
	pItemFactory->Initialise(list->GetWidth());

	for(int i=0;i<test->GetCount();i++){
		//AppLog("aantal trips : %d",test->GetCount());
		Trip* trip;
		test->GetAt(i,trip);
		/*
		 * we werken met connections, dus om start en einde van de trip te weten :  from van het eerste station, en to van het laatste station
		 * laatste kan natuurlijk == zijn eerste connection
		 */


		Connection* firstConn;
		Connection* secondConn;
		ArrayListT<Connection*>* connections = trip->getConnections();
		connections->GetAt(0,firstConn);
		connections->GetAt(connections->GetCount()-1,secondConn);
		String stations;
		AppLog("pointer check : %d",firstConn->getStartNode()->getStation());
		stations += L"Yelo";//*firstConn->getStartNode()->getStation()->getName();
		stations += L" - ";
		stations += L"Owla";//*secondConn->getEndNode()->getStation()->getName();
		String times = L"02:00";
		//times = Integer::ToString(conn.getFromTime().GetHour()) + L":" + Integer::ToString(conn.getFromTime().GetMinute())+L" - ";
		//times += Integer::ToString(conn.getToTime().GetHour()) + L":" + Integer::ToString(conn.getToTime().GetMinute());
		// indien het aantal minuten kleiner is dan 10 wordt er geen 0 voor gezet, dus zorgen we ervoor dat dit wel gebeurt
		String minutes;
		int intminutes = 5;
		minutes = Integer::ToString(intminutes);

		if(minutes.GetLength() < 2){
			minutes.Insert('0',0);
		}

		String duration = Integer::ToString(trip->getDuration()->GetHours()) + L":" + Integer::ToString(trip->getDuration()->GetMinutes());
		list->AddItem(*(pItemFactory->createItem(stations, times, duration,2)));
		}

		this->RequestRedraw(true);

	AppLog("Done");
}
