//
//  PrefController.h
//  Chicken of the VNC
//
//  Created by Jason Harris on 8/18/04.
//  Copyright 2004 Geekspiff. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "rfbproto.h"


@interface PrefController : NSObject {
	IBOutlet NSWindow *mWindow;
	IBOutlet NSSlider *mAutoscrollIncrement;
	IBOutlet NSButton *mFullscreenScrollbars;
	IBOutlet NSButton *mDisplayFullscreenWarning;
	IBOutlet NSSlider *mFrontInverseCPUSlider;
	IBOutlet NSSlider *mOtherInverseCPUSlider;
}

	// Creation
@property (class, readonly, strong) PrefController *sharedController;

	// Settings
@property (nonatomic) BOOL displayFullScreenWarning;
@property (nonatomic, readonly) CGFloat fullscreenAutoscrollIncrement;
@property (nonatomic, readonly) BOOL fullscreenHasScrollbars;
@property (nonatomic, readonly) NSTimeInterval frontFrameBufferUpdateSeconds;
@property (nonatomic, readonly) NSTimeInterval otherFrameBufferUpdateSeconds;
@property (nonatomic, readonly) CGFloat gammaCorrection;
- (void)getLocalPixelFormat:(rfbPixelFormat*)pf;
- (id)defaultFrameBufferClass;
@property (nonatomic, readonly) NSTimeInterval maxPossibleFrameBufferUpdateSeconds;
@property (nonatomic, readonly) BOOL usesRendezvous;
@property (nonatomic, copy) NSDictionary *hostInfo;
- (void)setHostInfo: (NSDictionary *)hostInfo;
@property (nonatomic, copy) NSDictionary *profileDict;
@property (nonatomic, readonly, copy) NSDictionary *defaultProfileDict;
- (void)setProfileDict: (NSDictionary *)dict;
@property (nonatomic, readonly) BOOL autoReconnect;
@property (nonatomic, readonly) NSTimeInterval intervalBeforeReconnect;

	// Preferences Window
- (void)showWindow;

	// Action Methods
- (IBAction)frontInverseCPUSliderChanged: (NSSlider *)sender;
- (IBAction)otherInverseCPUSliderChanged: (NSSlider *)sender;
- (IBAction)autoscrollSpeedChanged: (NSSlider *)sender;
- (IBAction)toggleFullscreenScrollbars: (NSButton *)sender;
- (IBAction)toggleFullscreenWarning: (NSButton *)sender;
- (IBAction)toggleUseRendezvous: (id)sender;

@end
