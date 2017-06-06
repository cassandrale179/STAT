#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

//RETURN FACTORIAL VERSION OF N
int f(int n){
  return (n == 1 || n == 0) ? 1 : f(n - 1) * n;
}

int main(){

  //CHANGE VALUE HERE
  double arr1[] = {0,1,2,3};
  double arr2[] = {0, 3, 3, 2, 1, 0, 1, 0, 0, 1, 1, 1, 2, 1, 0, 1, 0, 1, 2, 1, 1, 2, 1, 0, 1, 2, 0, 1, 0, 1};
  vector <double> no(arr1, arr1+30);
  vector <double> observed(arr2, arr2+30);
  vector <double> expected;


  //CALCULATING MEAN OF POISSON DISTRIBUTION
  double mean = 0; double count = 0;
  for (unsigned int i = 0; i < no.size(); i++){
    mean += observed[i]*no[i];
  }
  for (unsigned int i = 0; i < observed.size(); i++){
    count += observed[i];
  }
  mean = mean / count;
  cout << "Mean: " << mean << endl;


  //CALCULATING THE EXPECTED FREQUENCY OF POISSON DISTRIBUTION
  for (unsigned int i = 0; i < observed.size(); i++){
    expected.push_back(count*pow(mean,no[i])*exp(-1*mean)/f(no[i]));
  }

  //FINDING THE REMANING CATEGORY (SINCE POISSON IS DEFINED 0, INFINITY)
  double probability = 0;
  for (unsigned int i = 0; i < expected.size(); i++){
    probability += expected[i] / 100;
  }
  double remain = 1 - probability;
  expected.push_back(remain);


  //CALCULATING THE TEST STATISTICS
  vector <double> chi;
  double tstat = 0;
  for (unsigned int i = 0; i < observed.size(); i++){
    chi.push_back(pow(observed[i]-expected[i],2)/expected[i]);
    tstat += (pow(observed[i]-expected[i],2)/expected[i]);
  }

  //DISPLAY STUFF
  for (unsigned int i = 0; i < observed.size(); i++){
    cout << setw(10) << fixed << observed[i] << "   |   " << setw(10) << expected[i] <<  "   |   " << chi[i] << endl;
  }
  cout << "Test statistics: " << tstat << endl;
  cout << "Degree of freedom: " << expected.size() - 2 << endl;

}
