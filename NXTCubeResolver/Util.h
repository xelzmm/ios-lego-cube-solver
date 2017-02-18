//
//  Util.h
//  NXTCubeResolver
//
//  Created by xelz on 2017/2/18.
//  Copyright © 2017年 xelz. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Util : NSObject

+(NSData *) btDataForNxtWithString: (NSString*)string;
+(NSData *) btUTFDataForNxtWithString: (NSString*)string;
+(NSString *)btDataFromNxtWithBytes: (const uint8_t *) bytes length: (NSUInteger) size;

@end
