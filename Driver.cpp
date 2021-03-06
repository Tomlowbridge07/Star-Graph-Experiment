#include<iostream>
#include "IntMatrix.hpp"
#include "Int3DMatrix.hpp"
#include "AbstractPatroller.hpp"
#include "MixedPatroller.hpp"
#include "MixedPolicyEvaluation.hpp"
#include "PathWaitPatroller.hpp"
#include "SpecialGraphGenerator.hpp"
#include "PathGenerator.hpp"
#include "Vector.hpp"
#include "BatchMixedPolicyEvaluation.hpp"
#include "BatchTimeMixedPolicyEvaluation.hpp"
#include "ObjectsInBins.hpp"

int main(int argc,char* argv[])
{


/*
 std::flush(std::cout<<"Starting");
 SpecialGraphGenerator GraphGen;
 GraphGen.GenerateSymmetricDualStar(3,1);
 IntMatrix SymDualStar(GraphGen.GetAdjacenyMatrix());
 std::flush(std::cout<<SymDualStar);
 IntVector AttackNodes(6);
 AttackNodes(1)=1; AttackNodes(2)=2; AttackNodes(3)=3;
 AttackNodes(4)=7; AttackNodes(5)=8; AttackNodes(6)=9; ;
 PathGenerator PathGen(SymDualStar);
 PathGen.GeneratePathsFromDepth(AttackNodes,AttackNodes);
 IntMatrix Paths(PathGen.GetPaths());
 PathWaitPatroller PWPat(SymDualStar,AttackNodes,Paths,16,6);
 MixedPatroller MPWPat(PWPat);
 MixedAttackGenerator Gen(PWPat);
 Gen.GenerateSymmetricDualStarTestPW(3,1);
 MPWPat.SetMixedAttackerStrategy(Gen.GetGeneratedAttackVector());
 MPWPat.EvaluateAttackerAgainstPurePatroller();
 std::cout<<MPWPat.GetAttackerAgainstPureEvaluation().Max();
*/

 //We want to test the new range of strategies for m<2(k+1), m<2(n+1)
 //Consruct extended star graph
 SpecialGraphGenerator GraphGen;
 GraphGen.GenerateExtendedStar(7,5);
 IntMatrix ExtendedStar(GraphGen.GetAdjacenyMatrix());
 std::flush(std::cout<<"Adjacency matrix generated is:\n"<<ExtendedStar);
 //Construct Patroller system
 AbstractPatroller Patroller(ExtendedStar,7,4);
 //Construct attack we wish to use
 MixedAttackGenerator AttackGen(Patroller);
 AttackGen.GenerateLowerExtendedStarAttack(7,5);
 Vector Attack(AttackGen.GetGeneratedAttackVector());
 std::flush(std::cout<<"Attack generated is:\n"<<Attack);
 //Make Mixed patroller to evaluate the attack
 /*MixedPatroller MixPatroller(Patroller)
 MixPatroller.SetMixedAttackerStrategy(Attack);
 MixPatroller.EvaluatePatrollerAgainstPureAttacker();
 MixPatroller.GetPatrollerAgainstPureEvaluation();*/






















/*
 IntVector VectorK(4);
 VectorK(1)=2; VectorK(2)=1; VectorK(3)=1; VectorK(4)=1;
 SpecialGraphGenerator GraphGen;
 GraphGen.GenerateGeneralExtendedStar(4,VectorK);
 IntMatrix Star(GraphGen.GetAdjacenyMatrix());
 std::flush(std::cout<<"Star graph is: \n"<<Star<<"\n");
 PathGenerator PathGen(Star);
 IntVector AttackNodes(4);
 AttackNodes(1)=1;
 AttackNodes(2)=4;
 AttackNodes(3)=6;
 AttackNodes(4)=8;
 PathGen.GeneratePathsFromDepth(AttackNodes,AttackNodes);
 IntMatrix Paths(PathGen.GetPaths());
 std::flush(std::cout<<"Paths are: \n"<<Paths<<"\n");
 PathWaitPatroller PWPat(Star,AttackNodes,Paths,15,10);
 PWPat.PrintPurePatrollerOptions();
 MixedPatroller MPWPat(PWPat);
 MixedAttackGenerator Gen(PWPat);
 Gen.GenerateGeneralExtendedStarTestPW(4,VectorK);
 MPWPat.SetMixedAttackerStrategy(Gen.GetGeneratedAttackVector());
 MPWPat.EvaluateAttackerAgainstPurePatroller();
 std::cout<<MPWPat.GetAttackerAgainstPureEvaluation().Max();
*/

/*
 SpecialGraphGenerator GraphGen;
 GraphGen.GenerateExtendedStar(4,1);
 IntMatrix Star(GraphGen.GetAdjacenyMatrix());
 std::flush(std::cout<<"Star graph is: "<<Star<<"\n");
 PathGenerator PathGen(Star);
 IntVector AttackNodes(4);
 AttackNodes(1)=1;
 AttackNodes(2)=4;
 AttackNodes(3)=5;
 AttackNodes(4)=6;
 PathGen.GeneratePathsFromDepth(AttackNodes,AttackNodes);
 IntMatrix Paths(PathGen.GetPaths());
 std::flush(std::cout<<"Paths are:"<<Paths<<"\n");
 PathWaitPatroller PWPat(Star,AttackNodes,Paths,12,7);
 PWPat.PrintPurePatrollerOptions();
 MixedPatroller MPWPat(PWPat);
 MixedPolicyEvaluation Ev(MPWPat);
 Ev.EvaluateExtendedStarGraphTestPW(4,1);
 Ev.PrintPolicyEvaluation();

 //Testing Max and Min elements
 IntVector Test(6);
 Test(1)=5; Test(2)=-2; Test(3)=5; Test(4)=0; Test(5)=-2; Test(6)=5;
 std::cout<<Test.MaxElements();


 //Testing Int3DMatrix
 Int3DMatrix Matrix1(9,10,4);
 Matrix1(5,6,1)=5; Matrix1(6,2,2)=-3; Matrix1(1,1,1)=4;
 Int3DMatrix Copy(Matrix1);
 Copy(2,1,1)=-6;
 Int3DMatrix Addition(9,10,4);
 Addition=Copy+Matrix1;
 std::cout<<Matrix1;
 std::cout<<Copy;
 std::cout<<Addition;
 std::cout<<Addition.GetLayerMatrix(1);
 std::cout<<Addition.GetColMatrix(1);
 std::cout<<Addition.GetRowMatrix(1);
 IntMatrix Normal(9,10);
 Normal(1,1)=-100;
 Normal(9,10)=100;
 Addition.SetLayerMatrix(2,Normal);
 std::cout<<Addition;
 IntMatrix Test(3,2);
 Test(1,2)=5; Test(3,1)=5; Test(2,2)=7;
 std::cout<<Test;
 Test.AddRow(1);
 std::cout<<Test;
 Test.AddCol(1,false);
 std::cout<<Test;
 std::cout<<Addition;
 Addition.ExtendRow(2);
 Addition.ExtendLayer(5);
 std::cout<<Addition;
 Addition.DeleteLayer(1);
 std::cout<<Addition;
 Addition.DeleteCol(4);
 Addition.DeleteRow(2);
 std::cout<<Addition;

 SpecialGraphGenerator GraphGen;
 GraphGen.GenerateExtendedStar(4,1);
 IntMatrix Star(GraphGen.GetAdjacenyMatrix());
 std::flush(std::cout<<"Star graph is: "<<Star<<"\n");
 PathGenerator PathGen(Star);
 IntVector AttackNodes(4);
 AttackNodes(1)=1;
 AttackNodes(2)=4;
 AttackNodes(3)=5;
 AttackNodes(4)=6;
 PathGen.GeneratePathsFromDepth(AttackNodes,AttackNodes);
 IntMatrix Paths(PathGen.GetPaths());
 std::flush(std::cout<<"Paths are:"<<Paths<<"\n");
 PathWaitPatroller PWPat(Star,AttackNodes,Paths,12,8);
 PWPat.PrintPurePatrollerOptions();
 MixedPatroller MPWPat(PWPat);
 MixedPolicyEvaluation Ev(MPWPat);
 Ev.EvaluateExtendedStarGraphTestPW(4,1);
 std::cout<<Ev.GetAllBestPatrollerStrat();
 if((Ev.GetAllBestPatrollerStrat()).GetNumberRows()==
 PWPat.GetNumPurePatrolOptions())
 {
  std::cout<<"\nYes";
 }
 else
 {
  std::cout<<"\nNo";
 }

 */
/*
 IntMatrix TwinStar(7,7);
 TwinStar(1,1)=1; TwinStar(1,3)=1;
 TwinStar(2,2)=1; TwinStar(2,3)=1;
 TwinStar(3,1)=1; TwinStar(3,2)=1; TwinStar(3,3)=1; TwinStar(3,7)=1;
 TwinStar(4,4)=1; TwinStar(4,7)=1;
 TwinStar(5,5)=1; TwinStar(5,7)=1;
 TwinStar(6,6)=1; TwinStar(6,7)=1;
 TwinStar(7,3)=1; TwinStar(7,4)=1; TwinStar(7,5)=1; TwinStar(7,6)=1; TwinStar(7,7)=1;

 IntVector AttackNodes(5);
 AttackNodes(1)=1; AttackNodes(2)=2; AttackNodes(3)=4; AttackNodes(4)=5; AttackNodes(5)=6;
 PathGenerator Pathgen(TwinStar);
 Pathgen.GeneratePathsFromDepth(AttackNodes,AttackNodes);
 IntMatrix Paths(Pathgen.GetPaths());
 PathWaitPatroller PWPat(TwinStar,AttackNodes,Paths,12,7);
 PWPat.PrintPurePatrollerOptions();
 MixedPatroller MPWPat(PWPat);
 MixedPolicyEvaluation Ev(MPWPat);
 BatchMixedPolicyEvaluation Batcher(MPWPat,0.1);
 BatchTimeMixedPolicyEvaluation TimeBatcher(Batcher,2);
 TimeBatcher.EvaluateDualStarBatchTimeTestPW(2,3);
 */

/*
 IntMatrix TwinStar(6,6);
 TwinStar(1,1)=1; TwinStar(1,3)=1;
 TwinStar(2,2)=1; TwinStar(2,3)=1;
 TwinStar(3,1)=1; TwinStar(3,2)=1; TwinStar(3,3)=1; TwinStar(3,6)=1;
 TwinStar(4,4)=1; TwinStar(4,6)=1;
 TwinStar(5,5)=1; TwinStar(5,6)=1;
 TwinStar(6,3)=1; TwinStar(6,4)=1; TwinStar(6,5)=1; TwinStar(6,6)=1;

 IntVector AttackNodes(4);
 AttackNodes(1)=1; AttackNodes(2)=2; AttackNodes(3)=4; AttackNodes(4)=5;
 PathGenerator Pathgen(TwinStar);
 Pathgen.GeneratePathsFromDepth(AttackNodes,AttackNodes);
 IntMatrix Paths(Pathgen.GetPaths());
 PathWaitPatroller PWPat(TwinStar,AttackNodes,Paths,10,5);
 PWPat.PrintPurePatrollerOptions();
 MixedPatroller MPWPat(PWPat);
 MixedPolicyEvaluation Ev(MPWPat);
 BatchMixedPolicyEvaluation Batcher(MPWPat,0.5);
 BatchTimeMixedPolicyEvaluation TimeBatcher(Batcher,2);
 TimeBatcher.EvaluateDualStarBatchTimeTestPW(2,2); */


/*
 SpecialGraphGenerator GraphGen;
 GraphGen.GenerateExtendedStar(4,1);
 IntMatrix Star(GraphGen.GetAdjacenyMatrix());
 std::flush(std::cout<<"Star graph is: "<<Star<<"\n");
 AbstractPatroller Pat(Star,6,4);
 MixedPatroller MPat(Pat);
 BatchMixedPolicyEvaluation Batcher(MPat,0.05);
 BatchTimeMixedPolicyEvaluation TimeBatcher(Batcher,4);
 TimeBatcher.EvaluateExtendedStarBatchTimeTest(4,1);
*/

/*
 SpecialGraphGenerator GraphGen;
 GraphGen.GenerateExtendedStar(4,1);
 IntMatrix Star(GraphGen.GetAdjacenyMatrix());
 std::flush(std::cout<<"Star graph is: "<<Star<<"\n");
 PathGenerator PathGen(Star);
 IntVector AttackNodes(4);
 AttackNodes(1)=1;
 AttackNodes(2)=4;
 AttackNodes(3)=5;
 AttackNodes(4)=6;
 PathGen.GeneratePathsFromDepth(AttackNodes,AttackNodes);
 IntMatrix Paths(PathGen.GetPaths());
 std::flush(std::cout<<"Paths are:"<<Paths<<"\n");
 PathWaitPatroller PWPat(Star,AttackNodes,Paths,7,4);
 PWPat.PrintPurePatrollerOptions();
 MixedPatroller MPWPat(PWPat);
 BatchMixedPolicyEvaluation Batcher(MPWPat,0.1);
 BatchTimeMixedPolicyEvaluation TimeBatcher(Batcher);
 TimeBatcher.EvaluateBatchTimeTest(4,1);

/*
 SpecialGraphGenerator GraphGen;
 GraphGen.GenerateExtendedStar(4,1);
 IntMatrix Star(GraphGen.GetAdjacenyMatrix());
 std::flush(std::cout<<"Star graph is: "<<Star<<"\n");
 PathGenerator PathGen(Star);
 IntVector AttackNodes(4);
 AttackNodes(1)=1;
 AttackNodes(2)=4;
 AttackNodes(3)=5;
 AttackNodes(4)=6;
 PathGen.GeneratePathsFromDepth(AttackNodes,AttackNodes);
 IntMatrix Paths(PathGen.GetPaths());
 std::flush(std::cout<<"Paths are:"<<Paths<<"\n");
 PathWaitPatroller PWPat(Star,AttackNodes,Paths,9,6);
 PWPat.PrintPurePatrollerOptions();
 MixedPatroller MPWPat(PWPat);
 BatchMixedPolicyEvaluation Batcher(MPWPat,0.1);
 BatchTimeMixedPolicyEvaluation TimeBatcher(Batcher);
 TimeBatcher.EvaluateBatchTimeTest(4,1);

/*
 //Used to find solutions to weighting and attack positions
 SpecialGraphGenerator GraphGen;
 GraphGen.GenerateExtendedStar(4,1);
 IntMatrix Star(GraphGen.GetAdjacenyMatrix());
 std::flush(std::cout<<"Star graph is: "<<Star<<"\n");
 PathGenerator PathGen(Star);
 IntVector AttackNodes(4);
 AttackNodes(1)=1;
 AttackNodes(2)=4;
 AttackNodes(3)=5;
 AttackNodes(4)=6;
 PathGen.GeneratePathsFromDepth(AttackNodes,AttackNodes);
 IntMatrix Paths(PathGen.GetPaths());
 std::flush(std::cout<<"Paths are:"<<Paths<<"\n");
 PathWaitPatroller PWPat(Star,AttackNodes,Paths,9,6);
 PWPat.PrintPurePatrollerOptions();
 MixedPatroller MPWPat(PWPat);
 MixedAttackGenerator Gen(PWPat);
 Gen.GenerateExtendedStarTestOddPW(4,1);
 MPWPat.SetMixedAttackerStrategy(Gen.GetGeneratedAttackVector());
 MPWPat.EvaluateAttackerAgainstPurePatroller();
 std::cout<<MPWPat.GetAttackerAgainstPureEvaluation().Max();


 /*BatchMixedPolicyEvaluation Batcher(MPWPat,0.01);
 Batcher.EvaluateBatchTest1(4,1);
 std::cout<<"Batcher output: \n"
 <<Batcher.GetEvaluationVector()<<Batcher.GetBestPatrollerStrat();
 BatchTimeMixedPolicyEvaluation TimeBatcher(Batcher);
 TimeBatcher.EvaluateBatchTimeTest(4,1); */

/*
 SpecialGraphGenerator GraphGen;
 GraphGen.GenerateExtendedStar(4,1);
 IntMatrix Star(GraphGen.GetAdjacenyMatrix());
 std::flush(std::cout<<"Star graph is: "<<Star<<"\n");
 PathGenerator PathGen(Star);
 IntVector AttackNodes(4);
 AttackNodes(1)=1;
 AttackNodes(2)=4;
 AttackNodes(3)=5;
 AttackNodes(4)=6;
 PathGen.GeneratePathsFromDepth(AttackNodes,AttackNodes);
 IntMatrix Paths(PathGen.GetPaths());
 std::flush(std::cout<<"Paths are:"<<Paths<<"\n");
 PathWaitPatroller PWPat(Star,AttackNodes,Paths,10,10);
 PWPat.PrintPurePatrollerOptions();
 MixedPatroller MPWPat(PWPat);
 MixedPolicyEvaluation EV(MPWPat);
 EV.EvaluateOverallStarGraphMTSpaceBestPW(4,1,3,8,8,16);
 EV.PrintMTSpacePolicyEvaluation();


/*
 //Set up Adjacency matrix for S_{5}^1
 IntMatrix Adj(7,7);
 Adj(1,1)=1;
 Adj(1,2)=1;
 Adj(2,1)=1;
 Adj(2,2)=1;
 Adj(2,3)=1;
 Adj(3,2)=1;
 Adj(3,3)=1;
 Adj(3,4)=1;
 Adj(3,5)=1;
 Adj(3,6)=1;
 Adj(3,7)=1;
 Adj(4,3)=1;
 Adj(4,4)=1;
 Adj(5,3)=1;
 Adj(5,5)=1;
 Adj(6,3)=1;
 Adj(6,6)=1;
 Adj(7,3)=1;
 Adj(7,7)=1;
 std::cout<<Adj;

 //Set up Adjacency matrix for S_{6}^1
 IntMatrix Adj2(8,8);
 Adj2(1,1)=1;
 Adj2(1,2)=1;
 Adj2(2,1)=1;
 Adj2(2,2)=1;
 Adj2(2,3)=1;
 Adj2(3,2)=1;
 Adj2(3,3)=1;
 Adj2(3,4)=1;
 Adj2(3,5)=1;
 Adj2(3,6)=1;
 Adj2(3,7)=1;
 Adj2(3,8)=1;
 Adj2(4,3)=1;
 Adj2(4,4)=1;
 Adj2(5,3)=1;
 Adj2(5,5)=1;
 Adj2(6,3)=1;
 Adj2(6,6)=1;
 Adj2(7,3)=1;
 Adj2(7,7)=1;
 Adj2(8,3)=1;
 Adj2(8,8)=1;
 std::cout<<Adj2;

 //Set up line matrix for $L_{n}$
 int n=10;
 IntMatrix Line(n,n);
 Line(1,1)=1;
 Line(1,2)=1;
 int i=2;
 while(i<=n-1)
 {
  Line(i,i-1)=1;
  Line(i,i)=1;
  Line(i,i+1)=1;
  i=i+1;
 }
 Line(n,n-1)=1;
 Line(n,n)=1;

 IntVector Attacknodes(2);
 Attacknodes(1)=1;
 Attacknodes(2)=10;

 IntMatrix Paths(4,10);
 Paths.Fill(-1);
 Paths(1,1)=1; Paths(1,2)=1;
 Paths(4,1)=10; Paths(4,2)=10;
 i=1;
 while(i<=10)
 {
  Paths(2,i)=i;
  Paths(3,i)=11-i;
  i=i+1;
 }

 PathWaitPatroller PWPat(Line,Attacknodes,Paths,20,10);
 PWPat.PrintPurePatrollerOptions();
 PWPat.PrintPureAttackerOptions();
 MixedPatroller MPWPat(PWPat);
 MixedPolicyEvaluation Ev(MPWPat);
 Ev.EvaluateOverallLineGraphPW(n);
 Ev.PrintBestPatrollerStrategies();
 Ev.PrintPolicyEvaluation();
 std::flush(std::cout<<"");
 Ev.EvaluateOverallLineGraphMTSpaceBestPW(n,10,20,20,30);
 Ev.PrintMTSpacePolicyEvaluation();


/*
 //Run Line evaluation
 MixedPolicyEvaluation LineEv(Line,2,2,1);
 LineEv.EvaluateLineGraph(n);
 LineEv.PrintBestPatrollerStrategies();
 LineEv.EvaluateTimedLineGraphMTSpaceBest(n,1,1,9,9);
 LineEv.PrintMTSpacePolicyEvaluation();
 LineEv.SaveMTSpaceEvaluation();
 LineEv.SaveMTSpaceKeyProbability();
 LineEv.SaveMTSpaceBestPatrollerStrategies();

 i=1;
 /*
 //Testing S_{4}^{2,1}
 IntMatrix SpecialStar(8,8);
 SpecialStar(1,1)=1;
 SpecialStar(1,2)=1;
 i=2;
 while(i<=3)
 {
  SpecialStar(i,i-1)=1;
  SpecialStar(i,i)=1;
  SpecialStar(i,i+1)=1;
  i=i+2;
 }
 SpecialStar(4,3)=1;
 SpecialStar(4,4)=1;
 SpecialStar(4,5)=1;
 SpecialStar(4,6)=1;
 SpecialStar(4,7)=1;
 SpecialStar(5,4)=1;
 SpecialStar(5,5)=1;
 SpecialStar(6,4)=1;
 SpecialStar(6,6)=1;
 SpecialStar(7,4)=1;
 SpecialStar(7,7)=1;
 SpecialStar(7,8)=1;
 SpecialStar(8,7)=1;
 SpecialStar(8,8)=1;

 IntVector Attacknodes(4);
 Attacknodes(1)=1;
 Attacknodes(2)=5;
 Attacknodes(3)=6;
 Attacknodes(4)=8;

 IntMatrix Paths(16,6);
 Paths.Fill(-1);
 Paths(1,1)=1; Paths(1,2)=1;
 Paths(2,1)=1; Paths(2,2)=2; Paths(2,3)=3; Paths(2,4)=4; Paths(2,5)=5;
 Paths(3,1)=1; Paths(3,2)=2; Paths(3,3)=3; Paths(3,4)=4; Paths(3,5)=6;
 Paths(4,1)=1; Paths(4,2)=2; Paths(4,3)=3; Paths(4,4)=4; Paths(4,5)=7; Paths(4,6)=8;
 Paths(5,1)=5; Paths(5,2)=4; Paths(5,3)=3; Paths(5,4)=2; Paths(5,5)=1;
 Paths(6,1)=5; Paths(6,2)=5;
 Paths(7,1)=5; Paths(7,2)=4; Paths(7,3)=6;
 Paths(8,1)=5; Paths(8,2)=4; Paths(8,3)=7; Paths(8,4)=8;
 Paths(9,1)=6; Paths(9,2)=4; Paths(9,3)=3; Paths(9,4)=2; Paths(9,5)=1;
 Paths(10,1)=6; Paths(10,2)=4; Paths(10,3)=5;
 Paths(11,1)=6; Paths(11,2)=6;
 Paths(12,1)=6; Paths(12,2)=4; Paths(12,3)=7; Paths(12,4)=8;
 Paths(13,1)=8; Paths(13,2)=7; Paths(13,3)=4; Paths(13,4)=3; Paths(13,5)=2; Paths(13,6)=1;
 Paths(14,1)=8; Paths(14,2)=7; Paths(14,3)=4; Paths(14,4)=5;
 Paths(15,1)=8; Paths(15,2)=7; Paths(15,3)=4; Paths(15,4)=6;
 Paths(16,1)=8; Paths(16,2)=8;

 std::cout<<Paths;

 PathWaitPatroller Tester(SpecialStar,Attacknodes,Paths,7,7);
 std::cout<<Tester.GetPathLengths();
 std::cout<<Tester.countPatrols(1,2,6);
 std::cout<<Tester.GetPureAttackingOptions();
 std::cout<<Tester.GetPurePatrollingOptions();
 //std::cout<<Tester.GetPurePatrollingStrategies();
 */
/*
 IntVector Attacknodes(5);
 Attacknodes(1)=1;
 Attacknodes(2)=4;
 Attacknodes(3)=5;
 Attacknodes(4)=6;
 Attacknodes(5)=7;

 IntMatrix Paths(25,4);
 Paths.Fill(-1);
 Paths(1,1)=1; Paths(1,2)=1;
 Paths(2,1)=1; Paths(2,2)=2; Paths(2,3)=3; Paths(2,4)=4;
 Paths(3,1)=1; Paths(3,2)=2; Paths(3,3)=3; Paths(3,4)=5;
 Paths(4,1)=1; Paths(4,2)=2; Paths(4,3)=3; Paths(4,4)=6;
 Paths(5,1)=1; Paths(5,2)=2; Paths(5,3)=3; Paths(5,4)=7;
 //
 Paths(6,1)=4; Paths(6,2)=3; Paths(6,3)=2; Paths(6,4)=1;
 Paths(7,1)=4; Paths(7,2)=4;
 Paths(8,1)=4; Paths(8,2)=3; Paths(8,3)=5;
 Paths(9,1)=4; Paths(9,2)=3; Paths(9,3)=6;
 Paths(10,1)=4; Paths(10,2)=3; Paths(10,3)=7;
 //
 Paths(11,1)=5; Paths(11,2)=3; Paths(11,3)=2; Paths(11,4)=1;
 Paths(12,1)=5; Paths(12,2)=3; Paths(12,3)=4;
 Paths(13,1)=5; Paths(13,2)=5;
 Paths(14,1)=5; Paths(14,2)=3; Paths(14,3)=6;
 Paths(15,1)=5; Paths(15,2)=3; Paths(15,3)=7;
 //
 Paths(16,1)=6; Paths(16,2)=3; Paths(16,3)=2; Paths(16,4)=1;
 Paths(17,1)=6; Paths(17,2)=3; Paths(17,3)=4;
 Paths(18,1)=6; Paths(18,2)=3; Paths(18,3)=5;
 Paths(19,1)=6; Paths(19,2)=6;
 Paths(20,1)=6; Paths(20,2)=3; Paths(20,3)=7;
 //
 Paths(21,1)=7; Paths(21,2)=3; Paths(21,3)=2; Paths(21,4)=1;
 Paths(22,1)=7; Paths(22,2)=3; Paths(22,3)=4;
 Paths(23,1)=7; Paths(23,2)=3; Paths(23,3)=5;
 Paths(24,1)=7; Paths(24,2)=3; Paths(24,3)=6;
 Paths(25,1)=7; Paths(25,2)=7;

 /*
 AbstractPatroller PurePat(Line,5,4);
 MixedPatroller MixPat(PurePat);
 MixedPolicyEvaluation EvalPat(MixPat);
 EvalPat.EvaluateLineGraph(n);
 std::flush(std::cout<<"hello");
 EvalPat.EvaluateLineGraphMTSpaceBest(n,1,1,7,7);
 EvalPat.PrintMTSpacePolicyEvaluation();


 /*
 PathWaitPatroller Test2(Adj,Attacknodes,Paths,3,3);
 std::cout<<Test2.GetPathLengths();
 std::cout<<Test2.GetPurePatrollingOptions();
 MixedPolicyEvaluation Test2Ev(Test2,1);
 Test2Ev.EvaluateTimedStarGraphMTSpaceBest(5,1,2,5,2,5);
 Test2Ev.PrintMTSpacePolicyEvaluation();

/*
 MixedPolicyEvaluation Ev(Adj,4,4,100);
 Ev.EvaluateStarGraphMTSpaceBest(5,1,1,1,6,6);
 Ev.PrintMTSpaceBestPatrollerStrategies();
 Ev.PrintMTSpacePolicyEvaluation();
 Ev.PrintPolicyEvaluation();
 Ev.PrintMTSpaceBestPatrollerStrategies();
 Ev.SavePolicyEvaluation("Hello.dat");
 Ev.SaveMTSpaceEvaluation();
 Ev.SaveMTSpaceKeyProbability();
 Ev.SaveMTSpaceBestPatrollerStrategies();
 */


 //std::cout<<LineEv.GetMTSpaceEvaluation();
 //std::cout<<LineEv.GetMTSpaceBestPatrollerStratNum();
 //LineEv.PrintPolicyEvaluation();
  //LineEv.PrintMTSpacePolicyEvaluation();

/*
 MixedPolicyEvaluation Evaluator(Adj,8,8,10000);
 //Evaluator.EvaluateStarGraph(5,1);
 //std::cout<<(Evaluator.GetEvaluationVector()).Min();
 //int BestPatroller=(Evaluator.GetEvaluationVector()).MinElement();
 //std::cout<<(Evaluator.GetBestPatrollerVector())(BestPatroller);

 //std::flush(std::cout<<"using function");
 Evaluator.EvaluateStarGraphMTSpaceBest(5,1,4,4,8,8);
 std::cout<<(Evaluator.GetMTSpaceEvaluation()); */


 return 0;
}
