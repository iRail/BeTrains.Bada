
#ifndef _MAINFORM_H_
#define _MAINFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "FGraphics.h"
#include "FSystem.h"
#include "FMediaImage.h"


class MainForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IItemEventListener
{
private:
	enum ACTIONS {BACK, MENU_ITEM_PLANNER, MENU_ITEM_MAP, MENU_ITEM_CHAT,
				MENU_ITEM_STARRED, MENU_ITEM_TRAFFIC, MENU_ITEM_OPTIONS,PLANNER_SEARCH};
	enum LIST_ITEMS {LIST_STATIONS,LIST_TIMES,LIST_DURATION,LIST_TRAINS};
	void addItem(const Osp::Base::String& text,const Osp::Base::String& iconpath,const int id);
public:
	MainForm(void);
	virtual ~MainForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	void OnItemStateChanged(const Osp::Ui::Control&, int, int, Osp::Ui::ItemStatus);
};

#endif
