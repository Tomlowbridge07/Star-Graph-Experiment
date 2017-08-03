#ifndef MIXEDPATROLLERHEADERDEF
#define MIXEDPATROLLERHEADERDEF

#include "AbstractPatroller.hpp"

class MixedPatroller
{
 public:
 //Standard Constructor
  MixedPatroller(AbstractPatroller& aPatrollerSystem,
                Vector MixedPatrollerStrat , Vector MixedAttackerStrat );

 //Alternative Constructor
 MixedPatroller(AbstractPatroller& aPatrollerSystem);

 //Destructor
 ~MixedPatroller();

//Setters and Getters
void SetPatrollerSystem(AbstractPatroller& aPatrollerSystem);
void SetMixedPatrollerStrategy(Vector MixedPatrollerStrat);
void SetMixedAttackerStrategy(Vector MixedAttackerStrat);
AbstractPatroller* GetPatrollerSystem();
Vector GetMixedPatrollerStratergy();
Vector GetMixedAttackerStrategy();
Vector GetPatrollerAgainstPureEvaluation();
Vector GetAttackerAgainstPureEvaluation();

//Evaluating strategies
void EvaluatePatrollerAgainstPureAttacker();
void EvaluateAttackerAgainstPurePatroller();


 protected:

 AbstractPatroller* mpPatrollerSystem;

 Vector* mpMixedPatrollerStrat; //Stores the mixed strategy for the patroller
 Vector* mpMixedAttackerStrat; //Stores the mixed strategy for the attacker

 Vector* mpPatrollerAgainstPureAttacker; //Store the mixed strategy against all pure attacks
 Vector* mpAttackerAgainstPurePatroller; //Stores the mixed strategy against all pure patrols




 private:


};

#endif //MIXEDPATROLLERHEADERDEF
