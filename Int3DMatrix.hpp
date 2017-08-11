#ifndef INT3DMATRIXHEADERDEF
#define INT3DMATRIXHEADERDEF

#include "IntMatrix.hpp"

class Int3DMatrix
{
 public:

 //Standard Constructor
 Int3DMatrix(int NumRows, int NumCols, int NumLayers);

 //Copy Constructor
 Int3DMatrix(const Int3DMatrix& other3DMatrix);

 //Desctructor
 ~Int3DMatrix();


 protected:

 private:

 //Data
 int*** mData;

 //Number of Rows, Cols and Layers
 int mNumRows;
 int mNumCols;
 int mNumLayers;

};



#endif // INT3DMATRIXHEADERDEF
