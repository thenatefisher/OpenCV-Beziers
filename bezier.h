/*
 * bezier.cpp
 *
 * Bezier spline library for OpenCV (C++ only)
 * Author: Nate Fisher, nate.scott.fisher@gmail.com
 *
 */

#ifndef BEZIER_H
#define BEZIER_H

#include <stdio.h>
#include <cv.h>

using namespace cv;

class Bezier 
{

	private:

	CvMat* controlPoints;

	int length;

	public:

	Bezier();

	Point getPoint(int t);

	void setControlPoints(CvMat* input);

	int getLength();

	Point getControlPoint(int p);

	void loadFile(char* filename[]);

	void cvPlot();

	IplImage cvImage();

	void dumpPoints();
		
};

#endif
