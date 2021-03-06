#include "MixedAttackGenerator.hpp"

#include "UsefulFunctions.hpp"


#include<cassert>

//Standard Constructor
MixedAttackGenerator::MixedAttackGenerator(AbstractPatroller& aPatrollerSystem)
{
 //Set Pointer to Patrolling System
 mpPatrollerSystem=&aPatrollerSystem;

 //Set Generated Attacks to empty/Null
 mpGeneratedAttackVector=
 new Vector(mpPatrollerSystem->GetNumPureAttackOptions());
 mpGeneratedAttackMatrix=
 new Matrix(1,mpPatrollerSystem->GetNumPureAttackOptions());
}

//Destructor
MixedAttackGenerator::~MixedAttackGenerator()
{
 delete mpGeneratedAttackVector;
 delete mpGeneratedAttackMatrix;
}

//Setters and Getters
void MixedAttackGenerator::
    SetPatrollerSystem(AbstractPatroller& aPatrollerSystem)
{
 mpPatrollerSystem=&aPatrollerSystem;

 //Set Generated Attacks to empty/Null
 delete mpGeneratedAttackVector;
 delete mpGeneratedAttackVector;
 mpGeneratedAttackVector=
 new Vector(mpPatrollerSystem->GetNumPureAttackOptions());
 mpGeneratedAttackMatrix=
 new Matrix(1,mpPatrollerSystem->GetNumPureAttackOptions());
}
AbstractPatroller* MixedAttackGenerator::GetPatrollerSystem()
{
 return (mpPatrollerSystem);
}
Vector MixedAttackGenerator::GetGeneratedAttackVector()
{
 return (*mpGeneratedAttackVector);
}
Matrix MixedAttackGenerator::GetGeneratedAttackMatrix()
{
 return (*mpGeneratedAttackMatrix);
}

/*Methods to internally set Generated Attack- Designed for use with normal
generation of attacks*/

//Uniform
//This generated attack attacks at all times an all nodes (under the current
//patroller system) with equal weight
void MixedAttackGenerator::GenerateUniformAttack()
{
 int i=1;
 while(i<=mpPatrollerSystem->GetNumPureAttackOptions())
 {
  (*mpGeneratedAttackVector)(i)=
  (double)1/(double)(mpPatrollerSystem->GetNumPureAttackOptions());
  i=i+1;
 }
}

//Line (under diametric attack)
void MixedAttackGenerator::GenerateLineAttack(int n)
{
 if(mpPatrollerSystem->GetAttackTime()>=3) //If the Game has been reduced
 {
  int block=1;
  int i=1;
  int blocksize=
  (mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block <= n-2)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)1/(double)(2*blocksize);
     i=i+1;
    }
   }
   else if(block==n-2)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)1/(double)(2*blocksize);
     i=i+1;
    }
   }
   else
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     i=i+1;
    }
   }
   block=block+1;
  }
 }
 else //If the game has not been reduced
 {
  int block=1;
  int i=1;
  int blocksize=
  (mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block <= n)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)1/(double)(2*blocksize);
     i=i+1;
    }
   }
   else if(block==n)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)1/(double)(2*blocksize);
     i=i+1;
    }
   }
   else
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     i=i+1;
    }
   }
   block=block+1;
  }
 }
}

//Line (under timed attack)
//The timed attack only attakcs during the first diameter slots
void MixedAttackGenerator::GenerateTimedLineAttack(int n)
{
 if(mpPatrollerSystem->GetAttackTime()>=3)
 {
  int block=1;
  int i=1;
  int blocksize=
  (mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block <= n-2)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=n-1)
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      (double)1/(double)(2*(n-1));
     }
     else
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     }
     i=i+1;
    }
   }
   else if(block==n-2)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=n-1)
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      (double)1/(double)(2*(n-1));
     }
     else
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     }
     i=i+1;
    }
   }
   else
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     i=i+1;
    }
   }
   block=block+1;
  }
 }
 else
 {
  int block=1;
  int i=1;
  int blocksize=
  (mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block <= n)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=n-1)
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      (double)1/(double)(2*(n-1));
     }
     else
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     }
     i=i+1;
    }
   }
   else if(block==n)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=n-1)
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      (double)1/(double)(2*(n-1));
     }
     else
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     }
     i=i+1;
    }
   }
   else
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     i=i+1;
    }
   }
   block=block+1;
  }
 }
}
//This combines the choice of the timed attack when possible and the uniform
//when not possible
void MixedAttackGenerator::GenerateOverallLineAttack(int n)
{
 if(mpPatrollerSystem->GetGameTime()>= mpPatrollerSystem->GetAttackTime()+n-1)
 {
  GenerateTimedLineAttack(n);
 }
 else
 {
  GenerateLineAttack(n);
 }
}
//Extended Star (under weighted attack)
void MixedAttackGenerator::GenerateExtendedStarAttack(int n,int k)
{
 if(mpPatrollerSystem->GetGameTime()>=3)
 {
  int block=1;
  int i=1;
  int blocksize=
  (mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block<=n+k-2)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)(k+1)/(double)((n+k)*blocksize);
     i=i+1;
    }
   }
   else if(block>=k+1)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)1/(double)((n+k)*blocksize);
     i=i+1;
    }
   }
   else
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     i=i+1;
    }
   }
   block=block+1;
  }
 }
 else
 {
  int block=1;
  int i=1;
  int blocksize=
  (mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block<=n+k)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)(k+1)/(double)((n+k)*blocksize);
     i=i+1;
    }
   }
   else if(block>=k+3)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)1/(double)((n+k)*blocksize);
     i=i+1;
    }
   }
   else
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     i=i+1;
    }
   }
   block=block+1;
  }
 }
}
//Extended Star (under weighted timed attack)
void MixedAttackGenerator::GenerateTimedExtendedStarAttack(int n,int k)
{
 if(mpPatrollerSystem->GetGameTime()>=3)
 {
  int block=1;
  int i=1;
  int blocksize=
  (mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block<=n+k-2)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=2*(k+1))
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      (double)(k+1)/(double)((n+k)*blocksize);
     }
     else
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     }
     i=i+1;
    }
   }
   else if(block>=k+1)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=2*(k+1))
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      (double)1/(double)((n+k)*blocksize);
     }
     else
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     }
     i=i+1;
    }
   }
   else
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     i=i+1;
    }
   }
   block=block+1;
  }
 }
 else
 {
  int block=1;
  int i=1;
  int blocksize=
  (mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block<=n+k)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=2*(k+1))
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      (double)(k+1)/(double)((n+k)*blocksize);
     }
     else
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     }
     i=i+1;
    }
   }
   else if(block>=k+3)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=2*(k+1))
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      (double)1/(double)((n+k)*blocksize);
     }
     else
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     }
     i=i+1;
    }
   }
   else
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     i=i+1;
    }
   }
   block=block+1;
  }
 }
}
void MixedAttackGenerator::GenerateOverallExtendedStarAttack(int n,int k)
{
 if(mpPatrollerSystem->GetGameTime()>=
    mpPatrollerSystem->GetAttackTime()+(2*(k+1)))
 {
  GenerateTimedExtendedStarAttack(n,k);
 }
 else
 {
  GenerateExtendedStarAttack(n,k);
 }
}

/*Methods to internally set Generated Attack- Designed for use with
Path Wait Patroller generation of attacks*/
//Uniform- Same as before
void MixedAttackGenerator::GenerateUniformAttackPW()
{
 int i=1;
 while(i<=mpPatrollerSystem->GetNumPureAttackOptions())
 {
  (*mpGeneratedAttackVector)(i)=
  (double)1/(double)(mpPatrollerSystem->GetNumPureAttackOptions());
  i=i+1;
 }
}
//Line (under diametric attack)
void MixedAttackGenerator::GenerateLineAttackPW(int n)
{
 //Note the line attack is uniform on these selected points
 GenerateUniformAttackPW();
}
//Line (under timed attack)
void MixedAttackGenerator::GenerateTimedLineAttackPW(int n)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 while(block <= 2)
 {
  i=1;
  while(i<=blocksize)
  {
   if(i<=n-1)
   {
    (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
    (double)1/(double)(2*(n-1));
   }
   else
   {
    (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
   }
   i=i+1;
  }
  block=block+1;
 }
}
void MixedAttackGenerator::GenerateOverallLineAttackPW(int n)
{
 if(mpPatrollerSystem->GetGameTime()>= mpPatrollerSystem->GetAttackTime()+n-1)
 {
  GenerateTimedLineAttackPW(n);
 }
 else
 {
  GenerateLineAttackPW(n);
 }
}


//Extended Star (under weighted attack)
void MixedAttackGenerator::GenerateExtendedStarAttackPW(int n,int k)
{
 GenerateUniformAttackPW(); //Same as uniform attack
}
//Extended Star (under weighted timed attack)
void MixedAttackGenerator::GenerateTimedExtendedStarAttackPW(int n,int k)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 int timechoice1=6;
 int timechoice2=2;
 while(block <= n)
 {
  if(block==1)
  {
   i=1;
   while(i<=blocksize)
   {
    if(i<=timechoice1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)(k+1)/(double)((n+k)*timechoice1);
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else
  {
   int i=1;
   while(i<=blocksize)
   {
    if(i==1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)(1)/(double)((n+k)*timechoice2);
    }
    else if(i==4)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     (double)(1)/(double)((n+k)*timechoice2);
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}

//Overall Attack on Extended Star Graph
/*
Assuming to use Guessed Time Appropiate Strategy

Note. THIS IS REALLY FOR TEST PURPOSES AND DID NOT GIVE THE WANTED VALUE
*/
void MixedAttackGenerator::GenerateOverallExtendedStarAttackPW(int n,int k)
{
 if(mpPatrollerSystem->GetGameTime()>=
    mpPatrollerSystem->GetAttackTime()+2*(k+1))
 {
  GenerateTimedExtendedStarAttackPW(n,k);
 }
 else
 {
  GenerateExtendedStarAttackPW(n,k);
 }
}


//Testing Attacking Strategies
/*
The following 5 methods are variations on attacking time positions and weights
used as a test to attempt to find the correct attacking strategy

NOTE. THESE ARE NOT REALLY INTENDED FOR USE
*/
void MixedAttackGenerator::GenerateExtendedStarTest1PW(int n,
                                                       int k,double weight)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 int timechoice1=3;
 int timechoice2=1;
 while(block <= n)
 {
  if(block==1)
  {
   i=1;
   while(i<=blocksize)
   {
    if(i<=timechoice1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(timechoice1)) * weight;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else
  {
   i=1;
   while(i<=blocksize)
   {
    if(i<=timechoice2)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(timechoice2)) * ((double)(1-weight)/(double)(n-1));
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}

void MixedAttackGenerator::GenerateExtendedStarTest2PW(int n,
                                                       int k,double weight)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 int timechoice1=6;
 while(block <= n)
 {
  if(block==1)
  {
   i=1;
   int numtimesofattack=4;
   int j=1;
   while(i<=blocksize)
   {
    if(i % 3 ==1 && j<=numtimesofattack)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(numtimesofattack)) * weight;
     j=j+1;
    }
    else if(i % 3 ==2 && j<=numtimesofattack)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(numtimesofattack)) * weight;
     j=j+1;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else
  {
   i=1;
   int numtimesofattack=3;
   int j=1;
   while(i<=blocksize)
   {
    if(i % 2 ==1 && j<=numtimesofattack)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(numtimesofattack)) *
     ((double)(1-weight)/(double)(n-1));
     j=j+1;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 //assert(mpGeneratedAttackVector->Sum()==1);
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}

void MixedAttackGenerator::GenerateExtendedStarTest3PW(int n,
                                                       int k,double weight)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 int timechoice1=6;
 while(block <= n)
 {
  if(block==1)
  {
   i=1;
   while(i<=blocksize)
   {
    if(i<=timechoice1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(timechoice1)) * weight;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else
  {
   i=1;
   while(i<=blocksize)
   {
    if(i==1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(2)) * ((double)(1-weight)/(double)(n-1));
    }
    else if(i==blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(2)) * ((double)(1-weight)/(double)(n-1));
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}

void MixedAttackGenerator::GenerateExtendedStarTest4PW(int n,
                                                       int k,double weight)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 int timechoice1=6;
 while(block <= n)
 {
  if(block==1)
  {
   i=1;
   while(i<=blocksize)
   {
    if(i<=timechoice1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(timechoice1)) * weight;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else
  {
   i=1;
   while(i<=blocksize)
   {
    if(i==2)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    else if(i==blocksize-1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(blocksize-2)) * ((double)(1-weight)/(double)(n-1));
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}

void MixedAttackGenerator::GenerateExtendedStarTest5PW(int n,
                                                       int k,double weight)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 int timechoice1=6;
 while(block <= n)
 {
  if(block==1)
  {
   i=1;
   while(i<=blocksize)
   {
    if(i<=timechoice1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(timechoice1)) * weight;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else
  {
   i=1;
   while(i<=blocksize)
   {
    if(i>=4 && i<=blocksize-3)
    {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      ((double)(1)/(double)(blocksize-6)) * ((double)(1-weight)/(double)(n-1));
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}

//Extended Star Graph Test (Odd)
/*
This method generates an attack on S_{n}^{k} using the Odd strategy
*/
void MixedAttackGenerator::GenerateExtendedStarTestOddPW(int n,int k)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 double weight1=(double)(k+1)/(double)(n+k);
 double weight2=(double)(1)/(double)(n+k);
 int timechoice1=2*(k+1);
 int timechoice2=2;
 while(block <= n)
 {
  if(block==1)
  {
   i=1;
   while(i<=blocksize)
   {
    if(i<=timechoice1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(timechoice1)) * weight1;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else
  {
   i=1;
   while(i<=blocksize)
   {
    if(i==k+1 || i==k+2)
    {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      ((double)(1)/(double)(timechoice2)) * weight2;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}

//Extended Star Graph Test (Even)
/*
This method generates an attack on S_{n}^{k} using the Even Strategy

Note. We could use just the Odd Type of attack to produce equally good
results (This is an optional extra when m is odd)
*/
void MixedAttackGenerator::GenerateExtendedStarTestEvenPW(int n,int k)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 double weight1=(double)(k+1)/(double)(n+k);
 double weight2=(double)(1)/(double)(n+k);
 int timechoice1=k+1;
 int timechoice2=1;
 while(block <= n)
 {
  if(block==1)
  {
   i=1;
   while(i<=blocksize)
   {
    if(i<=2*(k+1) && i % 2==1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(timechoice1)) * weight1;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else
  {
   i=1;
   while(i<=blocksize)
   {
    if(i==k+1)
    {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      ((double)(1)/(double)(timechoice2)) * weight2;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}

//Extended Star Graph Test (Overall)
/*
This method generates an attack on S_{n}^{k} using the Odd and Even varied
strategies
*/
void MixedAttackGenerator::GenerateExtendedStarTestOverallPW(int n, int k)
{
 if(mpPatrollerSystem->GetAttackTime() % 2==0) //If even
 {
  GenerateExtendedStarTestEvenPW(n,k);
 }
 else //If odd
 {
  GenerateExtendedStarTestOddPW(n,k);
 }
}

//Informed from time position test
void MixedAttackGenerator::GenerateSymmetricDualStarTestPW(int n,int l)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 double weight=(double)(1)/(double)(2*n);
 int timechoice=2*n+l+1;
 while(block <= 2*n)
 {
  i=1;
   while(i<=blocksize)
   {
    if(i<=timechoice)
    {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      ((double)(1)/(double)(timechoice)) * weight;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
   block=block+1;
  }
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}
//General Extended Star Graph Test
/*
This method generates an attack on S_{n}^{VecK} according to the testing
strategy

Note.This function expects the Vector K to be in size order to allow correct
allignment with the node numbers
*/
void MixedAttackGenerator::GenerateGeneralExtendedStarTestPW(int n,
                           IntVector VectorK)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 int kmax=VectorK.Max();
 int ksum=VectorK.Sum();
 while(block<= n)
 {
  if(block<=VectorK.GetSize()) //if it is a extended arm
  {
    i=1;
    while(i<=blocksize)
    {
     if(i>=(kmax+1-VectorK(block)) && i<=(kmax+2+VectorK(block)))
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      ((double)(1))/(double)(2*(VectorK(block)+1)) *
      ((double)(VectorK(block)+1))/((double)(n+ksum));
     }
     else
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     }
     i=i+1;
    }
  }
  else
  {
    i=1;
    while(i<=blocksize)
    {
     if(i==kmax+1 || i==kmax+2)
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      ((double)(1))/((double)(2*(1))) * ((double)(1))/((double)(n+ksum));
     }
     else
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
     }
     i=i+1;
    }
  }
  block=block+1;
 }
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}

//Time Testing Extended Star
/*
This method generates a mixed attack vector applying:
-Weight to extended external node
-Choosing times according to the binary TimesToAttack vector

These are both meant to be varied by the batch picker
*/
void MixedAttackGenerator::GenerateExtendedStarTestTimePW(int n,int k,
                           double weight,IntVector TimesToAttack)
{
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);
 //Need to know how many attacks are there on each of the nodes
 int extendedcounter=0;
 while(i<=blocksize)
 {
  if(TimesToAttack(i)==1)
  {
   extendedcounter=extendedcounter+1;
  }
  i=i+1;
 }
 i=1;
 int normalcounter=0;
 while(i<=blocksize)
 {
  if(TimesToAttack(blocksize+i)==1)
  {
   normalcounter=normalcounter+1;
  }
  i=i+1;
 }

 //If no attack takes places at an extended node we need to ignore the weight
 // and place only weight 1 on normal
 if(extendedcounter==0)
 {
  weight=0;
 }


 //If no attack takes place at a normal node we nede to ignore the weight
 // and palce only weight 1 on extended
 if(normalcounter==0)
 {
  weight=1;
 }

 //Construct the attack
 i=1;
 int block=1;
 int readcounter=1;
 while(block <= n)
 {
  if(block==1)
  {
   i=1;
   while(i<=blocksize)
   {
    if(TimesToAttack(i)==1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(extendedcounter)) * weight;
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else
  {
   i=1;
   while(i<=blocksize)
   {
    if(TimesToAttack(blocksize+i)==1)
    {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      ((double)(1)/(double)(normalcounter)) *
      ((double)(1-weight)/(double)(n-1));
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 //std::flush(std::cout<<(*mpGeneratedAttackVector));
}

//For use with the batch time posistion testing
void MixedAttackGenerator::
GenerateExtendedStarTestTime(int n,int k,
Vector Weights,IntVector TimesToAttack)
{

 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);

 int numberoftypes=0;
 if(mpPatrollerSystem->GetAttackTime()>=3)
 {
  //removal of penultimate nodes along the line
  numberoftypes=k+1;
 }
 else
 {
  //no removal has occured
  numberoftypes=k+3;
 }


 //Need to know how many attacks are there on each of the nodes
 IntVector NumberofAttacks(numberoftypes); //Assuming k>0

 i=1;
 int j=1;
 while(i<=numberoftypes)
 {
  j=1;
  while(j<=blocksize)
  {
   if(TimesToAttack((i-1)*blocksize+j)==1)
   {
    NumberofAttacks(i)=NumberofAttacks(i)+1;
   }
   j=j+1;
  }
  i=i+1;
 }

 //Check on weights, weights must be made to be zero if its time is not selected
 i=1;
 while(i<=numberoftypes)
 {
  if(NumberofAttacks(i)==0 && Weights(i)!=0) //No attacks here (as no times selected)
  {
   // We form an illegal (but overcosted attacked) which will be ignored
   (*mpGeneratedAttackVector)((i-1)*blocksize+1)=2;
   return; //We return nothing to finish early
  }
  i=i+1;
 }


 //Construct the attack
 i=1;
 int block=1; //There will be n+k+1 blocks (with k+3,k+4,...,n+k+1 being normal type
 int readcounter=1;
 while(block <= n+numberoftypes-2)
 {
  if(block<=numberoftypes-1)
  {
   i=1;
   while(i<=blocksize)
   {
    if(TimesToAttack((block-1)*blocksize+i)==1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(NumberofAttacks(block))) * Weights(block);
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else // I.e in normal external nodes (so only look at final block)
  {
   i=1;
   while(i<=blocksize)
   {
    if(TimesToAttack((numberoftypes-1)*blocksize+i)==1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(NumberofAttacks(numberoftypes)*(n-1)))
     * Weights(numberoftypes);
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 //std::flush(std::cout<<(*mpGeneratedAttackVector));
}

//We place attacks at the times specified and at weights specified on nodes
//1,..,n_1 and n_1+2,...,n_2 (Nodes n_1+1 is the first centre and n_2+1 is the
//second centre)

//As all attacked nodes are of the same type we will
void MixedAttackGenerator::GenerateDualStarTestTimePW
(int n1, int n2,double Weight,IntVector TimesToAttack)
{
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem
                ->GetAttackTime()+1);

 //Need to know how many attacks through time there at the left stars nodes
 // and how many at the right stars nodes
 int leftattackcounter=0;
 while(i<=blocksize)
 {
  if(TimesToAttack(i)==1)
  {
   leftattackcounter=leftattackcounter+1;
  }
  i=i+1;
 }

 i=1;
 int rightattackcounter=0;
 while(i<=blocksize)
 {
  if(TimesToAttack(blocksize+i)==1)
  {
   rightattackcounter=rightattackcounter+1;
  }
  i=i+1;
 }


 //If no attack takes places at an left nodes we need to ignore the weight
 // and place only weight 1 on normal
 if(leftattackcounter==0)
 {
  Weight=0;
 }


 //If no attack takes place at a right nodes we nede to ignore the weight
 // and palce only weight 1 on extended
 if(rightattackcounter==0)
 {
  Weight=1;
 }

 //Construct the attack
 i=1;
 int block=1;
 while(block <= (n1+n2))
 {
  if(block<=n1) //left star nodes
  {
   i=1;
   while(i<=blocksize)
   {
    if(TimesToAttack(i)==1)
    {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
      ((double)(1)/(double)(leftattackcounter)) *
      ((double)(Weight)/(double)(n1));
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  else //Right star nodes
  {
   i=1;
   while(i<=blocksize)
   {
    if(TimesToAttack(blocksize+i)==1)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=
     ((double)(1)/(double)(rightattackcounter)) *
     ((double)(1-Weight)/(double)(n2));
    }
    else
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=0;
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 //std::flush(std::cout<<(*mpGeneratedAttackVector));
}


//Experimental lower line type attack
//TURN OFF REDUCTION WHEN USING THIS ATTACK PATTERN
void MixedAttackGenerator::GenerateLowerExtendedStarAttack(int n, int k)
{
 int i=1;
 int blocksize=mpPatrollerSystem->GetGameTime()-
               mpPatrollerSystem->GetAttackTime()+1;

 //Determine exact attack type used (1,2,3,4)
 int Type=0;
 int m=mpPatrollerSystem->GetAttackTime();
 if(m%2==0)
 {
  if(k-(m/2)%2==0)
  {
   Type=1;
  }
  else
  {
   std::flush(std::cout<<"Type 3 has been selected");
   Type=3;
  }
 }
 else
 {
  if(k-((m+1)/2)%2==0)
  {
   Type=2;
  }
  else
  {
   Type=4;
  }
 }

 //Now depending on type we construct the attack
 if(Type==1)
 {

 }

 else if(Type==2)
 {

 }

 else if(Type==3)
 {
 std::cout<<"this is run";
  i=1;
  int block=1;
  int TotalNumAttacks=4*n+2*k+m-2; //For even stratgies(type 1,3) we use double weight
  double Weight=1/((double)TotalNumAttacks);
  int FirstTwolineNode=(m/2)+2;

  while(block<=n+k+1)
  {
   if(block==1) //On the end place m attacks
   {
    i=1;
    while(i<=m)
    {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=2*Weight;
      i=i+1;
    }
   }
   else if(block>=FirstTwolineNode && block<=k+1 && block-(FirstTwolineNode)%2==0) //Place 2 centralised attacks at every other node
   {
    (*mpGeneratedAttackVector)((block-1)*blocksize+(m/2))=2*Weight;
    (*mpGeneratedAttackVector)((block-1)*blocksize+(m/2)+1)=2*Weight;
   }
   else if(block>=k+3) //On star part make 2 centralised attacks on each
   {
    (*mpGeneratedAttackVector)((block-1)*blocksize+(m/2))=2*Weight;
    (*mpGeneratedAttackVector)((block-1)*blocksize+(m/2)+1)=2*Weight;
   }
   block=block+1;
  }
 //std::flush(std::cout<<(*mpGeneratedAttackVector));
 }

 else if(Type==4)
 {

 }
}












