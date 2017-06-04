#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//RETURN FACTORIAL VERSION OF N
int f(int n){
  return (n == 1 || n == 0) ? 1 : f(n - 1) * n;
}

int main(){

  //CHANGE VALUE HERE
  double arr1[] = {0,1,2,3,4};
  double arr2[] = {59,31,8,1,1};
  double noLessThan = 5;

  //INITIAILZE VECTOR
  vector <double> no(arr1, arr1+5);
  vector <double> observed(arr2, arr2+5);
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


  //COMBINING THE PROBABILITY OF CATEGORY WITH LESS THAN X% (e.g 5%)
  double combine = 0;
  double j = expected.size()-1;
  while (combine < noLessThan){
    combine += expected[j];
    expected.pop_back();
    j--;
  }
  expected.push_back(combine);

  //COMBINING THE VALUE OF THE CATEGORY ITSELF
  int combine2 = 0;
  unsigned int k = 0;
  unsigned int l = observed.size() - 1;
  while (k < expected.size()){
      combine2 += observed[l];
      l--;
      k++;
      observed.pop_back();
  }

  observed.push_back(combine2);



  //CALCULATING THE TEST STATISTICS
  double tstat = 0;
  for (unsigned int i = 0; i < observed.size(); i++){
    tstat += (pow(observed[i]-expected[i],2)/expected[i]);
  }
  cout << "Test statistics: " << tstat << endl;
  cout << "Degree of freedom: " << expected.size() - 2 << endl;

}
