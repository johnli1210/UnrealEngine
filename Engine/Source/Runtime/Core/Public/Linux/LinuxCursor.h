// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ICursor.h"
#include "LinuxWindow.h"

#include <SDL.h>

typedef SDL_Cursor*		SDL_HCursor;

class FLinuxCursor : public ICursor
{
public:
	FLinuxCursor();

	virtual ~FLinuxCursor();

	virtual FVector2D GetPosition() const override;

	virtual void SetPosition( const int32 X, const int32 Y ) override;

	virtual void SetType( const EMouseCursor::Type InNewCursor ) override;

	virtual EMouseCursor::Type GetType() const override
	{
		return CurrentType;
	}

	virtual void GetSize( int32& Width, int32& Height ) const override;

	virtual void Show( bool bShow ) override;

	virtual void Lock( const RECT* const Bounds ) override;

public:

	bool UpdateCursorClipping( FVector2D& CursorPosition );

	bool IsHidden();

	uint32 GetCursorEvent();
	
private:

	EMouseCursor::Type CurrentType;
	bool bHidden;

	/** Cursors */
	SDL_HCursor CursorHandles[ EMouseCursor::TotalCursorCount ];

	FIntRect CursorClipRect;

	uint32 CursorEvent;
};

