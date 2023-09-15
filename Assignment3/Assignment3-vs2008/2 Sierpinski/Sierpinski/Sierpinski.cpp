/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
#include <cmath>
using namespace std;

/* draws 3 lines as regular triangle */
void drawTriangle(GWindow& window, double x0, double y0, double edgeLength){
	GPoint p1 = window.drawPolarLine(x0, y0, edgeLength, -120);
	GPoint p2 = window.drawPolarLine(p1, edgeLength, 0);
	window.drawPolarLine(p2, edgeLength, 120);
}

/* returns height of regular triangle for given edge length */
double calculateTriangleHeight(double edgeLength){
	double result = (double) sqrt(edgeLength*edgeLength - edgeLength/2.0 * edgeLength/2.0);
	return result;
}

/* recursion */
void drawSierpinskiTrianglesRec(GWindow& window,double x0, double y0, double edgeLength, int order){
	// base case
	if(order == 0) drawTriangle(window, x0, y0, edgeLength); 
	else {
		order--;
		edgeLength /= 2;
		drawSierpinskiTrianglesRec(window, x0, y0, edgeLength, order);
		x0 -= edgeLength/2;
		y0 += calculateTriangleHeight(edgeLength);
		drawSierpinskiTrianglesRec(window, x0, y0, edgeLength, order);
		x0 += 2 * edgeLength/2;
		drawSierpinskiTrianglesRec(window, x0, y0, edgeLength, order);
	}
}

/* wrapper function for recursion */
void drawSierpinskiTriangles(GWindow& window, double edgeLength, int order){
	double x0 = window.getWidth()/2;
	double triangleHeight = calculateTriangleHeight(edgeLength);
	double y0 = window.getHeight()/2 - triangleHeight/2;
	drawSierpinskiTrianglesRec(window, x0, y0, edgeLength, order);
}

/* main function */
int main() {
	GWindow window;

	double edgeLength = getInteger("Enter triangle side length: ");
	int fractalOrder = getInteger("Enter fractal order: ");

	drawSierpinskiTriangles(window, edgeLength, fractalOrder);

    return 0;
}
