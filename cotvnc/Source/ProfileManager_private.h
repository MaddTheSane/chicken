//
//  ProfileManager_private.h
//  Chicken of the VNC
//
//  Created by Jason Harris on 8/19/04.
//  Copyright 2004 Geekspiff. All rights reserved.
//

#import "ProfileManager.h"


@interface ProfileManager (Private)

- (Profile *)_currentProfile;
- (NSString *)_currentProfileName;
- (void)_selectProfileAtIndex: (NSInteger)index;
- (void)_selectProfileNamed:(NSString*)aProfile;
@property (readonly, copy) NSArray<NSString*> *_sortedProfileNames;
- (void)_updateBrowserButtons;
- (void)_updateForm;

@end
