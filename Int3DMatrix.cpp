#include "Int3DMatrix.hpp"
#include<cassert>
#include<iomanip>

//Standard Constructor
Int3DMatrix::Int3DMatrix(int NumRows, int NumCols, int NumLayers)
{
 //assertions
 assert(NumRows>0);
 assert(NumCols>0);
 assert(NumLayers>0);

 //Store sizes
 mNumRows=NumRows;
 mNumCols=NumCols;
 mNumLayers=NumLayers;

 //Create storage for 3D matrix
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Set data to zero
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers;k++)
   {
    mData[i][j][k]=0;
   }
  }
 }
}


//Copy Constructor
Int3DMatrix::Int3DMatrix(const Int3DMatrix& other3DMatrix)
{
 //Store sizes
 mNumRows=other3DMatrix.mNumRows;
 mNumCols=other3DMatrix.mNumCols;
 mNumLayers=other3DMatrix.mNumLayers;

 //Create storage for 3D matrix
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Copy values from other matrix
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    mData[i][j][k]=other3DMatrix.mData[i][j][k];
   }
  }
 }
}


//Desctructor
Int3DMatrix::~Int3DMatrix()
{
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part
}

//Getters and Setters
int Int3DMatrix::GetNumberRows() const
{
 return mNumRows;
}
int Int3DMatrix::GetNumberCols() const
{
 return mNumCols;
}
int Int3DMatrix::GetNumberLayers() const
{
 return mNumLayers;
}


// Overloading round bracket operator
// Note. Uses 1-based indexing
int& Int3DMatrix::operator()(int i, int j, int k)
{
 assert(i>0);
 assert(i<=mNumRows);
 assert(j>0);
 assert(j<=mNumCols);
 assert(k>0);
 assert(k<=mNumLayers);

 return mData[i-1][j-1][k-1];
}

std::ostream& operator<<(std::ostream& output,const Int3DMatrix& m)
{
  // Print formatted output
  for(int k=0; k<m.GetNumberLayers(); k++)
  {
   output<< "Displaying Layer:"<<(k+1)<<"\n"
         <<"----------------------------------- \n";
    for (int i=0; i< m.GetNumberRows(); i++)
   {
    for (int j=0; j< m.GetNumberCols(); j++)
    {
      output << std::setw(14)
             << std::setprecision(5)
	     << std::scientific
	     << m.mData[i][j][k];
    }
    output << std::endl;
  }
  output << std::endl;

  }

  return output;
}

// Read entry
int Int3DMatrix::Read(int i, int j, int k)
{
 assert(i>0);
 assert(i<=mNumRows);
 assert(j>0);
 assert(j<=mNumCols);
 assert(k>0);
 assert(k<=mNumLayers);

 return mData[i-1][j-1][k-1];
}

//Overloading assignment operator
Int3DMatrix& Int3DMatrix::operator=(const Int3DMatrix& otherMatrix)
{
 //Check they are the same size (or assignment will fail)
 assert(mNumRows==otherMatrix.GetNumberRows());
 assert(mNumCols==otherMatrix.GetNumberCols());
 assert(mNumLayers==otherMatrix.GetNumberLayers());

 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    mData[i][j][k]=otherMatrix.mData[i][j][k];
   }
  }
 }
}

// Unary +
Int3DMatrix Int3DMatrix::operator+() const
{
 Int3DMatrix mat(mNumRows,mNumCols,mNumLayers);
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    mat(i+1,j+1,k+1)=mData[i][j][k];
   }
  }
 }
 return mat;
}

// Unary -
Int3DMatrix Int3DMatrix::operator-() const
{
 Int3DMatrix mat(mNumRows,mNumCols,mNumLayers);
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    mat(i+1,j+1,k+1)=-mData[i][j][k];
   }
  }
 }
 return mat;
}

// Binary +
Int3DMatrix Int3DMatrix::operator+(const Int3DMatrix& m1) const
{
 //Check they are the same size to perform matrix addition
 assert(mNumRows==m1.GetNumberRows());
 assert(mNumCols==m1.GetNumberCols());
 assert(mNumLayers==m1.GetNumberLayers());

 Int3DMatrix mat(mNumRows,mNumCols,mNumLayers);
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    mat(i+1,j+1,k+1)=mData[i][j][k]+m1.mData[i][j][k];
   }
  }
 }
 return mat;

}

// Binary -
Int3DMatrix Int3DMatrix::operator-(const Int3DMatrix& m1) const
{
 //Check they are the same size to perform matrix subtraction
 assert(mNumRows==m1.GetNumberRows());
 assert(mNumCols==m1.GetNumberCols());
 assert(mNumLayers==m1.GetNumberLayers());

  Int3DMatrix mat(mNumRows,mNumCols,mNumLayers);
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    mat(i+1,j+1,k+1)=mData[i][j][k]-m1.mData[i][j][k];
   }
  }
 }
 return mat;
}











