/* AuthPrompt.m
 * Copyright (C) 2011 Dustin Cartwright
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

#import <AuthPrompt.h>

@implementation AuthPrompt {
    __weak NSWindow *parentWindow;
    NSArray *topLevelObjs;
}

- (id)initWithDelegate:(id<AuthPromptDelegate>)aDelegate
{
    if (self = [super init]) {
        delegate = aDelegate;
        NSArray *tlo;
        [[NSBundle mainBundle] loadNibNamed:@"AuthPrompt" owner:self topLevelObjects:&tlo];
        topLevelObjs = tlo;
    }
    return self;
}

- (void)runSheetOnWindow:(NSWindow *)window
{
    parentWindow = window;
    [window beginSheet:panel completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertSecondButtonReturn) {
            [self->delegate authCancelled];
        }
        [self->panel orderOut:self];
    }];
}

- (void)stopSheet
{
    [parentWindow endSheet:panel returnCode:NSModalResponseAbort];
}

- (IBAction)enterPassword:(id)sender
{
    [delegate authPasswordEntered:[passwordField stringValue]];
    [parentWindow endSheet:panel returnCode:NSAlertFirstButtonReturn];
}

- (IBAction)cancel:(id)sender
{
    [parentWindow endSheet:panel returnCode:NSAlertSecondButtonReturn];
}

@end
