
#ifndef _SEARCHSTATIONNAME_H_
#define _SEARCHSTATIONNAME_H_

#include <FBase.h>
#include <FUi.h>
#include <FUiITextEventListener.h>


class SearchStationName :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IScrollPanelEventListener,
	public Osp::Ui::ITextEventListener
{

// Construction
public:
	SearchStationName(void);
	virtual ~SearchStationName(void);
	bool Initialize();



// Implementation
protected:


// Generated call-back functions
public:
	virtual result OnInitializing(void);
	 virtual result OnTerminating(void);
	 virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	//1
	 virtual void OnOverlayControlCreated(const Osp::Ui::Control& source);
	 virtual void OnOverlayControlOpened(const Osp::Ui::Control& source);
	 virtual void OnOverlayControlClosed(const Osp::Ui::Control& source);
	 virtual void OnOtherControlSelected(const Osp::Ui::Control& source);
	 virtual void OnTextValueChanged(const Osp::Ui::Control& source);
     virtual void OnTextValueChangeCanceled(const Osp::Ui::Control& source);

private:
	static const int ID_BUTTON_EDITFIELD_DONE = 101;
	static const int ID_BUTTON_EDITFIELD_CLOSE = 102;

	Osp::Ui::Controls::ScrollPanel* pScrollPanel;
	Osp::Ui::Controls::EditField* pEditField;
	Osp::Ui::Controls::List* pResultList;
};

#endif
