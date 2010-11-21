
#ifndef _TRAINSRESULTSFORM_H_
#define _TRAINSRESULTSFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "ItemFactory.h"
#include "Connection.h"

using namespace Osp::Base::Collection;

class TrainsResultsForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IFocusEventListener,
	public Osp::Ui::IKeyEventListener,
	public Osp::Ui::ITouchEventListener,
	public Osp::Ui::ICustomItemEventListener,
	public Osp::Ui::ISlidableListEventListener
{

// Construction
private:
		ItemFactory* pItemFactory;
public:
	TrainsResultsForm(void);
	virtual ~TrainsResultsForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:

	void setConnections(ArrayListT<Connection> &connections);
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
	void OnItemStateChanged(const Osp::Ui::Control&, int, int, int, Osp::Ui::ItemStatus);
	void OnItemStateChanged(const Osp::Ui::Control&, int, int, Osp::Ui::ItemStatus);
	void OnListPropertyRequested(const Osp::Ui::Control&);
	void OnLoadToBottomRequested(const Osp::Ui::Control&, int, int);
	void OnLoadToTopRequested(const Osp::Ui::Control&, int, int);
	void OnUnloadItemRequested(const Osp::Ui::Control&, int);
};

#endif
