// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * conparser.cpp - the action based parser implementation       *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.12                        *
 *                                                              *
 ****************************************************************/

#include "conparser.h"
using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::conparser;

void CConParser::getLabeledBrackets(const CSentenceParsed &parse_tree, CStack<CLabeledBracket> &brackets) {
   std::vector<CLabeledBracket> vec;
   unsigned i;
   unsigned begin, end;
   unsigned long constituent;
   brackets.clear();
   for (i=0; i<parse_tree.nodes.size(); ++i) {
      const CCFGTreeNode &node = parse_tree.nodes[i];
      if (!node.is_constituent) {
         begin = node.token;
         end = begin;
      }
      else {
         begin = vec[node.left_child].begin;
         if (node.right_child == -1)
            end = vec[node.left_child].end;
         else
            end = vec[node.right_child].end;
      }
#ifdef NO_TEMP_CONSTITUENT
      constituent = node.constituent;
#else
      constituent = CConstituent::encodeTmp(node.constituent.code(), node.temp);
#endif
      vec.push_back(CLabeledBracket(begin, end, constituent));
      if (node.is_constituent)
         brackets.push(vec.back());
   } //for
}

/*---------------------------------------------------------------
 *
 * work - the working process shared by training and parsing
 *
 * Returns: makes a new instance of CSentenceParsed
 *
 *--------------------------------------------------------------*/

void CConParser::work(const CTwoStringVector &sentence, const CSentenceParsed &correct, CCoNLLOutput *o_conll){
	const int length = sentence.size();
	static int tmp_i,tmp_j;
	static CAction correct_action;
	m_lCache.clear();
	m_lWordLen.clear();
	for (tmp_i=0; tmp_i<length; tmp_i++ ) {
		m_lCache.push_back( CTaggedWord<CTag, TAG_SEPARATOR>(sentence[tmp_i].first , sentence[tmp_i].second) );
		m_lWordLen.push_back( getUTF8StringLength(sentence[tmp_i].first) );
	}
	std::vector<CStateItem> p(MAX_SENTENCE_SIZE*(2+UNARY_MOVES)+2);
	CStateItem *correctState = &p[0];
	//getLabeledBrackets(correct, correctState->gold_lb);
	correctState->clear();
	correctState->words = (&m_lCache);
	tmp_i = 1;
	while(true){
		correctState->StandardMove(correct, correct_action);
//		std::cerr<<correct_action<<std::endl;
		correctState->Move(&p[tmp_i],correct_action);
		correctState = &p[tmp_i];
		tmp_i ++;
		if (correctState == 0 || correctState->IsTerminated()) break; // while
	}

   correctState->GenerateStanford(sentence, o_conll);
	p.clear();
}

void CConParser::convert( const CSentenceParsed &correct, CCoNLLOutput *o_conll) {
	static CTwoStringVector sentence;
	UnparseSentence( &correct, &sentence );
	work(sentence, correct, o_conll);
};

