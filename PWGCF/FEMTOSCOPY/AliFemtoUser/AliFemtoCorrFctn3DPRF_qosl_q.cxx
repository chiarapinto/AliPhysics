///////////////////////////////////////////////////////////////////////////
//                                                                       //
// AliFemtoCorrFctn3DPRF_qosl_q: a class to calculate 3D correlation        //
// for pairs of particles in PRF. A 4D THnSparse is filled with Qout, Qside, QLong and Q//
// In analysis the function should be first created in a macro, then     //
// added to the analysis, and at the end of the macro the procedure to   //
// write out histograms should be called.                                //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

#include "AliFemtoCorrFctn3DPRF_qosl_q.h"

#include <cstdio>

#ifdef __ROOT__
ClassImp(AliFemtoCorrFctn3DPRF_qosl_q)
#endif
//____________________________
AliFemtoCorrFctn3DPRF_qosl_q::AliFemtoCorrFctn3DPRF_qosl_q(const char* title, const int& nbins, const float& QHi)
  :
  AliFemtoCorrFctn(),
  fNumerator(0),
  fDenominator(0),
  fNumeratorW(0),
  fDenominatorW(0),
  fNumS(0),
  fDenS(0)

{
  // Basic constructor

  // set up numerator
  char tTitNum[101] = "Num";
  strncat(tTitNum,title, 100);
  fNumerator = new TH3F(tTitNum,title,nbins,-QHi,QHi,nbins,-QHi,QHi,nbins,-QHi,QHi);
  // set up denominator
  char tTitDen[101] = "Den";
  strncat(tTitDen,title, 100);
  fDenominator = new TH3F(tTitDen,title,nbins,-QHi,QHi,nbins,-QHi,QHi,nbins,-QHi,QHi);
//Weighted by qinv histos
  // set up numerator
  char tTitNumW[101] = "NumWqinv";
  strncat(tTitNumW,title, 100);
  fNumeratorW = new TH3F(tTitNumW,title,nbins,-QHi,QHi,nbins,-QHi,QHi,nbins,-QHi,QHi);
  // set up denominator
  char tTitDenW[101] = "DenWqinv";
  strncat(tTitDenW,title, 100);
  fDenominatorW = new TH3F(tTitDenW,title,nbins,-QHi,QHi,nbins,-QHi,QHi,nbins,-QHi,QHi);
   //sparse
   const Int_t ndims = 4;
   Int_t bins[ndims] = {300, 300, 300, 300};
   Double_t kmin[ndims] = {0.,0.,0.,0.};
   Double_t kmax[ndims] = {0.3,0.3,0.3,0.3};
   fNumS = new THnSparseD("fNumS", "Numerator", ndims, bins, kmin, kmax);
   fDenS = new THnSparseD("fDenS", "Denominator", ndims, bins, kmin, kmax);

  // to enable error bar calculation...
  fNumerator->Sumw2();
  fDenominator->Sumw2();
  fNumeratorW->Sumw2();
  fDenominatorW->Sumw2();
}

AliFemtoCorrFctn3DPRF_qosl_q::AliFemtoCorrFctn3DPRF_qosl_q(const AliFemtoCorrFctn3DPRF_qosl_q& aCorrFctn) :
  AliFemtoCorrFctn(aCorrFctn),
  fNumerator(0),
  fDenominator(0),
  fNumeratorW(0),
  fDenominatorW(0),
  fNumS(0),
  fDenS(0)
{
  // Copy constructor
  fNumerator = new TH3F(*aCorrFctn.fNumerator);
  fDenominator = new TH3F(*aCorrFctn.fDenominator);
  fNumeratorW = new TH3F(*aCorrFctn.fNumeratorW);
  fDenominatorW = new TH3F(*aCorrFctn.fDenominatorW);
  // fNumS = new THnSparse(*aCorrFctn.fNumS);
  //fDenS = new THnSparse(*aCorrFctn.fDenS);
}
//____________________________
AliFemtoCorrFctn3DPRF_qosl_q::~AliFemtoCorrFctn3DPRF_qosl_q(){
  // Destructor
  delete fNumerator;
  delete fDenominator;
  delete fNumeratorW;
  delete fDenominatorW;
  // delete fNumS;
  //delete fDenS;
}
//_________________________
AliFemtoCorrFctn3DPRF_qosl_q& AliFemtoCorrFctn3DPRF_qosl_q::operator=(const AliFemtoCorrFctn3DPRF_qosl_q& aCorrFctn)
{
  // assignment operator
  if (this == &aCorrFctn)
    return *this;

  if (fNumerator) delete fNumerator;
  fNumerator = new TH3F(*aCorrFctn.fNumerator);
  if (fDenominator) delete fDenominator;
  fDenominator = new TH3F(*aCorrFctn.fDenominator);
  if (fNumeratorW) delete fNumeratorW;
  fNumeratorW = new TH3F(*aCorrFctn.fNumeratorW);
  if (fDenominatorW) delete fDenominatorW;
  fDenominatorW = new TH3F(*aCorrFctn.fDenominatorW);
  /* if (fNumS) delete fNumS;
  fNumS = new THnSparse(*aCorrFctn.fNumS);
  if (fDenS) delete fDenS;
  fDenS = new THnSparse(*aCorrFctn.fDenS);*/
  return *this;
}

//_________________________
void AliFemtoCorrFctn3DPRF_qosl_q::WriteOutHistos(){
  // Write out all histograms to file
  //fNumerator->Write();
  //fDenominator->Write();
  //fNumeratorW->Write();
  //fDenominatorW->Write();
  fNumS->Write();
  fDenS->Write();
}
//______________________________
TList* AliFemtoCorrFctn3DPRF_qosl_q::GetOutputList()
{
  // Prepare the list of objects to be written to the output
  TList *tOutputList = new TList();

  //tOutputList->Add(fNumerator);
  //tOutputList->Add(fDenominator);
  //tOutputList->Add(fNumeratorW);
  //tOutputList->Add(fDenominatorW);
  tOutputList->Add(fNumS);
  tOutputList->Add(fDenS);

  return tOutputList;
}

//_________________________
void AliFemtoCorrFctn3DPRF_qosl_q::Finish(){
  // here is where we should normalize, fit, etc...

}

//____________________________
AliFemtoString AliFemtoCorrFctn3DPRF_qosl_q::Report(){
  // Construct the report
  string stemp = "PRF 3D Correlation Function Report:\n";
  char ctemp[100];
  snprintf(ctemp , 100, "Number of entries in numerator:\t%E\n",fNumerator->GetEntries());
  stemp += ctemp;
  snprintf(ctemp , 100, "Number of entries in denominator:\t%E\n",fDenominator->GetEntries());
  stemp += ctemp;

  if (fPairCut){
    snprintf(ctemp , 100, "Here is the PairCut specific to this CorrFctn\n");
    stemp += ctemp;
    stemp += fPairCut->Report();
  }
  else{
    snprintf(ctemp , 100, "No PairCut specific to this CorrFctn\n");
    stemp += ctemp;
  }

  //
  AliFemtoString returnThis = stemp;
  return returnThis;
}
//____________________________
void AliFemtoCorrFctn3DPRF_qosl_q::AddRealPair( AliFemtoPair* pair){
  // perform operations on real pairs
  if (fPairCut && !fPairCut->Pass(pair)) {
    return;
  }
     Double_t x[4];
    for (Int_t d = 0; d < 4; ++d) {
         switch (d) {
         case 0: x[d] = (pair->KOut()); break;
         case 1: x[d] = (pair->KSide()); break;
         case 2:x[d] = (pair->KLong()); break;
         case 3: x[d] = sqrt(((pair->KOut())*(pair->KOut())) + ((pair->KSide())*(pair->KSide())) +
			     ((pair->KLong())*(pair->KLong()))); break;
         default: x[d] = (pair->KOut());
         }
      }
      fNumS->Fill(x);

  double qOut = (pair->KOut());
  double qSide = (pair->KSide());
  double qLong = (pair->KLong());
  double qqinv = (pair->QInv());

    fNumerator->Fill(qOut,qSide,qLong);
    //fNumeratorW->Fill(qOut,qSide,qLong,qqinv);



}
//____________________________
void AliFemtoCorrFctn3DPRF_qosl_q::AddMixedPair( AliFemtoPair* pair){
  // perform operations on mixed pairs
  if (fPairCut && !fPairCut->Pass(pair)) {
    return;
  }
     Double_t x[4];
    for (Int_t d = 0; d < 4; ++d) {
         switch (d) {
         case 0: x[d] = (pair->KOut()); break;
         case 1: x[d] = (pair->KSide()); break;
         case 2:x[d] = (pair->KLong()); break;
         case 3: x[d] = sqrt(((pair->KOut())*(pair->KOut())) + ((pair->KSide())*(pair->KSide())) +
          ((pair->KLong())*(pair->KLong()))); break;
         default: x[d] = (pair->KOut());
         }
      }
      fDenS->Fill(x);


  double qOut = (pair->KOut());
  double qSide = (pair->KSide());
  double qLong = (pair->KLong());
  double qqinv = (pair->QInv());


    fDenominator->Fill(qOut,qSide,qLong,1.0);
    //fDenominatorW->Fill(qOut,qSide,qLong,qqqinv);



}


