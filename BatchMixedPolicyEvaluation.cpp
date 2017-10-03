#include "BatchMixedPolicyEvaluation.hpp"
#include<cassert>
#include "ObjectsInBins.hpp"

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


 //Store weightings
 mpWeightings=new Matrix(mNumSteps+1,2);

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

 delete mpWeightings;
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
Matrix BatchMixedPolicyEvaluation::GetWeightings()
{
 return (*mpWeightings);
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
 /*
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
 } */


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

This method is meant to be used with PW type on the extended star graph for
attacking two types of nodes (The extended one and normal ones).
*/
void BatchMixedPolicyEvaluation::
EvaluateExtenedStarBatchTimePosTestPW(int n, int k,IntVector TimePosAttackVector)
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

/*
This method is designed to take a time position vector and goes for all weights
using a particular attack generator method designed for use with a time position
attack vector.

This method is meant to be used with normal patrolling (not PW format).
*/
void BatchMixedPolicyEvaluation::
EvaluateExtenedStarBatchTimePosTest(int n, int k,IntVector TimePosAttackVector)
{
 //Delete and reinizalize
 delete mpStepEvaluation;
 delete mpKeyProbability;
 delete mpAllEvaluations;
 delete mpBestPatrollerStratNum;
 delete mpBestPatrollerStrat;
 delete mpAllBestPatrollerStratNum;
 delete mpAllBestPatrollerStrat;
 delete mpWeightings;

  //Setting up Weights for some choice later
 //We need to know if the centre (i.e type k+2) has been removed by domination
 int attacktime=mpMixedPatrollerSystem->GetPatrollerSystem()->GetAttackTime();

 int numberoftypes=0;
 if(attacktime>=3)
 {
  //removal of penultimate nodes has occured so only k+1 types
  //Form Objects in bins to generate all combinations
  numberoftypes=k+1;
 }
 else
 {
  //no removal has occured so only k+3 types
  //Form Objects in bins to generate all combinations
  numberoftypes=k+3;
 }
  ObjectsInBins ObjBins(mNumSteps,numberoftypes);
  Matrix Weighting(ObjBins.GetNumberInBins());
  //assert(Weighting.GetNumberOfRows()==ObjBins.GetNumCombinations());
  Weighting=Weighting*mStepSize;
  //std::flush(std::cout<<"the total number of combs is "<<ObjBins.GetNumCombinations()<<"\n");


 mpStepEvaluation=new Vector(ObjBins.GetNumCombinations());
 mpKeyProbability=new Vector(ObjBins.GetNumCombinations());
 mpAllEvaluations=
 new Matrix(mpMixedPatrollerSystem->GetPatrollerSystem()
            ->GetNumPurePatrolOptions(),ObjBins.GetNumCombinations());
 mpBestPatrollerStratNum=new IntVector(ObjBins.GetNumCombinations());
 mpBestPatrollerStrat=
 new IntMatrix(ObjBins.GetNumCombinations(),mpMixedPatrollerSystem
               ->GetPatrollerSystem()->GetGameTime());
 mpAllBestPatrollerStratNum=new IntMatrix(1,ObjBins.GetNumCombinations());
 mpAllBestPatrollerStrat=new Int3DMatrix(1,mpMixedPatrollerSystem
                                    ->GetPatrollerSystem()->GetGameTime(),
                                    ObjBins.GetNumCombinations());

 mpWeightings=new Matrix(Weighting);

 //For each Weighting we will perform the single evaluation
 int i=1;
 while(i<=Weighting.GetNumberOfRows())
 {
  MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
  Generator.GenerateExtendedStarTestTime(n,k,
  Weighting.GetRow(i),TimePosAttackVector);
  Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());
  //std::flush(std::cout<<"We are evaluating the "<<i<<"th\n");
  EvaluateSingle(MixedAttackerStrat,i);

  i=i+1;
 }
}

void BatchMixedPolicyEvaluation::EvaluateDualStarBatchTimePosTestPW
(int n1, int n2, IntVector TimePosAttackVector)
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
  Generator.GenerateDualStarTestTimePW(n1,n1,weight,TimePosAttackVector);
  Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

  EvaluateSingle(MixedAttackerStrat,i+1);

  i=i+1;
 }

}
