/*
 * WaitingPopup.h
 *
 *  Created on: 19-sep.-2011
 *  Author: B123
 */

#include <FBase.h>
#include <FUi.h>

#ifndef WAITINGPOPUP_H_
#define WAITINGPOPUP_H_

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base;
using namespace Osp::App;

class WaitingPopup:
	public Osp::Ui::IActionEventListener
{
public:
	WaitingPopup();
	virtual ~WaitingPopup();
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	void Construct(int screenWidth, int screenHeight);
	void showPopup(int screenWidth, int screenHeight);
	void hidePopup();

private:
	static const int 					CANCEL_ACTION 	= 300;

	Osp::Ui::Controls::Button* 			cancelButton;
	Osp::Ui::Controls::Popup*			popup;
	Osp::Ui::Controls::MessageBox* 		msgbox;
	Osp::Ui::Controls::Button* 			button;
};

#endif /* WAITINGPOPUP_H_ */
