#include "MixedPatroller.hpp"
#include<assert.h>

//Standard Constructor
MixedPatroller::MixedPatroller(AbstractPatroller& aPatrollerSystem,
                Vector MixedPatrollerStrat , Vector MixedAttackerStrat )
{
 //Set pointer to Patroller class
 mpPatrollerSystem=&aPatrollerSystem;

  //Set Mixed strategies to zero
 mpMixedPatrollerStrat=new Vector(MixedPatrollerStrat);
 mpMixedAttackerStrat=new Vector(MixedAttackerStrat);

 //Set Evaluation vectors to empty/Null, to be used later if evaluation is asked for
 mpPatrollerAgainstPureAttacker=new Vector(1);
 mpAttackerAgainstPurePatroller=new Vector(1);

}

//Alternative Constructor
MixedPatroller::MixedPatroller(AbstractPatroller& aPatrollerSystem)
{
 //Set pointer to Patroller class
 mpPatrollerSystem=&aPatrollerSystem;

  //Set Mixed strategies to zero
 mpMixedPatrollerStrat=new Vector(mpPatrollerSystem->GetNumPurePatrolOptions());
 mpMixedAttackerStrat=new Vector(mpPatrollerSystem->GetNumPureAttackOptions());

 //Set Evaluation vectors to empty/Null, to be used later if evaluation is asked for
 mpPatrollerAgainstPureAttacker=new Vector(1);
 mpAttackerAgainstPurePatroller=new Vector(1);

}

MixedPatroller::~MixedPatroller()
{
delete mpMixedPatrollerStrat;
delete mpMixedAttackerStrat;
delete mpPatrollerAgainstPureAttacker;
delete mpAttackerAgainstPurePatroller;
}


//Setters and Getters
void MixedPatroller::SetPatrollerSystem(AbstractPatroller& aPatrollerSystem)
{
 mpPatrollerSystem=&aPatrollerSystem;
}
void MixedPatroller::SetMixedPatrollerStrategy(Vector MixedPatrollerStrat)
{
 delete mpMixedPatrollerStrat;
 mpMixedPatrollerStrat=new Vector(MixedPatrollerStrat);
}
void MixedPatroller::SetMixedAttackerStrategy(Vector MixedAttackerStrat)
{
 delete mpMixedAttackerStrat;
 mpMixedAttackerStrat=new Vector(MixedAttackerStrat);
}
AbstractPatroller* MixedPatroller::GetPatrollerSystem()
{
 return (mpPatrollerSystem);
}
Vector MixedPatroller::GetMixedPatrollerStratergy()
{
 return (*mpMixedPatrollerStrat);
}
Vector MixedPatroller::GetMixedAttackerStrategy()
{
 return (*mpMixedAttackerStrat);
}
Vector MixedPatroller::GetPatrollerAgainstPureEvaluation()
{
 return (*mpPatrollerAgainstPureAttacker);
}
Vector MixedPatroller::GetAttackerAgainstPureEvaluation()
{
 return (*mpAttackerAgainstPurePatroller);
}



//Evaluating strategies
//Evaluate the mixed patroller strategy against all pure attacker strategies
void MixedPatroller::EvaluatePatrollerAgainstPureAttacker()
{
 delete mpPatrollerAgainstPureAttacker;
 Vector Evaluation(mpPatrollerSystem->GetNumPureAttackOptions());
 //Playing against a pure
 int i=1;
 int j=1;
 while(i<=mpPatrollerSystem->GetNumPureAttackOptions())
 {
  j=1;
  while(j<=mpPatrollerSystem->GetNumPurePatrolOptions())
  {
   //Play the mixed strategy against each pure strategy. Claiming the pure payoff
   //with the probability that the strategy was played
   Evaluation(i)=Evaluation(i)+((*mpMixedPatrollerStrat)(j))*((mpPatrollerSystem->GetPureWinMatrix())(j,i));
   j=j+1;
  }
  i=i+1;
 }
 mpPatrollerAgainstPureAttacker=new Vector(Evaluation);
}

//Evaluates the mixed attacker strategy against all pure patroller strategies.
//Stores a vector of how well the attacker does against each pure strategy.
void MixedPatroller::EvaluateAttackerAgainstPurePatroller()
{
 delete mpAttackerAgainstPurePatroller;
 Vector Evaluation(mpPatrollerSystem->GetNumPurePatrolOptions());
 //Playing against a pure
 int i=1;
 int j=1;
 IntMatrix Win(mpPatrollerSystem->GetPureWinMatrix());
 while(i<=mpPatrollerSystem->GetNumPurePatrolOptions())
 {
  j=1;
  //std::flush(std::cout<<"i"<<i<<"\n");
  while(j<=mpPatrollerSystem->GetNumPureAttackOptions())
  {
   //std::flush(std::cout<<"j"<<j<<"\n");
   //Play the mixed strategy against each pure strategy. Claiming the pure payoff
   //with the probability that the strategy was played
   Evaluation(i)=Evaluation(i)+((*mpMixedAttackerStrat)(j))*(Win(i,j));
   j=j+1;
  }
  i=i+1;
 }
 mpAttackerAgainstPurePatroller=new Vector(Evaluation);
}







