#ifndef PATHGENERATORHEADERDEF
#define PATHGENERATORHEADERDEF

#include "IntVector.hpp"
#include "IntMatrix.hpp"

class PathGenerator
{
 public:

 //Standard Constructor
 PathGenerator(IntMatrix& AdjacencyMatrix);

 //Setters and Getters
 void SetAdjacencyMatrix(IntMatrix& AdjacencyMatrix);
 IntVector GetPath();
 IntMatrix GetPaths();


 void RunDepthFirst(int FromNode);

 void GeneratePathFromDepth(int FromNode, int ToNode);
 void GeneratePathsFromDepth(int FromNode, IntVector ToNodes);
 void GeneratePathsFromDepth(IntVector FromNodes, IntVector ToNodes);


 protected:

 IntMatrix* mpAdjacencyMatrix;

 IntMatrix* mpReasonNodeAdded;

 IntVector* mpQueue;

 IntVector* mpNodesAdded;

 IntVector* mpPath;

 IntMatrix* mpPaths;

 private:

};



#endif // PATHGENERATORHEADERDEF
