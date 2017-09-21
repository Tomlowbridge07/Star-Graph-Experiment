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
      mData[i] = 0;
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

// Two Vector Saver
/*
This method saves 2 vectors (the current one and the inputted one) into an
output file with the vectors organised into columns

Example: (1,4,-2),(4,0,2) ---> 1 4
                               4 0
                              -2 2/*
This method returns the minimum value of the vector
*/
void IntVector::SaveVectors(const IntVector v,
                const std::string FileName/*="2Vectors_Ouput.dat"*/)
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

//Reverse
/*
This method reverses the values in a vector
i.e (1,-6,5)->(5,-6,1)
*/
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

//Fill
/*
This method overwrites the values of the vector with the FillValue
*/
void IntVector::Fill(const int FillValue)
{
 int i=0;
 while(i<mSize)
 {
  mData[i]=FillValue;
  i=i+1;
 }
}


//Function evaluation
/*
This method evaluates the values of the vector and overwrites the values in the
vector for the pointed function
*/
void IntVector::Evaluate(int (*pFunc)(int x))
{
 int i=0;
 while(i<mSize)
 {
  mData[i]=pFunc(mData[i]);
  i=i+1;
 }
}

//Maximum value
/*
This method returns the maximum value of the vector
*/
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

//Maximum Element
/*
This method returns the 1-based index maximum element of a vector
*/
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

//Maximum Elements
/*
This method returns the 1-based index maximum elements of a vector.
The size of the vector determines how many maximum elements there are
*/
IntVector IntVector::MaxElements()
{
 int i=1;
 IntVector maxelements(1);
 int maxer=(*this).Max();
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

//Minimum value
/*
This method returns the minimum value of the vector
*/
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

//Mimimum element finder
/*
This method returns the 1-based index minimum element of a vector
*/
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

//Minimum Elements
/*
This method returns the 1-based index minimum elements of a vector.
The size of the vector determines how many minimum elements there are
*/
IntVector IntVector::MinElements()
{
 int i=1;
 IntVector minelements(1);
 int miner=(*this).Min();
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

//Internal Bubble sort
/*
This method performs the bubble sort on the vector internally.

Note. It does not remember which componenets were switched (if that is
wished it is best to use ReturnBubbleSort)
*/
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

//Returning BubbleSort
/*
This method performs the bubble sort on a vector externally and outputing
the sorted vector

Note. It allows a pointer to store which componenets were switched in the form
of a permutation vector (which used 1-based indexing)
*/
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



//Set to identity perm
/*
This method sets the vector to the identity vector i.e (1,2,3,4,...,n)
Note. It uses 1-based indexing for the identity
*/
void IntVector::SetToIdentityPerm()
{
 int i=1;
 while(i<=mSize)
 {
  mData[i-1]=i;
  i=i+1;
 }
}

//Calculate the Vector Sum
/*
This method Sums the components of the vector up
*/
int IntVector::Sum()
{
 int i=1;
 int Sum=0;
 while(i<=mSize)
 {
  Sum=Sum+mData[i-1];
  i=i+1;
 }
 return Sum;
}

//Calculates the average vector component
/*
This method calculates the average component value by summing and dividing
by the size of the vector.
Note. This outputs a double while all values are integers
*/
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

//Extend vector
/*
This method extends a vector's size by the ExtendBy variables size
The Extended Values are set to zero
*/
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
