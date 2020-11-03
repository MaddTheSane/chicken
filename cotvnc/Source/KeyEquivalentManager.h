//
//  KeyEquivalentManager.h
//  Chicken of the VNC
//
//  Created by Jason Harris on Sun Mar 21 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/NSEvent.h>
@class KeyEquivalentScenario, RFBView;


// Scenarios
extern NSString *const kNonConnectionWindowFrontmostScenario;
extern NSString *const kConnectionWindowFrontmostScenario;
extern NSString *const kConnectionFullscreenScenario;


@interface KeyEquivalentManager : NSObject {
    KeyEquivalentScenario *standardKeyEquivalents;
	NSMutableDictionary<NSString*,KeyEquivalentScenario*> *mScenarioDict;		// Scenario -> KeyEquivalentScenario
	NSString *mCurrentScenarioName;
	KeyEquivalentScenario *mCurrentScenario;
	//__weak RFBView *mKeyRFBView;
}

// Obtaining An Instance
+ (id)defaultManager;

// Persistent Scenarios
- (void)loadScenariosFromPreferences;
- (void)loadScenariosFromDefaults;
- (void)makeScenariosPersistant;
- (void)restoreDefaults;
- (NSDictionary *)propertyList;
- (void)takeScenariosFromPropertyList: (NSDictionary *)propertyList;

// Dealing With The Current Scenario
- (void)setCurrentScenarioToName: (NSString *)scenario;
@property (readonly, copy) NSString *currentScenarioName;

// Obtaining Scenario Equivalents
- (KeyEquivalentScenario *)keyEquivalentsForScenarioName: (NSString *)scenario;

// Performing Key Equivalants
- (BOOL)performEquivalentWithCharacters: (NSString *)characters modifiers: (NSEventModifierFlags)modifiers;

// Obtaining the current RFBView
@property (readonly, weak) RFBView *keyRFBView;

- (void)removeEquivalentForWindow:(NSString *)title;

@end
