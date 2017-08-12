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

 std::cout<<"Rows="<<mNumRows;
 std::cout<<"Cols="<<mNumCols;
 std::cout<<"Layers="<<mNumLayers;

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

 std::cout<<"hi";
 int counter=0;

 //Copy values from other matrix
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   for(int k=0; k<mNumLayers; k++)
   {
    counter=counter+1;
    std::cout<<"\nCounter="<<counter;
    std::cout<<"i="<<i<<"j="<<j<<"k="<<k;
    mData[i][j][k]=other3DMatrix.mData[i][j][k];
   }
  }
 }
 std::flush(std::cout<<"\n Complete");
}


//Desctructor
Int3DMatrix::~Int3DMatrix()
{
 for(int i=0; i<mNumRows; i++)
 {
  for(int j=0; j<mNumCols; j++)
  {
   delete[] mData[i][j]; //Delete Layer pointer part
   std::cout<<"\ndelete"<<"i="<<i<<"j="<<j;
  }
  delete[] mData[i]; //Delete Column pointer part
 }
 delete[] mData; //Delete Row pointer part
 std::cout<<"\n Destructor sucess";
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














