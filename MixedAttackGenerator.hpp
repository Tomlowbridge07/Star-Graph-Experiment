#ifndef MIXEDATTACKGENERATORHEADERDEF
#define MIXEDATTACKGENERATORHEADERDEF

#include "AbstractPatroller.hpp"

class MixedAttackGenerator
{
 public:

 //Standard Constructor
 MixedAttackGenerator(AbstractPatroller& aPatrollerSystem);

 //Destructor
 ~MixedAttackGenerator();

 //Setters and Getters
 void SetPatrollerSystem(AbstractPatroller& aPatrollerSystem);
 AbstractPatroller* GetPatrollerSystem();
 Vector GetGeneratedAttackVector();
 Matrix GetGeneratedAttackMatrix();

 /*Methods to internally set Generated Attack- Designed for use with normal
 generation of attacks*/
 //Uniform
 void GenerateUniformAttack();
 //Line (under diametric attack)
 void GenerateLineAttack(int n);
 //Line (under timed attack)
 void GenerateTimedLineAttack(int n);
 //Line overall (i.e timed attacked when possible otherwise normal diametric)
 void GenerateOverallLineAttack(int n);
 //Extended Star (under weighted attack)
 void GenerateExtendedStarAttack(int n,int k);
 //Extended Star (under weighted timed attack)
 void GenerateTimedExtendedStarAttack(int n,int k);
 //Star overall (i.e timed attacked when possible otherwise normal diametric)
 void GenerateOverallExtendedStarAttack(int n,int k);

 /*
 Methods to internally set Generated Attack- Designed
 for use with Path Wait Patroller generation of attacks
 */
 //Uniform
 void GenerateUniformAttackPW();
 //Line (under diametric attack)
 void GenerateLineAttackPW(int n);
 //Line (under timed attack)
 void GenerateTimedLineAttackPW(int n);
 //Line overall (i.e timed attacked when possible otherwise normal diametric)
 void GenerateOverallLineAttackPW(int n);
 //Extended Star (under weighted attack)
 void GenerateExtendedStarAttackPW(int n,int k);
 //Extended Star (under weighted timed attack)
 void GenerateTimedExtendedStarAttackPW(int n,int k);
 //Star overall (i.e timed attacked when possible otherwise normal diametric)
 void GenerateOverallExtendedStarAttackPW(int n,int k);

 /*
 Methods to set attack patterns depending on a step parameter- Designed for use
 with the path wait patroller
 */
 //Extended Star time variables
 void GenerateExtendedStarTest1PW(int n,int k,double weight);
 void GenerateExtendedStarTest2PW(int n,int k,double weight);
 void GenerateExtendedStarTest3PW(int n,int k,double weight);
 void GenerateExtendedStarTest4PW(int n,int k,double weight);
 void GenerateExtendedStarTest5PW(int n,int k,double weight);

 //Infromed from time position test
 void GenerateExtendedStarTestOddPW(int n,int k);
 void GenerateExtendedStarTestEvenPW(int n,int k);
 void GenerateExtendedStarTestOverallPW(int n, int k);

 //Informed from time position test extended to a more
 //general extended star graph
 void GenerateGeneralExtendedStarTestPW(int n, IntVector VectorK);

 //For use with the batch time posistion testing
 void GenerateExtendedStarTestTimePW(int n,int k,double weight,
                                     IntVector TimesToAttack);

 //For use with the batch time posistion testing
 //Note. This does not use PW, so it is a bigger function
 void GenerateExtendedStarTestTime(int n,int k,
                               Vector Weights
                               ,IntVector TimesToAttack);

 protected:

 //Pointer to Pure Patrolling System
 AbstractPatroller* mpPatrollerSystem;

 //Single Attack Vector
 Vector* mpGeneratedAttackVector;

 //Batch Attack Matrix
 Matrix* mpGeneratedAttackMatrix;

 private:
};




#endif // MIXEDATTACKGENERATORHEADERDEF
