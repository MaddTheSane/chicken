//
//  AppDelegate.h
//  Chicken of the VNC
//
//  Created by Jason Harris on 8/18/04.
//  Copyright 2004 Geekspiff. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class DockConnection;

@interface AppDelegate : NSObject <NSApplicationDelegate> {
	IBOutlet NSMenuItem *mRendezvousMenuItem;
	IBOutlet NSTextField *mInfoVersionNumber;
    __unsafe_unretained NSMenuItem *fullScreenMenuItem;
	
    NSMutableArray      *dockConnections;
}

- (IBAction)showPreferences: (id)sender;
- (IBAction)changeRendezvousUse:(id)sender;
- (IBAction)showNewConnectionDialog:(id)sender;
- (IBAction)showConnectionDialog: (id)sender;
- (IBAction)showListenerDialog: (id)sender;
- (IBAction)showProfileManager: (id)sender;
- (IBAction)showHelp: (id)sender;

@property (unsafe_unretained, getter=getFullScreenMenuItem) IBOutlet NSMenuItem *fullScreenMenuItem;
- (NSMenuItem *)getFullScreenMenuItem;

- (NSMenu *)applicationDockMenu:(NSApplication *)sender;
- (void)addDockConnection:(DockConnection *)conn;
- (void)removeDockConnection:(DockConnection *)conn;

@end
