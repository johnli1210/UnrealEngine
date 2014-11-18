// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Misc/OutputDeviceConsole.h"


/**
 * Feedback context implementation for windows.
 */
class FFeedbackContextWindows : public FFeedbackContext
{
	/** Context information for warning and error messages */
	FContextSupplier*	Context;

public:
	// Variables.

	// Constructor.
	FFeedbackContextWindows()
	: FFeedbackContext()
	, Context( NULL )
	{}
	void Serialize( const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category )
	{
		// if we set the color for warnings or errors, then reset at the end of the function
		// note, we have to set the colors directly without using the standard SET_WARN_COLOR macro
		if( Verbosity==ELogVerbosity::Error || Verbosity==ELogVerbosity::Warning )
		{
			if( TreatWarningsAsErrors && Verbosity==ELogVerbosity::Warning )
			{
				Verbosity = ELogVerbosity::Error;
			}

			FString Prefix;
			if( Context )
			{
				Prefix = Context->GetContext() + TEXT(" : ");
			}
			FString Format = Prefix + FOutputDevice::FormatLogLine(Verbosity, Category, V);

			if(Verbosity == ELogVerbosity::Error)
			{
				// Only store off the message if running a commandlet.
				if ( IsRunningCommandlet() )
				{
					Errors.Add(Format);
				}
			}
			else
			{
				// Only store off the message if running a commandlet.
				if ( IsRunningCommandlet() )
				{
					Warnings.Add(Format);
				}
			}
		}

		if( GLogConsole && IsRunningCommandlet() )
		{
			GLogConsole->Serialize( V, Verbosity, Category );
		}
		if( !GLog->IsRedirectingTo( this ) )
		{
			GLog->Serialize( V, Verbosity, Category );
		}
	}
	VARARG_BODY( bool, YesNof, const TCHAR*, VARARG_NONE )
	{
		TCHAR TempStr[4096];
		GET_VARARGS( TempStr, ARRAY_COUNT(TempStr), ARRAY_COUNT(TempStr)-1, Fmt, Fmt );
		if( ( GIsClient || GIsEditor ) && ( ( GIsSilent != true ) && ( FApp::IsUnattended() != true ) ) )
		{
			return( ::MessageBox( NULL, TempStr, *NSLOCTEXT("Core", "Question", "Question").ToString(), MB_YESNO|MB_TASKMODAL ) == IDYES);
		}
		else
		{
			return false;
		}
	}
	FContextSupplier* GetContext() const
	{
		return Context;
	}
	void SetContext( FContextSupplier* InSupplier )
	{
		Context = InSupplier;
	}
};

