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

#import "FrameBuffer.h"
@class EventFilter, RFBConnection, Profile;


@interface RFBView : NSView <NSDraggingDestination>
{
    __weak RFBConnection   *_delegate;
    EventFilter     *_eventFilter;
    NSCursor        *_modifierCursor;
    NSCursor        *_serverCursor; //!< cursor sent by server, if any
    FrameBuffer     *fbuf;
    NSColor         *tint;
    BOOL            drawTint;
}

- (void)setFrameBuffer:(FrameBuffer*)aBuffer;
@property (nonatomic, strong) FrameBuffer *frameBuffer;
@property (nonatomic, weak) RFBConnection *delegate;
- (void)drawRect:(NSRect)aRect;

- (void)setCursorTo: (NSString *)name;
//! cursor sent by server, if any.
@property (nonatomic, strong, setter=setServerCursorTo:) NSCursor *serverCursor;
- (void)setServerCursorTo: (NSCursor *)aCursor;

@property (nonatomic, strong) NSColor *tint;

- (void)concludeDragOperation:(id <NSDraggingInfo>)sender;
- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender;
- (void)draggingExited:(id <NSDraggingInfo>)sender;
- (NSDragOperation)draggingUpdated:(id <NSDraggingInfo>)sender;
- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender;
- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender;

@end
