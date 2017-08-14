#include "BatchMixedPolicyEvaluation.hpp"
#include<cassert>

//Standard constructor
BatchMixedPolicyEvaluation::
    BatchMixedPolicyEvaluation(MixedPatroller& aMixedPatrollerSystem,
                               double StepSize)
{
 mpMixedPatrollerSystem=&aMixedPatrollerSystem;

 //Store the Step information
 mStepSize=StepSize;
 mNumSteps=(double)(1)/(double)(mStepSize);

 //Store entries for Evaluation
 mpStepEvaluation=new Vector(mNumSteps+1);
 mpKeyProbability=new Vector(mNumSteps+1);
 mpAllEvaluations=
 new Matrix(mpMixedPatrollerSystem->GetPatrollerSystem()
            ->GetNumPurePatrolOptions(),mNumSteps+1);
 mpBestPatrollerStratNum=new IntVector(mNumSteps+1);
 mpBestPatrollerStrat=
 new IntMatrix(mNumSteps+1,mpMixedPatrollerSystem
               ->GetPatrollerSystem()->GetGameTime());

 mpAllBestPatrollerStratNum=new IntMatrix(1,mNumSteps+1);
 mpAllBestPatrollerStrat=new Int3DMatrix(1,mpMixedPatrollerSystem
                                    ->GetPatrollerSystem()->GetGameTime(),
                                    mNumSteps+1);

 //Store Empty/Null Matrices for MT Space Evaluation
 mpMTSpaceEvaluation=new Matrix(1,1);
 mpMTSpaceKeyProbability=new Matrix(1,1);
 mpMTSpaceBestPatrollerStratNum=new IntMatrix(1,1);
 mpMTSpaceBestPatrollerStrat=new IntMatrix(1,1);
}

//Deconstructor
BatchMixedPolicyEvaluation::~BatchMixedPolicyEvaluation()
{
 delete mpStepEvaluation;
 delete mpKeyProbability;
 delete mpAllEvaluations;
 delete mpBestPatrollerStratNum;
 delete mpBestPatrollerStrat;
 delete mpAllBestPatrollerStratNum;
 delete mpAllBestPatrollerStrat;

 delete mpMTSpaceEvaluation;
 delete mpMTSpaceKeyProbability;
 delete mpMTSpaceBestPatrollerStratNum;
 delete mpMTSpaceBestPatrollerStrat;
}

//Setters and Getters
void BatchMixedPolicyEvaluation::
    SetMixedPatrollerSystem(MixedPatroller& aMixedPatrollerSystem)
{
 mpMixedPatrollerSystem=&aMixedPatrollerSystem;
}
void BatchMixedPolicyEvaluation::SetStepSize(int StepSize)
{
 //Store the Step information
 mStepSize=StepSize;
 mNumSteps=(double)(1)/(double)(mStepSize);

 //Store entries for Evaluation
 mpStepEvaluation=new Vector(mNumSteps);
 mpKeyProbability=new Vector(mNumSteps);
 mpAllEvaluations=
 new Matrix(mpMixedPatrollerSystem->GetPatrollerSystem()
            ->GetNumPurePatrolOptions(),mNumSteps);
 mpBestPatrollerStratNum=new IntVector(mNumSteps);
 mpBestPatrollerStrat=
 new IntMatrix(mNumSteps,mpMixedPatrollerSystem
               ->GetPatrollerSystem()->GetGameTime());
}
int BatchMixedPolicyEvaluation::GetNumSteps()
{
 return mNumSteps;
}
double BatchMixedPolicyEvaluation::GetStepSize()
{
 return mStepSize;
}
MixedPatroller* BatchMixedPolicyEvaluation::GetMixedPatrollerSystem()
{
 return mpMixedPatrollerSystem;
}
Vector BatchMixedPolicyEvaluation::GetEvaluationVector()
{
 return (*mpStepEvaluation);
}
Vector BatchMixedPolicyEvaluation::GetKeyProbabilityVector()
{
 return (*mpKeyProbability);
}
Matrix BatchMixedPolicyEvaluation::GetAllEvaluations()
{
 return (*mpAllEvaluations);
}
IntVector BatchMixedPolicyEvaluation::GetBestPatrollerVector()
{
 return (*mpBestPatrollerStratNum);
}
IntVector BatchMixedPolicyEvaluation::GetBestPatrollerStratNum()
{
 return (*mpBestPatrollerStratNum);
}
IntMatrix BatchMixedPolicyEvaluation::GetBestPatrollerStrat()
{
 return (*mpBestPatrollerStrat);
}
IntMatrix BatchMixedPolicyEvaluation::GetAllBestPatrollerStratNum()
{
 return (*mpAllBestPatrollerStratNum);
}
Int3DMatrix BatchMixedPolicyEvaluation::GetAllBestPatrollerStrat()
{
 return (*mpAllBestPatrollerStrat);
}
Matrix BatchMixedPolicyEvaluation::GetMTSpaceEvaluation()
{
 return (*mpMTSpaceEvaluation);
}
Matrix BatchMixedPolicyEvaluation::GetMTSpaceKeyProbability()
{
 return (*mpMTSpaceKeyProbability);
}
IntMatrix BatchMixedPolicyEvaluation::GetMTSpaceBestPatrollerStratNum()
{
 return (*mpMTSpaceBestPatrollerStratNum);
}
IntMatrix BatchMixedPolicyEvaluation::GetMTSpaceBestPatrollerstrat()
{
 return (*mpMTSpaceBestPatrollerStrat);
}

//Single Attack Evaluation
/*
This method evaluates a single MixedAttacker Profile, by calling the evaluation
in the class MixedPatroller. It then stores the values in the entry given.
*/
void BatchMixedPolicyEvaluation::
    EvaluateSingle(Vector MixedAttackerStrat,int entry)
{
 //Once Set up We evaluate the mixed attacker strat.
 mpMixedPatrollerSystem->SetMixedAttackerStrategy(MixedAttackerStrat);
 mpMixedPatrollerSystem->EvaluateAttackerAgainstPurePatroller();

 //Store the Best the patroller can do purely and the key probability
 //(i.e that on external node)
 (*mpStepEvaluation)(entry)=
 (mpMixedPatrollerSystem->GetAttackerAgainstPureEvaluation()).Max();
 (*mpKeyProbability)(entry)=MixedAttackerStrat(1);

 //Store the evaluation vector for the particular strategy
 mpAllEvaluations
 ->SetCol(entry,mpMixedPatrollerSystem->GetAttackerAgainstPureEvaluation());

 //Store the strategy number
 (*mpBestPatrollerStratNum)(entry)=
 (mpMixedPatrollerSystem->GetAttackerAgainstPureEvaluation()).MaxElement();

 //store the strategy
 mpBestPatrollerStrat
 ->SetRow(entry,mpMixedPatrollerSystem->GetPatrollerSystem()
          ->ConvertPatrollerOptionNum(((*mpBestPatrollerStratNum)(entry))));


 //Storing all for this evaluation
 //Alter Storage Size
 IntVector AllBestElements(
 (mpMixedPatrollerSystem->GetAttackerAgainstPureEvaluation()).MaxElements());
 int NumOfBestStrategies=AllBestElements.GetSize();

 if(NumOfBestStrategies>mpAllBestPatrollerStratNum->GetNumberOfRows())
 {
  mpAllBestPatrollerStratNum->
  ExtendRow(NumOfBestStrategies-mpAllBestPatrollerStratNum->GetNumberOfRows());
 }

 if(NumOfBestStrategies>mpAllBestPatrollerStrat->GetNumberRows())
 {
  mpAllBestPatrollerStrat->
  ExtendRow(NumOfBestStrategies-mpAllBestPatrollerStrat->GetNumberRows());
 }

 //Store Strat Num's and Strat
 for(int i=1; i<=NumOfBestStrategies; i++)
 {
  (*mpAllBestPatrollerStratNum)(i,entry)=AllBestElements(i);
  mpAllBestPatrollerStrat->SetRowVector(i,entry,
  mpMixedPatrollerSystem->GetPatrollerSystem()->
  ConvertPatrollerOptionNum(AllBestElements(i)));
 }
}

//Test Evaluation
/*
This method runs a batch test on multiple weights generating attacks using
a chosen method (hard-coded). It stores all the evaluations
*/
void BatchMixedPolicyEvaluation::EvaluateBatchTest1(int n, int k)
{
 //Delete and reinizalize
 delete mpStepEvaluation;
 delete mpKeyProbability;
 delete mpAllEvaluations;
 delete mpBestPatrollerStratNum;
 delete mpBestPatrollerStrat;
 delete mpAllBestPatrollerStratNum;
 delete mpAllBestPatrollerStrat;

 mpStepEvaluation=new Vector(mNumSteps+1);
 mpKeyProbability=new Vector(mNumSteps+1);
 mpAllEvaluations=
 new Matrix(mpMixedPatrollerSystem->GetPatrollerSystem()
            ->GetNumPurePatrolOptions(),mNumSteps+1);
 mpBestPatrollerStratNum=new IntVector(mNumSteps+1);
 mpBestPatrollerStrat=
 new IntMatrix(mNumSteps+1,mpMixedPatrollerSystem
               ->GetPatrollerSystem()->GetGameTime());

  mpAllBestPatrollerStratNum=new IntMatrix(1,mNumSteps+1);
 mpAllBestPatrollerStrat=new Int3DMatrix(1,mpMixedPatrollerSystem
                                    ->GetPatrollerSystem()->GetGameTime(),
                                    mNumSteps+1);

 int i=0;
 double weight;
 while(i<=mNumSteps)
 {
  //For each step size generate the attack and evaluate

  weight=i*(mStepSize);

  MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
  Generator.GenerateExtendedStarTest5PW(n,k,weight);
  Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

  EvaluateSingle(MixedAttackerStrat,i+1);

  i=i+1;
 }
}

//For use with BatchTimeMixedPolicyEvaluation
/*
This method is designed to take a time position vector and goes for all weights
using a particular attack generator method designed for use with a time position
attack vector.
*/
void BatchMixedPolicyEvaluation::
    EvaluateBatchTimePosTest(int n, int k,IntVector TimePosAttackVector)
{
 //Delete and reinizalize
 delete mpStepEvaluation;
 delete mpKeyProbability;
 delete mpAllEvaluations;
 delete mpBestPatrollerStratNum;
 delete mpBestPatrollerStrat;

 mpStepEvaluation=new Vector(mNumSteps+1);
 mpKeyProbability=new Vector(mNumSteps+1);
 mpAllEvaluations=
 new Matrix(mpMixedPatrollerSystem->GetPatrollerSystem()
            ->GetNumPurePatrolOptions(),mNumSteps+1);
 mpBestPatrollerStratNum=new IntVector(mNumSteps+1);
 mpBestPatrollerStrat=
 new IntMatrix(mNumSteps+1,mpMixedPatrollerSystem
               ->GetPatrollerSystem()->GetGameTime());

 int i=0;
 double weight;
 while(i<=mNumSteps)
 {
  //For each step size generate the attack and evaluate

  weight=i*(mStepSize);

  MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
  Generator.GenerateExtendedStarTestTimePW(n,k,weight,TimePosAttackVector);
  Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

  EvaluateSingle(MixedAttackerStrat,i+1);

  i=i+1;
 }
}
