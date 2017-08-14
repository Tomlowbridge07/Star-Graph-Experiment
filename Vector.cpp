#include <cmath>
#include <cassert>
#include <iomanip>
#include<fstream>
#include "Vector.hpp"

// Overridden copy constructor
// Allocates memory for new vector, and copies
// entries of other vector into it
Vector::Vector(const Vector& otherVector)
{
   mSize = otherVector.GetSize();
   mData = new double [mSize];
   for (int i=0; i<mSize; i++)
   {
      mData[i] = otherVector.mData[i];
   }
}

// Constructor for vector of a given size
// Allocates memory, and initialises entries
// to zero
Vector::Vector(int size)
{
   assert(size > 0);
   mSize = size;
   mData = new double [mSize];
   for (int i=0; i<mSize; i++)
   {
      mData[i] = 0.0;
   }
}

// Overridden destructor to correctly free memory
Vector::~Vector()
{
   delete[] mData;
}

// Method to get the size of a vector
int Vector::GetSize() const
{
   return mSize;
}

// Overloading square brackets
// Note that this uses `zero-based' indexing,
// and a check on the validity of the index
double& Vector::operator[](int i)
{
   assert(i > -1);
   assert(i < mSize);
   return mData[i];
}

// Read-only variant of []
// Note that this uses `zero-based' indexing,
// and a check on the validity of the index
double Vector::Read(int i) const
{
   assert(i > -1);
   assert(i < mSize);
   return mData[i];
}

// Overloading round brackets
// Note that this uses `one-based' indexing,
// and a check on the validity of the index
double& Vector::operator()(int i)
{
   assert(i > 0);
   assert(i < mSize+1);
   return mData[i-1];
}

// Overloading the assignment operator
Vector& Vector::operator=(const Vector& otherVector)
{
   assert(mSize == otherVector.mSize);
   for (int i=0; i<mSize; i++)
   {
      mData[i] = otherVector.mData[i];
   }
   return *this;
}

// Overloading the unary + operator
Vector Vector::operator+() const
{
   Vector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = mData[i];
   }
   return v;
}

// Overloading the unary - operator
Vector Vector::operator-() const
{
   Vector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = -mData[i];
   }
   return v;
}

// Overloading the binary + operator
Vector Vector::operator+(const Vector& v1) const
{
   assert(mSize == v1.mSize);
   Vector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = mData[i] + v1.mData[i];
   }
   return v;
}

// Overloading the binary - operator
Vector Vector::operator-(const Vector& v1) const
{
   assert(mSize == v1.mSize);
   Vector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = mData[i] - v1.mData[i];
   }
   return v;
}

// Overloading scalar multiplication
Vector Vector::operator*(double a) const
{
   Vector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = a*mData[i];
   }
   return v;
}

// Method to calculate norm (with default value p=2)
// corresponding to the Euclidean norm
double Vector::CalculateNorm(int p) const
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
double Vector::CalculateInfinityNorm() const
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
double Vector::ScalarProduct(const Vector& v) const
{
   double scalar_product = 0.0;
   assert(mSize == v.GetSize());
   for (int i=0; i<mSize; i++)
   {
      scalar_product += mData[i]*v.Read(i);
   }
   return scalar_product;
}

// MATLAB style friend to get the size of a vector
int length(const Vector& v)
{
   return v.mSize;
}
//Code from Chapter10.tex line 60 save as Vector.cpp

// Added by Daniele Avitabile
std::ostream& operator<<(std::ostream& output,
                        const Vector& v)
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
void Vector::SaveVectors(const Vector v,const std::string FileName/*="2Vectors_Ouput.dat"*/)
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
void Vector::Reverse()
{
 Vector Temp(*this);
 int i=0;
 while(i<mSize)
 {
  mData[i]=Temp[mSize-i-1];
  i=i+1;
 }
}

//Fills a Vectors Components with a given value
void Vector::Fill(const double FillValue)
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
void Vector::Evaluate(double (*pFunc)(double x))
{
 int i=0;
 while(i<mSize)
 {
  mData[i]=pFunc(mData[i]);
  i=i+1;
 }
}

//Max of the vector
double Vector::Max()
{
 int i=1;
 double maxer;
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
int Vector::MaxElement()
{
 int i=1;
 double maxer;
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

//Maximum Elements
/*
This method returns the 1-based index maximum elements of a vector.
The size of the vector determines how many maximum elements there are
*/
IntVector Vector::MaxElements()
{
 int i=1;
 IntVector maxelements(1);
 double maxer=(*this).Max();
 int counter=1;
 while(i<=mSize)
 {
  if((*this)(i)==maxer)
  {
   if(counter!=1)
   {
    maxelements.Extend(1);
   }
   maxelements(counter)=i;
   counter=counter+1;
  }

  i=i+1;
 }
 return maxelements;
}

//Min of the vector
double Vector::Min()
{
 int i=1;
 double miner;
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
int Vector::MinElement()
{
 int i=1;
 double miner;
 int element;
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

//Minimum Elements
/*
This method returns the 1-based index minimum elements of a vector.
The size of the vector determines how many minimum elements there are
*/
IntVector Vector::MinElements()
{
 int i=1;
 IntVector minelements(1);
 double miner=(*this).Min();
 int counter=1;
 while(i<=mSize)
 {
  if((*this)(i)==miner)
  {
   if(counter!=1)
   {
    minelements.Extend(1);
   }
   minelements(counter)=i;
   counter=counter+1;
  }
  i=i+1;
 }
 return minelements;
}

//BubbleSort
//This Returns the vector and allows a pointers to hold the info
Vector Vector::ReturnBubbleSort(Vector* pPermutation)
{
 bool Swapped=true;
 int i=1;
 int run=1;
 double temp=0;
 double temp2=0;
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

void Vector::BubbleSort()
{
 bool Swapped=true;
 int i=1;
 int run=1;
 double temp=0;
 double temp2=0;
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
void Vector::SetToIdentityPerm()
{
 int i=1;
 while(i<=mSize)
 {
  mData[i-1]=i;
  i=i+1;
 }
}

double Vector::Average()
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

double Vector::Sum()
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
