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

// Scalar multiplication
Int3DMatrix Int3DMatrix::operator*(int a) const
{
 Int3DMatrix mat(mNumRows,mNumCols,mNumLayers);
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    mat(i+1,j+1,k+1)=a*mData[i][j][k];
   }
  }
 }
 return mat;
}

//Retriving 2d Matrix
/*
This method retrive matrixes for a particular row,col or layer
Note. It uses 1-based index
*/
//Retruned matrix is of size [ColxLayers]
IntMatrix Int3DMatrix::GetRowMatrix(int Row) const
{
 //Check valid row is chosen
 assert(Row>0);
 assert(Row<=mNumRows);

 //Form layer matrix
 IntMatrix RowMatrix(mNumCols,mNumLayers);
 for(int j=0; j<mNumCols; j++)
 {
  for(int k=0; k<mNumLayers; k++)
  {
   RowMatrix(j+1,k+1)=mData[Row-1][j][k];
  }
 }
 return RowMatrix;
}
//Retruned matrix is of size [RowxLayers]
IntMatrix Int3DMatrix::GetColMatrix(int Col) const
{
 //Check valid col is chosen
 assert(Col>0);
 assert(Col<=mNumCols);

 //Form layer matrix
 IntMatrix ColMatrix(mNumRows,mNumLayers);
 for(int i=0; i<mNumRows; i++)
 {
  for(int k=0; k<mNumLayers; k++)
  {
   ColMatrix(i+1,k+1)=mData[i][Col-1][k];
  }
 }
 return ColMatrix;
}
//Retruned matrix is of size [RowxCols]
IntMatrix Int3DMatrix::GetLayerMatrix(int Layer) const
{
 //Check valid layer is chosen
 assert(Layer>0);
 assert(Layer<=mNumLayers);

 //Form layer matrix
 IntMatrix LayerMatrix(mNumRows,mNumCols);
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   LayerMatrix(i+1,j+1)=mData[i][j][Layer-1];
  }
 }
 return LayerMatrix;
}

//Setting 2d Matrices
void Int3DMatrix::SetRowMatrix(int Row, IntMatrix mat)
{
 //Check valid row is chosen
 assert(Row>0);
 assert(Row<=mNumRows);

 //Check valid matrix is selected to be placed i.e of size [ColsxLayers]
 assert(mat.GetNumberOfRows()==mNumCols);
 assert(mat.GetNumberOfColumns()==mNumLayers);

 for(int j=0; j<mNumCols; j++)
 {
  for(int k=0; k<mNumLayers; k++)
  {
   mData[Row-1][j][k]=mat(j+1,k+1);
  }
 }
}
void Int3DMatrix::SetColMatrix(int Col, IntMatrix mat)
{
 //Check valid row is chosen
 assert(Col>0);
 assert(Col<=mNumRows);

 //Check valid matrix is selected to be placed i.e of size [RowsxLayers]
 assert(mat.GetNumberOfRows()==mNumRows);
 assert(mat.GetNumberOfColumns()==mNumLayers);

 for(int i=0; i<mNumRows; i++)
 {
  for(int k=0; k<mNumLayers; k++)
  {
   mData[i][Col-1][k]=mat(i+1,k+1);
  }
 }
}
void Int3DMatrix::SetLayerMatrix(int Layer, IntMatrix mat)
{
 //Check valid row is chosen
 assert(Layer>0);
 assert(Layer<=mNumRows);

 //Check valid matrix is selected to be placed i.e of size [RowsxCols]
 assert(mat.GetNumberOfRows()==mNumRows);
 assert(mat.GetNumberOfColumns()==mNumCols);

 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j][Layer-1]=mat(i+1,j+1);
  }
 }
}


//Returns a Block of the matrix
/*
This method retrives a smaller block of the 3D matrix
Note. Topleft means closest to (1,1,1)
Also uses 1-based indexing
*/
Int3DMatrix Int3DMatrix::GetBlock(int TopLeftI,int TopLeftJ,int TopLeftK,
                                  int rows, int cols, int layers)
{
 Int3DMatrix Block(rows,cols,layers);
 for(int i=0; i<rows; i++)
 {
  for(int j=0; j<cols; j++)
  {
   for(int k=0; k<layers; k++)
   {
    Block(i+1,j+1,k+1)=mData[TopLeftI-1+i][TopLeftJ-1+j][TopLeftK-1+k];
   }
  }
 }
 return Block;
}


//Fill
void Int3DMatrix::Fill(const int FillValue)
{
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    mData[i][j][k]=FillValue;
   }
  }
 }
}









