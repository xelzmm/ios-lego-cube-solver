//
//  ViewController.h
//  BTStackTest
//
//  Created by xelz on 2017/2/16.
//  Copyright © 2017年 xelz. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BTstackManager.h"

@interface ViewController : UIViewController<BTstackManagerDelegate, BTstackManagerListener>

@property (weak, nonatomic) IBOutlet UITextView *textView;
@property BTstackManager* manager;
@property uint16_t channelId;
@end

