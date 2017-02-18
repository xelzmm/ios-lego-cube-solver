//
//  ScanViewController.h
//  NXTCubeResolver
//
//  Created by xelz on 2017/2/11.
//  Copyright © 2017年 xelz. All rights reserved.
//

#import <opencv2/opencv.hpp>
#import <opencv2/highgui/cap_ios.h>
#import "BTstackManager.h"

#import <UIKit/UIKit.h>

using namespace cv;

struct colorNode{
    Scalar scalar;
    int i;
    char color;
};

@interface ScanViewController : UIViewController <CvVideoCameraDelegate, BTstackManagerListener> {
    CvVideoCamera* videoCamera;
    Mat element;
    Mat tmpMat;
    Mat cube;
    BOOL previewGray;
    BOOL shouldPickupColor;
    int currentFacelet;
    vector<colorNode> colorNodes;
    NSString* facelets;
}

@property (weak, nonatomic) IBOutlet UIView *videoView;
@property (weak, nonatomic) IBOutlet UIImageView *cubeColorView;
@property BTstackManager* manager;
@property uint16_t btConnectionId;

- (IBAction)changePreviewWhenTap:(UILongPressGestureRecognizer *)sender;
- (IBAction)pickupColorsWhenTap:(UITapGestureRecognizer *)sender;

@end
