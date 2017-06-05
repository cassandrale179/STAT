#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;



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
  //------READ IN LARGE DATA FROM A FILE------
  double samplesize = 0;
  vector <double> data;
  ifstream is("input.txt");
  double x;
  while (is >> x){
    data.push_back(x);
    samplesize++;
  }

  //------NUMBER OF BINS TO BE USED (CHANGE VALUE HERE)------
  double bins = 8;

  //------CALCULATE SAMPLE MEAN OF DATA------
  double sum = 0;
  for (unsigned int i = 0; i < data.size(); i++){
    sum += data[i];
  }
  double mean = sum / data.size();
  cout << "Sample mean: " << mean << endl;

  //------CALCULATE STANDARD DEVIATION OF DATA------
  double sd = 0;
  for (unsigned int i = 0; i < data.size(); i++){
    sd += pow((data[i]-mean),2) / (data.size()-1);
  }
  sd = sqrt(sd);
  cout << "Standard deviation: " << sd << endl;


  //------FINDING CUTOFF POINTS------
  vector <double> cutoff;
  double size =  1 / bins;
  const double interval = 1 / bins;
  while(size < 1){
      double z = NormalCDFInverse(size);
      z = floor(z*1000+0.001) / 1000;
      double t = z*sd + mean;
      cutoff.push_back(t);
      size += interval;
  }

  //------FINDING NUMBER OF OBSERVATIONS THAT LIE WITHIN THE INTERVAL------
  vector <double> observed;
  sort(data.begin(), data.end());

  unsigned int count = 0; unsigned int j = 0;
  while(j < cutoff.size()){
    if (data[0] < cutoff[j]){
      count++;
    }
    data.erase(data.begin(), data.begin()+1);
    if (data[0] >= cutoff[j]){
      observed.push_back(count);
      count = 0;
      j++;
    }
  }
    //NUMBER OF SAMPLE > LAST BIN
    double sum2 = 0;
    for (unsigned int i = 0; i < observed.size(); i++){
      sum2 += observed[i];
    }

    double remain = samplesize - sum2;
    observed.push_back(remain);

  //------CALCULATING EXPECTED FREQUENCY FOR NORMAL DISTRIBUTION------
  vector <double> expected;
  for (unsigned int i = 0; i < observed.size(); i++){
    expected.push_back(samplesize / bins);
  }


  //------CALCULATING CHI SQUARE STATISTICS------
  double tstat = 0;
  for (unsigned int i = 0; i < observed.size(); i++){
    tstat += (pow(observed[i] - expected[i],2)) / expected[i];
  }

  cout << "Tstat: " << tstat << endl;

  //CALCULATING THE DEGREE OF FREEDOM
  double df = bins - 3;
  cout << "Df: " << df << endl;










}
