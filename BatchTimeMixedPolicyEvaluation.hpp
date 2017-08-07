#ifndef BATCHTIMEMIXEDPOLICYEVALUATIONHEADERDEF
#define BATCHTIMEMIXEDPOLICYEVALUATIONHEADERDEF

#include "BatchMixedPolicyEvaluation.hpp"

class BatchTimeMixedPolicyEvaluation
{
 public:

  //Standard constructor
  BatchTimeMixedPolicyEvaluation(BatchMixedPolicyEvaluation &aBatch);

  //Deconstructor
  ~BatchTimeMixedPolicyEvaluation();

  //Setters and Getters
  void SetBatchPolicyEvaluation(BatchMixedPolicyEvaluation &aBatch);
  BatchMixedPolicyEvaluation* GetMixedPolicyEvaluation();
  int GetNumTimeChoices();
  IntVector GetAttackingTimePos();

  //Batch Evaluation
  void EvaluateBatchTimeTest(int n,int k);

 protected:

  //Pointer to Batch weight process
  BatchMixedPolicyEvaluation* mpBatchPolicyEvaluation;

  //Number of start times for attack (stored for ease of use)
  int mNumStartTimes;

  //Amount of time choices to check
  int mNumTimeChoices;

  //Vector stores 1 if placing an attack there and 0 if not
  IntVector* mpAttackingTimePos;

  //Vectors stores the best choice of weight for that particular position
  //of time attacks
  Vector* mpTimePosEvaluation; //Store the evaluation of the time positions choice
  Vector* mpBestTimePosWeight; //
  IntVector* mpBestTimePosPatrollerStratNum;
  IntMatrix* mpBestTimePosPatrollerStrat;

  //Conversion of number to binary vector
  void ConvToBinary(int number,IntVector* pStorageVector,int StartEntry=1);

 private:


};


#endif // BATCHTIMEMIXEDPOLICYEVALUATIONHEADERDEF
