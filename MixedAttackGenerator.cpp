#include "MixedAttackGenerator.hpp"

#include "UsefulFunctions.hpp"


#include<cassert>

//Standard Constructor
MixedAttackGenerator::MixedAttackGenerator(AbstractPatroller& aPatrollerSystem)
{
 //Set Pointer to Patrolling System
 mpPatrollerSystem=&aPatrollerSystem;

 //Set Generated Attacks to empty/Null
 mpGeneratedAttackVector=new Vector(mpPatrollerSystem->GetNumPureAttackOptions());
 mpGeneratedAttackMatrix=new Matrix(1,mpPatrollerSystem->GetNumPureAttackOptions());
}

//Destructor
MixedAttackGenerator::~MixedAttackGenerator()
{
 delete mpGeneratedAttackVector;
 delete mpGeneratedAttackMatrix;
}

//Setters and Getters
void MixedAttackGenerator::SetPatrollerSystem(AbstractPatroller& aPatrollerSystem)
{
 mpPatrollerSystem=&aPatrollerSystem;

 //Set Generated Attacks to empty/Null
 delete mpGeneratedAttackVector;
 delete mpGeneratedAttackVector;
 mpGeneratedAttackVector=new Vector(mpPatrollerSystem->GetNumPureAttackOptions());
 mpGeneratedAttackMatrix=new Matrix(1,mpPatrollerSystem->GetNumPureAttackOptions());
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
void MixedAttackGenerator::GenerateUniformAttack()
{
 int i=1;
 while(i<=mpPatrollerSystem->GetNumPureAttackOptions())
 {
  (*mpGeneratedAttackVector)(i)=(double)1/(double)(mpPatrollerSystem->GetNumPureAttackOptions());
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
  int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block <= n-2)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)(2*blocksize);
     i=i+1;
    }
   }
   else if(block==n-2)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)(2*blocksize);
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
  int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block <= n)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)(2*blocksize);
     i=i+1;
    }
   }
   else if(block==n)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)(2*blocksize);
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
void MixedAttackGenerator::GenerateTimedLineAttack(int n)
{
 if(mpPatrollerSystem->GetAttackTime()>=3)
 {
  int block=1;
  int i=1;
  int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block <= n-2)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=n-1)
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)(2*(n-1));
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
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)(2*(n-1));
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
  int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block <= n)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=n-1)
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)(2*(n-1));
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
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)(2*(n-1));
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
  int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block<=n+k-2)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)(k+1)/(double)((n+k)*blocksize);
     i=i+1;
    }
   }
   else if(block>=k+1)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)((n+k)*blocksize);
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
  int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block<=n+k)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)(k+1)/(double)((n+k)*blocksize);
     i=i+1;
    }
   }
   else if(block>=k+3)
   {
    i=1;
    while(i<=blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)((n+k)*blocksize);
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
  int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block<=n+k-2)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=2*(k+1))
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)(k+1)/(double)((n+k)*blocksize);
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
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)((n+k)*blocksize);
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
  int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
  while(block<=n+k)
  {
   if(block==1)
   {
    i=1;
    while(i<=blocksize)
    {
     if(i<=2*(k+1))
     {
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)(k+1)/(double)((n+k)*blocksize);
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
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)((n+k)*blocksize);
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
 if(mpPatrollerSystem->GetGameTime()>= mpPatrollerSystem->GetAttackTime()+(2*(k+1)))
 {
  GenerateTimedExtendedStarAttack(n,k);
 }
 else
 {
  GenerateExtendedStarAttack(n,k);
 }
}

/*Methods to internally set Generated Attack- Designed for use with Path Wait Patroller
generation of attacks*/
//Uniform- Same as before
void MixedAttackGenerator::GenerateUniformAttackPW()
{
 int i=1;
 while(i<=mpPatrollerSystem->GetNumPureAttackOptions())
 {
  (*mpGeneratedAttackVector)(i)=(double)1/(double)(mpPatrollerSystem->GetNumPureAttackOptions());
  i=i+1;
 }
}
//Line (under diametric attack)
void MixedAttackGenerator::GenerateLineAttackPW(int n)
{
 GenerateUniformAttackPW(); //Note the line attack is uniform on these slected points
}
//Line (under timed attack)
void MixedAttackGenerator::GenerateTimedLineAttackPW(int n)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
 while(block <= 2)
 {
  i=1;
  while(i<=blocksize)
  {
   if(i<=n-1)
   {
    (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)1/(double)(2*(n-1));
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
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)(k+1)/(double)((n+k)*timechoice1);
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)(1)/(double)((n+k)*timechoice2);
    }
    else if(i==4)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=(double)(1)/(double)((n+k)*timechoice2);
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
void MixedAttackGenerator::GenerateOverallExtendedStarAttackPW(int n,int k)
{
 if(mpPatrollerSystem->GetGameTime()>= mpPatrollerSystem->GetAttackTime()+2*(k+1))
 {
  GenerateTimedExtendedStarAttackPW(n,k);
 }
 else
 {
  GenerateExtendedStarAttackPW(n,k);
 }
}


/* Methods to set attack patterns depending on a step parameter- Designed for use
with the path wait patroller
*/
//Extended Star time variables
void MixedAttackGenerator::GenerateExtendedStarTest1PW(int n,int k,double weight)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(timechoice1)) * weight;
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(timechoice2)) * ((double)(1-weight)/(double)(n-1));
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

void MixedAttackGenerator::GenerateExtendedStarTest2PW(int n,int k,double weight)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(numtimesofattack)) * weight;
     j=j+1;
    }
    else if(i % 3 ==2 && j<=numtimesofattack)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(numtimesofattack)) * weight;
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(numtimesofattack)) * ((double)(1-weight)/(double)(n-1));
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

void MixedAttackGenerator::GenerateExtendedStarTest3PW(int n,int k,double weight)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(timechoice1)) * weight;
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(2)) * ((double)(1-weight)/(double)(n-1));
    }
    else if(i==blocksize)
    {
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(2)) * ((double)(1-weight)/(double)(n-1));
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

void MixedAttackGenerator::GenerateExtendedStarTest4PW(int n,int k,double weight)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(timechoice1)) * weight;
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(blocksize-2)) * ((double)(1-weight)/(double)(n-1));
    }
    i=i+1;
   }
  }
  block=block+1;
 }
 std::flush(std::cout<<(*mpGeneratedAttackVector));
}

void MixedAttackGenerator::GenerateExtendedStarTest5PW(int n,int k,double weight)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(timechoice1)) * weight;
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
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(blocksize-6)) * ((double)(1-weight)/(double)(n-1));
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

void MixedAttackGenerator::GenerateExtendedStarTestOddPW(int n,int k)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(timechoice1)) * weight1;
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
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(timechoice2)) * weight2;
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

void MixedAttackGenerator::GenerateExtendedStarTestEvenPW(int n,int k)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(timechoice1)) * weight1;
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
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(timechoice2)) * weight2;
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

/* This function expects the Vector K to be in size order (though may work without)
*/
void MixedAttackGenerator::GenerateGeneralExtendedStarTestPW(int n, IntVector VectorK)
{
 int block=1;
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
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
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1))/(double)(2*(VectorK(block)+1)) * ((double)(VectorK(block)+1))/((double)(n+ksum));
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
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1))/((double)(2*(1))) * ((double)(1))/((double)(n+ksum));
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

void MixedAttackGenerator::GenerateExtendedStarTestTimePW(int n,int k,double weight,IntVector TimesToAttack)
{
 int i=1;
 int blocksize=(mpPatrollerSystem->GetGameTime()-mpPatrollerSystem->GetAttackTime()+1);
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

 //If no attack takes places at an extended node we need to ignore the weight and place only weight 1 on normal
 if(extendedcounter==0)
 {
  weight=0;
 }


 //If no attack takes place at a normal node we nede to ignore the weight and palce only weight 1 on extended
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
     (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(extendedcounter)) * weight;
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
      (*mpGeneratedAttackVector)((block-1)*blocksize+i)=((double)(1)/(double)(normalcounter)) * ((double)(1-weight)/(double)(n-1));
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
