#ifndef FANCYPOWER_HPP
#define FANCYPOWER_HPP
//m is the base and n is the power
int fancyPower(int n, int m)
{
  int a;
  int b;
  if (n==0){
    return 1;
  }
  else if (n%2==0){ //if n is even then x^n = (x^2)^(n/2)
    b = fancyPower(n/2,m*m);
    return (b); 
  }
  else{
    b = fancyPower((n-1)/2,m*m);
    return (m*b);
  }
}

#endif
