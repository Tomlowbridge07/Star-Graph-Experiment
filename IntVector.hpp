#ifndef INTVECTORHEADERDEF
#define INTVECTORHEADERDEF

#include <iostream>


// Class adapted from Whiteley, Pitt-Francis
class IntVector
{

private:

  // Data stored in vector
  int* mData;

  // Size of vector
  int mSize;

public:

  // Copy constructor
  IntVector(const IntVector& otherVector);

  // Specialised constructor
  IntVector(int size);

  // Destructor
  ~IntVector();

  // Accessor
  int GetSize() const;

  // Zero-based indexing
  int& operator[](int i);

  // Read-only zero-based indexing
  int Read(int i) const;

  // One-based indexing
  int& operator()(int i);

  // Assignment
  IntVector& operator=(const IntVector& otherVector);

  // Unary +
  IntVector operator+() const;

  // Unary -
  IntVector operator-() const;

  // Binary +
  IntVector operator+(const IntVector& v1) const;

  // Binary -
  IntVector operator-(const IntVector& v1) const;

  // Scalar multiplication
  IntVector operator*(int a) const;

  // p-norm method
  double CalculateNorm(int p=2) const;

  // infinity-norm method
  double CalculateInfinityNorm() const;

  // Scalar product with another vector
  int ScalarProduct(const IntVector& v) const;

  // Declare length function as a friend
  friend int length(const IntVector& v);

  // Override << operator
  friend std::ostream& operator<<(std::ostream& output,
                       const IntVector& v);

  //Added By T.Lowbridge

   //Save Vector Vector in columns in file
   void SaveVectors(const IntVector v,
        const std::string FileName="2Vectors_Ouput.dat");

   //Reverse Vector
   void Reverse();

   //Fill vector with value
   void Fill(const int FillValue);

   //Evaluate Vector at a function
   void Evaluate(int (*pFunc)(int x));

   //Max and Min Utilities
   int Max();
   int MaxElement();
   IntVector MaxElements();
   int Min();
   int MinElement();
   IntVector MinElements();


   //BubbleSorts:
   //Internal Bubble Sort
   void BubbleSort();
   //Returning Bubble Sort
   IntVector ReturnBubbleSort(IntVector* pPermutation);

   //Set to Identity Permutation
   void SetToIdentityPerm();

   //Average
   double Average();

   //Compute sum
   int Sum();

   //Extend vector
   void Extend(int ExtendBy);

};

// Prototype signature of length() friend function
int length(const IntVector& v);

#endif
