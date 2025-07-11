#pragma once

#include "Action.h"
#include "CellPosition.h" 

class AddSnakeAction : public Action
{
private:
  
    CellPosition startPos; // 1- The start position of the snake (top)
    CellPosition endPos;   // 2- The end position of the snake (bottom)

public:
    AddSnakeAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual ~AddSnakeAction();
};
