/*
 * SelectStationForm.h
 *
 *  Created on: 10 sep. 2011
 *      Author: Jan
 */

#ifndef SelectStationForm_H_
#define SelectStationForm_H_

#include <FBase.h>
#include <FUi.h>
#include "model/Station.h"
using namespace Osp::Ui;

class SelectStationForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::Controls::IListViewItemEventListener,
	public Osp::Ui::Controls::IListViewItemProvider,
	//public Osp::Ui::IScrollPanelEventListener,
	//public Osp::Ui::IActionEventListener,
	public Osp::Ui::ITextEventListener
	//public Osp::Ui::IOrientationEventListener
{

// Construction
public:
	SelectStationForm(void);
	virtual ~SelectStationForm(void);
	bool Initialize();
private:
	int settings;
// Implementation
protected:

public:
	virtual result OnInitializing();
	virtual result OnTerminating(void);
	//void setKeypad(); // must happen extern, and not on initialising

	//implement IScrollPanelEventListener
	/*
	void OnOverlayControlCreated(const Osp::Ui::Control& source);
	void OnOverlayControlOpened(const Osp::Ui::Control& source);
	void OnOverlayControlClosed(const Osp::Ui::Control& source);
	void OnOtherControlSelected(const Osp::Ui::Control& source);
	*/

	//implement IActionEventListener
	//void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	// implement ITextEventListener
	void  OnTextValueChangeCanceled (const Osp::Ui::Control &source);
	void  OnTextValueChanged (const Osp::Ui::Control &source);

	//implements IListViewItemEventListener
	virtual void OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus state);
	virtual void OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction);

	//implements IListViewItemProvider
	virtual Osp::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
	virtual bool DeleteItem(int index, Osp::Ui::Controls::ListItemBase* pItem, int itemWidth);
	virtual int GetItemCount(void);


	static const int ID_FORMAT_STRING = 100;
	static const int ID_FORMAT_BITMAP = 101;
	static const int ID_FORMAT_CUSTOM = 102;
	static const int ID_CONTEXT_ITEM_1 = 103;
	static const int ID_CONTEXT_ITEM_2 = 104;

	//implement IOrientationEventListener
	//void OnOrientationChanged(const Control& source, OrientationStatus orientationStatus);
private:
	static const int CANCEL_ACTION					= 301;
	static const int CLEAR_ACTION					= 302;
	Osp::Ui::Controls::ScrollPanel* 				scrollPanel; //owner
	Osp::Ui::Controls::EditField* 					editField; //owner
	Osp::Ui::Controls::ListView * 					stationSuggestionList; //owner
	Osp::Base::Collection::ArrayListT<Station *> 	suggestionStations;
	Osp::Base::Collection::ArrayListT<Station *>*	stations; //ownership only over the pointer
};

#endif /* SelectStationForm_H_ */
