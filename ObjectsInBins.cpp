#include "ObjectsInBins.hpp"
#include "UsefulFunctions.hpp"

//Constructor
ObjectsInBins::ObjectsInBins(int NumObjects, int NumBins)
{
 //Store Variables
 mNumObjects=NumObjects;
 mNumBins=NumBins;

 //Store number of seperators
 mNumSeperators=mNumBins-1;
 mNumSpaces=mNumObjects+mNumSeperators;

 //Calculate number of combinations
 mNumCombinations=combinatorial(mNumSpaces,mNumSeperators);
 std::flush(std::cout<<"combs of"<<mNumSpaces<<" and "<<mNumSeperators<< " is "<<mNumCombinations<<"\n");

 //Store null matrices
 mpSeperatorMat=NULL;
 mpOptionsLeft=NULL;
 mpNumberInBins=NULL;

 //Compute Seperator matrix
 ComputeSeperatorMat();
}

//Getters and Setters
IntMatrix ObjectsInBins::GetSeperatorMatrix()
{
 return (*mpSeperatorMat);
}

//Destructor
ObjectsInBins::~ObjectsInBins()
{
delete mpSeperatorMat;
delete mpOptionsLeft;
}

void ObjectsInBins::ComputeSeperatorMat()
{
 //We compute the seperator Matrix which stores the positions of
 delete mpSeperatorMat;
 delete mpOptionsLeft;
 mpSeperatorMat=new IntMatrix(mNumCombinations,mNumSeperators);
 mpOptionsLeft=new IntMatrix(mNumCombinations,mNumSpaces);

 std::flush(std::cout<<"Here");

 //Set up options
 IntVector Asscending(mNumSpaces);
 Asscending.SetToIdentityPerm();
 int i=1;
 while(i<=mNumSpaces)
 {
  mpOptionsLeft->SetRow(i,Asscending);
  i=i+1;
 }


 //Initialise
 i=1;
 while(i<=mNumSpaces)
 {
  //Set initial sepeator
  (*mpSeperatorMat)(i,1)=i;

  //Remove option from options matrix
  (*mpOptionsLeft)(i,i)=0;

  i=i+1;
 }

 int IterationNum=1;
 int NumSpacesLeft=mNumObjects+mNumSeperators-IterationNum;
 i=1;
 int j=1;
 while(IterationNum<mNumSeperators) //per iteration places one new seperator in each
 {
  //Store Temp matrix
  IntMatrix SepTemp((*mpSeperatorMat));
  IntMatrix OptTemp((*mpOptionsLeft));


  int counter=1;
  int row=1;
  //Now block out next step of matrix (per line we add mNumObjects+mNumSeperators-IterationNum strategies)
  while(SepTemp(row,IterationNum)!=0)
  {
   j=1;
   while(j<=mNumSpaces)
   {
    if(OptTemp(row,j)!=0 && j>=SepTemp(row,IterationNum))
    {
     //Copy current row
     mpSeperatorMat->SetRow(counter,SepTemp.GetRow(row));

    //Insert next choice
    (*mpSeperatorMat)(counter,IterationNum+1)=j;

    //copy options and remove one just picked for next iteration
    mpOptionsLeft->SetRow(counter,OptTemp.GetRow(row));
    (*mpOptionsLeft)(counter,j)=0;

    //Progress counter on to move to next row
    counter=counter+1;
    }
    j=j+1;
   }
   row=row+1;
  }
  IterationNum=IterationNum+1;
 }

}
