//
//  squares.h
//  NXT Cuber
//
//  Created by xelz on 15-1-20.
//  Copyright (c) 2015年 xelz. All rights reserved.
//

#ifndef __NXT_Cuber__squares__
#define __NXT_Cuber__squares__

// The "Square Detector" program.
// It loads several images sequentially and tries to find squares in
// each image

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <math.h>
#include <algorithm>

#endif /* defined(__NXT_Cuber__squares__) */

using namespace cv;
using namespace std;

void findAndDrawSquares(Mat& image, Mat& gray, vector<vector<cv::Point> >& squares, vector<Scalar>& scalars);