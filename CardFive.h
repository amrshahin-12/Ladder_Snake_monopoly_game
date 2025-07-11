#pragma once

#include "Card.h"



class CardFive : public Card
{
public:
    CardFive(const CellPosition& pos); 

    virtual void Apply(Grid* pGrid, Player* pPlayer); // Moves the player forward by rolled steps

    virtual ~CardFive(); 
   virtual bool IsCardDetailsOk();

};
