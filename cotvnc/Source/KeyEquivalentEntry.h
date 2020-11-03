//
//  KeyEquivalentEntry.h
//  Chicken of the VNC
//
//  Created by Jason Harris on Sun Mar 21 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//

#import <AppKit/AppKit.h>
@class KeyEquivalent;


/**
 * Encapsulates a menu item, which will be assigned to a key equivalence by
 * KeyEquivalentScenario.
 */
@interface KeyEquivalentEntry : NSObject {
	__weak NSMenuItem *mMenuItem;
}

- (instancetype)init UNAVAILABLE_ATTRIBUTE;
- (instancetype)initWithTitle: (NSString *)title NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithMenuItem: (NSMenuItem *)menuItem NS_DESIGNATED_INITIALIZER;
@property (readonly, weak) NSMenuItem *menuItem;
- (void)makeActive: (BOOL)active forKeyEquivalent: (KeyEquivalent *)keyEquivalent;
- (BOOL)isEqualToEntry: (KeyEquivalentEntry *)x;

@end
