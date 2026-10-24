#include <iostream>
#include <vector>
#include <cmath>
// trying linear regression from scratch

using namespace std;

// both linear function y = mx+c and cost function everything is in one function named cost_function

double cost_function(std::vector<double> x, double m, double c, std::vector<double> y_og){
    int n = y_og.size();
    double a = 0;
    // going through the vector x and y in the main func
    for (int i=0; i<n; i++){
        // the linear function y = mx+c
        double lin = (m * x[i]) + c;
        // from here cost function - subtraction between calculated output and original output
        double dif = lin - y_og[i];
        // square the result
        double sub = std::pow(dif,2);
        // adding all the results in a final varibale
        a += sub;
    }
    // calculating final loss function
    double cst = a/(2*n);
    // return cst in case future me uses it and i did needed it
    return cst;
}

//gradient descent
void gradient_descent(const std::vector<double>& x,const std::vector<double>& y,double& m,double& c,double alpha){
    int n = x.size();
    // slope or m value
    double slope_differential = 0;
    // intercept or c value
    double intercept_differential = 0;

    /* Batch - Gradient Descent : This first calculates the entire dataset and then updates the slope and intercept
    // running the loop through once for the enitre dataset - batch gradient descent
    for(int i =0;i<n;i++){
            // gradient descent working
            double linear = (m * x[i] + c);
            slope_differential +=  (linear- y[i]) * x[i];
            intercept_differential += (linear - y[i]);

    }
    slope_differential /= n;
    intercept_differential /=n;
    //updating parameters outside the loop after the entire training dataset - batch gradient descent
    m = m - alpha * (slope_differential);
    c = c - alpha * (intercept_differential);
    */

    /* Stochastic Gradient Descent : different from batch gradient descent it calculates for single training example and updates the slope and intercept values
    requires less memory suitable for mid to high datasets */
    for (int j = 0; j<n;j++){
        double linear = (m * x[j] +c);
        slope_differential += (linear - y[j]) * x[j];
        intercept_differential += (linear - y[j]);
        slope_differential /= n;
        intercept_differential /=n;
        //Updating the parameters inside the loop for each training example - stochastic gradient descent
        m = m - alpha * (slope_differential );
        c = c - alpha * (intercept_differential);
    }
}

int main()
{
    // Input training variables x
    std::vector<double> x = {1,2,3,4,5};
    // Output trainign variables y
    std::vector<double> y = {6,7,8,9,10};
    // slope and intercept
    double m,c,epochs,alpha;
    std::cout << "Enter slope or m : "<<endl;
    std::cin >>m;
    std::cout << "Enter intercept or c : "<<endl;
    std::cin >>c;
    // calling the function
    std::cout << "Select epochs "<<endl;
    std::cin >> epochs;
    std::cout << "Enter alpha" <<endl;
    std::cin>> alpha;
    for (int i =0; i < epochs; i++){
        gradient_descent(x,y,m,c,alpha);
        if (i % 500 == 0){
                std::cout<<"Iteration "<< i <<" Cost "<< cost_function(x,m,c,y) <<" m is "<< m <<" c is "<< c <<endl; ;
        }
    }
    return 0;
}


