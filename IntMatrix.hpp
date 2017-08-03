#ifndef INTMATRIXHEADERDEF
#define INTMATRIXHEADERDEF

#include "IntVector.hpp"

// Class adapted from Whiteley, Pitt-Francis
class IntMatrix
{

private:

  // Entries of matrix
  int** mData;

  // Dimensions
  int mNumRows, mNumCols;

public:

  // Copy constructor
  IntMatrix(const IntMatrix& otherMatrix);

  // Specialised Constructor
  IntMatrix(int numRows, int numCols);

  //From Vector
  IntMatrix(IntVector Vector, bool Row=true);

  // Destructor
  ~IntMatrix();

  // Accessors
  int GetNumberOfRows() const;
  int GetNumberOfColumns() const;

  // 1-based indexing
  int& operator()(int i, int j);

  //Overloaded assignment operator
  IntMatrix& operator=(const IntMatrix& otherMatrix);

  // Unary +
  IntMatrix operator+() const;

  // Unary -
  IntMatrix operator-() const;

  // Binary +
  IntMatrix operator+(const IntMatrix& m1) const;

  // Binary -
  IntMatrix operator-(const IntMatrix& m1) const;

  // Scalar multiplication
  IntMatrix operator*(int a) const;

  // Determinant
  int CalculateDeterminant() const;

  // Declare vector multiplication friendship
  friend IntVector operator*(const IntMatrix& m,
                          const IntVector& v);
  friend IntVector operator*(const IntVector& v,
                          const IntMatrix& m);

  // Overridden << operator
  friend std::ostream& operator<<(std::ostream& output,
                        const IntMatrix& m);

  //added by T.Lowbridge

  //Read entry
  int Read(const int i,const int j) const;

  //Get Column
  IntVector GetCol(const int j) const;

  //Get Row
  IntVector GetRow(const int i) const;

  //Returns a Block of the matrix
  IntMatrix GetBlock(int TopLeftI,int TopLeftJ,int rows, int cols);

  //Set Column
  void SetCol(const int j,IntVector SetColTo);

  //Set Row
  void SetRow(const int i, IntVector SetRowTo);

  //Set Row to value
  void SetRowToValue(const int Row ,const int Value);

  //Set Column to value
  void SetColToValue(const int Col,const int Value);

  //Set Matrix Block
  void SetBlock(const int TopLeftI, const int TopLeftJ,IntMatrix Mat);

  //Fill
  void Fill(const int FillValue);

  //Set to identity
  void SetToIdentity();

  //pre-matrix multiplication
  IntMatrix operator*(const IntMatrix& m1) const;

  //kroneckerProduct
  IntMatrix KroneckerProduct(const IntMatrix& m1) const;

  //Check if Square
  bool IsSquare() const;

  //Check if symmetric
  bool IsSymmetric() const;

  //Check Diagonal
  bool IsDiagonal(const int DiagonalValue) const;

 //Delete Row
 void DeleteRow(const int Row);

 //Delete Row
 void DeleteCol(const int Col);

};

// prototype signatures for friend operators
IntVector operator*(const IntMatrix& m, const IntVector& v);
IntVector operator*(const IntVector& v, const IntMatrix& m);

#endif
