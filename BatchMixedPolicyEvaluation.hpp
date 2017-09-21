#ifndef BATCHMIXEDPOLICYEVALUATIONHEADERDEF
#define BATCHMIXEDPOLICYEVALUATIONHEADERDEF

#include "MixedPatroller.hpp"
#include "MixedAttackGenerator.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "IntVector.hpp"
#include "IntMatrix.hpp"
#include "Int3DMatrix.hpp"

/*
This class is designed to evaluate an attack for a mixed policy for a variety of
weights (the weight is the total weight placed on the extended node)

This class is primarily designed to be used to get an evaluation on the
extended star graph.

(A similar adaptation of the class could be used for multiple weights)

Note. This Class is similar to MixedPolicyEvaluation
*/
class BatchMixedPolicyEvaluation
{
 public:

 //Standard constructor
 BatchMixedPolicyEvaluation(MixedPatroller& aMixedPatrollerSystem,
                            double StepSize);

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
 IntMatrix GetAllBestPatrollerStratNum();
 Int3DMatrix GetAllBestPatrollerStrat();
 Matrix GetWeightings();
 Matrix GetMTSpaceEvaluation();
 Matrix GetMTSpaceKeyProbability();
 IntMatrix GetMTSpaceBestPatrollerStratNum();
 IntMatrix GetMTSpaceBestPatrollerstrat();

 //Evaluations

 //Single Attack Evaulation
 void EvaluateSingle(Vector MixedAttackerStrat,int entry);

 //Evaluate a test batch (test 1)
 void EvaluateBatchTest1(int n, int k);

 //This is designed for use with the Class BatchTimeMixedPolicyEvaluation
 /*It is supposed to be used with PW patroller (as it calls its matching
    attack generator*/
 void EvaluateExtenedStarBatchTimePosTestPW
 (int n, int k,IntVector TimePosAttackVector);

 void EvaluateExtenedStarBatchTimePosTest
 (int n, int k,IntVector TimePosAttackVector);

 protected:
 int mNumSteps;
 double mStepSize;

 //Store the Patrolling System
 MixedPatroller* mpMixedPatrollerSystem;

 //Used to store the value of the game for that step
 Vector* mpStepEvaluation;

 //Used to store the key probability (i.e the probability that each step used)
 Vector* mpKeyProbability;

 //Used to store the evaluation at all steps for all strategies
 Matrix* mpAllEvaluations;

 //Stores the Strategy the patroller will use against each
 //of the key probability strategies
 //Note. Stores the strategy number as according to patroller strategy options.
 //Used alongside the Step Evaluation to see what the best
 //strategy for the patroller was
 IntVector* mpBestPatrollerStratNum;

 //Store the strategy the patroller will use against each choice of weight
 IntMatrix* mpBestPatrollerStrat;

 //Stores all Best Patroller StratNum's and actual strategies
 //Rows for each of the evaluation number and number of cols is the number of
 //evaluations
 IntMatrix* mpAllBestPatrollerStratNum;

 //Layer Matrices store all the different strategies for a particular evaluation
 Int3DMatrix* mpAllBestPatrollerStrat;

 //This matrix stores the weightings
 Matrix* mpWeightings;


 int mStartT;
 int mLastT;
 int mStartM;
 int mLastM;

 Matrix* mpMTSpaceEvaluation;
 Matrix* mpMTSpaceKeyProbability;
 IntMatrix* mpMTSpaceBestPatrollerStratNum;

 //Note strategies are stored as a whole number with mGamtime length (not a
 //                                                                   vector)
 IntMatrix* mpMTSpaceBestPatrollerStrat;

 private:

};

#endif // BATCHMIXEDPOLICYEVALUATIONHEADERDEF
