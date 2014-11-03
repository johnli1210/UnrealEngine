// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

class SChatWindow : public SUserWidget
{
public:
	SLATE_USER_ARGS(SChatWindow)
	{ }
	SLATE_ARGUMENT( const FFriendsAndChatStyle*, FriendStyle )
	SLATE_ARGUMENT(SMenuAnchor::EMethod, Method)
	SLATE_EVENT(FOnClicked, OnCloseClicked)
	SLATE_EVENT(FOnClicked, OnMinimizeClicked)
	SLATE_END_ARGS()

	/**
	 * Constructs the widget.
	 *
	 * @param InArgs The Slate argument list.
	 */
	virtual void Construct(const FArguments& InArgs, const TSharedRef<class FChatViewModel>& ViewModel) = 0;
};
