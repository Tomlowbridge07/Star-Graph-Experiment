#include "SpecialGraphGenerator.hpp"

#include<cassert>

//Standard Constructor
SpecialGraphGenerator::SpecialGraphGenerator()
{
 mpAdjacencyMatrix=NULL;
}

//Destructor
SpecialGraphGenerator::~SpecialGraphGenerator()
{
 delete mpAdjacencyMatrix;
}

//Line Graph Constructor
void SpecialGraphGenerator::GenerateLine(int n)
{
 //Create Storage for matrix
 delete mpAdjacencyMatrix;
 mpAdjacencyMatrix=new IntMatrix(n,n);
 mpAdjacencyMatrix->Fill(0);

 //Place 1 for Adjacent nodes
 int i=1;
 while(i<=n)
 {
  if(i==1)
  {
   (*mpAdjacencyMatrix)(i,i)=1;
   (*mpAdjacencyMatrix)(i,i+1)=1;
  }
  else if(i==n)
  {
   (*mpAdjacencyMatrix)(i,i-1)=1;
   (*mpAdjacencyMatrix)(i,i)=1;
  }
  else
  {
   (*mpAdjacencyMatrix)(i,i-1)=1;
   (*mpAdjacencyMatrix)(i,i)=1;
   (*mpAdjacencyMatrix)(i,i+1)=1;
  }
  i=i+1;
 }
}

//Star Graph Constructor
void SpecialGraphGenerator::GenerateStar(int n)
{
 //Create Storage for matrix
 delete mpAdjacencyMatrix;
 mpAdjacencyMatrix=new IntMatrix(n+1,n+1);
 mpAdjacencyMatrix->Fill(0);

 //Place 1 for Adjacent nodes
 int i=1;
 int j=1;
 while(i<=n)
 {
  if(i==1)
  {
   (*mpAdjacencyMatrix)(i,i)=1;
   j=1;
   while(j<=n)
   {
    (*mpAdjacencyMatrix)(i,j+1)=1;
    j=j+1;
   }
  }
  else
  {
   (*mpAdjacencyMatrix)(i,1)=1;
   (*mpAdjacencyMatrix)(i,i)=1;
  }
  i=i+1;
 }
}

//Extended Star Graph Constructor
void SpecialGraphGenerator::GenerateExtendedStar(int n, int k)
{
  //Create Storage for matrix
 delete mpAdjacencyMatrix;
 mpAdjacencyMatrix=new IntMatrix(n+k+1,n+k+1);
 mpAdjacencyMatrix->Fill(0);

 //Place 1 for Adjacent nodes
 int i=1;
 int j=1;
 while(i<=n+k+1)
 {
  if(i<=k+1) //if in line segment(branch)
  {
   if(i==1)
   {
    (*mpAdjacencyMatrix)(i,i)=1;
    (*mpAdjacencyMatrix)(i,i+1)=1;
   }
   else
   {
    (*mpAdjacencyMatrix)(i,i-1)=1;
    (*mpAdjacencyMatrix)(i,i)=1;
    (*mpAdjacencyMatrix)(i,i+1)=1;
   }
  }
  else if(i==k+2)
  {
   (*mpAdjacencyMatrix)(i,i-1)=1;
   (*mpAdjacencyMatrix)(i,i)=1;
   j=1;
   while(j<=n-1)
   {
    (*mpAdjacencyMatrix)(i,j+k+2)=1;
    j=j+1;
   }
  }
  else
  {
   (*mpAdjacencyMatrix)(i,k+2)=1;
   (*mpAdjacencyMatrix)(i,i)=1;
  }
  i=i+1;
 }
}


//General (Extended) Star Graph
void SpecialGraphGenerator::GenerateGeneralExtendedStar(int n, IntVector k)
{
 //Check assumptions about vector
 assert(k.GetSize()<=n);

 //Order vector from highest to lowest
 k.BubbleSort();
 k.Reverse();

 int numextensions=k.GetSize();
 int sum=k.Sum();

 //Create Storage for matrix
 delete mpAdjacencyMatrix;
 mpAdjacencyMatrix=new IntMatrix(n+sum+1,n+sum+1);
 mpAdjacencyMatrix->Fill(0);

 //Start Construction
 int extensionnumber=1;
 int priorbranchcount=0;
 int centreid=n+sum+1;
 int i=1;
 int j=1;
 while(extensionnumber<=numextensions) //In each extension run through the line
 {
  i=1;
  while(i<=k(extensionnumber)+1)
  {
   if(i==1) //Start of line segment
   {
    (*mpAdjacencyMatrix)(priorbranchcount+i,priorbranchcount+i)=1;
    (*mpAdjacencyMatrix)(priorbranchcount+i,priorbranchcount+i+1)=1;
   }
   else if(i==k(extensionnumber)+1) //Attacthed to centre
   {
    (*mpAdjacencyMatrix)(priorbranchcount+i,priorbranchcount+i-1)=1;
    (*mpAdjacencyMatrix)(priorbranchcount+i,priorbranchcount+i)=1;
    (*mpAdjacencyMatrix)(priorbranchcount+i,centreid)=1;

    (*mpAdjacencyMatrix)(centreid,priorbranchcount+i)=1; //This is the centres connection which is added her to make it easier
   }
   else //Interal line segment pieces
   {
    (*mpAdjacencyMatrix)(priorbranchcount+i,priorbranchcount+i-1)=1;
    (*mpAdjacencyMatrix)(priorbranchcount+i,priorbranchcount+i)=1;
    (*mpAdjacencyMatrix)(priorbranchcount+i,priorbranchcount+i+1)=1;
   }
   i=i+1;
  }
  priorbranchcount=priorbranchcount+k(extensionnumber)+1;
  extensionnumber=extensionnumber+1;
 }
 //Deal with singletons
 int numsingletons=n+sum+1-(priorbranchcount)-1; //Note. -1 for centre
 i=1;
 while(i<=numsingletons)
 {
  (*mpAdjacencyMatrix)(priorbranchcount+i,priorbranchcount+i)=1;
  (*mpAdjacencyMatrix)(priorbranchcount+i,centreid)=1;
  (*mpAdjacencyMatrix)(centreid,priorbranchcount+i)=1;
  i=i+1;
 }
 //Deal with centret to itsself
 (*mpAdjacencyMatrix)(n+sum+1,n+sum+1)=1;
}

//Symmetric Dual Star Graph
//Note. The labeling is 1,...,n are the left nodes then n+1 is centre
//Next centre is n+l+2 and n+l+3,...,2n+l+2 are the right nodes
void SpecialGraphGenerator::GenerateSymmetricDualStar(int n, int l)
{
 //Create Storage for matrix
 delete mpAdjacencyMatrix;
 mpAdjacencyMatrix=new IntMatrix(2*n+l+2,2*n+l+2);
 mpAdjacencyMatrix->Fill(0);

 //Place 1 for adjacent nodes
 int i=1;
 int j=1;
 while(i<=2*n+l+2)
 {
  if(i<=n) //Left external nodes are self adjacent and adjacent to centre
  {
   (*mpAdjacencyMatrix)(i,i)=1;
   (*mpAdjacencyMatrix)(i,n+1)=1;
   //We also do the reverse now
   (*mpAdjacencyMatrix)(n+1,i)=1;
  }
  if(i==n+1) //Left centre is adjacent to itself and next on line (and other lefts which is already connected to)
  {
   (*mpAdjacencyMatrix)(i,i)=1;
   (*mpAdjacencyMatrix)(i,n+2)=1;
  }
  if(i>=n+2 && i<=n+l+1) //Along the line are connected behind,self and infront
  {
   (*mpAdjacencyMatrix)(i,i-1)=1;
   (*mpAdjacencyMatrix)(i,i)=1;
   (*mpAdjacencyMatrix)(i,i+1)=1;
  }
  if(i==n+l+2) //Right centre connected to behind,self (and right nodes which will be included later)
  {
   (*mpAdjacencyMatrix)(i,i-1)=1;
   (*mpAdjacencyMatrix)(i,i)=1;
  }
  if(i>=n+l+3) //Right Nodes
  {
   (*mpAdjacencyMatrix)(i,i)=1;
   (*mpAdjacencyMatrix)(i,n+l+2)=1;
   //And reverse
   (*mpAdjacencyMatrix)(n+l+2,i)=1;
  }
  i=i+1;
 }
}

//Setters and Getters
IntMatrix SpecialGraphGenerator::GetAdjacenyMatrix()
{
 return (*mpAdjacencyMatrix);
}
