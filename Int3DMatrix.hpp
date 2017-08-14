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

 //Setting 2d Matrices
 void SetRowMatrix(int Row, IntMatrix mat);
 void SetColMatrix(int Col, IntMatrix mat);
 void SetLayerMatrix(int Layer, IntMatrix mat);

 //Setting Vectors
 void SetRowVector(int Row,int Layer, IntVector Vec);
 void SetColVector(int Col, int Layer, IntVector Vec);
 void SetLayerVector(int Row, int Col, IntVector Vec);

 //Returns a Block of the matrix
 Int3DMatrix GetBlock(int TopLeftI,int TopLeftJ,int TopLeftK,
                      int rows, int cols, int layers);

 //Set Block
 void SetBlock(int TopLeftI, int TopLeftJ, int TopLeftK, Int3DMatrix mat);

 //Fill
 void Fill(const int FillValue);



 //Extending
 void ExtendRow(const int ExtendBy);
 void ExtendCol(const int ExtendBy);
 void ExtendLayer(const int ExtendBy);

 //Adding
 void AddRow(const int Row, bool below=true);
 void AddCol(const int Col, bool right=true);
 void AddLayer(const int Layer, bool backwards=true);

 //Deleting
 void DeleteRow(const int Row);
 void DeleteCol(const int Col);
 void DeleteLayer(const int Layer);

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
