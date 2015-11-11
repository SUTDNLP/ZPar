// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * depparser_base.h - the definition for the dependency parser. *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.10                        *
 *                                                              *
 ****************************************************************/

#ifndef _POSDEPPARSER_BASE_H
#define _POSDEPPARSER_BASE_H

#include "posdepparser_base_include.h"

#include "posdepparser_weight_base.h"

namespace TARGET_LANGUAGE {

/*===============================================================
 *
 * CPosDepParserBase - the general dependency parser def
 *
 *==============================================================*/

class CPosDepParserBase {

protected:

   posdepparser::CWeightBase *m_weights;

   bool m_bTrain ; // the system runs either at training mode or decoding mode



public:
   // constructor and destructor
   CPosDepParserBase( std::string sFeatureDBPath , bool bTrain) : m_bTrain(bTrain)  {
      // do nothing
   }
   virtual ~CPosDepParserBase() {
      // do nothing
   }
   CPosDepParserBase( CPosDepParserBase &depparser) { 
      THROW("CPosDepParser does not support copy constructor!"); 
   }

public:
   void setRules(const bool &bRules) {
      m_weights->setRules(bRules);
   }


public:

   virtual void parse( const CStringVector &sentence , CDependencyParse *retval , const CSTackFeatsVec & stackfeats, int nBest=1, posdepparser::SCORE_TYPE *scores=0 ) = 0 ;
   virtual void train( const CDependencyParse &correct , const CSTackFeatsVec & stackfeats, int round ) = 0 ;


   virtual void finishtraining() = 0 ;  

};

}; // namespace TARGET_LANGUAGE

#endif


