#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "Snake.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}
//explanation from me: players turns
void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

void Grid::SetCurrentPlayer(int x)
{
	currPlayerNumber = x;
}


// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}
//Player* Grid::GetSpecificPlayer() const
//{
//	//return PlayerList[currPlayerNumber];
//}


Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			GameObject* pObject = CellList[i][j]->GetGameObject(); // to Get the object at this cell
			if (Ladder* pLadder = dynamic_cast<Ladder*>(pObject)) // to Check if the object is a ladder or not
			{
				return pLadder; // Return the ladder if it is found
			}

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}
Snake* Grid::GetNextSnake(const CellPosition& position) 
{
	int startH = position.HCell(); // Start searching from the current horizontal cell
	for (int i = position.VCell(); i >= 0; i--) // Search from current vertical cell upwards
	{
		for (int j = startH; j < NumHorizontalCells; j++) // Search from the current horizontal cell to the right
		{
			// Access the GameObject in the current cell
			GameObject* pObject = CellList[i][j]->GetGameObject();

			// Check if the GameObject is a Snake
			Snake* pSnake = dynamic_cast<Snake*>(pObject);
			if (pSnake)
			{
				return pSnake; // Return the first snake found
			}
		}
		startH = 0; // Reset horizontal search to the first column for the next row above
	}
	return nullptr; // No snakes found ahead
}



// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}

GameObject* Grid::GetGameObjectAt(const CellPosition& pos)
{
	if (pos.IsValidCell()) // To see if it's valid
	{
		// Access the cell at the specified position
		Cell* pCell = CellList[pos.VCell()][pos.HCell()];
		if (pCell)
		{
			// Return the game object stored in that cell (can be NULL if no object is there)
			return pCell->GetGameObject();
		}
	}
	return nullptr; // nullptr if the position is invalid 
}

CellPosition Grid::GetEndPosition() const
{
	
	return CellPosition(0, NumHorizontalCells - 1); 
}
	//for the overlapping part(snake/ladder), i used ai to make me understand the logic more,
	// also alot with code structure in the classes (grid, snake, ladder, addladderaction, addsnakeaction)

bool Grid::IsObjectOverlapping(GameObject* newObject) const
{
	CellPosition newStartPos = newObject->GetPosition(); // Position of the new object

	// handle Ladder Overlap Check
	if (Ladder* newLadder = dynamic_cast<Ladder*>(newObject))
	{
		for (int row = 0; row < NumVerticalCells; ++row)
		{
			for (int col = 0; col < NumHorizontalCells; ++col)
			{
				Ladder* existingLadder = CellList[row][col]->HasLadder();

				if (existingLadder && existingLadder->GetPosition().HCell() == newStartPos.HCell())
				{
					if (existingLadder->IsOverlapping(newLadder))
					{
						return true;
					}
				}
			}
		}
	}
	// handle Snake Overlap Check
	else if (Snake* newSnake = dynamic_cast<Snake*>(newObject))
	{
		for (int row = 0; row < NumVerticalCells; ++row)
		{
			for (int col = 0; col < NumHorizontalCells; ++col)
			{
				Snake* existingSnake = CellList[row][col]->HasSnake();

				if (existingSnake && existingSnake->GetPosition().HCell() == newStartPos.HCell())
				{
					if (existingSnake->IsOverlapping(newSnake))
					{
						return true;
					}
				}
			}
		}
	}

	return false; //if there's no overlap
}




