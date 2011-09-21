#ifndef _LiveBoardResults_H_
#define _LiveBoardResults_H_

#include <FBase.h>
#include <FUi.h>
#include "HeaderForm.h"
#include "model/LiveBoardRequest.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base;
using namespace Osp::App;

class LiveBoardResults :
	public HeaderForm,
	public IListViewItemEventListener,
	public IListViewItemProvider
{

// Construction
public:
	LiveBoardResults(void);
	virtual ~LiveBoardResults(void);
	bool Initialize(void);

	virtual result 	OnInitializing(void);
	virtual result 	OnTerminating(void);

	void 			RequestRedraw (bool show=true);

	//Action performed Listener
	virtual void 	OnActionPerformed(const Osp::Ui::Control& source, int actionId);

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
	static const int REFRESH_ACTION			= 301;
	static const int BACK_ACTION 			= 302;

	/*
	 * Element id's for custom element
	 */
	static const int TIME 					= 401;
	static const int DELAY 					= 402;
	static const int PLATFORM 				= 403;
	static const int STATION				= 404;

private:
	//DATA
	LiveBoardRequest* 				liveBoardRequest;

	//Compontents
	ListView*				list;
};

#endif	//_LiveBoardResults_H_
