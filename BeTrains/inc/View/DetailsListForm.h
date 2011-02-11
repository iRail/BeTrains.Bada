
#ifndef _DETAILSLISTFORM_H_
#define _DETAILSLISTFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "Model/Trip.h"
#include "Model/ConnectionNode.h"

class DetailsListForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener
{

// Construction
public:
	DetailsListForm(void);
	void update(Trip *trip);
	virtual ~DetailsListForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
private:
	//data members
	Trip* trip; //no ownership
	enum Actions{ACTION_BACK};
	enum ListPlace{LIST_NAME,LIST_PLATFORM,LIST_TIME,LIST_IN_OUT};
	Osp::Ui::Controls::CustomListItemFormat* format;
	Osp::Ui::Controls::CustomList* connectionList;
	Osp::Graphics::Font* defaultFont;
	//methods
	void createItem(ConnectionNode* node,bool in);
	String formatTime(DateTime *dateTime);
	void OnActionPerformed(const Osp::Ui::Control &source, int actionId);
};

#endif
