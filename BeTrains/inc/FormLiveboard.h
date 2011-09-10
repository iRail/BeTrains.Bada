#ifndef _FormLiveboard_H_
#define _FormLiveboard_H_

#include <FBase.h>
#include <FUi.h>
#include "HeaderForm.h"

class FormLiveboard :
	public HeaderForm,
	public Osp::Ui::IActionEventListener
{

// Construction
public:
	FormLiveboard(void);
	virtual ~FormLiveboard(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	/*
	 * Action id's
	 */

	static const int SEARCH_ACTION = 101;

	static const int HEADER_ID_LIVEBOARD = 201;
	static const int HEADER_ID_STATIONS = 202;

};

#endif	//_FormLiveboard_H_
