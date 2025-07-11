#include "NewGameAction.h"
#include "Grid.h"
#include "Player.h"
#include "CellPosition.h"
#include "GameObject.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{

}



void NewGameAction::ReadActionParameters()
{
  
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    pOut->PrintMessage("Starting a new game...");

    // clear the bar
    pOut->ClearStatusBar();
}

void NewGameAction::Execute()
{
    
    ReadActionParameters();

 
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();

    // reset all players 
    for (int i = 0; i < MaxPlayerCount; i++) {
        pGrid->SetCurrentPlayer(i);
        Player* pPlayer = pGrid->GetCurrentPlayer();

        // reset player position to the start position
        CellPosition startPos(NumVerticalCells - 1, 0);
        pGrid->UpdatePlayerCell(pPlayer, startPos);

        // reset wallet
        pPlayer->SetWallet(100);

        // reset any other attribute
        pPlayer->SetTurnCount(0);
    }

    // reset current player to player 0
    pGrid->SetCurrentPlayer(0);

    // print message to tell the user he started new game
    pOut->PrintMessage("The game has been reset. Player 0's turn!");
    //in case the game had ended 
    pGrid->SetEndGame(false);

    
}
NewGameAction::~NewGameAction()
{
}