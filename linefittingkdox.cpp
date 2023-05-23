/**
 * @file main.cpp
 * @brief This program calculates the mean squared error and regression line for a set of data points.
 */

#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>

using namespace std::chrono;

using namespace std;

/**
 * @struct Line
 * @brief A struct representing a line in slope-intercept form (y = mx + b).
 */
struct Line
{
    double y_intercept; /**< The y-intercept of the line. */
    double slope; /**< The slope of the line. */
    int st; /**< The start index of the line. */
    int ed; /**< The end index of the line. */
};

/**
 * @brief Calculates the mean squared error (MSE) between two vectors of values.
 *
 * @param y_pred The vector of predicted values.
 * @param y_actual The vector of actual values.
 *
 * @return The MSE between the two vectors.
 */
double calculate_mse(vector<double> y_pred, vector<double> y_actual) {
    int n = y_pred.size();

    // calculate the difference between predicted and actual values
    vector<double> diff(n);
    for(int i=0; i<n; i++) {
        diff[i] = y_pred[i] - y_actual[i];
    }

    // calculate the squared error
    double squared_error = 0;
    for(int i=0; i<n; i++) {
        squared_error += pow(diff[i], 2);
    }

    // calculate the mean squared error
    double mse = squared_error / n;
    return mse;
}

/**
 * @brief Calculates the regression line for a set of data points.
 *
 * @param x The vector of x-values.
 * @param y The vector of y-values.
 * @param st The start index of the line.
 * @param ed The end index of the line.
 *
 * @return A Line struct representing the regression line for the given set of data points.
 */
Line calculate_regression_line(vector<double> x, vector<double> y,int st,int ed) {
    int n = ed+1;
    if(st==ed)
    {
        Line L;L.slope=0;L.y_intercept=y[st];return L;
    }

    // calculate the mean of x and y
    double x_mean = 0;
    double y_mean = 0;
    for(int i=st; i<n; i++) {
        x_mean += x[i];
        y_mean += y[i];
    }
    x_mean /= n;
    y_mean /= n;

    // calculate the slope and y-intercept
    double numerator = 0;
    double denominator = 0;
    for(int i=st; i<n; i++) {
        numerator += (x[i] - x_mean) * (y[i] - y_mean);
        denominator += (x[i] - x_mean) * (x[i] - x_mean);
    }
    double slope = numerator / denominator;
    double y_intercept = y_mean - slope * x_mean;

    // create and return a Line struct representing the regression line
    Line L;
    L.slope = slope;
    L.y_intercept = y_intercept;
    return L;
}
/**

@brief Finds the optimal value for the given set of x and y values using dynamic programming algorithm.

@param x The set of x values.

@param y The set of y values.

@return A vector containing vectors of Line objects representing the optimal lines.
*/
vector<vector<Line>> optimal(vector<double> x, vector<double> y)
{
vector<vector<Line>> v; //Vector to store optimal lines
vector<Line> v2; //Vector to store lines
Line l; //Line object
l.slope=0; //Assigning slope
l.y_intercept=y[0]; //Assigning y-intercept
l.st=0; //Assigning starting point
l.ed=0; //Assigning ending point
v2.push_back(l); //Pushing line into vector
v.push_back(v2); //Pushing vector into vector of vectors

int p=2; //Variable to store value of p
int n=x.size(); //Variable to store size of x vector

vector<double> error(n,0); //Vector to store error values

//Implementation of dynamic programming algorithm
for(int i=1;i<n;i++)
{
int ind=-1; //Variable to store index
Line op=calculate_regression_line(x,y,0,i); //Line object to store regression line for all points from 0 to i
op.st=0; //Assigning starting point
op.ed=i; //Assigning ending point
 vector<double> ypred; //Vector to store predicted values of y
 vector<double> y1; //Vector to store actual values of y
 for(int j1=0;j1<=i;j1++)
 {
     ypred.push_back(op.slope*x[j1]+op.y_intercept); //Calculating predicted value of y
     y1.push_back(y[j1]); //Pushing actual value of y into vector
 }
 double m=calculate_mse(ypred,y1)+p; //Calculating mean squared error

 for(int j=0;j<i;j++)
 {
     Line op1=calculate_regression_line(x,y,j+1,i); //Line object to store regression line for all points from j+1 to i
     op1.st=j+1; //Assigning starting point
     op1.ed=i; //Assigning ending point

     vector<double> ypred1; //Vector to store predicted values of y
     vector<double> y2; //Vector to store actual values of y
     for(int j1=j+1;j1<=i;j1++)
     {
         ypred.push_back(op.slope*x[j1]+op.y_intercept); //Calculating predicted value of y
         y1.push_back(y[j1]); //Pushing actual value of y into vector
     }
     double m1=calculate_mse(ypred,y1)+p+error[j]; //Calculating mean squared error

     if(m1<m)
     {
         ind=j; //Storing the index
         m=m1; //Updating the mean squared error
         op=op1; //Storing the regression line
     }
 }
 vector<Line> v3;
 if(ind!=-1)
 {
     v3=v[ind];
 }
 v3.push_back(op); //Pushing the optimal line into vector
 v.push_back(v3); //Pushing the vector into vector of vectors
}
return v;
}
/**

@file main.cpp
@brief This file reads input from a file, calculates optimal lines using a dynamic programming algorithm,
and prints the lines and time taken by the algorithm.
*/


/**

@brief This function reads input from a file, calculates optimal lines using a dynamic programming algorithm,
and returns a vector of vector of Line objects.
@param x Vector of x-coordinates
@param y Vector of y-coordinates
@return Vector of vector of Line objects
*/

int main()
{
vector<double> x;
vector<double> y;
std::string line;
std::ifstream myfile("input3.txt"); // replace example.txt with your file name

if (myfile.is_open()) { // check if file is open
    while (std::getline(myfile, line)) { // read each line using getline
       int fi = line.find(' ');
       string sl1 = line.substr(0, fi);
       string sl2 = line.substr(fi + 1);
       x.push_back(stod(sl1));
       y.push_back(stod(sl2));
    }
    myfile.close(); // close the file
}
else {
    std::cout << "Unable to open file";
}

//starting timer
auto start = high_resolution_clock::now();

//calculating optimal lines using function optimal
vector<vector<Line>> v = optimal(x, y);

auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);

cout << "Time taken by algorithm: "
     << duration.count() << " microseconds" << endl;
//ending timer and printing it
//printing the decomposition just for our reference

for(int i = 0; i < v[v.size() - 1].size(); i++)
{
    cout<<"y="<<v[v.size() - 1][i].slope<<"X+"<<v[v.size() - 1][i].y_intercept<<"["<<v[v.size() - 1][i].st<<","<<v[v.size() - 1][i].ed<<"]"<<endl;
}

return 0;
}













