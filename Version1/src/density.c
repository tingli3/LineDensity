#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double lineLength(double x, double y, double r, double * lineSegX1, double * lineSegY1, double * lineSegX2, double * lineSegY2, int lineSegCount) {

	double lLen = 0;
	double segLen = 0;
	double x1, y1, x2, y2;
	double dis1, dis2;

	double plDis;

	//Variables for vector calcuation
	double bL;
	double aX, aY;
	double bX, bY;
	double beX, beY;

	for(int i = 0; i < lineSegCount; i++) {
		x1 = lineSegX1[i];
		y1 = lineSegY1[i];
		x2 = lineSegX2[i];
		y2 = lineSegY2[i];

		if(x1 != x2 || y1 != y2) {

			dis1 = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
			dis2 = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));

			segLen = 0;	
	
			if(dis1 < r) {
				if(dis2 < r) {
					segLen = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
				}
				else {
					bL = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
					plDis = fabs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1) / bL;	
					aX = x - x1;
					aY = y - y1;
					beX = (x2 - x1) / bL;
					beY = (y2 - y1) / bL;

					segLen = sqrt(r * r - plDis * plDis) + aX * beX + aY * beY;
				}
			}
			else {
				if(dis2 < r) {
					bL = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
					plDis = fabs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1) / bL;	
					aX = x - x2;
					aY = y - y2;
					beX = (x1 - x2) / bL;
					beY = (y1 - y2) / bL;

					segLen = sqrt(r * r - plDis * plDis) + aX * beX + aY * beY;
				
				}
				else {
					bL = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
					plDis = fabs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1) / bL;	
			
					if(plDis < r) {
						if(dis1 < dis2) {
							aX = x - x1;
							aY = y - y1;
							bX = x2 - x1;
							bY = y2 - y1;					
						}
						else {
							aX = x - x2;
							aY = y - y2;
							bX = x1 - x2;
							bY = y1 - y2;
						}
						if(aX * bX + aY * bY > 0) {
							segLen = 2 * sqrt(r * r - plDis * plDis);
						}
					}
				}
			}	

			lLen += segLen;
		}	
	}

	return lLen;
}

void lineDensityRaster(float * density, int nRow, int nCol, double xMin, double yMax, double cellSize, double r, double * lineSegX1, double * lineSegY1, double * lineSegX2, double * lineSegY2, int lineSegCount) {

	double x, y;
	double area = M_PI * r * r;

	for(int i = 0; i < nRow; i ++) {
		
		y = yMax - cellSize * (i + 0.5);
		for(int j = 0; j < nCol; j++) {
		
			x = xMin + cellSize * (j + 0.5);
		
			density[i * nCol + j] = (float)(lineLength(x, y, r, lineSegX1, lineSegY1, lineSegX2, lineSegY2, lineSegCount) / area);
		}
	}	
}
