object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'History'
  ClientHeight = 652
  ClientWidth = 829
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object VirtualStringTree: TVirtualStringTree
    Left = 8
    Top = 8
    Width = 813
    Height = 513
    Header.AutoSizeIndex = 0
    Header.DefaultHeight = 50
    Header.Height = 20
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible, hoHeightResize]
    TabOrder = 0
    TreeOptions.SelectionOptions = [toFullRowSelect, toMultiSelect]
    OnGetText = VirtualStringTreeGetText
    Columns = <
      item
        Position = 0
        Text = 'ID'
        Width = 100
      end
      item
        Position = 1
        Text = 'Path'
        Width = 767
      end>
  end
  object LoadHistoryButton: TButton
    Left = 192
    Top = 543
    Width = 113
    Height = 34
    Caption = 'Load'
    TabOrder = 1
    OnClick = LoadHistoryButtonClick
  end
  object DeleteButton: TButton
    Left = 328
    Top = 543
    Width = 129
    Height = 34
    Caption = 'Delete'
    TabOrder = 2
    OnClick = DeleteButtonClick
  end
  object ClearButton: TButton
    Left = 480
    Top = 543
    Width = 129
    Height = 34
    Caption = 'Clear'
    TabOrder = 3
    OnClick = ClearButtonClick
  end
  object OpenDataBaseFileButton: TButton
    Left = 80
    Top = 543
    Width = 97
    Height = 34
    BiDiMode = bdLeftToRight
    Caption = 'Open'
    ParentBiDiMode = False
    TabOrder = 4
    OnClick = OpenDataBaseFileButtonClick
  end
  object HistoryFileOpenDialog: TOpenDialog
    InitialDir = '.'
    Left = 40
    Top = 544
  end
end
