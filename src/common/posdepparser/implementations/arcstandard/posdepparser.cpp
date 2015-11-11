// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * depparser.cpp - the action based parser implementation       *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.12                        *
 *                                                              *
 ****************************************************************/

#include "posdepparser.h"
#include "posdepparser_weight.h"

using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::posdepparser;

const CWord g_emptyWord("");
const CTaggedWord<CTag, TAG_SEPARATOR> g_emptyTaggedWord;
const CTag g_noneTag = CTag::NONE;

#define cast_weights static_cast<CWeight*>(m_weights)
#define refer_or_allocate_tuple2(x, o1, o2) { if (amount == 0) x.refer(o1, o2); else x.allocate(o1, o2); }
#define refer_or_allocate_tuple3(x, o1, o2, o3) { if (amount == 0) x.refer(o1, o2, o3); else x.allocate(o1, o2, o3); }
#define refer_or_allocate_tuple4(x, o1, o2, o3, o4) { if (amount == 0) x.refer(o1, o2, o3, o4); else x.allocate(o1, o2, o3, o4); }
#define _conll_or_empty(x) (x == "_" ? "" : x)

/*===============================================================
 *
 * CPosDepParser - the depparser for TARGET_LANGUAGE 
 *
 *==============================================================*/

/*---------------------------------------------------------------
 * 
 * getOrUpdateStackScore - manipulate the score from stack 
 *
 *---------------------------------------------------------------*/

inline void CPosDepParser::getOrUpdateStackScore( const CStateItem *item, CPackedScoreType<SCORE_TYPE, action::MAX> &retval, const unsigned &action, SCORE_TYPE amount , int round ) {

   // stack
   const int &st0_index = item->stackempty() ? -1 : item->stacktop(); // stack top
   const int &st0r1_index = (st0_index!=-1&&st0_index+1<m_lCache.size())? st0_index+1 : -1; // the next word of st0_index
   const int &st0l1_index = (st0_index!=-1&&st0_index-1>=0)? st0_index-1 : -1; // the previous word of st0_index
   const int &st1_index = item->stacksize() <= 1 ? -1 : item->stackitem(item->stacksize()-2); // stack top head
   const int &st1r1_index = (st1_index!=-1&&st1_index+1<m_lCache.size())? st1_index+1 : -1; // the next word of st1_index
   const int &st1l1_index = (st1_index!=-1&&st1_index-1>=0)? st1_index-1 : -1; // the previous word of st1_index
   const int &st2_index = item->stacksize() <= 2 ? -1 : item->stackitem(item->stacksize()-3); // stack top 2 head
   const int &st0ld1_index = st0_index == -1 ? -1 : item->leftdep(st0_index); // leftmost dep
   const int &st0rd1_index = st0_index == -1 ? -1 : item->rightdep(st0_index); // rightmost dep
   const int &st0ld2_index = st0ld1_index == -1 ? -1 : item->sibling(st0ld1_index); // secondleftmost dep
   const int &st0rd2_index = st0rd1_index == -1 ? -1 : item->sibling(st0rd1_index); // secondrightmost dep
   const int &st1ld1_index = st1_index == -1 ? -1 : item->leftdep(st1_index); // leftmost dep
   const int &st1rd1_index = st1_index == -1 ? -1 : item->rightdep(st1_index); // rightmost dep
   const int &st1ld2_index = st1ld1_index == -1 ? -1 : item->sibling(st1ld1_index); // secondleftmost dep
   const int &st1rd2_index = st1rd1_index == -1 ? -1 : item->sibling(st1rd1_index); // secondrightmost dep

   //queue
   const int &n0_index = item->nextword()==m_lCache.size() ? -1 : item->nextword(); // next
   assert(n0_index<static_cast<int>(m_lCache.size())); // the next index shouldn't exceed sentence
   static int n1_index;
   static int n2_index;
   n1_index = (n0_index != -1 && n0_index+1<m_lCache.size()) ? n0_index+1 : -1 ;
   n2_index = (n0_index != -1 && n0_index+2<m_lCache.size()) ? n0_index+2 : -1 ;


   static int p1_index;
   static int p2_index;
   p1_index = (n0_index != -1 && n0_index-1>=0) ? n0_index-1 : -1 ;
   p2_index = (n0_index != -1 && n0_index-2>=0) ? n0_index-2 : -1 ;

   const CWord &st0_word = st0_index==-1 ?  g_emptyWord : m_lCache[st0_index];
   const CWord &st1_word = st1_index==-1 ?  g_emptyWord : m_lCache[st1_index];
   const CWord &st2_word = st2_index==-1 ?  g_emptyWord : m_lCache[st2_index];
   const CWord &st0ld1_word = st0ld1_index == -1 ?  g_emptyWord : m_lCache[st0ld1_index];
   const CWord &st0rd1_word = st0rd1_index == -1 ?  g_emptyWord : m_lCache[st0rd1_index];
   const CWord &st0ld2_word = st0ld2_index == -1 ?  g_emptyWord : m_lCache[st0ld2_index];
   const CWord &st0rd2_word = st0rd2_index == -1 ?  g_emptyWord : m_lCache[st0rd2_index];
   const CWord &st1ld1_word = st1ld1_index == -1 ?  g_emptyWord : m_lCache[st1ld1_index];
   const CWord &st1rd1_word = st1rd1_index == -1 ?  g_emptyWord : m_lCache[st1rd1_index];
   const CWord &st1ld2_word = st1ld2_index == -1 ?  g_emptyWord : m_lCache[st1ld2_index];
   const CWord &st1rd2_word = st1rd2_index == -1 ?  g_emptyWord : m_lCache[st1rd2_index];
   const CWord &n0_word = n0_index==-1 ?  g_emptyWord : m_lCache[n0_index];
   const CWord &n1_word = n1_index==-1 ?  g_emptyWord : m_lCache[n1_index];
   const CWord &n2_word = n2_index==-1 ?  g_emptyWord : m_lCache[n2_index];

   const CWord &p1_word = p1_index==-1 ?  g_emptyWord : m_lCache[p1_index];
   const CWord &p2_word = p2_index==-1 ?  g_emptyWord : m_lCache[p2_index];




   const CTag &st0_tag = st0_index==-1 ?  g_noneTag : CTag(item->pos(st0_index));
   const CTag &st1_tag = st1_index==-1 ?  g_noneTag : CTag(item->pos(st1_index));
   const CTag &st2_tag = st2_index==-1 ?  g_noneTag : CTag(item->pos(st2_index));

   //const CTag &st0r1_tag = st0r1_index==-1||st0r1_index>=n0_index?  g_noneTag : CTag(item->pos(st0r1_index));
   const CTag &st0l1_tag = st0l1_index==-1?  g_noneTag : CTag(item->pos(st0l1_index));
   const CTag &st1r1_tag = st1r1_index==-1?  g_noneTag : CTag(item->pos(st1r1_index));
   const CTag &st1l1_tag = st1l1_index==-1?  g_noneTag : CTag(item->pos(st1l1_index));
   const CTag &st0ld1_tag = st0ld1_index == -1 ?  g_noneTag : CTag(item->pos(st0ld1_index));
   const CTag &st0rd1_tag = st0rd1_index == -1 ?  g_noneTag : CTag(item->pos(st0rd1_index));
   const CTag &st0ld2_tag = st0ld2_index == -1 ?  g_noneTag : CTag(item->pos(st0ld2_index));
   const CTag &st0rd2_tag = st0rd2_index == -1 ?  g_noneTag : CTag(item->pos(st0rd2_index));
   const CTag &st1ld1_tag = st1ld1_index == -1 ?  g_noneTag : CTag(item->pos(st1ld1_index));
   const CTag &st1rd1_tag = st1rd1_index == -1 ?  g_noneTag : CTag(item->pos(st1rd1_index));
   const CTag &st1ld2_tag = st1ld2_index == -1 ?  g_noneTag : CTag(item->pos(st1ld2_index));
   const CTag &st1rd2_tag = st1rd2_index == -1 ?  g_noneTag : CTag(item->pos(st1rd2_index));

   const CTag &p1_tag = p1_index == -1 ?  g_noneTag : CTag(item->pos(p1_index));
   const CTag &p2_tag = p2_index == -1 ?  g_noneTag : CTag(item->pos(p2_index));


   const int &st0ld1_label = st0ld1_index == -1 ?  CDependencyLabel::NONE : item->label(st0ld1_index);
   const int &st0rd1_label = st0rd1_index == -1 ?  CDependencyLabel::NONE : item->label(st0rd1_index);
   const int &st0ld2_label = st0ld2_index == -1 ?  CDependencyLabel::NONE : item->label(st0ld2_index);
   const int &st0rd2_label = st0rd2_index == -1 ?  CDependencyLabel::NONE : item->label(st0rd2_index);
   const int &st1ld1_label = st1ld1_index == -1 ?  CDependencyLabel::NONE : item->label(st1ld1_index);
   const int &st1rd1_label = st1rd1_index == -1 ?  CDependencyLabel::NONE : item->label(st1rd1_index);
   const int &st1ld2_label = st1ld2_index == -1 ?  CDependencyLabel::NONE : item->label(st1ld2_index);
   const int &st1rd2_label = st1rd2_index == -1 ?  CDependencyLabel::NONE : item->label(st1rd2_index);


   const int st0st1_dist = encodeLinkDistance(st0_index, st1_index);

   const int st0_rarity = st0_index==-1?0:item->rightarity(st0_index);
   const int st0_larity = st0_index==-1?0:item->leftarity(st0_index);
   const int st1_rarity = st1_index==-1?0:item->rightarity(st1_index);
   const int st1_larity = st1_index==-1?0:item->leftarity(st1_index);

   const CSetOfTags<CDependencyLabel> &st0_rtagset = st0_index==-1?CSetOfTags<CDependencyLabel>():item->righttagset(st0_index);
   const CSetOfTags<CDependencyLabel> &st0_ltagset = st0_index==-1?CSetOfTags<CDependencyLabel>():item->lefttagset(st0_index);
   const CSetOfTags<CDependencyLabel> &st1_rtagset = st1_index==-1?CSetOfTags<CDependencyLabel>():item->righttagset(st1_index);
   const CSetOfTags<CDependencyLabel> &st1_ltagset = st1_index==-1?CSetOfTags<CDependencyLabel>():item->lefttagset(st1_index);


   static CTuple2<CWord, CTag> word_tag;
   static CTuple2<CWord, int> word_int;
   static CTuple2<CWord, CWord> word_word;
   static CTuple2<CTag, CTag> tag_tag;
   static CTuple2<CTag, int> tag_int;
   static CTuple3<CWord, CTag, CTag> word_tag_tag;
   static CTuple3<CTag, CTag, CTag> tag_tag_tag;
   static CTuple3<CWord, CWord, CTag> word_word_tag;
   static CTuple3<CWord, CWord, CWord> word_word_word;
   static CTuple4<CWord, CWord, CWord, CWord> word_word_word_word;
   static CTuple4<CWord, CWord, CTag, CTag> word_word_tag_tag;
   static CTuple3<CWord, CWord, int> word_word_int;
   static CTuple3<CWord, CTag, int> word_tag_int;
   static CTuple3<CTag, CTag, int> tag_tag_int;
   static CTuple2<CWord, CSetOfTags<CDependencyLabel> > word_tagset;
   static CTuple2<CTag, CSetOfTags<CDependencyLabel> > tag_tagset;
   static char letter;

   unsigned newaction = action;
   //if(action::getUnlabeledAction(action) == action::SHIFT)
	//{
	//   newaction = action::SHIFT;
	//}

   // single
   //S0
   if (st0_index != -1) {
      cast_weights->m_mapST0w.getOrUpdateScore( retval, st0_word, newaction, m_nScoreIndex, amount, round) ;
      cast_weights->m_mapST0t.getOrUpdateScore( retval, st0_tag, newaction, m_nScoreIndex, amount, round ) ;
      cast_weights->m_mapST0wt.getOrUpdateScore( retval, std::make_pair(st0_word, st0_tag), newaction, m_nScoreIndex, amount, round) ;
	  refer_or_allocate_tuple2(word_int, &st0_word, &st0_larity);
	  cast_weights->m_mapST0wLARITY.getOrUpdateScore( retval, word_int, newaction, m_nScoreIndex, amount, round) ;
	  refer_or_allocate_tuple2(tag_int, &st0_tag, &st0_larity);
	  cast_weights->m_mapST0tLARITY.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round) ;

   }

   //S1
   if (st1_index != -1) {
      cast_weights->m_mapST1w.getOrUpdateScore( retval, st1_word, newaction, m_nScoreIndex, amount, round) ;
      cast_weights->m_mapST1t.getOrUpdateScore( retval, st1_tag, newaction, m_nScoreIndex, amount, round ) ;
      cast_weights->m_mapST1wt.getOrUpdateScore( retval, std::make_pair(st1_word, st1_tag), newaction, m_nScoreIndex, amount, round) ;
	  refer_or_allocate_tuple2(word_int, &st1_word, &st1_larity);
	  cast_weights->m_mapST1wLARITY.getOrUpdateScore( retval, word_int, newaction, m_nScoreIndex, amount, round) ;
	  refer_or_allocate_tuple2(tag_int, &st1_tag, &st1_larity);
	  cast_weights->m_mapST1tLARITY.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round) ;
	  refer_or_allocate_tuple2(word_int, &st1_word, &st1_rarity);
	  cast_weights->m_mapST1wRARITY.getOrUpdateScore( retval, word_int, newaction, m_nScoreIndex, amount, round) ;
	  refer_or_allocate_tuple2(tag_int, &st1_tag, &st1_rarity);
	  cast_weights->m_mapST1tRARITY.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round) ;

   }


   //N0
   if (n0_index != -1) {
      cast_weights->m_mapN0w.getOrUpdateScore( retval, n0_word, newaction, m_nScoreIndex, amount, round ) ;
   }

   //N1
   if (n1_index != -1) {
      cast_weights->m_mapN1w.getOrUpdateScore( retval, n1_word, newaction, m_nScoreIndex, amount, round ) ;
   }


   //S0S1
   if (st1_index != -1) {
	   refer_or_allocate_tuple2(word_word, &st0_word, &st1_word);
	   cast_weights->m_mapST0wST1w.getOrUpdateScore( retval, word_word, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple2(tag_tag, &st0_tag, &st1_tag);
	   cast_weights->m_mapST0tST1t.getOrUpdateScore( retval, tag_tag, newaction, m_nScoreIndex, amount, round ) ;
	   cast_weights->m_mapST0wST1t.getOrUpdateScore( retval, std::make_pair(st0_word, st1_tag), newaction, m_nScoreIndex, amount, round) ;
	   cast_weights->m_mapST0tST1w.getOrUpdateScore( retval, std::make_pair(st1_word, st0_tag), newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_tag_tag, &st0_word, &st0_tag, &st1_tag);
	   cast_weights->m_mapST0wtST1t.getOrUpdateScore( retval, word_tag_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_tag_tag, &st1_word, &st0_tag, &st1_tag);
	   cast_weights->m_mapST0tST1wt.getOrUpdateScore( retval, word_tag_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_word_tag, &st0_word, &st1_word, &st0_tag);
	   cast_weights->m_mapST0wtST1w.getOrUpdateScore( retval, word_word_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_word_tag, &st0_word, &st1_word, &st1_tag);
	   cast_weights->m_mapST0wST1wt.getOrUpdateScore( retval, word_word_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple4(word_word_tag_tag, &st0_word, &st1_word, &st0_tag, &st1_tag);
	   cast_weights->m_mapST0wtST1wt.getOrUpdateScore( retval, word_word_tag_tag, newaction, m_nScoreIndex, amount, round) ;



	   refer_or_allocate_tuple2(word_int, &st0_word, &st0st1_dist);
	   cast_weights->m_mapST0wDist.getOrUpdateScore( retval, word_int, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple2(word_int, &st1_word, &st0st1_dist);
	   cast_weights->m_mapST1wDist.getOrUpdateScore( retval, word_int, newaction, m_nScoreIndex, amount, round ) ;
	   refer_or_allocate_tuple2(tag_int, &st0_tag, &st0st1_dist);
	   cast_weights->m_mapST0tDist.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple2(tag_int, &st1_tag, &st0st1_dist);
	   cast_weights->m_mapST1tDist.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_word_int, &st0_word, &st1_word, &st0st1_dist);
	   cast_weights->m_mapST0wST1wDist.getOrUpdateScore( retval, word_word_int, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(tag_tag_int, &st0_tag, &st1_tag, &st0st1_dist);
	   cast_weights->m_mapST0tST1tDist.getOrUpdateScore( retval, tag_tag_int, newaction, m_nScoreIndex, amount, round) ;



	   refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st1_tag, &st1l1_tag);
	   cast_weights->m_mapST0tST1tST1L1t.getOrUpdateScore( retval, tag_tag_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st1_tag, &st1r1_tag);
	   cast_weights->m_mapST0tST1tST1R1t.getOrUpdateScore( retval, tag_tag_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st1_tag, &st0l1_tag);
	   cast_weights->m_mapST0tST1tST0L1t.getOrUpdateScore( retval, tag_tag_tag, newaction, m_nScoreIndex, amount, round) ;
   }

   //S0N0
   if (st0_index != -1 && n0_index != -1) {
	   refer_or_allocate_tuple2(word_word, &st0_word, &n0_word);
	   cast_weights->m_mapST0wN0w.getOrUpdateScore( retval, word_word, newaction, m_nScoreIndex, amount, round) ;
	   cast_weights->m_mapST0tN0w.getOrUpdateScore( retval, std::make_pair(n0_word, st0_tag), newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_word_tag, &st0_word, &n0_word, &st0_tag);
	   cast_weights->m_mapST0wtN0w.getOrUpdateScore( retval, word_word_tag, newaction, m_nScoreIndex, amount, round) ;
   }

   //S0N1
   if (st0_index != -1 && n1_index != -1) {
	   refer_or_allocate_tuple2(word_word, &st0_word, &n1_word);
	   cast_weights->m_mapST0wN1w.getOrUpdateScore( retval, word_word, newaction, m_nScoreIndex, amount, round) ;
	   cast_weights->m_mapST0tN1w.getOrUpdateScore( retval, std::make_pair(n1_word, st0_tag), newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_word_tag, &st0_word, &n1_word, &st0_tag);
	   cast_weights->m_mapST0wtN1w.getOrUpdateScore( retval, word_word_tag, newaction, m_nScoreIndex, amount, round) ;
   }


   //S1N0
   if (st1_index != -1 && n0_index != -1) {
	   refer_or_allocate_tuple2(word_word, &st1_word, &n0_word);
	   cast_weights->m_mapST1wN0w.getOrUpdateScore( retval, word_word, newaction, m_nScoreIndex, amount, round) ;
	   cast_weights->m_mapST1tN0w.getOrUpdateScore( retval, std::make_pair(n0_word, st1_tag), newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_word_tag, &st1_word, &n0_word, &st1_tag);
	   cast_weights->m_mapST1wtN0w.getOrUpdateScore( retval, word_word_tag, newaction, m_nScoreIndex, amount, round) ;
   }

   //S1N1
   if (st1_index != -1 && n1_index != -1) {
	   refer_or_allocate_tuple2(word_word, &st1_word, &n1_word);
	   cast_weights->m_mapST1wN1w.getOrUpdateScore( retval, word_word, newaction, m_nScoreIndex, amount, round) ;
	   cast_weights->m_mapST1tN1w.getOrUpdateScore( retval, std::make_pair(n1_word, st1_tag), newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_word_tag, &st1_word, &n1_word, &st1_tag);
	   cast_weights->m_mapST1wtN1w.getOrUpdateScore( retval, word_word_tag, newaction, m_nScoreIndex, amount, round) ;
   }


   //N0N1
   if (n1_index != -1) {
	   refer_or_allocate_tuple2(word_word, &n0_word, &n1_word);
	   cast_weights->m_mapN0wN1w.getOrUpdateScore( retval, word_word, newaction, m_nScoreIndex, amount, round ) ;
   }

   //S0S1N0
   if (st1_index != -1 && n0_index != -1) {
	   refer_or_allocate_tuple3(word_tag_tag, &n0_word, &st0_tag, &st1_tag);
	   cast_weights->m_mapST0tST1tN0w.getOrUpdateScore( retval, word_tag_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_word_tag, &n0_word, &st1_word, &st0_tag);
	   cast_weights->m_mapST0tST1wN0w.getOrUpdateScore( retval, word_word_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_word_tag, &n0_word, &st0_word, &st1_tag);
	   cast_weights->m_mapST0wST1tN0w.getOrUpdateScore( retval, word_word_tag, newaction, m_nScoreIndex, amount, round) ;
   }

   //S0S1ST1LD1
   if(st1_index != -1 && st1ld1_index != -1)
   {
	   refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st1_tag, &st1ld1_tag);
	   cast_weights->m_mapST0tST1tST1LD1t.getOrUpdateScore( retval, tag_tag_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_tag_tag, &st0_word, &st1_tag, &st1ld1_tag);
	   cast_weights->m_mapST0wST1tST1LD1t.getOrUpdateScore( retval, word_tag_tag, newaction, m_nScoreIndex, amount, round) ;
   }

   //S0S1ST1RD1
   if(st1_index != -1 && st1rd1_index != -1)
   {
	   refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st1_tag, &st1rd1_tag);
	   cast_weights->m_mapST0tST1tST1RD1t.getOrUpdateScore( retval, tag_tag_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_tag_tag, &st0_word, &st1_tag, &st1rd1_tag);
	   cast_weights->m_mapST0wST1tST1RD1t.getOrUpdateScore( retval, word_tag_tag, newaction, m_nScoreIndex, amount, round) ;
   }

   //S0S1ST0LD1
   if(st1_index != -1 && st0ld1_index != -1)
   {
	   refer_or_allocate_tuple3(tag_tag_tag, &st1_tag, &st0_tag, &st0ld1_tag);
	   cast_weights->m_mapST1tST0tST0LD1t.getOrUpdateScore( retval, tag_tag_tag, newaction, m_nScoreIndex, amount, round) ;
	   refer_or_allocate_tuple3(word_tag_tag, &st1_word, &st0_tag, &st0ld1_tag);
	   cast_weights->m_mapST1wST0tST0LD1t.getOrUpdateScore( retval, word_tag_tag, newaction, m_nScoreIndex, amount, round) ;
   }

   //ST0LD1
   if(st0_index != -1 && st0ld1_index != -1)
   {
	  cast_weights->m_mapST0LD1w.getOrUpdateScore( retval, st0ld1_word, newaction, m_nScoreIndex, amount, round) ;
	  cast_weights->m_mapST0LD1t.getOrUpdateScore( retval, st0ld1_tag, newaction, m_nScoreIndex, amount, round ) ;
	  cast_weights->m_mapST0LD1wt.getOrUpdateScore( retval, std::make_pair(st0ld1_word, st0ld1_tag), newaction, m_nScoreIndex, amount, round) ;
   }

   //ST1LD1
   if(st1_index != -1 && st1ld1_index != -1)
   {
	  cast_weights->m_mapST1LD1w.getOrUpdateScore( retval, st1ld1_word, newaction, m_nScoreIndex, amount, round) ;
	  cast_weights->m_mapST1LD1t.getOrUpdateScore( retval, st1ld1_tag, newaction, m_nScoreIndex, amount, round ) ;
	  cast_weights->m_mapST1LD1wt.getOrUpdateScore( retval, std::make_pair(st1ld1_word, st1ld1_tag), newaction, m_nScoreIndex, amount, round) ;
   }


   //ST1RD1
   if(st1_index != -1 && st1rd1_index != -1)
   {
	  cast_weights->m_mapST1RD1w.getOrUpdateScore( retval, st1rd1_word, newaction, m_nScoreIndex, amount, round) ;
	  cast_weights->m_mapST1RD1t.getOrUpdateScore( retval, st1rd1_tag, newaction, m_nScoreIndex, amount, round ) ;
	  cast_weights->m_mapST1RD1wt.getOrUpdateScore( retval, std::make_pair(st1rd1_word, st1rd1_tag), newaction, m_nScoreIndex, amount, round) ;
   }


   //ST0ST0LD1ST0LD2
   if(st0_index != -1 && st0ld1_index != -1 && st0ld2_index != -1)
   {
	  refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st0ld1_tag, &st0ld2_tag);
	  cast_weights->m_mapST0tST0LD1tST0LD2t.getOrUpdateScore( retval, tag_tag_tag, newaction, m_nScoreIndex, amount, round) ;
   }

   //ST1ST1LD1ST1LD2
   if(st1_index != -1 && st1ld1_index != -1 && st1ld2_index != -1)
   {
	  refer_or_allocate_tuple3(tag_tag_tag, &st1_tag, &st1ld1_tag, &st1ld2_tag);
	  cast_weights->m_mapST1tST1LD1tST1LD2t.getOrUpdateScore( retval, tag_tag_tag, newaction, m_nScoreIndex, amount, round) ;
   }

   //ST1ST1RD1ST1RD2
   if(st1_index != -1 && st1rd1_index != -1 && st1rd2_index != -1)
   {
	  refer_or_allocate_tuple3(tag_tag_tag, &st1_tag, &st1rd1_tag, &st1rd2_tag);
	  cast_weights->m_mapST1tST1RD1tST1RD2t.getOrUpdateScore( retval, tag_tag_tag, newaction, m_nScoreIndex, amount, round) ;
   }


   //S0S1S2
   if(st2_index != -1)
   {
	   refer_or_allocate_tuple3(tag_tag_tag, &st2_tag, &st1_tag, &st0_tag);
	   cast_weights->m_mapST2tST1tST0t.getOrUpdateScore( retval, tag_tag_tag, newaction, m_nScoreIndex, amount, round) ;
   }


   // stacking features put here, users can also define own external features here, for example cluster features
   // only first order stacking features is enough, only contains head and pos tagging stacking
   // note that stacking features, the heads  are conll format
   if(m_stackfeats.size() == m_lCache.size() )
   {
	   if(st0_index != -1)
	   {

		   const int stackheadst0_1 = m_stackfeats[st0_index].m_feats.size() >= 2 ? atoi(m_stackfeats[st0_index].m_feats[1].c_str()) -1 : -2;
		   const int stackheadst1_1 = st1_index != -1 && m_stackfeats[st1_index].m_feats.size() >= 2 ? atoi(m_stackfeats[st1_index].m_feats[1].c_str()) -1 : -2;
		   // arcleft, 2; arcright, 3; st0root, 4; other 1
		   static int arctype1;
		   if(stackheadst0_1  == st1_index)
		   {
			   arctype1 = 3;
		   }
		   else if(stackheadst1_1  == st0_index)
		   {
			   arctype1 = 2;
		   }
		   else if(stackheadst0_1 == -1)
		   {
			   arctype1 = 4;
		   }
		   else
		   {
			   arctype1 = 1;
		   }

		   if(stackheadst0_1 != -2)
		   {
			   refer_or_allocate_tuple2(tag_int, &st0_tag, &arctype1);
			   cast_weights->m_mapStackingRIGHT1ST0t.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round ) ;
			   if(stackheadst1_1 != -2)
			   {
				   refer_or_allocate_tuple2(tag_int, &st1_tag, &arctype1);
				   cast_weights->m_mapStackingRIGHT1ST1t.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round ) ;
				   refer_or_allocate_tuple3(tag_tag_int, &st0_tag, &st1_tag, &arctype1);
				   cast_weights->m_mapStackingRIGHT1ST0tST1t.getOrUpdateScore( retval, tag_tag_int, newaction, m_nScoreIndex, amount, round ) ;
			   }
		   }

		   const int stackheadst0_2 = m_stackfeats[st0_index].m_feats.size() >= 4 ? atoi(m_stackfeats[st0_index].m_feats[3].c_str()) -1 : -2;
		   const int stackheadst1_2 = st1_index != -1 && m_stackfeats[st1_index].m_feats.size() >= 4 ? atoi(m_stackfeats[st1_index].m_feats[3].c_str()) -1 : -2;
		   // arcleft, 2; arcright, 3; st0root, 4; other 1
		   static int arctype2;
		   if(stackheadst0_2  == st1_index)
		   {
			   arctype2 = 3;
		   }
		   else if(stackheadst1_2  == st0_index)
		   {
			   arctype2 = 2;
		   }
		   else if(stackheadst0_2 == -1)
		   {
			   arctype2 = 4;
		   }
		   else
		   {
			   arctype2 = 1;
		   }

		   if(stackheadst0_2 != -2)
		   {
			   refer_or_allocate_tuple2(tag_int, &st0_tag, &arctype2);
			   cast_weights->m_mapStackingRIGHT2ST0t.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round ) ;
			   if(stackheadst1_2 != -2)
			   {
				   refer_or_allocate_tuple2(tag_int, &st1_tag, &arctype2);
				   cast_weights->m_mapStackingRIGHT2ST1t.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round ) ;
				   refer_or_allocate_tuple3(tag_tag_int, &st0_tag, &st1_tag, &arctype2);
				   cast_weights->m_mapStackingRIGHT2ST0tST1t.getOrUpdateScore( retval, tag_tag_int, newaction, m_nScoreIndex, amount, round ) ;
			   }

			   if(arctype1 == arctype2)
			   {
				   refer_or_allocate_tuple2(tag_int, &st0_tag, &arctype2);
				   cast_weights->m_mapStackingRIGHT1and2ST0t.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round ) ;
				   if(stackheadst1_2 != -2)
				   {
					   refer_or_allocate_tuple2(tag_int, &st1_tag, &arctype2);
					   cast_weights->m_mapStackingRIGHT1and2ST1t.getOrUpdateScore( retval, tag_int, newaction, m_nScoreIndex, amount, round ) ;
					   refer_or_allocate_tuple3(tag_tag_int, &st0_tag, &st1_tag, &arctype2);
					   cast_weights->m_mapStackingRIGHT1and2ST0tST1t.getOrUpdateScore( retval, tag_tag_int, newaction, m_nScoreIndex, amount, round ) ;
				   }
			   }
		   }

	   }
   }



   // POS Tagging features

   if(n0_index != -1 && (action == action::NO_ACTION || action::getUnlabeledAction(action) == action::SHIFT))
   {
	   // current


	   static unsigned long int last_start , last_length ;
	   static unsigned long int next_start , next_length ;
	   static unsigned long int start , end , length ;

	   // abstd::cout the words
	   start = m_wordIndexs[n0_index] ;
	   end = m_wordIndexs[n0_index+1]-1 ;
	   length = end-start+1 ;
	   last_start = p1_index > 0 ? m_wordIndexs[p1_index] : -1 ;
	   last_length = p1_index > 0 ? m_wordIndexs[p1_index+1]-m_wordIndexs[p1_index] : 99999 ;
	   next_start = n1_index > 0 ? m_wordIndexs[n1_index] : -1 ;
	   next_length = n1_index > 0 ? m_wordIndexs[n1_index+1]-m_wordIndexs[n1_index] : 99999 ;

	   // abstd::cout the chars
	   const CWord &first0_char = m_lCharCache[start] ;
	   const CWord &first1_char = start+1 <= end ? m_lCharCache[start+1] : g_emptyWord;
	   const CWord &first2_char = start+2 <= end ? m_lCharCache[start+2] : g_emptyWord;
	   const CWord &last0_char = m_lCharCache[end] ;
	   const CWord &last1_char = end-1 >= start ? m_lCharCache[end-1] : g_emptyWord;
	   const CWord &last2_char = end-2 >= start ? m_lCharCache[end-2] : g_emptyWord;
	   const CWord &next1_char = n1_index != -1 ?  m_lCharCache[end+1] : g_emptyWord;
	   const CWord &prev1_char = p1_index != -1 ?  m_lCharCache[start-1] : g_emptyWord;

	   const CWord &st0_firstchar = st0_index != -1 ?  m_lCharCache[m_wordIndexs[st0_index]] : g_emptyWord;
	   const CWord &st0_lastchar = st0_index != -1 ?  m_lCharCache[m_wordIndexs[st0_index+1]-1] : g_emptyWord;

#ifndef CHINESE
	   const CWord &first3_char = start+3 <= end ? m_lCharCache[start+3] : g_emptyWord;
	   const CWord &last3_char = end-3 >= start ? m_lCharCache[end-3] : g_emptyWord;
#endif

	   unsigned long long bContainHyphen = 1;
	   unsigned long long bContainNumber = 1;
	   unsigned long long bContainCapitalLetter = 1;

	   for (int i=start; i<=end; ++i ) {
	      letter = m_lCharCache[i].str().at(0);
	      if ( letter == '-' ) bContainHyphen = 2;
	      if ( letter >= '0' && letter <= '9' ) bContainNumber = 2;
	      if ( letter >= 'A' && letter <= 'Z' ) bContainCapitalLetter = 2;
	   }

#ifdef CHINESE
	   unsigned long long first0_char_cat = cast_weights->m_mapCharTagDictionary.lookup(first0_char) ;
	   unsigned long long last0_char_cat = cast_weights->m_mapCharTagDictionary.lookup(last0_char) ;
#endif
	   cast_weights->m_mapCurrentWord.getOrUpdateScore( retval, n0_word, action, m_nScoreIndex, amount, round);
	   cast_weights->m_mapLastTag.getOrUpdateScore( retval, p1_tag, action, m_nScoreIndex, amount, round);

	   refer_or_allocate_tuple2(tag_tag, &p2_tag, &p1_tag);
	   cast_weights->m_mapLastTwoTags.getOrUpdateScore( retval, tag_tag, action, m_nScoreIndex, amount, round);
	   if ( p1_index != -1 ) {

#ifdef CHINESE
	      if ( last_length <= 2 )
#endif
	      {
	          cast_weights->m_mapLastWord.getOrUpdateScore( retval, p1_word, action, m_nScoreIndex, amount, round);
	      }
#ifdef CHINESE
	      if ( last_length <= 2 )
#endif
	      {
	          cast_weights->m_mapLastTagCurrentWord.getOrUpdateScore( retval, std::make_pair(p1_word, p1_tag), action, m_nScoreIndex, amount, round);
	      }
#ifdef CHINESE
	      if ( length <= 2 )
	      {
	    	  refer_or_allocate_tuple2(word_word, &n0_word, &prev1_char);
	    	  cast_weights->m_mapCurentWordPrevChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	      }
	      if ( last_length <= 2 )
	      {
	    	  refer_or_allocate_tuple2(word_word, &p1_word, &first0_char);
	    	  cast_weights->m_mapLastWordFirstChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	      }
#endif
	   }


	   if ( n1_index != -1 ) {
#ifdef CHINESE
	      if ( next_length <= 2 )
#endif
	      {
	          cast_weights->m_mapNextWord.getOrUpdateScore( retval, n1_word, action, m_nScoreIndex, amount, round);
	      }

#ifdef CHINESE
	      if ( length <= 2 )
	      {
	    	  refer_or_allocate_tuple2(word_word, &n0_word, &next1_char);
	    	  cast_weights->m_mapCurentWordNextChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	      }
	      if ( next_length <= 2 )
	      {
	    	  refer_or_allocate_tuple2(word_word, &n1_word, &last0_char);
	    	  cast_weights->m_mapNextWordLastChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	      }
#endif
	   }

#ifdef CHINESE
	   if ( length == 1 ) {
		   if ( p1_index != -1 && n1_index != -1 )
		   {
			   refer_or_allocate_tuple3(word_word_word, &prev1_char, &first0_char, &next1_char);
			   cast_weights->m_mapOneCharWordTriChar.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round);
		   }
	   }
	   else {
	     cast_weights->m_mapFirstChar.getOrUpdateScore( retval, first0_char, action, m_nScoreIndex, amount, round);
	     cast_weights->m_mapLastChar.getOrUpdateScore( retval, last0_char, action, m_nScoreIndex, amount, round);
	     cast_weights->m_mapFirstCharCat.getOrUpdateScore( retval, first0_char_cat, action, m_nScoreIndex, amount, round);
	     cast_weights->m_mapLastCharCat.getOrUpdateScore( retval, last0_char_cat, action, m_nScoreIndex, amount, round);

	      for ( int j = 0 ; j < length ; ++ j ) {
	    	 const CWord &curChar = m_lCharCache[start+j];
	         if ( j > 0 && j < length-1 )
	         {
	        	 cast_weights->m_mapCharInWord.getOrUpdateScore( retval, curChar, action, m_nScoreIndex, amount, round);
	         }
	         if ( j > 0 ) {
	        	refer_or_allocate_tuple2(word_word, &curChar, &first0_char);
	            cast_weights->m_mapCharInWordByFirstChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	            if ( m_lCharCache[start+j] == m_lCharCache[start+j-1])
	              cast_weights->m_mapRepeatedChar.getOrUpdateScore( retval, curChar, action, m_nScoreIndex, amount, round);
	            if(j > 1 && m_lCharCache[start+j] == m_lCharCache[start+j-2])
	            {
	            	cast_weights->m_mapRepeated2Char.getOrUpdateScore( retval, curChar, action, m_nScoreIndex, amount, round);
	            }
	         }
	         if ( j < length-1 ) {
	             refer_or_allocate_tuple2(word_word, &curChar, &last0_char);
	             cast_weights->m_mapCharInWordByLastChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	         }

	      }
	   }
#endif

#ifndef CHINESE
	   // for english
       refer_or_allocate_tuple3(word_word_word, &p1_word, &n0_word, &n1_word);
       cast_weights->m_mapOneCharWordTriChar.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round);
       refer_or_allocate_tuple2(word_word, &p1_word, &n0_word);
       cast_weights->m_mapCharInWordByLastChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
       refer_or_allocate_tuple2(word_word, &n1_word, &n0_word);
       cast_weights->m_mapCharInWordByFirstChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
       refer_or_allocate_tuple2(word_word, &p1_word, &n1_word);
       cast_weights->m_mapNextWordLastChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);

#endif


	      //prefix
		 cast_weights->m_mapPrefixChar1.getOrUpdateScore( retval, first0_char, action, m_nScoreIndex, amount, round);
		 cast_weights->m_mapSuffixChar1.getOrUpdateScore( retval, last0_char, action, m_nScoreIndex, amount, round);
		 if(length > 1)
		 {
			 refer_or_allocate_tuple2(word_word, &first0_char, &first1_char);
			 cast_weights->m_mapPrefixChar2.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
			 refer_or_allocate_tuple2(word_word, &last0_char, &last1_char);
			 cast_weights->m_mapSuffixChar2.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
		 }
		 if(length > 2)
		 {
			 refer_or_allocate_tuple3(word_word_word, &first0_char, &first1_char, &first2_char);
			 cast_weights->m_mapPrefixChar3.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round);
			 refer_or_allocate_tuple3(word_word_word, &last0_char, &last1_char, &last2_char);
			 cast_weights->m_mapSuffixChar3.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round);
		 }

#ifndef CHINESE
        if(length > 3)
         {
             refer_or_allocate_tuple4(word_word_word_word, &first0_char, &first1_char, &first2_char, &first3_char);
             cast_weights->m_mapPrefixChar4.getOrUpdateScore( retval, word_word_word_word, action, m_nScoreIndex, amount, round);
             refer_or_allocate_tuple4(word_word_word_word, &last0_char, &last1_char, &last2_char, &last3_char);
             cast_weights->m_mapSuffixChar4.getOrUpdateScore( retval, word_word_word_word, action, m_nScoreIndex, amount, round);
         }
#endif

        cast_weights->m_mapContainHyphen.getOrUpdateScore( retval, bContainHyphen, action, m_nScoreIndex, amount, round);
        cast_weights->m_mapContainNumber.getOrUpdateScore( retval, bContainNumber, action, m_nScoreIndex, amount, round);
        cast_weights->m_mapContainCapitalLetter.getOrUpdateScore( retval, bContainCapitalLetter, action, m_nScoreIndex, amount, round);


#ifdef CHINESE
	      unsigned long long normalizedlength = length < 5 ? length : 5;
	      cast_weights->m_mapNormalizedLength.getOrUpdateScore( retval, normalizedlength, action, m_nScoreIndex, amount, round);
#endif
	      //dictionary features
	      if(cast_weights->m_mapWordFrequency.find(n0_word, 0)  >= cast_weights->m_nMaxWordFrequency/5000 + 5)
	      {
	    	  for (int label=CTag::FIRST; label<CTag::COUNT; ++label) {
	    		  unsigned long long labelIndex = label;
	    		  if(cast_weights->m_mapTagDictionary.lookup(n0_word, CTag(label)) )
	    		  {
	    			  cast_weights->m_mapWordLabelInDict.getOrUpdateScore( retval, labelIndex, action, m_nScoreIndex, amount, round);
	    		  }
	    	  }
	      }

#ifdef CHINESE
	      if(cast_weights->m_mapCharFrequency.find(first0_char, 0)  >= cast_weights->m_nMaxWordFrequency/5000 + 10)
	      {
	    	  for (int label=CTag::FIRST; label<CTag::COUNT; ++label) {
	    		  unsigned long long labelIndex = label;
	    		  if(cast_weights->m_mapCharTagDictionary.lookup(first0_char, CTag(label)))
	    		  {
	    			  cast_weights->m_mapFirstCharLabelInDict.getOrUpdateScore( retval, labelIndex, action, m_nScoreIndex, amount, round);
	    		  }
	    	  }
	      }

	      if(cast_weights->m_mapCharFrequency.find(last0_char, 0)  >= cast_weights->m_nMaxWordFrequency/5000 + 10)
	      {
	    	  for (int label=CTag::FIRST; label<CTag::COUNT; ++label) {
	    		  unsigned long long labelIndex = label;
	    		  if(cast_weights->m_mapCharTagDictionary.lookup(last0_char, CTag(label)))
	    		  {
	    			  cast_weights->m_mapLastCharLabelInDict.getOrUpdateScore( retval, labelIndex, action, m_nScoreIndex, amount, round);
	    		  }
	    	  }
	      }
#endif
	      if (st0_index != -1) {
	         //cast_weights->m_mapPOSST0w.getOrUpdateScore( retval, st0_word, action, m_nScoreIndex, amount, round) ;
	         //cast_weights->m_mapPOSST0t.getOrUpdateScore( retval, st0_tag, action, m_nScoreIndex, amount, round ) ;
	         //cast_weights->m_mapPOSST0wt.getOrUpdateScore( retval, std::make_pair(st0_word, st0_tag), action, m_nScoreIndex, amount, round) ;
	         //cast_weights->m_mapPOSST0tCurWord.getOrUpdateScore( retval, std::make_pair(n0_word, st0_tag), action, m_nScoreIndex, amount, round) ;
	         //refer_or_allocate_tuple2(word_word, &st0_word, &n0_word);
	          //cast_weights->m_mapPOSST0wCurWord.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
#ifdef CHINESE
	         refer_or_allocate_tuple2(word_word, &st0_firstchar, &n0_word);
	         cast_weights->m_mapPOSST0fcCurWord.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
	         refer_or_allocate_tuple2(word_word, &st0_lastchar, &n0_word);
	         cast_weights->m_mapPOSST0lcCurWord.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
#endif
	         if(st0ld1_index != -1)
	         {
	        	 refer_or_allocate_tuple2(tag_tag, &st0_tag, &st0ld1_tag);
	        	 cast_weights->m_mapPOSST0tST0LD1t.getOrUpdateScore( retval, tag_tag, action, m_nScoreIndex, amount, round) ;
	        	 refer_or_allocate_tuple3(word_tag_tag, &st0_word, &st0_tag, &st0ld1_tag);
	        	 cast_weights->m_mapPOSST0wtST0LD1t.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
	         }

	         if(st0rd1_index != -1)
	         {
	        	 refer_or_allocate_tuple2(tag_tag, &st0_tag, &st0rd1_tag);
	        	 cast_weights->m_mapPOSST0tST0RD1t.getOrUpdateScore( retval, tag_tag, action, m_nScoreIndex, amount, round) ;
	        	 refer_or_allocate_tuple3(word_tag_tag, &st0_word, &st0_tag, &st0rd1_tag);
	        	 cast_weights->m_mapPOSST0wtST0RD1t.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
	         }
	      }

	   //stacking features put here, users can define own features here
	   if(m_stackfeats.size() == m_lCache.size())
	   {
		   const CTag &stacktag1 = m_stackfeats[n0_index].m_feats.size() >= 1 ? CTag(m_stackfeats[n0_index].m_feats[0]) : g_noneTag;
		   if(stacktag1 != g_noneTag)
		   {
			   cast_weights->m_mapStackingPOS1.getOrUpdateScore( retval, stacktag1, action, m_nScoreIndex, amount, round);
			   cast_weights->m_mapStackingPOS1CurrentWord.getOrUpdateScore( retval, std::make_pair(n0_word, stacktag1), action, m_nScoreIndex, amount, round);
		   }

		   const CTag &stacktag2 = m_stackfeats[n0_index].m_feats.size() >= 3 ? CTag(m_stackfeats[n0_index].m_feats[2]) : g_noneTag;
		   if(stacktag2 != g_noneTag)
		   {
			   cast_weights->m_mapStackingPOS2.getOrUpdateScore( retval, stacktag2, action, m_nScoreIndex, amount, round);
			   cast_weights->m_mapStackingPOS2CurrentWord.getOrUpdateScore( retval, std::make_pair(n0_word, stacktag2), action, m_nScoreIndex, amount, round);

			   if(stacktag2 == stacktag1)
			   {
				   cast_weights->m_mapStackingPOS1and2.getOrUpdateScore( retval, stacktag2, action, m_nScoreIndex, amount, round);
				   cast_weights->m_mapStackingPOS1and2CurrentWord.getOrUpdateScore( retval, std::make_pair(n0_word, stacktag2), action, m_nScoreIndex, amount, round);
			   }
		   }
	   }
   }

}

/*---------------------------------------------------------------
 *
 * getGlobalScore - get the score of a parse tree
 *
 * Inputs: parse graph
 *
 *---------------------------------------------------------------*/

SCORE_TYPE CPosDepParser::getGlobalScore(const CDependencyParse &parsed) {
   THROW("posposdepparser.cpp: getGlobalScore unsupported");
}

/*---------------------------------------------------------------
 *
 * updateScores - update the score std::vector 
 *
 * This method is different from updateScoreVector in that
 * 1. It is for external call
 * 2. The tagging sequences for parsed and correct may differ
 *
 * Inputs: the parsed and the correct example
 *
 *---------------------------------------------------------------*/

void CPosDepParser::updateScores(const CDependencyParse & parsed , const CDependencyParse & correct , int round ) {
   THROW("posdepparser.cpp: updateScores unsupported");
}

/*---------------------------------------------------------------
 *
 * updateScoreForState - update a single positive or negative outout
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::updateScoreForState( const CStateItem &from, const CStateItem *outout , const SCORE_TYPE &amount ) {
   static CStateItem item(&m_lCache);
   item.clear();
   static unsigned action;
   static CPackedScoreType<SCORE_TYPE, action::MAX> empty;
   item = from;
   //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
   while ( item != *outout ) {
      action = item.FollowMove( outout );
      if(item.m_nActionSize >= outout->m_nActionSize || action != outout->m_Action[item.m_nActionSize])
      {
    	  std::cout << "error" << std::endl;
      }
      //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
      getOrUpdateStackScore( &item, empty, action, amount, m_nTrainingRound );
#ifdef LABELED
//      if ( action::getLabel(action) )
//         getOrUpdateStackScore( &item, empty, action::getUnlabeledAction(action), amount, m_nTrainingRound );
#endif
   item.Move( action );
      //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
   }
}

/*---------------------------------------------------------------
 *
 * updateScoresForStates - update scores for states
 *
 *--------------------------------------------------------------*/

void CPosDepParser::updateScoresForStates( const CStateItem *outout , const CStateItem *correct , SCORE_TYPE amount_add, SCORE_TYPE amount_subtract ) {

   // do not update those steps where they are correct
   static CStateItem item(&m_lCache);
   static unsigned action, correct_action;
   item.clear();
   while ( item != *outout ) {
      action = item.FollowMove( outout );
      if(item.m_nActionSize >= outout->m_nActionSize || action != outout->m_Action[item.m_nActionSize])
      {
    	  std::cout << "error" << std::endl;
      }
      correct_action = item.FollowMove( correct );
      if(item.m_nActionSize >= correct->m_nActionSize || correct_action != correct->m_Action[item.m_nActionSize])
      {
    	  std::cout << "error" << std::endl;
      }
      if ( action == correct_action )
         item.Move( action );
      else break;
   }

   // for the necessary information for the correct and outout burster
   updateScoreForState( item, correct , amount_add ) ;
   updateScoreForState( item, outout , amount_subtract ) ;

   m_nTotalErrors++;
}



/*---------------------------------------------------------------
 *
 * arcleft - helping function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::arcleft( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
   static action::CScoredAction scoredaction;
   static unsigned label;
#ifdef LABELED
   for (label=CDependencyLabel::FIRST; label<CDependencyLabel::COUNT; ++label) {
      //if ( !m_weights->rules() || canAssignLabel(m_lCache, item->size(), item->stacktop(), label) ) {
	   //const int &st0_index = item->stackempty() ? -1 : item->stacktop(); // stack top
	   //const int &st1_index = item->stacksize() <= 1 ? -1 : item->stackitem(item->stacksize()-2); // stack top head
	   //const int &st0_tag_code = st0_index==-1 ?  g_noneTag.code() : item->pos(st0_index);
	   //const int &st1_tag_code = st1_index==-1 ?  g_noneTag.code() : item->pos(st1_index);

	   //unsigned long tagpairindex = st0_tag_code*CTag::COUNT + st1_tag_code;
	   //unsigned long index = (st0_tag_code*CTag::COUNT + st1_tag_code)*CDependencyLabel::COUNT + label;


	   //if( cast_weights->m_mapTagPairDictionary.find(tagpairindex, 0) < cast_weights->m_nMaxWordFrequency/5000 + 20
		//	   || cast_weights->m_mapTagPairLabelDictionary.find(index, 0) > 0)
	   //{

		   //if(cast_weights->m_mapTagPairLabelDictionary.element(index))
		   //{
		 //   std::cout << cast_weights->m_mapTagPairLabelDictionary.find(index, 0) << " " << cast_weights->m_nMaxWordFrequency/5000+10 << std::endl;
		   //}
         scoredaction.action = action::encodeAction(action::ARC_LEFT, label);
         scoredaction.score = item->score + scores[scoredaction.action];
                               //+scores[action::ARC_LEFT];
         m_Beam->insertItem(&scoredaction);
	  // }
      //}
   }
#else
   scoredaction.action = action::ARC_LEFT;
   scoredaction.score = item->score + scores[scoredaction.action];
      m_Beam->insertItem(&scoredaction);
#endif
}

/*---------------------------------------------------------------
 *
 * arcright - helping function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::arcright( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
   static action::CScoredAction scoredaction;
   static unsigned label;
#ifdef LABELED
   for (label=CDependencyLabel::FIRST; label<CDependencyLabel::COUNT; ++label) {
      //if ( !m_weights->rules() || canAssignLabel(m_lCache, item->stacktop(), item->size(), label) ) {
	   //const int &st0_index = item->stackempty() ? -1 : item->stacktop(); // stack top
	   //const int &st1_index = item->stacksize() <= 1 ? -1 : item->stackitem(item->stacksize()-2); // stack top head
	   //const int &st0_tag_code = st0_index==-1 ?  g_noneTag.code() : item->pos(st0_index);
	   //const int &st1_tag_code = st1_index==-1 ?  g_noneTag.code() : item->pos(st1_index);

	   //unsigned long tagpairindex = st1_tag_code*CTag::COUNT + st0_tag_code;
	   //unsigned long index = (st1_tag_code*CTag::COUNT + st0_tag_code)*CDependencyLabel::COUNT + label;

	   //if( cast_weights->m_mapTagPairDictionary.find(tagpairindex, 0) < cast_weights->m_nMaxWordFrequency/5000 + 20
		//	   || cast_weights->m_mapTagPairLabelDictionary.find(index, 0) > 0)
	   //{
         scoredaction.action = action::encodeAction(action::ARC_RIGHT, label);
         scoredaction.score = item->score + scores[scoredaction.action];
                              //+scores[action::ARC_RIGHT];
         m_Beam->insertItem(&scoredaction);
      //}
	   //}
   }
#else
   scoredaction.action = action::ARC_RIGHT;
   scoredaction.score = item->score + scores[scoredaction.action];
   m_Beam->insertItem(&scoredaction);
#endif
}

/*---------------------------------------------------------------
 *
 * shift - help function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::shift( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
   static action::CScoredAction scoredaction;
   // update stack score
   static unsigned label;

   for (label=CTag::FIRST; label<CTag::COUNT; ++label) {
	   //if ( !m_weights->rules() || canAssignLabel(m_lCache, item->stacktop(), item->size(), label) ) {
	   const int &n0_index = item->nextword()==m_lCache.size() ? -1 : item->nextword(); // next
	   const CWord &n0_word = n0_index==-1 ?  g_emptyWord : m_lCache[n0_index];
	   if(PENN_TAG_CLOSED[label] && !cast_weights->m_mapTagDictionary.lookup(n0_word, CTag(label)))
	   {
		   continue;
	   //}
	   }
	   if(cast_weights->m_mapWordFrequency.find(n0_word, 0)  < cast_weights->m_nMaxWordFrequency/5000 + 5
			   || cast_weights->m_mapTagDictionary.lookup(n0_word, CTag(label)))
	   {
		   scoredaction.action = action::encodeAction(action::SHIFT, label);
		   scoredaction.score = item->score + scores[scoredaction.action];
		   m_Beam->insertItem(&scoredaction);
	   //}
	   }
    }
}

/*---------------------------------------------------------------
 *
 * poproot - help function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::poproot( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
   static action::CScoredAction scoredaction;
   // update stack score
   //const int &st0_index = item->stackempty() ? -1 : item->stacktop(); // stack top
   //const int &st0_tag_code = st0_index==-1 ?  g_noneTag.code() : item->pos(st0_index);
   //unsigned long tagpairindex = g_noneTag.code()*CTag::COUNT + st0_tag_code;
   //unsigned long index = (g_noneTag.code()*CTag::COUNT + st0_tag_code)*CDependencyLabel::COUNT + CDependencyLabel::ROOT;
   //if( cast_weights->m_mapTagPairDictionary.find(tagpairindex, 0) < cast_weights->m_nMaxWordFrequency/5000 + 20
	//	   || cast_weights->m_mapTagPairLabelDictionary.find(index, 0) > 0)
   //{
	   scoredaction.action = action::POP_ROOT;
	   scoredaction.score = item->score + scores[scoredaction.action];
	   m_Beam->insertItem(&scoredaction);
   //}
}
   

/*---------------------------------------------------------------
 *
 * work - the working process shared by training and parsing
 *
 * Returns: makes a new instance of CDependencyParse 
 *
 *--------------------------------------------------------------*/

void CPosDepParser::work( const bool bTrain , const CStringVector &sentence , CDependencyParse *retval , const CDependencyParse &correct, const CSTackFeatsVec  & stackfeats , int nBest , SCORE_TYPE *scores ) {

#ifdef DEBUG
   clock_t total_start_time = clock();
#endif
   static int index;
   const int length = sentence.size() ; 

   const CStateItem *pGenerator ;
   static CStateItem pCandidate(&m_lCache) ;

   // used only for training
   static bool bCorrect ;  // used in learning for early update
   //static bool bContradictsRules;
   static CStateItem correctState(&m_lCache) ;
   static CPackedScoreType<SCORE_TYPE, action::MAX> packed_scores;

   ASSERT(length<MAX_SENTENCE_SIZE, "The size of the sentence is larger than the system configuration.");

   TRACE("Initialising the decoding process...") ;
   // initialise word cache
   //bContradictsRules = false;
   m_lCache.clear();
   m_lCharCache.clear();
   m_wordIndexs.clear();
   if(!stackfeats.empty())
   {
	   assert(stackfeats.size() == length);
   }
   m_stackfeats.clear();
   static std::vector< std::string > currentwordchars;
   for ( index=0; index<length; ++index ) {
      m_lCache.push_back( sentence[index] );
      if(!stackfeats.empty())
      {
    	  m_stackfeats.push_back(stackfeats[index]);
      }
      currentwordchars.clear();
      getCharactersFromUTF8String(sentence[index], &currentwordchars);
      m_wordIndexs.push_back(m_lCharCache.size());

      for(int idx = 0; idx < currentwordchars.size(); idx++)
      {
    	  m_lCharCache.push_back(currentwordchars[idx]);
      }
      // filter std::cout training examples with rules
      if (bTrain && m_weights->rules()) {
         // the root
      //   if ( correct[index].head == DEPENDENCY_LINK_NO_HEAD && canBeRoot(m_lCache[index].tag.code())==false) {
      //      TRACE("Rule contradiction: " << m_lCache[index].tag.code() << " can be root.");
      //      bContradictsRules = true;
      //   }
         // head left
      //   if ( correct[index].head < index && hasLeftHead(m_lCache[index].tag.code())==false) {
      //      TRACE("Rule contradiction: " << m_lCache[index].tag.code() << " has left head.");
     //       bContradictsRules = true;
     //    }
         // head right
      //  if ( correct[index].head > index && hasRightHead(m_lCache[index].tag.code())==false) {
      //      TRACE("Rule contradiction: " << m_lCache[index].tag.code() << " has right head.");
      //      bContradictsRules = true;
      //  }
      }
   }

   m_wordIndexs.push_back(m_lCharCache.size());
   /*
   {
	   assert(m_lCache.size() == m_wordIndexs.size()-1);
	   assert(m_wordIndexs[m_wordIndexs.size()-1] == m_lCharCache.size());
	   for(index=0; index<length; ++index)
	   {
		   std::cout << m_lCache[index].str() << "//";
		   for(int idx = m_wordIndexs[index]; idx < m_wordIndexs[index+1]; idx++)
		   {
			   std::cout << m_lCharCache[idx].str();
		   }

		   std::cout << "  ";
	   }

	   std::cout << std::endl;
   }
	*/
   // initialise agenda
   m_Agenda->clear();
   pCandidate.clear();                          // restore state using clean
   m_Agenda->pushCandidate(&pCandidate);           // and push it back
   m_Agenda->nextRound();                       // as the generator item
   if (bTrain) correctState.clear();


#ifdef LABELED
   unsigned long label;
   m_lCacheLabel.clear();
   if (bTrain) {
      for (index=0; index<length; ++index) {
         m_lCacheLabel.push_back(CDependencyLabel(correct[index].label));
         //std::cout << index << ":\t" << correct[index].label << "...." << m_lCacheLabel[index].str() << std::endl;
         //if (m_weights->rules() && !canAssignLabel(m_lCache, correct[index].head, index, m_lCacheLabel[index])) {
         //   TRACE("Rule contradiction: " << correct[index].label << " on link head " << m_lCache[correct[index].head].tag.code() << " dep " << m_lCache[index].tag.code());
         //   bContradictsRules = true;
         //}
      }
   }
#endif

   // skip the training example if contradicts
   //if (bTrain && m_weights->rules() && bContradictsRules) {
  //    std::cout << "Skipping training example because it contradicts rules..." <<std::endl;
  //    return;
  // }

   TRACE("Decoding started"); 
   // loop with the next word to process in the sentence
   for (index=0; index<length*2; ++index) {
      
      if (bTrain) bCorrect = false ; 

      // none can this find with pruning ???
      if (m_Agenda->generatorSize() == 0) {
         WARNING("parsing failed"); 
         return;
      }

      pGenerator = m_Agenda->generatorStart();
      // iterate generators
      for (int j=0; j<m_Agenda->generatorSize(); ++j) {

         // for the state items that already contain all words
         m_Beam->clear();
         packed_scores.reset();
         getOrUpdateStackScore( pGenerator, packed_scores, action::NO_ACTION );

		 if ( pGenerator->stacksize()>1 )
		 {
			 arcright(pGenerator, packed_scores) ;
			 if(pGenerator->stacktop() == pGenerator->nextword()-1)
			 {
				 arcleft(pGenerator, packed_scores) ;
			 }
		 }

		 if ( pGenerator->nextword() == length && pGenerator->stacksize() == 1) {
			 poproot(pGenerator, packed_scores);
		 }

		 if ( pGenerator->nextword() < length )
		 {
			 shift(pGenerator, packed_scores) ;
		 }

         // insert item
         for (unsigned i=0; i<m_Beam->size(); ++i) {
            pCandidate = *pGenerator;
            pCandidate.score = m_Beam->item(i)->score;
            pCandidate.Move( m_Beam->item(i)->action );
            m_Agenda->pushCandidate(&pCandidate);
         }

         CStateItem * bestitem = m_Agenda->bestGenerator();

         if (bTrain && *pGenerator == correctState) {
            bCorrect = true ;
         }
         pGenerator = m_Agenda->generatorNext() ;



      }
      // when we are doing training, we need to consider the standard move and update
      if (bTrain) {
#ifdef EARLY_UPDATE
         if (!bCorrect) {
            TRACE("Error at the "<<correctState.nextword()<<"th word; total is "<<correct.size())
            CStateItem * bestitem = m_Agenda->bestGenerator();
            if(*bestitem == correctState)
            {
            	std::cout << "error" << std::endl;
            }
            updateScoresForStates(bestitem, &correctState, 1, -1) ;
#ifndef LOCAL_LEARNING
            return ;
#else
            m_Agenda->clearCandidates();
            m_Agenda->pushCandidate(&correctState);
#endif
         }
#endif

#ifdef EARLY_UPDATE
         if (bCorrect)
#endif
         {
#ifdef LABELED
            correctState.StandardMoveStep(correct, m_lCacheLabel);
#else
            correctState.StandardMoveStep(correct);
#endif
         }
#ifdef LOCAL_LEARNING
         ++m_nTrainingRound; // each training round is one transition-action
#endif
      } 
      
      m_Agenda->nextRound(); // move round
   }

   if (bTrain) {
      correctState.StandardFinish(); // pop the root that is left
      // then make sure that the correct item is stack top finally
      if ( *(m_Agenda->bestGenerator()) != correctState ) {
         TRACE("The  best item is not the correct one")
         updateScoresForStates(m_Agenda->bestGenerator(), &correctState, 1, -1) ; 
         return ;
      }
   } 

   TRACE("Outputing sentence");
   m_Agenda->sortGenerators();
   for (int i=0; i<std::min(m_Agenda->generatorSize(), nBest); ++i) {
      pGenerator = m_Agenda->generator(i) ; 
      if (pGenerator) {
         pGenerator->GenerateTree( sentence , retval[i] ) ; 
         if (scores) scores[i] = pGenerator->score;
      }
   }
   TRACE("Done, the highest score is: " << m_Agenda->bestGenerator()->score ) ;
   TRACE("The total time spent: " << double(clock() - total_start_time)/CLOCKS_PER_SEC) ;
}

/*---------------------------------------------------------------
 *
 * parse - do dependency parsing to a sentence
 *
 * Returns: makes a new instance of CDependencyParse 
 *
 *--------------------------------------------------------------*/

void CPosDepParser::parse( const CStringVector &sentence , CDependencyParse *retval, const CSTackFeatsVec  & stackfeats , int nBest , SCORE_TYPE *scores ) {

   static CDependencyParse empty ;


   for (int i=0; i<nBest; ++i) {
      // clear the outout sentences
      retval[i].clear();
      if (scores) scores[i] = 0; //pGenerator->score;
   }

   work(false, sentence, retval, empty, stackfeats, nBest, scores ) ;

}

/*---------------------------------------------------------------
 *
 * train - train the models with an example
 *
 *---------------------------------------------------------------*/

void CPosDepParser::train( const CDependencyParse &correct, const CSTackFeatsVec  & stackfeats , int round ) {

   static CStringVector sentence ;
   static CDependencyParse outout ; 
   static CTwoStringVector wordtags;

#ifndef FRAGMENTED_TREE
   assert( IsProjectiveDependencyTree(correct) ) ;
#endif
   UnparseSentence( &correct, &sentence ) ;
   UnparseSentence( &correct, &wordtags ) ;

   // Updates that are common for all example
   for ( unsigned i=0; i<wordtags.size(); ++i ) {

      const CWord &word = wordtags.at(i).first ;
      unsigned long tag = CTag( wordtags.at(i).second ).code() ;

      static CStringVector chars;
      static unsigned j;
      static unsigned local_size;
      chars.clear();
      getCharactersFromUTF8String(wordtags.at(i).first, &chars);
      local_size = chars.size();

      cast_weights->m_mapWordFrequency[word]++;
      if (cast_weights->m_mapWordFrequency[word] > cast_weights->m_nMaxWordFrequency)
    	  cast_weights->m_nMaxWordFrequency = cast_weights->m_mapWordFrequency[word];

      cast_weights->m_mapTagDictionary.add(word, tag);
      for ( j=0 ; j<local_size; ++j ) {
    	  cast_weights->m_mapCharTagDictionary.add(CWord(chars[j]), tag) ;
    	  cast_weights->m_mapCharFrequency[CWord(chars[j])]++;
      }

      int head = correct.at(i).head;
      int label = CDependencyLabel(correct.at(i).label).code();

      unsigned long headtag = head != -1 ? CTag( wordtags.at(head).second ).code() : g_noneTag.code();

      // label = ivalue % CDependencyLabel::COUNT; tag = (ivalue / CDependencyLabel::COUNT) % CTag::COUNT
      // headtag = (ivalue / CDependencyLabel::COUNT) / CTag::COUNT
      cast_weights->m_mapTagPairLabelDictionary[(headtag*CTag::COUNT + tag)*CDependencyLabel::COUNT + label]++;
      cast_weights->m_mapTagPairDictionary[headtag*CTag::COUNT + tag]++;

   }



   // The following code does update for each processing stage
#ifndef LOCAL_LEARNING
   ++m_nTrainingRound;
   ASSERT(m_nTrainingRound == round, "Training round error") ;
#endif
   work( true , sentence , &outout , correct , stackfeats, 1 , 0 ) ;

};

/*---------------------------------------------------------------
 *
 * extract_features - extract features from an example (counts recorded to parser model as weights)
 *
 *---------------------------------------------------------------*/

void CPosDepParser::extract_features(const CDependencyParse &input, const CSTackFeatsVec  & stackfeats) {

   CStateItem item(&m_lCache);
   CStateItem tmp(&m_lCache);
   unsigned action;
   CPackedScoreType<SCORE_TYPE, action::MAX> empty;

   // word and pos
   m_lCache.clear();
#ifdef LABELED
   m_lCacheLabel.clear();
#endif
   m_stackfeats.clear();
   m_lCharCache.clear();
   static std::vector< std::string > currentwordchars;

   for (int i=0; i<input.size(); ++i) {
      m_lCache.push_back(CWord(input[i].word));
#ifdef LABELED
   m_lCacheLabel.push_back(CDependencyLabel(input[i].label));
#endif

    if(!stackfeats.empty())
    {
  	  m_stackfeats.push_back(stackfeats[i]);
    }
    currentwordchars.clear();
    getCharactersFromUTF8String(input[i].word, &currentwordchars);
    m_wordIndexs.push_back(m_lCharCache.size());

    for(int idx = 0; idx < currentwordchars.size(); idx++)
    {
  	  m_lCharCache.push_back(currentwordchars[idx]);
    }
   }

   // make standard item
   item.clear();
   for (int i=0; i<input.size() * 2; ++i) {
#ifdef LABELED
   item.StandardMoveStep(input, m_lCacheLabel);
#else
   item.StandardMoveStep(input);
#endif
   }

   // extract feature now with another step less efficient yet easier here
   tmp.clear();
   while (tmp != item) {
      action = tmp.FollowMove(&item );
      getOrUpdateStackScore(&tmp, empty, action, 1, 0);
      tmp.Move(action);
   }
}


