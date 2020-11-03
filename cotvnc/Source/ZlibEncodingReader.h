//
//  ZlibEncodingReader.h
//  Chicken of the VNC
//
//  Created by Helmut Maierhofer on Wed Nov 06 2002.
//  Copyright (c) 2002 Helmut Maierhofer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <zlib.h>
#import "EncodingReader.h"

@class ZlibStreamReader;
@class ByteReader;

@interface ZlibEncodingReader : EncodingReader
{
	ByteReader			*numBytesReader;
    ZlibStreamReader    *zlibReader;
}

- (unsigned)maximumUncompressedSize;
- (void)setUncompressedData:(NSData *)data;

@end
