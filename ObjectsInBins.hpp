#ifndef OBJECTSINBINSHEADERDEF
#define OBJECTSINBINSHEADERDEF

#include "IntMatrix.hpp"

class ObjectsInBins
{
 public:

 //Constructor
 ObjectsInBins(int NumObjects, int NumBins);

 //Destructor
 ~ObjectsInBins();

 //Getters and Setters
 int GetNumObjects();
 int GetNumBins();
 int GetNumSeperators();
 int GetNumSpaces();
 int GetNumCombinations();
 IntMatrix GetSeperatorMatrix();
 IntMatrix GetNumberInBins();

 //Seperator matrix computer
 void ComputeSeperatorMat();

 //Number in bin computer
 void  ComputeNumInBins();

 protected:

 int mNumObjects;
 int mNumBins;
 int mNumSeperators;
 int mNumSpaces;
 int mNumCombinations;

 //This tells us at what location the seperators are placed
 IntMatrix* mpSeperatorMat;

 //This is used to see what we can pick from
 IntMatrix* mpOptionsLeft;

 //This tells us how many are in each bin
 IntMatrix* mpNumberInBins;



 private:
};

#endif // OBJECTSINBINSHEADERDEF
