#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cctype>

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
void batch_gradient_descent(const std::vector<double>& x,const std::vector<double>& y,double& m,double& c,double alpha,int n){
    // slope or m value
    double slope_differential = 0;
    // intercept or c value
    double intercept_differential = 0;

    // Batch - Gradient Descent : This first calculates the entire dataset and then updates the slope and intercept
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

}
void stochastic_gradient_descent(const std::vector<double>& x, const std::vector<double>& y, double& m,double& c,double alpha,int n){
    //Stochastic Gradient Descent : different from batch gradient descent it calculates for single training example and updates the slope and intercept values
    //requires less memory suitable for mid to high
       // slope or m value
    double slope_differential = 0;
    // intercept or c value
    double intercept_differential = 0;
    for (int j = 0; j<n;j++){
        double linear = (m * x[j] +c);
        slope_differential += (linear - y[j]) * x[j];
        intercept_differential += (linear - y[j]);
        //Updating the parameters inside the loop for each training example - stochastic gradient descent
        m = m - alpha * (slope_differential );
        c = c - alpha * (intercept_differential);
    }
}

void mini_batch_gradient_descent(const std::vector<double>& x,const std::vector<double>& y, double& m,double& c, double alpha,int batch_size,int n){
    /* mini batch gradient descent */
      //outer loop is for each batch
    for (int start_idx = 0; start_idx < n; start_idx += batch_size){
        double slope_differential = 0;
        double intercept_differential = 0;
        // to define end of a batch using batch size and starting index
        int end_idx = std::min(start_idx + batch_size,n);
        // inner loop is for the real work
        for (int k = start_idx; k < end_idx;k++){
            double linear_minibatch = (m * x[k] + c);
            slope_differential += (linear_minibatch - y[k]) * x[k];
            intercept_differential += (linear_minibatch - y[k]);
        }
        // for dividing
        int current_batch_size = end_idx - start_idx;

        slope_differential /= current_batch_size;
        intercept_differential /= current_batch_size;
        // update rule is outside the loop cause this is mini "batch" gradient descent
        m = m - alpha * (slope_differential);
        c = c - alpha * (intercept_differential);
    }


}

void selection(const std::vector<double>& x,
               const std::vector<double>& y,
               double& m,
               double& c,
               double alpha,
               int epochs,
               int n,
               char choice,
               int batch_size
               ){
for (int j = 0; j < epochs; j++){
    switch(choice){
    case 'A':
        batch_gradient_descent(x, y, m, c, alpha, n);
        break;
    case 'B':
        stochastic_gradient_descent(x, y, m, c, alpha, n);
        break;
    case 'C':
        mini_batch_gradient_descent(x, y, m, c, alpha, batch_size, n);
        break;

                }
    if (j % 500 == 0){
        std::cout<<"Iteration "<< j <<" Cost "<< cost_function(x,m,c,y) <<" m is "<< m <<" c is "<< c <<endl; ;
    }
    }



}

int main()
{
    // Input training variables x
    std::vector<double> x = {1,2,3,4,5};
    // Output trainign variables y
    std::vector<double> y = {6,7,8,9,10};
    // slope, intercept , learning rate
    double m,c,alpha;
    char choice;
    int epochs, batch_size=1;
    int n = x.size();
    std::cout << "Enter slope or m "<<endl;
    std::cin >>m;
    std::cout << "Enter intercept or c "<<endl;
    std::cin >>c;
    std::cout << "Enter learning rate(alpha) "<<endl;
    std::cin >>alpha;
    std::cout << "Select epochs "<<endl;
    std::cin >> epochs;
    std::cout << "Enter your Choice "<<endl;
    std::cout << " A : Batch Gradient Descent \n B : Stochastic Gradient Descent \n C : mini batch gradient descent \n";
    std::cin >>choice;
    choice = std::toupper(static_cast<unsigned char>(choice));
    if (choice == 'C' ){
        std::cout << "Enter batch size ";
        std::cin >> batch_size;
        if (batch_size <= 0){
            std::cout <<"Batch sizes have to be greater than 0 ";
            return 1;
        }
    }
    if (choice == 'A' || choice == 'B' || choice == 'C'){
        selection(x,y,m,c,alpha,epochs,n,choice,batch_size);
    }

    return 0;
}
