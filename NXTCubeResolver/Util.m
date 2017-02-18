//
//  Util.m
//  NXTCubeResolver
//
//  Created by xelz on 2017/2/18.
//  Copyright © 2017年 xelz. All rights reserved.
//

#import "Util.h"

@implementation Util

+(NSData *) btDataForNxtWithString: (NSString*)string {
    const void* bytes = string.UTF8String;
    NSInteger length = string.length;
    u_int8_t* data = malloc(length + 2);
    data[0] = length & 0xff;
    data[1] = (length >> 8) & 0xff;
    memcpy(data + 2, bytes, length);
    NSData* _data = [NSData dataWithBytes:data length:length + 2];
    free(data);
    NSLog(@"Send Data: %@", _data);
    return _data;
}

+(NSData *) btUTFDataForNxtWithString: (NSString*)string {
    const char* bytes = string.UTF8String;
    NSInteger utfLen = strlen(bytes);
    u_int8_t* data = malloc(utfLen + 4);
    data[3] = utfLen & 0xff;
    data[2] = (utfLen >> 8) & 0xff;
    NSInteger dataLen = utfLen + 2;
    data[0] = dataLen & 0xff;
    data[1] = (dataLen >> 8) & 0xff;
    memcpy(data + 4, bytes, utfLen);
    NSData* _data = [NSData dataWithBytes:data length:dataLen + 2];
    free(data);
    NSLog(@"Send Data: %@", _data);
    return _data;
}

+(NSString *)btDataFromNxtWithBytes: (const uint8_t *) bytes length: (NSUInteger) size {
    if(size < 2) return nil;
    NSUInteger length = bytes[0] + (bytes[1] << 8);
    if(size < length + 2) return nil;
    char* data = malloc(length + 1);
    data[length] = 0;
    memcpy(data, bytes + 2, length);
    NSString* string =  [NSString stringWithCString:data encoding:NSISOLatin1StringEncoding];
    NSLog(@"Received Data: %@", string);
    return string;
}

@end
