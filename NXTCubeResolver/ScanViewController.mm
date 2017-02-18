//
//  ScanViewController.m
//  NXTCubeResolver
//
//  Created by xelz on 2017/2/11.
//  Copyright © 2017年 xelz. All rights reserved.
//

#import "ScanViewController.h"
#import "squares.h"
#import "cube.h"
#import <opencv2/imgproc/imgproc.hpp>
#import "Util.h"

@interface ScanViewController ()

@end

@implementation ScanViewController


- (void)initCamera {
    videoCamera = [[CvVideoCamera alloc] initWithParentView:self.videoView];
    videoCamera.delegate = self;
    videoCamera.defaultAVCaptureDevicePosition = AVCaptureDevicePositionBack;
    videoCamera.defaultAVCaptureSessionPreset = AVCaptureSessionPresetMedium;
    videoCamera.defaultFPS = 12;
    videoCamera.defaultAVCaptureVideoOrientation = AVCaptureVideoOrientationPortrait;
    videoCamera.grayscaleMode = NO;
    previewGray = false;
    shouldPickupColor = YES;
    facelets = @"DFUBLR";
    
    element = getStructuringElement( MORPH_ELLIPSE,
                                    cv::Size( 3, 3 ),
                                    cv::Point( 1, 1 ) );
    Mat img(180, 240, CV_8UC4, Scalar(255, 255, 255, 32));
    rectangle(img, cv::Rect(60, 0, 60, 60), Scalar(255,0,0,255), CV_FILLED);
    rectangle(img, cv::Rect(0, 60, 60, 60), Scalar(0,255,0,255), CV_FILLED);
    rectangle(img, cv::Rect(60, 60, 60, 60), Scalar(0,0,255,255), CV_FILLED);
    rectangle(img, cv::Rect(120, 60, 60, 60), Scalar(255,255,0,255), CV_FILLED);
    rectangle(img, cv::Rect(180, 60, 60, 60), Scalar(0,255,255,255), CV_FILLED);
    rectangle(img, cv::Rect(60, 120, 60, 60), Scalar(255,0,255,255), CV_FILLED);
    UIImage *image = [self UIImageFromCVMat:img];
    //    self.cubeColorView.backgroundColor = [[UIColor alloc]initWithPatternImage:image];
    self.cubeColorView.image = image;
    cube = Mat(180, 240, CV_8UC4, Scalar(255, 255, 255, 32));
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self.manager addListener:self];
    self.manager.rfcommDelegate = self;
    [self initCamera];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) processImage:(cv::Mat &)image {
    vector<vector<cv::Point> > squares;
    vector<Scalar> scalars;
    static int pauseFrameCount = 0;
    float cannyFilterThreshold = 50;
    
    if(pauseFrameCount) {
        //        image = tmpMat.clone();  // this doesn't work right
        tmpMat.copyTo(image);
        pauseFrameCount--;
        return;
    }
    
    cv::Mat gray;
    gray = image.clone();
    //    cvtColor(image, gray, CV_BGR2GRAY);
    //    blur(gray, gray, cv::Size(3, 3));
    Canny(gray, gray, cannyFilterThreshold, cannyFilterThreshold * 3, 3);
    dilate(gray, gray, element);
    if(previewGray) {
        Canny(image, image, cannyFilterThreshold, cannyFilterThreshold * 3, 3);
        dilate(image, image, element);
    }
    //    blur(image, image, cv::Size(10, 10));
    findAndDrawSquares(image, gray, squares, scalars);
    if(squares.size() == 9 && shouldPickupColor) {
        shouldPickupColor = NO;
        tmpMat = image.clone();
        pauseFrameCount = videoCamera.defaultFPS;
        [self pickupColors:scalars];
        //        [videoCamera stop];
        //        dispatch_time_t delay = dispatch_time(DISPATCH_TIME_NOW, NSEC_PER_SEC * 3);
        //        dispatch_after(delay, dispatch_get_main_queue(), ^(void){
        //            [videoCamera start];
        //        });
    }
}


/*
 *              |U***********|
 *              |*08**07**06*|
 *              |************|
 *              |*05**04**03*|
 *              |************|
 *              |*02**01**00*|
 *              |************|
 * |L***********|F***********|R***********|B***********|
 * |*47**50**53*|*35**34**33*|*38**41**44*|*09**10**11*|
 * |************|************|************|************|
 * |*46**49**52*|*32**31**30*|*37**40**43*|*12**13**14*|
 * |************|************|************|************|
 * |*45**48**51*|*29**28**27*|*36**39**42*|*15**16**17*|
 * |************|************|************|************|
 *              |D***********|
 *              |*26**25**24*|
 *              |************|
 *              |*23**22**21*|
 *              |************|
 *              |*20**19**18*|
 *              |************|
 * Facelet sequence U R F D L B
 * Scan sequence U B D F R L
 */
- (void) pickupColors: (vector<Scalar> &)scalars {
    if(scalars.size() != 9) return;
    printf("currentFacelet: %d\n", currentFacelet);
    for(int i = 0; i < scalars.size(); i++) {
        printf("color %d: %f, %f, %f\n", i, scalars[i].val[2], scalars[i].val[1], scalars[i].val[0]);
        colorNode node;
        node.i = currentFacelet * 9 + i;
        node.scalar = scalars[i];
        node.color = 'U';
        colorNodes.push_back(node);
    }
    cv::Point origin;
    switch(currentFacelet) {
        case 0: // U
        case 3: // F
        case 2: // D
            origin = currentFacelet == 0 ? cv::Point(60, 0) :
            currentFacelet == 3 ? origin = cv::Point(60, 60) : cv::Point(60, 120);
            for(int y = 0; y < 3; y++) {
                for(int x = 0; x < 3; x++) {
                    Scalar s = scalars[8 - y * 3 - x];
                    rectangle(cube,
                              cv::Rect(origin.x + x * 20, origin.y + y * 20, 20, 20),
                              Scalar(s[2], s[1], s[0], 255),
                              CV_FILLED);
                }
            }
            break;
        case 4: // R
        case 5: // L
            origin = currentFacelet == 4 ? cv::Point(120, 60) : cv::Point(0, 60);
            for(int y = 0; y < 3; y++) {
                for(int x = 0; x < 3; x++) {
                    Scalar s = scalars[x * 3 + 2 - y];
                    rectangle(cube,
                              cv::Rect(origin.x + x * 20, origin.y + y * 20, 20, 20),
                              Scalar(s[2], s[1], s[0], 255),
                              CV_FILLED);
                }
            }
            break;
        case 1:
            origin = cv::Point(180, 60);
            for(int y = 0; y < 3; y++) {
                for(int x = 0; x < 3; x++) {
                    Scalar s = scalars[y * 3 + x];
                    rectangle(cube,
                              cv::Rect(origin.x + x * 20, origin.y + y * 20, 20, 20),
                              Scalar(s[2], s[1], s[0], 255),
                              CV_FILLED);
                }
            }
            break;
    }
    currentFacelet++;
    if(currentFacelet == 6) {
        NSString* state = [self detectColors];
        NSLog(@"cube state: %@", state);
        [videoCamera stop];
        char* solution = solvecube([state UTF8String]);
        NSString* solutionString = [[NSString alloc]initWithUTF8String: solution];
        free(solution);
        solution = NULL;
        solutionString = [solutionString stringByReplacingOccurrencesOfString:@"1" withString:@""];
        solutionString = [solutionString stringByReplacingOccurrencesOfString:@"3" withString:@"'"];
        NSLog(@"Solution: %@", solutionString);
        [self.manager sendRFCOMMPacket:[Util btUTFDataForNxtWithString:[@"SOLUTION: " stringByAppendingString:solutionString]] ForConnectionId:self.btConnectionId];
        [[[UIAlertView alloc] initWithTitle:@"Solution" message:solutionString delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil] show];
        [self.manager sendRFCOMMPacket:[Util btUTFDataForNxtWithString:@"EXIT"] ForConnectionId:self.btConnectionId];
    } else {
        [self.manager sendRFCOMMPacket:[Util btUTFDataForNxtWithString:[facelets substringWithRange:NSMakeRange(currentFacelet, 1)]] ForConnectionId:self.btConnectionId];
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        self.cubeColorView.image = [self UIImageFromCVMat:cube];
    });
}

bool sortForWhite(const colorNode & colorNode1, const colorNode & colorNode2) {
    Scalar s1 = colorNode1.scalar, s2 = colorNode2.scalar;
    return s1[0] + s1[1] + s1[2] > s2[0] + s2[1] + s2[2];
}

bool sortForBlue(const colorNode & colorNode1, const colorNode & colorNode2) {
    Scalar s1 = colorNode1.scalar, s2 = colorNode2.scalar;
    return s1[0] - s1[1] - s1[2] > s2[0] - s2[1] - s2[2];
}

bool sortForGreen(const colorNode & colorNode1, const colorNode & colorNode2) {
    Scalar s1 = colorNode1.scalar, s2 = colorNode2.scalar;
    return s1[1] - s1[0] - s1[2] > s2[1] - s2[0] - s2[2];
}

//bool sortForYellow(const colorNode & colorNode1, const colorNode & colorNode2) {
//    Scalar s1 = colorNode1.scalar, s2 = colorNode2.scalar;
//    return s1[1] + s1[2] - s1[0] > s2[1] + s2[2] - s2[0];
//}

bool restoreInputSequence(const colorNode & colorNode1, const colorNode & colorNode2) {
    return colorNode1.i < colorNode2.i;
}

//bool sortForRed(const colorNode & colorNode1, const colorNode & colorNode2) {
//    Scalar s1 = colorNode1.scalar, s2 = colorNode2.scalar;
//    return s1[0] - s1[1] - s1[2] > s2[0] - s2[1] - s2[2];
//}

- (NSString *) detectColors {
    sort(colorNodes.begin(), colorNodes.end(), sortForWhite); // W X X X X X
    sort(colorNodes.begin() + 9 , colorNodes.end(), sortForGreen); // W G X X X X
    sort(colorNodes.begin() + 18 , colorNodes.end(), sortForBlue); // W G B
    //    sort(colorNodes.begin() + 27 , colorNodes.end(), sortForYellow);
    //    sort(colorNodes.begin() + 36 , colorNodes.end(), sortForBlue);
    //
    char colors[] = "WWWWWWWWWGGGGGGGGGBBBBBBBBBRRRRRRRRROOOOOOOOOYYYYYYYYY";
    for(int i = 0; i < colorNodes.size(); i ++) {
        colorNodes[i].color = colors[i];
        
    }
    sort(colorNodes.begin(), colorNodes.end(), restoreInputSequence);
    map<char, char> colorMap;
    colorMap[colorNodes[4].color] = 'U';
    colorMap[colorNodes[13].color] = 'B';
    colorMap[colorNodes[22].color] = 'D';
    colorMap[colorNodes[31].color] = 'F';
    colorMap[colorNodes[40].color] = 'R';
    colorMap[colorNodes[49].color] = 'L';
    
    int convertTable[] = {
        8,7,6,5,4,3,2,1,0,
        38,41,44,37,40,43,36,39,42,
        35,34,33,32,31,30,29,28,27,
        26,25,24,23,22,21,20,19,18,
        47,50,53,46,49,52,45,48,51,
        9,10,11,12,13,14,15,16,17
    };
    
    char state[55];
    state[54] = 0;
    printf("============================\n");
    for(int i = 0; i < colorNodes.size(); i ++) {
        state[i] = colorMap[colorNodes[convertTable[i]].color];
        printf("color %d: %c %f, %f, %f\n", i, colorNodes[i].color, colorNodes[i].scalar.val[2], colorNodes[i].scalar.val[1], colorNodes[i].scalar.val[0]);
    }
    return [[NSString alloc]initWithCString:state encoding: NSUTF8StringEncoding];
}

- (IBAction)changePreviewWhenTap:(UILongPressGestureRecognizer *)sender {
    switch (sender.state) {
        case UIGestureRecognizerStateBegan:
            previewGray = true;
            break;
        case UIGestureRecognizerStateEnded:
            previewGray = false;
            break;
        default:
            break;
    }
}

- (IBAction)pickupColorsWhenTap:(UITapGestureRecognizer *)sender {
//    if(currentFacelet < 6)
//        shouldPickupColor = YES;
}

- (BOOL)shouldAutorotate {
    return NO;
}

- (void) viewDidAppear:(BOOL)animated {
    [videoCamera start];
}

- (void) viewWillDisappear:(BOOL)animated {
    [videoCamera stop];
}


// When converting from cv::Mat to UIImage, I had to swap the red and blue color channels.
// Since the default order in opencv is bgr but UIImage color space is rgb
// Usually you need to convert color space with: cvtColor( image, image, CV_BGR2RGB); which will drop the alpha channel
// but what I do here is directly give (R, G, B, A) to Scalar(B, G, R, A) format, so I didn't have to convert it
-(UIImage *)UIImageFromCVMat:(cv::Mat)cvMat
{
    //    cvtColor( cvMat, cvMat, CV_BGR2RGB);
    NSData *data = [NSData dataWithBytes:cvMat.data length:cvMat.elemSize()*cvMat.total()];
    CGColorSpaceRef colorSpace;
    
    if (cvMat.elemSize() == 1) {
        colorSpace = CGColorSpaceCreateDeviceGray();
    } else {
        colorSpace = CGColorSpaceCreateDeviceRGB();
    }
    
    CGDataProviderRef provider = CGDataProviderCreateWithCFData((__bridge CFDataRef)data);
    
    CGImageAlphaInfo alphaInfo = cvMat.elemSize() == 4 ? kCGImageAlphaLast : kCGImageAlphaNone;
    // Creating CGImage from cv::Mat
    CGImageRef imageRef = CGImageCreate(cvMat.cols,                                 //width
                                        cvMat.rows,                                 //height
                                        8,                                          //bits per component
                                        8 * cvMat.elemSize(),                       //bits per pixel
                                        cvMat.step[0],                              //bytesPerRow
                                        colorSpace,                                 //colorspace
                                        alphaInfo | kCGBitmapByteOrderDefault,      // bitmap info
                                        provider,                                   //CGDataProviderRef
                                        NULL,                                       //decode
                                        false,                                      //should interpolate
                                        kCGRenderingIntentDefault                   //intent
                                        );
    
    
    // Getting UIImage from CGImage
    UIImage *finalImage = [UIImage imageWithCGImage:imageRef];
    CGImageRelease(imageRef);
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(colorSpace);
    
    return finalImage;
}

-(void) rfcommDataReceivedForConnectionID:(uint16_t)connectionID withData:(uint8_t *)packet ofLen:(uint16_t)size {
    NSString* recv = [Util btDataFromNxtWithBytes:packet length:size];
    if ([recv isEqualToString:@"DONE"]) {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            shouldPickupColor = YES;
        });
    }
}

-(void) rfcommConnectionClosedForConnectionID:(uint16_t)connectionId {
    NSLog(@"Bluetooth RFCOMM Connection %hu Closed!!!", connectionId);
    exit(0);
}

/*
 #pragma mark - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 */

@end
