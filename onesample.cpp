#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
using namespace std;

/*
  THIS IS THE CODE TO CALCUALTE THE TEST STATISTICS OF ONE-SAMPLE RUN TEST TO DETERMINE IF A GIVEN SEQUENCEFOLLOW BINARY PATTERN.

*/

//------INERSE FORMULA (SOURCE: JOHNDCOOK.COM)------
double RationalApproximation(double t)
{
  // Abramowitz and Stegun formula 26.2.23
  double c[] = {2.515517, 0.802853, 0.010328};
  double d[] = {1.432788, 0.189269, 0.001308};
  return t - ((c[2]*t + c[1])*t + c[0]) / (((d[2]*t + d[1])*t + d[0])*t + 1.0);
}

double NormalCDFInverse(double p){
  if (p <= 0.0 || p >= 1.0){
      std::stringstream os;
      os << "Invalid input argument (" << p
      << "); must be larger than 0 but less than 1.";
      throw std::invalid_argument( os.str() );
  }

  // See article above for explanation of this section.
  if (p < 0.5){// F^-1(p) = - G^-1(p)
      return -RationalApproximation( sqrt(-2.0*log(p)) );
  }
  else{// F^-1(p) = G^-1(1-p)
      return RationalApproximation( sqrt(-2.0*log(1-p)) );
  }
}



int main(){

  //CHANGE VALUE HERE (PLEASE DO NOT HAVE SPACE BETWEEN EVENTS)
  string arr[] = {"HMMHHMHMMHHHHHMMHHMMHMHHHMHHHHMMMHH"};
  //string arr[] = {"CCICCCCCIICICCCIIIICCCCICIIICC"};
  //string arr[] = {"++---+++++++----++-+-+-+----++++-++++-+++-+-+-+++------++++--"};

  //ASKING USER FOR SYMBOL USED IN BINARY EVENTS
  char s1; char s2;
  cout << "Enter symbol 1: ";
  cin >> s1;
  cout << "Enter symbol 2: ";
  cin >> s2;


  //COUNTING NUMBER OF OCCURENCE
  double a = 0;
  double b = 0;
  for (unsigned int i = 0; i < arr[0].length(); i++){
    if (arr[0][i] == s1) a++;
    if (arr[0][i] == s2) b++;
  }
  double n = a + b;


  //CALCULATING THE EXPECTED NUMBER OF RUNS
  double mu = (a*b*2) / n + 1;
  cout << "Expected value: " << mu << endl;

  //CALCULATING STANDARD DEVIATION
  double s = sqrt(2*a*b*(2*a*b-n)/(n*n*(n-1)));
  cout << "Standard deviation: " << s << endl;


  //COUNTING NUMBER OF RUNS
  double r = 1;
  for (unsigned int i = 0; i < arr[0].length()-1; i++){
    if ((arr[0][i] == s1 && arr[0][i+1] == s2) || (arr[0][i] == s2 && arr[0][i+1] == s1)) r++;
  }
  cout << "Total run: " << r << endl;


  //CALCULATING THE ZCALC
  double zcalc = (r - mu) / s;
  cout << "Zcalc: " << zcalc << endl;

  //FINDING THE CRITICAL VALUE (CHANGE VALUE HERE!!!!!)
  double left = NormalCDFInverse(0.025);
  double right = NormalCDFInverse(1-0.025);
  cout << "Rejection zone: " << left << " < x < " << right << endl;
  if (zcalc > left && zcalc < right) cout << "Conclusion: Fail to reject the null hypothesis. Events follow random pattern" << endl;
  else{
    cout << "Conclusion: Reject the null hypothesis. There is a possibility events do not follow random pattern" << endl;
  }



}
