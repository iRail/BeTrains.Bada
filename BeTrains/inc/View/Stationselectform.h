
#ifndef _STATIONSELECTFORM_H_
#define _STATIONSELECTFORM_H_

#include <FBase.h>
#include <FUi.h>

using namespace Osp::Ui::Controls;

class Stationselectform :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::ITextEventListener
{
private:
	EditField *editField;
	List *list;
	ScrollPanel* scrollPanel;
public:
	Stationselectform(void);
	virtual ~Stationselectform(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	void OnTextValueChangeCanceled (const Osp::Ui::Control &source);
	void OnTextValueChanged (const Osp::Ui::Control &source);
};

#endif
