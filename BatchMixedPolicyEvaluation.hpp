#ifndef BATCHMIXEDPOLICYEVALUATIONHEADERDEF
#define BATCHMIXEDPOLICYEVALUATIONHEADERDEF

#include "MixedPatroller.hpp"
#include "MixedAttackGenerator.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "IntVector.hpp"
#include "IntMatrix.hpp"

/*
This inherited class is designed to evaluate a batch of attack styles
for a set step size (going through a variety of attack styles at a step
size)

Note. This Class is similar to MixedPolicyEvaluation
*/
class BatchMixedPolicyEvaluation
{
 public:

 //Standard constructor
 BatchMixedPolicyEvaluation(MixedPatroller& aMixedPatrollerSystem,double StepSize);

 //Deconstructor
 ~BatchMixedPolicyEvaluation();

 //Setters and Getters
 void SetMixedPatrollerSystem(MixedPatroller& aMixedPatrollerSystem);
 void SetStepSize(int StepSize);
 int GetNumSteps();
 double GetStepSize();
 MixedPatroller* GetMixedPatrollerSystem();
 Vector GetEvaluationVector();
 Vector GetKeyProbabilityVector();
 Matrix GetAllEvaluations();
 IntVector GetBestPatrollerVector();
 IntVector GetBestPatrollerStratNum();
 IntMatrix GetBestPatrollerStrat();
 Matrix GetMTSpaceEvaluation();
 Matrix GetMTSpaceKeyProbability();
 IntMatrix GetMTSpaceBestPatrollerStratNum();
 IntMatrix GetMTSpaceBestPatrollerstrat();

 //Evaluations
 void EvaluateSingle(Vector MixedAttackerStrat,int entry);
 void EvaluateBatchTest1(int n, int k);
 void EvaluateBatchTimePosTest(int n, int k,IntVector TimePosAttackVector);

 protected:
 int mNumSteps;
 double mStepSize;

 //Store the Patrolling System
 MixedPatroller* mpMixedPatrollerSystem;

 Vector* mpStepEvaluation; //Used to store the value of the game for that step
 Vector* mpKeyProbability; //Used to store the key probability (i.e the probability that each step used)

 Matrix* mpAllEvaluations; //Used to store the evaluation at all steps for all strategies

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

 //Note strategies are stored as a whole number with mGamtime
 IntMatrix* mpMTSpaceBestPatrollerStrat;

 private:

};

#endif // BATCHMIXEDPOLICYEVALUATIONHEADERDEF
