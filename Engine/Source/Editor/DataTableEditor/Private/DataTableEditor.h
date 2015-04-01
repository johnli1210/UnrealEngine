// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IDataTableEditor.h"
#include "Toolkits/AssetEditorToolkit.h"

#include "Kismet2/StructureEditorUtils.h"
#include "DataTableEditorUtils.h"

class UDataTable;
class FJsonObject;

DECLARE_DELEGATE_OneParam(FOnRowHighlighted, FName /*Row name*/);

/** Viewer/editor for a DataTable */
class FDataTableEditor : public IDataTableEditor
	, public FStructureEditorUtils::INotifyOnStructChanged
	, public FDataTableEditorUtils::INotifyOnDataTableChanged
{

public:

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;

	/**
	 * Edits the specified table
	 *
	 * @param	Mode					Asset editing mode for this editor (standalone or world-centric)
	 * @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within
	 * @param	Table					The table to edit
	 */
	void InitDataTableEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UDataTable* Table );

	/** Constructor */
	FDataTableEditor();

	/** Destructor */
	virtual ~FDataTableEditor();

	/* Create the grid panel */
	TSharedRef<SWidget> CreateGridPanel();

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	// INotifyOnStructChanged
	virtual void PreChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;
	virtual void PostChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;

	// INotifyOnDataTableChanged
	virtual void PreChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo Info) override;
	virtual void PostChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo Info) override;

	void SetHighlightedRow(FName Name);

private:

	void ReloadVisibleData();

	void OnSearchTextChanged(const FText& SearchText);

	TSharedRef<SVerticalBox> CreateContentBox();

	TSharedRef<SWidget> CreateRowEditorBox();

	/**	Spawns the tab with the data table inside */
	TSharedRef<SDockTab> SpawnTab_DataTable( const FSpawnTabArgs& Args );

	/**	Spawns the tab with the Row Editor inside */
	TSharedRef<SDockTab> SpawnTab_RowEditor(const FSpawnTabArgs& Args);

	FSlateColor GetRowColor(FName RowName) const;

	FReply OnRowClicked(const FGeometry&, const FPointerEvent&, FName RowName);

	float GetColumnWidth(const int32 ColumnIndex);

	void OnColumnResized(const float NewWidth, const int32 ColumnIndex);

	void LoadLayoutData();

	void SaveLayoutData();

private:

	/** Struct holding information about the current column widths */
	struct FColumnWidth
	{
		FColumnWidth()
			: bIsAutoSized(true)
			, CurrentWidth(0.0f)
		{
		}

		/** True if this column is being auto-sized rather than sized by the user */
		bool bIsAutoSized;
		/** The width of the column, either sized by the user, or auto-sized */
		float CurrentWidth;
	};

	/** Cached table data */
	TArray<TArray<FString> > CachedDataTable;

	/** Cached raw column names */
	TArray<FString> CachedRawColumnNames;

	/** Visibility of data table rows */
	TArray<bool> RowsVisibility;

	/** Widths of data table columns */
	TArray<FColumnWidth> ColumnWidths;

	/** Search box */
	TSharedPtr<SWidget> SearchBox;

	/** Scroll containing data table */
	TSharedPtr<SScrollBox> ScrollBoxWidget;

	/**Border surrounding the GridPanel */
	TSharedPtr<SBorder>	 GridPanelOwner;

	/* The DataTable that is active in the editor */
	TAssetPtr<UDataTable> DataTable;

	/** The layout data for the currently loaded data table */
	TSharedPtr<FJsonObject> LayoutData;

	FName HighlightedRowName;

	FOnRowHighlighted CallbackOnRowHighlighted;

	/**	The tab id for the data table tab */
	static const FName DataTableTabId;

	/**	The tab id for the row editor tab */
	static const FName RowEditorTabId;
};
