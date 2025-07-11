#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "CellPosition.h" 

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	
	CellPosition starttemp;
	CellPosition endtemp;

	// Read the temporary positions ==> is a part of my attempt to handle if the ladder is invalid, now we won't assign 'startPos'& 'endPos' 
	//with the invalid user inout values
	//at first when we try to add a ladder, say in cells x,y and it's not valid
	//if we try to add another but VALID ladder in x,y it might say it has an object even though it's not 
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	starttemp = pIn->GetCellClicked();

	// read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endtemp = pIn->GetCellClicked();

	GameObject* pObjectStart = pGrid->GetGameObjectAt(startPos);
	GameObject* pObjectEnd = pGrid->GetGameObjectAt(endPos);

	bool isvalid;  //to indicate whether the ladder is valid or not 
	isvalid = true;

	// Validation: Start cell should be below the end cell
	if (starttemp.VCell() <= endtemp.VCell()) {
		
		pGrid->PrintErrorMessage("Error: Ladder start cell must be below the end cell! Click to continue ...");
		isvalid = false;
		return; // return without creating the ladder if invalid
	}
	// validation: start and end cells must be in the same column
	if (starttemp.HCell() != endtemp.HCell()) {
		pGrid->PrintErrorMessage("Error: Ladder start and end cells must be in the same column! Click to continue ...");
		isvalid = false;

		return; 
	}

	// Validation: Start cell should not be in the last row 
	if (starttemp.VCell() == 0 ) {
		isvalid = false;
		return; 
	}

	if (isvalid) //if it's true then we add the ladder, assign the original attributes now
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
	

	// Clear messages
	pOut->ClearStatusBar();
	
}



void AddLadderAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	//for the overlapping part(snake/ladder), i used ai to make me understand the logic more,
	// also alottttt with code the structure in the classes (grid, snake, ladder, addladderaction, addsnakeaction)

	if (pGrid->IsObjectOverlapping(pLadder))
	{
		pGrid->PrintErrorMessage("Error: This ladder overlaps with an existing ladder.");
	}
	else
	{
		// attempting to add the ladder to the grid
		bool added = pGrid->AddObjectToCell(pLadder);
		bool isValidPosition = (startPos.HCell() != -1 && startPos.VCell() != -1 &&
			endPos.HCell() != -1 && endPos.VCell() != -1);

		if (!added && isValidPosition)
		{
			pGrid->PrintErrorMessage("Error: The cell already has an object. Click to continue...");
		}
	}
}
