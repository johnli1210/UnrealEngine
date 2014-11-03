// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

/**
 * Interface for the Friends and chat manager.
 */
class IFriendsAndChatManager
{
public:

	/**
	 * Create the friends list widget.
	 *
	 * @param ParentWindow The parent window to add the widget
	 * @param InStyle The style to use to create the widgets
	 */
	virtual void CreateFriendsListWidget( TSharedPtr< const SWidget > ParentWidget, const struct FFriendsAndChatStyle* InStyle ) = 0;

	/**
	 * Create the a friends list widget without a container.
	 * @param InStyle The style to use to create the widgets.
	 * @return The Friends List widget.
	 */
	virtual TSharedPtr< SWidget > GenerateFriendsListWidget( const struct FFriendsAndChatStyle* InStyle ) = 0;

	/**
	 * Set that we are in a session, so can send join game requests.
	 *
	 * @param bInSession If we are in a session.
	 */
	virtual void SetInSession( bool bInSession ) = 0;

	/** Log out and kill the friends list window. */
	virtual void Logout() = 0;

	/** Log in and start checking for Friends. */
	virtual void Login() = 0;

	DECLARE_EVENT_OneParam(IFriendsAndChatManager, FOnFriendsNotificationEvent, const bool /*Show or Clear */)
	virtual FOnFriendsNotificationEvent& OnFriendsNotification() = 0;

public:

	/** Virtual destructor. */
	virtual ~IFriendsAndChatManager() { }
};
