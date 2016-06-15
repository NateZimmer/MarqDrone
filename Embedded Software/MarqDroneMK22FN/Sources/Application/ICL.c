/*
 * ICP.c
 *
 *  Created on: Mar 18, 2016
 *      Author: Z
 */

#include "ICL.h"
#include "Math.h"
#include "ICL_Test.h"

#define Iteration_Limit 10
#define Learning_Rate 1

#define POINTS 180


/*
 * Finds the 2 closest points in a array, puts the array index of these 2 points in index1 * index 2
 */

void Find_Two_Closest_Points(uint32_t * Index1, uint32_t * Index2, float InputX, float InputY, float * minJ, float * prev_X, float * prev_Y)
{
	float R_Min1 = 99999999999; // Big Compare Values
	float R_Min2 = 99999999999;
	float J = 0;
	for(int i = 0; i <POINTS; i++) // For the size of our arrays
	{

		if((prev_X[i] !=0)&&(prev_Y[i] !=0))
		{
			J = (InputX - prev_X[i])*(InputX - prev_X[i]) + (InputY - prev_Y[i])*(InputY - prev_Y[i]);

			if(J<R_Min1)
			{
				* Index2 = * Index1;
				* Index1 = i;
				R_Min2 = R_Min1;
				R_Min1 = J;
			}
			else if(J<R_Min2)
			{
				* Index2 = i;
				R_Min2 = J;
			}
		}
	}
	*minJ = R_Min1;
}

/*
 * ICL_For_A_Point
 */

void ICL_For_A_Point(float * DeltaX, float * DeltaY, float X_New, float Y_New, float * ArrayX, float * ArrayY, uint32_t * Valid_Points)
{
	uint32_t Index1 = 0; uint32_t Index2 = 0; float minCost = 0;

	if(Y_New*X_New==0) // If point is not valid.
	{

	}
	else
	{
		Find_Two_Closest_Points(&Index1, &Index2, X_New, Y_New,&minCost,ArrayX,ArrayY);

		if(minCost<(100.0*100.0))
		{
			float a = ArrayY[Index1] - ArrayY[Index2]; //General line form
			float b = ArrayX[Index2] - ArrayX[Index1];
			float c = (-b)*ArrayY[Index1] + (-a)*ArrayX[Index1];

			float delta_X = X_New - (b*(b*X_New - a*Y_New)-a*c)/(a*a+b*b); //Calculate error
			float delta_Y = Y_New - (a*(-b*X_New + a*Y_New)-b*c)/(a*a+b*b);

			*DeltaX = *DeltaX + delta_X; // Accumulate & store error
			*DeltaY = *DeltaY + delta_Y;
			*Valid_Points = *Valid_Points + 1;
		}
	}

}


/*
 * ICL: Function to be performed once 2 lidar complete datasets have been achieved
 */

void ICL(float * DeltaX, float * DeltaY, float * ArrayX, float * ArrayY, float * ArrayX2, float * ArrayY2)
{
	float DeltaXX = 0; float DeltaYY = 0; uint32_t Valid_Points = 0;
	for(int i=0; i<Iteration_Limit;i++)
	{
		for(int j = 0; j < POINTS; j++) // Perform ICL for our points
		{
			ICL_For_A_Point(&DeltaXX,&DeltaYY, ArrayX2[j] ,ArrayY2[j], ArrayX, ArrayY,&Valid_Points);
		}

		if(Valid_Points)
		{
			for(int j = 0; j < POINTS; j++) // Array subtraction
			{
				if(ArrayX2[j]*ArrayY2[j] !=0) // Only update valid points.
				{
					ArrayX2[j] = ArrayX2[j] - (DeltaXX)/((float)Valid_Points);
					ArrayY2[j] = ArrayY2[j] - (DeltaYY)/((float)Valid_Points);
				}

			}

			*DeltaX = *DeltaX + DeltaXX/((float)Valid_Points);
			*DeltaY = *DeltaY + DeltaYY/((float)Valid_Points);
		}

		DeltaXX = 0; DeltaYY = 0;Valid_Points = 0; // Reset Values

	}
}

float X_Distance = 0; float Y_Distance = 0 ;

void Run_ICL_Test()
{

	ICL(&X_Distance, &Y_Distance,X_ICL,Y_ICL, X_ICL2, Y_ICL2);

}




