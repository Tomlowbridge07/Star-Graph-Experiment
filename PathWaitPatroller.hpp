#ifndef PATHWAITPATROLLERHEADERDEF
#define PATHWAITPATROLLERHEADERDEF

#include "AbstractPatroller.hpp"

class PathWaitPatroller:
 public AbstractPatroller
{
 public:

 //Standard Constructor
 PathWaitPatroller(IntMatrix& AdjacencyMatrix,IntVector AttackNodes,
                   const int GameTime, const int AttackTime);

 //Explicit Constructor
 PathWaitPatroller(IntMatrix& AdjacencyMatrix,
                   IntVector AttackNodes, IntMatrix Paths,
                   const int GameTime, const int AttackTime);

 //Destructor
 ~PathWaitPatroller();

 //Getters and Setters:
 //Overwritten Setters to ensure no reduction
 void SetAdjacenyMatrix(IntMatrix& AdjacencyMatrix);
 void SetGameTime(const int GameTime);
 void SetAttackTime(const int AttackTime);

 //New Setters
 void SetAttackNodes(IntVector AttackNodes);
 void SetPaths(IntMatrix Paths);

 //New Getters
 IntVector GetAttackNodes();
 int GetNumNodesAttacked();
 IntMatrix GetPaths();
 int GetNumPaths();
 IntMatrix GetPathLengths();

 //Update the Path lengths
 void UpdatePathLengths();

 int countPatrols(int FromNode, int ToNode, int Length);

 void UpdatePurePatrollerStrategies();

 void UpdatePureAttackerStrategies();

 //Update



 protected:

 IntVector* mpAttackNodes;
 int mNumNodesAttacked;
 IntMatrix* mpPaths;
 int mNumPaths;
 IntMatrix* mpPathLengths;


 private:

};



#endif // PATHWAITPATROLLERHEADERDEF
