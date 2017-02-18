//
//  NXTCubeResolverTests.m
//  NXTCubeResolverTests
//
//  Created by xelz on 2017/2/11.
//  Copyright © 2017年 xelz. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "cube.h"

@interface NXTCubeResolverTests : XCTestCase

@end

@implementation NXTCubeResolverTests

- (void)setUp {
    [super setUp];
    
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testTwoPhase {
    NSLog(@"Init two-phase.");
    init();
    NSLog(@"Init done.");
    char *solution = solvecube("FUUUUDRBULBLLRDURBBRBLFFUFFBRRLDUFBDDLDDLBDDRFFLFBRLUR");
    NSLog(@"Solution: %@", [[NSString alloc]initWithUTF8String: solution]);
    free(solution);
    solution = NULL;
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
