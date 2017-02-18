//
//  ViewController.m
//  BTStackTest
//
//  Created by xelz on 2017/2/16.
//  Copyright © 2017年 xelz. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.manager = [BTstackManager sharedInstance];
    self.manager.delegate = self;
    [self.manager addListener: self];
    self.manager.rfcommDelegate = self;
    self.channelId = 0x01;
    [self.manager activate];
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) btstackManager:(BTstackManager *)manager
   handlePacketWithType:(uint8_t)packet_type
             forChannel:(uint16_t)channel
                andData:(uint8_t *)packet
                withLen:(uint16_t)size {
    NSLog(@"packet_type: %02x channel: %02x packet: %@", packet_type, channel, [NSData dataWithBytes:packet length:size]);
}

- (void) activatedBTstackManager:(BTstackManager *)manager {
    NSLog(@"Bluetooth Activated!");
    [self log:@"Bluetooth Activated!"];
    uint8_t addr[] = {0x00, 0x16, 0x53, 0x11, 0xc2, 0xcd};
    [self.manager createRFCOMMConnectionAtAddress:&addr withChannel:self.channelId authenticated:YES];
}

-(void) rfcommConnectionCreatedAtAddress:(bd_addr_t)addr forChannel:(uint16_t)channel asID:(uint16_t)connectionId {
    NSLog(@"Bluetooth RFCOMM Connection %hu created.", connectionId);
    [self log:@"Bluetooth RFCOMM Connection created."];
    [self.manager sendRFCOMMPacket:[self btDataForNxtWithBytes:"CUBE" length:4] ForConnectionId:connectionId];
    [self log:@"Hello sent!"];
}

-(void) rfcommDataReceivedForConnectionID:(uint16_t)connectionID withData:(uint8_t *)packet ofLen:(uint16_t)size {
    NSLog(@"Bluetooth RFCOMM Data received: %@", [NSData dataWithBytes:packet length:size]);
}

-(void) rfcommConnectionClosedForConnectionID:(uint16_t)connectionId {
    NSLog(@"Bluetooth RFCOMM Connection %hu Closed!!!", connectionId);
    [self log:@"Bluetooth RFCOMM Connection Closed!!!"];
}


-(NSData *) btDataForNxtWithBytes: (const void *) bytes length: (NSUInteger) length {
    u_int8_t* data = malloc(length + 2);
    data[0] = length & 0xff;
    data[1] = (length >> 8) & 0xff;
    memcpy(data + 2, bytes, length);
    NSData* _data = [NSData dataWithBytes:data length:length + 2];
    free(data);
    NSLog(@"Send Data: %@", _data);
    return _data;
}

-(void) log: (NSString*) msg {
    self.textView.text = [[self.textView.text stringByAppendingString:msg] stringByAppendingString:@"\n"];
}

@end
