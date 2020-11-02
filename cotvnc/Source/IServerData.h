//
//  IServerData.h
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

#import <Foundation/Foundation.h>

/** Implementers of IServerData will send this notification when a property has changed */
extern NSNotificationName const ServerChangeNotification;
#define ServerChangeMsg ServerChangeNotification

typedef NS_ENUM(int, SUPPORT_TYPE)
{
	EDIT_ADDRESS,
	EDIT_PORT,
	EDIT_NAME,
	EDIT_PASSWORD,
	CONNECT,
};

@class Profile;

@protocol ServerDelegate <NSObject>

- (void)serverResolvedWithHost: (NSString *)host port: (int)port;
- (void)serverDidNotResolve;

@end

@protocol IServerData <NSObject>

- (bool)doYouSupport: (SUPPORT_TYPE)type;

@property (readonly, copy) NSString *name;
@property (readwrite, nonatomic, copy) NSString *host;
@property (readwrite, copy) NSString *password;
@property (readonly, nonatomic) BOOL rememberPassword;
@property (readwrite) int port;
@property (readwrite) bool shared;
@property (readwrite) bool fullscreen;
@property (readwrite) bool viewOnly;
@property (readwrite, strong) Profile *profile;
@property (readonly) bool addToServerListOnConnect;
@property (readonly, copy) NSString *sshHost;
@property (readonly) in_port_t sshPort;
@property (readonly, copy) NSString *sshUser;
- (void)resolveWithDelegate: (id <ServerDelegate>)delegate;

- (void)setHost: (NSString*)host;
- (BOOL)setHostAndPort: (NSString*)host;
- (void)setPassword: (NSString*)password;
- (void)setDisplay: (int)display;
- (void)setPort: (int)port;
- (void)setShared: (bool)shared;
- (void)setFullscreen: (bool)fullscreen;
- (void)setViewOnly: (bool)viewOnly;
- (void)setProfile: (Profile *)profile;

- (void)copyServer: (id<IServerData>)server;

@optional
- (void)setRememberPassword: (BOOL)rememberPassword;

@end
