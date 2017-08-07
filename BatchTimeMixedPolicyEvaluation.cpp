#include "BatchTimeMixedPolicyEvaluation.hpp"
#include<cmath>

//Standard constructor
BatchTimeMixedPolicyEvaluation::
    BatchTimeMixedPolicyEvaluation(BatchMixedPolicyEvaluation &aBatch)
{
 mpBatchPolicyEvaluation=&aBatch;

 //Store the number of options to start the attack at each node
 mNumStartTimes=mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
 ->GetPatrollerSystem()->GetGameTime()
 -mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
 ->GetPatrollerSystem()->GetAttackTime()+1;

 //Number of choices to try for time
 //Note. 1 is subtracted due to not allowing the null choice (i.e no attack)
 mNumTimeChoices=pow(2,2*mNumStartTimes)-1;

 mpAttackingTimePos=new IntVector(2*mNumStartTimes);

 //Create Storage
 mpTimePosEvaluation=new Vector(mNumTimeChoices);
 mpBestTimePosWeight=new Vector(mNumTimeChoices);
 mpBestTimePosPatrollerStratNum=new IntVector(mNumTimeChoices);
 mpBestTimePosPatrollerStrat=
 new IntMatrix(mNumTimeChoices,mpBatchPolicyEvaluation
               ->GetMixedPatrollerSystem()->GetPatrollerSystem()
               ->GetGameTime());
}

//Destructor
BatchTimeMixedPolicyEvaluation::~BatchTimeMixedPolicyEvaluation()
{
 delete mpAttackingTimePos;

 delete mpTimePosEvaluation;
 delete mpBestTimePosWeight;
 delete mpBestTimePosPatrollerStratNum;
 delete mpBestTimePosPatrollerStrat;
}

//Setters and Getters
void BatchTimeMixedPolicyEvaluation::SetBatchPolicyEvaluation
                                     (BatchMixedPolicyEvaluation &aBatch)
{
 mpBatchPolicyEvaluation=&aBatch;

 //Store the number of options to start the attack at each node
 mNumStartTimes=mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
 ->GetPatrollerSystem()->GetGameTime()-mpBatchPolicyEvaluation
 ->GetMixedPatrollerSystem()->GetPatrollerSystem()->GetAttackTime()+1;

 //Number of choices to try for time
 mNumTimeChoices=pow(2,2*mNumStartTimes)-1;

 mpAttackingTimePos=new IntVector(2*mNumStartTimes);
}
BatchMixedPolicyEvaluation* BatchTimeMixedPolicyEvaluation::
                            GetMixedPolicyEvaluation()
{
 return mpBatchPolicyEvaluation;
}
int BatchTimeMixedPolicyEvaluation::GetNumTimeChoices()
{
 return mNumTimeChoices;
}
IntVector BatchTimeMixedPolicyEvaluation::GetAttackingTimePos()
{
 return (*mpAttackingTimePos);
}

//Batch Evaluation (on time)
/*
This method is used to batch evaluation all possible time position for the
Weight Batch evaluator passed to the object.

Note. The Possible number of time positions checked is 2^(2*number of time
                                                          attack options)
      Therefore for great choices, it is very slow at evaluating
*/
void BatchTimeMixedPolicyEvaluation::EvaluateBatchTimeTest(int n,int k)
{
 //Reinisalize storage
 delete mpTimePosEvaluation;
 delete mpBestTimePosWeight;
 delete mpBestTimePosPatrollerStratNum;
 delete mpBestTimePosPatrollerStrat;

 mpTimePosEvaluation=new Vector(mNumTimeChoices);
 mpBestTimePosWeight=new Vector(mNumTimeChoices);
 mpBestTimePosPatrollerStratNum=new IntVector(mNumTimeChoices);
 mpBestTimePosPatrollerStrat=
 new IntMatrix(mNumTimeChoices,mpBatchPolicyEvaluation->
               GetMixedPatrollerSystem()->GetPatrollerSystem()->GetGameTime());

 //Perform evaluation
 int choice=1;
 int minElement=0;
 std::cout<<"Trying choices: \n";
 std::cout<<"------------------------------------------ \n";
 while(choice<=mNumTimeChoices)
 {
  //Create time selection vector
  delete mpAttackingTimePos;
  mpAttackingTimePos=new IntVector(2*mNumStartTimes);
  ConvToBinary(choice,mpAttackingTimePos,1);

  std::cout<<"Choice:"<<choice<<" Attacking Pattern: \n"<<(*mpAttackingTimePos);

  //Evaluate the time positions for each step in the weight
  mpBatchPolicyEvaluation->EvaluateBatchTimePosTest(n,k,(*mpAttackingTimePos));

  //Retrive the best weight for the attack time position and store information

  //Store the minimum for choice fo time positioning
  minElement=(mpBatchPolicyEvaluation->GetEvaluationVector()).MinElement();

  //Store the information for the choice of time positioning
  (*mpTimePosEvaluation)(choice)=(mpBatchPolicyEvaluation->
                                  GetEvaluationVector())(minElement);
  (*mpBestTimePosWeight)(choice)=
  (minElement-1)*(mpBatchPolicyEvaluation->GetStepSize());
  (*mpBestTimePosPatrollerStratNum)(choice)=
  (mpBatchPolicyEvaluation->GetBestPatrollerStratNum())(minElement);
   mpBestTimePosPatrollerStrat->
   SetRow(choice,(mpBatchPolicyEvaluation->
                  GetBestPatrollerStrat()).GetRow(minElement));



  choice=choice+1;
  }

 //Display the ultimate results of the best choice of attack
 //time position and weight
 std::cout<<"Overall best choice of Weight and Attack Position \n";
 std::cout<<"------------------------------------------------------------ \n";
 int BestTimeChoice=mpTimePosEvaluation->MinElement();
 std::cout<<"Attack Position is number "<<BestTimeChoice<<" being: \n";
 IntVector* pAttackPattern;
 pAttackPattern=new IntVector(2*mNumStartTimes);
 ConvToBinary(BestTimeChoice,pAttackPattern,1);
 std::cout<<(*pAttackPattern);
 std::cout<<"Weight is "<<(*mpBestTimePosWeight)(BestTimeChoice)<<"\n";
 std::cout<<"For an evaluation of "
 <<(*mpTimePosEvaluation)(BestTimeChoice)<<"\n";
 std::cout<<"The response patrol will be:"<<mpBestTimePosPatrollerStrat
                                             ->GetRow(BestTimeChoice);
}

//Converts to binary vector
/*
This method takes a number to be converted to binary, a vector to store the
binary digits and a starting entry to store the binary digits (default is 1)

Note. If the passed storage vector is too small the method will extend the
vector to the correct size
*/
void BatchTimeMixedPolicyEvaluation::
     ConvToBinary(int number,IntVector* pStorageVector,int StartEntry/*=1*/)
{
 int remainder=0;
 //std::cout<<"converting to binary";

 //If the StorageVector is not large enough then add a space
 if(StartEntry > pStorageVector->GetSize())
 {
  //Add a space in the vector
  pStorageVector->Extend(1);
 }
 else{}

 //Convert to binary
 if(number >=2)
 {
  remainder=number % 2;
  (*pStorageVector)(StartEntry)=remainder;
  ConvToBinary(number >> 1,pStorageVector,StartEntry+1);
 }
 else
 {
  remainder=number % 2;
  (*pStorageVector)(StartEntry)=remainder;
  }
}
