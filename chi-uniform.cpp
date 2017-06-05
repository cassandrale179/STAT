#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

//PRINT OUT THE TABLE
void print(vector <double> v, vector <double> v2, vector <double> v3){
  for (unsigned int i = 0; i < v.size(); i++){
    cout << v[i] << "    " << v2[i] << "     " << v3[i] << endl;
  }
}

int main(){
  //CREATE A VECTOR OF OBSERVED FREQUENCY
  vector <double> observed;
  ifstream is("input.txt");
  double x;
  while (is >> x){
    observed.push_back(x);
  }

  //CREATE VECTOR OF EXPECTED FREQUENCY
  vector <double> expected;
  int sum = 0;
  for (unsigned int i = 0; i < observed.size(); i++){
    sum+= observed[i];
  }
  for (unsigned int i = 0; i < observed.size(); i++){
    expected.push_back(sum/observed.size());
  }

  //FIND THE CHI-SQUARE STATISTICS [(O-E)^2/E]
  double chisquare = 0;
  vector <double> difference;
  for (unsigned int i = 0; i < observed.size(); i++){
    difference.push_back(pow(observed[i]-expected[i],2)/expected[i]);
  }
  for (unsigned int i = 0; i < difference.size(); i++){
    chisquare += difference[i];
  }

  //CALCULATING THE DEGREE OF FREEDOM
  int df = observed.size() - 1;

  //DISPLAYING VALUES
  print(observed, expected, difference);
  cout << "Chi Square Value: " << chisquare << endl;
  cout << "Df: " << df << endl;

}
