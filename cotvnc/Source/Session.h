/* Copyright (C) 1998-2000  Helmut Maierhofer <helmut.maierhofer@chello.at>
 * Copyright 2011 Dustin Cartwright
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
#import "ConnectionWaiter.h"

@protocol IServerData;

@class RFBConnection;
@class RFBView;
@class SshTunnel;

@interface Session : NSObject <NSNetServiceDelegate, NSWindowDelegate, ConnectionWaiterDelegate>
{
    RFBConnection   *connection;
    IBOutlet RFBView *rfbView;
    IBOutlet NSWindow    *window;
    id<IServerData> server_;
    NSString        *password;
    SshTunnel       *sshTunnel;

    IBOutlet NSScrollView *scrollView;
    IBOutlet NSTextField *newTitleField;
    IBOutlet NSPanel *newTitlePanel;
    NSString    *titleString;
    IBOutlet NSTextField *statisticField;

    NSSize _maxSize;

    BOOL	horizontalScroll;
    BOOL	verticalScroll;

    IBOutlet NSPanel *optionPanel;
    IBOutlet NSTextField *infoField;

    NSString *realDisplayName;
    NSString *host;

    IBOutlet NSPanel *passwordSheet;
    IBOutlet NSTextField *passwordField;
    IBOutlet NSTextField *authHeader;
    IBOutlet NSTextField *authMessage;
    IBOutlet NSButton *rememberNewPassword;

        // for reconnection attempts
    IBOutlet NSPanel                *_reconnectPanel;
    IBOutlet NSProgressIndicator    *_reconnectIndicator;
    IBOutlet NSTextField            *_reconnectReason;
    NSDate                          *_connectionStartDate;
    NSTimer                         *_reconnectSheetTimer;
    ConnectionWaiter                *_reconnectWaiter;

        // instance variables for managing the fullscreen display
	BOOL _isFullscreen;
    NSWindow *windowedWindow;
	NSTrackingRectTag _leftTrackingTag;
	NSTrackingRectTag _topTrackingTag;
	NSTrackingRectTag _rightTrackingTag;
	NSTrackingRectTag _bottomTrackingTag;
    int         _horizScrollFactor;
    int         _vertScrollFactor;
	NSTimer *_autoscrollTimer;
}

- (instancetype)initWithConnection:(RFBConnection*)conn;

- (BOOL)viewOnly;

- (void)setSize:(NSSize)size;
@property (copy, nonatomic) NSString *displayName;
- (void)setupWindow;
- (void)frameBufferUpdateComplete;
- (void)resize:(NSSize)size;

- (IBAction)paste:(id)sender;
- (IBAction)sendPasteboardToServer:(id)sender;
- (void)terminateConnection:(NSString*)aReason;
- (void)authenticationFailed:(NSString *)aReason;
- (void)promptForPassword;
- (IBAction)reconnectWithNewPassword:(id)sender;
- (IBAction)dontReconnect:(id)sender;
- (IBAction)forceReconnect:(id)sender;
- (IBAction)openNewTitlePanel:(id)sender;
- (IBAction)setNewTitle:(id)sender;

- (IBAction)requestFrameBufferUpdate:(id)sender;

    //window delegate messages
- (void)windowDidBecomeKey:(NSNotification *)aNotification;
- (void)windowDidResignKey:(NSNotification *)aNotification;
- (void)windowDidDeminiaturize:(NSNotification *)aNotification;
- (void)windowDidMiniaturize:(NSNotification *)aNotification;
- (void)windowWillClose:(NSNotification *)aNotification;
- (void)windowDidResize:(NSNotification *)aNotification;
- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)proposedFrameSize;

- (IBAction)openOptions:(id)sender;

- (BOOL)hasKeyWindow;

// Full-screen mode
@property (readonly) BOOL connectionIsFullscreen;
- (IBAction)toggleFullscreenMode: (id)sender;
- (IBAction)makeConnectionWindowed: (id)sender;
- (IBAction)makeConnectionFullscreen: (id)sender;
- (void)applicationWillHide:(NSNotification*)notif;

- (void)installFullscreenTrackingRects;
- (void)removeFullscreenTrackingRects;
- (void)mouseEntered:(NSEvent *)theEvent;
- (void)mouseExited:(NSEvent *)theEvent;
- (void)mouseDragged:(NSEvent *)theEvent;
- (void)beginFullscreenScrolling;
- (void)endFullscreenScrolling;
- (void)scrollFullscreenView: (NSTimer *)timer;

- (void)setFrameBufferUpdateSeconds: (NSTimeInterval)seconds;

// For reconnect
- (void)createReconnectSheet:(id)sender;
- (IBAction)reconnectCancelled:(id)sender; // returnCode:(int)retCode

@end
