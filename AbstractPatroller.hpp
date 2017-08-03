#ifndef ABSTRACTPATROLLERHEADERDEF
#define ABSTRACTPATROLLERHEADERDEF

#include "Matrix.hpp"
#include "Vector.hpp"
#include "IntMatrix.hpp"
#include "IntVector.hpp"
#include<string>

/*
Class:Abstract Patroller
Type: Abstract
Info: Provides generic construction of an element, printing utilities

*/
class AbstractPatroller
{
 public:

 //Standard Constructor
 AbstractPatroller(IntMatrix& AdjacencyMatrix,const int GameTime,const int AttackTime);

 //Specialised Constructor from stored files
 AbstractPatroller(IntMatrix& AdjacencyMatrix, const int GameTime,const int AttackTime,
                   std::string PurePatrollerFile,std::string PureAttackerFile,
                   std::string PurePayoffFile);

  //Null constructor
  AbstractPatroller();

 //Destructor
 ~AbstractPatroller();

 //Setters and Getters
 virtual void SetAdjacenyMatrix(IntMatrix& AdjacencyMatrix);
 virtual void SetGameTime(const int GameTime);
 virtual void SetAttackTime(const int AttackTime);
 IntMatrix GetAdjacenyMatrix() const;
 int GetNumNodes() const;
 int GetGameTime() const;
 int GetAttackTime() const;
 IntMatrix GetPurePatrollingStrategies() const;
 IntMatrix GetPureAttackingStrategies() const;
 IntMatrix GetPurePayoffMatrix() const;
 IntMatrix GetPurePatrollingOptions() const;
 IntMatrix GetPureAttackingOptions() const;
 IntMatrix GetPureWinMatrix() const;
 int GetNumPurePatrols();
 int GetNumPureAttacks();
 int GetNumPurePatrolOptions();
 int GetNumPureAttackOptions();

 //Patrolling Options
 int CountWalks(int FromNode,int ToNode,int Length);
 virtual void UpdatePurePatrollerStrategies();

 //Attacking Options
 virtual void UpdatePureAttackerStrategies();

  //Strategy intercection
 int Intersection(IntVector PatrollerStrat, IntVector AttackerStrat) const;

 //Strategy vs Strategy
 bool DoesBeat(IntVector PatrollerStrat, IntVector AttackerStrat) const;

 //Pure Payoff/Win Matrix
 void UpdatePurePayoffMatrix(); //Used once during construction
 void UpdatePureWinMatrix(); //May be called after initial creation if strategies have been moved

 //Removing Dominating Strategies
 void RemoveDominatedWaitingStrategies();
 bool DoesPayoffDominate(IntVector StratPayoff, IntVector DominatedStratPayoff,bool IsPatrollerStrats) const;
 void RemovePayoffDominatedStrategies();
 void RemovePenultimateAttackStrategies();

 //Converting Numbers to actual strategies
 //These two are for use before removal of dominated strategies has taken place
 IntVector ConvertPatrollerStratergyNum(int StratNum);
 IntVector ConvertAttackerStratergyNum(int StratNum);
 //These two are for use after removal of dominated strategies
 IntVector ConvertPatrollerOptionNum(int OptionNum);
 IntVector ConvertAttackerOptionNum(int OptionNum);



 //Printing and Save
 void PrintPurePatrollerOptions() const;
 void SavePurePatrollerOptions(std::string FileName="PurePatrollerOptions.dat") const;
 void PrintPureAttackerOptions() const;
 void SavePureAttackerOptions(std::string FileName="PureAttackerOptions.dat") const;
 void PrintPureWinMatrix() const;
 void SavePureWinMatrix(std::string FileName="PureWinMatrix.dat") const;
 void PrintPurePatrollerStrategies() const;
 void SavePurePatrollerStrategies(std::string FileName="PurePatrollerStrategies.dat") const;
 void PrintPureAttackerStrategies() const;
 void SavePureAttackerStrategies(std::string FileName="PureAttackerStrategies.dat") const;
 void PrintPurePayoffMatrix() const;
 void SavePurePayoffMatrix(std::string FileName="PurePayoffMatrix.dat") const;

 //Read Files
 void ReadPurePatrollerFile(std::string FileName="PurePatrollerStrategies.dat");
 void ReadPureAttackerFile(std::string FileName="PureAttackerStrategies.dat");
 void ReadPurePayoffFile(std::string FileName="PurePayoffMatrix");

 protected:

 IntMatrix* mpAdjacencyMatrix;
 int mNumNodes;
 int mGameTime;
 int mAttackTime;
 IntMatrix* mpPurePatrollerStrategies; //Stores all pure options
 IntMatrix* mpPurePatrollingOptions; //Stores options left (i.e strategies after domination)
 int mNumPurePatrols;
 int mNumPurePatrolOptions; //not yet implemented as different to the above
 IntMatrix* mpPureAttackerStrategies; //Stores all pure options
 IntMatrix* mpPureAttackingOptions; //Stores options left (i.e strategies after domination)
 int mNumPureAttacks;
 int mNumPureAttackOptions; //not yet implemented as different to the above
 IntMatrix* mpPurePayoffMatrix; //Stores all pure options payoffs
 IntMatrix* mpPureWinMatrix; //Stores payoffs after domination

 private:

};

#endif //ABSTRACTPATROLLERHEADERDEF
