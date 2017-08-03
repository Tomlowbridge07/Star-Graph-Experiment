#ifndef SPECIALGRAPHGENERATORHEADERDEF
#define SPECIALGRAPHGENERATORHEADERDEF

#include "IntVector.hpp"
#include "IntMatrix.hpp"

class SpecialGraphGenerator
{
 public:

 //Standard Constructor
 SpecialGraphGenerator();

 //Destructor
 ~SpecialGraphGenerator();

 //Line Graph Constructor
 void GenerateLine(int n);

 //Star Graph Constructor
 void GenerateStar(int n);

 //Extended Star Graph Constructor
 void GenerateExtendedStar(int n, int k);


 //General (Extended) Star Graph
 void GenerateGeneralStar(int n, IntVector k);


 //Setters and Getters
 IntMatrix GetAdjacenyMatrix();

 protected:

 IntMatrix* mpAdjacencyMatrix;

 private:

};


#endif // SPECIALGRAPHGENERATORHEADERDEF
