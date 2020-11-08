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
#import "ProfileManager.h"
#import "Profile.h"

//! Notifications
extern NSString * const ProfileAddDeleteNotification;

	
@interface ProfileManager : NSWindowController <NSTableViewDataSource, NSTableViewDelegate>
{
    IBOutlet NSTableView *mProfileTable;
    IBOutlet NSTextField *mProfileNameField;
    IBOutlet NSButton *mNewProfileButton;
    IBOutlet NSButton *mDeleteProfileButton;
	IBOutlet NSPopUpButton *mEmulationPopup2;
	IBOutlet NSPopUpButton *mEmulationPopup3;
	IBOutlet NSTabView *mEmulationTabView2;
	IBOutlet NSTabView *mEmulationTabView3;
	IBOutlet NSPopUpButton *mClickWhileHoldingEmulationModifier2;
	IBOutlet NSPopUpButton *mClickWhileHoldingEmulationModifier3;
	IBOutlet NSPopUpButton *mMultiTapEmulationModifier2;
	IBOutlet NSPopUpButton *mMultiTapEmulationModifier3;
	IBOutlet NSStepper *mMultiTapEmulationCountStepper2;
	IBOutlet NSStepper *mMultiTapEmulationCountStepper3;
	IBOutlet NSTextField *mMultiTapEmulationCountText2;
	IBOutlet NSTextField *mMultiTapEmulationCountText3;
	IBOutlet NSPopUpButton *mTapAndClickEmulationModifier2;
	IBOutlet NSPopUpButton *mTapAndClickEmulationModifier3;
	IBOutlet NSTextField *mTapAndClickEmulationTimeout2;
	IBOutlet NSTextField *mTapAndClickEmulationTimeout3;
    IBOutlet NSPopUpButton *mAltKey;
    IBOutlet NSPopUpButton *mCommandKey;
    IBOutlet NSPopUpButton *mControlKey;
    IBOutlet NSTableView *mEncodingTableView;
	IBOutlet NSButton *mEnableCopyRect;
    IBOutlet NSButton *mEnableJpegEncoding;
    IBOutlet NSMatrix *mPixelFormatMatrix;
    IBOutlet NSColorWell *mTintColorWell;
	NSInteger mEncodingDragRow;
}

	// Shared Instance
+ (id)sharedManager;
- (void)wakeup;

	// Profile Manager Window
- (IBAction)showWindow: (id)sender;
- (void)showWindowWithProfile: (NSString *)profileName;

	// Profile Access
- (Profile *)defaultProfile;
- (BOOL)profileWithNameExists:(NSString*)name;
- (Profile*)profileNamed:(NSString*)name;

	// Action Methods
- (IBAction)addProfile:(id)sender;
- (IBAction)deleteProfile:(id)sender;
- (IBAction)formDidChange:(id)sender;
- (IBAction)toggleSelectedEncodingEnabled: (id)sender;
- (IBAction)tintDidChange:(id)sender;

@end
