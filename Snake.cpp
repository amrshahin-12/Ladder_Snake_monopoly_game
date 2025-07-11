#include "Snake.h"
#include <stdexcept>

Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
    this->endCellPos = endCellPos;

    // TODO: Add necessary validation, such as ensuring that the start cell is after the end cell, and checking for other rules.
}

void Snake::Draw(Output* pOut) const
{
    pOut->DrawSnake(position, endCellPos); // Draw the snake from its start (head) to its end (tail)
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{
    Output* pOut = pGrid->GetOutput(); // Get Output object to interact with UI

    // 1- Print a message "You have reached a snake. Click to continue ..." and wait for the mouse click
    pOut->PrintMessage("You have reached a snake. Click to continue ...");

    // 2- Apply the snake's effect by moving the player to the endCellPos (tail position)
    //    You may need to use pGrid->UpdatePlayerCell to move the player
    pGrid->UpdatePlayerCell(pPlayer, endCellPos);

    // Clear the status bar after the action is completed
    pOut->ClearStatusBar(); // Clears the status bar
}

CellPosition Snake::GetEndPosition() const
{
    return endCellPos; // Return the snake's tail position
}

Snake::~Snake()
{
}


bool Snake::IsOverlapping(GameObject* pNew) const
{
    Snake* otherSnake = dynamic_cast<Snake*>(pNew); // Check if pNew is a Snake
    if (otherSnake)
    {
        int thisStart = this->position.GetCellNum(); // start cell of current Snake
        int thisEnd = this->endCellPos.GetCellNum(); // end cell of current Snake
        int otherStart = otherSnake->position.GetCellNum(); // start cell of new Snake
        int otherEnd = otherSnake->endCellPos.GetCellNum(); // end cell of new Snake

        // check if the snakes' ranges overlap
        if ((otherStart >= thisEnd && otherEnd <= thisStart) || // full overlap
            (thisStart >= otherEnd && thisEnd <= otherStart))   // full overlap reverse
        {
            return true;
        }
    }
    return false; //if there's no overlap
}