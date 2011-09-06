/*
 * bezier.cpp
 *
 * Bezier spline library for OpenCV (C++ only)
 * Author: Nate Fisher, nate.scott.fisher@gmail.com
 *
 */

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <cv.h>
#include <fstream>

using namespace std;
#include "bezier.h"

/* 	Bezier() 
*
* 	Constructor for Bezier object
*/
Bezier::Bezier(){}

/* 	setControlPoints() 
*
* 	@input CvMat
* 
*	Loads the control points for a cubic Bezier
*/
void Bezier::setControlPoints(CvMat* input)
{
	this->controlPoints = input;
}

/* 	getLength() 
*
*	Returns the number of control points in the spline as an integer
*/
int Bezier::getLength()
{
	return this->length;
}

/* 	getControlPoint() 
*
*	@input int
*
*	Returns a Point object with coordinates for a particular control point given by p
*/
Point Bezier::getControlPoint(int p)
{

	Point output; 
	
 	CvMat* spline = this->controlPoints; 	

	output.x = *((float*) CV_MAT_ELEM_PTR(*spline, 1, p));
	output.y = *((float*) CV_MAT_ELEM_PTR(*spline, 1, p) + spline->step);
	
	return output;
		
}

/* 	dumpPoints() 
*
*	Outputs all control points in spline to stdout
*/
void Bezier::dumpPoints()
{

 	CvMat* spline = this->controlPoints; 	
 	
	for (int i = 1; i < this->length; i++)
	{
		cout << "X(" << i << "): " << *((float*) CV_MAT_ELEM_PTR(*spline, 1, i));
		cout << "\tY: " << *((float*) CV_MAT_ELEM_PTR(*spline, 1, i) + spline->step) << "\n";
	}
	
}

/* 	loadFile() 
*
*	@input char*
*
*	Loads a text file with coordinates as float values, separated by commas
*	Each point should be on a new line
*/
void Bezier::loadFile(char* filename[])
{

	int lines = 1; 
	float points[2][1000];

	FILE* fp;
	fp = fopen (*filename, "r");
	fscanf(fp, "%f,%f", &points[0][0], &points[1][0]);
	
	while(fscanf(fp, "%f,%f", &points[0][lines], &points[1][lines]) == 2)
		lines++;
	
	//close file
	fclose(fp);
	
	// set length property to number of control points
	this->length = lines;
	
	// create CvMat object
	CvMat* input = cvCreateMat(lines, lines, CV_32FC2);
	
	// load CvMat with coordinates
	for(int i = 0; i < lines; i++)
	{
		*((float*) CV_MAT_ELEM_PTR(*input, 1, i)) = points[0][i];
		*((float*) CV_MAT_ELEM_PTR(*input, 1, i)+input->step) = points[1][i];
	}
	
	this->controlPoints = input;
	
}

/* 	getPoint() 
*
*	@input int
*
*	Returns a Point object with coordinates for a particular station on the spline given by t
*/
Point Bezier::getPoint(int t)
{
	Point output;

 	CvMat* spline = this->controlPoints; 	
 	
 	int splineCount = this->length/4;
 	int currSpline = (int) ((t/1000.0f) * (float) splineCount);
 	int splineShare = 1000/splineCount;
 	float step = (t % splineShare) / (float)splineShare;
 	int CP[2][4];
 	
	for (int i = currSpline*4; i < (currSpline+1)*4; i++)
	{
		CP[0][i] = (int) *((float*) CV_MAT_ELEM_PTR(*spline, 1, i));
		CP[1][i] = (int) *((float*) CV_MAT_ELEM_PTR(*spline, 1, i) + spline->step);
	}
	
	int cx = 3 * (CP[0][1] - CP[0][0]);
	int bx = 3 * (CP[0][2] - CP[0][1]) - cx;
	int ax = CP[0][3] - CP[0][0] - cx - bx;
	
	int cy = 3 * (CP[1][1] - CP[1][0]);
	int by = 3 * (CP[1][2] - CP[1][1]) - cy;
	int ay = CP[1][3] - CP[1][0] - cy - by;

	output.x = (int) (ax*step*step*step + bx*step*step + cx*step + CP[0][0]);
	output.y = (int) (ay*step*step*step + by*step*step + cy*step + CP[1][0]);
		
	return output;
}

