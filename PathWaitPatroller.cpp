#include "PathWaitPatroller.hpp"

#include<cassert>

//Standard Constructor
PathWaitPatroller::PathWaitPatroller(IntMatrix& AdjacencyMatrix,
                                     IntVector AttackNodes, const int GameTime, const int AttackTime)
{
 //Store the Attackable Nodes
 mpAttackNodes=new IntVector(AttackNodes);
 mNumNodesAttacked=AttackNodes.GetSize();

 /*
 Find the paths between the attack nodes using shortest path methods.
 */

 //Store times
 assert(GameTime-AttackTime>=0);
 mGameTime=GameTime;
 mAttackTime=AttackTime;

}

//Explicit Constructor
/*
The matrix of paths passed to this should use -1 to state the end of paths.
It is assumed that no paths given are the null path. Shorest paths should be given!
*/
PathWaitPatroller::PathWaitPatroller(IntMatrix& AdjacencyMatrix,
                                      IntVector AttackNodes, IntMatrix Paths,
                                     const int GameTime, const int AttackTime)
{
 //Store the Attackable Nodes
 mpAttackNodes=new IntVector(AttackNodes);
 mNumNodesAttacked=AttackNodes.GetSize();

 //Store the allowed paths
 mpPaths=new IntMatrix(Paths);
 mNumPaths=Paths.GetNumberOfRows();
 UpdatePathLengths();
 //std::flush(std::cout<<(*mpPathLengths));

 //Store the adjacency matrix
 mpAdjacencyMatrix=new IntMatrix(AdjacencyMatrix);
 mNumNodes=AdjacencyMatrix.GetNumberOfColumns();

 //Store times
 assert(GameTime-AttackTime>=0);
 mGameTime=GameTime;
 mAttackTime=AttackTime;

 //Allow construction of Strategies and Payoffs
 UpdatePurePatrollerStrategies();
 UpdatePureAttackerStrategies();
 UpdatePurePayoffMatrix();

 //Store as Options(no domination will occur though)
 mNumPurePatrolOptions=mNumPurePatrols;
 mpPurePatrollingOptions=new IntMatrix(*mpPurePatrollerStrategies);
 mNumPureAttackOptions=mNumPureAttacks;
 mpPureAttackingOptions=new IntMatrix(*mpPureAttackerStrategies);
 mpPureWinMatrix=new IntMatrix(*mpPurePayoffMatrix);
}


PathWaitPatroller::~PathWaitPatroller()
{
 delete mpAttackNodes;
 delete mpPaths;
 delete mpPathLengths;
}

//Getters and Setters:
//Overwritten Setters to ensure no reduction
void PathWaitPatroller::SetAdjacenyMatrix(IntMatrix& AdjacencyMatrix)
{
 //Warn user of usage to change the Paths if required
 std::flush(std::cout<<"WARNING: make sure to set new Paths if required \n");

 //Store the adjacency matrix
 delete mpAdjacencyMatrix;
 mpAdjacencyMatrix=new IntMatrix(AdjacencyMatrix);
 mNumNodes=AdjacencyMatrix.GetNumberOfColumns();
}
void PathWaitPatroller::SetGameTime(const int GameTime)
{
 assert(GameTime-mAttackTime>=0);
 mGameTime=GameTime;

 //Allow construction of Strategies and Payoffs
 UpdatePurePatrollerStrategies();
 UpdatePureAttackerStrategies();
 std::flush(std::cout<<"Updating Pure Payoff");
 UpdatePurePayoffMatrix();
 std::flush(std::cout<<"update complete");

 //Store as Options(no domination will occur though)
 mNumPurePatrolOptions=mNumPurePatrols;
 delete mpPurePatrollingOptions;
 mpPurePatrollingOptions=new IntMatrix(*mpPurePatrollerStrategies);
 mNumPureAttackOptions=mNumPureAttacks;
 delete mpPureAttackingOptions;
 mpPureAttackingOptions=new IntMatrix(*mpPureAttackerStrategies);
 delete mpPureWinMatrix;
 mpPureWinMatrix=new IntMatrix(*mpPurePayoffMatrix);
}
void PathWaitPatroller::SetAttackTime(const int AttackTime)
{
 assert(mGameTime-AttackTime>=0);
 mAttackTime=AttackTime;

 //Allow construction of Strategies and Payoffs
 UpdatePureAttackerStrategies();
 UpdatePurePayoffMatrix();

 //Store as Options(no domination will occur though)
 mNumPureAttackOptions=mNumPureAttacks;
 delete mpPureAttackingOptions;
 mpPureAttackingOptions=new IntMatrix(*mpPureAttackerStrategies);
 delete mpPureWinMatrix;
 mpPureWinMatrix=new IntMatrix(*mpPurePayoffMatrix);
}

//New Setters
void PathWaitPatroller::SetAttackNodes(IntVector AttackNodes)
{
  //Warn user of usage to change the Paths if required
 std::flush(std::cout<<"WARNING: make sure to set new Paths if manually doing so \n");

 //Store the Attackable Nodes
 delete mpAttackNodes;
 mpAttackNodes=new IntVector(AttackNodes);
 mNumNodesAttacked=AttackNodes.GetSize();

 //Allow construction of Strategies and Payoffs
 UpdatePurePatrollerStrategies();
 UpdatePureAttackerStrategies();
 UpdatePurePayoffMatrix();

 //Store as Options(no domination will occur though)
 mNumPurePatrolOptions=mNumPurePatrols;
 mpPurePatrollingOptions=new IntMatrix(*mpPurePatrollerStrategies);
 mNumPureAttackOptions=mNumPureAttacks;
 mpPureAttackingOptions=new IntMatrix(*mpPureAttackerStrategies);
 mpPureWinMatrix=new IntMatrix(*mpPurePayoffMatrix);

}
void PathWaitPatroller::SetPaths(IntMatrix Paths)
{
 //Store the allowed paths
 delete mpPaths;
 mpPaths=new IntMatrix(Paths);
 mNumPaths=Paths.GetNumberOfRows();
 UpdatePathLengths();
}

//New Getters
IntVector PathWaitPatroller::GetAttackNodes()
{
 return (*mpAttackNodes);
}
int PathWaitPatroller::GetNumNodesAttacked()
{
 return mNumNodesAttacked;
}
IntMatrix PathWaitPatroller::GetPaths()
{
 return (*mpPaths);
}
int PathWaitPatroller::GetNumPaths()
{
 return mNumPaths;
}
IntMatrix PathWaitPatroller::GetPathLengths()
{
 return (*mpPathLengths);
}

//Update the Path lengths
void PathWaitPatroller::UpdatePathLengths()
{
 //Create storage
 mpPathLengths=new IntMatrix(mNumNodesAttacked,mNumNodesAttacked);

 //Go through each line of the matrix to get lengths.
 int i=1;
 int j=1;
 int k=1;
 int counter=0;
 while(i<=mNumNodesAttacked)
 {
  j=1;
  while(j<=mNumNodesAttacked)
  {
   counter=0;
   k=1;
   while(k<=mpPaths->GetNumberOfColumns())
   {
    //std::flush(std::cout<<"i is "<<i<<" j is "<<j<<" k is "<<k<<" Path value is "<<(*mpPaths)((i-1)*mNumNodesAttacked+j,k)<<"\n");
    if((*mpPaths)((i-1)*mNumNodesAttacked+j,k)!=-1)
    {
     counter=counter+1;
    }
    else
    {
     k=mpPaths->GetNumberOfColumns()+1;
    }
    k=k+1;
   }
   (*mpPathLengths)(i,j)=counter-1;
   j=j+1;
  }
  i=i+1;
 }
}

int PathWaitPatroller::countPatrols(int FromNode, int ToNode, int Length)
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

 //Initialize counter
 int Count=0;

 //Count recursively
 int i=1;
 while(i<=mNumNodesAttacked)
 {
   Count=Count+countPatrols(i,ToNode,Length-((*mpPathLengths)(FromNode,i)));
  i=i+1;
 }
 //std::cout<<"from node "<<FromNode<<"to node "<<ToNode<<"count is "<<Count<<"for length"<<Length<<"\n";
 //Return the counter
 return Count;
}

/*
IntMatrix PathWaitPatroller::PatrolsofLength(int Length)
{
 IntMatrix PatrolOptions()
 if(Length==1)
 {
   while(i<=mNumNodesAttacked)
 {
  PatrollerOptions(i,1)=1;
  i=i+1;
 }
 }
}
*/

/*
This function is to overwrite How the Pure Patroller Strategies are created instead using the
Path and Wait method.
*/
void PathWaitPatroller::UpdatePurePatrollerStrategies()
{
 //Count number of strategies
 int i=1;
 int j=1;
 int NumberofOptions=0;
 while(i<=mNumNodesAttacked)
 {
  j=1;
  while(j<=mNumNodesAttacked)
  {
   NumberofOptions=NumberofOptions+countPatrols(i,j,mGameTime-1);
   //std::flush(std::cout<<"i="<<i<<" j="<<j<<" updated number of options="<<NumberofOptions<<"\n");
   j=j+1;
  }
  i=i+1;
 }
 mNumPurePatrols=NumberofOptions;

 //Create Storage for patrols
 IntMatrix PatrollerOptions(NumberofOptions,mGameTime);
 PatrollerOptions.Fill(-1);

 //set up starting nodes
 i=1;
 while(i<=mNumNodesAttacked)
 {
  PatrollerOptions(i,1)=mpAttackNodes->Read(i-1);
  i=i+1;
 }

  //Create Storage for picked points
 IntMatrix PickedPoints(NumberofOptions,mGameTime);
 PickedPoints.Fill(-1);

 //set up starting nodes
 i=1;
 while(i<=mNumNodesAttacked)
 {
  PickedPoints(i,1)=i;
  i=i+1;
 }

 //Create and store current patrol length
 IntVector PatrolLengths(NumberofOptions);
 PatrolLengths.Fill(-1);
 i=1;
 while(i<=mNumNodesAttacked)
 {
  PatrolLengths(i)=1;
  i=i+1;
 }

 //Compute recursively all walks
 IntMatrix TempPick(PickedPoints);
 IntMatrix TempOpts(PatrollerOptions);
 IntVector TempPatrolLength(PatrolLengths);
 i=1;
 j=1;
 int k=1;
 int m=1;
 int Counter=1;
 int Steps=1;
 while(Steps<mGameTime)
 {
  //Copy the Patroller matrix
  TempPick=PickedPoints;
  TempOpts=PatrollerOptions;
  TempPatrolLength=PatrolLengths;
  //std::flush(std::cout<<TempPick);
  //std::flush(std::cout<<TempPatrolLength);
  //std::flush(std::cout<<TempOpts);
  Counter=1;
  i=1;
  while(i<=NumberofOptions)
  {
   if(TempPatrolLength(i)!=mGameTime)
    {
   if(TempPick(i,Steps)!=-1) //require this as if we hit -1 we're at the current end
   {
     j=1;
     while(j<=mNumNodesAttacked)
     {
      //Identify the end point of the current sequence
      if(TempPick(i,Steps)==j)
      {
       //Decide to add something
       k=1;
       while(k<=mNumNodesAttacked)
       {
        if(TempPatrolLength(i)+((*mpPathLengths)(j,k))<=mGameTime) //If path length is not too large then add in
        { //std::flush(std::cout<<"When i is "<<i<<" j is "<<j<<" k is "<<k<<"counter is "<<Counter<<"\n");
         //Copy prior sequence of picked points and add in new point
         m=1;
         while(m<=Steps)
         {
          PickedPoints(Counter,m)=TempPick(i,m);
          m=m+1;
         }
         PickedPoints(Counter,Steps+1)=k;

         //Add the cost of moving
         PatrolLengths(Counter)=TempPatrolLength(i)+(*mpPathLengths)(j,k);

         //Copy prior sequence of actual patrols and add in new points
         m=1;
         while(m<=TempPatrolLength(i))
         {
          PatrollerOptions(Counter,m)=TempOpts(i,m);
          m=m+1;
         }
         m=1;
         while(m<=(*mpPathLengths)(j,k))
         {
          PatrollerOptions(Counter,m+TempPatrolLength(i))=(*mpPaths)((j-1)*mNumNodesAttacked+k,m+1);
          m=m+1;
         }
         Counter=Counter+1;
        }
        k=k+1;
       }
      }
      j=j+1;
     }
    }
     }
    else
    {
     m=1;
     while(m<=Steps)
     {
     PickedPoints(Counter,m)=TempPick(i,m);
     m=m+1;
     }

     PatrolLengths(Counter)=TempPatrolLength(i);

     m=1;
     while(m<=TempPatrolLength(i))
     {
      PatrollerOptions(Counter,m)=TempOpts(i,m);
      m=m+1;
     }
     Counter=Counter+1;
    }
    i=i+1;
   }
  Steps=Steps+1;
 }

 //std::flush(std::cout<<PickedPoints);
 //std::flush(std::cout<<PatrolLengths);

 //Store the pure patrolling options
 mpPurePatrollerStrategies=new IntMatrix(PatrollerOptions);
}

/*
This function is to overwrite how the Pure Attacker Strategies are created. To allow only attacks
at certain nodes.
*/
void PathWaitPatroller::UpdatePureAttackerStrategies()
{
 //Store the number of options and attacker has i.e number of possible attack times x number of nodes
 int NumberofOptions=mNumNodesAttacked*(mGameTime-mAttackTime+1);
 mNumPureAttacks=NumberofOptions;

 //For the matrix form 2 columns , 1st column being node and 2nd being the starting time.
 IntMatrix AttackerOptions(NumberofOptions,2);
 int i=1;
 int j=1;
 while(i<=mNumNodesAttacked)
 {
  j=1;
  while(j<=mGameTime-mAttackTime+1)
  {
   AttackerOptions((mGameTime-mAttackTime+1)*(i-1)+j,1)=mpAttackNodes->Read(i-1);
   AttackerOptions((mGameTime-mAttackTime+1)*(i-1)+j,2)=j;
   j=j+1;
  }
  i=i+1;
 }

 //Store the Pure attacking options
 mpPureAttackerStrategies=new IntMatrix(AttackerOptions);
}
