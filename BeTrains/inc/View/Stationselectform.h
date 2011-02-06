
#ifndef _STATIONSELECTFORM_H_
#define _STATIONSELECTFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "Model/Station.h"

class StationSelectForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IScrollPanelEventListener,
	public Osp::Ui::ITextEventListener
{
private:
	static const int ID_BUTTON_EDITFIELD_DONE=101;
	static const int ID_BUTTON_EDITFIELD_CLOSE = 102;
	Osp::Ui::Controls::ScrollPanel* vpScrollPanel;
	Osp::Ui::Controls::EditField* vpEditFiled;
	Osp::Ui::Controls::List* stationSuggestionList;
	Osp::Base::Collection::ArrayListT<Station *> * stations;
public:
	StationSelectForm(Osp::Base::Collection::ArrayListT<Station *> * stations);
	virtual ~StationSelectForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	virtual void OnOverlayControlCreated(const Osp::Ui::Control& source);
	virtual void OnOverlayControlOpened(const Osp::Ui::Control& source);
	virtual void OnOverlayControlClosed(const Osp::Ui::Control& source);
	virtual void OnOtherControlSelected(const Osp::Ui::Control& source);
	void setKeyboard();
	virtual void  OnTextValueChangeCanceled (const Osp::Ui::Control &source);
	virtual void  OnTextValueChanged (const Osp::Ui::Control &source);
};

#endif
