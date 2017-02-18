//
//  BTConnectViewController.h
//  NXTCubeResolver
//
//  Created by xelz on 2017/2/17.
//  Copyright © 2017年 xelz. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BTstackManager.h"

@interface BTConnectViewController : UIViewController<BTstackManagerDelegate, BTstackManagerListener>

@property (weak, nonatomic) IBOutlet UITextField *addressTextField;
@property (weak, nonatomic) IBOutlet UIButton *connectButton;
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;

- (IBAction)connectButtonClicked:(UIButton *)sender;

@end
