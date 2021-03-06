#ifndef AliForwardFlowUtil_cxx
#define AliForwardFlowUtil_cxx
/**
 * @file AliForwardFlowUtil.h
 * @author Freja Thoresen <freja.thoresen@cern.ch>
 *
 * @brief
 *
 * @ingroup pwgcf_forward_flow
 */
#include "TObject.h"
#include "TString.h"
#include "TH3.h"
#include "TH2.h"
#include "AliVEvent.h"
#include "AliAODEvent.h"
#include "AliMCEvent.h"
#include "AliTrackReference.h"
#include "AliMCParticle.h"
#include "AliAODVertex.h"
#include "AliForwardSettings.h"
#include "AliFMDStripIndex.h"
#include "AliFMDEncodedEdx.h"
#include "AliFMDMCTrackDensity.h"

class AliForwardFlowUtil : public TObject {
  typedef std::vector< Double_t > edgeContainer;

 public:
   AliForwardFlowUtil();


  Bool_t ExtraEventCutFMD(TH2D& forwarddNdedp, double cent, Bool_t mc,TH2D* hOutliers);
  void FillData(TH2D*& refDist, TH2D*& centralDist, TH2D*& forwardDist);

  void FillFromTrackrefs(TH2D*& cen, TH2D*& fwd) const;
  void FillFromTrackrefs(TH2D*& fwd) ;
  void FillFromPrimaries(TH2D*& cen, TH2D*& fwd) const;
  void FillFromPrimariesAOD(TH2D*& cen, TH2D*& fwd) const;
  void FillFromPrimaries(TH2D*& cen) const;
  void FillFromPrimariesFwd(TH2D*& cen) const;
  void FillFromPrimariesAOD(TH2D*& cen) const;
  void FillFromTracklets(TH2D*& cen) const;
  void FillFromCentralClusters(TH2D*& cen) const;
  void FillFromTracks(TH2D*& cen, UInt_t tracktype) const;

  void FillFromTrackrefs(TH3D*& cen, TH3D*& fwd, Double_t zvertex) const;
  void FillFromPrimaries(TH3D*& cen, TH3D*& fwd, Double_t zvertex) const;
  void FillFromTracklets(TH3D*& cen, Double_t zvertex) const;
  void FillFromTracks(TH3D*& cen, Int_t tracktype, Double_t zvertex) const;
  void FillFromTrackrefsITS(TH2D*& fwd);
  Bool_t ProcessTrackITS(AliMCParticle* particle,AliMCParticle* mother,TH2D*& cen);

  Double_t GetZ();
  Double_t GetCentrality(TString centrality_estimator);
  // Check if a given particle itself hit the FMD. If so, return the
    // (first) track reference of such a hit
  AliTrackReference* IsHitTPC(AliMCParticle* p);
  AliTrackReference* IsHitFMD(AliMCParticle* p);
  void GetTrackRefEtaPhi(AliMCParticle* p, Double_t* etaPhi);
    void GetTrackRefEtaPhi(AliTrackReference* ref, Double_t* etaPhi);

  AliMCParticle* GetMother(Int_t iTr, const AliMCEvent* event) const;

  void MakeFakeHoles(TH2D& forwarddNdedp);
  AliVEvent* fevent; //!
  AliAODEvent* fAODevent; //!
  AliMCEvent* fMCevent; //!
  Bool_t mc; //!
  TH1F* dNdeta; //!
  AliForwardSettings fSettings;
  Double_t maxpt;//!
  Double_t minpt;//!
  Bool_t dodNdeta;//!
  AliFMDMCTrackDensity* fTrackDensity; //!

  mutable struct State
  {
    Double_t angle;            // Angle
    UShort_t oldDetector;      // Last detector
    Char_t   oldRing;          // Last ring
    UShort_t oldSector;        // Last sector
    UShort_t oldStrip;         // Last strip
    UShort_t startStrip;       // First strip
    UShort_t nRefs;            // Number of references
    UShort_t nStrips;          // Number of strips
    UShort_t count;            // Count of hit strips
    AliTrackReference* longest; //! Longest track through
    /**
     * Clear this state
     *
     * @param alsoCount If true, also clear count
    */
    void Clear(Bool_t alsoCount=false);
    /**
     * Assignment operator
     *
     * @param o Object to assign from
     *
     * @return Reference to this object
     */
    State& operator=(const State& o);
  } fState; //! State
  UShort_t fMaxConsequtiveStrips;
  Double_t fLowCutvalue;
  Bool_t            fTrackGammaToPi0;
  AliTrackReference*  ProcessRef(AliMCParticle*       particle,
    AliMCParticle* mother,
    AliTrackReference*   ref,TH2D*& fwd);

  void BeginTrackRefs();
  void EndTrackRefs();

  void StoreParticle(AliMCParticle*       particle,
    AliMCParticle* mother,
    AliTrackReference*   ref,TH2D*& fwd) ;


  Bool_t ProcessTrack(AliMCParticle* particle, AliMCParticle* mother, TH2D*& fwd);

  Double_t GetTrackRefTheta(const AliTrackReference* ref) const;

  AliTrackReference* fStored; //! Last stored


private:
  ClassDef(AliForwardFlowUtil, 2);
};
#endif
