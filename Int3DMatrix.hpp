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

 //Getters and Setters
 int GetNumberRows() const;
 int GetNumberCols() const;
 int GetNumberLayers() const;

 // Overloading round bracket operator
 int& operator()(int i, int j, int k);

 //Overwritten << operator
 friend std::ostream& operator<<(std::ostream& output,const Int3DMatrix& m);

 // Read entry
 int Read(int i, int j, int k);

 //Overloaded assignment operator
 Int3DMatrix& operator=(const Int3DMatrix& otherMatrix);

 // Unary +
 Int3DMatrix operator+() const;

 // Unary -
 Int3DMatrix operator-() const;

 // Binary +
 Int3DMatrix operator+(const Int3DMatrix& m1) const;

 // Binary -
 Int3DMatrix operator-(const Int3DMatrix& m1) const;

 // Scalar multiplication
 Int3DMatrix operator*(int a) const;

 //Retriving 2d Matrix
 IntMatrix GetRowMatrix(int Row) const;
 IntMatrix GetColMatrix(int Col) const;
 IntMatrix GetLayerMatrix(int Layer) const;

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
