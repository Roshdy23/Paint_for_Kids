#include "To_PlayMode.h"
#include "AddSaveAction.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include "ApplicationManager.h"

To_PlayMode::To_PlayMode(ApplicationManager* pApp):Action(pApp)
{
}

void To_PlayMode::ReadActionParameters()
{
}

void To_PlayMode::Execute()
{

	AddSaveAction s(pManager);
	s.Execute2();
	Output* pOut = pManager->GetOutput();
	pOut->ClearDrawArea();
	pOut->ClearToolBar();

	pOut->CreatePlayToolBar();
	PlaySound(TEXT("Voice-Bouns\\Play.wav"), NULL, SND_FILENAME | SND_SYNC);

	pOut->PrintMessage("Now you are in the play mode , let's have some fun ! ");
}
