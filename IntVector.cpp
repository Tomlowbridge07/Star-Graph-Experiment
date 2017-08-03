#include <cmath>
#include <cassert>
#include <iomanip>
#include<fstream>
#include "IntVector.hpp"

// Overridden copy constructor
// Allocates memory for new vector, and copies
// entries of other vector into it
IntVector::IntVector(const IntVector& otherVector)
{
   mSize = otherVector.GetSize();
   mData = new int [mSize];
   for (int i=0; i<mSize; i++)
   {
      mData[i] = otherVector.mData[i];
   }
}

// Constructor for vector of a given size
// Allocates memory, and initialises entries
// to zero
IntVector::IntVector(int size)
{
   assert(size > 0);
   mSize = size;
   mData = new int [mSize];
   for (int i=0; i<mSize; i++)
   {
      mData[i] = 0.0;
   }
}

// Overridden destructor to correctly free memory
IntVector::~IntVector()
{
   delete[] mData;
}

// Method to get the size of a vector
int IntVector::GetSize() const
{
   return mSize;
}

// Overloading square brackets
// Note that this uses `zero-based' indexing,
// and a check on the validity of the index
int& IntVector::operator[](int i)
{
   assert(i > -1);
   assert(i < mSize);
   return mData[i];
}

// Read-only variant of []
// Note that this uses `zero-based' indexing,
// and a check on the validity of the index
int IntVector::Read(int i) const
{
   assert(i > -1);
   assert(i < mSize);
   return mData[i];
}

// Overloading round brackets
// Note that this uses `one-based' indexing,
// and a check on the validity of the index
int& IntVector::operator()(int i)
{
   assert(i > 0);
   assert(i < mSize+1);
   return mData[i-1];
}

// Overloading the assignment operator
IntVector& IntVector::operator=(const IntVector& otherVector)
{
   assert(mSize == otherVector.mSize);
   for (int i=0; i<mSize; i++)
   {
      mData[i] = otherVector.mData[i];
   }
   return *this;
}

// Overloading the unary + operator
IntVector IntVector::operator+() const
{
   IntVector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = mData[i];
   }
   return v;
}

// Overloading the unary - operator
IntVector IntVector::operator-() const
{
   IntVector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = -mData[i];
   }
   return v;
}

// Overloading the binary + operator
IntVector IntVector::operator+(const IntVector& v1) const
{
   assert(mSize == v1.mSize);
   IntVector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = mData[i] + v1.mData[i];
   }
   return v;
}

// Overloading the binary - operator
IntVector IntVector::operator-(const IntVector& v1) const
{
   assert(mSize == v1.mSize);
   IntVector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = mData[i] - v1.mData[i];
   }
   return v;
}

// Overloading scalar multiplication
IntVector IntVector::operator*(int a) const
{
   IntVector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = a*mData[i];
   }
   return v;
}

// Method to calculate norm (with default value p=2)
// corresponding to the Euclidean norm
double IntVector::CalculateNorm(int p) const
{
   double norm_val, sum = 0.0;
   for (int i=0; i<mSize; i++)
   {
      sum += pow(fabs(mData[i]), p);
   }
   norm_val = pow(sum, 1.0/((double)(p)));
   return norm_val;
}

// Method to calculate the infinity norm
double IntVector::CalculateInfinityNorm() const
{
   double norm_val = 0;
   for (int i=0; i<mSize; i++)
   {
     double abs_val = fabs(mData[i]);
     if ( norm_val < abs_val )
     {
       norm_val = abs_val;
     }
   }
   return norm_val;
}

// Method to calculate scalar product with another vector
int IntVector::ScalarProduct(const IntVector& v) const
{
   int scalar_product = 0;
   assert(mSize == v.GetSize());
   for (int i=0; i<mSize; i++)
   {
      scalar_product += mData[i]*v.Read(i);
   }
   return scalar_product;
}

// MATLAB style friend to get the size of a vector
int length(const IntVector& v)
{
   return v.mSize;
}
//Code from Chapter10.tex line 60 save as Vector.cpp

// Added by Daniele Avitabile
std::ostream& operator<<(std::ostream& output,
                        const IntVector& v)
{
   for (int i=0; i<v.mSize; i++)
   {
      output << std::setw(14)
             << std::setprecision(5)
	     << std::scientific
	     << v.Read(i)
	     << std::endl;
   }
   output << std::endl;

   return output;
}

// Added by T.Lowbridge

//Saves 2 vectors in column form in a file
//Vectors are saved in the order written
void IntVector::SaveVectors(const IntVector v,const std::string FileName/*="2Vectors_Ouput.dat"*/)
{
 //assert they are both the same length
 assert(mSize==v.GetSize());

 //set up outstream
 std::ofstream outfile;
 outfile.setf(std::ios::scientific);
 outfile.precision(7);

 //open stream
 outfile.open(FileName);

 //Write data
 int i=0;
 while(i<mSize)
 {
  outfile<<mData[i]<<std::setw(15)<<v.Read(i)<<"\n";
  i=i+1;
 }

 //Close file
 outfile.close();
}

//Reverses a Vectors Components
void IntVector::Reverse()
{
 IntVector Temp(*this);
 int i=0;
 while(i<mSize)
 {
  mData[i]=Temp[mSize-i-1];
  i=i+1;
 }
}

//Fills a Vectors Components with a given value
void IntVector::Fill(const int FillValue)
{
 int i=0;
 while(i<mSize)
 {
  mData[i]=FillValue;
  i=i+1;
 }
}

//Overwrites the Vector with its enteries evaluated a given function
//Note. The order remains the same (no reordering takes place just evaluation)
void IntVector::Evaluate(int (*pFunc)(int x))
{
 int i=0;
 while(i<mSize)
 {
  mData[i]=pFunc(mData[i]);
  i=i+1;
 }
}

//Max of the vector
int IntVector::Max()
{
 int i=1;
 int maxer;
 while(i<=mSize)
 {
  if(i==1)
  {
   maxer=mData[i-1];
  }
  else
  {
   if(mData[i-1]>maxer)
   {
    maxer=mData[i-1];
   }
  }
  i=i+1;
 }
 return maxer;
}

//Max Element
int IntVector::MaxElement()
{
 int i=1;
 int maxer;
 int element;
 while(i<=mSize)
 {
  if(i==1)
  {
   maxer=mData[i-1];
   element=i;
  }
  else
  {
   if(mData[i-1]>maxer)
   {
    maxer=mData[i-1];
    element=i;
   }
  }
  i=i+1;
 }
 return element;
}

//Min of the vector
int IntVector::Min()
{
 int i=1;
 int miner;
 while(i<=mSize)
 {
  if(i==1)
  {
   miner=mData[i-1];
  }
  else
  {
   if(mData[i-1]<miner)
   {
    miner=mData[i-1];
   }
  }
  i=i+1;
 }
 return miner;
}

//Find the element that generates the minimum
int IntVector::MinElement()
{
 int i=1;
 int miner;
 int element=1;
 while(i<=mSize)
 {
  if(i==1)
  {
   miner=mData[i-1];
   element=i;
  }
  else
  {
   if(mData[i-1]<miner)
   {
    miner=mData[i-1];
    element=i;
   }
  }
  i=i+1;
 }
 return element;
}

//BubbleSort
//This Returns the vector and allows a pointers to hold the info
IntVector IntVector::ReturnBubbleSort(IntVector* pPermutation)
{
 //Create Storage for pPermutation
 delete pPermutation;
 pPermutation=new IntVector(mSize);

 bool Swapped=true;
 int i=1;
 int run=1;
 int temp=0;
 int temp2=0;
 while(run<=mSize && Swapped==true)
 {
  i=1;
  Swapped=false;
  while(i<=mSize-run)
  {
   if(mData[i-1]>mData[i])
   {
    temp=mData[i-1];
    mData[i-1]=mData[i];
    mData[i]=temp;
    temp=(*pPermutation)[i-1];
    temp2=(*pPermutation)[i];
    (*pPermutation)[i-1]=temp2;
    (*pPermutation)[i]=temp;
    Swapped=true;
   }
   i=i+1;
  }
  run=run+1;
 }
 return *this;
}

void IntVector::BubbleSort()
{
 bool Swapped=true;
 int i=1;
 int run=1;
 int temp=0;
 int temp2=0;
 while(run<=mSize && Swapped==true)
 {
  i=1;
  Swapped=false;
  while(i<=mSize-run)
  {
   if(mData[i-1]>mData[i])
   {
    temp=mData[i-1];
    mData[i-1]=mData[i];
    mData[i]=temp;
    Swapped=true;
   }
   i=i+1;
  }
  run=run+1;
 }
}


//Set to identity perm
//using 1-based indexing
void IntVector::SetToIdentityPerm()
{
 int i=1;
 while(i<=mSize)
 {
  mData[i-1]=i;
  i=i+1;
 }
}

double IntVector::Average()
{
 int i=1;
 double Sum=0;
 while(i<=mSize)
 {
  Sum=Sum+mData[i-1];
  i=i+1;
 }
 return Sum/(double)mSize;
}

int IntVector::Sum()
{
 int i=1;
 double Sum=0;
 while(i<=mSize)
 {
  Sum=Sum+mData[i-1];
  i=i+1;
 }
 return Sum;
}

//Extend vector
void IntVector::Extend(int ExtendBy)
{
 IntVector Temp(*this);
 delete[] mData;

 mSize = Temp.GetSize()+ExtendBy;
 mData = new int [mSize];
 for (int i=0; i<mSize; i++)
 {
  if(i<Temp.GetSize())
  {
   mData[i] = Temp(i+1);
  }
  else
  {
   mData[i]= 0;
  }
 }
}
