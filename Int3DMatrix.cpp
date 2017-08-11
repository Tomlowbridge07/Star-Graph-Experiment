#include "Int3DMatrix.hpp"
#include<cassert>

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
