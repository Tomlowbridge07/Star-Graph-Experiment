#include "MixedPolicyEvaluation.hpp"

#include "MixedAttackGenerator.hpp"

#include<iomanip>
#include<iostream>
#include<fstream>

//Standard
MixedPolicyEvaluation::
    MixedPolicyEvaluation(MixedPatroller& aMixedPatrollerSystem)
{
 mpMixedPatrollerSystem=&aMixedPatrollerSystem;

 //Store entries for Evaluation
 mpStepEvaluation=new Vector(1);
 mpKeyProbability=new Vector(1);
 mpBestPatrollerStratNum=new IntVector(1);
 mpBestPatrollerStrat=new IntMatrix(1,mpMixedPatrollerSystem
                                    ->GetPatrollerSystem()->GetGameTime());

 mpAllBestPatrollerStratNum=new IntMatrix(1,1);
 mpAllBestPatrollerStrat=new Int3DMatrix(1,mpMixedPatrollerSystem
                                    ->GetPatrollerSystem()->GetGameTime(),1);

 //Store Empty/Null Matrices for MT Space Evaluation
 mpMTSpaceEvaluation=new Matrix(1,1);
 mpMTSpaceKeyProbability=new Matrix(1,1);
 mpMTSpaceBestPatrollerStratNum=new IntMatrix(1,1);
 mpMTSpaceBestPatrollerStrat=new IntMatrix(1,1);
}


MixedPolicyEvaluation::~MixedPolicyEvaluation()
{

 delete mpStepEvaluation;
 delete mpKeyProbability;
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
void MixedPolicyEvaluation::
    SetMixedPatrollerSystem(MixedPatroller& aMixedPatrollerSystem)
{
 mpMixedPatrollerSystem=&aMixedPatrollerSystem;
}
MixedPatroller* MixedPolicyEvaluation::GetMixedPatrollerSystem()
{
 return mpMixedPatrollerSystem;
}
Vector MixedPolicyEvaluation::GetEvaluationVector()
{
 return (*mpStepEvaluation);
}
Vector MixedPolicyEvaluation::GetKeyProbabilityVector()
{
 return (*mpKeyProbability);
}
IntVector MixedPolicyEvaluation::GetBestPatrollerVector()
{
 return (*mpBestPatrollerStratNum);
}
IntMatrix MixedPolicyEvaluation::GetBestPatrollerStrat()
{
 return (*mpBestPatrollerStrat);
}
Int3DMatrix MixedPolicyEvaluation::GetAllBestPatrollerStrat()
{
 return (*mpAllBestPatrollerStrat);
}
Matrix MixedPolicyEvaluation::GetMTSpaceEvaluation()
{
 return (*mpMTSpaceEvaluation);
}
Matrix MixedPolicyEvaluation::GetMTSpaceKeyProbability()
{
 return (*mpMTSpaceKeyProbability);
}
IntMatrix MixedPolicyEvaluation::GetMTSpaceBestPatrollerStratNum()
{
 return (*mpMTSpaceBestPatrollerStratNum);
}
IntMatrix MixedPolicyEvaluation::GetMTSpaceBestPatrollerstrat()
{
 return (*mpMTSpaceBestPatrollerStrat);
}


void MixedPolicyEvaluation::EvaluateGraph(Vector MixedAttackerStrat)
{
   //Delete and reinizalize
 delete mpStepEvaluation;
 delete mpKeyProbability;
 delete mpBestPatrollerStratNum;
 delete mpBestPatrollerStrat;
 delete mpAllBestPatrollerStratNum;
 delete mpAllBestPatrollerStrat;

 mpStepEvaluation=new Vector(1);
 mpKeyProbability=new Vector(1);
 mpBestPatrollerStratNum=new IntVector(1);
 mpBestPatrollerStrat=
 new IntMatrix(1,mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime());

 mpAllBestPatrollerStratNum=new IntMatrix(1,1);
 mpAllBestPatrollerStrat=new Int3DMatrix(1,mpMixedPatrollerSystem
                                    ->GetPatrollerSystem()->GetGameTime(),1);

 //Once Set up We evaluate the mixed attacker strat.
 mpMixedPatrollerSystem->SetMixedAttackerStrategy(MixedAttackerStrat);
 mpMixedPatrollerSystem->EvaluateAttackerAgainstPurePatroller();
 //Store the Best the patroller can do purely and the key probability (i.e that on external node)
 (*mpStepEvaluation)(1)=
 (mpMixedPatrollerSystem->GetAttackerAgainstPureEvaluation()).Max();
 (*mpKeyProbability)(1)=MixedAttackerStrat(1);
 //Store the strategy number
 (*mpBestPatrollerStratNum)(1)=
 (mpMixedPatrollerSystem->GetAttackerAgainstPureEvaluation()).MaxElement();
 //store the strategy
 mpBestPatrollerStrat->SetRow(1,mpMixedPatrollerSystem->GetPatrollerSystem()->
                    ConvertPatrollerOptionNum((*mpBestPatrollerStratNum)(1)));


 //Saving All Best Strategies
 //Alter Storage Size
 IntVector AllBestElements(
 (mpMixedPatrollerSystem->GetAttackerAgainstPureEvaluation()).MaxElements());
 int NumOfBestStrategies=AllBestElements.GetSize();
 mpAllBestPatrollerStratNum->ExtendRow(NumOfBestStrategies-1);
 mpAllBestPatrollerStrat->ExtendRow(NumOfBestStrategies-1);

 //Store Strat Num's and Strat
 for(int i=1; i<=NumOfBestStrategies; i++)
 {
  (*mpAllBestPatrollerStratNum)(i,1)=AllBestElements(i);
  mpAllBestPatrollerStrat->SetRowVector(i,1,
  mpMixedPatrollerSystem->GetPatrollerSystem()->
  ConvertPatrollerOptionNum(AllBestElements(i)));
 }

}

//Evaluations designed to use the generators for a normal walk style
void MixedPolicyEvaluation::EvaluateLineGraph(int n)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateLineAttack(n);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 //Evaluate the attack
 EvaluateGraph(MixedAttackerStrat);
}
void MixedPolicyEvaluation::EvaluateTimedLineGraph(int n)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateTimedLineAttack(n);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 //Evaluate the attack
 EvaluateGraph(MixedAttackerStrat);
}
void MixedPolicyEvaluation::EvaluateOverallLineGraph(int n)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateOverallLineAttack(n);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 //Evaluate the attack
 EvaluateGraph(MixedAttackerStrat);
}
void MixedPolicyEvaluation::EvaluateStarGraph(int n , int k)
{
 //Generate the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateExtendedStarAttack(n,k);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 //Evaluate
 EvaluateGraph(MixedAttackerStrat);
}
void MixedPolicyEvaluation::EvaluateTimedStarGraph(int n,int k)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateTimedExtendedStarAttack(n,k);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 EvaluateGraph(MixedAttackerStrat);
}
void MixedPolicyEvaluation::EvaluateOverallStarGraph(int n,int k)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateOverallExtendedStarAttack(n,k);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 EvaluateGraph(MixedAttackerStrat);
}

//Evaulations designed to use the generators for a Path Wait style walk
void MixedPolicyEvaluation::EvaluateLineGraphPW(int n)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateLineAttackPW(n);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 //Evaluate the attack
 EvaluateGraph(MixedAttackerStrat);
}
void MixedPolicyEvaluation::EvaluateTimedLineGraphPW(int n)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateTimedLineAttackPW(n);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 //Evaluate the attack
 EvaluateGraph(MixedAttackerStrat);
}
void MixedPolicyEvaluation::EvaluateOverallLineGraphPW(int n)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateOverallLineAttackPW(n);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 //Evaluate the attack
 EvaluateGraph(MixedAttackerStrat);
}
void MixedPolicyEvaluation::EvaluateStarGraphPW(int n , int k)
{
 //Generate the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateExtendedStarAttackPW(n,k);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 //Evaluate
 EvaluateGraph(MixedAttackerStrat);
}
void MixedPolicyEvaluation::EvaluateTimedStarGraphPW(int n,int k)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateTimedExtendedStarAttackPW(n,k);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());

 EvaluateGraph(MixedAttackerStrat);
}
void MixedPolicyEvaluation::EvaluateOverallStarGraphPW(int n,int k)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateOverallExtendedStarAttackPW(n,k);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());
 EvaluateGraph(MixedAttackerStrat);
}

/*
These methods were developed alongside new strategies
*/
void MixedPolicyEvaluation::EvaluateExtendedStarGraphTestPW(int n,int k)
{
 //Generated the attack
 MixedAttackGenerator Generator(*mpMixedPatrollerSystem->GetPatrollerSystem());
 Generator.GenerateExtendedStarTestOddPW(n,k);
 Vector MixedAttackerStrat(Generator.GetGeneratedAttackVector());
 EvaluateGraph(MixedAttackerStrat);
}

//MTSpace Evaluations for normal walk style
void MixedPolicyEvaluation::EvaluateLineGraphMTSpaceBest
(int n,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateLineGraph(n);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}
void MixedPolicyEvaluation::EvaluateTimedLineGraphMTSpaceBest
(int n,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateTimedLineGraph(n);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}
void MixedPolicyEvaluation::EvaluateOverallLineGraphMTSpaceBest
(int n,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateOverallLineGraph(n);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}
void MixedPolicyEvaluation::EvaluateStarGraphMTSpaceBest
(int n,int k,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateStarGraph(n,k);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}
void MixedPolicyEvaluation::EvaluateTimedStarGraphMTSpaceBest
(int n,int k,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateTimedStarGraph(n,k);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}
void MixedPolicyEvaluation::EvaluateOverallStarGraphMTSpaceBest
(int n,int k,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateOverallStarGraph(n,k);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}


//MTSpace Evaluations for Path Wait style walk
void MixedPolicyEvaluation::EvaluateLineGraphMTSpaceBestPW
(int n,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateLineGraphPW(n);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}
void MixedPolicyEvaluation::EvaluateTimedLineGraphMTSpaceBestPW
(int n,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateTimedLineGraphPW(n);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}
void MixedPolicyEvaluation::EvaluateOverallLineGraphMTSpaceBestPW
(int n,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateOverallLineGraphPW(n);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}
void MixedPolicyEvaluation::EvaluateStarGraphMTSpaceBestPW
(int n,int k,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateStarGraphPW(n,k);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}
void MixedPolicyEvaluation::EvaluateTimedStarGraphMTSpaceBestPW
(int n,int k,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateTimedStarGraphPW(n,k);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartM+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}
void MixedPolicyEvaluation::EvaluateOverallStarGraphMTSpaceBestPW
(int n,int k,int StartM ,int StartT , int LastM , int LastT)
{
  //Set variable
  mStartT=StartT;
  mLastT=LastT;
  mStartM=StartM;
  mLastM=LastM;


  //Set up matrices
  delete mpMTSpaceEvaluation;
  delete mpMTSpaceKeyProbability;
  delete mpMTSpaceBestPatrollerStratNum;
  delete mpMTSpaceBestPatrollerStrat;

  mpMTSpaceEvaluation=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceKeyProbability=new Matrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStratNum=new IntMatrix(LastT-StartT+1,LastM-StartM+1);
  mpMTSpaceBestPatrollerStrat=
  new IntMatrix(LastT-StartT+1,LastT*(LastM-StartM+1));

  //Set to Basic Game Time and Attack Time
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(1);
  mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(1);

  int i=StartT;
  int j=StartM;
  int BestElement;
  while(i<=LastT)
  {
    std::flush(std::cout<<"Starting Evaluation of T="<<i<<"\n");
    //Set up game time
    mpMixedPatrollerSystem->GetPatrollerSystem()->SetGameTime(i);
    j=StartM;
    while(j<=LastM)
    {
     std::flush(std::cout<<"For m="<<j<<"\n");
     if(j<=i)
     {
      //Set up the attack time
      mpMixedPatrollerSystem->GetPatrollerSystem()->SetAttackTime(j);

      //Run Evaluation
      EvaluateOverallStarGraphPW(n,k);
      std::flush(std::cout<<"Evaluation Complete, moving on \n");
      //Save best values for attacker
      BestElement=(*mpStepEvaluation).MinElement();
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=
      (*mpStepEvaluation)(BestElement);
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=
      (*mpKeyProbability)(BestElement);
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=
      (*mpBestPatrollerStratNum)(BestElement);

      //Saving the Converted patrol vector

      //Take best
      mpMTSpaceBestPatrollerStrat->SetBlock(i-StartT+1,LastT*(j-StartM)+1,
      mpBestPatrollerStrat->GetBlock(BestElement,1,1,
      mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()));
     }
     else
     {
      (*mpMTSpaceEvaluation)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceKeyProbability)(i-StartT+1,j-StartM+1)=0;
      (*mpMTSpaceBestPatrollerStratNum)(i-StartT+1,j-StartM+1)=0;
       std::flush(std::cout<<"No Evaluation, as T<m \n");
     }
     j=j+1;
    }
    i=i+1;
  }
}



//Saving and displaying variables
void MixedPolicyEvaluation::PrintStepEvaluation() const
{
 std::cout<<"Displaying the Evaluation, for "<<
 mpStepEvaluation->GetSize()<<" strategies \n";
 int i=1;
 while(i<=mpStepEvaluation->GetSize())
 {
  std::cout<<std::setw(3)<<(*mpStepEvaluation)(i)<<"\n";
  i=i+1;
 }
}
void MixedPolicyEvaluation::SaveStepEvaluation
(std::string FileName/*="StepEvaluation.dat"*/) const
{
 //Open file
 std::ofstream outfile;
 outfile.open(FileName);

 //Set outfile style
 outfile<<std::scientific<<std::setprecision(5);

 //Information about the File
 outfile<<"Step Evaluation \n"
 <<"Type:Vector of Size"<<mpStepEvaluation->GetSize()<<"\n"
 <<"Game Time:"<<mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()
 <<" Attack Time:"<<
 mpMixedPatrollerSystem->GetPatrollerSystem()->GetAttackTime()<<"\n";

 //Printing the vector
 int i=1;
 while(i<=mpStepEvaluation->GetSize())
 {
  outfile<<(*mpStepEvaluation)(i)<<"\n";
  i=i+1;
 }

 outfile.close();
}
void MixedPolicyEvaluation::PrintKeyProbability() const
{
 std::cout<<"Displaying the Evaluation, for "<<
 mpStepEvaluation->GetSize()<<" strategies \n";
 int i=1;
 while(i<=mpKeyProbability->GetSize())
 {
  std::cout<<std::setw(3)<<(*mpKeyProbability)(i)<<"\n";
  i=i+1;
 }
}
void MixedPolicyEvaluation::SaveKeyProbability
(std::string FileName/*="KeyProbabilities.dat"*/) const
{
  //Open file
 std::ofstream outfile;
 outfile.open(FileName);

 //Set outfile style
 outfile<<std::scientific<<std::setprecision(5);

 //Information about the File
 outfile<<"Key Probabilities \n"
 <<"Type:Vector of Size"<<mpKeyProbability->GetSize()<<"\n"
 <<"Game Time:"<<mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()
 <<" Attack Time:"<<
 mpMixedPatrollerSystem->GetPatrollerSystem()->GetAttackTime()<<"\n";

 //Printing the vector
 int i=1;
 while(i<=mpKeyProbability->GetSize())
 {
  outfile<<(*mpKeyProbability)(i)<<"\n";
  i=i+1;
 }

 outfile.close();
}
void MixedPolicyEvaluation::PrintBestPatrollerStratNum() const
{
 std::cout<<"Displaying the Evaluation, for "<<
 mpStepEvaluation->GetSize()<<" strategies \n";
 int i=1;
 while(i<=mpBestPatrollerStratNum->GetSize())
 {
  std::cout<<std::setw(3)<<(*mpBestPatrollerStratNum)(i)<<"\n";
  i=i+1;
 }
}
void MixedPolicyEvaluation::SaveBestPatrollerStratNum
(std::string FileName/*="BestPatrollerStrategyNumbers.dat"*/) const
{
 //Open file
 std::ofstream outfile;
 outfile.open(FileName);

 //Set outfile style
 outfile<<std::scientific<<std::setprecision(5);

 //Information about the File
 outfile<<"Best Patroller Numbers \n"
 <<"Type:Vector of Size "<<mpBestPatrollerStratNum->GetSize()<<"\n"
 <<"Game Time:"<<mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()
 <<" Attack Time:"<<
 mpMixedPatrollerSystem->GetPatrollerSystem()->GetAttackTime()<<"\n";

 //Printing the vector
 int i=1;
 while(i<=mpBestPatrollerStratNum->GetSize())
 {
  outfile<<(*mpBestPatrollerStratNum)(i)<<"\n";
  i=i+1;
 }

 outfile.close();
}
void MixedPolicyEvaluation::PrintMTSpaceEvaluation() const
{
 std::cout<<"Displaying the (T,M) Space Evaluation, for "<<
 mpStepEvaluation->GetSize()<<" Strategies \n";
 int i=1;
 int j=1;
 while(i<=mpMTSpaceEvaluation->GetNumberOfRows())
 {
  j=1;
  while(j<=mpMTSpaceEvaluation->GetNumberOfColumns())
  {
   std::cout<<std::setw(3)<<(*mpMTSpaceEvaluation)(i,j)<<" ";
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }
}
void MixedPolicyEvaluation::SaveMTSpaceEvaluation
(std::string FileName/*="MTSpaceEvaluation.dat"*/) const
{
  //Open file
 std::ofstream outfile;
 outfile.open(FileName);

 //Set outfile style
 outfile<<std::scientific<<std::setprecision(5);

 //Information about the File
 outfile<<"MTSpace Evaluation \n"
 <<"Type:Matrix of Size"<<(mLastT-mStartT+1)<<"x"<<(mLastM-mStartM+1)<<"\n"
 <<"Type:Matrix of Size"<<(mLastT-mStartT+1)<<"x"<<(mLastM-mStartM+1)<<"\n"
 <<"Game Time Range:"<<mStartT<<"-"<<mLastT<<"\n"
 <<"Attack Time:"<<mStartM<<"-"<<mLastM<<"\n";

 //Printing the vector
 int i=1;
 int j=1;
 while(i<=mpMTSpaceEvaluation->GetNumberOfRows())
 {
  j=1;
  while(j<=mpMTSpaceEvaluation->GetNumberOfColumns())
  {
   outfile<<(*mpMTSpaceEvaluation)(i,j)<<" ";
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }

 outfile.close();
}
void MixedPolicyEvaluation::PrintMTSpaceKeyProbability() const
{
 std::cout<<"Displaying the (T,M) Space Key Probability, for "<<
 mpStepEvaluation->GetSize()<<" Strategies \n";
 int i=1;
 int j=1;
 while(i<=mpMTSpaceKeyProbability->GetNumberOfRows())
 {
  j=1;
  while(j<=mpMTSpaceKeyProbability->GetNumberOfColumns())
  {
   std::cout<<std::setw(3)<<(*mpMTSpaceKeyProbability)(i,j)<<" ";
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }
}
void MixedPolicyEvaluation::SaveMTSpaceKeyProbability
(std::string FileName/*="MTSpaceKeyProbabilities.dat"*/) const
{
  //Open file
 std::ofstream outfile;
 outfile.open(FileName);

 //Set outfile style
 outfile<<std::scientific<<std::setprecision(5);

 //Information about the File
 outfile<<"MTSpace Key Probabilities \n"
 <<"Type:Matrix of Size"<<(mLastT-mStartT+1)<<"x"<<(mLastM-mStartM+1)<<"\n"
 <<"Game Time Range:"<<mStartT<<"-"<<mLastT<<"\n"
 <<"Attack Time:"<<mStartM<<"-"<<mLastM<<"\n";

 //Printing the vector
 int i=1;
 int j=1;
 while(i<=mpMTSpaceKeyProbability->GetNumberOfRows())
 {
  j=1;
  while(j<=mpMTSpaceKeyProbability->GetNumberOfColumns())
  {
   outfile<<(*mpMTSpaceKeyProbability)(i,j)<<" ";
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }

 outfile.close();
}
void MixedPolicyEvaluation::PrintMTSpaceBestPatrollerStratNum() const
{
 std::cout<<"Displaying the (T,M) Space best Patroller Strategy Numbers for "<<
 mpStepEvaluation->GetSize()<<" Strategies \n";
 int i=1;
 int j=1;
 while(i<=mpMTSpaceBestPatrollerStratNum->GetNumberOfRows())
 {
  j=1;
  while(j<=mpMTSpaceBestPatrollerStratNum->GetNumberOfColumns())
  {
   std::cout<<std::setw(3)<<(*mpMTSpaceBestPatrollerStratNum)(i,j)<<" ";
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }
}
void MixedPolicyEvaluation::SaveMTSpaceBestPatrollerStratNum
(std::string FileName/*="MTSpaceBestPatrollerStrategyNumbers.dat"*/) const
{
 //Open file
 std::ofstream outfile;
 outfile.open(FileName);

 //Set outfile style
 outfile<<std::fixed<<std::setprecision(0);

 //Information about the File
 outfile<<"MTSpace Best Patroller Strategy Numbers \n"
 <<"Type:Matrix of Size"<<(mLastT-mStartT+1)<<"x"<<(mLastM-mStartM+1)<<"\n"
 <<"Game Time Range:"<<mStartT<<"-"<<mLastT<<"\n"
 <<"Attack Time:"<<mStartM<<"-"<<mLastM<<"\n";

 //Printing the vector
 int i=1;
 int j=1;
 while(i<=mpMTSpaceBestPatrollerStratNum->GetNumberOfRows())
 {
  j=1;
  while(j<=mpMTSpaceBestPatrollerStratNum->GetNumberOfColumns())
  {
   outfile<<(*mpMTSpaceBestPatrollerStratNum)(i,j)<<" ";
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }

 outfile.close();
}
void MixedPolicyEvaluation::PrintBestPatrollerStrategies()
{
 std::cout<<"Displaying the Best Patroller Strategies for "<<
 mpStepEvaluation->GetSize()<<" Strategies \n";
 int i=1;
 int j=1;
 while(i<=mpBestPatrollerStrat->GetNumberOfRows())
 {
  j=1;
  while(j<=mpBestPatrollerStrat->GetNumberOfColumns())
  {
   if((*mpBestPatrollerStrat)(i,j)!=0)
   {
    std::cout<<std::setw(3)<<(*mpBestPatrollerStrat)(i,j);
   }
   else
   {
    std::cout<<" ";
   }
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }

}
void MixedPolicyEvaluation::SaveBestPatrollerStrategies
(std::string FileName/*="BestPatrollerStrategies.dat"*/) const
{
 //Open file
 std::ofstream outfile;
 outfile.open(FileName);

 //Set outfile style
 outfile<<std::fixed<<std::setprecision(0);

 //Information about the File
 outfile<<"Best Patroller Strategy Numbers \n"
 <<"Type:Vector of Size"<<mpBestPatrollerStrat->GetNumberOfRows()<<"\n"
 <<"Game Time Range:"<<mStartT<<"-"<<mLastT<<"\n"
 <<"Attack Time:"<<mStartM<<"-"<<mLastM<<"\n";

 //Printing the vector
 int i=1;
 int j=1;
 while(i<=mpBestPatrollerStrat->GetNumberOfRows())
 {
  j=1;
  while(j<=mpBestPatrollerStrat->GetNumberOfColumns())
  {
   outfile<<(*mpBestPatrollerStrat)(i,j);
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }

 outfile.close();
}
void MixedPolicyEvaluation::PrintMTSpaceBestPatrollerStrategies()
{
 std::cout<<"Displaying the (T,m) Space Best Patroller Strategies for "<<
 mpStepEvaluation->GetSize()<<" Strategies \n";
 int i=1;
 int j=1;
 int k=1;
 std::cout<<std::fixed<<std::setprecision(0);
 while(i<=mpMTSpaceBestPatrollerStrat->GetNumberOfRows())
 {
  j=1;
  while(j<=mpMTSpaceBestPatrollerStrat->GetNumberOfColumns()/mLastT)
  {
   k=1;
   while(k<=mLastT)
   {
    if((*mpMTSpaceBestPatrollerStrat)(i,mLastT*(j-1)+k)!=0)
    {
     std::cout<<(*mpMTSpaceBestPatrollerStrat)(i,mLastT*(j-1)+k);
    }
    else
    {
     std::cout<<" ";
    }
    k=k+1;
   }
   std::cout<<" ";
   j=j+1;
  }
  std::cout<<"\n";
  i=i+1;
 }

}
void MixedPolicyEvaluation::SaveMTSpaceBestPatrollerStrategies
(std::string FileName/*="MTSpaceBestPatrollerStrategies.dat"*/) const
{
  //Open file
 std::ofstream outfile;
 outfile.open(FileName);

 //Set outfile style
 outfile<<std::fixed<<std::setprecision(0);

 //Information about the File
 outfile<<"MTSpace Best Patroller Strategy Numbers \n"
 <<"Type:Matrix of Size"<<(mLastT-mStartT+1)<<"x"<<(mLastM-mStartM+1)<<"\n"
 <<"Game Time Range:"<<mStartT<<"-"<<mLastT<<"\n"
 <<"Attack Time:"<<mStartM<<"-"<<mLastM<<"\n";

 //Printing the vector
 int i=1;
 int j=1;
 int k=1;
 while(i<=mpMTSpaceBestPatrollerStrat->GetNumberOfRows())
 {
  j=1;
  while(j<=mpMTSpaceBestPatrollerStrat->GetNumberOfColumns()/mLastT)
  {
   k=1;
   while(k<=mLastT)
   {
    if((*mpMTSpaceBestPatrollerStrat)(i,mLastT*(j-1)+k)!=0)
    {
     outfile<<(*mpMTSpaceBestPatrollerStrat)(i,mLastT*(j-1)+k);
    }
    else
    {
    }
    k=k+1;
   }
   outfile<<" ";
   j=j+1;
  }
  outfile<<"\n";
  i=i+1;
 }

 outfile.close();
}

//Print and Save all data for the experiment
//These print all data for the evaluation
//(i.e the value, the key probability of the policy and the reaction strategy)
void MixedPolicyEvaluation::PrintPolicyEvaluation()
{
 std::cout<<"Displaying the Policy Evaluation, for "<<
 mpStepEvaluation->GetSize()<<" Strategies \n";

 //Set up Column Headers
 std::cout<<"Value         ";
 std::cout<<"Key Prob      ";
 std::cout<<"Strategy"<<"\n";

 int i=1;
 int k=1;
 while(i<=mpStepEvaluation->GetSize())
 {
  //set up format
  std::cout<<std::scientific<<std::setprecision(5)
  <<std::setw(4)<<(*mpStepEvaluation)(i)<<"   "
  <<std::setw(4)<<(*mpKeyProbability)(i)<<"   ";

   //Set stream to fixed
  std::cout<<std::fixed<<std::setprecision(0)
  <<std::setw(2)<<(*mpBestPatrollerStratNum)(i)
  <<"(";

  //Convert Number in strategy for display by side of number
  k=1;
  while(k<=mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime())
  {
   if((*mpBestPatrollerStrat)(i,k)!=0)
      {
       std::cout<<(*mpBestPatrollerStrat)(i,k);
      }
      else
      {

      }
      k=k+1;
  }
  std::cout<<")"
  <<"\n";
  i=i+1;
 }
}
void MixedPolicyEvaluation::SavePolicyEvaluation
(std::string FileName/*="PolicyEvaluation.dat"*/)
{
 //Open file
 std::ofstream outfile;
 outfile.open(FileName);

 //Set outfile style
 outfile<<std::scientific<<std::setprecision(5);

 //Information about the File
 outfile<<"Policy Evaluation  \n"
 <<"Type:4 Vectors of Size "<<mpStepEvaluation->GetSize()<<"\n"
 <<"In the Order Value, Key Prob , Stratergy Number , Strategy \n"
 <<"Game Time:"<<mpMixedPatrollerSystem->GetPatrollerSystem()->GetGameTime()
 <<" Attack Time:"<<
 mpMixedPatrollerSystem->GetPatrollerSystem()->GetAttackTime()<<"\n";

 //Print the Vectors
 int i=1;
 int k=1;
  while(i<=mpStepEvaluation->GetSize())
 {
  //set up format
  outfile<<std::scientific<<std::setprecision(5)
  <<std::setw(4)<<(*mpStepEvaluation)(i)<<" "
  <<std::setw(4)<<(*mpKeyProbability)(i)<<" ";

   //Set stream to fixed
  outfile<<std::fixed<<std::setprecision(0)
  <<std::setw(2)<<(*mpBestPatrollerStratNum)(i)
  <<" ";

  //Convert Number in strategy for display by side of number
  k=1;
  while(k<=mLastT)
  {
   if((*mpBestPatrollerStrat)(i,k)!=0)
      {
       outfile<<(*mpBestPatrollerStrat)(i,k);
      }
      else
      {

      }
      k=k+1;
  }
  outfile<<"\n";
  i=i+1;
 }
}

void MixedPolicyEvaluation::PrintMTSpacePolicyEvaluation()
{
  std::cout<<std::scientific;
  std::cout<<"Displaying the (T,m) Space Policy Evaluation, for "<<
  mpStepEvaluation->GetSize()<<" Strategies \n";

  //Set up initial row=0, having Values of m
  std::cout<<std::setw(15)<<mStartM;
  int i=mStartM+1;
  while(i<=mLastM)
  {
   std::cout<<std::setw(21)<<i;
   i=i+1;
  }
  std::cout<<"\n";

  int block=1;
  int column=1;
  int time=mStartT;
  int k=1;
  while(block<=(mpMTSpaceEvaluation->GetNumberOfRows()))
  {
   //Set up outpute type for Block 1 and 2
   std::cout<<std::scientific<<std::setprecision(5);

   //If in block 1
    std::cout<<std::setw(5)<<time<<" ";
    time=time+1;
    column=1;
    while(column<=mpMTSpaceEvaluation->GetNumberOfColumns())
    {
     std::cout<<"Value:"<<std::setw(14)<<
     (*mpMTSpaceEvaluation)(block,column)<<" ";
     column=column+1;
    }
    column=1;
    std::cout<<"\n";

   //If in block 2
    std::cout<<std::setw(5)<<" "<<" ";
    column=1;
    while(column<=mpMTSpaceEvaluation->GetNumberOfColumns())
    {
     std::cout<<"Key Prob:"<<std::setw(11)<<
     (*mpMTSpaceKeyProbability)(block,column)<<" ";
     column=column+1;
    }
    column=1;
    std::cout<<"\n";

    //Block 3 and 4 should use intergers so set output
    std::cout<<std::fixed<<std::setprecision(0);

    //If in block 3
    std::cout<<std::setw(5)<<" "<<" ";
    column=1;
    while(column<=mpMTSpaceEvaluation->GetNumberOfColumns())
    {
     std::cout<<"Strat No:"<<std::setw(11)<<
     (*mpMTSpaceBestPatrollerStratNum)(block,column)<<" ";
     column=column+1;
    }
    column=1;
    std::cout<<"\n";

    //If in block 4
    std::cout<<std::setw(5)<<" "<<" ";
    column=1;
    while(column<=mpMTSpaceEvaluation->GetNumberOfColumns())
    {
     std::cout<<"Strat:"<<std::setw(14-block)<<"";
     k=1;
     while(k<=mLastT)
     {
      if((*mpMTSpaceBestPatrollerStrat)(block,k+mLastT*(column-1))!=0)
      {
       std::cout<<(*mpMTSpaceBestPatrollerStrat)(block,k+mLastT*(column-1));
      }
      else if(column>block) //else if they are all zero i.e no strategy
      {
       std::cout<<std::setw(block)<<" ";
       k=mLastT; //exit loop
      }
      else
      {

      }
      k=k+1;
     }
     std::cout<<" ";
     column=column+1;
    }
    column=1;
    std::cout<<"\n";

   block=block+1;
  }
}
void MixedPolicyEvaluation::SaveMTSpacePolicyEvaluation
(std::string FileName/*="MTSpacePolicyEvaluation.dat"*/)
{
 //Open file
 std::ofstream outfile;
 outfile.open(FileName);

 //Set outfile style
 outfile<<std::fixed<<std::setprecision(0);

 //Information about the File
 outfile<<"MTSpace Best Patroller Strategy Numbers \n"
 <<"Type:4 Matrix of Size"<<(mLastT-mStartT+1)<<"x"<<(mLastM-mStartM+1)<<"\n"
 <<"In the Order Value, Key Probability, Strategy Number,Strategy and broken up by a -- \n"
 <<"Value Starts at Row="<<"\n"
 <<"Key Probability Starts at Row="<<" and ends at Row="<<"\n"
 <<"Strategy Number Starts at Row="<<" and ends at Row="<<"\n"
 <<"Strategy at Row="<<" and ends at Row="<<"\n"
 <<"Game Time Range:"<<mStartT<<"-"<<mLastT<<" and ends at Row="<<"\n"
 <<"Attack Time:"<<mStartM<<"-"<<mLastM<<"\n";

 //Printing Matrices
 //Printing Value

 //Printing Key Probability

 //Printing Strategy Number

 //Printing Strategy


}
