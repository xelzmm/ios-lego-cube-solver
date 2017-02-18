//
//  BTConnectViewController.m
//  NXTCubeResolver
//
//  Created by xelz on 2017/2/17.
//  Copyright © 2017年 xelz. All rights reserved.
//

#import "BTConnectViewController.h"
#import <btstack/btstack.h>
#import "Util.h"
#import "ScanViewController.h"
#import "cube.h"

@interface BTConnectViewController () {
    uint16_t btConnectionId;
}

@property uint16_t channelId;
@property BTstackManager* manager;
@property BOOL connected;

@end

@implementation BTConnectViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self performSelectorInBackground:@selector(init2phase) withObject:nil];
    self.channelId = 0x01;
    self.manager = [BTstackManager sharedInstance];
//    self.manager.delegate = self;
    self.manager.rfcommDelegate = self;
    [self.manager addListener:self];
    self.statusLabel.text = @"Bluetooth Activating...";
    [self.manager activate];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
    if([segue.identifier isEqualToString:@"goToScan"]) {
        ScanViewController* scanViewController = (ScanViewController*)segue.destinationViewController;
        scanViewController.manager = self.manager;
        scanViewController.btConnectionId = btConnectionId;
        [self.manager removeListener:self];
        self.manager.rfcommDelegate = nil;
    }
}

- (void)init2phase {
    NSLog(@"Init two-phase.");
    init();
    NSLog(@"Init done.");
    //    char *solution = solvecube("FUUUUDRBULBLLRDURBBRBLFFUFFBRRLDUFBDDLDDLBDDRFFLFBRLUR");
    //    NSLog(@"Solution: %@", [[NSString alloc]initWithUTF8String: solution]);
    //    free(solution);
    //    solution = NULL;
}

// BTstackManagerDelegate
//- (void) btstackManager:(BTstackManager *)manager
//   handlePacketWithType:(uint8_t)packet_type
//             forChannel:(uint16_t)channel
//                andData:(uint8_t *)packet
//                withLen:(uint16_t)size {
//    NSLog(@"packet_type: %02x channel: %02x packet: %@", packet_type, channel, [NSData dataWithBytes:packet length:size]);
//}

- (IBAction)connectButtonClicked:(UIButton *)sender {
    if (!self.connected) {
        [[[UIAlertView alloc] initWithTitle:@"Warning!" message:@"Bluetooth not ACTIVATED!\nPlease wait..." delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil] show];
        return;
    }
    bd_addr_t addr;
    NSString* addrString = self.addressTextField.text;
    NSRegularExpression *addrRegex = [NSRegularExpression regularExpressionWithPattern:@"[0-9a-fA-F]{12}" options:kNilOptions error:nil];
    if (![addrRegex firstMatchInString:addrString options:kNilOptions range:NSMakeRange(0, [addrString length])]) {
        [[[UIAlertView alloc] initWithTitle:@"Warning!" message:@"NXT Address not valid!" delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil] show];
        return;
    }
    const char* addrCString = addrString.UTF8String;
    sscanf(addrCString, "%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", &addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]);
    self.statusLabel.text = @"Connecting NXT...";
    [self.manager createRFCOMMConnectionAtAddress:&addr withChannel:self.channelId authenticated:NO];
}

- (void) activatedBTstackManager:(BTstackManager *)manager {
    NSLog(@"Bluetooth Activated!");
    self.statusLabel.text = @"Bluetooth Activated!";
    self.connected = YES;
}

-(void) rfcommConnectionCreatedAtAddress:(bd_addr_t)addr forChannel:(uint16_t)channel asID:(uint16_t)connectionId {
    NSLog(@"Bluetooth RFCOMM Connection 0x%02X created.", connectionId);
    btConnectionId = connectionId;
    self.statusLabel.text = @"Authenticating...";
    [self.manager sendRFCOMMPacket:[Util btDataForNxtWithString:@"CUBE"] ForConnectionId:connectionId];
}

-(void) rfcommDataReceivedForConnectionID:(uint16_t)connectionID withData:(uint8_t *)packet ofLen:(uint16_t)size {
    NSString* recv = [Util btDataFromNxtWithBytes:packet length:size];
    if ([recv isEqualToString:@"CUBE"]) {
        self.statusLabel.text = @"Authenticated!";
        [self performSegueWithIdentifier:@"goToScan" sender:self];
    }
}

-(void) rfcommConnectionClosedForConnectionID:(uint16_t)connectionId {
    NSLog(@"Bluetooth RFCOMM Connection %hu Closed!!!", connectionId);
    self.statusLabel.text = @"Connection Failed!";
}

@end
