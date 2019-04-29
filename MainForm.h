//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <ustring.h>
#include "sqlite3.h"
#include "VirtualTrees.hpp"
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------

typedef struct tagNodeStruct {
	int Id;
	UnicodeString Path;
} NodeStruct;

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree;
	TButton *LoadHistoryButton;
	TButton *DeleteButton;
	TButton *ClearButton;
	TOpenDialog *HistoryFileOpenDialog;
	TButton *OpenDataBaseFileButton;
	void __fastcall LoadHistoryButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall VirtualStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall DeleteButtonClick(TObject *Sender);
	void __fastcall ClearButtonClick(TObject *Sender);
	void __fastcall OpenDataBaseFileButtonClick(TObject *Sender);


private:	// User declarations
    sqlite3* TForm1::getDataBaseHandle();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall DeleteSelectedRecords(int selectedCount,
		  std::vector<PVirtualNode> selectedNodes, std::vector<int> selectedIds);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
