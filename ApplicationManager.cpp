#pragma once
#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "AddSquaAction.h"
#include "AddCircleAction.h"
#include "AddTriaAction.h"
#include "AddHexagonAction.h"
#include "SelectAction.h"
#include "FillClrAction.h"
#include "DrawClrAction.h"
#include "MoveAction.h"
#include "DeleteAction.h"
#include "StartRecAction.h"
#include "StopRecAction.h"
#include "PlayRecAction.h"
#include "AddSaveAction.h"
#include "AddLoadAction.h"
#include "To_PlayMode.h"
#include "To_DrawMode.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	isrecording = false;
	isplaying = false;
	FigCount = 0;
	recmgr = NULL;
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;
		case DRAW_SQUARE:
			pAct = new AddSquaAction(this);
			break;
		case DRAW_CIRC:
			pAct = new AddCircleAction(this);
			break;
		case DRAW_TRIANGLE:
			pAct = new AddTriaAction(this);
			break;
		case DRAW_HEXAGON:
			pAct = new AddHexagonAction(this);
			break;
		case DRAW_SELECT_ONE:
			pAct = new SelectAction(this);
			break;
		case DRAW_FILLING_COLOR:
			pAct = new FillClrAction(this);
			break;
		case DRAW_DRAWING_COLOR:
			pAct = new DrawClrAction(this);
			break;
		case DRAW_MOVE:
			pAct = new MoveAction(this);
			break;
		case DRAW_DELETE:
			pAct = new DeleteAction(this);
			break;
		case DRAW_START_REC:
			pAct = new StartRecAction(this);
			break;
		case DRAW_STOP_REC:
			pAct = new StopRecAction(this);
			break;
		case DRAW_PLAY_RECORDING:
			pAct = new PlayRecAction(this);
			break;
		case DRAW_CLEAR_ALL:
			clearall();
			break;
		case DRAW_SAVE_GRAPH:
			pAct = new AddSaveAction(this);
			break;
		case DRAW_LOAD_GRAPH:
			pAct = new AddLoadAction(this);
			break;
		case TO_PLAYMODE:
			pAct = new To_PlayMode(this);
			break;
		case TO_DRAW:
			pAct = new To_DrawMode(this);
			break;

		case EXIT:
			for (int i = 0; i < FigCount; i++)
				delete FigList[i];
			delete pIn;
			delete pOut;  ///create ExitAction here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		if (!isrecording)
		{
			delete pAct;	//You may need to change this line depending to your implementation
			pAct = NULL;
		}
		else
		{
			StartRecAction* test = dynamic_cast<StartRecAction*>(pAct);
			if (test == NULL)
			{
				recmgr->recordaction(pAct);
			}
			else
				recmgr = test;
		}
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->ClickedPointinsideFig(x, y))
		{
			//FigList[i]->PrintInfo(pOut);
			return FigList[i];
		}
	}
	return NULL;
	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.
}

void ApplicationManager::SetSelectedFig(CFigure* p) 
{
	SelectedFig = p;
}
CFigure* ApplicationManager::GetSelectedFig() const
{
	return SelectedFig;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	//////////////////////////////////////////////////////
	// Must clear drawing area before update interface////
	/////////////////////////////////////////////////////
	pOut->ClearDrawArea();

	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
//*******************************************************************************************
void ApplicationManager::OnlyThisFigIsSelected(CFigure* DesiredFig) //unselect all fig except the sent one 
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] != DesiredFig)
			FigList[i]->SetSelected(false);
	}
}
void ApplicationManager::setrecording(bool k)
{
	isrecording = k;
}
void ApplicationManager::setPlaying(bool k)
{
	isplaying = k;
}
//********************************************************************************************
void ApplicationManager::DeletingFigure() {
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
		{
			FigList[i]->SetSelected(false);
			SetSelectedFig(NULL);
			delete FigList[i];
			FigList[i] = NULL;
			FigCount--;
			for (int k = i; k < FigCount; k++) // Shifting FigList elements After deleting Selected Figure
				FigList[k] = FigList[k + 1];
			break;
		}
}
void ApplicationManager::clearall()
{
	if (FigList[0] != NULL)
		FigList[0]->setCount(0);
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
	
	pOut->ClearStatusBar();
	pOut->PrintMessage("Now everything is clean :)");
	


}
bool ApplicationManager::isclear()
{
	if (FigCount == 0)
		return true;
	else
		return false;
}
bool ApplicationManager::IsPlaying()
{
	if (isplaying)
		return true;
	else
		return false;
}
 StartRecAction* ApplicationManager::getrecmgr()
{
	return recmgr;
}
 void ApplicationManager::SaveAll(ofstream& output)
 {
	 for (int i = 0; i < FigCount; i++)
		 FigList[i]->Save(output);// call save func of each figure

 }
// *******************************************************************************************
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}
