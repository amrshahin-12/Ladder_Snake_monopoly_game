#pragma once
#include "Card.h"
//#include "Grid.h"
#include "Player.h"

class CardFour : public Card
{
public:
    CardFour(const CellPosition& pos);
    virtual void Apply(Grid* pGrid, Player* pPlayer); 
    virtual ~CardFour(); 
    virtual bool IsCardDetailsOk();

};
