// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * conparser.h - the definitions for the constituent parser.    *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.8                         *
 *                                                              *
 ****************************************************************/

#ifndef _CONPARSER_IMPL_H
#define _CONPARSER_IMPL_H

#include "conparser_base.h"

namespace TARGET_LANGUAGE {

/*===============================================================
 *
 * CConParser - the constituent parser
 *
 *==============================================================*/

class CConParser : public CConParserBase{ 

private:

   std::vector< CTaggedWord<CTag, TAG_SEPARATOR> > m_lCache;
   std::vector<unsigned long> m_lWordLen;

public:
   // constructor and destructor
   CConParser():CConParserBase("",false){}
   ~CConParser() {}
public:
   void convert(const CSentenceParsed &correct, CCoNLLOutput *o_conll);
private:
   enum SCORE_UPDATE {eAdd=0, eSubtract};

   void work(const CTwoStringVector &sentence, const CSentenceParsed &correct, CCoNLLOutput *o_conll);

   void getLabeledBrackets(const CSentenceParsed &parse_tree, CStack<CLabeledBracket> &brackets);

   void train( const CSentenceParsed &correct , int round ){};

   void finishtraining(){};
};

}; // namespace TARGET_LANGUAGE

#endif


