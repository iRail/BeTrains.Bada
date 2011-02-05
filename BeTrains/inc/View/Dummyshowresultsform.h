
#ifndef _DUMMYSHOWRESULTSFORM_H_
#define _DUMMYSHOWRESULTSFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "ItemFactory.h"


class Dummyshowresultsform :
	public Osp::Ui::Controls::Form
{

// Construction
public:
	Dummyshowresultsform(void);
	void Fill();
	virtual ~Dummyshowresultsform(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
private:
	ItemFactory* pItemFactory;
// Implementation
protected:

// Generated call-back functions
public:

};

#endif
