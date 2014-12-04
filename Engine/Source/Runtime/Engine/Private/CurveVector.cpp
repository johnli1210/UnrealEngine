// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	CurveVector.cpp
=============================================================================*/

#include "EnginePrivate.h"
#include "Curves/CurveVector.h"


UCurveVector::UCurveVector(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FVector UCurveVector::GetVectorValue( float InTime ) const
{
	FVector Result;
	Result.X = FloatCurves[0].Eval(InTime);
	Result.Y = FloatCurves[1].Eval(InTime);
	Result.Z = FloatCurves[2].Eval(InTime);
	return Result;
}

static const FName XCurveName(TEXT("X"));
static const FName YCurveName(TEXT("Y"));
static const FName ZCurveName(TEXT("Z"));

TArray<FRichCurveEditInfoConst> UCurveVector::GetCurves() const 
{
	TArray<FRichCurveEditInfoConst> Curves;
	Curves.Add(FRichCurveEditInfoConst(&FloatCurves[0], XCurveName));
	Curves.Add(FRichCurveEditInfoConst(&FloatCurves[1], YCurveName));
	Curves.Add(FRichCurveEditInfoConst(&FloatCurves[2], ZCurveName));
	return Curves;
}

TArray<FRichCurveEditInfo> UCurveVector::GetCurves() 
{
	TArray<FRichCurveEditInfo> Curves;
	Curves.Add(FRichCurveEditInfo(&FloatCurves[0], XCurveName));
	Curves.Add(FRichCurveEditInfo(&FloatCurves[1], YCurveName));
	Curves.Add(FRichCurveEditInfo(&FloatCurves[2], ZCurveName));
	return Curves;
}

bool UCurveVector::operator==( const UCurveVector& Curve ) const
{
	return (FloatCurves[0] == Curve.FloatCurves[0]) && (FloatCurves[1] == Curve.FloatCurves[1]) && (FloatCurves[2] == Curve.FloatCurves[2]) ;
}

