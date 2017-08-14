#include <cmath>
#include <cassert>
#include <iomanip>
#include "IntMatrix.hpp"
#include "IntVector.hpp"


// Overwritten copy constructor
// Allocate memory for new matrix, and copy
// entries into this matrix
IntMatrix::IntMatrix(const IntMatrix& otherMatrix)
{
   mNumRows = otherMatrix.mNumRows;
   mNumCols = otherMatrix.mNumCols;
   mData = new int* [mNumRows];
   for (int i=0; i<mNumRows; i++)
   {
      mData[i] = new int [mNumCols];
   }
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = otherMatrix.mData[i][j];
      }
   }
}

// Constructor for vector of a given length
// Allocates memory, and initialises entries
// to zero
IntMatrix::IntMatrix(int numRows, int numCols)
{
   assert(numRows > 0);
   assert(numCols > 0);
   mNumRows = numRows;
   mNumCols = numCols;
   mData = new int* [mNumRows];
   for (int i=0; i<mNumRows; i++)
   {
      mData[i] = new int [mNumCols];
   }
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = 0;
      }
   }
}

///Untested function
IntMatrix::IntMatrix(IntVector Vector, bool Row/*=true*/)
{
 std::cout<<Vector.GetSize();
 if(Row)
 {
   mData = new int* [1];
   mData[0] = new int [Vector.GetSize()];
  int i=1;
  while(i<=Vector.GetSize())
  {
   mData[0][i-1]=Vector(i);
   i=i+1;
  }
 }
 else
 {
   mData = new int* [Vector.GetSize()];
   for (int i=0; i<Vector.GetSize(); i++)
   {
      mData[i] = new int [1];
   }
  int i=1;
  while(i<=Vector.GetSize())
  {
   mData[i-1][0]=Vector(i);
   i=i+1;
  }
 }
}

// Overwritten destructor to correctly free memory
IntMatrix::~IntMatrix()
{
   for (int i=0; i<mNumRows; i++)
   {
      delete[] mData[i];
   }
   delete[] mData;
}

// Method to get number of rows of matrix
int IntMatrix::GetNumberOfRows() const
{
   return mNumRows;
}

// Method to get number of columns of matrix
int IntMatrix::GetNumberOfColumns() const
{
   return mNumCols;
}

// Overloading the round brackets
// Note that this uses `one-based' indexing,
// and a check on the validity of the index
int& IntMatrix::operator()(int i, int j)
{
   assert(i > 0);
   assert(i < mNumRows+1);
   assert(j > 0);
   assert(j < mNumCols+1);
   return mData[i-1][j-1];
}

// Overloading the assignment operator
IntMatrix& IntMatrix::operator=(const IntMatrix& otherMatrix)
{
   assert(mNumRows == otherMatrix.mNumRows);
   assert(mNumCols == otherMatrix.mNumCols);

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
IntMatrix IntMatrix::operator+() const
{
   IntMatrix mat(mNumRows, mNumCols);
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
IntMatrix IntMatrix::operator-() const
{
   IntMatrix mat(mNumRows, mNumCols);
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
IntMatrix IntMatrix::operator+(const IntMatrix& m1) const
{
   assert(mNumRows == m1.mNumRows);
   assert(mNumCols == m1.mNumCols);
   IntMatrix mat(mNumRows, mNumCols);
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
IntMatrix IntMatrix::operator-(const IntMatrix& m1) const
{
   assert(mNumRows == m1.mNumRows);
   assert(mNumCols == m1.mNumCols);
   IntMatrix mat(mNumRows, mNumCols);
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
IntMatrix IntMatrix::operator*(int a) const
{
   IntMatrix mat(mNumRows, mNumCols);
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
IntVector operator*(const IntMatrix& m, const IntVector& v)
{
   int original_vector_size = v.GetSize();
   assert(m.GetNumberOfColumns() == original_vector_size);
   int new_vector_length = m.GetNumberOfRows();
   IntVector new_vector(new_vector_length);

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
IntVector operator*(const IntVector& v, const IntMatrix& m)
{
   int original_vector_size = v.GetSize();
   assert(m.GetNumberOfRows() == original_vector_size);
   int new_vector_length = m.GetNumberOfColumns();
   IntVector new_vector(new_vector_length);

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
int IntMatrix::CalculateDeterminant() const
{
   assert(mNumRows == mNumCols);
   int determinant = 0;

   if (mNumRows == 1)
   {
      determinant = mData[0][0];
   }
   else
   {
      // More than one entry of matrix
      for (int i_outer=0; i_outer<mNumRows; i_outer++)
      {
         IntMatrix sub_matrix(mNumRows-1,
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
         int sub_matrix_determinant =
                  sub_matrix.CalculateDeterminant();

         determinant += pow(-1.0, i_outer)*
                  mData[0][i_outer]*sub_matrix_determinant;
      }
   }
   return determinant;
}

// Added by Daniele Avitabile
std::ostream& operator<<(std::ostream& output,
                        const IntMatrix& m)
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
int IntMatrix::Read(const int i,const int j) const
{
 //Check i and j are valid to pick an entry
 assert(i > 0 && i < mNumRows+1);
 assert(j > 0 && j < mNumCols+1);
 return mData[i-1][j-1];
}

//Gets a Column and returns it in Vector form
//Uses 1 based indexing
IntVector IntMatrix::GetCol(const int j) const
{
 //Check j is a valid column
 assert(j>0 && j<mNumCols+1);

 //Form a Vector
 IntVector Column(mNumRows);
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
IntVector IntMatrix::GetRow(const int i) const
{
 //Check i is a valid row
 assert(i>0 && i<mNumRows+1);

 //Form a Vector
 IntVector Row(mNumCols);
 int j=0;
 while(j<mNumCols)
 {
  Row[j]=mData[i-1][j];
  j=j+1;
 }

 return Row;
}

//Returns a Block of the matrix
IntMatrix IntMatrix::GetBlock(int TopLeftI,int TopLeftJ,int rows, int cols)
{
 IntMatrix Block(rows,cols);
 int i=1;
 int j=1;
 while(i<=rows)
 {
  j=1;
  while(j<=cols)
  {
   Block(i,j)=mData[TopLeftI-2+i][TopLeftJ-2+j];
   j=j+1;
  }
  i=i+1;
 }

 return Block;
}

//Set Column
void IntMatrix::SetCol(const int j,IntVector SetColTo)
{
 int i=1;
 while(i<=mNumRows)
 {
  mData[i-1][j-1]=SetColTo(i);
  i=i+1;
 }
}

//Set Row
void IntMatrix::SetRow(const int i, IntVector SetRowTo)
{
 int j=1;
 while(j<=mNumCols)
 {
  mData[i-1][j-1]=SetRowTo(j);
  j=j+1;
 }
}


//Fills a matrices elements with a given value
void IntMatrix::Fill(const int FillValue)
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
void IntMatrix::SetRowToValue(const int Row,const int Value)
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
void IntMatrix::SetColToValue(const int Col,const int Value)
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
void IntMatrix::SetBlock(const int TopLeftI, const int TopLeftJ,IntMatrix Mat)
{
 int i=TopLeftI;
 int j=TopLeftJ;
 while(i<=Mat.GetNumberOfRows()+TopLeftI-1)
 {
  j=TopLeftJ;
  while(j<=Mat.GetNumberOfColumns()+TopLeftJ-1)
  {
   mData[i-1][j-1]=Mat(i-TopLeftI+1,j-TopLeftJ+1);
   j=j+1;
  }
  i=i+1;
 }
}

//Sets the matrix to the standard identity
void IntMatrix::SetToIdentity()
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
IntMatrix IntMatrix::operator*(const IntMatrix& m1) const
{
 //Check the matrices are valid to multiple together
 assert(mNumCols==m1.GetNumberOfRows());

 //Set a Matrix to the size of the resultant
 IntMatrix Resultant(mNumRows,m1.GetNumberOfColumns());

 //Compute entries of the resultant column-wise by Matrix*Vector multiplication
 int i=1;
 int j=1;
 while(j<=m1.GetNumberOfColumns())
 {
  //Make the Column of the resultant by using Matrix1*(col of Matrix2)
  IntVector Mc((*this)*(m1.GetCol(j)));

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
IntMatrix IntMatrix::KroneckerProduct(const IntMatrix& m1) const
{
 //Set a matrix to be the size of the resultant
 IntMatrix Resultant(mNumRows*m1.GetNumberOfRows(),mNumCols*m1.GetNumberOfColumns());

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
   IntMatrix Block(m1*mData[blockrow-1][blockcol-1]);

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
bool IntMatrix::IsSquare() const
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
bool IntMatrix::IsSymmetric() const
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
bool IntMatrix::IsDiagonal(const int DiagonalValue) const
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

//Extend Row
void IntMatrix::ExtendRow(const int ExtendBy)
{
 //Temp store this data
 IntMatrix Temp(*this);

 //delete current storage
 for (int i=0; i<mNumRows; i++)
 {
  delete[] mData[i];
 }
 delete[] mData;

 //Alter Size
 int oldNumRows=mNumRows;
 mNumRows=mNumRows+ExtendBy;

 //Create new storage
 mData = new int* [mNumRows];
 for (int i=0; i<mNumRows; i++)
 {
  mData[i] = new int [mNumCols];
 }

 //Insert values
 for (int i=0; i<mNumRows; i++)
 {
  for (int j=0; j<mNumCols; j++)
  {
   if(i<oldNumRows)
   {
    mData[i][j] = Temp(i+1,j+1);
   }
   else
   {
    mData[i][j] = 0;
   }
  }
 }

}

//Extend Col
void IntMatrix::ExtendCol(const int ExtendBy)
{
 //Temp store this data
 IntMatrix Temp(*this);

 //delete current storage
 for (int i=0; i<mNumRows; i++)
 {
  delete[] mData[i];
 }
 delete[] mData;

 //Alter Size
 int oldNumCols=mNumCols;
 mNumCols=mNumCols+ExtendBy;

 //Create new storage
 mData = new int* [mNumRows];
 for (int i=0; i<mNumRows; i++)
 {
  mData[i] = new int [mNumCols];
 }

 //Insert values
 for (int i=0; i<mNumRows; i++)
 {
  for (int j=0; j<mNumCols; j++)
  {
   if(j<oldNumCols)
   {
    mData[i][j] = Temp(i+1,j+1);
   }
   else
   {
    mData[i][j] = 0;
   }
  }
 }
}

//Add Row
/*
This method adds a zero row below the selected row
Note. Changing below=false will make it appear above instead
*/
void IntMatrix::AddRow(const int Row,const bool below/*=true*/)
{
 //Store Temp data
 IntMatrix Temp(*this);

 //delete current storage
 for (int i=0; i<mNumRows; i++)
 {
  delete[] mData[i];
 }
 delete[] mData;

 //Alter Size
 mNumRows=mNumRows+1;

  //Create new storage
 mData = new int* [mNumRows];
 for (int i=0; i<mNumRows; i++)
 {
  mData[i] = new int [mNumCols];
 }

 //Insert values
 for (int i=0; i<mNumRows; i++)
 {
  for (int j=0; j<mNumCols; j++)
  {
   if(below==true) //insert zeros in row Row+1
   {
    if(i<=Row-1)
    {
     mData[i][j] = Temp(i+1,j+1);
    }
    else if(i>Row)
    {
     mData[i][j] = Temp(i,j+1);
    }
    else
    {
     mData[i][j]=0;
    }
   }
   else //If above, insert zeroes in row Row
   {
    if(i<Row-1)
    {
     mData[i][j] = Temp(i+1,j+1);
    }
    else if(i>Row-1)
    {
     mData[i][j] = Temp(i,j+1);
    }
    else
    {
     mData[i][j]=0;
    }
   }
  }
 }
}

//Add Col
/*
This method adds a zero col to the right of the selected col
Note. Changing right=false will make it appear to the left instead
*/
void IntMatrix::AddCol(const int Col,const bool right/*=true*/)
{
//Store Temp data
 IntMatrix Temp(*this);

 //delete current storage
 for (int i=0; i<mNumRows; i++)
 {
  delete[] mData[i];
 }
 delete[] mData;

 //Alter Size
 mNumCols=mNumCols+1;

 //Create new storage
 mData = new int* [mNumRows];
 for (int i=0; i<mNumRows; i++)
 {
  mData[i] = new int [mNumCols];
 }

 //Insert values
 for (int i=0; i<mNumRows; i++)
 {
  for (int j=0; j<mNumCols; j++)
  {
   if(right==true) //Insert Zeroes in Column Col+1
   {
    if(j<=Col-1)
    {
     mData[i][j] = Temp(i+1,j+1);
    }
    else if(j>Col)
    {
     mData[i][j] = Temp(i+1,j);
    }
    else
    {
     mData[i][j]=0;
    }
   }
   else //If to left insert zereos in column Col
   {
    if(j<Col-1)
    {
     mData[i][j] = Temp(i+1,j+1);
    }
    else if(j>Col-1)
    {
     mData[i][j] = Temp(i+1,j);
    }
    else
    {
     mData[i][j]=0;
    }
   }
  }
 }
}


//Delete Row
void IntMatrix::DeleteRow(const int Row)
{
 IntMatrix Temp(*this);
 int i=1;
 while(i<=mNumRows)
 {
  delete[] mData[i-1];
  i=i+1;
 }
 delete[] mData;
 mNumRows=mNumRows-1;
 mData=new int* [mNumRows];
 i=1;
 while(i<=mNumRows)
 {
  mData[i-1]=new int[mNumCols];
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
void IntMatrix::DeleteCol(const int Col)
{
 IntMatrix Temp(*this);
 int i=1;
 while(i<=mNumRows)
 {
  delete[] mData[i-1];
  i=i+1;
 }
 delete[] mData;
 mNumCols=mNumCols-1;
 mData=new int* [mNumRows];
 i=1;
 while(i<=mNumRows)
 {
  mData[i-1]=new int[mNumCols];
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
