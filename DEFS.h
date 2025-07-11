#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode

	ADD_LADDER,		// Add Ladder Action
	ADD_SNAKE,		// Add Snake Action	
	ADD_CARD,		// Add Card Action	
	EXIT,			// Exit Application
	TO_PLAY_MODE,	// Go to Play Mode
	Copy_Card,
	Paste_Card,
	Edit_Card,
	Delete_Game_Object,
	Save_Grid,
	Open_Grid,
	Cut_Card,
	///TODO: Add more action types of Design Mode

	//  [2] Actions of Play Mode

	ROLL_DICE,		// Roll Dice Action
	TO_DESIGN_MODE,	// Go to Design Mode
	EXIT_Play_Mode,
	Input_Dice_Value,
	New_Game,
	///TODO: Add more action types of Play Mode

	//  [3] Others

	EMPTY,				// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,			// Inside Grid Area
	STATUS, 				// Inside StatusBar Area
};

#endif