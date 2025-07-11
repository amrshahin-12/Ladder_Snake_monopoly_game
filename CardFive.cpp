#include "CardFive.h"
#include "Player.h"
#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"

CardFive::CardFive(const CellPosition& pos) : Card(pos)
{
    cardNumber = 5; // Set the card number to 5
}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
    
    // Step 1 Call the base class Apply to print the card number message
    Card::Apply(pGrid, pPlayer);

    // Step 2 Get the last rolled dice value
    int roll = pPlayer->GetLastDiceRoll();

    // Step 3 Move the player forward by the rolled value
    pPlayer->Move(pGrid, roll); 
    pPlayer->DecTurnCount();

    // i think "move" will implement any object
}

CardFive::~CardFive()
{
    // No special cleanup needed
}
bool CardFive::IsCardDetailsOk() {
    return true; 
}
