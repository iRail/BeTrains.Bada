#ifndef _RoutePlannerResults_H_
#define _RoutePlannerResults_H_

#include <FBase.h>
#include <FUi.h>
#include "HeaderForm.h"
#include "model/Request.h"
#include "model/Station.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base;
using namespace Osp::App;


class RoutePlannerResults :
	public HeaderForm,
	//public IGroupedListViewItemProvider,
	//public IGroupedListViewItemEventListener
	public IListViewItemEventListener,
	public IListViewItemProvider
{

// Construction
public:
	RoutePlannerResults(void);
	virtual ~RoutePlannerResults(void);
	bool Initialize(void);

	virtual result 	OnInitializing(void);
	virtual result 	OnTerminating(void);

	void 			RequestRedraw (bool show=true) const;

	//Action performed Listener
	virtual void 	OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	//IGroupedListViewItemProvider
	/*
	virtual GroupItem * 	CreateGroupItem (int groupIndex, int itemWidth);
	virtual ListItemBase * 	CreateItem (int groupIndex, int itemIndex, int itemWidth);
	virtual bool 			DeleteGroupItem (int groupIndex, GroupItem *pItem, int itemWidth);
	virtual bool 			DeleteItem (int groupIndex, int itemIndex, ListItemBase *pItem, int itemWidth);
	virtual int 			GetGroupCount (void);
	virtual int 			GetItemCount (int groupIndex);
	*/

	//IGroupedListViewItemEventListener
	/*
	virtual void 	OnGroupedListViewContextItemStateChanged (GroupedListView &listView, int groupIndex, int itemIndex, int elementId, ListContextItemStatus status);
	virtual void 	OnGroupedListViewItemLongPressed (GroupedListView &listView, int groupIndex, int itemIndex, int elementId, bool &invokeListViewItemCallback);
	virtual void 	OnGroupedListViewItemStateChanged (GroupedListView &listView, int groupIndex, int itemIndex, int elementId, ListItemStatus status);
	virtual void 	OnGroupedListViewItemSwept (GroupedListView &listView, int groupIndex, int itemIndex, SweepDirection direction);
	*/


	//implements IListViewItemEventListener
	virtual void OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus state);
	virtual void OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction);

	//implements IListViewItemProvider
	virtual Osp::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
	virtual bool DeleteItem(int index, Osp::Ui::Controls::ListItemBase* pItem, int itemWidth);
	virtual int GetItemCount(void);

	/*
	 * action id's
	 */
	static const int NEXT_ACTION = 301;
	static const int PREVIOUS_ACTION = 302;
	static const int SAVE_CALENDAR_ACTION = 303;

	/*
	 * Element id's for custom element
	 */
	static const int TIME_HEADER 			= 401;
	static const int NUMBER_CONNECTIONS 	= 402;
	static const int TOTAL_TIME 			= 403;
	static const int TIME_1					= 404;
	static const int TIME_2					= 405;
	static const int STATION_1				= 406;
	static const int STATION_2				= 407;
	static const int PLATFORM_1				= 408;
	static const int PLATFORM_2				= 409;

private:
	//DATA
	Request* 				request;

	//Compontents
	//GroupedListView*		list;
	ListView*				list;
};

#endif	//_RoutePlannerResults_H_
