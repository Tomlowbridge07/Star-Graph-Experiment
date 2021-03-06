#include <cmath>
#include <cassert>
#include <iomanip>
#include "Matrix.hpp"
#include "Vector.hpp"


// Overwritten copy constructor
// Allocate memory for new matrix, and copy
// entries into this matrix
Matrix::Matrix(const Matrix& otherMatrix)
{
   mNumRows = otherMatrix.mNumRows;
   mNumCols = otherMatrix.mNumCols;
   mData = new double* [mNumRows];
   for (int i=0; i<mNumRows; i++)
   {
      mData[i] = new double [mNumCols];
   }
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = otherMatrix.mData[i][j];
      }
   }
}

// Copy constructor (from interger type)
Matrix::Matrix(const IntMatrix& anIntMatrix)
{
   mNumRows = anIntMatrix.GetNumberOfRows();
   mNumCols = anIntMatrix.GetNumberOfColumns();
   mData = new double* [mNumRows];
   for (int i=0; i<mNumRows; i++)
   {
      mData[i] = new double [mNumCols];
   }
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = anIntMatrix.Read(i+1,j+1);
      }
   }
}

// Constructor for vector of a given length
// Allocates memory, and initialises entries
// to zero
Matrix::Matrix(int numRows, int numCols)
{
   assert(numRows > 0);
   assert(numCols > 0);
   mNumRows = numRows;
   mNumCols = numCols;
   mData = new double* [mNumRows];
   for (int i=0; i<mNumRows; i++)
   {
      mData[i] = new double [mNumCols];
   }
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = 0.0;
      }
   }
}

// Overwritten destructor to correctly free memory
Matrix::~Matrix()
{
   for (int i=0; i<mNumRows; i++)
   {
      delete[] mData[i];
   }
   delete[] mData;
}

// Method to get number of rows of matrix
int Matrix::GetNumberOfRows() const
{
   return mNumRows;
}

// Method to get number of columns of matrix
int Matrix::GetNumberOfColumns() const
{
   return mNumCols;
}

// Overloading the round brackets
// Note that this uses `one-based' indexing,
// and a check on the validity of the index
double& Matrix::operator()(int i, int j)
{
   assert(i > 0);
   assert(i < mNumRows+1);
   assert(j > 0);
   assert(j < mNumCols+1);
   return mData[i-1][j-1];
}

// Overloading the assignment operator
Matrix& Matrix::operator=(const Matrix& otherMatrix)
{
   assert(mNumRows = otherMatrix.mNumRows);
   assert(mNumCols = otherMatrix.mNumCols);

   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = otherMatrix.mData[i][j];
      }
   }
   return *this;
}

// Overloading the unary + operator
Matrix Matrix::operator+() const
{
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i+1,j+1) = mData[i][j];
      }
   }
   return mat;
}

// Overloading the unary - operator
Matrix Matrix::operator-() const
{
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i+1,j+1) = -mData[i][j];
      }
   }
   return mat;
}

// Overloading the binary + operator
Matrix Matrix::operator+(const Matrix& m1) const
{
   assert(mNumRows == m1.mNumRows);
   assert(mNumCols == m1.mNumCols);
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i+1,j+1) = mData[i][j] + m1.mData[i][j];
      }
   }
   return mat;
}

// Overloading the binary - operator
Matrix Matrix::operator-(const Matrix& m1) const
{
   assert(mNumRows == m1.mNumRows);
   assert(mNumCols == m1.mNumCols);
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i+1,j+1) = mData[i][j] - m1.mData[i][j];
      }
   }
   return mat;
}

// Overloading scalar multiplication
Matrix Matrix::operator*(double a) const
{
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i+1,j+1) = a*mData[i][j];
      }
   }
   return mat;
}

// Overloading matrix multiplied by a vector
Vector operator*(const Matrix& m, const Vector& v)
{
   int original_vector_size = v.GetSize();
   assert(m.GetNumberOfColumns() == original_vector_size);
   int new_vector_length = m.GetNumberOfRows();
   Vector new_vector(new_vector_length);

   for (int i=0; i<new_vector_length; i++)
   {
      for (int j=0; j<original_vector_size; j++)
      {
         new_vector[i] += m.mData[i][j]*v.Read(j);
      }
   }

   return new_vector;
}

// Overloading vector multiplied by a matrix
Vector operator*(const Vector& v, const Matrix& m)
{
   int original_vector_size = v.GetSize();
   assert(m.GetNumberOfRows() == original_vector_size);
   int new_vector_length = m.GetNumberOfColumns();
   Vector new_vector(new_vector_length);

   for (int i=0; i<new_vector_length; i++)
   {
      for (int j=0; j<original_vector_size; j++)
      {
         new_vector[i] += v.Read(j)*m.mData[j][i];
      }
   }

   return new_vector;
}

// Calculate determinant of square matrix recursively
double Matrix::CalculateDeterminant() const
{
   assert(mNumRows == mNumCols);
   double determinant = 0.0;

   if (mNumRows == 1)
   {
      determinant = mData[0][0];
   }
   else
   {
      // More than one entry of matrix
      for (int i_outer=0; i_outer<mNumRows; i_outer++)
      {
         Matrix sub_matrix(mNumRows-1,
                             mNumRows-1);
         for (int i=0; i<mNumRows-1; i++)
         {
            for (int j=0; j<i_outer; j++)
            {
               sub_matrix(i+1,j+1) = mData[i+1][j];
            }
            for (int j=i_outer; j<mNumRows-1; j++)
            {
               sub_matrix(i+1,j+1) = mData[i+1][j+1];
            }
         }
         double sub_matrix_determinant =
                  sub_matrix.CalculateDeterminant();

         determinant += pow(-1.0, i_outer)*
                  mData[0][i_outer]*sub_matrix_determinant;
      }
   }
   return determinant;
}

// Added by Daniele Avitabile
std::ostream& operator<<(std::ostream& output,
                        const Matrix& m)
{

  // Print formatted output
  for (int i=0; i< m.GetNumberOfRows(); i++)
  {
    for (int j=0; j< m.GetNumberOfColumns(); j++)
    {
      output << std::setw(14)
             << std::setprecision(5)
	     << std::scientific
	     << m.mData[i][j];
    }
    output << std::endl;
  }
  output << std::endl;

  return output;

}

///added by T.Lowbridge

//Reads the entry
//Uses 1 based indexing
double Matrix::Read(const int i,const int j) const
{
 //Check i and j are valid to pick an entry
 assert(i > 0 && i < mNumRows+1);
 assert(j > 0 && j < mNumCols+1);
 return mData[i-1][j-1];
}

//Gets a Column and returns it in Vector form
//Uses 1 based indexing
Vector Matrix::GetCol(const int j) const
{
 //Check j is a valid column
 assert(j>0 && j<mNumCols+1);

 //Form a Vector
 Vector Column(mNumRows);
 int i=0;
 while(i<mNumRows)
 {
  Column[i]=mData[i][j-1];
  i=i+1;
 }

 return Column;
}

//Gets a Row and returns it in Vector form
//Uses 1 based indexing
Vector Matrix::GetRow(const int i) const
{
 //Check i is a valid row
 assert(i>0 && i<mNumRows+1);

 //Form a Vector
 Vector Row(mNumCols);
 int j=0;
 while(j<mNumCols)
 {
  Row[j]=mData[i-1][j];
  j=j+1;
 }

 return Row;
}

//Set Column
void Matrix::SetCol(const int j,Vector SetColTo)
{
 int i=1;
 while(i<=mNumRows)
 {
  mData[i-1][j-1]=SetColTo(i);
  i=i+1;
 }
}

//Set Row
void Matrix::SetRow(const int i, Vector SetRowTo)
{
 int j=1;
 while(j<=mNumCols)
 {
  mData[i-1][j-1]=SetRowTo(j);
  j=j+1;
 }
}


//Fills a matrices elements with a given value
void Matrix::Fill(const double FillValue)
{
 int i=0;
 int j=0;
 while(i<mNumRows)
 {
  j=0;
  while(j<mNumCols)
  {
   mData[i][j]=FillValue;
   j=j+1;
  }
  i=i+1;
 }
}

//Sets a matrixes given row elements to a given value
//Uses 1 based indexing
void Matrix::SetRowToValue(const int Row,const int Value)
{
 //Check the Row is valid
 assert(Row>0 && Row<mNumRows+1);

 //Alter the Row's values
 int i=0;
 while(i<mNumCols)
 {
  mData[Row-1][i]=Value;
  i=i+1;
 }
}

//Sets a matrixes given Column elements to a given value
//Uses 1 based indexing
void Matrix::SetColToValue(const int Col,const int Value)
{
  //Check the Row is valid
 assert(Col>0 && Col<mNumCols+1);

 //Alter the Columns's values
 int j=0;
 while(j<mNumRows)
 {
  mData[j][Col-1]=Value;
  j=j+1;
 }
}


//Set Matrix Block
void Matrix::SetBlock(const int TopLeftI, const int TopLeftJ,Matrix Mat)
{
 int i=TopLeftI;
 int j=TopLeftJ;
 while(i<=mNumRows-Mat.GetNumberOfRows())
 {
  j=TopLeftJ;
  while(j<=mNumCols-Mat.GetNumberOfColumns())
  {
   mData[i-1][j-1]=Mat(i,j);
   j=j+1;
  }
  i=i+1;
 }
}

//Sets the matrix to the standard identity
void Matrix::SetToIdentity()
{
 //Check the matrix is square
 assert(mNumCols==mNumRows);

 //Make all zero apart from diagonals which are set to 1
 Fill(0);
 int i=0;
 while(i<mNumRows)
 {
  mData[i][i]=1;
  i=i+1;
 }
}

//pre-matrix Multiplication
Matrix Matrix::operator*(const Matrix& m1) const
{
 //Check the matrices are valid to multiple together
 assert(mNumCols==m1.GetNumberOfRows());

 //Set a Matrix to the size of the resultant
 Matrix Resultant(mNumRows,m1.GetNumberOfColumns());

 //Compute entries of the resultant column-wise by Matrix*Vector multiplication
 int i=1;
 int j=1;
 while(j<=m1.GetNumberOfColumns())
 {
  //Make the Column of the resultant by using Matrix1*(col of Matrix2)
  Vector Mc((*this)*(m1.GetCol(j)));

  //Read this vector and place in the resultant
  i=1;
  while(i<=mNumRows)
  {
   Resultant(i,j)=Mc(i);
   i=i+1;
  }
  j=j+1;
 }

 return Resultant;
}

//Kronecker Product
Matrix Matrix::KroneckerProduct(const Matrix& m1) const
{
 //Set a matrix to be the size of the resultant
 Matrix Resultant(mNumRows*m1.GetNumberOfRows(),mNumCols*m1.GetNumberOfColumns());

 //Form the resultant block by block and in the blocks using scalar multiplication
 int blockrow=1;
 int blockcol=1;
 int i=1;
 int j=1;
 while(blockrow<=mNumRows)
 {
  blockcol=1;
  while(blockcol<=mNumCols)
  {
   //Form the matrix which is the block of the resulatnt
   Matrix Block(m1*mData[blockrow-1][blockcol-1]);

   //Read values from matrix and place in resultant
   i=1;
   while(i<=m1.GetNumberOfRows())
   {
    j=1;
    while(j<=m1.GetNumberOfColumns())
    {
     Resultant(m1.GetNumberOfRows()*(blockrow-1)+i,m1.GetNumberOfColumns()*(blockcol-1)+j)=
     Block(i,j);
     j=j+1;
    }
    i=i+1;
   }
   blockcol=blockcol+1;
  }
  blockrow=blockrow+1;
 }

 return Resultant;
}

//Is Square
bool Matrix::IsSquare() const
{
 if(mNumCols==mNumRows)
 {
  return true;
 }
 else
 {
  return false;
 }
}

//Is Symmetric
bool Matrix::IsSymmetric() const
{
 int i=0;
 int j=0;
 while(i<mNumRows)
 {
  j=0;
  while(j<mNumCols && j<i)
  {
   if(mData[i][j]!=mData[j][i])
   {
    return false;
   }
   j=j+1;
  }
  i=i+1;
 }
 return true;
}

//Is diagonal value
bool Matrix::IsDiagonal(const double DiagonalValue) const
{
 int i=0;
 while(i<mNumCols)
 {
  if(mData[i][i]!=DiagonalValue)
  {
   return false;
  }
  i=i+1;
 }
 return true;
}

//Delete Row
void Matrix::DeleteRow(const int Row)
{
 Matrix Temp(*this);
 int i=1;
 while(i<=mNumRows)
 {
  delete[] mData[i-1];
  i=i+1;
 }
 delete[] mData;
 mNumRows=mNumRows-1;
 mData=new double* [mNumRows];
 i=1;
 while(i<=mNumRows)
 {
  mData[i-1]=new double[mNumCols];
  i=i+1;
 }
 i=1;
 int j=1;
 while(i<=mNumRows)
 {
  j=1;
  while(j<=mNumCols)
  {
   if(i<Row)
   {
    mData[i-1][j-1]=Temp(i,j);
   }
   if(i>=Row)
   {
    mData[i-1][j-1]=Temp(i+1,j);
   }
   j=j+1;
  }
  i=i+1;
 }
}

//Delete Row
void Matrix::DeleteCol(const int Col)
{
 Matrix Temp(*this);
 int i=1;
 while(i<=mNumRows)
 {
  delete[] mData[i-1];
  i=i+1;
 }
 delete[] mData;
 mNumCols=mNumCols-1;
 mData=new double* [mNumRows];
 i=1;
 while(i<=mNumRows)
 {
  mData[i-1]=new double[mNumCols];
  i=i+1;
 }
 i=1;
 int j=1;
 while(i<=mNumRows)
 {
  j=1;
  while(j<=mNumCols)
  {
   if(j<Col)
   {
    mData[i-1][j-1]=Temp(i,j);
   }
   if(i>=Col)
   {
    mData[i-1][j-1]=Temp(i,j+1);
   }
   j=j+1;
  }
  i=i+1;
 }
}

//Concate
//This sticks a matrix to the bottom (requiring the same number of columns)
void Matrix::VerticalConcatenate(Matrix M)
{
 assert(mNumRows=M.GetNumberOfRows());
 Matrix Temp(*this);
 int i=1;
 while(i<=mNumRows)
 {
  delete[] mData[i-1];
  i=i+1;
 }
 delete[] mData;
 int OldNumCols=mNumCols;
 mNumCols=mNumCols+M.GetNumberOfColumns();
 mData=new double* [mNumRows];
 i=1;
 while(i<=mNumRows)
 {
  mData[i-1]=new double[mNumCols];
  i=i+1;
 }
 i=1;
 int j=1;
 while(i<=mNumRows)
 {
  j=1;
  while(j<=mNumCols)
  {
   if(i<=OldNumCols)
   {
    mData[i-1][j-1]=Temp(i,j);
   }
   if(i>OldNumCols)
   {
    mData[i-1][j-1]=M(i-OldNumCols,j);
   }
   j=j+1;
  }
  i=i+1;
 }
}
//This sticks a matrix to the side (requiring the same number of rows)
void Matrix::HorizontalConcatenate(Matrix M)
{
 assert(mNumCols=M.GetNumberOfColumns());
 Matrix Temp(*this);
 int i=1;
 while(i<=mNumRows)
 {
  delete[] mData[i-1];
  i=i+1;
 }
 delete[] mData;
 int OldNumRows=mNumRows;
 mNumRows=mNumRows+M.GetNumberOfRows();
 mData=new double* [mNumRows];
 i=1;
 while(i<=mNumRows)
 {
  mData[i-1]=new double[mNumCols];
  i=i+1;
 }
 i=1;
 int j=1;
 while(i<=mNumRows)
 {
  j=1;
  while(j<=mNumCols)
  {
   if(i<=OldNumRows)
   {
    mData[i-1][j-1]=Temp(i,j);
   }
   if(i>OldNumRows)
   {
    mData[i-1][j-1]=M(i-OldNumRows,j);
   }
   j=j+1;
  }
  i=i+1;
 }
}

//Overload to allow interaction with Int Matrix

//This sticks a matrix to the bottom (requiring the same number of columns)
void Matrix::VerticalConcatenate(IntMatrix M)
{
 assert(mNumRows=M.GetNumberOfRows());
 Matrix Temp(*this);
 int i=1;
 while(i<=mNumRows)
 {
  delete[] mData[i-1];
  i=i+1;
 }
 delete[] mData;
 int OldNumCols=mNumCols;
 mNumCols=mNumCols+M.GetNumberOfColumns();
 mData=new double* [mNumRows];
 i=1;
 while(i<=mNumRows)
 {
  mData[i-1]=new double[mNumCols];
  i=i+1;
 }
 i=1;
 int j=1;
 while(i<=mNumRows)
 {
  j=1;
  while(j<=mNumCols)
  {
   if(i<=OldNumCols)
   {
    mData[i-1][j-1]=Temp(i,j);
   }
   if(i>OldNumCols)
   {
    mData[i-1][j-1]=M(i-OldNumCols,j);
   }
   j=j+1;
  }
  i=i+1;
 }
}
//This sticks a matrix to the side (requiring the same number of rows)
void Matrix::HorizontalConcatenate(IntMatrix M)
{
 assert(mNumCols=M.GetNumberOfColumns());
 Matrix Temp(*this);
 int i=1;
 while(i<=mNumRows)
 {
  delete[] mData[i-1];
  i=i+1;
 }
 delete[] mData;
 int OldNumRows=mNumRows;
 mNumRows=mNumRows+M.GetNumberOfRows();
 mData=new double* [mNumRows];
 i=1;
 while(i<=mNumRows)
 {
  mData[i-1]=new double[mNumCols];
  i=i+1;
 }
 i=1;
 int j=1;
 while(i<=mNumRows)
 {
  j=1;
  while(j<=mNumCols)
  {
   if(i<=OldNumRows)
   {
    mData[i-1][j-1]=Temp(i,j);
   }
   if(i>OldNumRows)
   {
    mData[i-1][j-1]=M(i-OldNumRows,j);
   }
   j=j+1;
  }
  i=i+1;
 }
}
