#ifndef BATCHTIMEMIXEDPOLICYEVALUATIONHEADERDEF
#define BATCHTIMEMIXEDPOLICYEVALUATIONHEADERDEF

#include "BatchMixedPolicyEvaluation.hpp"
/*
This class is currently designed to use the PWPatrooler for the star graph to
select only 2 types of time attack patterns.

It tests all time positions for the best (i.e minimal) best weight evaluation.

*/
class BatchTimeMixedPolicyEvaluation
{
 public:

  //Standard constructor
  BatchTimeMixedPolicyEvaluation
  (BatchMixedPolicyEvaluation &aBatch, int NumTypes=2);

  //Deconstructor
  ~BatchTimeMixedPolicyEvaluation();

  //Setters and Getters
  void SetBatchPolicyEvaluation(BatchMixedPolicyEvaluation &aBatch);
  void SetNumTypes(int NumTypes);
  BatchMixedPolicyEvaluation* GetMixedPolicyEvaluation();
  int GetNumTimeChoices();
  IntVector GetAttackingTimePos();

  //Batch Evaluation for Extended Star PW
  void EvaluateExtendedStarBatchTimeTestPW(int n,int k);

  //Batch Evaluation for Extended Star (for use with normal)
  void EvaluateExtendedStarBatchTimeTest(int n,int k);

 protected:

  //Pointer to Batch weight process
  BatchMixedPolicyEvaluation* mpBatchPolicyEvaluation;

  //Number of types of nodes (to allow variety on number of attacks)
  int mNumTypes;

  //Number of start times for attack (stored for ease of use)
  int mNumStartTimes;

  //Amount of time choices to check
  int mNumTimeChoices;

  //Vector stores 1 if placing an attack there and 0 if not
  IntVector* mpAttackingTimePos;

  //Vectors stores the best choice of weight for that particular position
  //of time attacks

  //Store the evaluation of the time positions choice
  Vector* mpTimePosEvaluation;

  //Stores the Best choice of weight for that choice of time positions
  Vector* mpBestTimePosWeight;

  //Stores the Best Patroller strategy number for that choice of time position
  //and the choice of the best weight
  IntVector* mpBestTimePosPatrollerStratNum;

  //Stores the Best Patroller strategy for that choice of time position
  // and the choice of the best weight
  IntMatrix* mpBestTimePosPatrollerStrat;

  //Storing All best patroller
  //Rows for each of the evaluation number and number of cols is the number of
  //evaluations
  IntMatrix* mpAllBestTimePatrollerStratNum;

  //Layer Matrices store all the different strategies for a particular evaluation
  Int3DMatrix* mpAllBestTimePatrollerStrat;

  //Conversion of number to binary vector
  void ConvToBinary(int number,IntVector* pStorageVector,int StartEntry=1);

 private:


};


#endif // BATCHTIMEMIXEDPOLICYEVALUATIONHEADERDEF
