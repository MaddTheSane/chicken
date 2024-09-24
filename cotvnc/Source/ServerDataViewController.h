//
//  ServerDataViewController.h
//  Chicken of the VNC
//
//  Created by Jared McIntyre on Sun May 1 2004.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//


#import <Cocoa/Cocoa.h>
#import "ConnectionWaiter.h"

NS_ASSUME_NONNULL_BEGIN

@protocol IServerData;
@protocol ConnectionDelegate;
@class RFBConnection;
@class RFBConnectionManager;
@class ServerBase;

@interface ServerDataViewController : NSWindowController
                                            <ConnectionWaiterDelegate>
{
    IBOutlet NSTextField *display;
    IBOutlet NSTextField *displayDescription;
    IBOutlet NSTextField *hostName;
    IBOutlet NSTextField *password;
    IBOutlet NSPopUpButton *profilePopup;
    IBOutlet NSButton *rememberPwd;
	IBOutlet NSButton *fullscreen;
    IBOutlet NSButton *shared;
	IBOutlet NSButton *viewOnly;
	IBOutlet NSButton *save;
    IBOutlet NSButton *useSshTunnel;
    IBOutlet NSTextField *sshHost;

	NSBox *box;
	IBOutlet NSButton *connectBtn;
	
	IBOutlet NSProgressIndicator *connectIndicator;
	IBOutlet NSTextField *connectIndicatorText;
	
	ServerBase  *mServer;
	
	bool selfTerminate;
	bool removedSaveCheckbox;

    ConnectionWaiter    *connectionWaiter;
    BOOL saveCheckboxWasVisible;
    RFBConnectionManager *superController;
}

- (instancetype)initWithReleaseOnCloseOrConnect;

@property (nonatomic, retain, nullable) id<IServerData> server;

- (IBAction)passwordChanged:(nullable id)sender;
- (IBAction)rememberPwdChanged:(nullable id)sender;
- (IBAction)profileSelectionChanged:(nullable id)sender;
- (IBAction)fullscreenChanged:(nullable id)sender;
- (IBAction)sharedChanged:(nullable id)sender;
- (IBAction)viewOnlyChanged:(nullable id)sender;
- (IBAction)useSshTunnelChanged:(nullable id)sender;
- (IBAction)sshHostChanged:(nullable id)sender;
- (IBAction)addServerChanged:(nullable id)sender;

- (IBAction)showProfileManager:(nullable id)sender;

- (IBAction)connectToServer:(nullable id)sender;
- (IBAction)cancelConnect: (nullable id)sender;

- (void)connectionSucceeded: (RFBConnection *)theConnection;
- (void)connectionFailed;
- (void)connectionAttemptEnded;

- (void)disableControls;

@property (assign, nullable) IBOutlet NSBox *box;

- (void)updateView:(nullable id)notification;
- (void)updateProfileView:(nullable id)notification;
- (void)setProfilePopupToProfile: (nullable Profile *)profileName;

- (void)loadProfileIntoView;

- (void)setSaveCheckboxIsVisible:(BOOL)visible;
- (void)setSuperController:(RFBConnectionManager *)aSuperController;

@end

NS_ASSUME_NONNULL_END
