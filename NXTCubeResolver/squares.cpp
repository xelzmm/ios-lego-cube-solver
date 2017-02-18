//
//  squares.cpp
//  NXT Cuber
//
//  Created by xelz on 15-1-20.
//  Copyright (c) 2015年 xelz. All rights reserved.
//

#include "squares.h"

int thresh = 50, N = 11;

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// helper function:
// get the distance of to point
double distance(cv::Point pt1, cv::Point pt2) {
    double dx = pt1.x - pt2.x;
    double dy = pt1.y - pt2.y;
    return sqrt(dx * dx + dy * dy);
}

// helper function:
// compare two square's location
bool compareTwoPointsWithY(vector<cv::Point>& s1, vector<cv::Point>& s2) {
    return s1[0].y < s2[0].y;
}
bool compareTwoPointsWithX(vector<cv::Point>& s1, vector<cv::Point>& s2) {
    return s1[0].x < s2[0].x;
}

// helper function:
// determain whether one square contains or contained by another
// return 1 if s1 contains s2 and -1 versa, 0 indicates no overlap
int squareContains(vector<cv::Point>& s1, vector<cv::Point>& s2) {
    // center point of the diagonal line
    cv::Point c1 = cv::Point((s1[0].x + s1[2].x) / 2, (s1[0].y + s1[2].y) / 2);
    cv::Point c2 = cv::Point((s2[0].x + s2[2].x) / 2, (s2[0].y + s2[2].y) / 2);
    bool s2ins1 = pointPolygonTest(s1, c2, false) >= 0;
    bool s1ins2 = pointPolygonTest(s2, c1, false) >= 0;
    
    if(s2ins1 && s1ins2) { // overlap
        if(distance(s1[0], s1[2]) > distance(s2[0], s2[2])) { // s1 contains s2
            return 1;
        } else {
            return -1;
        }
    } else if(s2ins1) {
        return 1;
    } else if(s1ins2) {
        return -1;
    } else {
        return 0;
    }
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
void findSquares( Mat& image, vector<vector<cv::Point> >& squares )
{
//    printf("=============================");
    squares.clear();
    
//    Mat pyr, timg, gray0(image.size(), CV_8U), gray;
    
    // down-scale and upscale the image to filter out the noise
//    pyrDown(image, pyr, cv::Size(image.cols/2, image.rows/2));
//    pyrUp(pyr, timg, image.size());
    vector<vector<cv::Point> > contours;

    // find squares in every color plane of the image
//    for( int c = 0; c < 3; c++ )
//    {
//        int ch[] = {c, 0};
//        mixChannels(&timg, 1, &gray0, 1, ch, 1);
//        mixChannels(&image, 1, &gray0, 1, ch, 1);
    
        // try several threshold levels
//        for( int l = 2; l < 5; l++ )
//        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
//            if( l == 0 )
//            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
//                Canny(gray0, gray, 0, 100, 5);
                // dilate canny output to remove potential
                // holes between edge segments
//                dilate(gray, gray, Mat(), cv::Point(-1,-1));
//            }
//            else
//            {
//                dilate(gray0, gray0, Mat(), cv::Point(-1,-1));
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
//                gray = gray0 >= (l+1)*255/N;
//            }
            // find contours and store them all as a list
            findContours(image, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
            
            vector<cv::Point> approx;
            
            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.05, true);
                
                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if( approx.size() == 4 &&
                   fabs(contourArea(Mat(approx))) > 1000 &&
                   isContourConvex(Mat(approx)) )
                {
                    double maxCosine = 0;
                    
                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }
                    
                    double lineLength1 = distance(approx[0], approx[1]);
                    double lineLength2 = distance(approx[1], approx[2]);
                    
                    
                    // if cosines of all angles are small and border length almost equals
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    // then filter out big squares such as the whole facelet of the cube
                    if( maxCosine < 0.1
                       && fabs(lineLength1 - lineLength2) / MAX(lineLength1, lineLength2) < 0.1
                       && lineLength1 / image.cols < 0.3) {
                        
                        if(squares.empty()) {
                            squares.push_back(approx);
                        } else {
                            for(vector<vector<cv::Point>>::iterator s = squares.begin(); s < squares.end(); s++) {
                                int contains = squareContains(*s, approx);
                                if (contains == 1){ //s contains approx
//                                    printf("s contains approx\n");
                                    squares.erase(s);
                                    squares.push_back(approx);
                                    break;
                                } else if(contains == -1) { // approx contains s
//                                    printf("approx contains s\n");
                                    break; // discard this approx
                                } else {
                                    if (s == squares.end() - 1) {
                                        squares.push_back(approx);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
//        }
//    }
//    printf("found %lu squares\n", squares.size());

    if(squares.size() != 9) {
        squares.clear();
    } else {
        // sort squares to sequence
        // 0 1 2
        // 3 4 5
        // 6 7 8
        sort(squares.begin(), squares.end(), compareTwoPointsWithY);
        sort(squares.begin()+0, squares.begin()+3, compareTwoPointsWithX);
        sort(squares.begin()+3, squares.begin()+6, compareTwoPointsWithX);
        sort(squares.begin()+6, squares.begin()+9, compareTwoPointsWithX);
    }
}


// the function draws all the squares in the image
void drawSquares( Mat& image, const vector<vector<cv::Point> >& squares, vector<Scalar>& scalars)
{
    double minBorderLength = DBL_MAX, borderLength;
    for( int i = 0; i < squares.size(); i++) {
        minBorderLength = MIN(minBorderLength, distance(squares[i][0], squares[i][1]));
    }
    for( int i = 0; i < squares.size(); i++ )
    {
        cv::Point center = cv::Point((squares[i][0].x + squares[i][2].x) / 2, (squares[i][0].y + squares[i][2].y) / 2);
        const cv::Point* pcenter = &center, *p = &squares[i][0];
        int n = (int)squares[i].size();
        
        // get mean color of the square
        Mat mask = Mat::zeros(image.size(), CV_8UC1);
        drawContours(mask, squares, i, Scalar(255), CV_FILLED);
        if((borderLength = distance(squares[i][0], squares[i][1])) / minBorderLength >= 1.18) {
//            printf("border ratio: %f\n", borderLength / minBorderLength);
            double erodeSize = borderLength / 3;
            erode(mask, mask, getStructuringElement( MORPH_RECT,
                                                    cv::Size( erodeSize, erodeSize ),
                                                    cv::Point( 1, 1 )));
        }
        Scalar meanScalar = mean(image, mask);
        scalars.push_back(meanScalar);
        
        drawContours(image, squares, i, meanScalar, CV_FILLED);
        polylines(image, &p, &n, 1, true, Scalar::all(255), 2, CV_AA);
        Scalar inverseScalar = Scalar(255 - meanScalar[0],255 - meanScalar[1],255 - meanScalar[2], 255);
        putText(image,
                to_string(i),
                *pcenter,
                FONT_HERSHEY_PLAIN,
                2,
                inverseScalar,
                3);
//        printf("%f, %f, %f\n", inverseScalar[0], inverseScalar[1], inverseScalar[2]);
    }
}

void findAndDrawSquares(Mat& image, Mat& gray, vector<vector<cv::Point> >& squares, vector<Scalar>& scalars) {
    findSquares(gray, squares);
    drawSquares(image, squares, scalars);
}