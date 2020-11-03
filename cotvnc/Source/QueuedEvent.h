//
//  QueuedEvent.h
//  keysymtest
//
//  Created by Bob Newhart on 7/1/05.
//  Copyright 2005 Geekspiff. All rights reserved.
//

#import <Cocoa/Cocoa.h>


typedef NS_ENUM(int, QueuedEventType) {
	kQueuedMouse1DownEvent, 
	kQueuedMouse1UpEvent, 
	kQueuedMouse2DownEvent, 
	kQueuedMouse2UpEvent, 
	kQueuedMouse3DownEvent, 
	kQueuedMouse3UpEvent, 
	kQueuedKeyDownEvent, 
	kQueuedKeyUpEvent, 
	kQueuedModifierDownEvent, 
	kQueuedModifierUpEvent, 
};

/*!
 * An event queue is maintained in order to emulate mouse clicks by multi-event
 * sequences. This represents an event in that queue. It is an essentially a
 * distillation from the NSEvent of the parts which will be relevant for RFB.
 * Note that a single @c NSEvent can produce multiple @c QueuedEvent instances, such
 * as releasing multiple modifier keys at once.
 */
@interface QueuedEvent : NSObject {
	QueuedEventType _eventType;
	NSPoint _location; //!< location in RFBView's coordinates
	NSTimeInterval _timestamp;
	unichar _character;
	NSEventModifierFlags _modifier;
}

// Creation
+ (QueuedEvent *)mouseDownEventForButton: (int)buttonNumber
								location: (NSPoint)location
							   timestamp: (NSTimeInterval)timestamp;
+ (QueuedEvent *)mouseUpEventForButton: (int)buttonNumber
							  location: (NSPoint)location
							 timestamp: (NSTimeInterval)timestamp;
+ (QueuedEvent *)keyDownEventWithCharacter: (unichar)character
								 timestamp: (NSTimeInterval)timestamp;
+ (QueuedEvent *)keyUpEventWithCharacter: (unichar)character
							   timestamp: (NSTimeInterval)timestamp;
+ (QueuedEvent *)modifierDownEventWithCharacter: (NSEventModifierFlags)modifier
								 timestamp: (NSTimeInterval)timestamp;
+ (QueuedEvent *)modifierUpEventWithCharacter: (NSEventModifierFlags)modifier
							   timestamp: (NSTimeInterval)timestamp;

// Event Attributes
@property (readonly) QueuedEventType type;

//! location in RFBView's coordinates
@property (readonly) NSPoint locationInWindow;

@property (readonly) NSTimeInterval timestamp;
@property (readonly) unichar character;
@property (readonly) NSEventModifierFlags modifier;

@end
