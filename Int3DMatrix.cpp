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

//Overloading Output operator
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
/*
These methods set a Row,Col or Layer 2d matrix to a particular other 2d matrix
*/
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

//Setting Vectors
void Int3DMatrix::SetRowVector(int Row,int Layer, IntVector Vec)
{
 //Check Valid Row and Layer are selected
 assert(Row>0);
 assert(Row<=mNumRows);
 assert(Layer>0);
 assert(Layer<=mNumLayers);
 //Check Vector is valid for insertion
 assert(Vec.GetSize()==mNumCols);

 //Insert Values
 for(int j=0; j<mNumCols; j++)
 {
  mData[Row-1][j][Layer-1]=Vec(j+1);
 }
}
void Int3DMatrix::SetColVector(int Col, int Layer, IntVector Vec)
{
 //Check Valid Row and Layer are selected
 assert(Col>0);
 assert(Col<=mNumCols);
 assert(Layer>0);
 assert(Layer<=mNumLayers);
 //Check Vector is valid for insertion
 assert(Vec.GetSize()==mNumRows);

 //Insert Values
 for(int i=0; i<mNumRows; i++)
 {
  mData[i][Col-1][Layer-1]=Vec(i+1);
 }
}
void Int3DMatrix::SetLayerVector(int Row, int Col, IntVector Vec)
{
 //Check Valid Row and Layer are selected
 assert(Row>0);
 assert(Row<=mNumRows);
 assert(Col>0);
 assert(Col<=mNumCols);
 //Check Vector is valid for insertion
 assert(Vec.GetSize()==mNumLayers);

 //Insert Values
 for(int k=0; k<mNumLayers; k++)
 {
  mData[Row-1][Col-1][k]=Vec(k+1);
 }
}

//Returns a Block of the matrix
/*
This method retrives a smaller block of the 3D matrix
Note. Topleft means closest to (1,1,1)
Also uses 1-based indexing
*/
Int3DMatrix Int3DMatrix::Get3DBlock(int TopLeftI,int TopLeftJ,int TopLeftK,
                                  int rows, int cols, int layers)
{
 //Check the TopLeft's are valid choices
 assert(TopLeftI>0);
 assert(TopLeftI<=mNumRows);
 assert(TopLeftJ>0);
 assert(TopLeftJ<=mNumCols);
 assert(TopLeftK>0);
 assert(TopLeftK<=mNumLayers);
 //Check the Block retrival does not go out of bounds
 assert(TopLeftI+rows-1<=mNumRows);
 assert(TopLeftJ+cols-1<=mNumCols);
 assert(TopLeftK+layers-1<=mNumLayers);

 //Create and return Block
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

//Set Block
/*
This method sets a block of the matrix to another matrix
*/
void Int3DMatrix::Set3DBlock(int TopLeftI, int TopLeftJ, int TopLeftK,
                           Int3DMatrix mat)
{
 //Check the TopLeft's are valid choices
 assert(TopLeftI>0);
 assert(TopLeftI<=mNumRows);
 assert(TopLeftJ>0);
 assert(TopLeftJ<=mNumCols);
 assert(TopLeftK>0);
 assert(TopLeftK<=mNumLayers);
 //Check the Block setting does not go out of bounds
 assert(TopLeftI+mat.GetNumberRows()-1<=mNumRows);
 assert(TopLeftJ+mat.GetNumberCols()-1<=mNumCols);
 assert(TopLeftK+mat.GetNumberLayers()-1<=mNumLayers);

 //Set Block
 for(int i=0; i<mat.GetNumberRows(); i++)
 {
  for(int j=0; j<mat.GetNumberCols(); j++)
  {
   for(int k=0; k<mat.GetNumberLayers(); k++)
   {
    mData[TopLeftI-1+i][TopLeftJ-1+j][TopLeftK-1+k]=
    mat(i+1,j+1,k+1);
   }
  }
 }
}

//Fill
/*
This method fills the matrix with certain value
*/
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

//Extending
/*
These methods extend the dimensions of the current matrix
*/
void Int3DMatrix::ExtendRow(const int ExtendBy)
{
 //Create temp storage
 Int3DMatrix Temp(*this);

 //Delete storage
  for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part

 //Alter Size
 int OldNumRows=mNumRows;
 mNumRows=mNumRows+ExtendBy;

 //Create Storage
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Insert Values
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    if(i<OldNumRows)
    {
     mData[i][j][k]=Temp(i+1,j+1,k+1);
    }
    else
    {
     mData[i][j][k]=0;
    }
   }
  }
 }
}
void Int3DMatrix::ExtendCol(const int ExtendBy)
{
//Create temp storage
 Int3DMatrix Temp(*this);

 //Delete storage
  for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part

 //Alter Size
 int OldNumCols=mNumCols;
 mNumCols=mNumCols+ExtendBy;

 //Create Storage
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Insert Values
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    if(j<OldNumCols)
    {
     mData[i][j][k]=Temp(i+1,j+1,k+1);
    }
    else
    {
     mData[i][j][k]=0;
    }
   }
  }
 }
}
void Int3DMatrix::ExtendLayer(const int ExtendBy)
{
//Create temp storage
 Int3DMatrix Temp(*this);

 //Delete storage
  for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part

 //Alter Size
 int OldNumLayers=mNumLayers;
 mNumLayers=mNumLayers+ExtendBy;

 //Create Storage
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Insert Values
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    if(k<OldNumLayers)
    {
     mData[i][j][k]=Temp(i+1,j+1,k+1);
    }
    else
    {
     mData[i][j][k]=0;
    }
   }
  }
 }
}

//Adding
/*
These methods add a Row, Col or Layer Matrix(full of zeroes)
Note. They have the option to add to either side of the given Row,Col or Layer
*/
void Int3DMatrix::AddRow(const int Row, bool below/*=true*/)
{
//Create temp storage
 Int3DMatrix Temp(*this);

 //Delete storage
  for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part

 //Alter Size
 mNumRows=mNumRows+1;

 //Create Storage
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Insert Values
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    if(below==true) //insert zeroes at Row+1
    {
     if(i<Row)
     {
      mData[i][j][k]=Temp(i+1,j+1,k+1);
     }
     else if(i>Row)
     {
      mData[i][j][k]=Temp(i,j+1,k+1);
     }
     else
     {
      mData[i][j][k]=0;
     }
    }
    else //If above insert zeroes at Row
    {
     if(i<Row-1)
     {
      mData[i][j][k]=Temp(i+1,j+1,k+1);
     }
     else if(i>Row-1)
     {
      mData[i][j][k]=Temp(i,j+1,k+1);
     }
     else
     {
      mData[i][j][k]=0;
     }
    }
   }
  }
 }
}
void Int3DMatrix::AddCol(const int Col, bool right/*=true*/)
{
//Create temp storage
 Int3DMatrix Temp(*this);

 //Delete storage
  for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part

 //Alter Size
 mNumCols=mNumCols+1;

 //Create Storage
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Insert Values
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    if(right==true) //Insert zeroes at Col+1
    {
     if(j<Col)
     {
      mData[i][j][k]=Temp(i+1,j+1,k+1);
     }
     else if(j>Col)
     {
      mData[i][j][k]=Temp(i+1,j,k+1);
     }
     else
     {
      mData[i][j][k]=0;
     }
    }
    else //If left insert zeroes at Col
    {
     if(j<Col-1)
     {
      mData[i][j][k]=Temp(i+1,j+1,k+1);
     }
     else if(j>Col-1)
     {
      mData[i][j][k]=Temp(i+1,j,k+1);
     }
     else
     {
      mData[i][j][k]=0;
     }
    }
   }
  }
 }
}
void Int3DMatrix::AddLayer(const int Layer, bool backwards/*=true*/)
{
 //Create temp storage
 Int3DMatrix Temp(*this);

 //Delete storage
  for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part

 //Alter Size
 mNumLayers=mNumLayers+1;

 //Create Storage
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Insert Values
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    if(backwards==true) //Insert zeroes at Layer+1
    {
     if(k<Layer)
     {
      mData[i][j][k]=Temp(i+1,j+1,k+1);
     }
     else if(k>Layer)
     {
      mData[i][j][k]=Temp(i+1,j+1,k);
     }
     else
     {
      mData[i][j][k]=0;
     }
    }
    else //If forward insert zereoes at Layer
    {
     if(k<Layer-1)
     {
      mData[i][j][k]=Temp(i+1,j+1,k+1);
     }
     else if(k>Layer-1)
     {
      mData[i][j][k]=Temp(i+1,j+1,k);
     }
     else
     {
      mData[i][j][k]=0;
     }
    }
   }
  }
 }
}

//Deleting
/*
These methods delete a 2d matrix for the selected Row, Col or Layer
*/
void Int3DMatrix::DeleteRow(const int Row)
{
//Create temp storage
 Int3DMatrix Temp(*this);

 //Delete storage
  for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part

 //Alter Size
 mNumRows=mNumRows-1;

 //Create Storage
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Insert Values
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    //Copy the temp skipping the 'Row' Row
    if(i<Row-1)
    {
     mData[i][j][k]=Temp(i+1,j+1,k+1);
    }
    else
    {
     mData[i][j][k]=Temp(i+2,j+1,k+1);
    }
   }
  }
 }
}
void Int3DMatrix::DeleteCol(const int Col)
{
//Create temp storage
 Int3DMatrix Temp(*this);

 //Delete storage
  for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part

 //Alter Size
 mNumCols=mNumCols-1;

 //Create Storage
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Insert Values
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    //Copy the temp skipping the 'Layer' Layer
    if(j<Col-1)
    {
     mData[i][j][k]=Temp(i+1,j+1,k+1);
    }
    else
    {
     mData[i][j][k]=Temp(i+1,j+2,k+1);
    }
   }
  }
 }
}
void Int3DMatrix::DeleteLayer(const int Layer)
{
//Create temp storage
 Int3DMatrix Temp(*this);

 //Delete storage
  for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part

 //Alter Size
 mNumLayers=mNumLayers-1;

 //Create Storage
 mData= new int** [mNumRows];
 for(int i=0; i<mNumRows; i++)
 {
  mData[i]=new int* [mNumCols];
  for(int j=0; j<mNumCols; j++)
  {
   mData[i][j]= new int [mNumLayers];
  }
 }

 //Insert Values
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    //Copy the temp skipping the 'Layer' Layer
    if(k<Layer-1)
    {
     mData[i][j][k]=Temp(i+1,j+1,k+1);
    }
    else
    {
     mData[i][j][k]=Temp(i+1,j+1,k+2);
    }
   }
  }
 }
}





