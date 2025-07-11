#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum), isTurnCanceled(false)
{
	this->pCell = pCell;
	this->turnCount = 0;

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}
//!!!!!!!!!!!!!!!
void Player::SetTurnCount(int x) {
	turnCount = x;
}
// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	if (pCell) {
		pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
	}
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	
		pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
		
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)

}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	
	// 3- Set the justRolledDiceNum with the passed diceNumber

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"

	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position

	// 6- Apply() the game object of the reached cell (if any)

	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	//===================================================execution================================================
	// Step 1: Increment the turn count

	if (isTurnCanceled) {
		//if canceled set the dice roll to zero
		diceNumber = 0;
		// notice for the user
		pGrid->PrintErrorMessage("your next turn is canceled by a Card 8. Click to continue....");
		// reset
		isTurnCanceled = false;
		turnCount++;
		return;  //exit without moving
	}

	if (turnCount == 2) {
		turnCount = 0;   //resets the counter
		//step 2: check if it's a recharging turn
		if (turnCount == 0) { //cause it happens on the 3rd turn

			int AddedNum = diceNumber * 10;  // 10 * roll
			wallet += AddedNum;

			// make message for the user
			pGrid->PrintErrorMessage("Recharge Turn! " + to_string(AddedNum) +
				" coins added to your wallet. Press any key to continue.");
			return;  //the player won't move cause we exited the function
		}
	}
	turnCount++;

	
	
	
	// Step 3: Set the last rolled dice number
	SetLastDiceRoll(diceNumber);

	// Step 4: Calculate the new position
	CellPosition newPos = pCell->GetCellPosition();
	newPos.AddCellNum(diceNumber);

			// from ai: check if the new position is valid, i used IsValidCell() from cellposition class
			if (!newPos.IsValidCell())
			{
				pGrid->PrintErrorMessage("Move out of bounds, it will stay in the same cell. Click to continue.....");
				return;
			}
			
			//see the money in the wallet 
			if (GetWallet() < 1) {
				return;
			}
	// Step 5: Update the player's cell pointer
	pGrid->UpdatePlayerCell(this, newPos);

	// Step 6: Apply the game object at the new cell, if any
	GameObject* pObject = pGrid->GetGameObjectAt(newPos);
	if (pObject)
	{
		pObject->Apply(pGrid, this);
	}
	// Step 7: Check if the player reached the end cell, if yes, set the end game flag
	if (newPos == pGrid->GetEndPosition())  // I made GetEndPosition() which gives the end cell position
	{
		pGrid->SetEndGame(true);
	}
}

int Player::GetBetweenCellsNum(int target) {
	CellPosition newPos = pCell->GetCellPosition();
	int x =target - newPos.GetCellNum();
	return x;

}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}
void Player::DecrementWallet(int amount)
{
	// if it can't be -ve ????  (check)
	wallet -= amount;
	if (wallet < 0) {
		wallet = 0; // so it wont be -ve
	}
}
// Increment the wallet 
void Player::IncrementWallet(int amount)
{
	wallet += amount; // Add the specified amount to the wallet
}
void Player::SetLastDiceRoll(int roll)
{
	lastDiceRoll = roll;
}

int Player::GetLastDiceRoll() const
{
	return lastDiceRoll;
}
void Player::DecTurnCount() {
	turnCount--;
}
void Player::SetTurnCanceled(bool c) {
	isTurnCanceled = c;

}
bool Player::GetTurnCanceled() const {
	return isTurnCanceled; }