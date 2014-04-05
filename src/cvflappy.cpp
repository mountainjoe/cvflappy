#include <stdio.h>

#include <limits>

#include <opencv2/opencv.hpp>

using namespace cv; 


static int global_threshold = 160;

static Rect findPhoneScreen(Mat frame) {
  // convert to HSV


  return Rect(0,0,0,0); 
}

static Rect processFrame(Mat frame) {
  // convert to HSV
  
  Mat hsv; 

  cvtColor(frame, hsv, CV_BGR2HSV); 

  // pick V as my monochrome matrix
  Mat value(hsv.rows, hsv.cols, CV_8UC1); 
  // theoretically takes 3rd channel of input and makes it 1st channel of output
  int from_to[] = { 2,0 }; 
  mixChannels(&hsv, 1, &value, 1, from_to, 1); 

  // threshold
  Mat thr; 
  threshold(value, thr, global_threshold, 255, CV_THRESH_BINARY); 

  imshow("proc", thr); 
  //
  // find contours
  //

  vector< vector<Point> > contours; 
  vector<Vec4i> hierarchy; 
  findContours(thr, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0)); 

  vector< vector<Point> > contours_poly(contours.size());

  Point2f imageCenter(frame.cols/2, frame.rows/2); 
  double leastContourArea = std::numeric_limits<double>::max(); 
  int bestIndex = -1; 

  // shouldn't there be a foreach-style syntax? 
  for (int i=0; i < contours.size(); ++i) {
    approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true); 

    if (pointPolygonTest(contours_poly[i], imageCenter, false) > 0) {
      // inside! 
      double area = contourArea(contours_poly[i]); 
      if (area < leastContourArea) {
        bestIndex = i; 
        leastContourArea = area; 
      }
    }
  }
  if (bestIndex < 0) {
    return Rect(0,0,0,0); // we filter on area==0 later
  }

  // now I want to pick the contour closest to the center of the image. 

  // I want the contour of least area which contains the center of the image. 


  // draw contours on frame
  for (int i=0; i < contours.size(); ++i) {
    Scalar red(255,0,0); 
    Scalar blue(0,0,255); 

    drawContours(frame, contours, i, (i==bestIndex) ? red : blue, 2, 8, hierarchy, 0, Point()); 
  }

  // and here we pick the rectangle we'll crop with for future processing
  Rect bound = boundingRect( Mat(contours_poly[bestIndex]) );
  rectangle(frame, bound.tl(), bound.br(), Scalar(0,255,0), 2, 8, 0); 

  return bound; 
}

static void trackbar_callback(int value, void* ignored) {
  printf("Trackbar value: %d\n", value); 
} 

static void runOpenCv() {
  VideoCapture cap(0); 
  if (!cap.isOpened())
    return; 

  namedWindow("proc"); 
  createTrackbar("Threshold", "proc", &global_threshold, 255, trackbar_callback); 

  for (;;) {
    Mat frame; 

    cap >> frame; 
    // for convenience, make the images smaller. Get detail later. 
    resize(frame, frame, Size(frame.cols/2, frame.rows/2)); 


    //Rect screen = findPhoneScreen(frame); 

    /* want to draw 'screen' rectangle onto 'frame' */

    Rect screenBound = processFrame(frame); 
    imshow("frame", frame); 

#if 0
    if (screenBound.area() > 0) {
      // crop our frame and display that separately
      Mat cropped = frame(screenBound); 
      imshow("cropped", cropped); 
    }
#endif 

    if (waitKey(1) >= 0) 
      break;
  }

  // creepy c++ auto-destroys VideoCapture object
  return; 
}

int main(int argc, char **argv) {

  runOpenCv(); 

  return 0; 

}
