#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main(){

  //CHANGE VALUE HERE
  int row = 3;
  int column = 3;
  double a[row][column] =
  {
    {14,8,5},
    {11,12,5},
    {6, 5, 19}
  };

  //FINDING TOTAL ACROSS ROW
  double rsum = 0;
  vector <double> trow;
  int rowcount = 0;
  while(rowcount < row){
    for (int i = 0; i < column; i++){
      rsum += a[rowcount][i];
    }
    trow.push_back(rsum);
    rsum = 0;
    rowcount++;
  }

  //FINDING TOTAL ACROSS COLUMNS
  double csum = 0;
  vector <double> tcol;
  int colcount = 0;
  while(colcount < column){
    for (int i = 0; i < row; i++){
      csum += a[i][colcount];
    }
    tcol.push_back(csum);
    csum = 0;
    colcount++;
  }

  //FINDING TOTAL OF BOTH ROW AND COLUMN
  double tsum = 0;
  for (unsigned int i = 0; i < tcol.size(); i++){
    tsum += tcol[i];
  }

  //FINDING EXPECTED VALUE
  vector <double> expected;
  for (int i = 0; i  < row; i++){
    for (int j = 0; j < column; j++){
        expected.push_back(trow[i]*tcol[j]/tsum);
    }
  }


  //FINDING THE CHI SQUARE TEST STATISTICS
  double tstat = 0;
  for (unsigned int i = 0; i < expected.size(); i++){
    cout << expected[i] << endl;
  }







}

/*



*/
