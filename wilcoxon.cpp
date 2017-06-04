#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
void print(vector <double> v){
  for (unsigned int i = 0; i < v.size(); i++){
    cout << v[i] << endl;
  }
}


int main(){
  double benchmark = 75;
  const int size = 20;

  //SORT THE GIVEN DATA FROM HIGHEST TO SMALLEST
  double arr[size] = {60, 53, 79, 99, 89, 60, 76, 54, 65, 83, 55, 51, 59, 90, 54, 62, 100, 59, 95, 67};
  vector <double> v(arr, arr+size);  //change size here
  sort(v.begin(), v.end());
  vector <int> v2;
  for (int i = v.size()-1; i >= 0; i--){
    v2.push_back(v[i]);
  }

  //CALCULATING THE MEDIAN VALUE MW
  int n = v.size();
  double Mw = n*(n+1) / 4;
  cout << "Value of Mw: " << Mw << endl;


  //CALCULATING THE STANDARD DEVIATION
  double Sw = sqrt(n*(n+1)*(2*n+1)/24);
  cout << "Value of Sw: " << Sw << endl;

  //CALCULATING THE DIFFERENCE BETWEEN DATA AND BENCHMARK
  vector <double> v3;
  for (unsigned int i = 0; i < v2.size(); i++){
    v3.push_back(v2[i]-benchmark);
  }
  sort(v3.begin(), v3.end());
  print(v3);

  //CREATING RANK FOR THE VECTOR
  vector <double> rank;
  for (unsigned int i = 1; i <= v3.size(); i++){
    rank.push_back(i);
  }
  print(rank);


  //DISPLAY FINAL RESULT


  //CALCULATING Z-CALC
//  double z = (w-Mw) / Sw;
//  cout << "Z-score: " << z << endl;

}
