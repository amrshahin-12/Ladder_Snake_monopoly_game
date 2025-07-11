#pragma once

#include "Card.h"


class CardTwo : public Card
{
   
    int walletAmount; 

public:
    CardTwo(const CellPosition& pos); // Constructor that takes the card position

    virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardTwo which is: walletAmount

    virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwo by incrementing the player's wallet

    virtual ~CardTwo(); 
    virtual bool IsCardDetailsOk();
};
