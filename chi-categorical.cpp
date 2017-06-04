#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//PRINT OUT A DECENT LOOKING TABLE WITH ROWS AND COLUMNS
void print(vector <double> val, int row, int col){
  for (unsigned int i = 0; i < val.size(); i++){
    cout << val[i] << " ";
    if ((i+1) % col == 0) cout << endl;
  }

}

int main(){
  int row, col;
  cout << "No. of rows: "; cin >> row;
  cout << "No. of columns: "; cin >> col;

  //CHANGE VALUE HERE!
  double arr[] = {5, 8, 10, 8, 10, 6, 6, 6, 9, 5, 6, 5};
  vector <double> observed(arr, arr+12);

  //CALCULATING DEGREE OF FREEDOM
  int df = (row-1)*(col-1);

  //CALCULATING TOTAL FROM EACH ROW
  vector <double> trow;
  double rowsum = 0;
  for (unsigned int i = 0; i < observed.size(); i++){
    rowsum += observed[i];
    if ((i+1) % col == 0){
      trow.push_back(rowsum);
      rowsum = 0;
    }
  }

  //CALCULATING TOTAL FROM EACH COLUMNS
  vector <double> tcol;
  double colsum = 0;
  int num = 0;
  while(num < row){
    for (unsigned int i = num; i < observed.size(); i+=3){
      colsum += observed[i];
    }
    tcol.push_back(colsum);
    colsum = 0;
    num++;
  }

  //CALCULATING SUM OF ROW (OR COLUMN)
  double sum = 0;
  for (unsigned int i = 0; i < trow.size(); i++){
    sum += trow[i];
  }

  //CALCULATING EXPECTED VALUE
  vector <double> expected;
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col; j++){
      expected.push_back(trow[i]*tcol[j] / sum);
    }
  }

  //CALCULATING TEST STATISTICS
  double tstat = 0;
  for (unsigned int i = 0; i < expected.size(); i++){
    tstat += pow(expected[i]-observed[i],2)/expected[i];
  }
  cout << "Test statistics: " << tstat << endl;
  cout << "Degree of freedom: " << df << endl;




}
