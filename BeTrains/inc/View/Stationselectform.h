
#ifndef _STATIONSELECTFORM_H_
#define _STATIONSELECTFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "Model/Station.h"

class StationSelectForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IScrollPanelEventListener,
	public Osp::Ui::IItemEventListener,
	public Osp::Ui::ITextEventListener
{
private:
	static const int ID_BUTTON_EDITFIELD_DONE=101;
	static const int ID_BUTTON_EDITFIELD_CLOSE = 102;
	Osp::Ui::Controls::ScrollPanel* vpScrollPanel; //owner
	Osp::Ui::Controls::EditField* vpEditFiled; //owner
	Osp::Ui::Controls::List* stationSuggestionList; //owner
	Osp::Base::Collection::ArrayListT<Station *> * stations;
	Osp::Base::Collection::ArrayListT<Station *> suggestionStations;
	Station* selectedStation;
public:
	StationSelectForm(Osp::Base::Collection::ArrayListT<Station *> * stations,Station* &selectedStation);
	virtual ~StationSelectForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	void OnOverlayControlCreated(const Osp::Ui::Control& source);
	void OnOverlayControlOpened(const Osp::Ui::Control& source);
	void OnOverlayControlClosed(const Osp::Ui::Control& source);
	void OnOtherControlSelected(const Osp::Ui::Control& source);
	void setKeyboard();
	void  OnTextValueChangeCanceled (const Osp::Ui::Control &source);
	void  OnTextValueChanged (const Osp::Ui::Control &source);
	void OnItemStateChanged(const Osp::Ui::Control&, int, int, Osp::Ui::ItemStatus);
};

#endif
