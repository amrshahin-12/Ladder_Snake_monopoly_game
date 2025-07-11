#pragma once
#include "Action.h" 
#include "Grid.h"

class NewGameAction : public Action
{

public:
  
    NewGameAction(ApplicationManager* pApp);

    virtual ~NewGameAction();
    
    virtual void ReadActionParameters();

    virtual void Execute();
};
