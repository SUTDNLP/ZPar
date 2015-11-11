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

   const int &st_index = item->stackempty() ? -1 : item->stacktop(); // stack top
   const int &sth_index = st_index == -1 ? -1 : item->head(st_index); // stack top head
   const int &sthh_index = sth_index == -1 ? -1 : item->head(sth_index); // stack top head
   const int &stld_index = st_index == -1 ? -1 : item->leftdep(st_index); // leftmost dep of stack
   const int &strd_index = st_index == -1 ? -1 : item->rightdep(st_index); // rightmost dep st
   const int &stl2d_index = stld_index == -1 ? -1 : item->sibling(stld_index); // left 2ndmost dep of stack
   const int &str2d_index = strd_index == -1 ? -1 : item->sibling(strd_index); // right 2ndmost dep st
   const int &n0_index = item->nextbufferword()==m_lCache.size() ? -1 : item->nextbufferword(); // next
   assert(n0_index<static_cast<int>(m_lCache.size())); // the next index shouldn't exceed sentence
   const int &n0ld_index = n0_index==-1 ? -1 : item->leftdep(n0_index); // leftmost dep of next
   const int &n0l2d_index = n0ld_index==-1 ? -1 : item->sibling(n0ld_index); // leftmost dep of next
   const int &ht_index = item->headstackempty() ? -1 : item->headstacktop(); // headstack
   const int &ht2_index = item->headstacksize()<2 ? -1 : item->headstackitem(item->headstacksize()-2); // headstack 2nd
   static int n1_index;
   static int n2_index;
   static int n3_index;
   n1_index = (n0_index != -1 && n0_index+1<m_lCache.size()) ? n0_index+1 : -1 ;
   n2_index = (n0_index != -1 && n0_index+2<m_lCache.size()) ? n0_index+2 : -1 ;
   n3_index = (n0_index != -1 && n0_index+3<m_lCache.size()) ? n0_index+3 : -1 ;


   static CTaggedWord<CTag, TAG_SEPARATOR> st_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> sth_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> sthh_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> stld_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> strd_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> stl2d_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> str2d_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> n0_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> n0ld_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> n0l2d_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> n1_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> n2_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> ht_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> ht2_word_tag;


   const CWord &st_word = st_index==-1 ? g_emptyWord : m_lCache[st_index];
   const CWord &sth_word = sth_index==-1 ? g_emptyWord : m_lCache[sth_index];
   const CWord &sthh_word = sthh_index==-1 ? g_emptyWord : m_lCache[sthh_index];
   const CWord &stld_word = stld_index==-1 ? g_emptyWord : m_lCache[stld_index];
   const CWord &strd_word = strd_index==-1 ? g_emptyWord : m_lCache[strd_index];
   const CWord &stl2d_word = stl2d_index==-1 ? g_emptyWord : m_lCache[stl2d_index];
   const CWord &str2d_word = str2d_index==-1 ? g_emptyWord : m_lCache[str2d_index];
   const CWord &n0_word = n0_index==-1 ? g_emptyWord : m_lCache[n0_index];
   const CWord &n0ld_word = n0ld_index==-1 ? g_emptyWord : m_lCache[n0ld_index];
   const CWord &n0l2d_word = n0l2d_index==-1 ? g_emptyWord : m_lCache[n0l2d_index];
   const CWord &n1_word = n1_index==-1 ? g_emptyWord : m_lCache[n1_index];
   const CWord &n2_word = n2_index==-1 ? g_emptyWord : m_lCache[n2_index];
   const CWord &ht_word = ht_index==-1 ? g_emptyWord : m_lCache[ht_index];
   const CWord &ht2_word = ht2_index==-1 ? g_emptyWord : m_lCache[ht2_index];



   const CTag &st_tag = item->pos(st_index)==-1 ? g_noneTag : CTag(item->pos(st_index));
   const CTag &sth_tag = item->pos(sth_index)==-1 ? g_noneTag : CTag(item->pos(sth_index));
   const CTag &sthh_tag = item->pos(sthh_index)==-1 ? g_noneTag : CTag(item->pos(sthh_index));
   const CTag &stld_tag = item->pos(stld_index)==-1 ? g_noneTag : CTag(item->pos(stld_index));
   const CTag &strd_tag = item->pos(strd_index)==-1 ? g_noneTag : CTag(item->pos(strd_index));
   const CTag &stl2d_tag = item->pos(stl2d_index)==-1 ? g_noneTag : CTag(item->pos(stl2d_index));
   const CTag &str2d_tag = item->pos(str2d_index)==-1 ? g_noneTag : CTag(item->pos(str2d_index));
   const CTag &n0_tag = item->pos(n0_index)==-1 ? g_noneTag : CTag(item->pos(n0_index));
   const CTag &n0ld_tag = item->pos(n0ld_index)==-1 ? g_noneTag : CTag(item->pos(n0ld_index));
   const CTag &n0l2d_tag = item->pos(n0l2d_index)==-1 ? g_noneTag : CTag(item->pos(n0l2d_index));
   const CTag &n1_tag = item->pos(n1_index)==-1 ? g_noneTag : CTag(item->pos(n1_index));
   const CTag &n2_tag = item->pos(n2_index)==-1 ? g_noneTag : CTag(item->pos(n2_index));
   const CTag &ht_tag = item->pos(ht_index)==-1 ? g_noneTag : CTag(item->pos(ht_index));
   const CTag &ht2_tag = item->pos(ht2_index)==-1 ? g_noneTag : CTag(item->pos(ht2_index));

   st_word_tag.load(st_word, st_tag);
   sth_word_tag.load(sth_word, sth_tag);
   sthh_word_tag.load(sthh_word, sthh_tag);
   stld_word_tag.load(stld_word, stld_tag);
   strd_word_tag.load(strd_word, strd_tag);
   stl2d_word_tag.load(stl2d_word, stl2d_tag);
   str2d_word_tag.load(str2d_word, str2d_tag);
   n0_word_tag.load(n0_word, n0_tag);
   n0ld_word_tag.load(n0ld_word, n0ld_tag);
   n0l2d_word_tag.load(n0l2d_word, n0l2d_tag);
   n1_word_tag.load(n1_word, n1_tag);
   n2_word_tag.load(n2_word, n2_tag);
   ht_word_tag.load(ht_word, ht_tag);
   ht2_word_tag.load(ht2_word, ht2_tag);


   const int &st_label = st_index==-1 ? CDependencyLabel::NONE : item->label(st_index);
   const int &sth_label = sth_index==-1 ? CDependencyLabel::NONE : item->label(sth_index);
   const int &stld_label = stld_index==-1 ? CDependencyLabel::NONE : item->label(stld_index);
   const int &strd_label = strd_index==-1 ? CDependencyLabel::NONE : item->label(strd_index);
   const int &stl2d_label = stl2d_index==-1 ? CDependencyLabel::NONE : item->label(stl2d_index);
   const int &str2d_label = str2d_index==-1 ? CDependencyLabel::NONE : item->label(strd_index);
   const int &n0ld_label = n0ld_index==-1 ? CDependencyLabel::NONE : item->label(n0ld_index);
   const int &n0l2d_label = n0l2d_index==-1 ? CDependencyLabel::NONE : item->label(n0l2d_index);

   static int st_n0_dist;
   st_n0_dist = encodeLinkDistance(st_index, n0_index);

   const int st_rarity = st_index==-1?0:item->rightarity(st_index);
   const int st_larity = st_index==-1?0:item->leftarity(st_index);
   const int n0_larity = n0_index==-1?0:item->leftarity(n0_index);

   const CSetOfTags<CDependencyLabel> &st_rtagset = st_index==-1?CSetOfTags<CDependencyLabel>():item->righttagset(st_index);
   const CSetOfTags<CDependencyLabel> &st_ltagset = st_index==-1?CSetOfTags<CDependencyLabel>():item->lefttagset(st_index);
   const CSetOfTags<CDependencyLabel> &n0_ltagset = n0_index==-1?CSetOfTags<CDependencyLabel>():item->lefttagset(n0_index);

   static CTwoTaggedWords st_word_tag_n0_word_tag ;
   static CTwoWords st_word_n0_word ;
   if ( amount == 0 ) {
      st_word_tag_n0_word_tag.refer( &st_word_tag, &n0_word_tag );
      st_word_n0_word.refer( &st_word, &n0_word );
   }
   else {
      st_word_tag_n0_word_tag.allocate( st_word_tag, n0_word_tag );
      st_word_n0_word.allocate( st_word, n0_word );
   }

   static CTuple2<CWord, int> word_int;
   static CTuple2<CWord, CWord> word_word;
   static CTuple2<CTag, CTag> tag_tag;
   static CTuple2<CTag, int> tag_int;
   static CTuple3<CWord, CTag, CTag> word_tag_tag;
   static CTuple3<CTag, CTag, CTag> tag_tag_tag;
   static CTuple3<CWord, CWord, CTag> word_word_tag;
   static CTuple3<CWord, CWord, CWord> word_word_word;
   static CTuple4<CWord, CWord, CTag, CTag> word_word_tag_tag;
   static CTuple3<CWord, CWord, int> word_word_int;
   static CTuple3<CWord, CTag, int> word_tag_int;
   static CTuple3<CTag, CTag, int> tag_tag_int;
   static CTuple2<CWord, CSetOfTags<CDependencyLabel> > word_tagset;
   static CTuple2<CTag, CSetOfTags<CDependencyLabel> > tag_tagset;

   if(action == action::NO_ACTION || action < action::LABEL_SH_FIRST)
   {
	   CWeight* curweights = amount == 0 ? static_cast<CWeight*>(m_weights) : static_cast<CWeight*>(m_delta_dep);

	   // single
	   if (st_index != -1) {
	      curweights->m_mapSTw.getOrUpdateScore( retval, st_word, action, m_nScoreIndex, amount, round) ;
	      curweights->m_mapSTt.getOrUpdateScore( retval, st_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTwt.getOrUpdateScore( retval, st_word_tag, action, m_nScoreIndex, amount, round) ;
	   }

	   if (n0_index != -1) {
	      curweights->m_mapN0w.getOrUpdateScore( retval, n0_word, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapN0t.getOrUpdateScore( retval, n0_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapN0wt.getOrUpdateScore( retval, n0_word_tag, action, m_nScoreIndex, amount, round) ;
	   }

	   if (n1_index != -1) {
	      curweights->m_mapN1w.getOrUpdateScore( retval, n1_word, action, m_nScoreIndex, amount, round ) ;
	      if(item->buffersize()>1)
	      {
	    	  curweights->m_mapN1t.getOrUpdateScore( retval, n1_tag, action, m_nScoreIndex, amount, round ) ;
	    	  curweights->m_mapN1wt.getOrUpdateScore( retval, n1_word_tag, action, m_nScoreIndex, amount, round) ;
	      }
	   }

	   if (n2_index != -1) {
	      curweights->m_mapN2w.getOrUpdateScore( retval, n2_word, action, m_nScoreIndex, amount, round ) ;
	      if(item->buffersize()>2)
	      {
	    	  curweights->m_mapN2t.getOrUpdateScore( retval, n2_tag, action, m_nScoreIndex, amount, round ) ;
	    	  curweights->m_mapN2wt.getOrUpdateScore( retval, n2_word_tag, action, m_nScoreIndex, amount, round) ;
	      }
	   }

	   if (sth_index != -1) {
	      curweights->m_mapSTHw.getOrUpdateScore( retval, sth_word, action, m_nScoreIndex, amount, round) ;
	      curweights->m_mapSTHt.getOrUpdateScore( retval, sth_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTi.getOrUpdateScore( retval, st_label, action, m_nScoreIndex, amount, round) ;
	   }

	   if (sthh_index != -1) {
	      curweights->m_mapSTHHw.getOrUpdateScore( retval, sthh_word, action, m_nScoreIndex, amount, round) ;
	      curweights->m_mapSTHHt.getOrUpdateScore( retval, sthh_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTHi.getOrUpdateScore( retval, sth_label, action, m_nScoreIndex, amount, round) ;
	   }

	   if (stld_index != -1) {
	      curweights->m_mapSTLDw.getOrUpdateScore( retval, stld_word, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTLDt.getOrUpdateScore( retval, stld_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTLDi.getOrUpdateScore( retval, stld_label, action, m_nScoreIndex, amount, round) ;
	   }

	   if (strd_index != -1) {
	      curweights->m_mapSTRDw.getOrUpdateScore( retval, strd_word, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTRDt.getOrUpdateScore( retval, strd_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTRDi.getOrUpdateScore( retval, strd_label, action, m_nScoreIndex, amount, round) ;
	   }

	   if (n0ld_index != -1) {
	      curweights->m_mapN0LDw.getOrUpdateScore( retval, n0ld_word, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapN0LDt.getOrUpdateScore( retval, n0ld_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapN0LDi.getOrUpdateScore( retval, n0ld_label, action, m_nScoreIndex, amount, round) ;
	   }

	   if (stl2d_index != -1) {
	      curweights->m_mapSTL2Dw.getOrUpdateScore( retval, stl2d_word, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTL2Dt.getOrUpdateScore( retval, stl2d_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTL2Di.getOrUpdateScore( retval, stl2d_label, action, m_nScoreIndex, amount, round) ;
	   }

	   if (str2d_index != -1) {
	      curweights->m_mapSTR2Dw.getOrUpdateScore( retval, str2d_word, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTR2Dt.getOrUpdateScore( retval, str2d_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTR2Di.getOrUpdateScore( retval, str2d_label, action, m_nScoreIndex, amount, round) ;
	   }

	   if (n0l2d_index != -1) {
	      curweights->m_mapN0L2Dw.getOrUpdateScore( retval, n0l2d_word, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapN0L2Dt.getOrUpdateScore( retval, n0l2d_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapN0L2Di.getOrUpdateScore( retval, n0l2d_label, action, m_nScoreIndex, amount, round) ;
	   }

	   // s0 and n0
	   if (st_index != -1) {
	      curweights->m_mapSTwtN0wt.getOrUpdateScore( retval, st_word_tag_n0_word_tag, action, m_nScoreIndex, amount, round );
	      refer_or_allocate_tuple3(word_word_tag, &st_word, &n0_word, &st_tag);
	      curweights->m_mapSTwtN0w.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round ) ;
	      refer_or_allocate_tuple3(word_word_tag, &st_word, &n0_word, &n0_tag);
	      curweights->m_mapSTwN0wt.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round ) ;
	      refer_or_allocate_tuple3(word_tag_tag, &st_word, &st_tag, &n0_tag);
	      curweights->m_mapSTwtN0t.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round ) ;
	      refer_or_allocate_tuple3(word_tag_tag, &n0_word, &st_tag, &n0_tag);
	      curweights->m_mapSTtN0wt.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTwN0w.getOrUpdateScore( retval, st_word_n0_word, action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTtN0t.getOrUpdateScore( retval, CTagSet<CTag, 2>(encodeTags(st_tag,n0_tag)), action, m_nScoreIndex, amount, round ) ;
	   }

	   if (st_index != -1 && n0_index != -1) {
	      curweights->m_mapN0tN1t.getOrUpdateScore( retval, CTagSet<CTag, 2>(encodeTags(n0_tag,n1_tag)), action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapN0tN1tN2t.getOrUpdateScore( retval, CTagSet<CTag, 3>(encodeTags(n0_tag,n1_tag,n2_tag)), action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTtN0tN1t.getOrUpdateScore( retval, CTagSet<CTag, 3>(encodeTags(st_tag,n0_tag,n1_tag)), action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTtN0tN0LDt.getOrUpdateScore( retval, CTagSet<CTag, 3>(encodeTags(st_tag,n0_tag,n0ld_tag)), action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapN0tN0LDtN0L2Dt.getOrUpdateScore( retval, CTagSet<CTag, 3>(encodeTags(n0_tag,n0ld_tag,n0l2d_tag)), action, m_nScoreIndex, amount, round ) ;
	   }
	   if (st_index!=-1) {
	      curweights->m_mapSTHtSTtN0t.getOrUpdateScore( retval, CTagSet<CTag, 3>(encodeTags(sth_tag,st_tag,n0_tag)), action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTHHtSTHtSTt.getOrUpdateScore( retval, CTagSet<CTag, 3>(encodeTags(sthh_tag, sth_tag,st_tag)), action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTtSTLDtN0t.getOrUpdateScore( retval, CTagSet<CTag, 3>(encodeTags(st_tag,stld_tag,n0_tag)), action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTtSTLDtSTL2Dt.getOrUpdateScore( retval, CTagSet<CTag, 3>(encodeTags(st_tag,stld_tag,stl2d_tag)), action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTtSTRDtN0t.getOrUpdateScore( retval, CTagSet<CTag, 3>(encodeTags(st_tag,strd_tag,n0_tag)), action, m_nScoreIndex, amount, round ) ;
	      curweights->m_mapSTtSTRDtSTR2Dt.getOrUpdateScore( retval, CTagSet<CTag, 3>(encodeTags(st_tag,strd_tag,str2d_tag)), action, m_nScoreIndex, amount, round ) ;
	   }

	   // distance
	   if (st_index!=-1 && n0_index!=-1) {
	      refer_or_allocate_tuple2(word_int, &st_word, &st_n0_dist);
	      curweights->m_mapSTwd.getOrUpdateScore( retval, word_int, action, m_nScoreIndex, amount, round) ;
	      refer_or_allocate_tuple2(tag_int, &st_tag, &st_n0_dist);
	      curweights->m_mapSTtd.getOrUpdateScore( retval, tag_int, action, m_nScoreIndex, amount, round ) ;
	      refer_or_allocate_tuple2(word_int, &n0_word, &st_n0_dist);
	      curweights->m_mapN0wd.getOrUpdateScore( retval, word_int, action, m_nScoreIndex, amount, round ) ;
	      refer_or_allocate_tuple2(tag_int, &n0_tag, &st_n0_dist);
	      curweights->m_mapN0td.getOrUpdateScore( retval, tag_int, action, m_nScoreIndex, amount, round ) ;
	      refer_or_allocate_tuple3(word_word_int, &st_word, &n0_word, &st_n0_dist);
	      curweights->m_mapSTwN0wd.getOrUpdateScore( retval, word_word_int, action, m_nScoreIndex, amount, round ) ;
	      refer_or_allocate_tuple3(tag_tag_int, &st_tag, &n0_tag, &st_n0_dist);
	      curweights->m_mapSTtN0td.getOrUpdateScore( retval, tag_tag_int, action, m_nScoreIndex, amount, round ) ;
	   }

	   // st arity
	   if (st_index != -1) {
	      refer_or_allocate_tuple2(word_int, &st_word, &st_rarity);
	      curweights->m_mapSTwra.getOrUpdateScore( retval, word_int, action, m_nScoreIndex, amount, round) ;
	      refer_or_allocate_tuple2(tag_int, &st_tag, &st_rarity);
	      curweights->m_mapSTtra.getOrUpdateScore( retval, tag_int, action, m_nScoreIndex, amount, round ) ;
	      refer_or_allocate_tuple2(word_int, &st_word, &st_larity);
	      curweights->m_mapSTwla.getOrUpdateScore( retval, word_int, action, m_nScoreIndex, amount, round) ;
	      refer_or_allocate_tuple2(tag_int, &st_tag, &st_larity);
	      curweights->m_mapSTtla.getOrUpdateScore( retval, tag_int, action, m_nScoreIndex, amount, round ) ;
	   }

	   // n0 arity
	   if (n0_index!=-1) {
	      refer_or_allocate_tuple2(word_int, &n0_word, &n0_larity);
	      curweights->m_mapN0wla.getOrUpdateScore( retval, word_int, action, m_nScoreIndex, amount, round) ;
	      refer_or_allocate_tuple2(tag_int, &n0_tag, &n0_larity);
	      curweights->m_mapN0tla.getOrUpdateScore( retval, tag_int, action, m_nScoreIndex, amount, round ) ;
	   }

	   // st labelset
	   if (st_index != -1){
	      refer_or_allocate_tuple2(word_tagset, &st_word, &st_rtagset);
	      curweights->m_mapSTwrp.getOrUpdateScore( retval, word_tagset, action, m_nScoreIndex, amount, round) ;
	      refer_or_allocate_tuple2(tag_tagset, &st_tag, &st_rtagset);
	      curweights->m_mapSTtrp.getOrUpdateScore( retval, tag_tagset, action, m_nScoreIndex, amount, round ) ;

	      refer_or_allocate_tuple2(word_tagset, &st_word, &st_ltagset);
	      curweights->m_mapSTwlp.getOrUpdateScore( retval, word_tagset, action, m_nScoreIndex, amount, round) ;
	      refer_or_allocate_tuple2(tag_tagset, &st_tag, &st_ltagset);
	      curweights->m_mapSTtlp.getOrUpdateScore( retval, tag_tagset, action, m_nScoreIndex, amount, round ) ;
	   }

	   // n0 labelset
	   if (n0_index != -1){
	      refer_or_allocate_tuple2(word_tagset, &n0_word, &n0_ltagset);
	      curweights->m_mapN0wlp.getOrUpdateScore( retval, word_tagset, action, m_nScoreIndex, amount, round) ;
	      refer_or_allocate_tuple2(tag_tagset, &n0_tag, &n0_ltagset);
	      curweights->m_mapN0tlp.getOrUpdateScore( retval, tag_tagset, action, m_nScoreIndex, amount, round ) ;
	   }


   }


   // POS Tagging features
   const int &q0_index = item->nextqueueword()>=m_lCache.size() ? -1 : item->nextqueueword(); // next
   if(q0_index>static_cast<int>(m_lCache.size())) // the next index shouldn't exceed sentence
   {
	   std::cout << q0_index << " " << item->nextbufferword() << " " << m_lCache.size() << std::endl;
   }
   static int q1_index;
   static int q2_index;
   q1_index = (q0_index != -1 && q0_index+1<m_lCache.size()) ? q0_index+1 : -1 ;
   q2_index = (q0_index != -1 && q0_index+2<m_lCache.size()) ? q0_index+2 : -1 ;

   const CWord &q0_word = q0_index==-1 ?  g_emptyWord : m_lCache[q0_index];
   const CWord &q1_word = q1_index==-1 ?  g_emptyWord : m_lCache[q1_index];
   const CWord &q2_word = q2_index==-1 ?  g_emptyWord : m_lCache[q2_index];

   static int p1_index;
   static int p2_index;
   p1_index = (q0_index != -1 && q0_index-1>=0) ? q0_index-1 : -1 ;
   p2_index = (q0_index != -1 && q0_index-2>=0) ? q0_index-2 : -1 ;

   const CWord &p1_word = p1_index==-1 ?  g_emptyWord : m_lCache[p1_index];
   const CWord &p2_word = p2_index==-1 ?  g_emptyWord : m_lCache[p2_index];
   const CTag &p1_tag = p1_index == -1 ?  g_noneTag : CTag(item->pos(p1_index));
   const CTag &p2_tag = p2_index == -1 ?  g_noneTag : CTag(item->pos(p2_index));

   static CTaggedWord<CTag, TAG_SEPARATOR> p1_word_tag;
   static CTaggedWord<CTag, TAG_SEPARATOR> p2_word_tag;
   p1_word_tag.load(p1_word, p1_tag);
   p2_word_tag.load(p2_word, p2_tag);


   if(q0_index != -1 && (action == action::NO_ACTION || action >= action::LABEL_SH_FIRST))
   {
	   CWeight* curweights = amount == 0 ? static_cast<CWeight*>(m_weights) : static_cast<CWeight*>(m_delta_pos);

	   // current
	   static unsigned long int last_start , last_length ;
	   static unsigned long int next_start , next_length ;
	   static unsigned long int start , end , length ;



	   // abstd::cout the words
	   start = m_wordIndexs[q0_index] ;
	   end = m_wordIndexs[q0_index+1]-1 ;
	   length = end-start+1 ;
	   last_start = p1_index > 0 ? m_wordIndexs[p1_index] : -1 ;
	   last_length = p1_index > 0 ? m_wordIndexs[p1_index+1]-m_wordIndexs[p1_index] : 99999 ;
	   next_start = q1_index > 0 ? m_wordIndexs[q1_index] : -1 ;
	   next_length = q1_index > 0 ? m_wordIndexs[q1_index+1]-m_wordIndexs[q1_index] : 99999 ;

	   // abstd::cout the chars
	   const CWord &first_char = m_lCharCache[start] ;
	   const CWord &first1_char = start+1 <= end ? m_lCharCache[start+1] : g_emptyWord;
	   const CWord &first2_char = start+2 <= end ? m_lCharCache[start+2] : g_emptyWord;
	   const CWord &last_char = m_lCharCache[end] ;
	   const CWord &last1_char = end-1 >= start ? m_lCharCache[end-1] : g_emptyWord;
	   const CWord &last2_char = end-2 >= start ? m_lCharCache[end-2] : g_emptyWord;
	   const CWord &next1_char = q1_index != -1 ?  m_lCharCache[end+1] : g_emptyWord;
	   const CWord &prev1_char = p1_index != -1 ?  m_lCharCache[start-1] : g_emptyWord;

	   const CWord &st_firstchar = st_index != -1 ?  m_lCharCache[m_wordIndexs[st_index]] : g_emptyWord;
	   const CWord &st_lastchar = st_index != -1 ?  m_lCharCache[m_wordIndexs[st_index+1]-1] : g_emptyWord;

	   const CWord &n0_firstchar = n0_index != -1 ?  m_lCharCache[m_wordIndexs[n0_index]] : g_emptyWord;
	   const CWord &n0_lastchar = n0_index != -1 ?  m_lCharCache[m_wordIndexs[n0_index+1]-1] : g_emptyWord;


	   unsigned long long first_char_cat = cast_weights->m_mapCharTagDictionary.lookup(first_char) ;
	   unsigned long long last_char_cat = cast_weights->m_mapCharTagDictionary.lookup(last_char) ;

	   curweights->m_mapCurrentWord.getOrUpdateScore( retval, q0_word, action, m_nScoreIndex, amount, round);
	   curweights->m_mapLastTag.getOrUpdateScore( retval, p1_tag, action, m_nScoreIndex, amount, round);

	   refer_or_allocate_tuple2(tag_tag, &p2_tag, &p1_tag);
	   curweights->m_mapLastTwoTags.getOrUpdateScore( retval, tag_tag, action, m_nScoreIndex, amount, round);
	   if ( p1_index != -1 ) {

	      if ( last_length <= 2 )curweights->m_mapLastWord.getOrUpdateScore( retval, p1_word, action, m_nScoreIndex, amount, round);
	      if ( last_length <= 2 )curweights->m_mapLastTagCurrentWord.getOrUpdateScore( retval, p1_word_tag, action, m_nScoreIndex, amount, round);
	      if ( length <= 2 )
	      {
	    	  refer_or_allocate_tuple2(word_word, &q0_word, &prev1_char);
	    	  curweights->m_mapCurentWordPrevChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	      }
	      if ( last_length <= 2 )
	      {
	    	  refer_or_allocate_tuple2(word_word, &p1_word, &first_char);
	    	  curweights->m_mapLastWordFirstChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	      }

	   }


	   if ( q1_index != -1 ) {
	      if ( next_length <= 2 )curweights->m_mapNextWord.getOrUpdateScore( retval, q1_word, action, m_nScoreIndex, amount, round);
	      if ( length <= 2 )
	      {
	    	  refer_or_allocate_tuple2(word_word, &q0_word, &next1_char);
	    	  curweights->m_mapCurentWordNextChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	      }
	      if ( next_length <= 2 )
	      {
	    	  refer_or_allocate_tuple2(word_word, &q1_word, &last_char);
	    	  curweights->m_mapNextWordLastChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	      }
	   }


	   if ( length == 1 ) {
		   if ( p1_index != -1 && q1_index != -1 )
		   {
			   refer_or_allocate_tuple3(word_word_word, &prev1_char, &first_char, &next1_char);
			   curweights->m_mapOneCharWordTriChar.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round);
		   }
	   }
	   else {
	     curweights->m_mapFirstChar.getOrUpdateScore( retval, first_char, action, m_nScoreIndex, amount, round);
	     curweights->m_mapLastChar.getOrUpdateScore( retval, last_char, action, m_nScoreIndex, amount, round);
	     curweights->m_mapFirstCharCat.getOrUpdateScore( retval, first_char_cat, action, m_nScoreIndex, amount, round);
	     curweights->m_mapLastCharCat.getOrUpdateScore( retval, last_char_cat, action, m_nScoreIndex, amount, round);

	      for ( int j = 0 ; j < length ; ++ j ) {
	    	 const CWord &curChar = m_lCharCache[start+j];
	         if ( j > 0 && j < length-1 )
	         {
	        	 curweights->m_mapCharInWord.getOrUpdateScore( retval, curChar, action, m_nScoreIndex, amount, round);
	         }
	         if ( j > 0 ) {
	        	refer_or_allocate_tuple2(word_word, &curChar, &first_char);
	            curweights->m_mapCharInWordByFirstChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	            if ( m_lCharCache[start+j] == m_lCharCache[start+j-1])
	              curweights->m_mapRepeatedChar.getOrUpdateScore( retval, curChar, action, m_nScoreIndex, amount, round);
	            if(j > 1 && m_lCharCache[start+j] == m_lCharCache[start+j-2])
	            {
	            	curweights->m_mapRepeated2Char.getOrUpdateScore( retval, curChar, action, m_nScoreIndex, amount, round);
	            }
	         }
	         if ( j < length-1 ) {
	        	 refer_or_allocate_tuple2(word_word, &curChar, &last_char);
	           curweights->m_mapCharInWordByLastChar.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	         }

	      }
	   }

	  //prefix
	   curweights->m_mapPrefixChar1.getOrUpdateScore( retval, first_char, action, m_nScoreIndex, amount, round);
	   curweights->m_mapSuffixChar1.getOrUpdateScore( retval, last_char, action, m_nScoreIndex, amount, round);
	   if(length > 1)
	   {
		   refer_or_allocate_tuple2(word_word, &first_char, &first1_char);
		   curweights->m_mapPrefixChar2.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
		   refer_or_allocate_tuple2(word_word, &last_char, &last1_char);
		   curweights->m_mapSuffixChar2.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round);
	   }
	   if(length > 2)
	 	{
			 refer_or_allocate_tuple3(word_word_word, &first_char, &first1_char, &first2_char);
			 curweights->m_mapPrefixChar3.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round);
			 refer_or_allocate_tuple3(word_word_word, &last_char, &last1_char, &last2_char);
			 curweights->m_mapSuffixChar3.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round);
	 	}

	  unsigned long long normalizedlength = length < 5 ? length : 5;
	  curweights->m_mapNormalizedLength.getOrUpdateScore( retval, normalizedlength, action, m_nScoreIndex, amount, round);

	  //dictionary features
	  if(cast_weights->m_mapWordFrequency.find(q0_word, 0)  >= cast_weights->m_nMaxWordFrequency/5000 + 5)
	  {
		  for (int label=CTag::FIRST; label<CTag::COUNT; ++label) {
			  unsigned long long labelIndex = label;
			  if(cast_weights->m_mapTagDictionary.lookup(q0_word, CTag(label)) )
			  {
				  curweights->m_mapWordLabelInDict.getOrUpdateScore( retval, labelIndex, action, m_nScoreIndex, amount, round);
			  }
		  }
	  }


	  if(cast_weights->m_mapCharFrequency.find(first_char, 0)  >= cast_weights->m_nMaxWordFrequency/5000 + 10)
	  {
		  for (int label=CTag::FIRST; label<CTag::COUNT; ++label) {
			  unsigned long long labelIndex = label;
			  if(cast_weights->m_mapCharTagDictionary.lookup(first_char, CTag(label)))
			  {
				  curweights->m_mapFirstCharLabelInDict.getOrUpdateScore( retval, labelIndex, action, m_nScoreIndex, amount, round);
			  }
		  }
	  }

	  if(cast_weights->m_mapCharFrequency.find(last_char, 0)  >= cast_weights->m_nMaxWordFrequency/5000 + 10)
	  {
		  for (int label=CTag::FIRST; label<CTag::COUNT; ++label) {
			  unsigned long long labelIndex = label;
			  if(cast_weights->m_mapCharTagDictionary.lookup(last_char, CTag(label)))
			  {
				  curweights->m_mapLastCharLabelInDict.getOrUpdateScore( retval, labelIndex, action, m_nScoreIndex, amount, round);
			  }
		  }
	  }

	  /*
	  if (item->nextqueueword() >= action::max_buffer_size && st_index != -1 && item->buffersize() <3 ) {
		 curweights->m_mapPOSSTw.getOrUpdateScore( retval, st_word, action, m_nScoreIndex, amount, round) ;
		 curweights->m_mapPOSSTt.getOrUpdateScore( retval, st_tag, action, m_nScoreIndex, amount, round ) ;
		 curweights->m_mapPOSSTwt.getOrUpdateScore( retval, st_word_tag, action, m_nScoreIndex, amount, round) ;

		 refer_or_allocate_tuple2(word_word, &st_word, &q0_word);
		 curweights->m_mapPOSSTwCurWord.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
		 refer_or_allocate_tuple2(word_word, &st_firstchar, &q0_word);
		 curweights->m_mapPOSSTfcCurWord.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
		 refer_or_allocate_tuple2(word_word, &st_lastchar, &q0_word);
		 curweights->m_mapPOSSTlcCurWord.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;

		 if(stld_index != -1)
		 {
			 refer_or_allocate_tuple2(tag_tag, &st_tag, &stld_tag);
			 curweights->m_mapPOSSTtSTLDt.getOrUpdateScore( retval, tag_tag, action, m_nScoreIndex, amount, round) ;
			 refer_or_allocate_tuple3(word_tag_tag, &st_word, &st_tag, &stld_tag);
			 curweights->m_mapPOSSTwtSTLDt.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
		 }

		 if(strd_index != -1)
		 {
			 refer_or_allocate_tuple2(tag_tag, &st_tag, &strd_tag);
			 curweights->m_mapPOSSTtSTRDt.getOrUpdateScore( retval, tag_tag, action, m_nScoreIndex, amount, round) ;
			 refer_or_allocate_tuple3(word_tag_tag, &st_word, &st_tag, &strd_tag);
			 curweights->m_mapPOSSTwtSTRDt.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
		 }
	  }

	 if (item->nextqueueword() >= action::max_buffer_size && item->buffersize() >= 1 && item->buffersize() <= 3) {
		 curweights->m_mapPOSN0w.getOrUpdateScore( retval, n0_word, action, m_nScoreIndex, amount, round) ;
		 curweights->m_mapPOSN0t.getOrUpdateScore( retval, n0_tag, action, m_nScoreIndex, amount, round ) ;
		 curweights->m_mapPOSN0wt.getOrUpdateScore( retval, n0_word_tag, action, m_nScoreIndex, amount, round) ;

		 refer_or_allocate_tuple2(word_word, &n0_word, &q0_word);
		 curweights->m_mapPOSN0wCurWord.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
		 refer_or_allocate_tuple2(word_word, &n0_firstchar, &q0_word);
		 curweights->m_mapPOSN0fcCurWord.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
		 refer_or_allocate_tuple2(word_word, &n0_lastchar, &q0_word);
		 curweights->m_mapPOSN0lcCurWord.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;

		 if(n0ld_index != -1)
		 {
			 refer_or_allocate_tuple2(tag_tag, &n0_tag, &n0ld_tag);
			 curweights->m_mapPOSN0tN0LDt.getOrUpdateScore( retval, tag_tag, action, m_nScoreIndex, amount, round) ;
			 refer_or_allocate_tuple3(word_tag_tag, &n0_word, &n0_tag, &n0ld_tag);
			 curweights->m_mapPOSN0wtN0LDt.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
		 }
	 }
	   */

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
   THROW("depparser.cpp: getGlobalScore unsupported");
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
   THROW("depparser.cpp: updateScores unsupported");
}

/*---------------------------------------------------------------
 *
 * updateScoreForState - update a single positive or negative outout
 *
 *--------------------------------------------------------------*/

inline SCORE_TYPE CPosDepParser::updateScoreForState(const CDependencyParse &tree,  const CStateItem &from, const CStateItem *outout , const SCORE_TYPE &amount ) {
   static CStateItem item(&m_lCache);
   item.clear();
   static unsigned action;
   static CPackedScoreType<SCORE_TYPE, action::MAX> empty;
   item = from;
   //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
   SCORE_TYPE loss = 0;
   while ( item != *outout ) {
      action = item.FollowMove( outout );
      if(item.m_nActionSize >= outout->m_nActionSize || action != outout->m_Action[item.m_nActionSize])
      {
    	  std::cout << "error" << std::endl;
      }
      //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
      getOrUpdateStackScore( &item, empty, action, amount,  m_nTrainingRound );

      loss = loss + item.hammingloss(tree, action);
      //loss = loss + 1;
#ifdef LABELED
//      if ( action::getLabel(action) )
//         getOrUpdateStackScore( &item, empty, action::getUnlabeledAction(action), amount, m_nTrainingRound );
#endif
   item.Move( action );
      //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
   }

   return loss;
}

/*---------------------------------------------------------------
 *
 * updateScoresForStates - update scores for states
 *
 *--------------------------------------------------------------*/

void CPosDepParser::updateScoresForStates(const CDependencyParse &tree,  const CStateItem *outout , const CStateItem *correct , SCORE_TYPE amount_add, SCORE_TYPE amount_subtract ) {

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
   SCORE_TYPE correct_loss = updateScoreForState(tree, item, correct , amount_add ) ;
   SCORE_TYPE outout_loss = updateScoreForState(tree, item, outout , amount_subtract ) ;
   if(correct_loss > 0)
   {
	   std::cout << "error" << std::endl;
   }

   //SCORE_TYPE pos_loss = outout->postagloss(tree);
   //SCORE_TYPE dep_loss = outout_loss - correct_loss;

   //if(dep_loss > 1e-20)
   {
	   //SCORE_TYPE normalization = m_delta_dep->squareNorm();
	   //SCORE_TYPE weightloss = (dep_loss)/(normalization + 0.5);
	   SCORE_TYPE weightloss = 1;
	   //if(pos_loss < 1e-20)weightloss = weightloss * 3;
	   static_cast<CWeight*>(m_delta_dep)->scaleCurrent(weightloss, m_nTrainingRound);
	   cast_weights->addCurrent(m_delta_dep, m_nTrainingRound);
   }


   //if(pos_loss > 1e-20 )
   {
	   //SCORE_TYPE normalization = m_delta_pos->squareNorm();
	   //SCORE_TYPE weightloss = (pos_loss)/(normalization + 0.5);
	   SCORE_TYPE weightloss = 2;
	   static_cast<CWeight*>(m_delta_pos)->scaleCurrent(weightloss, m_nTrainingRound);
	   cast_weights->addCurrent(m_delta_pos, m_nTrainingRound);
   }

   m_delta_pos->clear();
   m_delta_dep->clear();

   m_nTotalErrors++;
}


/*---------------------------------------------------------------
 *
 * reduce - helper function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::reduce( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
   static action::CScoredAction scoredaction;
   // update stack score
   scoredaction.action = action::REDUCE;
   scoredaction.score = item->score + scores[scoredaction.action]; 
   m_Beam->insertItem(&scoredaction);
}

/*---------------------------------------------------------------
 *
 * arcleft - helping function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::arcleft( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
   static action::CScoredAction scoredaction;
   static unsigned label;
   for (label=CDependencyLabel::FIRST; label<CDependencyLabel::COUNT; ++label) {
         scoredaction.action = action::encodeAction(action::ARC_LEFT, label);
         scoredaction.score = item->score + scores[scoredaction.action];
	     scoredaction.score_dep = item->score_dep + scores[scoredaction.action];
	     scoredaction.score_pos = item->score_pos;
                               //+scores[action::ARC_LEFT];
         m_Beam->insertItem(&scoredaction);
   }

}

/*---------------------------------------------------------------
 *
 * arcright - helping function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::arcright( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
   static action::CScoredAction scoredaction;
   static unsigned label;
   for (label=CDependencyLabel::FIRST; label<CDependencyLabel::COUNT; ++label) {
         scoredaction.action = action::encodeAction(action::ARC_RIGHT, label);
         scoredaction.score = item->score + scores[scoredaction.action];
	     scoredaction.score_dep = item->score_dep + scores[scoredaction.action];
	     scoredaction.score_pos = item->score_pos;
                              //+scores[action::ARC_RIGHT];
         m_Beam->insertItem(&scoredaction);
   }
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

	   const int &n0_index = item->nextqueueword()==m_lCache.size() ? -1 : item->nextqueueword();
	   //const CWord &n0_word = n0_index==-1 ?  g_emptyWord : m_lCache[n0_index];

	   for (label=CTag::FIRST; label<CTag::COUNT; ++label) {
	   //for(int idx = 0; idx < m_stackfeats[n0_index].m_feats.size(); idx++){
		   //if ( !m_weights->rules() || canAssignLabel(m_lCache, item->stacktop(), item->size(), label) ) {
		   //label = CTag(m_stackfeats[n0_index].m_feats[idx]).code();
		   //if(PENN_TAG_CLOSED[label] && !cast_weights->m_mapTagDictionary.lookup(n0_word, CTag(label)))
		   //{
			//   continue;
		   //}
		   //}


		   //if(cast_weights->m_mapWordFrequency.find(n0_word, 0)  < cast_weights->m_nMaxWordFrequency/5000 + 5
			//	   || cast_weights->m_mapTagDictionary.lookup(n0_word, CTag(label)))
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
 * shiftnone - help function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::shiftnone( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
   static action::CScoredAction scoredaction;
   // update stack score
   scoredaction.action = action::encodeAction(action::SHIFT, 0);
   scoredaction.score = item->score + scores[scoredaction.action];
   scoredaction.score_dep = item->score_dep + scores[scoredaction.action];
   scoredaction.score_pos = item->score_pos;
						 //+scores[action::SHIFT];
   m_Beam->insertItem(&scoredaction);

}

/*---------------------------------------------------------------
 *
 * poproot - help function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::poproot( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
   static action::CScoredAction scoredaction;
   // update stack score
   scoredaction.action = action::POP_ROOT;
   scoredaction.score = item->score + scores[scoredaction.action];
   scoredaction.score_dep = item->score_dep + scores[scoredaction.action];
   scoredaction.score_pos = item->score_pos;
   m_Beam->insertItem(&scoredaction);
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
   //static CStateItem correctState_next(&m_lCache) ;
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
   //if (bTrain) correctState_next.clear();


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
   for (index=0; index<length*3; ++index) {
      
      if (bTrain) bCorrect = false ; 
      //if (bTrain) correctState_next.StandardMoveStep(correct, m_lCacheLabel);

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

         if(pGenerator->canDEPOperation())
         {
			 if ( pGenerator->nextbufferword() == length ) {
				assert( pGenerator->stacksize() != 0 );
				if ( pGenerator->stacksize()>1 ) {
				    if(pGenerator->head( pGenerator->stacktop() ) == DEPENDENCY_LINK_NO_HEAD)
				    {
				    	 std::cout << "error" << std::endl;
				    }
					reduce(pGenerator, packed_scores) ;
				}
				else {
				   poproot(pGenerator, packed_scores);
				}
			 }
			 // for the state items that still need more words
			 else {
				if ( !pGenerator->afterreduce() ) { // there are many ways when there are many arcrighted items on the stack and the root need arcleft. force this.
				   if ( pGenerator->nextbufferword() < length-1 || pGenerator->stackempty() ) // rules
				   {
					   shiftnone(pGenerator, packed_scores) ;
				   }
				}
				if ( !pGenerator->stackempty() ) {
					if(pGenerator->nextbufferword() < length-1 || pGenerator->headstacksize() == 1)
					{
						arcright(pGenerator, packed_scores) ;
					}
				}
				if ( !pGenerator->stackempty()) {
				   if ( pGenerator->head( pGenerator->stacktop() ) != DEPENDENCY_LINK_NO_HEAD ) {
					  reduce(pGenerator, packed_scores) ;
				   }
				   else {
						 arcleft(pGenerator, packed_scores) ;
				   }
				}
			 }
         }
         else
         {
        	 shift(pGenerator, packed_scores) ;
         }

         // insert item
         //bool canReachGold = false;
         for (unsigned i=0; i<m_Beam->size(); ++i) {
            pCandidate = *pGenerator;
            pCandidate.score = m_Beam->item(i)->score;
            pCandidate.score_dep = m_Beam->item(i)->score_dep;
            pCandidate.score_pos = m_Beam->item(i)->score_pos;
            pCandidate.Move( m_Beam->item(i)->action );
            //if(pCandidate == correctState_next)
            //{
            //	canReachGold = true;
            //}
            m_Agenda->pushCandidate(&pCandidate);
         }

         //if(bTrain && !canReachGold)
         //{
        //	 std::cout << "error" << std::endl;
        // }

         if (bTrain && *pGenerator == correctState) {
            bCorrect = true ;
            correctState.score = pGenerator->score;
            correctState.score_dep = pGenerator->score_dep;
            correctState.score_pos = pGenerator->score_pos;
         }

         pGenerator = m_Agenda->generatorNext() ;

      }
      // when we are doing training, we need to consider the standard move and update
      if (bTrain) {
#ifdef EARLY_UPDATE
         if (!bCorrect) {
            TRACE("Error at the "<<correctState.nextbufferword()<<"th word; total is "<<correct.size())
            CStateItem * bestitem = m_Agenda->bestGenerator();
            if(*bestitem == correctState)
            {
            	std::cout << "error" << std::endl;
            }
            updateScoresForStates(correct, bestitem, &correctState, 1, -1) ;
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
            //m_Agenda->clearCandidates();
            //m_Agenda->pushCandidate(&correctState);
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

      if(correctState.m_nNextWord != correct.size() || correctState.m_nQNextWord != correct.size())
      {
    	  std::cout << "error" << std::endl;
      }
      for(int idx = 0; idx < correct.size(); idx++)
      {
    	  if(correctState.m_lHeads[idx] != correct[idx].head || CTag(correctState.m_lPOSs[idx]).str() != correct[idx].tag)
    	  {
    		  std::cout << correctState.m_lHeads[idx] << " " << CTag(correctState.m_lPOSs[idx]).str() <<" " << correct[idx].head << "" << correct[idx].tag << std::endl;
    	  }
      }
      // then make sure that the correct item is stack top finally
      if ( *(m_Agenda->bestGenerator()) != correctState ) {
         TRACE("The best item is not the correct one")
         updateScoresForStates(correct, m_Agenda->bestGenerator(), &correctState, 1, -1) ;
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
