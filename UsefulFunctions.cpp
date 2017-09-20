#include "UsefulFunctions.hpp"
#include<cassert>
#include<iostream>

int gcd(int a, int b)
{
 if(b==0)
 {
  return a;
 }
 else
 {
  return gcd(b,a % b);
 }
}

int factorial(int n)
{
 assert(n>=0);
 if(n==0 || n==1)
 {
  return 1;
 }
 else //If n>1
 {
  return n*factorial(n-1);
 }
}

int combinatorial(int n, int r)
{
 assert(n>=0);
 assert(r>=0);
 assert(r<=n);

 int i=0;
 double answer=1;
 while(i<r)
 {
  std::flush(std::cout<<"answer is "<<answer<<"\n");
  answer=answer*(n-i);
  answer=answer/(i+1);
  i=i+1;
 }
 return (int)answer;
}
/*
int combinatorial(int n, int r)
{
 assert(n>=0);
 assert(r>=0);
 assert(r<=n);

 return (factorial(n))/(factorial(n-r)*factorial(r));
}
*/
