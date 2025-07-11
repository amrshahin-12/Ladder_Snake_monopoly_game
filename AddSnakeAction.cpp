#include "AddSnakeAction.h"
#include "Input.h"
#include "Output.h"
#include "Snake.h" 
#include "Grid.h" 

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
    
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
    // get a pointer to the input / output interfaces
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    CellPosition starttemp;
    CellPosition endtemp;
    // read the startPos parameter
    pOut->PrintMessage("New Snake: Click on its Start Cell (top)...");
    starttemp = pIn->GetCellClicked();

    // read the endPos parameter
    pOut->PrintMessage("New Snake: Click on its End Cell (bottom)...");
    endtemp = pIn->GetCellClicked();

    bool isvalid;  //to indicate whether the ladder is valid or not 
    isvalid = true;
    // validations
    // start cell should be below the end cell

    if (starttemp.VCell() >= endtemp.VCell()) {
        pGrid->PrintErrorMessage("Error: Snake start cell must be above the end cell! Click to continue ...");
        isvalid = false;

        return; 
    }

    // start and end cells must be in the same column
    if (starttemp.HCell() != endtemp.HCell()) {
        pGrid->PrintErrorMessage("Error: Snake start and end cells must be in the same column! Click to continue ...");
        isvalid = false;

        return; 
    }

    // start cell cannot be in the first row 
    if (starttemp.VCell() == 8 ) {
        pGrid->PrintErrorMessage("Error: Snake start cell cannot be in the first row or a special cell! Click to continue ...");
        isvalid = false;

        return; 
    }

    if (isvalid) //if it's true then we add the snake, assign the original attributes now
    {
        startPos = starttemp;
        endPos = endtemp;
    }
    else  //set it to -1 to indicate it's not valid (i remember we did that in phase1)
    {
        endPos.SetHCell(-1);
        endPos.SetVCell(-1);
        startPos.SetHCell(-1);
        startPos.SetVCell(-1);
    }
    

    // clear messages
    pOut->ClearStatusBar();
}

void AddSnakeAction::Execute()
{
    ReadActionParameters();

    // create a new Snake object with the read parameters
    Snake* pSnake = new Snake(startPos, endPos);

    Grid* pGrid = pManager->GetGrid(); // get the Grid pointer from the Application Manager

    if (pGrid->IsObjectOverlapping(pSnake))
    {
        pGrid->PrintErrorMessage("Error: This ladder overlaps with an existing ladder.");
    }
    else
    {
        // attempting to add the ladder to the grid
        bool added = pGrid->AddObjectToCell(pSnake);
        bool isValidPosition = (startPos.HCell() != -1 && startPos.VCell() != -1 &&
            endPos.HCell() != -1 && endPos.VCell() != -1);

        if (!added && isValidPosition)
        {
            pGrid->PrintErrorMessage("Error: The cell already has an object. Click to continue...");
        }
    }
}
