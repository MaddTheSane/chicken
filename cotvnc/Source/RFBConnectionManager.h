/* Copyright (C) 1998-2000  Helmut Maierhofer <helmut.maierhofer@chello.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#import <AppKit/AppKit.h>
#import "ServerDataViewController.h"

@class Profile, ProfileManager;
@class RFBConnection;
@class ServerDataViewController;
@protocol IServerData;


@interface RFBConnectionManager : NSWindowController <NSTableViewDataSource, NSTableViewDelegate>
{
	IBOutlet NSTableView *serverList;
	IBOutlet NSTableView *groupList;
	IBOutlet NSBox *serverDataBoxLocal;
	NSBox *serverListBox;
	NSBox *serverGroupBox;
	IBOutlet NSSplitView *splitView;
    IBOutlet NSButton *serverDeleteBtn;
    IBOutlet NSButton *serverAddBtn;
    NSMutableArray*	sessions;
	ServerDataViewController* mServerCtrler;
	BOOL mDisplayGroups;
	BOOL mRunningFromCommandLine;
	BOOL mLaunchedByURL;
	NSArray* mOrderedServerNames;

    ConnectionWaiter    *connectionWaiter;
    NSInteger lockedSelection;
}

@property (class, readonly) RFBConnectionManager *sharedManager;

@property (strong) IBOutlet NSBox *serverListBox;
@property (strong) IBOutlet NSBox *serverGroupBox;


- (void)wakeup;
@property (readonly, nonatomic) BOOL runFromCommandLine;
- (void)runNormally;

- (IBAction)showNewConnectionDialog: (id)sender;
- (IBAction)showConnectionDialog: (id)sender;

- (IBAction)removeConnection:(id)aConnection;
- (void)cmdlineUsage;

- (void)selectedHostChanged;

- (void)setControlsEnabled:(BOOL)enabled;
- (void)connectionDone;

- (NSString*)translateDisplayName:(NSString*)aName forHost:(NSString*)aHost;
- (void)setDisplayNameTranslation:(NSString*)translation forName:(NSString*)aName forHost:(NSString*)aHost;

- (BOOL)createConnectionWithFileHandle:(NSFileHandle*)file 
    server:(id<IServerData>) server;
- (void)successfulConnection: (RFBConnection *)theConnection;

- (IBAction)addServer:(id)sender;
- (IBAction)deleteSelectedServer:(id)sender;

- (void)makeAllConnectionsWindowed;

- (void)serverListDidChange:(NSNotification*)notification;

@property (readonly) id<IServerData> selectedServer;
- (BOOL)selectServerByName:(NSString *)aName;

- (void)useRendezvous:(BOOL)useRendezvous;

- (void)displayGroups:(bool)display;

- (void)setFrontWindowUpdateInterval: (NSTimeInterval)interval;
- (void)setOtherWindowUpdateInterval: (NSTimeInterval)interval;

@property BOOL launchedByURL;

@end
