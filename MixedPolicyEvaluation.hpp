#ifndef MIXEDPOLICYEVALUATIONHEADERDEF
#define MIXEDPOLICYEVALUATIONHEADERDEF

#include "AbstractPatroller.hpp"
#include "PathWaitPatroller.hpp"
#include "MixedPatroller.hpp"

/*
Class:Mixed Policy Batch Evaluation
Type:
Info: Provides the tools to batch evaluate a policy against all pure attacks.
At the moment a mixed attacker against all pure patrols!
*/
class MixedPolicyEvaluation
{
 public:

 //Standard Constructer
 MixedPolicyEvaluation(MixedPatroller& aMixedPatrollerSystem);

 //Batch Testing Constructor for multiple attack types
 //MixedPolicyEvaluation(MixedPatroller& aMixedPatrollerSystem);

 //Destructor
 ~MixedPolicyEvaluation();

 //Setters and Getters
 void SetMixedPatrollerSystem(MixedPatroller& aMixedPatrollerSystem);
 MixedPatroller* GetMixedPatrollerSystem();
 Vector GetEvaluationVector();
 Vector GetKeyProbabilityVector();
 IntVector GetBestPatrollerVector();
 IntMatrix GetBestPatrollerStrat();
 Matrix GetMTSpaceEvaluation();
 Matrix GetMTSpaceKeyProbability();
 IntMatrix GetMTSpaceBestPatrollerStratNum();
 IntMatrix GetMTSpaceBestPatrollerstrat();

 //Generalised Evaluation suite
 void EvaluateGraph(Vector MixedAttackerStrat);

 //Evaluations designed to use the generators for a normal walk style
 void EvaluateLineGraph(int n);
 void EvaluateTimedLineGraph(int n);
 void EvaluateOverallLineGraph(int n);
 void EvaluateStarGraph(int n , int k);
 void EvaluateTimedStarGraph(int n,int k);
 void EvaluateOverallStarGraph(int n, int k);

 //Evaulations designed to use the generators for a Path Wait style walk
 void EvaluateLineGraphPW(int n);
 void EvaluateTimedLineGraphPW(int n);
 void EvaluateOverallLineGraphPW(int n);
 void EvaluateStarGraphPW(int n,int k);
 void EvaluateTimedStarGraphPW(int n,int k);
 void EvaluateOverallStarGraphPW(int n,int k);


 void EvaluateExtendedStarGraphTestPW(int n,int k);


 //MTSpace Evaluations for normal walk style
 void EvaluateLineGraphMTSpaceBest
 (int n,int StartM , int StartT , int LastM , int LastT);
 void EvaluateTimedLineGraphMTSpaceBest
 (int n,int StartM , int StartT , int LastM , int LastT);
 void EvaluateOverallLineGraphMTSpaceBest
 (int n,int StartM , int StartT , int LastM , int LastT);
 void EvaluateStarGraphMTSpaceBest
 (int n, int k,int StartM , int StartT , int LastM , int LastT);
 void EvaluateTimedStarGraphMTSpaceBest
 (int n,int k,int StartM , int StartT , int LastM , int LastT);
 void EvaluateOverallStarGraphMTSpaceBest
 (int n,int k,int StartM , int StartT , int LastM , int LastT);


 //MTSpace Evaluations for Path Wait style walk
 void EvaluateLineGraphMTSpaceBestPW
 (int n,int StartM , int StartT , int LastM , int LastT);
 void EvaluateTimedLineGraphMTSpaceBestPW
 (int n,int StartM , int StartT , int LastM , int LastT);
 void EvaluateOverallLineGraphMTSpaceBestPW
 (int n,int StartM , int StartT , int LastM , int LastT);
 void EvaluateStarGraphMTSpaceBestPW
 (int n, int k,int StartM , int StartT , int LastM , int LastT);
 void EvaluateTimedStarGraphMTSpaceBestPW
 (int n,int k,int StartM , int StartT , int LastM , int LastT);
 void EvaluateOverallStarGraphMTSpaceBestPW
 (int n,int k,int StartM , int StartT , int LastM , int LastT);

 //Saving and displaying variables
 void PrintStepEvaluation() const;
 void SaveStepEvaluation(std::string FileName="StepEvaluation.dat") const;
 void PrintKeyProbability() const;
 void SaveKeyProbability(std::string FileName="KeyProbabilities.dat") const;
 void PrintBestPatrollerStratNum() const;
 void SaveBestPatrollerStratNum
 (std::string FileName="BestPatrollerStrategyNumbers.dat") const;
 void PrintMTSpaceEvaluation() const;
 void SaveMTSpaceEvaluation(std::string FileName="MTSpaceEvaluation.dat") const;
 void PrintMTSpaceKeyProbability() const;
 void SaveMTSpaceKeyProbability
 (std::string FileName="MTSpaceKeyProbabilities.dat") const;
 void PrintMTSpaceBestPatrollerStratNum() const;
 void SaveMTSpaceBestPatrollerStratNum
 (std::string FileName="MTSpaceBestPatrollerStrategyNumbers.dat") const;

 //These Print and Save the Converted to actual pure strategy values
 void PrintBestPatrollerStrategies();
 void SaveBestPatrollerStrategies
 (std::string FileName="BestPatrollerStrategies.dat") const;
 void PrintMTSpaceBestPatrollerStrategies();
 void SaveMTSpaceBestPatrollerStrategies
 (std::string FileName="MTSpaceBestPatrollerStrategies.dat") const;

 //Print and Save all data for the experiment
 void PrintPolicyEvaluation();
 void SavePolicyEvaluation(std::string FileName="PolicyEvaluation.dat");
 void PrintMTSpacePolicyEvaluation();
 void SaveMTSpacePolicyEvaluation
 (std::string FileName="MTSpacePolicyEvaluation.dat");

 protected:

 //Store the Patrolling System
 MixedPatroller* mpMixedPatrollerSystem;

 Vector* mpStepEvaluation; //Used to store the value of the game for that step
 Vector* mpKeyProbability; //Used to store the key probability (i.e the probability that each step used)

 //Stores the Strategy the patroller will use against each of the key probability strategies
 //Note. Stores the strategy number as according to patroller strategy options.
 IntVector* mpBestPatrollerStratNum; //Used alongside the Step Evaluation to see what the best strategy for the patroller was

 IntMatrix* mpBestPatrollerStrat;

 int mStartT;
 int mLastT;
 int mStartM;
 int mLastM;

 Matrix* mpMTSpaceEvaluation;
 Matrix* mpMTSpaceKeyProbability;
 IntMatrix* mpMTSpaceBestPatrollerStratNum;

 //Note strategies are stored as a whole number with $mGamtime$
 IntMatrix* mpMTSpaceBestPatrollerStrat;

 private:

};

#endif // MIXEDPOLICYEVALUATIONHEADERDEF
