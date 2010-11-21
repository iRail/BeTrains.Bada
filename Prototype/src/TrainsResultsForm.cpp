
#include "TrainsResultsForm.h"
#include "Connection.h"
#include "BetrainsPrototype.h"
#include <FLclLocaleManager.h>
#include <FLclLocale.h>


using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base::Collection;
using namespace Osp::Locales;

TrainsResultsForm::TrainsResultsForm(void)//: pItemFactory(new TableItemFactory())
{
	// Nothing to do
	pItemFactory = new ItemFactory();
}

TrainsResultsForm::~TrainsResultsForm(void)
{
}

bool
TrainsResultsForm::Initialize()
{
	Form::Construct(L"IDF_PLANNER");
	SlidableList* list = static_cast<SlidableList*>(GetControl(L"TESTLIJST", false));
	pItemFactory->Initialise(list->GetWidth());
	SetSoftkeyActionId(SOFTKEY_1, Constants::BACK);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
	return E_SUCCESS;
}

void TrainsResultsForm::setConnections(ArrayListT<Connection> &connections){
	SlidableList* list = static_cast<SlidableList*>(GetControl(L"TESTLIJST", false));
	pItemFactory->Initialise(list->GetWidth());
	for(int i=0;i<connections.GetCount();i++){
		Connection conn;
		String stations;
		connections.GetAt(i,conn);
		stations += conn.getFromStation();
		stations += L" - ";
		stations += conn.getToStation();
		String times;
		times = Integer::ToString(conn.getFromTime().GetHour()) + L":" + Integer::ToString(conn.getFromTime().GetMinute())+L" - ";
		times += Integer::ToString(conn.getToTime().GetHour()) + L":" + Integer::ToString(conn.getToTime().GetMinute());
		// indien het aantal minuten kleiner is dan 10 wordt er geen 0 voor gezet, dus zorgen we ervoor dat dit wel gebeurt
		String minutes;
		int intminutes = conn.getDuration().GetMinutes();
		minutes = Integer::ToString(intminutes);
		if(minutes.GetLength() < 2){
			minutes.Insert('0',0);
		}
		String duration = Integer::ToString(conn.getDuration().GetHours()) + L":" + minutes.GetPointer();
		list->AddItem(*(pItemFactory->createItem(stations, times, duration,conn.getTrains())));
	}

	this->RequestRedraw(true);
}

result
TrainsResultsForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result
TrainsResultsForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}


void
TrainsResultsForm::OnActionPerformed(const Control& source, int actionId)
{
	BetrainsPrototype* app = (BetrainsPrototype*)this->GetParent();
	switch ( actionId ) {
	  case Constants::BACK:
		  app->showMenu();
	  default :
		  app->showMenu();
	}

}

void
TrainsResultsForm::OnFocusGained(const Control &source)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnFocusLost(const Control &source)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnKeyLongPressed(const Control &source, KeyCode keyCode)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnKeyPressed(const Control &source, KeyCode keyCode)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnKeyReleased(const Control &source, KeyCode keyCode)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnTouchDoublePressed(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnTouchFocusIn(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnTouchFocusOut(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnTouchLongPressed(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnTouchMoved(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnTouchPressed(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnTouchReleased(const Control &source, const Osp::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnItemStateChanged(const Control &source, int index, int itemId, int elementId, ItemStatus status)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnItemStateChanged(const Control &source, int index, int itemId, ItemStatus status)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnListPropertyRequested(const Control &source)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnLoadToBottomRequested(const Control &source, int index, int numItems)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnLoadToTopRequested(const Control &source, int index, int numItems)
{
	// TODO: Add your implementation codes here

}

void
TrainsResultsForm::OnUnloadItemRequested(const Control  &source, int index)
{
	// TODO: Add your implementation codes here

}

