//---------------------------------------------------------------------------

#include <vcl.h>
#include <sstream>
#pragma hdrstop

#include <vector>
#include <cstring>
#include "MainForm.h"
#include "sqlite3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;

using namespace std;

sqlite3* TForm1::getDataBaseHandle()
{
	sqlite3* dbHandle = NULL;
	UnicodeString dbFileName = HistoryFileOpenDialog->FileName;
	if (dbFileName.IsEmpty()) {
		throw Exception("No history file selected");
	}
	const wchar_t * dbFileName_c = dbFileName.c_str();
	sqlite3_open16(dbFileName_c, &dbHandle);

	if (dbHandle == NULL) {
		throw Exception("Some errors occurred while open DataBase");
	}

	return dbHandle;
}



//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadHistoryButtonClick(TObject *Sender)
{
	VirtualStringTree -> NodeDataSize = sizeof(NodeStruct);
	VirtualStringTree -> Clear();

	sqlite3* dbHandle = getDataBaseHandle();

	sqlite3_stmt *pStatement;

	int queryExecResult = sqlite3_prepare_v2(dbHandle, "select * from segments", -1, &pStatement, NULL);

	if (queryExecResult != SQLITE_OK)
	{
		const char *errmsg = sqlite3_errmsg(dbHandle);
		throw Exception(strcat("Some error occurred while execute query: ", errmsg));
	}

	while (sqlite3_step(pStatement) != SQLITE_DONE)
	{
	   int index;
	   int columnCount = sqlite3_column_count(pStatement);
	   PVirtualNode entryNode = VirtualStringTree -> AddChild(VirtualStringTree -> RootNode);
	   NodeStruct *nodeData = (NodeStruct*)VirtualStringTree -> GetNodeData(entryNode);
	   for (index = 0; index < columnCount; index++)
	   {
		   nodeData -> Id = sqlite3_column_int(pStatement, 0) ;
		   nodeData -> Path  = (wchar_t*)sqlite3_column_text16(pStatement, 1);
	   }
	}

	sqlite3_finalize(pStatement);
	sqlite3_close(dbHandle);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
     VirtualStringTree -> NodeDataSize = sizeof(NodeStruct);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (!Node) return;

	NodeStruct *nodeData = (NodeStruct *)Sender -> GetNodeData(Node);
	switch (Column)
		{
		   case 0:
			   CellText = nodeData -> Id;
			   break;
		   case 1:
			   CellText = nodeData -> Path;
			   break;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteButtonClick(TObject *Sender)
{
	int selectedNodeIndex = NULL;

	PVirtualNode selectedNode = VirtualStringTree -> FocusedNode;

	int selectedCount = VirtualStringTree -> SelectedCount;

	if (selectedCount == 0)
	{
		throw Exception("No records selected");
	}

	vector<PVirtualNode> selectedNodes;
	vector<NodeStruct *> nodeData;
	vector<int> selectedIds;

	for (int index = 0; index < selectedCount; index++) {
		  if (index == 0) {
			  selectedNodes.push_back(VirtualStringTree -> GetFirstSelected());
		  }
		  else {
			  selectedNodes.push_back(VirtualStringTree -> GetNextSelected(selectedNodes[index-1]));
		  }

		  nodeData.push_back((NodeStruct *)VirtualStringTree -> GetNodeData(selectedNodes[index]));
		  selectedIds.push_back(nodeData[index]->Id);
	}

	DeleteSelectedRecords(selectedCount, selectedNodes, selectedIds);

	PVirtualNode selectedNext = VirtualStringTree -> GetNext(selectedNodes[selectedCount-1]);
	VirtualStringTree -> AddToSelection(selectedNext, false);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteSelectedRecords(int selectedCount, vector<PVirtualNode> selectedNodes, vector<int> selectedIds){

	sqlite3* dbHandle = getDataBaseHandle();

	for (int index = 0; index < selectedCount; index++)
	{
		VirtualStringTree -> DeleteNode(selectedNodes[index]);

		char buffer [10];
		itoa(selectedIds[index], buffer, 10);

		sqlite3_stmt *delStmt;

		char query [50] = "delete from segments where id=";
		strcat(query, buffer);
		int queryExecResult = sqlite3_prepare_v2(dbHandle, query, -1, &delStmt, NULL);

		queryExecResult = sqlite3_step(delStmt);
		if(queryExecResult != SQLITE_DONE)
		{
			const char * errmsg = sqlite3_errmsg(dbHandle);
			throw Exception(strcat("Some errors occured while execute query: ", errmsg));
		}

		sqlite3_finalize(delStmt);
	}

	sqlite3_close(dbHandle);
}


void __fastcall TForm1::ClearButtonClick(TObject *Sender)
{
		VirtualStringTree->BeginUpdate();

		sqlite3* dbHandle = getDataBaseHandle();

		char *errmsg;
		int queryExecResult = sqlite3_exec(dbHandle, "delete from segments", NULL, NULL, &errmsg);

		if(queryExecResult != SQLITE_OK)
		{
			sqlite3_close(dbHandle);
			throw Exception(strcat("Some errors occured while execute query: ", errmsg));
		}

		VirtualStringTree->Clear();
		VirtualStringTree->EndUpdate();

		sqlite3_close(dbHandle);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OpenDataBaseFileButtonClick(TObject *Sender)
{
   if (HistoryFileOpenDialog->Execute()){
	   return;
   }
}
//---------------------------------------------------------------------------

