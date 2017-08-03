#include "AbstractPatroller.hpp"

#include<assert.h>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "IntMatrix.hpp"
#include "IntVector.hpp"

 //Standard Constructor
AbstractPatroller:: AbstractPatroller(IntMatrix& AdjacencyMatrix,const int GameTime,const int AttackTime)
{
 //Check the Adjacency matrix is valid
 assert(AdjacencyMatrix.IsSquare());
 assert(AdjacencyMatrix.IsDiagonal(1));
 assert(AdjacencyMatrix.IsSymmetric());

 //Store the private variables
 mpAdjacencyMatrix=new IntMatrix(AdjacencyMatrix);
 mNumNodes=AdjacencyMatrix.GetNumberOfColumns();
 assert(GameTime-AttackTime>=0);
 mGameTime=GameTime;
 mAttackTime=AttackTime;

 //Find Pure Strategies and Payoffs
 UpdatePurePatrollerStrategies();
 UpdatePureAttackerStrategies();
 UpdatePurePayoffMatrix();

 //Store Options (to allow domination)
 mNumPurePatrolOptions=mNumPurePatrols;
 mpPurePatrollingOptions=new IntMatrix(*mpPurePatrollerStrategies);
 mNumPureAttackOptions=mNumPureAttacks;
 mpPureAttackingOptions=new IntMatrix(*mpPureAttackerStrategies);
 mpPureWinMatrix=new IntMatrix(*mpPurePayoffMatrix);

 //Removed dominated and update
 RemoveDominatedWaitingStrategies();
 RemovePenultimateAttackStrategies();
 //RemovePayoffDominatedStrategies();
 UpdatePureWinMatrix();
}

 //Specialised Constructor from stored files
AbstractPatroller::AbstractPatroller(IntMatrix& AdjacencyMatrix, const int GameTime,const int AttackTime,
                   std::string PurePatrollerFile,std::string PureAttackerFile,
                   std::string PurePayoffFile)
{
 //Store the private variables
 mpAdjacencyMatrix=new IntMatrix(AdjacencyMatrix);
 mNumNodes=AdjacencyMatrix.GetNumberOfColumns();
 assert(GameTime-AttackTime>=0);
 mGameTime=GameTime;
 mAttackTime=AttackTime;

 //Read pure Strategies and Payoffs
 ReadPurePatrollerFile(PurePatrollerFile);
 ReadPureAttackerFile(PureAttackerFile);
 ReadPurePayoffFile(PurePayoffFile);

 //Store Options (to allow domination)
 mNumPurePatrolOptions=mNumPurePatrols;
 mpPurePatrollingOptions=new IntMatrix(*mpPurePatrollerStrategies);
 mNumPureAttackOptions=mNumPureAttacks;
 mpPureAttackingOptions=new IntMatrix(*mpPureAttackerStrategies);
 mpPureWinMatrix=new IntMatrix(*mpPurePayoffMatrix);

 //Removed dominated and update
 //RemovePayoffDominatedStrategies();
 //UpdatePurePayoffMatrix();
}

//Null constructor
AbstractPatroller::AbstractPatroller()
{
  mpAdjacencyMatrix=NULL;
  mpPurePatrollingOptions=NULL;
  mpPureAttackingOptions=NULL;
  mpPureWinMatrix=NULL;
}

 //Destructor
 AbstractPatroller::~AbstractPatroller()
 {
  delete mpAdjacencyMatrix;
  delete mpPurePatrollingOptions;
  delete mpPureAttackingOptions;
  delete mpPureWinMatrix;
 }

//Setters and Getters
/*
These can be used to set and get the private variables
*/
void AbstractPatroller::SetAdjacenyMatrix(IntMatrix& AdjacencyMatrix)
{
 assert(AdjacencyMatrix.IsSquare());
 assert(AdjacencyMatrix.IsDiagonal(1));
 assert(AdjacencyMatrix.IsSymmetric());
 mpAdjacencyMatrix=&AdjacencyMatrix;
 mNumNodes=AdjacencyMatrix.GetNumberOfColumns();
 delete mpPurePatrollerStrategies;
 UpdatePurePatrollerStrategies();
 delete mpPureAttackerStrategies;
 UpdatePureAttackerStrategies();
 delete mpPurePayoffMatrix;
 UpdatePurePayoffMatrix();
 delete mpPurePatrollingOptions;
 mpPurePatrollingOptions=new IntMatrix(*mpPurePatrollerStrategies);
 delete mpPureAttackingOptions;
 mpPureAttackingOptions=new IntMatrix(*mpPureAttackerStrategies);
 delete mpPureWinMatrix;
 mpPureWinMatrix=new IntMatrix(*mpPurePayoffMatrix);

  //Removed dominated and update
 RemoveDominatedWaitingStrategies();
 RemovePenultimateAttackStrategies();
 //RemovePayoffDominatedStrategies();
 UpdatePureWinMatrix();
}
void AbstractPatroller::SetGameTime(const int GameTime)
{
 assert(GameTime-mAttackTime>=0);
 mGameTime=GameTime;
 delete mpPurePatrollerStrategies;
 UpdatePurePatrollerStrategies();
 delete mpPureAttackerStrategies;
 UpdatePureAttackerStrategies();
 delete mpPurePayoffMatrix;
 UpdatePurePayoffMatrix();
 delete mpPurePatrollingOptions;
 mNumPurePatrolOptions=mNumPurePatrols;
 mpPurePatrollingOptions=new IntMatrix(*mpPurePatrollerStrategies);
 delete mpPureAttackingOptions;
 mNumPureAttackOptions=mNumPureAttacks;
 mpPureAttackingOptions=new IntMatrix(*mpPureAttackerStrategies);
 delete mpPureWinMatrix;
 mpPureWinMatrix=new IntMatrix(*mpPurePayoffMatrix);
 //Removed dominated and update
 RemoveDominatedWaitingStrategies();
 RemovePenultimateAttackStrategies();
 //RemovePayoffDominatedStrategies();
  UpdatePureWinMatrix();
}
void AbstractPatroller::SetAttackTime(const int AttackTime)
{
 assert(mGameTime-AttackTime>=0);
 mAttackTime=AttackTime;
 delete mpPureAttackerStrategies;
 UpdatePureAttackerStrategies();
 delete mpPurePayoffMatrix;
 UpdatePurePayoffMatrix();
 mNumPureAttackOptions=mNumPureAttacks;
 delete mpPureAttackingOptions;
 mpPureAttackingOptions=new IntMatrix(*mpPureAttackerStrategies);
 delete mpPureWinMatrix;
 mpPureWinMatrix=new IntMatrix(*mpPurePayoffMatrix);

 //Removed dominated and update
 RemovePenultimateAttackStrategies();
 //RemovePayoffDominatedStrategies();
 UpdatePureWinMatrix();
}
IntMatrix AbstractPatroller::GetAdjacenyMatrix() const
{
 return *mpAdjacencyMatrix;
}
int AbstractPatroller::GetNumNodes() const
{
 return mNumNodes;
}
int AbstractPatroller::GetGameTime() const
{
 return mGameTime;
}
int AbstractPatroller::GetAttackTime() const
{
 return mAttackTime;
}
IntMatrix AbstractPatroller::GetPurePatrollingStrategies() const
{
 return (*mpPurePatrollerStrategies);
}
IntMatrix AbstractPatroller::GetPureAttackingStrategies() const
{
 return (*mpPureAttackerStrategies);
}
IntMatrix AbstractPatroller::GetPurePayoffMatrix() const
{
 return (*mpPurePayoffMatrix);
}
IntMatrix AbstractPatroller::GetPurePatrollingOptions() const
{
 return (*mpPurePatrollingOptions);
}
IntMatrix AbstractPatroller::GetPureAttackingOptions() const
{
 return (*mpPureAttackingOptions);
}
IntMatrix AbstractPatroller::GetPureWinMatrix() const
{
 return (*mpPureWinMatrix);
}
int AbstractPatroller::GetNumPurePatrols()
{
 return mNumPurePatrols;
}
int AbstractPatroller::GetNumPureAttacks()
{
 return mNumPureAttacks;
}
int AbstractPatroller::GetNumPurePatrolOptions()
{
 return mNumPurePatrolOptions;
}
int AbstractPatroller::GetNumPureAttackOptions()
{
 return mNumPureAttackOptions;
}

//Patrolling Options
/*
This function counts the number of walks from a node to another node of a set length
*/
int AbstractPatroller::CountWalks(int FromNode,int ToNode,int Length)
{
 //Base Cases
 if(Length==0 && FromNode==ToNode)
 {
  return 1;
 }
 else if(Length<=0)
 {
  return 0;
 }

 //Initilize count
 int Count=0;

 //Go to all adjacent and recursively count
 int i=1;
 while(i<=mNumNodes)
 {
  if((*mpAdjacencyMatrix)(FromNode,i)==1)
  {
   Count=Count+CountWalks(i,ToNode,Length-1);
  }
  i=i+1;
 }

 //Return the Counter
 return Count;
}

/*
This function creates a matrix storing all the pure patrolling options
it stores this matrix and the row size of it (i.e number of options)
*/
void AbstractPatroller::UpdatePurePatrollerStrategies()
{
 //Find the number of walks possible
 int i=1;
 int j=1;
 int NumberofOptions=0;

 //Count from every node to every other node , at Game time length
 while(i<=mNumNodes)
 {
  j=1;
  while(j<=mNumNodes)
  {
   NumberofOptions=NumberofOptions+CountWalks(i,j,mGameTime-1);
   j=j+1;
  }
  i=i+1;
 }

 //Store the number of patroller options
 mNumPurePatrols=NumberofOptions;

 //Form alternative adjugate matrix & Adjaceny number vector
 /*The AlteredAdj Matrix stores for a given node what it is adjacent to in order
   ,with the rest filled with -1 (i.e a fill number)
    eg. 1,2,4,-1
        1,2,3,-1
        2,3,-1,-1
        1,4,-1,-1
   The AdjacencyNum Vector stores for each node the number of nodes its adjacent to
   i.e the number of non -1's in the above matrix for rows
   eg. 3,3,2,2 for the above
 */
 IntMatrix AlteredAdj(mNumNodes,mNumNodes);
 IntVector AdjacencyNum(mNumNodes);
 AlteredAdj.Fill(-1);
 i=1;
 j=1;
 int Count=1;
 //each row i will store the nodes adjacent in accending order
 //with empty slots being filled with -1.
 while(i<=mNumNodes)
 {
  j=1;
  Count=1;
  while(j<=mNumNodes)
  {
   if((*mpAdjacencyMatrix)(i,j)==1)
   {
    AlteredAdj(i,Count)=j;
    AdjacencyNum(i)=AdjacencyNum(i)+1;
    Count=Count+1;
   }
   j=j+1;
  }
  i=i+1;
 }

 //Form the patroller options
 /*
  PatrollerOptions is formed recursively from the start point to the end point
  It stores them in ascending order of place.
 */
 IntMatrix PatrollerOptions(NumberofOptions,mGameTime);
 PatrollerOptions.Fill(-1);

 //Set up Starting nodes
 i=1;
 while(i<=mNumNodes)
 {
  PatrollerOptions(i,1)=i;
  i=i+1;
 }

 //Compute recurisvely all walks
 IntMatrix Temp(PatrollerOptions);
 i=1;
 j=1;
 int k=1;
 int m=1;
 int Counter=1;
 int Steps=1;
 while(Steps<mGameTime) //Moving across Time's i.e the column number of the final matrix
 {
  //Copy the Patroller matrix
  Temp=PatrollerOptions;
  Counter=1;
  i=1;
  while(i<=NumberofOptions) //for every row i.e option
  {
   if(Temp(i,Steps)!=-1) //Require this as if we hit -1 , it is just a void
   {
    j=1;
    while(j<=mNumNodes)
    {
     //Identify the end point of the current sequence
     if(Temp(i,Steps)==j)
     {
      //For the end point add in the places it could go from there
      k=1;
      while(k<=AdjacencyNum(j)) //This one sequence becomes Adjacency number now
      {
       m=1;
       while(m<=Steps) //Copy the prior sequence
       {
        PatrollerOptions(Counter,m)=Temp(i,m);
        m=m+1;
       }
       PatrollerOptions(Counter,Steps+1)=AlteredAdj(j,k); //place the new number at the end
       k=k+1;
       Counter=Counter+1;
      }
     }
     j=j+1;
    }
   }
   i=i+1;
  }
 Steps=Steps+1;
 }

 //Store the pure patrolling options
 mpPurePatrollerStrategies=new IntMatrix(PatrollerOptions);
}

//Attacking Options
/*
This function creates a matrix storing all the pure attacking options
it stores this matrix and the row size of it (i.e number of options)
*/
void AbstractPatroller::UpdatePureAttackerStrategies()
{
 //Store the number of options and attacker has i.e number of possible attack times x number of nodes
 int NumberofOptions=mNumNodes*(mGameTime-mAttackTime+1);
 mNumPureAttacks=NumberofOptions;

 //For the matrix form 2 columns , 1st column being node and 2nd being the starting time.
 IntMatrix AttackerOptions(NumberofOptions,2);
 int i=1;
 int j=1;
 while(i<=mNumNodes)
 {
  j=1;
  while(j<=mGameTime-mAttackTime+1)
  {
   AttackerOptions((mGameTime-mAttackTime+1)*(i-1)+j,1)=i;
   AttackerOptions((mGameTime-mAttackTime+1)*(i-1)+j,2)=j;
   j=j+1;
  }
  i=i+1;
 }

 //Store the Pure attacking options
 mpPureAttackerStrategies=new IntMatrix(AttackerOptions);
}

//Intersection
/*
This function finds the number of times a given Patroller strategy and Attacker strategy
intersect
eg. 4 is returned for P=(1,1,2,1,5,) and A=(1,0) m=4, then P=(*,*,-*,ignored) so 3 returned
*/
int AbstractPatroller::Intersection(IntVector PatrollerStrat, IntVector AttackerStrat) const
{
 int Counter=0;
 int i=1;
 int m=AttackerStrat(2);
 while(i<=mGameTime)
 {
  if(PatrollerStrat(i)==AttackerStrat(1) && i>=m && i<m+mAttackTime)
  {
   Counter=Counter+1;
  }
  i=i+1;
 }
 return Counter;
}

//Strategy vs Strategy
/*
 This returns true if it beats and flase if it doesn't beat
*/
bool AbstractPatroller::DoesBeat(IntVector PatrollerStrat, IntVector AttackerStrat) const
{
 if(Intersection(PatrollerStrat,AttackerStrat)==0)
 {
  return false;
 }
 else
 {
  return true;
 }
}

//Pure Payoff Matrix
/*
This function finds a matrix of play every pure strategy.
Storing a 1 if the patroller wins and 0 if the attacker wins
*/
void AbstractPatroller::UpdatePurePayoffMatrix()
{
 //Form a matrix with rows storing each patrollers options and columns storing each attacker options
 IntMatrix Win(mNumPurePatrols,mNumPureAttacks);

 //For every entry test if it beats then store a value accordingly
 int i=1;
 int j=1;
 while(i<=mNumPurePatrols)
 {
  j=1;
  while(j<=mNumPureAttacks)
  {
   if(DoesBeat(mpPurePatrollerStrategies->GetRow(i),mpPureAttackerStrategies->GetRow(j)))
   {
    Win(i,j)=1;
   }
   else
   {
    Win(i,j)=0;
   }
   j=j+1;
  }
  i=i+1;
 }

 //Store the pure payoff matrix
 mpPurePayoffMatrix=new IntMatrix(Win);
}

//Pure Win Matrix
/*
This function is made to be used to update the Win matrix
Which is a dominated version of the Payoff matrix
*/
void AbstractPatroller::UpdatePureWinMatrix()
{
 //Form a matrix with rows storing each patrollers options and columns storing each attacker options
 IntMatrix Win(mNumPurePatrolOptions,mNumPureAttackOptions);

 //For every entry test if it beats then store a value accordingly
 int i=1;
 int j=1;
 while(i<=mNumPurePatrolOptions)
 {
  j=1;
  while(j<=mNumPureAttackOptions)
  {
   if(DoesBeat(mpPurePatrollingOptions->GetRow(i),mpPureAttackingOptions->GetRow(j)))
   {
    Win(i,j)=1;
   }
   else
   {
    Win(i,j)=0;
   }
   j=j+1;
  }
  i=i+1;
 }

 //Store the pure payoff matrix
 mpPureWinMatrix=new IntMatrix(Win);
}

//Remove Dominated Strategies
/*
This function aims to removed startegies from mpPurePatrollingOptions that are dominated by
knowledge of waiting at the same node for 3 time units or more (if m>=3)
*/
void AbstractPatroller::RemoveDominatedWaitingStrategies()
{
 //Only run if the Game time is above 3 and attack time is above 2 , if not then no chance for domination by waiting
 if(mGameTime>=3 && mAttackTime>=2)
 {
 //Keep track of 3 node
 int i=1;
 int j=1;
 int Check1;
 int Check2;
 int Check3;
 while(i<=mNumPurePatrolOptions)
 {
  j=1;
  while(j<=mGameTime-2)
  {
   //Update nodes
    Check1=(*mpPurePatrollingOptions)(i,j);
    Check2=(*mpPurePatrollingOptions)(i,j+1);
    Check3=(*mpPurePatrollingOptions)(i,j+2);
    if(Check1==Check2 && Check2==Check3) //if the nodes are equal removed them from the pure patrolling options
    {
     mpPurePatrollingOptions->DeleteRow(i);
     mNumPurePatrolOptions=mNumPurePatrolOptions-1;
     i=i-1;
     j=mGameTime;
    }
    j=j+1;
  }
  i=i+1;
 }
}
}


void AbstractPatroller::RemovePenultimateAttackStrategies()
{
 //Only run if the Game time remove all attacks at penultimate attacks
 if(mAttackTime>=3)
 {
  //Identify nodes which are penultimate. Storing 1 if it a penultimate
  IntVector PenultimateYN(mNumNodes);
  int i=1;
  int j=1;
  int NumOfConnections=0;
  int Connection=0;
  while(i<=mNumNodes)
  {
   j=1;
   NumOfConnections=0;
   Connection=0;
   while(j<=mNumNodes)
   {
    if(mpAdjacencyMatrix->Read(i,j)==1 && j!=i)
    {
     NumOfConnections=NumOfConnections+1;
     Connection=j;
    }
    j=j+1;
   }
   if(NumOfConnections==1)
   {
    PenultimateYN(Connection)=1;
   }
   i=i+1;
  }

  //std::cout<<PenultimateYN;

  //If there are penultimate nodes then delete them
  if(PenultimateYN.Sum()>0)
  {
   i=1;
   j=1;
   int PenultimateNode=0;
   while(i<=mNumNodes)
   {
    j=1;
    PenultimateNode=i*PenultimateYN(i);
    if(PenultimateNode!=0)
    {
     while(j<=mNumPureAttackOptions)
     {
      if(mpPureAttackingOptions->Read(j,1)==PenultimateNode)
      {
       mpPureAttackingOptions->DeleteRow(j);
       mNumPureAttackOptions=mNumPureAttackOptions-1;
       j=j-1;
      }
      j=j+1;
     }
    }
    i=i+1;
   }
  }
 }
}


/*
This function determines if a Strategy dominates another, return true if so , false otherwise
It takes Payoff vectors for the strategies.
For use in attacker strategy change bool IsPatrollerstart to false i.e its attacker
*/
bool AbstractPatroller::DoesPayoffDominate(IntVector StratPayoff, IntVector DominatedStratPayoff,bool IsPatrollerStrats) const
{
 //Checks
 assert(StratPayoff.GetSize()==DominatedStratPayoff.GetSize());

 //Run through the vector
 int i=1;
 bool Beats=false;
 bool Beaten=false;
 while(i<=StratPayoff.GetSize() && Beaten==false)
 {
  if(pow(-1,(int)IsPatrollerStrats+1)*StratPayoff(i)>pow(-1,(int)IsPatrollerStrats+1)*DominatedStratPayoff(i))
  {
   Beats=true; //it beats it in at least one instance
  }
  if(pow(-1,(int)IsPatrollerStrats+1)*StratPayoff(i)<pow(-1,(int)IsPatrollerStrats+1)*DominatedStratPayoff(i))
  {
   Beaten=true; //it is beaten in at least one instance
  }
  i=i+1;
 }
 if(Beats && !Beaten) //If it beats once and isn't beat then it dominates
 {
  return true;
 }
 else //otherwise it doesn't dominate
 {
  return false;
 }
}

/*
This function removes ooptions from mpPurePatrollingOptions, if it is dominated.
Note. It does NOT update the payoff
*/
void AbstractPatroller::RemovePayoffDominatedStrategies()
{
 bool Removal=true;
 bool StopSearch=false;
 int i=1;
 int j=1;
 while(Removal)
 {
  Removal=false;
  StopSearch=false;
  i=1;
  while(i<=mNumPurePatrolOptions)
  {
   j=1;
   while(j<=mNumPurePatrols && StopSearch==false)
   {
    if(DoesPayoffDominate(mpPureWinMatrix->GetRow(i),mpPureWinMatrix->GetRow(j),true) && j!=i)
    {
     mpPureWinMatrix->DeleteRow(j);
     mpPurePatrollingOptions->DeleteRow(j);
     mNumPurePatrolOptions=mNumPurePatrolOptions-1;
     j=j-1;
     if(i>j)
     {
      i=i-1;
     }
     Removal=true;
     if(i==mNumPurePatrolOptions)
     {
      StopSearch=true;
     }
    }
    j=j+1;
   }
   i=i+1;
  }
  /* This code is currently commented out as it is unsure whether removing attacker strategies
   affects the game.
  i=1;
  StopSearch=false;
  while(i<=mNumPureAttacks)
  {
   j=1;
   while(j<=mNumPureAttacks && StopSearch==false)
   {
    if(DoesPayoffDominate(mpPureWinMatrix->GetCol(i),mpPureWinMatrix->GetCol(j),false) && j!=i)
    {
     mpPureWinMatrix->DeleteCol(j);
     mpPureAttackingOptions->DeleteRow(j);
     mNumPureAttacks=mNumPureAttacks-1;
     j=j-1;
     if(i>j)
     {
      i=i-1;
     }
     Removal=true;
     if(i==mNumPureAttacks)
     {
      StopSearch=true;
     }
    }
    j=j+1;
   }
   i=i+1;
  } */
 }
}

 //Converting Numbers to actual strategies

//These two are for use before removal of dominated strategies has taken place
IntVector AbstractPatroller::ConvertPatrollerStratergyNum(int StratNum)
{
 if(StratNum>=1 && StratNum<=mNumPurePatrols)
 {
  return (mpPurePatrollerStrategies->GetRow(StratNum));
 }
 else
 {
  IntVector Zero(1);
  Zero(1)=0;
  return Zero;
 }
}
IntVector AbstractPatroller::ConvertAttackerStratergyNum(int StratNum)
{
  if(StratNum>=1 && StratNum<=mNumPureAttacks)
  {
   return (mpPureAttackerStrategies->GetRow(StratNum));
  }
  else
  {
   IntVector Zero(1);
   Zero(1)=0;
   return Zero;
  }

}

 //These two are for use after removal of dominated strategies
IntVector AbstractPatroller::ConvertPatrollerOptionNum(int OptionNum)
{
  if(OptionNum>=1 && OptionNum<=mNumPurePatrolOptions)
  {
   return (mpPurePatrollingOptions->GetRow(OptionNum));
  }
  else
  {
   IntVector Zero(1);
   Zero(1)=0;
   return Zero;
  }
}
IntVector AbstractPatroller::ConvertAttackerOptionNum(int OptionNum)
{
  if(OptionNum>=1 && OptionNum<=mNumPureAttackOptions)
  {
   return (mpPureAttackingOptions->GetRow(OptionNum));
  }
  else
  {
   IntVector Zero(1);
   Zero(1)=0;
   return Zero;
  }
}

//Printing and Saving
void AbstractPatroller::PrintPurePatrollerOptions() const
{
 std::cout<<"Displaying Pure Patroller Options(Strategy number against Time): \n";
 int i=0;
 int j=0;
 while(i<=mpPurePatrollingOptions->GetNumberOfRows())
 {
  if(i==0)
  {
   std::cout<<"   ";
  }
  else
  {
   std::cout<<std::setw(3)<<i;
  }
  j=0;
  while(j<mGameTime)
  {
   if(i==0)
   {
    std::cout<<std::setw(4)<<j+1;
   }
   else
   {
   std::cout<<std::setw(4)<<((*mpPurePatrollingOptions)(i,j+1));
   }
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }
}
void AbstractPatroller::SavePurePatrollerOptions(std::string FileName/*="PurePatrollerStrategies.dat"*/) const
{
 std::ofstream outfile;
 outfile.open(FileName);
 outfile<<(mpPurePatrollingOptions->GetNumberOfRows())<<(mpPurePatrollingOptions->GetNumberOfColumns())<<"\n";
 int i=1;
 int j=1;
 while(i<=mpPurePatrollingOptions->GetNumberOfRows())
 {
  j=1;
  while(j<=mGameTime)
  {
   outfile<<((*mpPurePatrollingOptions)(i,j));
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }
 outfile.close();
}
void AbstractPatroller::PrintPureAttackerOptions() const
{
 std::cout<<"Displaying Pure Attacker Options(Strategy number against (Node, Starting Time)): \n";
 int i=0;
 int j=0;
 while(i<=mpPureAttackingOptions->GetNumberOfRows())
 {
  if(i==0)
  {
   std::cout<<"   ";
  }
  else
  {
   std::cout<<std::setw(3)<<i;
  }
  j=0;
  while(j<=1)
  {
   if(i==0)
   {
    std::cout<<std::setw(4)<<"Node"<<" Time";
    j=2;
   }
   else
   {
   std::cout<<std::setw(4)<<((*mpPureAttackingOptions)(i,j+1));
   }
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }
}
void AbstractPatroller::SavePureAttackerOptions(std::string FileName/*="PureAttackerStrategies.dat"*/) const
{
 std::ofstream outfile;
 outfile.open(FileName);
 outfile<<(mpPureAttackingOptions->GetNumberOfRows())<<(mpPureAttackingOptions->GetNumberOfColumns())<<"\n";
 int i=1;
 int j=1;
 while(i<=mpPureAttackingOptions->GetNumberOfRows())
 {
  j=1;
  while(j<=2)
  {
   outfile<<((*mpPureAttackingOptions)(i,j));
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }
 outfile.close();
}
void AbstractPatroller::PrintPureWinMatrix() const
{
 std::cout<<"Displaying Win Matrix(Patroller Strategy number against Attacker Strategy number): \n";
 int i=0;
 int j=0;
 while(i<=mpPureWinMatrix->GetNumberOfRows())
 {
  if(i==0)
  {
   std::cout<<"   ";
  }
  else
  {
   std::cout<<std::setw(3)<<i;
  }
  j=0;
  while(j<=mpPureWinMatrix->GetNumberOfColumns()-1)
  {
   if(i==0)
   {
    std::cout<<std::setw(4)<<j+1;
   }
   else
   {
   std::cout<<std::setw(4)<<((*mpPureWinMatrix)(i,j+1));
   }
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }
}
void AbstractPatroller::AbstractPatroller::SavePureWinMatrix(std::string FileName/*="PureWinMatrix.dat"*/) const
{
 std::ofstream outfile;
 outfile.open(FileName);
 outfile<<(mpPureWinMatrix->GetNumberOfRows())<<(mpPureWinMatrix->GetNumberOfColumns())<<"\n";
 int i=1;
 int j=1;
 while(i<=mpPureWinMatrix->GetNumberOfRows())
 {
  j=1;
  while(j<=2)
  {
   outfile<<((*mpPureWinMatrix)(i,j));
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }
 outfile.close();
}
void AbstractPatroller::PrintPurePatrollerStrategies() const
{
 std::cout<<"Displaying Pure Patroller Strategies(Strategy number against Time): \n";
 int i=0;
 int j=0;
 while(i<=mpPurePatrollerStrategies->GetNumberOfRows())
 {
  if(i==0)
  {
   std::cout<<"   ";
  }
  else
  {
   std::cout<<std::setw(3)<<i;
  }
  j=0;
  while(j<mGameTime)
  {
   if(i==0)
   {
    std::cout<<std::setw(4)<<j+1;
   }
   else
   {
   std::cout<<std::setw(4)<<((*mpPurePatrollerStrategies)(i,j+1));
   }
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }
}
void AbstractPatroller::SavePurePatrollerStrategies(std::string FileName/*="PurePatrollerStrategies.dat"*/) const
{
 std::ofstream outfile;
 outfile.open(FileName);
 outfile<<(mpPurePatrollerStrategies->GetNumberOfRows())<<(mpPurePatrollerStrategies->GetNumberOfColumns())<<"\n";
 int i=1;
 int j=1;
 while(i<=mpPurePatrollerStrategies->GetNumberOfRows())
 {
  j=1;
  while(j<=mGameTime)
  {
   outfile<<((*mpPurePatrollerStrategies)(i,j));
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }
 outfile.close();
}
void AbstractPatroller::PrintPureAttackerStrategies() const
{
 std::cout<<"Displaying Pure Attacker Strategies(Strategy number against (Node, Starting Time)): \n";
 int i=0;
 int j=0;
 while(i<=mpPureAttackerStrategies->GetNumberOfRows())
 {
  if(i==0)
  {
   std::cout<<"   ";
  }
  else
  {
   std::cout<<std::setw(3)<<i;
  }
  j=0;
  while(j<=1)
  {
   if(i==0)
   {
    std::cout<<std::setw(4)<<"Node"<<" Time";
    j=2;
   }
   else
   {
   std::cout<<std::setw(4)<<((*mpPureAttackerStrategies)(i,j+1));
   }
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }
}
void AbstractPatroller::SavePureAttackerStrategies(std::string FileName/*="PureAttackerStrategies.dat"*/) const
{
  std::ofstream outfile;
 outfile.open(FileName);
 outfile<<(mpPureAttackerStrategies->GetNumberOfRows())<<(mpPureAttackerStrategies->GetNumberOfColumns())<<"\n";
 int i=1;
 int j=1;
 while(i<=mpPureAttackerStrategies->GetNumberOfRows())
 {
  j=1;
  while(j<=2)
  {
   outfile<<((*mpPureAttackerStrategies)(i,j));
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }
 outfile.close();
}
void AbstractPatroller::PrintPurePayoffMatrix() const
{
std::cout<<"Displaying Payoff Matrix(Patroller Strategy number against Attacker Strategy number): \n";
 int i=0;
 int j=0;
 while(i<=mpPurePayoffMatrix->GetNumberOfRows())
 {
  if(i==0)
  {
   std::cout<<"   ";
  }
  else
  {
   std::cout<<std::setw(3)<<i;
  }
  j=0;
  while(j<=mpPurePayoffMatrix->GetNumberOfColumns()-1)
  {
   if(i==0)
   {
    std::cout<<std::setw(4)<<j+1;
   }
   else
   {
   std::cout<<std::setw(4)<<((*mpPurePayoffMatrix)(i,j+1));
   }
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }
}
void AbstractPatroller::SavePurePayoffMatrix(std::string FileName/*="PurePayoffMatrix.dat"*/) const
{
  std::ofstream outfile;
 outfile.open(FileName);
 outfile<<(mpPurePayoffMatrix->GetNumberOfRows())<<(mpPurePayoffMatrix->GetNumberOfColumns())<<"\n";
 int i=1;
 int j=1;
 while(i<=mpPurePayoffMatrix->GetNumberOfRows())
 {
  j=1;
  while(j<=mpPurePayoffMatrix->GetNumberOfColumns())
  {
   outfile<<((*mpPurePayoffMatrix)(i,j));
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }
 outfile.close();
}

//Read Files
/*
 This reads a file in Patroller form and stores the relative information.
 It sets mNumPurePatrols and the Patroller Strategy matrix
*/
void AbstractPatroller::ReadPurePatrollerFile(std::string FileName)
{
 //Set up the infile and open
 std::ifstream infile;
 infile.open(FileName);

 //Read the Size of the matrix
 int RowSize;
 int ColSize;
 infile>>RowSize>>ColSize;

 mNumPurePatrols=RowSize;

 //Reset the state of infile
 infile.clear();

 //Form the matrix to store values
 IntMatrix PatrolStrat(mNumPurePatrols,mGameTime);

 //Set elements of the matrix by reading infile
 int j=1;
 int i=1;
 while(i<=mNumPurePatrols)
 {
  j=1;
  while(j<=mGameTime)
  {
   infile>>PatrolStrat(i,j);
   j=j+1;
  }
  i=i+1;
 }

 //close infile
 infile.close();

 //Store the private variable
 mpPurePatrollerStrategies=new IntMatrix(PatrolStrat);
}

/*
 This reads a file in Attacker form and stores the relative information
 It sets mNumPureAttacks and the Attacker Strategy matrix
*/
void AbstractPatroller::ReadPureAttackerFile(std::string FileName)
{
  //Set up the infile and open
 std::ifstream infile;
 infile.open(FileName);

 //Read the Size of the matrix
 int RowSize;
 int ColSize;
 infile>>RowSize>>ColSize;

 //Store mNumPurePatrols
 mNumPureAttacks=RowSize;

 //Reset the state of infile
 infile.clear();

 //Form the matrix to store values
 IntMatrix AttackStrat(mNumPureAttacks,2);

 //Set elements of the matrix by reading infile
 int j=1;
 int i=1;
 while(i<=mNumPureAttacks)
 {
  j=1;
  while(j<=2)
  {
   infile>>AttackStrat(i,j);
   j=j+1;
  }
  i=i+1;
 }

 //close infile
 infile.close();

 //Store the private variable
 mpPureAttackerStrategies=new IntMatrix(AttackStrat);

}

/*
 This reads a file in Payoff form and stores the relative information.
 This Read method will assume that both mNumPurePatrols and mNumPureAttacks are set
*/
void AbstractPatroller::ReadPurePayoffFile(std::string FileName)
{
  //Set up the infile and open
 std::ifstream infile;
 infile.open(FileName);

 //Form the matrix to store values
 IntMatrix Payoff(mNumPurePatrols,mNumPureAttacks);

 //Set elements of the matrix by reading infile
 int j=1;
 int i=1;
 while(i<=mNumPurePatrols)
 {
  j=1;
  while(j<=mNumPureAttacks)
  {
   infile>>Payoff(i,j);
   j=j+1;
  }
  i=i+1;
 }

 //close infile
 infile.close();

 //Store the private variable
 mpPurePayoffMatrix=new IntMatrix(Payoff);
}
