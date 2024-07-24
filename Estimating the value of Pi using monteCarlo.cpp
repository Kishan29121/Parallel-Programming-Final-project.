 #include <cstdlib>
#include <iostream>
 using namespace std;
//Function to find estimated 
//value of Pi
//using Monte Carlo algorithm.
 void monteCarlo(int N, int K)
 {
    //Stores X and Y Coordinates
    //of a random point.
    double x,y;


    //Stores distance of a random point from origin.
    double d;
    
    //Stores number of points lying inside a circle.
    int points_in_Circle = 0;


    //Stores number of points lying inside a square.
    int points_in_Square = 0;
    int i = 0;


//Paralle calculation of random points lying inside a circle.
#pragma omp parallel firstprivate(x, y, d, i) reduction(+ : pCircle, pSquare) num_threads(K)
    {
        //Intializes a random points with a seed.
        srand48((int)time(NULL));
        for (i = 0; i < N; i++)
        {
            //Finds random X-coordinate.
            x = (double)drand48();

            //Finds random Y-Coordinate.
            y = (double)drand48();
            //Finds the square of distance of point (x, y) from origin.
            d = ((x * x) + (y * y));
            //If d is less than or equal to 1.
            if (d <= 1)
            {
                //Increment pCircle by 1.

                points_in_Circle++;
            }
            //Increment pSquare by 1.
            points_in_Square++;
        }
    } 

    //Stores the estimated value of Pi.
    double pi = 4.0 * ((double)points_in_Circle / (double)(points_in_Square));

    //Prints the value of Pi.
    cout << "Final Estimation of Pi ="<< pi;

 }

//Driver code.
 int main()
 {
    //Input.
    int N = 100000;
    int K = 8;


    //Function call.
    monteCarlo(N, K);
 }