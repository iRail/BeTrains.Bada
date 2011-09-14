#include "view/RoutePlannerResults.h"
#include "controller/Controller.h"
#include "model/AppData.h"
#include "view/Utils.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

RoutePlannerResults::RoutePlannerResults(void) {
	request=null;
}

RoutePlannerResults::~RoutePlannerResults(void) {
}

bool RoutePlannerResults::Initialize() {
	this->RemoveAllControls();
	HeaderForm::Initialize(true, true); //enables left and right softkey
	this->request=AppData::GetInstance()->getCurrentRequest();
	/*
	 * get Data from current request from appdata
	 */
	request = AppData::GetInstance()->getCurrentRequest(); // no ownership offcourse

	this->SetSoftkeyText(SOFTKEY_0, "Previous");
	this->SetSoftkeyActionId(SOFTKEY_0, PREVIOUS_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_0,*this);

	this->SetSoftkeyText(SOFTKEY_1, "Next");
	this->SetSoftkeyActionId(SOFTKEY_1, NEXT_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_1,*this);

	/*
	 * Calculate sizes for all controls
	 */
	Rectangle bounds = this->GetClientAreaBounds();
	//int heightBody = int( 1.0 / 6.0 * double(bounds.height));

	/*
	 * Construct a list
	 */
	/*
	list = new GroupedListView();
	list->Construct(Rectangle(0, 0, bounds.width, bounds.height),GROUPED_LIST_VIEW_STYLE_INDEXED, true, true);
	list->SetItemProvider(*this);
	list->AddGroupedListViewItemEventListener(*this);
	AddControl(*list);
	*/

	/*
	 * Construct a ListView
	 */
	list = new ListView();
	list->Construct(Rectangle(0,0,bounds.width,bounds.height),true,false);
	list->SetTextOfEmptyList("empty list");
	list->SetItemProvider(*this);
	list->AddListViewItemEventListener(*this);
	AddControl(*list);

	return true;
}


/*
 * implements IListViewItemEventListener
 */
void RoutePlannerResults::OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status){}

void RoutePlannerResults::OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction){}

void RoutePlannerResults::OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus state)
{
	//TODO make context menu to add to calendar
}

/*
 * implements IListViewItemProvider
 */
Osp::Ui::Controls::ListItemBase*
RoutePlannerResults::CreateItem(int index, int itemWidth)
{
	Rectangle bounds = this->GetClientAreaBounds();
	int itemHeight = bounds.height/9;
	if(bounds.width>bounds.height)
		itemHeight = bounds.width /9;


	/*
	 * Get the trip from the index id
	 */
	Trip* trip;
	request->getTrips()->GetAt(index,trip);
	Connection* firstConnection;
	Connection* lastConnection;
	trip->getConnections()->GetAt(0,firstConnection);
	trip->getConnections()->GetAt(trip->getConnections()->GetCount()-1,lastConnection);

	int amountConnections = trip->getConnections()->GetCount();
	/*
	 * Get trip data
	 */
	String time = Utils::formatTime(firstConnection->getStartConnectionNode()->getDateTime()) + " - " +
				  Utils::formatTime(lastConnection->getEndConnectionNode()->getDateTime());
	String totalTime = Utils::formatDelay(trip->getDuration());
	String numberConnections = "#" + Integer::ToString(amountConnections);

	//create custom item with right size, height is calculated with amount of connections
	CustomItem* item = new CustomItem();
	item->Construct(Osp::Graphics::Dimension(itemWidth,itemHeight), LIST_ANNEX_STYLE_NORMAL); //+itemHeight*amountConnections
	//item->AddElement(Rectangle(0, 0, itemWidth*2/3,itemHeight), TIME_HEADER, L"time");
	item->AddElement(Rectangle(0, 0, itemWidth*0.75,itemHeight), TIME_HEADER, time,0.8*itemHeight,Color::COLOR_BLUE,Color::COLOR_WHITE,Color::COLOR_WHITE);
	item->AddElement(Rectangle(itemWidth*0.75, 0, itemWidth*0.25,itemHeight/2), NUMBER_CONNECTIONS, numberConnections,0.4*itemHeight,Color::COLOR_WHITE,Color::COLOR_BLUE,Color::COLOR_BLUE);
	item->AddElement(Rectangle(itemWidth*0.75, itemHeight/2, itemWidth*0.25, itemHeight/2), TOTAL_TIME, totalTime  ,0.4*itemHeight,Color::COLOR_WHITE,Color::COLOR_BLUE,Color::COLOR_BLUE);
	Connection* conn;
	for(int i=0;i<amountConnections;i++){
		trip->getConnections()->GetAt(i,conn);
		ConnectionNode* startNode 	= conn->getStartConnectionNode();
		ConnectionNode* endNode 	= conn->getEndConnectionNode();
	}

	/*
	 * create context menu
	 */
	ListContextItem* itemContext = new ListContextItem();
	itemContext->Construct();
	itemContext->AddElement(SAVE_CALENDAR_ACTION, "Save to calendar");
	item->SetContextItem(itemContext);

	return item;
}

bool
RoutePlannerResults::DeleteItem(int index, Osp::Ui::Controls::ListItemBase* item, int itemWidth)
{
    delete item; item = null; return true;
}

int
RoutePlannerResults::GetItemCount(void)
{
	return request->getTrips()->GetCount();
}

result RoutePlannerResults::OnInitializing(void) {
	result r = E_SUCCESS;
	r = HeaderForm::OnInitializing(HEADER_ID_ROUTE_PLANNER);
	return r;
}

result RoutePlannerResults::OnTerminating(void) {
	result r = E_SUCCESS;
	return r;
}

/*
 * IAction Event Listener
 */
void RoutePlannerResults::OnActionPerformed(const Osp::Ui::Control& source,int actionId) {
	HeaderForm::OnActionPerformed(source,actionId);
	if(actionId == NEXT_ACTION){
		AppLog("Clicked RoutePlannerResults::search");
		Controller::GetInstance()->retrieveRoutePlannerResults();
	}else if(actionId == PREVIOUS_ACTION){
		AppLog("Clicked RoutePlannerResults::clear");
	}
}


void RoutePlannerResults::RequestRedraw (bool show) const{
	AppLog("RoutePlannerResults::RequestRedraw");
	Form::RequestRedraw(show);
}

/*
 * implement IGroupedListViewItemProvider
 */
/*
GroupItem * 	RoutePlannerResults::CreateGroupItem (int groupIndex, int itemWidth){
	Trip* trip;
	request->getTrips()->GetAt(groupIndex,trip);
	//trip->getDuration();

	Rectangle bounds = this->GetClientAreaBounds();
	int itemHeight = bounds.height/10;
	if(bounds.width>bounds.height)
		itemHeight = bounds.width /10;

	GroupItem* item = new GroupItem();
	item->Construct(Osp::Graphics::Dimension(itemWidth,itemHeight));
	item->SetElement("test1");
	return item;
}

ListItemBase * 	RoutePlannerResults::CreateItem (int groupIndex, int itemIndex, int itemWidth){
	Trip* trip;
	request->getTrips()->GetAt(groupIndex,trip);
	Connection* connection;
	trip->getConnections()->GetAt(itemIndex,connection);


	Rectangle bounds = this->GetClientAreaBounds();
	int itemHeight = bounds.height/12;
	if(bounds.width>bounds.height)
		itemHeight = bounds.width /12;

	SimpleItem* item = new SimpleItem();
	item->Construct(Osp::Graphics::Dimension(itemWidth,itemHeight), LIST_ANNEX_STYLE_NORMAL);
	item->SetElement("test2");
	return item;
}

bool 			RoutePlannerResults::DeleteGroupItem (int groupIndex, GroupItem *pItem, int itemWidth){
	//we dont do this in this context
	return false;
}

bool 			RoutePlannerResults::DeleteItem (int groupIndex, int itemIndex, ListItemBase *pItem, int itemWidth){
	//we dont do this in this context
	return false;
}

int 			RoutePlannerResults::GetGroupCount (void){
	return request->getTrips()->GetCount();
}

int 			RoutePlannerResults::GetItemCount (int groupIndex){
	Trip* trip;
	request->getTrips()->GetAt(groupIndex,trip);
	return trip->getConnections()->GetCount();
}
*/

/*
 * implement IGroupedListViewItemEventListener
 */
/*
void 	RoutePlannerResults::OnGroupedListViewContextItemStateChanged (GroupedListView &listView, int groupIndex, int itemIndex, int elementId, ListContextItemStatus status){}
void 	RoutePlannerResults::OnGroupedListViewItemLongPressed (GroupedListView &listView, int groupIndex, int itemIndex, int elementId, bool &invokeListViewItemCallback){
	AppLog("RoutePlannerResults::OnGroupedListViewItemLongPressed gr:%S id:%S elementId:%S",Integer::ToString(groupIndex).GetPointer(),Integer::ToString(itemIndex).GetPointer(),Integer::ToString(elementId).GetPointer());
}
void 	RoutePlannerResults::OnGroupedListViewItemStateChanged (GroupedListView &listView, int groupIndex, int itemIndex, int elementId, ListItemStatus status){}
void 	RoutePlannerResults::OnGroupedListViewItemSwept (GroupedListView &listView, int groupIndex, int itemIndex, SweepDirection direction){}
*/
