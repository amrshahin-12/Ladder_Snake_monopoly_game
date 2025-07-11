#pragma once

#include "Action.h"

class RollDiceAction : public Action
{

public:
	RollDiceAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~RollDiceAction();
};

