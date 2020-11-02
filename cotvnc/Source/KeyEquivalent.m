//
//  KeyEquivalent.m
//  Chicken of the VNC
//
//  Created by Jason Harris on Sun Mar 21 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//

#import "KeyEquivalent.h"
#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>


@implementation KeyEquivalent

- (id)initWithCharacters: (NSString *)characters modifiers: (NSEventModifierFlags)modifiers
{
	if ( self = [super init] )
	{
		mCharacters = [characters copy];
		mModifiers = modifiers;
	}
	return self;
}

- (BOOL)isEqual:(id)anObject
{  return [self isEqualToKeyEquivalent: anObject];  }

- (BOOL)isEqualToKeyEquivalent: (KeyEquivalent *)anObject
{
	if ( ! anObject )
		return NO;
	return (mModifiers == anObject->mModifiers) && ([mCharacters isEqualToString: anObject->mCharacters]);
}

- (NSUInteger)hash
{
	return [mCharacters hash] + mModifiers;
}

- (id)copyWithZone:(NSZone *)zone
{  return [[KeyEquivalent allocWithZone: zone] initWithCharacters: mCharacters modifiers: mModifiers];  }

- (NSString *)description
{  return [NSString stringWithFormat: @"0x%0.8lx (%@)", (unsigned long)mModifiers, mCharacters];  }

- (NSString *)characters
{  return mCharacters ? mCharacters : @"";  }

@synthesize modifiers=mModifiers;


- (NSAttributedString *)userString
{
	if ( ! mCharacters || [mCharacters length] == 0 ) 
		return [[NSAttributedString alloc] initWithString: @""];
	NSMutableString *string = [NSMutableString string];
	NSRange foundRange = [mCharacters rangeOfCharacterFromSet: [NSCharacterSet uppercaseLetterCharacterSet]];
	if (mModifiers & NSEventModifierFlagShift || foundRange.location != NSNotFound)
		[string appendString: @"⇧"];
	if (mModifiers & NSEventModifierFlagControl)
		[string appendString: @"⌃"];
	if (mModifiers & NSEventModifierFlagOption)
		[string appendString: @"⌥"];
	if (mModifiers & NSEventModifierFlagCommand)
		[string appendString: @"⌘"];
	
	NSMutableAttributedString *attrString = [[NSMutableAttributedString alloc] initWithString: string];
	
	NSString *chars = [mCharacters uppercaseString];
	size_t i, length = [chars length];
	for (i = 0; i < length; ++i)
	{
		unichar c = [chars characterAtIndex: i];
		NSMutableAttributedString *newAttrString = nil;
		if ( c == kBackspaceCharCode )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"⌫"];
		else if ( c == kTabCharCode )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"⇥"];
		else if ( c == kEnterCharCode )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"⌅"];
		else if ( c == NSHomeFunctionKey )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"↖"];
		else if ( c == NSEndFunctionKey )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"↘"];
		else if ( c == NSPageUpFunctionKey )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"⇞"];
		else if ( c == NSPageDownFunctionKey )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"⇟"];
		else if ( c == kReturnCharCode )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"↩"];
		else if ( c == kEscapeCharCode )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"⎋"];
		else if ( c == kClearCharCode )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"⌧"];
		else if ( c == NSLeftArrowFunctionKey )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"←"];
		else if ( c == NSRightArrowFunctionKey )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"→"];
		else if ( c == NSUpArrowFunctionKey )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"↑"];
		else if ( c == NSDownArrowFunctionKey )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"↓"];
		else if ( c == kSpaceCharCode )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"␣"];
		else if ( c == kDeleteCharCode )
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @"⌦"];
		else if ( c == NSDeleteFunctionKey )
			return [[NSAttributedString alloc] initWithString: @""];
		else if (c >= NSF1FunctionKey && c <= NSF15FunctionKey)
		{
			unsigned int cid = 1173 + c - NSF1FunctionKey;
			newAttrString = [[NSMutableAttributedString alloc] initWithString: @" "];
			NSRange rangeOfStringToBeOverriden = {0, 1};
			NSString *baseString = [[newAttrString string] substringWithRange: rangeOfStringToBeOverriden];
			NSGlyphInfo *glyphInfo = [NSGlyphInfo glyphInfoWithCharacterIdentifier: cid
																		collection: NSIdentityMappingCharacterCollection
																		baseString: baseString];
			[newAttrString addAttribute: NSGlyphInfoAttributeName
								  value: glyphInfo
								  range: rangeOfStringToBeOverriden];
		}
		if (newAttrString == nil)
		{
			NSString *newString = [[NSString alloc] initWithBytes: &c length: sizeof(c) encoding: [mCharacters fastestEncoding]];
			newAttrString = [[NSMutableAttributedString alloc] initWithString: newString];
		}
		[attrString appendAttributedString: newAttrString];
	}
	return attrString;
}

- (NSString *)string
{
    /* Produces a string representation of the key equivalent. It's just a hack
     * to cover the one case where we can't just use the underlying string of
     * userString actually uses an attribute. */
    if ([mCharacters length] > 0) {
        unichar c = [mCharacters characterAtIndex:0];
        if (c >= NSF1FunctionKey && c <= NSF15FunctionKey)
            return [NSString stringWithFormat:@"F%d", c - NSF1FunctionKey + 1];
    }
    return [[self userString] string];
}

@end
