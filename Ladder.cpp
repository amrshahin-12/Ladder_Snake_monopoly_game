#include "Ladder.h"
#include "Grid.h"
#include "Player.h"
#include <iostream>

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	// Validate ladder positions before initializing
	

	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
	
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	// Step 1: Print message and wait for mouse click
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue...");

	// Step 2: Move player to the end cell
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

Ladder::~Ladder()
{
}
bool Ladder::ValidateLadderPositions(const CellPosition& startCellPos, const CellPosition& endCellPos)
{
	return startCellPos.VCell() < endCellPos.VCell();
}

bool Ladder::IsOverlapping(GameObject* otherObj) const
{
	Ladder* otherLadder = dynamic_cast<Ladder*>(otherObj);
	if (otherLadder)
	{
		int otherStart = otherLadder->position.GetCellNum();
		int otherEnd = otherLadder->endCellPos.GetCellNum();
		int thisStart = this->position.GetCellNum();
		int thisEnd = this->endCellPos.GetCellNum();

		// check overlap cond...
		if ((otherStart >= thisStart && otherStart <= thisEnd) ||
			(thisStart >= otherStart && thisStart <= otherEnd))
		{
			return true;
		}
	}
	return false;
}