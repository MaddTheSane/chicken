//
//  ServerFromPrefs.m
//  Chicken of the VNC
//
//  Created by Jared McIntyre on Sat Jan 24 2004.
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

#import "ServerFromPrefs.h"
#import "IServerData.h"
#import "ProfileManager.h"
#import "ProfileDataManager.h"

#import <Foundation/Foundation.h>

@interface ServerBase ()

- (void)profileListUpdate:(NSNotification *)notification;

@end


@implementation ServerBase

- (id)init
{
	if( self = [super init] )
	{
        _host = @"localhost";
        _password = nil;
        _port = 5900;
        _shared = NO;
        _fullscreen = NO;
        _viewOnly = NO;
        _profile = [[ProfileDataManager sharedInstance] defaultProfile];

		[[NSNotificationCenter defaultCenter] addObserver:self
												 selector:@selector(profileListUpdate:)
													 name:ProfileListChangeMsg
												   object:[ProfileDataManager sharedInstance]];
	}
	
	return self;
}

- (void)dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (bool)doYouSupport: (SUPPORT_TYPE)type
{
	return NO;
}

- (NSString*)name
{
    return NSLocalizedString(@"RFBUntitledServerName", nil);
}

@synthesize host=_host;

- (BOOL)rememberPassword
{
    return NO;
}

@synthesize port=_port;
@synthesize shared=_shared;
@synthesize profile=_profile;
@synthesize fullscreen=_fullscreen;
@synthesize viewOnly=_viewOnly;
@synthesize sshPort=_sshPort;
@synthesize sshUser=_sshUser;

- (NSString *)sshString
{
    NSString    *str = _sshHost;

    if (_sshUser)
        str = [NSString stringWithFormat:@"%@@%@", _sshUser, str];

    if (_sshPort)
        str = [NSString stringWithFormat:@"%@:%d", str, _sshPort];

    return str;
}

- (void)resolveWithDelegate: (id <ServerDelegate>)delegate
{
    [delegate serverResolvedWithHost:_host port:_port];
}

- (void)setHost: (NSString*)host
{
	if( nil != host )
	{
        _host = [host copy];
	}
	else
	{
		_host = @"new server";
	}
}

- (BOOL)setHostAndPort: (NSString*)hostAndPort
{
    NSString    *strippedHost = [hostAndPort stringByTrimmingCharactersInSet:
                                    [NSCharacterSet whitespaceCharacterSet]];
	
    if( nil != hostAndPort )
    {
        if ([strippedHost hasPrefix: @"["]) {
            // IPv6 escaped notation, in which the host is surrounded by []
            NSRange endBracket = [strippedHost rangeOfString: @"]"];
            NSRange hostRange;

            hostRange.location = 1;
            if (endBracket.location == NSNotFound)
                hostRange.length = [strippedHost length] - 1;
            else
                hostRange.length = endBracket.location - 1;

            [self setHost: [strippedHost substringWithRange: hostRange]];
            
            if ([strippedHost length] > hostRange.length + 2
                    && [strippedHost characterAtIndex: hostRange.length + 2] == ':') {
                // port also specified in string
                NSString    *portStr;
                portStr = [strippedHost substringFromIndex: hostRange.length + 3];
                [self setPort: [portStr intValue]];
                return YES;
            } else
                return NO;
        } else {
            NSArray *items = [strippedHost componentsSeparatedByString:@":"];

            if ([items count] == 2) {
                // host:port format
                [self setHost: [items objectAtIndex: 0]];
                [self setPort: [[items objectAtIndex: 1] intValue]];
                return YES;
            } else {
                // Either no colons or IPv6 notation
                [self setHost: strippedHost];
                return NO;
            }
        }
    } else
        return NO;
}

@synthesize password=_password;

- (void)setDisplay: (int)display
{
    _port = display + PORT_BASE;
}

- (void)setProfileName: (NSString*)profileName
{
	ProfileDataManager* profileManager = [ProfileDataManager sharedInstance];
    Profile *prof = [profileManager profileForKey:profileName];
	
    if (prof)
	{
		_profile = [prof copy];
	}
}

@synthesize sshHost=_sshHost;

- (void)setSshString:(NSString *)str
{
    NSRange sep;

    if (str == nil) {
        _sshHost = nil;
        _sshPort = 0;
        _sshUser = nil;
        return;
    }

    sep = [str rangeOfString:@"@"];
    if (sep.location != NSNotFound) {
        _sshUser = [str substringToIndex:sep.location];
        str = [str substringFromIndex:sep.location + 1];
    } else
        _sshUser = nil;

    sep = [str rangeOfString:@":"];
    if (sep.location != NSNotFound) {
        _sshPort = [[str substringFromIndex: sep.location + 1] intValue];
        str = [str substringToIndex:sep.location];
    } else
        _sshPort = 0;

    _sshHost = [str copy];
}

- (void)setSshTunnel:(BOOL)enable
{
    if (!enable) {
        _sshHost = nil;
        _sshUser = nil;
        _sshPort = 0;
    } else if (_sshHost == nil) {
        _sshHost = _host;
    }
}

- (void)profileListUpdate:(NSNotification *)notification
{
	ProfileDataManager* profileManager = [ProfileDataManager sharedInstance];
	
	if( ![profileManager profileWithNameExists: [_profile profileName]] )
	{
		[self setProfile:[profileManager defaultProfile]];
        [[NSNotificationCenter defaultCenter] postNotificationName:ServerChangeMsg
                                                            object:self];
	}
}

- (void)copyServer: (id<IServerData>)server
{
    [self setHost:[server host]];
    [self setPort:[server port]];
	[self setPassword:[server password]];
    _shared = [server shared];
    _fullscreen = [server fullscreen];
    _viewOnly = [server viewOnly];
    [self setProfile:[server profile]];
}

- (bool)addToServerListOnConnect
{
	return NO;
}

@end
