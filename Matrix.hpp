#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF
#include "Vector.hpp"
#include "IntMatrix.hpp"

// Class adapted from Whiteley, Pitt-Francis
class Matrix
{

private:

  // Entries of matrix
  double** mData;

  // Dimensions
  int mNumRows, mNumCols;

public:

  // Copy constructor
  Matrix(const Matrix& otherMatrix);

  // Specialised Constructor
  Matrix(int numRows, int numCols);

  // Destructor
  ~Matrix();

  // Accessors
  int GetNumberOfRows() const;
  int GetNumberOfColumns() const;

  // 1-based indexing
  double& operator()(int i, int j);

  //Overloaded assignment operator
  Matrix& operator=(const Matrix& otherMatrix);

  // Unary +
  Matrix operator+() const;

  // Unary -
  Matrix operator-() const;

  // Binary +
  Matrix operator+(const Matrix& m1) const;

  // Binary -
  Matrix operator-(const Matrix& m1) const;

  // Scalar multiplication
  Matrix operator*(double a) const;

  // Determinant
  double CalculateDeterminant() const;

  // Declare vector multiplication friendship
  friend Vector operator*(const Matrix& m,
                          const Vector& v);
  friend Vector operator*(const Vector& v,
                          const Matrix& m);

  // Overridden << operator
  friend std::ostream& operator<<(std::ostream& output,
                        const Matrix& m);

  //added by T.Lowbridge

  //Read entry
  double Read(const int i,const int j) const;

  //Get Column
  Vector GetCol(const int j) const;

  //Get Row
  Vector GetRow(const int i) const;

  //Set Column
  void SetCol(const int j,Vector SetColTo);

  //Set Row
  void SetRow(const int i, Vector SetRowTo);

  //Set Row to value
  void SetRowToValue(const int Row ,const int Value);

  //Set Column to value
  void SetColToValue(const int Col,const int Value);

  //Set Matrix Block
  void SetBlock(const int TopLeftI, const int TopLeftJ,Matrix Mat);

  //Fill
  void Fill(const double FillValue);

  //Set to identity
  void SetToIdentity();

  //pre-matrix multiplication
  Matrix operator*(const Matrix& m1) const;

  //kroneckerProduct
  Matrix KroneckerProduct(const Matrix& m1) const;

  //Check if Square
  bool IsSquare() const;

  //Check if symmetric
  bool IsSymmetric() const;

  //Check Diagonal
  bool IsDiagonal(const double DiagonalValue) const;

 //Delete Row
 void DeleteRow(const int Row);

 //Delete Row
 void DeleteCol(const int Col);

 //Concate
 void VerticalConcatenate(Matrix M);
 void HorizontalConcatenate(Matrix M);

 //Overloaded functions
 void VerticalConcatenate(IntMatrix M);
 void HorizontalConcatenate(IntMatrix M);

};

// prototype signatures for friend operators
Vector operator*(const Matrix& m, const Vector& v);
Vector operator*(const Vector& v, const Matrix& m);

#endif
