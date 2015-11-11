// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * posdepparser.h - the definitions for the dependency parser.     *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.8                         *
 *                                                              *
 ****************************************************************/

#ifndef _POSDEPPARSER_IMPL_H
#define _POSDEPPARSER_IMPL_H

#include "posdepparser_base.h"

/*===============================================================
 *
 * Global items
 *
 *==============================================================*/

namespace TARGET_LANGUAGE {

namespace posdepparser {

#include "state.h"

}; // namespace posdepparser
};

#include "posdepparser_weight.h"

namespace TARGET_LANGUAGE {

/*===============================================================
 *
 * CPosDepParser - the dependency parser for English
 *
 *==============================================================*/

class CPosDepParser : public CPosDepParserBase {

private:

   CAgendaBeam<posdepparser::CStateItem> *m_Agenda;
   CAgendaSimple<posdepparser::action::CScoredAction> *m_Beam;

   // caches for input
   std::vector< CWord > m_lCache;
   std::vector< CWord > m_lCharCache;
   std::vector< int > m_wordIndexs;
   CSTackFeatsVec  m_stackfeats;

#ifdef LABELED
   std::vector< CDependencyLabel > m_lCacheLabel;
#endif


   int m_nTrainingRound;
   int m_nTotalErrors;
   bool m_bScoreModified;
   int m_nScoreIndex;

   posdepparser::CWeight *m_delta_pos;
   posdepparser::CWeight *m_delta_dep;

public:
   // constructor and destructor
   CPosDepParser( const std::string &sFeatureDBPath , bool bTrain ) : CPosDepParserBase(sFeatureDBPath, bTrain) {
      m_Agenda = new CAgendaBeam<posdepparser::CStateItem>(AGENDA_SIZE);
      m_Beam = new CAgendaSimple<posdepparser::action::CScoredAction>(AGENDA_SIZE);
      m_weights = new posdepparser :: CWeight(sFeatureDBPath, bTrain,  posdepparser::DEP_TABLE_SIZE);
      m_delta_pos = new posdepparser :: CWeight("", bTrain, 512 );
      m_delta_dep = new posdepparser :: CWeight("", bTrain, 512 );
      m_nTrainingRound = 0; 
      m_nTotalErrors = 0;
//      m_nScoreIndex = CScore<posdepparser::SCORE_TYPE>::eNonAverage ;
      if (bTrain) m_nScoreIndex = CScore<posdepparser::SCORE_TYPE>::eNonAverage ; else m_nScoreIndex = CScore<posdepparser::SCORE_TYPE>::eAverage ;
   }
   ~CPosDepParser() {
      delete m_Agenda;
      delete m_Beam;
      delete m_weights;
      if (m_delta_pos) { delete m_delta_pos; m_delta_pos=0; }
      if (m_delta_dep) { delete m_delta_dep; m_delta_dep=0; }
   }
   CPosDepParser( CPosDepParser &posdepparser) : CPosDepParserBase(posdepparser) {
      assert(1==0);
   }

public:
   void parse( const CStringVector &sentence , CDependencyParse *retval, const CSTackFeatsVec  & stackfeats , int nBest=1 , posdepparser::SCORE_TYPE *scores=0 ) ;
   void train( const CDependencyParse &correct, const CSTackFeatsVec  & stackfeats , int round ) ;
   void extract_features( const CDependencyParse &input, const CSTackFeatsVec  & stackfeats ) ;


   void finishtraining() {
      static_cast<posdepparser::CWeight*>(m_weights)->computeAverageFeatureWeights(m_nTrainingRound);
      static_cast<posdepparser::CWeight*>(m_weights)->saveScores();
      std::cout << "Total number of training errors are: " << m_nTotalErrors << std::endl;
   }
   posdepparser::SCORE_TYPE getGlobalScore(const CDependencyParse &parsed);
   void updateScores(const CDependencyParse &parse, const CDependencyParse &correct, int round=0);

private:
   enum SCORE_UPDATE {eAdd=0, eSubtract};

   void work( const bool bTrain, const CStringVector &sentence , CDependencyParse *retval, const CDependencyParse &correct, const CSTackFeatsVec  & stackfeats, int nBest, posdepparser::SCORE_TYPE *scores ) ;

   inline void getOrUpdateStackScore( const posdepparser::CStateItem *item, CPackedScoreType<posdepparser::SCORE_TYPE, posdepparser::action::MAX> &retval, const unsigned &action, posdepparser::SCORE_TYPE amount=0, int round=0 );

   // update the built-in weight std::vector for this feature object specifically
   void updateScoresForStates(const CDependencyParse &tree,  const posdepparser::CStateItem *outout , const posdepparser::CStateItem *correct , posdepparser::SCORE_TYPE amount_add , posdepparser::SCORE_TYPE amount_subtract ) ;
   inline posdepparser::SCORE_TYPE updateScoreForState(const CDependencyParse &tree,  const posdepparser::CStateItem &from, const posdepparser::CStateItem *outout , const posdepparser::SCORE_TYPE &amount ) ;

   // helper method
   inline void reduce( const posdepparser::CStateItem *item, const CPackedScoreType<posdepparser::SCORE_TYPE, posdepparser::action::MAX> &scores ) ;
   inline void shift( const posdepparser::CStateItem *item, const CPackedScoreType<posdepparser::SCORE_TYPE, posdepparser::action::MAX> &scores) ;
   inline void shiftnone( const posdepparser::CStateItem *item, const CPackedScoreType<posdepparser::SCORE_TYPE, posdepparser::action::MAX> &scores );
   inline void arcleft( const posdepparser::CStateItem *item, const CPackedScoreType<posdepparser::SCORE_TYPE, posdepparser::action::MAX> &scores) ;
   inline void arcright( const posdepparser::CStateItem *item, const CPackedScoreType<posdepparser::SCORE_TYPE, posdepparser::action::MAX> &scores) ;
   inline void poproot( const posdepparser::CStateItem *item, const CPackedScoreType<posdepparser::SCORE_TYPE, posdepparser::action::MAX> &scores) ;

};

}; // namespace TARGET_LANGUAGE

#endif


