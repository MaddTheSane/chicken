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

#import "RFBView.h"
#import "EventFilter.h"
#import "RFBConnection.h"
#import "FrameBuffer.h"
#import "Profile.h"
//#import "RectangleList.h"

@implementation RFBView

/*! One-time initializer to read the cursors into memory. */
+ (NSCursor *)_cursorForName: (NSString *)name
{
	static NSDictionary *sMapping = nil;
    static dispatch_once_t onceToken;
	dispatch_once(&onceToken, ^{
		NSBundle *mainBundle = [NSBundle mainBundle];
		NSDictionary *entries = [NSDictionary dictionaryWithContentsOfURL: [mainBundle URLForResource: @"cursors" withExtension: @"plist"]];
		NSParameterAssert( entries != nil );
		NSMutableDictionary *mapping = [[NSMutableDictionary alloc] init];
		
		for (NSString *cursorName in entries )
		{
			NSDictionary *cursorEntry = [entries objectForKey: cursorName];
			NSString *localPath = [cursorEntry objectForKey: @"localPath"];
			NSImage *image = [NSImage imageNamed:localPath];
			
			int hotspotX = [[cursorEntry objectForKey: @"hotspotX"] intValue];
			int hotspotY = [[cursorEntry objectForKey: @"hotspotY"] intValue];
			NSPoint hotspot = {hotspotX, hotspotY};
			
			NSCursor *cursor = [[NSCursor alloc] initWithImage: image hotSpot: hotspot];
			[mapping setObject: cursor forKey: cursorName];
		}
		sMapping = [mapping copy];
	});
	
	return [sMapping objectForKey: name];
}

- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent
{
    return NO;
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

@synthesize frameBuffer=fbuf;

- (void)setFrameBuffer:(id)aBuffer;
{
    NSRect f = [self frame];
    
    fbuf = aBuffer;
    f.size = [aBuffer size];
    [self setFrame:f];
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)setCursorTo: (NSString *)name
{
	if (name == nil)
        _modifierCursor = nil;
    else
        _modifierCursor = [[self class] _cursorForName: name];
    [[self window] invalidateCursorRectsForView: self];
}

- (void)setServerCursor: (NSCursor *)aCursor
{
    _serverCursor = aCursor;
    if (!_modifierCursor)
        [[self window] invalidateCursorRectsForView: self];
}

@synthesize serverCursor=_serverCursor;

- (void)setTint: (NSColor *)aTint
{
    if (![tint isEqual:aTint]) {
        tint = aTint;
        drawTint = [tint alphaComponent] != 0.0;
        [self setNeedsDisplay:YES];
    }
}

@synthesize tint;

- (void)setDelegate:(RFBConnection *)delegate
{
    _delegate = delegate;
	_eventFilter = [_delegate eventFilter];
	[self setCursorTo: nil];
	[self setPostsFrameChangedNotifications: YES];
	[[NSNotificationCenter defaultCenter] addObserver: _delegate selector: @selector(viewFrameDidChange:) name: NSViewFrameDidChangeNotification object: self];
}

@synthesize delegate=_delegate;

- (void)drawRect:(NSRect)destRect
{
    NSRect          b = [self bounds];
    const NSRect    *rects;
    NSInteger       numRects;
    NSInteger       i;

    /* We always draw the framebuffer at scale. However, on a "Retina" display,
     * there are 4 pixels for each point. By default, the OS will interpolate
     * for us, but we don't want that. We want to draw "large" pixels. */
    [[NSGraphicsContext currentContext]
        setImageInterpolation:NSImageInterpolationNone];

    if (drawTint)
        [tint setFill];

    [self getRectsBeingDrawn:&rects count:&numRects];
    for (i = 0; i < numRects; i++) {
        NSRect      r = rects[i];
        r.origin.y = b.size.height - NSMaxY(r);
        [fbuf drawRect:r at:rects[i].origin];
        if (drawTint)
			NSRectFillUsingOperation(rects[i], NSCompositingOperationSourceOver);
    }
}

/* Called by system to set-up cursors for this view */
- (void)resetCursorRects
{
    if ([_delegate viewOnly])
        return;

    NSRect cursorRect;
    cursorRect = [self visibleRect];
    if (_modifierCursor)
        [self addCursorRect: cursorRect cursor: _modifierCursor];
    else if (_serverCursor)
        [self addCursorRect: cursorRect cursor: _serverCursor];
    else
        [self addCursorRect: cursorRect cursor: [[self class] _cursorForName: @"rfbCursor"]];
}

- (void)mouseDown:(NSEvent *)theEvent
{  [_eventFilter mouseDown: theEvent];  }

- (void)rightMouseDown:(NSEvent *)theEvent
{  [_eventFilter rightMouseDown: theEvent];  }

- (void)otherMouseDown:(NSEvent *)theEvent
{  [_eventFilter otherMouseDown: theEvent];  }

- (void)mouseUp:(NSEvent *)theEvent
{  [_eventFilter mouseUp: theEvent];  }

- (void)rightMouseUp:(NSEvent *)theEvent
{  [_eventFilter rightMouseUp: theEvent];  }

- (void)otherMouseUp:(NSEvent *)theEvent
{  [_eventFilter otherMouseUp: theEvent];  }

- (void)mouseEntered:(NSEvent *)theEvent
{  [[self window] setAcceptsMouseMovedEvents: YES];  }

- (void)mouseExited:(NSEvent *)theEvent
{  [[self window] setAcceptsMouseMovedEvents: NO];  }

- (void)mouseMoved:(NSEvent *)theEvent
{  [_eventFilter mouseMoved: theEvent];  }

- (void)mouseDragged:(NSEvent *)theEvent
{  [_eventFilter mouseDragged: theEvent];
   [_delegate mouseDragged: theEvent];}

- (void)rightMouseDragged:(NSEvent *)theEvent
{  [_eventFilter rightMouseDragged: theEvent];  }

- (void)otherMouseDragged:(NSEvent *)theEvent
{  [_eventFilter otherMouseDragged: theEvent];  }

- (void)scrollWheel:(NSEvent *)theEvent
{  [_eventFilter scrollWheel: theEvent];  }

- (void)keyDown:(NSEvent *)theEvent
{  [_eventFilter keyDown: theEvent];  }

- (void)keyUp:(NSEvent *)theEvent
{  [_eventFilter keyUp: theEvent];  }

- (void)flagsChanged:(NSEvent *)theEvent
{  [_eventFilter flagsChanged: theEvent];  }


- (void)concludeDragOperation:(id <NSDraggingInfo>)sender {}

- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender
{
    return NSDragOperationGeneric;
}

- (void)draggingExited:(id <NSDraggingInfo>)sender {}

- (NSDragOperation)draggingUpdated:(id <NSDraggingInfo>)sender
{
    return NSDragOperationGeneric;
}

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender
{
    return [_delegate pasteFromPasteboard:[sender draggingPasteboard]];
}

- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender
{
    return YES;
}

@end
