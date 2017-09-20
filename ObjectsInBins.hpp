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
 IntMatrix GetSeperatorMatrix();

 //Seperator matrix computer
 void ComputeSeperatorMat();

 protected:

 int mNumObjects;
 int mNumBins;
 int mNumSeperators;
 int mNumSpaces;
 int mNumCombinations;

 //This tells us at what location the seperators are placed
 IntMatrix* mpSeperatorMat;

 IntMatrix* mpOptionsLeft;


 IntMatrix* mpNumberInBins;



 private:
};

#endif // OBJECTSINBINSHEADERDEF
