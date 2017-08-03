#include "PathGenerator.hpp"

//Standard Constructor
PathGenerator::PathGenerator(IntMatrix& AdjacencyMatrix)
{
 //Store Adjacency matrix
 mpAdjacencyMatrix=&AdjacencyMatrix;

 //Create Storage for pointers
 mpReasonNodeAdded=NULL;
 mpNodesAdded=NULL;
 mpQueue=NULL;
 mpPath=NULL;
 mpPaths=NULL;
}

//Setters and Getters
void PathGenerator::SetAdjacencyMatrix(IntMatrix& AdjacencyMatrix)
{
 //replace Adjacency matrix pointer
 mpAdjacencyMatrix=&AdjacencyMatrix;
}
IntVector PathGenerator::GetPath()
{
 return (*mpPath);
}
IntMatrix PathGenerator::GetPaths()
{
 return (*mpPaths);
}


void PathGenerator::RunDepthFirst(int FromNode)
{
 //Create storage
 delete mpReasonNodeAdded;
 delete mpNodesAdded;
 delete mpQueue;
 std::flush(std::cout<<"Depth First search is run from node:"<<FromNode);

 mpReasonNodeAdded=new IntMatrix(mpAdjacencyMatrix->GetNumberOfRows(),2);
 int i=1;
 while(i<=mpAdjacencyMatrix->GetNumberOfRows())
 {
  (*mpReasonNodeAdded)(i,1)=i;
  i=i+1;
 }

 mpNodesAdded=new IntVector(mpAdjacencyMatrix->GetNumberOfRows());
 mpQueue=new IntVector(mpAdjacencyMatrix->GetNumberOfRows());


 //Initialize
 int workingnode=FromNode;
 (*mpQueue)(1)=0;
 (*mpNodesAdded)(FromNode)=1;
 (*mpReasonNodeAdded)(FromNode,2)=FromNode; //Indicating it is the start and why it was added

 //Repeat depth algorithm
 int addedcounter=2;
 int nextqueuelevel=1;
 do//While the Queue is not empty
 { std::flush(std::cout<<"currently working on node"<<workingnode<<"\n");
  std::flush(std::cout<<"Queue is curerrently"<<*mpQueue);
  int i=1;
  bool addediniteration=false;
  while(i<=mpAdjacencyMatrix->GetNumberOfRows())
  {
   if((*mpAdjacencyMatrix)(workingnode,i)==1) //If connected
   {
    if((*mpNodesAdded)(i)==0) //Considering adding it has not already been added
    {
     (*mpNodesAdded)(i)=addedcounter;
     (*mpReasonNodeAdded)(i,2)=workingnode;
     (*mpQueue)(nextqueuelevel)=i;
     nextqueuelevel=nextqueuelevel+1;
     addedcounter=addedcounter+1;
     addediniteration=true;
    }
   }
   i=i+1;
  }
  std::flush(std::cout<<"Queue is curerrently"<<*mpQueue<<"NodesAdded is"<<*mpNodesAdded<<"Reasons added is"<<*mpReasonNodeAdded);
  if(addediniteration==false) //If no nodes were added
  {
   //Delete value and shift queue along
   workingnode=(*mpQueue)(1);
   (*mpQueue)(1)=0;
   int i=1;
   while(i<=nextqueuelevel-1)
   {
    (*mpQueue)(i)=(*mpQueue)(i+1);
    i=i+1;
   }
   nextqueuelevel=nextqueuelevel-1;
  }
  else
  {
   workingnode=(*mpQueue)(1);
   (*mpQueue)(1)=0;
   int i=1;
   while(i<=nextqueuelevel-1)
   {
    (*mpQueue)(i)=(*mpQueue)(i+1);
    i=i+1;
   }
   nextqueuelevel=nextqueuelevel-1;
  }
 }while(workingnode!=0);
 std::flush(std::cout<<"Queue is declared as empty");
}

void PathGenerator::GeneratePathFromDepth(int FromNode, int ToNode)
{
 //Run Depth-First Search
 RunDepthFirst(FromNode);

 //Create Storage
 delete mpPath;
 mpPath=new IntVector(mpAdjacencyMatrix->GetNumberOfRows());
 mpPath->Fill(-1);

 //Recreate Path-Backwards
 int i=1;
 bool complete=false;
 int currentnode=ToNode;
 int j=1;
 while(i<=mpAdjacencyMatrix->GetNumberOfRows() && complete==false)
 {
  //Push sequence one to left
  j=i;
  while(j>=0)
  {
   (*mpPath)(j+1)=(*mpPath)(j);
   j=j-1;
  }

  //Add reason the penultimate node was added
  (*mpPath)(1)=(*mpReasonNodeAdded)(currentnode,2);

  //update current node
  currentnode=(*mpPath)(1);

  i=i+1;
 }

}

void PathGenerator::GeneratePathsFromDepth(int FromNode, IntVector ToNodes)
{
  //Run Depth-First Search
 RunDepthFirst(FromNode);

 //Create Storage
 delete mpPaths;
 mpPaths=new IntMatrix(ToNodes.GetSize(),mpAdjacencyMatrix->GetNumberOfRows());
 mpPaths->Fill(-1);

 //For each node in the ToNodes we want to find the path and store it

 int nodelevel=1;
 while(nodelevel<=ToNodes.GetSize())
 {
  //Recreate Path-Backwards
  int i=1;
  bool complete=false;
  int currentnode=ToNodes(nodelevel);
  int j=1;
  while(i<=mpAdjacencyMatrix->GetNumberOfRows() && complete==false)
  {
   //Push sequence one to left
   j=i;
   while(j>=0)
   {
    (*mpPaths)(nodelevel,j+1)=(*mpPaths)(nodelevel,j);
    j=j-1;
   }

   //Add reason the penultimate node was added
   (*mpPaths)(nodelevel,1)=(*mpReasonNodeAdded)(currentnode,2);

   //update current node
   currentnode=(*mpPaths)(nodelevel,1);

   i=i+1;
  }
  nodelevel=nodelevel+1;
 }
}

void PathGenerator::GeneratePathsFromDepth(IntVector FromNodes, IntVector ToNodes)
{
  //Create Storage
  delete mpPaths;
  mpPaths=new IntMatrix(FromNodes.GetSize()*ToNodes.GetSize(),mpAdjacencyMatrix->GetNumberOfRows());
  mpPaths->Fill(-1);
  std::flush(std::cout<<"Running Paths Generator");

 //For each from node store the path to all to nodes

 int fromnodenumber=1;
 while(fromnodenumber<=FromNodes.GetSize())
 {
  //Run Depth-First Search
  std::flush(std::cout<<"Depth First Being run");
  RunDepthFirst(FromNodes(fromnodenumber));
  std::flush(std::cout<<"Reasons added is:"<<(*mpReasonNodeAdded));


  //For each node in the ToNodes we want to find the path and store it

  int tonodenumber=1;
  while(tonodenumber<=ToNodes.GetSize())
  {
   if(FromNodes(fromnodenumber)==ToNodes(tonodenumber))
   {
    (*mpPaths)((fromnodenumber-1)*FromNodes.GetSize()+tonodenumber,1)=FromNodes(fromnodenumber);
    (*mpPaths)((fromnodenumber-1)*FromNodes.GetSize()+tonodenumber,2)=FromNodes(fromnodenumber);
   }
   else{
   //Recreate Path-Backwards
   int i=1;
   bool complete=false;
   int currentnode=ToNodes(tonodenumber);
   int j=1;
   (*mpPaths)((fromnodenumber-1)*FromNodes.GetSize()+tonodenumber,1)=currentnode;
   while(i<=mpAdjacencyMatrix->GetNumberOfRows() && complete==false)
   {
    //Push sequence one to left
    j=mpAdjacencyMatrix->GetNumberOfRows()-1;
    std::flush(std::cout<<"i is:"<<i);
    while(j>=1)
    {
     (*mpPaths)((fromnodenumber-1)*FromNodes.GetSize()+tonodenumber,j+1)=(*mpPaths)((fromnodenumber-1)*FromNodes.GetSize()+tonodenumber,j);
     j=j-1;
    }

    //Add reason the penultimate node was added
    std::flush(std::cout<<"reason added to add is"<<(*mpReasonNodeAdded)(currentnode,2));
    (*mpPaths)((fromnodenumber-1)*FromNodes.GetSize()+tonodenumber,1)=(*mpReasonNodeAdded)(currentnode,2);

    //update current node
    currentnode=(*mpPaths)((fromnodenumber-1)*FromNodes.GetSize()+tonodenumber,1);

    if(currentnode==FromNodes(fromnodenumber))
    {
     complete=true;
    }
   std::flush(std::cout<<(*mpPaths));
    i=i+1;
   }
   }
   tonodenumber=tonodenumber+1;
  }
  fromnodenumber=fromnodenumber+1;
 }
}
