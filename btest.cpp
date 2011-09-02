#include <iostream>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
using namespace std;
#include "bezier.h"


Bezier testSpline;

int main(int argc, char* argv[])
{ 
	
	// Load control points from file
	if (argc > 1)
		testSpline.loadFile(&argv[1]);
	else {
		cout << "Please specify an input file";
		return 0;
	}
	
	// Create canvas	
	IplImage* inputFrame;
	if (argc > 2) { inputFrame = cvLoadImage(argv[1]); }
	else { inputFrame = cvCreateImage(cvSize(400,400),IPL_DEPTH_8U, 1); }
	
	// Draw splines
	int step = inputFrame->widthStep/sizeof(uchar);
	uchar* imgData = (uchar*) inputFrame->imageData;

	for (int t = 0; t < 1000; t++)
	{
	
		Point p = testSpline.getPoint(t);
		
		if (p.y > 500 || p.y < 0) p.y = 0;
		if (p.x > 500 || p.x < 0) p.x = 0;
		//cout << "X: " << p.x << "     Y: " << p.y << "\n";
		
		imgData[p.y*step+p.x] = 255;		
	}
	
	// Draw control points
	for (int j = 0; j < testSpline.getLength(); j++)
	{
	
		Point p = testSpline.getControlPoint(j);
		
		if (p.y > 500 || p.y < 0) p.y = 0;
		if (p.x > 500 || p.x < 0) p.x = 0;
		
		cvCircle(inputFrame, p, 5, Scalar(200,200,200));		
	}
		
	// Output control points
	testSpline.dumpPoints();
	
	// Display output
	namedWindow("Output", 1);
	imshow("Output", inputFrame);
	waitKey();	
	
	return 0; 

}



