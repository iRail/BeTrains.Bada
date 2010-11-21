
#ifndef _MAINOPTIONLIST_H_
#define _MAINOPTIONLIST_H_

#include <FBase.h>
#include <FUi.h>
#include "BetrainsPrototype.h"


class MainOptionList :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IFocusEventListener,
	public Osp::Ui::IKeyEventListener,
	public Osp::Ui::ITouchEventListener,
	public Osp::Ui::IItemEventListener
{

// Construction
public:
	MainOptionList(void);
	virtual ~MainOptionList(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:
	void addItem(const Osp::Base::String& text,const Osp::Base::String& iconpath,const int id);
// Generated call-back functions
public:
	void OnActionPerformed(const Osp::Ui::Control&, int);
	void OnFocusGained(const Osp::Ui::Control&);
	void OnFocusLost(const Osp::Ui::Control&);
	void OnKeyLongPressed(const Osp::Ui::Control&, Osp::Ui::KeyCode);
	void OnKeyPressed(const Osp::Ui::Control&, Osp::Ui::KeyCode);
	void OnKeyReleased(const Osp::Ui::Control&, Osp::Ui::KeyCode);
	void OnTouchDoublePressed(const Osp::Ui::Control&, const Osp::Graphics::Point&, const Osp::Ui::TouchEventInfo&);
	void OnTouchFocusIn(const Osp::Ui::Control&, const Osp::Graphics::Point&, const Osp::Ui::TouchEventInfo&);
	void OnTouchFocusOut(const Osp::Ui::Control&, const Osp::Graphics::Point&, const Osp::Ui::TouchEventInfo&);
	void OnTouchLongPressed(const Osp::Ui::Control&, const Osp::Graphics::Point&, const Osp::Ui::TouchEventInfo&);
	void OnTouchMoved(const Osp::Ui::Control&, const Osp::Graphics::Point&, const Osp::Ui::TouchEventInfo&);
	void OnTouchPressed(const Osp::Ui::Control&, const Osp::Graphics::Point&, const Osp::Ui::TouchEventInfo&);
	void OnTouchReleased(const Osp::Ui::Control&, const Osp::Graphics::Point&, const Osp::Ui::TouchEventInfo&);
	void OnItemStateChanged(const Osp::Ui::Control&, int, int, Osp::Ui::ItemStatus);
};

#endif
