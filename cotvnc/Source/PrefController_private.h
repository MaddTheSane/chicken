//
//  PrefController_private.h
//  Chicken of the VNC
//
//  Created by Jason Harris on 8/18/04.
//  Copyright 2004 Geekspiff. All rights reserved.
//

#import "PrefController.h"


// --- Preference Keys -- //
/* These are private because they should only be used by PrefController */
extern NSString *const kPrefs_FullscreenWarning_Key;
extern NSString *const kPrefs_AutoscrollIncrement_Key;
extern NSString *const kPrefs_FullscreenScrollbars_Key;
extern NSString *const kPrefs_UseRendezvous_Key;
extern NSString *const kPrefs_ConnectionProfiles_Key;
extern NSString *const kPrefs_FrontFrameBufferUpdateSeconds_Key;
extern NSString *const kPrefs_OtherFrameBufferUpdateSeconds_Key;
extern NSString *const kPrefs_HostInfo_Key;
extern NSString *const kPrefs_Version_Key;
extern NSString *const kPrefs_AutoReconnect_Key;
extern NSString *const kPrefs_IntervalBeforeReconnect_Key;


@interface PrefController (Private)

	// Preference Updating
- (void)_updatePrefs_20b2;

	// Preferences Window
- (void)_setupWindow;

@end
