#include "BatchTimeMixedPolicyEvaluation.hpp"
#include<cmath>

BatchTimeMixedPolicyEvaluation::BatchTimeMixedPolicyEvaluation(BatchMixedPolicyEvaluation &aBatch)
{
 mpBatchPolicyEvaluation=&aBatch;

 //Store the number of options to start the attack at each node
 mNumStartTimes=mpBatchPolicyEvaluation->GetMixedPatrollerSystem()->GetPatrollerSystem()->GetGameTime()
 -mpBatchPolicyEvaluation->GetMixedPatrollerSystem()->GetPatrollerSystem()->GetAttackTime()+1;

 //Number of choices to try for time
 mNumTimeChoices=pow(2,2*mNumStartTimes)-1; //1 is subtracted due to not allowing the null choice

 mpAttackingTimePos=new IntVector(2*mNumStartTimes);

 //Create Storage
 mpTimePosEvaluation=new Vector(mNumTimeChoices);
 mpBestTimePosWeight=new Vector(mNumTimeChoices);
 mpBestTimePosPatrollerStratNum=new IntVector(mNumTimeChoices);
 mpBestTimePosPatrollerStrat=new IntMatrix(mNumTimeChoices,mpBatchPolicyEvaluation->GetMixedPatrollerSystem()->GetPatrollerSystem()->GetGameTime());
}

BatchTimeMixedPolicyEvaluation::~BatchTimeMixedPolicyEvaluation()
{
 delete mpAttackingTimePos;

 delete mpTimePosEvaluation;
 delete mpBestTimePosWeight;
 delete mpBestTimePosPatrollerStratNum;
 delete mpBestTimePosPatrollerStrat;
}

//Setters and Getters
void BatchTimeMixedPolicyEvaluation::SetBatchPolicyEvaluation(BatchMixedPolicyEvaluation &aBatch)
{
 mpBatchPolicyEvaluation=&aBatch;

 //Store the number of options to start the attack at each node
 mNumStartTimes=mpBatchPolicyEvaluation->GetMixedPatrollerSystem()->GetPatrollerSystem()->GetGameTime()
 -mpBatchPolicyEvaluation->GetMixedPatrollerSystem()->GetPatrollerSystem()->GetAttackTime()+1;

 //Number of choices to try for time
 mNumTimeChoices=pow(2,2*mNumStartTimes)-1;

 mpAttackingTimePos=new IntVector(2*mNumStartTimes);
}
BatchMixedPolicyEvaluation* BatchTimeMixedPolicyEvaluation::GetMixedPolicyEvaluation()
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
 mpBestTimePosPatrollerStrat=new IntMatrix(mNumTimeChoices,mpBatchPolicyEvaluation->GetMixedPatrollerSystem()->GetPatrollerSystem()->GetGameTime());

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
  (*mpTimePosEvaluation)(choice)=(mpBatchPolicyEvaluation->GetEvaluationVector())(minElement);
  (*mpBestTimePosWeight)(choice)=(minElement-1)*(mpBatchPolicyEvaluation->GetStepSize());
  (*mpBestTimePosPatrollerStratNum)(choice)=(mpBatchPolicyEvaluation->GetBestPatrollerStratNum())(minElement);
   mpBestTimePosPatrollerStrat->SetRow(choice,(mpBatchPolicyEvaluation->GetBestPatrollerStrat()).GetRow(minElement));



  choice=choice+1;
  }

 //Display the ultimate results of the best choice of attack time position and weight
 std::cout<<"Overall best choice of Weight and Attack Position \n";
 std::cout<<"------------------------------------------------------------ \n";
 int BestTimeChoice=mpTimePosEvaluation->MinElement();
 std::cout<<"Attack Position is number "<<BestTimeChoice<<" being: \n";
 IntVector* pAttackPattern;
 pAttackPattern=new IntVector(2*mNumStartTimes);
 ConvToBinary(BestTimeChoice,pAttackPattern,1);
 std::cout<<(*pAttackPattern);
 std::cout<<"Weight is "<<(*mpBestTimePosWeight)(BestTimeChoice)<<"\n";
 std::cout<<"For an evaluation of "<<(*mpTimePosEvaluation)(BestTimeChoice)<<"\n";
 std::cout<<"The response patrol will be:"<<mpBestTimePosPatrollerStrat->GetRow(BestTimeChoice);
}

//Converts to binary vector
//Not the VectorSize given needs to be large enough to perform conversion
void BatchTimeMixedPolicyEvaluation::ConvToBinary(int number,IntVector* pStorageVector,int StartEntry)
{
 int remainder=0;
 //std::cout<<"converting to binary";
 if(StartEntry > pStorageVector->GetSize()) //If the StorageVector is not large enough then add a space
 {
  //Add a space in the vector
  pStorageVector->Extend(1);
 }
 else{}
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
