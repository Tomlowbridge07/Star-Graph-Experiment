#include "BatchTimeMixedPolicyEvaluation.hpp"
#include<cmath>
#include<cassert>

//Standard constructor
BatchTimeMixedPolicyEvaluation::
BatchTimeMixedPolicyEvaluation
(BatchMixedPolicyEvaluation &aBatch,int NumTypes/*=2*/)
{
 mpBatchPolicyEvaluation=&aBatch;
 mNumTypes=NumTypes;

 //Store the number of options to start the attack at each node
 mNumStartTimes=mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
 ->GetPatrollerSystem()->GetGameTime()
 -mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
 ->GetPatrollerSystem()->GetAttackTime()+1;

 //Number of choices to try for time
 //Note. 1 is subtracted due to not allowing the null choice (i.e no attack)
 mNumTimeChoices=pow(2,mNumTypes*mNumStartTimes)-1;

 mpAttackingTimePos=new IntVector(mNumTypes*mNumStartTimes);

 //Create Storage
 mpTimePosEvaluation=new Vector(mNumTimeChoices);
 mpBestTimePosWeight=new Matrix(mNumTimeChoices,mNumTypes);
 mpBestTimePosPatrollerStratNum=new IntVector(mNumTimeChoices);
 mpBestTimePosPatrollerStrat=
 new IntMatrix(mNumTimeChoices,mpBatchPolicyEvaluation
               ->GetMixedPatrollerSystem()->GetPatrollerSystem()
               ->GetGameTime());

 mpAllBestTimePatrollerStratNum=new IntMatrix(1,mNumTimeChoices);
 mpAllBestTimePatrollerStrat=new Int3DMatrix(1,
 mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
 ->GetPatrollerSystem()->GetGameTime(), mNumTimeChoices);
}

//Destructor
BatchTimeMixedPolicyEvaluation::~BatchTimeMixedPolicyEvaluation()
{
 delete mpAttackingTimePos;

 delete mpTimePosEvaluation;
 delete mpBestTimePosWeight;
 delete mpBestTimePosPatrollerStratNum;
 delete mpBestTimePosPatrollerStrat;
 delete mpAllBestTimePatrollerStratNum;
 delete mpAllBestTimePatrollerStrat;
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
 mNumTimeChoices=pow(2,mNumTypes*mNumStartTimes)-1;

 mpAttackingTimePos=new IntVector(2*mNumStartTimes);
}
void BatchTimeMixedPolicyEvaluation::SetNumTypes(int NumTypes)
{
 mNumTypes=NumTypes;

 //Number of choices to try for time
 //Note. 1 is subtracted due to not allowing the null choice (i.e no attack)
 mNumTimeChoices=pow(2,mNumTypes*mNumStartTimes)-1;

 mpAttackingTimePos=new IntVector(mNumTypes*mNumStartTimes);

 //delete storage
 delete mpAttackingTimePos;

 delete mpTimePosEvaluation;
 delete mpBestTimePosWeight;
 delete mpBestTimePosPatrollerStratNum;
 delete mpBestTimePosPatrollerStrat;
 delete mpAllBestTimePatrollerStratNum;
 delete mpAllBestTimePatrollerStrat;


 //Create Storage
 mpTimePosEvaluation=new Vector(mNumTimeChoices);
 mpBestTimePosWeight=new Matrix(mNumTimeChoices,mNumTypes);
 mpBestTimePosPatrollerStratNum=new IntVector(mNumTimeChoices);
 mpBestTimePosPatrollerStrat=
 new IntMatrix(mNumTimeChoices,mpBatchPolicyEvaluation
               ->GetMixedPatrollerSystem()->GetPatrollerSystem()
               ->GetGameTime());

 mpAllBestTimePatrollerStratNum=new IntMatrix(1,mNumTimeChoices);
 mpAllBestTimePatrollerStrat=new Int3DMatrix(1,
 mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
 ->GetPatrollerSystem()->GetGameTime(), mNumTimeChoices);
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
void BatchTimeMixedPolicyEvaluation::
EvaluateExtendedStarBatchTimeTestPW(int n,int k)
{
 if(mNumTypes!=2)
 {
  std::cout<<"Error: Did you mean to run this \n"
  <<"This method is designed to only attack the extended end node and"
  <<"the normal end nodes";
 }

 //Reinisalize storage
 delete mpTimePosEvaluation;
 delete mpBestTimePosWeight;
 delete mpBestTimePosPatrollerStratNum;
 delete mpBestTimePosPatrollerStrat;
 delete mpAllBestTimePatrollerStratNum;
 delete mpAllBestTimePatrollerStrat;

 mpTimePosEvaluation=new Vector(mNumTimeChoices);
 mpBestTimePosWeight=new Matrix(mNumTimeChoices,mNumTypes);
 mpBestTimePosPatrollerStratNum=new IntVector(mNumTimeChoices);
 mpBestTimePosPatrollerStrat=
 new IntMatrix(mNumTimeChoices,mpBatchPolicyEvaluation->
               GetMixedPatrollerSystem()->GetPatrollerSystem()->GetGameTime());

 mpAllBestTimePatrollerStratNum=new IntMatrix(1,mNumTimeChoices);
 mpAllBestTimePatrollerStrat=new Int3DMatrix(1,
 mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
 ->GetPatrollerSystem()->GetGameTime(), mNumTimeChoices);

 //Perform evaluation
 int choice=1;
 int minElement=0;
 std::cout<<"Trying choices: \n";
 std::cout<<"------------------------------------------ \n";
 while(choice<=mNumTimeChoices)
 {
  //Create time selection vector
  delete mpAttackingTimePos;
  mpAttackingTimePos=new IntVector(mNumTypes*mNumStartTimes);
  ConvToBinary(choice,mpAttackingTimePos,1);

  std::cout<<"Choice:"<<choice<<" Attacking Pattern: \n"<<(*mpAttackingTimePos);

  //Evaluate the time positions for each step in the weight
  mpBatchPolicyEvaluation->
  EvaluateExtenedStarBatchTimePosTestPW(n,k,(*mpAttackingTimePos));

  //Retrive the best weight for the attack time position and store information

  //Store the minimum for choice fo time positioning
  minElement=(mpBatchPolicyEvaluation->GetEvaluationVector()).MinElement();

  //Store the information for the choice of time positioning
  (*mpTimePosEvaluation)(choice)=(mpBatchPolicyEvaluation->
                                  GetEvaluationVector())(minElement);
  ///Need to fix to allow it either store the vector of weights (or the combination number
  ///which can be retrived later
  Vector Weight(mNumTypes);
  Weight(1)=(minElement-1)*(mpBatchPolicyEvaluation->GetStepSize());
  Weight(2)=1-Weight(1);
  mpBestTimePosWeight->SetRow(choice,Weight);

  (*mpBestTimePosPatrollerStratNum)(choice)=
  (mpBatchPolicyEvaluation->GetBestPatrollerStratNum())(minElement);
   mpBestTimePosPatrollerStrat->
   SetRow(choice,(mpBatchPolicyEvaluation->
                  GetBestPatrollerStrat()).GetRow(minElement));

   //Storing all for that best weighted time choice
   IntMatrix
   BestWeightNumMat(mpBatchPolicyEvaluation->GetAllBestPatrollerStratNum());
   Int3DMatrix
   BestWeight3DMat(mpBatchPolicyEvaluation->GetAllBestPatrollerStrat());
   int NumberOfStrategies=BestWeightNumMat.GetNumberOfRows();
   NumberOfStrategies=BestWeight3DMat.GetNumberRows();
   assert(BestWeightNumMat.GetNumberOfRows()==NumberOfStrategies);

   //Make sure correct size
   if(NumberOfStrategies>mpAllBestTimePatrollerStratNum->GetNumberOfRows())
   {
    mpAllBestTimePatrollerStratNum->ExtendRow(NumberOfStrategies-
    mpAllBestTimePatrollerStratNum->GetNumberOfRows());

    mpAllBestTimePatrollerStrat->ExtendRow(NumberOfStrategies-
    mpAllBestTimePatrollerStrat->GetNumberRows());
   }
   //Storing all patrolling strategies for this time choice

   //Form in matrix form to allow block storage
   /*
    The conversion to a column matrix and block insertion is used as the
    inserted vector may not be of the correct length.
   */
   IntMatrix InsertingColMatrix(BestWeightNumMat.GetCol(minElement),false);
   mpAllBestTimePatrollerStratNum->SetBlock(1,choice,
   InsertingColMatrix);

   mpAllBestTimePatrollerStrat->Set3DBlock(1,1,choice,
   BestWeight3DMat.Get3DBlock(1,1,minElement,NumberOfStrategies,
    mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
    ->GetPatrollerSystem()->GetGameTime(),1));

  choice=choice+1;
  }

 //Display the ultimate results of the best choice of attack
 //time position and weight
 std::cout<<"Overall best choice of Weight and Attack Position \n";
 std::cout<<"------------------------------------------------------------ \n";
 int BestTimeChoice=mpTimePosEvaluation->MinElement();
 std::cout<<"Attack Position is number "<<BestTimeChoice<<" being: \n";
 IntVector* pAttackPattern;
 pAttackPattern=new IntVector(mNumTypes*mNumStartTimes);
 ConvToBinary(BestTimeChoice,pAttackPattern,1);
 std::cout<<(*pAttackPattern);
 std::cout<<"Weight is "<<mpBestTimePosWeight->GetRow(BestTimeChoice)<<"\n";
 std::cout<<"For an evaluation of "
 <<(*mpTimePosEvaluation)(BestTimeChoice)<<"\n";
 std::cout<<"The response patrol will be:"<<mpBestTimePosPatrollerStrat
                                             ->GetRow(BestTimeChoice)<<"\n";
 std::cout<<"With Other (equally good) response patrolling being:"<<
 mpAllBestTimePatrollerStrat->GetLayerMatrix(BestTimeChoice)<<"\n";
 std::cout<<"------------------------------------------------------------ \n";
 std::cout<<"Other (equally good) attack position numbers are \n ";
 IntVector BestTimeChoices(mpTimePosEvaluation->MinElements());
 std::cout<<BestTimeChoices<<"\n";
 std::cout<<"Corresponding to attack positions being: \n";
 std::cout<<"Note:The following are displayed in Rows \n";

 IntMatrix AttackPatterns(BestTimeChoices.GetSize(),mNumTypes*mNumStartTimes);
 for(int i=1; i<=BestTimeChoices.GetSize(); i++)
 {
  delete pAttackPattern;
  pAttackPattern=new IntVector(2*mNumStartTimes);
  ConvToBinary(BestTimeChoices(i),pAttackPattern,1);
  AttackPatterns.SetRow(i,(*pAttackPattern));
 }
 std::cout<<AttackPatterns;

 delete pAttackPattern;
}

//Batch Evaluation (on time)
/*
This method is used to batch evaluation all possible time position for the
Weight Batch evaluator passed to the object.

Note. The Possible number of time positions checked is
2^(numoftypes* number of time attack options)
Therefore for great choices, it is very slow at evaluating
*/
void BatchTimeMixedPolicyEvaluation::
EvaluateExtendedStarBatchTimeTest(int n,int k)
{
 if(mNumTypes==2)
 {
  std::cout<<"Error: Did you mean to run this \n"
  <<"This method is designed to use all the line type nodes"
  <<" bar the two end penultimate nodes if they are dominated (i.e m>=3)";
 }

 //Reinisalize storage
 delete mpTimePosEvaluation;
 delete mpBestTimePosWeight;
 delete mpBestTimePosPatrollerStratNum;
 delete mpBestTimePosPatrollerStrat;
 delete mpAllBestTimePatrollerStratNum;
 delete mpAllBestTimePatrollerStrat;

 mpTimePosEvaluation=new Vector(mNumTimeChoices);
 mpBestTimePosWeight=new Matrix(mNumTimeChoices,mNumTypes);
 mpBestTimePosPatrollerStratNum=new IntVector(mNumTimeChoices);
 mpBestTimePosPatrollerStrat=
 new IntMatrix(mNumTimeChoices,mpBatchPolicyEvaluation->
               GetMixedPatrollerSystem()->GetPatrollerSystem()->GetGameTime());

 mpAllBestTimePatrollerStratNum=new IntMatrix(1,mNumTimeChoices);
 mpAllBestTimePatrollerStrat=new Int3DMatrix(1,
 mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
 ->GetPatrollerSystem()->GetGameTime(), mNumTimeChoices);

 //Perform evaluation
 int choice=1;
 int minElement=0;
 std::cout<<"Trying choices: \n";
 std::cout<<"------------------------------------------ \n";
 while(choice<=mNumTimeChoices)
 {
  //Create time selection vector
  delete mpAttackingTimePos;
  mpAttackingTimePos=new IntVector(mNumTypes*mNumStartTimes);
  ConvToBinary(choice,mpAttackingTimePos,1);

  std::cout<<"Choice:"<<choice<<" Attacking Pattern: \n"<<(*mpAttackingTimePos);

  //Evaluate the time positions for each step in the weight
  mpBatchPolicyEvaluation->
  EvaluateExtenedStarBatchTimePosTest(n,k,(*mpAttackingTimePos));

  //Retrive the best weight for the attack time position and store information
  //std::flush(std::cout<<"Here");

  //Store the minimum for choice fo time positioning
  minElement=(mpBatchPolicyEvaluation->GetEvaluationVector()).MinElement();
  std::cout<<"min element is"<<minElement;

  //Store the information for the choice of time positioning
  (*mpTimePosEvaluation)(choice)=(mpBatchPolicyEvaluation->
                                  GetEvaluationVector())(minElement);

 //std::flush(std::cout<<"Weightings "<<(mpBatchPolicyEvaluation->GetWeightings()));
 mpBestTimePosWeight->SetRow(choice,(mpBatchPolicyEvaluation->GetWeightings()).GetRow(minElement));


  //std::flush(std::cout<<"Change is "<<(*mpBestTimePosWeight));

  (*mpBestTimePosPatrollerStratNum)(choice)=
  (mpBatchPolicyEvaluation->GetBestPatrollerStratNum())(minElement);

   mpBestTimePosPatrollerStrat->
   SetRow(choice,(mpBatchPolicyEvaluation->
                  GetBestPatrollerStrat()).GetRow(minElement));

   //std::flush(std::cout<<"Here2"<<(*mpBestTimePosPatrollerStrat));

   //Storing all for that best weighted time choice

   //Retrive All Best patrolling strat numbers for this particular choice of
   //time and
   IntMatrix
   BestWeightNumMat(mpBatchPolicyEvaluation->GetAllBestPatrollerStratNum());
   //Retrive All Best patrolling strats
   Int3DMatrix
   BestWeight3DMat(mpBatchPolicyEvaluation->GetAllBestPatrollerStrat());
   int NumberOfStrategies=BestWeightNumMat.GetNumberOfRows();
   NumberOfStrategies=BestWeight3DMat.GetNumberRows();
   assert(BestWeightNumMat.GetNumberOfRows()==NumberOfStrategies);
   //std::flush(std::cout<<"Here3"<<BestWeightNumMat<<"\n");

   //Make sure correct size
   if(NumberOfStrategies>mpAllBestTimePatrollerStratNum->GetNumberOfRows())
   {
    mpAllBestTimePatrollerStratNum->ExtendRow(NumberOfStrategies-
    mpAllBestTimePatrollerStratNum->GetNumberOfRows());

    mpAllBestTimePatrollerStrat->ExtendRow(NumberOfStrategies-
    mpAllBestTimePatrollerStrat->GetNumberRows());
   }
   //std::flush(std::cout<<"Here4"<<(*mpAllBestTimePatrollerStratNum));

   //Storing all patrolling strategies for this time choice
   //Form in matrix form to allow block storage
   IntMatrix InsertingColMatrix(BestWeightNumMat.GetCol(minElement),false);
   mpAllBestTimePatrollerStratNum->SetBlock(1,choice,
   InsertingColMatrix);
   //std::flush(std::cout<<"Here5");
   mpAllBestTimePatrollerStrat->Set3DBlock(1,1,choice,
   BestWeight3DMat.Get3DBlock(1,1,minElement,NumberOfStrategies,
    mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
    ->GetPatrollerSystem()->GetGameTime(),1));

  choice=choice+1;
  }

 //Display the ultimate results of the best choice of attack
 //time position and weight
 std::cout<<"Overall best choice of Weight and Attack Position \n";
 std::cout<<"------------------------------------------------------------ \n";
 int BestTimeChoice=mpTimePosEvaluation->MinElement();
 std::cout<<"Attack Position is number "<<BestTimeChoice<<" being: \n";
 IntVector* pAttackPattern;
 pAttackPattern=new IntVector(mNumTypes*mNumStartTimes);
 ConvToBinary(BestTimeChoice,pAttackPattern,1);
 std::cout<<(*pAttackPattern);
 std::cout<<"Weight is "<<mpBestTimePosWeight->GetRow(BestTimeChoice)<<"\n";
 std::cout<<"For an evaluation of "
 <<(*mpTimePosEvaluation)(BestTimeChoice)<<"\n";
 std::cout<<"The response patrol will be:"<<mpBestTimePosPatrollerStrat
                                             ->GetRow(BestTimeChoice)<<"\n";
 /*std::cout<<"With Other (equally good) response patrolling being:"<<
 mpAllBestTimePatrollerStrat->GetLayerMatrix(BestTimeChoice)<<"\n";


 std::cout<<"------------------------------------------------------------ \n";
 std::cout<<"Other (equally good) attack position numbers are \n ";
 IntVector BestTimeChoices(mpTimePosEvaluation->MinElements());
 std::cout<<BestTimeChoices<<"\n";
 std::cout<<"Corresponding to attack positions being: \n";
 std::cout<<"Note:The following are displayed in Rows \n";

 IntMatrix AttackPatterns(BestTimeChoices.GetSize(),mNumTypes*mNumStartTimes);
 for(int i=1; i<=BestTimeChoices.GetSize(); i++)
 {
  delete pAttackPattern;
  pAttackPattern=new IntVector(mNumTypes*mNumStartTimes);
  ConvToBinary(BestTimeChoices(i),pAttackPattern,1);
  AttackPatterns.SetRow(i,(*pAttackPattern));
 } */
 delete pAttackPattern;
 //std::cout<<AttackPatterns;
}

//Currently in use to test (S_2,S_2)
void BatchTimeMixedPolicyEvaluation::
                    EvaluateDualStarBatchTimeTestPW(int n1 , int n2)
{
if(mNumTypes!=2)
 {
  std::cout<<"Error: Did you mean to run this \n"
  <<"This method is designed to only attack the extended end node and"
  <<"the normal end nodes";
 }

 //Reinisalize storage
 delete mpTimePosEvaluation;
 delete mpBestTimePosWeight;
 delete mpBestTimePosPatrollerStratNum;
 delete mpBestTimePosPatrollerStrat;
 delete mpAllBestTimePatrollerStratNum;
 delete mpAllBestTimePatrollerStrat;

 mpTimePosEvaluation=new Vector(mNumTimeChoices);
 mpBestTimePosWeight=new Matrix(mNumTimeChoices,mNumTypes);
 mpBestTimePosPatrollerStratNum=new IntVector(mNumTimeChoices);
 mpBestTimePosPatrollerStrat=
 new IntMatrix(mNumTimeChoices,mpBatchPolicyEvaluation->
               GetMixedPatrollerSystem()->GetPatrollerSystem()->GetGameTime());

 mpAllBestTimePatrollerStratNum=new IntMatrix(1,mNumTimeChoices);
 mpAllBestTimePatrollerStrat=new Int3DMatrix(1,
 mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
 ->GetPatrollerSystem()->GetGameTime(), mNumTimeChoices);

 //Perform evaluation
 int choice=1;
 int minElement=0;
 std::cout<<"Trying choices: \n";
 std::cout<<"------------------------------------------ \n";
 while(choice<=mNumTimeChoices)
 {
  //Create time selection vector
  delete mpAttackingTimePos;
  mpAttackingTimePos=new IntVector(mNumTypes*mNumStartTimes);
  ConvToBinary(choice,mpAttackingTimePos,1);

  std::cout<<"Choice:"<<choice<<" Attacking Pattern: \n"<<(*mpAttackingTimePos);

  //Evaluate the time positions for each step in the weight
  mpBatchPolicyEvaluation->
  EvaluateDualStarBatchTimePosTestPW(n1,n2,(*mpAttackingTimePos));

  //Retrive the best weight for the attack time position and store information

  //Store the minimum for choice fo time positioning
  minElement=(mpBatchPolicyEvaluation->GetEvaluationVector()).MinElement();

  //Store the information for the choice of time positioning
  (*mpTimePosEvaluation)(choice)=(mpBatchPolicyEvaluation->
                                  GetEvaluationVector())(minElement);
  ///Need to fix to allow it either store the vector of weights (or the combination number
  ///which can be retrived later
  Vector Weight(mNumTypes);
  Weight(1)=(minElement-1)*(mpBatchPolicyEvaluation->GetStepSize());
  Weight(2)=1-Weight(1);
  mpBestTimePosWeight->SetRow(choice,Weight);

  (*mpBestTimePosPatrollerStratNum)(choice)=
  (mpBatchPolicyEvaluation->GetBestPatrollerStratNum())(minElement);
   mpBestTimePosPatrollerStrat->
   SetRow(choice,(mpBatchPolicyEvaluation->
                  GetBestPatrollerStrat()).GetRow(minElement));

   //Storing all for that best weighted time choice
   IntMatrix
   BestWeightNumMat(mpBatchPolicyEvaluation->GetAllBestPatrollerStratNum());
   Int3DMatrix
   BestWeight3DMat(mpBatchPolicyEvaluation->GetAllBestPatrollerStrat());
   int NumberOfStrategies=BestWeightNumMat.GetNumberOfRows();
   NumberOfStrategies=BestWeight3DMat.GetNumberRows();
   assert(BestWeightNumMat.GetNumberOfRows()==NumberOfStrategies);

   //Make sure correct size
   if(NumberOfStrategies>mpAllBestTimePatrollerStratNum->GetNumberOfRows())
   {
    mpAllBestTimePatrollerStratNum->ExtendRow(NumberOfStrategies-
    mpAllBestTimePatrollerStratNum->GetNumberOfRows());

    mpAllBestTimePatrollerStrat->ExtendRow(NumberOfStrategies-
    mpAllBestTimePatrollerStrat->GetNumberRows());
   }
   //Storing all patrolling strategies for this time choice

   //Form in matrix form to allow block storage
   /*
    The conversion to a column matrix and block insertion is used as the
    inserted vector may not be of the correct length.
   */
   IntMatrix InsertingColMatrix(BestWeightNumMat.GetCol(minElement),false);
   mpAllBestTimePatrollerStratNum->SetBlock(1,choice,
   InsertingColMatrix);

   mpAllBestTimePatrollerStrat->Set3DBlock(1,1,choice,
   BestWeight3DMat.Get3DBlock(1,1,minElement,NumberOfStrategies,
    mpBatchPolicyEvaluation->GetMixedPatrollerSystem()
    ->GetPatrollerSystem()->GetGameTime(),1));

  choice=choice+1;
  }

 //Display the ultimate results of the best choice of attack
 //time position and weight
 std::cout<<"Overall best choice of Weight and Attack Position \n";
 std::cout<<"------------------------------------------------------------ \n";
 int BestTimeChoice=mpTimePosEvaluation->MinElement();
 std::cout<<"Attack Position is number "<<BestTimeChoice<<" being: \n";
 IntVector* pAttackPattern;
 pAttackPattern=new IntVector(mNumTypes*mNumStartTimes);
 ConvToBinary(BestTimeChoice,pAttackPattern,1);
 std::cout<<(*pAttackPattern);
 std::cout<<"Weight is "<<mpBestTimePosWeight->GetRow(BestTimeChoice)<<"\n";
 std::cout<<"For an evaluation of "
 <<(*mpTimePosEvaluation)(BestTimeChoice)<<"\n";
 std::cout<<"The response patrol will be:"<<mpBestTimePosPatrollerStrat
                                             ->GetRow(BestTimeChoice)<<"\n";
 std::cout<<"With Other (equally good) response patrolling being:"<<
 mpAllBestTimePatrollerStrat->GetLayerMatrix(BestTimeChoice)<<"\n";
 /*
 std::cout<<"------------------------------------------------------------ \n";
 std::cout<<"Other (equally good) attack position numbers are \n ";
 IntVector BestTimeChoices(mpTimePosEvaluation->MinElements());
 std::cout<<BestTimeChoices<<"\n";
 std::cout<<"Corresponding to attack positions being: \n";
 std::cout<<"Note:The following are displayed in Rows \n";

 IntMatrix AttackPatterns(BestTimeChoices.GetSize(),mNumTypes*mNumStartTimes);
 for(int i=1; i<=BestTimeChoices.GetSize(); i++)
 {
  delete pAttackPattern;
  pAttackPattern=new IntVector(2*mNumStartTimes);
  ConvToBinary(BestTimeChoices(i),pAttackPattern,1);
  AttackPatterns.SetRow(i,(*pAttackPattern));
 }
 std::cout<<AttackPatterns; */

 delete pAttackPattern;
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
