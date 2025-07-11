#include "Input.h"

#include "Output.h"
/*me*/
#include <stdexcept>  // For std::invalid_argument and std::out_of_range
#include <string>      // For std::string
#include <iostream>    // For std::getline
//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(window* pW)
{
	pWind = pW; // point to the passed window
}

////////////////////////////////////////////////////////////////////////////////////////// 

void Input::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y); // Note: x and y of WaitMouseClick are sent by reference
}

////////////////////////////////////////////////////////////////////////////////////////// 

string Input::GetSrting(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if (Key == 13)	// ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

////////////////////////////////////////////////////////////////////////////////////////// 

//fixed the errors that was in phase1
//ai helped me a little here
int Input::GetInteger(Output* pO) const
{
	int x = 0;
	bool validInput = false;

	// the user will stuck in the loop untill a valid integer is the input
	while (!validInput) {
		// get string input
		string input = GetSrting(pO);  

		// Check 
		if (input == "") {
			pO->PrintMessage("Card addition cancelled.");
			return -1;  // Return -1 to indicate cancellation
		}

		try {
			// try converting the string to integer
			x = std::stoi(input);
			validInput = true;  //if successful, exit loop
		}
		catch (const std::invalid_argument& e) {
			// if the input is not a valid integer, print a message and prompt again
			pO->PrintMessage("Invalid input. Please enter a valid integer, enter again:");
		}
		//gpt
		catch (const std::out_of_range& e) {
			// Handle cases where the input number is too large or too small
			pO->PrintMessage("Input out of range. Please enter a valid integer. enter again:");
		}
	}

	return x;  // Return the valid integer input
}

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType Input::GetUserAction() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	//  ============ GUI in the Design mode ============
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// [1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_ADD_LADDER: return ADD_LADDER;
			case ITM_ADD_SNAKE: return ADD_SNAKE;
			case ITM_ADD_CARD: return ADD_CARD;
			case ITM_EXIT: return EXIT;    //exit design mode
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;
			case ITM_Copy_Card: return Copy_Card;
			case ITM_Cut_Card: return Cut_Card;
			case ITM_Edit_Card: return Edit_Card;
			case ITM_Paste_Card: return Paste_Card;
			case ITM_Delete_Game_Object: return  Delete_Game_Object;
			case ITM_Save_Grid: return Save_Grid;
			case ITM_Open_Grid:  return Open_Grid;
				///TODO: Add cases for the other items of Design Mode




			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}

	// ============ GUI in the Play mode ============
	else
	{
		if (UI.InterfaceMode == MODE_PLAY) {
			if (y >= 0 && y < UI.ToolBarHeight) {
				int ClickedItemOrder = (x / UI.MenuItemWidth);
				switch (ClickedItemOrder) {
				case ITM_ROLL_DICE: return ROLL_DICE;
				case	ITM_SWITCH_TO_DESIGN_MODE: return TO_DESIGN_MODE;
				case	ITM_Exit_Play_Mode: return EXIT_Play_Mode;     //exit play mode
				case	ITM_Input_Dice_Value: return Input_Dice_Value;
				case   ITM_New_Game: return New_Game;

				default: return EMPTY;

				}
			}
			if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
			{
				return GRID_AREA;
			}
			return STATUS;




			///TODO:
			// perform checks similar to Design mode checks above for the Play Mode
			// and return the corresponding ActionType

				// just for now ==> This should be updated




		}

	}
}
//////////////////////////////////////////////////////////////////////////////////////////

CellPosition Input::GetCellClicked() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	// Get the coordinates of the user click

	CellPosition cellPos;

	if (UI.InterfaceMode == MODE_DESIGN)
	{
		if (y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
		{
			cellPos.SetHCell(x / UI.CellWidth);
			cellPos.SetVCell((y / UI.CellHeight) - 1);




			///TODO: SetHCell and SetVCell of the object cellPost appropriately
			//using the coordinates x, y and the appropriate variables of the UI_Info Object (UI)



		}
	}

	return cellPos;
}

////////////////////////////////////////////////////////////////////////////////////////// 
