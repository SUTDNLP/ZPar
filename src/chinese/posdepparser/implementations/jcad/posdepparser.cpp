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
#define find_or_replace_word_cache(tmp_start, tmp_end) ( amount == 0 ? m_lCache.find(tmp_start, tmp_end, &m_Sentence) : m_lCache.replace(tmp_start, tmp_end, &m_Sentence) )

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
    const int &st0r1_index = (st0_index!=-1&&st0_index+1<m_Sentence.size())? st0_index+1 : -1; // the next word of st0_index
    const int &st0l1_index = (st0_index!=-1&&st0_index-1>=0)? st0_index-1 : -1; // the previous word of st0_index
    const int &st1_index = item->stacksize() <= 1 ? -1 : item->stackitem(item->stacksize()-2); // stack top head
    const int &st1r1_index = (st1_index!=-1&&st1_index+1<m_Sentence.size())? st1_index+1 : -1; // the next word of st1_index
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


    const int &st0ld0in_index = st0_index == -1 ? -1 : item->leftinnerfirstchild(st0_index); // first left inner dep
    const int &st0rd0in_index = st0_index == -1 ? -1 : item->rightinnerfirstchild(st0_index); // first right inner dep
    const int &st1ld0in_index = st1_index == -1 ? -1 : item->leftinnerfirstchild(st1_index); // first left inner dep
    const int &st1rd0in_index = st1_index == -1 ? -1 : item->rightinnerfirstchild(st1_index); // first rightmost inner dep

    const int &st0ld1in_index = st0_index == -1 ? -1 : item->leftindep(st0_index); // leftmost inner dep
    const int &st0rd1in_index = st0_index == -1 ? -1 : item->rightindep(st0_index); // rightmost inner dep
    const int &st1ld1in_index = st1_index == -1 ? -1 : item->leftindep(st1_index); // leftmost inner dep
    const int &st1rd1in_index = st1_index == -1 ? -1 : item->rightindep(st1_index); // rightmost inner dep

    //queue
    const int &n0_index = item->nextword()==m_Sentence.size() ? -1 : item->nextword(); // next
    if(n0_index>=static_cast<int>(m_Sentence.size())) // the next index shouldn't exceed sentence
    {
        std::cout << "debug" << std::endl;
    }
    static int n1_index;
    static int n2_index;
    static int n3_index;
    n1_index = (n0_index != -1 && n0_index+1<m_Sentence.size()) ? n0_index+1 : -1 ;
    n2_index = (n0_index != -1 && n0_index+2<m_Sentence.size()) ? n0_index+2 : -1 ;
    n3_index = (n0_index != -1 && n0_index+3<m_Sentence.size()) ? n0_index+3 : -1 ;
    static int p1_index_start, p1_index_end;
    static int p2_index_start, p2_index_end;
    p1_index_end = item->nextword() > 0 ? item->nextword()-1 : -1;
    p1_index_start =  p1_index_end >= 0 ? item->wordstart(p1_index_end) : -1;
    p2_index_end = p1_index_start > 0 ? p1_index_start -1 : -1;
    p2_index_start =  p2_index_end >= 0 ? item->subwordstart(p2_index_end) : -1;





    const CWord &st0_word = st0_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st0_index), item->subwordend(st0_index)));
    const CWord &st1_word = st1_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st1_index), item->subwordend(st1_index)));
    const CWord &st0_char = st0_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st0_index, st0_index));
    const CWord &st1_char = st1_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st1_index, st1_index));
    const CWord &st2_char = st2_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st2_index, st2_index));
/*
    const unsigned long long &st0_charpos = st0_index==-1 ?  100 : item->subwordstart(st0_index) ==  item->subwordend(st0_index) ? 4 :
            ( item->subwordstart(st0_index) ==  st0_index ? 1 : (item->subwordend(st0_index) == st0_index ? 3 : 2)) ;
    const unsigned long long &st1_charpos = st1_index==-1 ?  100 : item->subwordstart(st1_index) ==  item->subwordend(st1_index) ? 4 :
            ( item->subwordstart(st1_index) ==  st1_index ? 1 : (item->subwordend(st1_index) == st1_index ? 3 : 2)) ;
    const unsigned long long &st2_charpos = st2_index==-1 ?  100 : item->subwordstart(st2_index) ==  item->subwordend(st2_index) ? 4 :
            ( item->subwordstart(st2_index) ==  st2_index ? 1 : (item->subwordend(st2_index) == st2_index ? 3 : 2)) ;
*/
    const CWord &st0_schar = st0_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st0_index), item->subwordstart(st0_index)));
    const CWord &st1_schar = st1_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st1_index), item->subwordstart(st1_index)));
    const CWord &st0_echar = st0_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordend(st0_index), item->subwordend(st0_index)));
    const CWord &st1_echar = st1_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordend(st1_index), item->subwordend(st1_index)));
    //   const CWord &st2_word = st2_index==-1 ?  g_emptyWord : m_lCache[st2_index];
    const CWord &st0ld1_word = st0ld1_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st0ld1_index), item->subwordend(st0ld1_index)));
    const CWord &st0rd1_word = st0rd1_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st0rd1_index), item->subwordend(st0rd1_index)));
    const CWord &st0ld2_word = st0ld2_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st0ld2_index), item->subwordend(st0ld2_index)));
    const CWord &st0rd2_word = st0rd2_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st0rd2_index), item->subwordend(st0rd2_index)));
    const CWord &st1ld1_word = st1ld1_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st1ld1_index), item->subwordend(st1ld1_index)));
    const CWord &st1rd1_word = st1rd1_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st1rd1_index), item->subwordend(st1rd1_index)));
    const CWord &st1ld2_word = st1ld2_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st1ld2_index), item->subwordend(st1ld2_index)));
    const CWord &st1rd2_word = st1rd2_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st1rd2_index), item->subwordend(st1rd2_index)));

    const CWord &st0ld1_char = st0ld1_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st0ld1_index, st0ld1_index));
    const CWord &st0rd1_char = st0rd1_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st0rd1_index, st0rd1_index));
    const CWord &st0ld2_char = st0ld2_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st0ld2_index, st0ld2_index));
    const CWord &st0rd2_char = st0rd2_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st0rd2_index, st0rd2_index));
    const CWord &st1ld1_char = st1ld1_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st1ld1_index, st1ld1_index));
    const CWord &st1rd1_char = st1rd1_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st1rd1_index, st1rd1_index));
    const CWord &st1ld2_char = st1ld2_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st1ld2_index, st1ld2_index));
    const CWord &st1rd2_char = st1rd2_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st1rd2_index, st1rd2_index));

/*
    const std::string &st0ld1_charpos = st0ld1_index==-1 ?  "##" : item->subwordstart(st0ld1_index) ==  item->subwordend(st0ld1_index) ? "#S" :
            ( item->subwordstart(st0ld1_index) ==  st0ld1_index ? "#B" : (item->subwordend(st0ld1_index) == st0ld1_index ? "#E" : "#M")) ;
    const std::string &st0rd1_charpos = st0rd1_index==-1 ?  "##" : item->subwordstart(st0rd1_index) ==  item->subwordend(st0rd1_index) ? "#S" :
            ( item->subwordstart(st0rd1_index) ==  st0rd1_index ? "#B" : (item->subwordend(st0rd1_index) == st0rd1_index ? "#E" : "#M")) ;
    const std::string &st0ld2_charpos = st0ld2_index==-1 ?  "##" : item->subwordstart(st0ld2_index) ==  item->subwordend(st0ld2_index) ? "#S" :
            ( item->subwordstart(st0ld2_index) ==  st0ld2_index ? "#B" : (item->subwordend(st0ld2_index) == st0ld2_index ? "#E" : "#M")) ;
    const std::string &st0rd2_charpos = st0rd2_index==-1 ?  "##" : item->subwordstart(st0rd2_index) ==  item->subwordend(st0rd2_index) ? "#S" :
            ( item->subwordstart(st0rd2_index) ==  st0rd2_index ? "#B" : (item->subwordend(st0rd2_index) == st0rd2_index ? "#E" : "#M")) ;
    const std::string &st1ld1_charpos = st1ld1_index==-1 ?  "##" : item->subwordstart(st1ld1_index) ==  item->subwordend(st1ld1_index) ? "#S" :
            ( item->subwordstart(st1ld1_index) ==  st1ld1_index ? "#B" : (item->subwordend(st1ld1_index) == st1ld1_index ? "#E" : "#M")) ;
    const std::string &st1rd1_charpos = st1rd1_index==-1 ?  "##" : item->subwordstart(st1rd1_index) ==  item->subwordend(st1rd1_index) ? "#S" :
            ( item->subwordstart(st1rd1_index) ==  st1rd1_index ? "#B" : (item->subwordend(st1rd1_index) == st1rd1_index ? "#E" : "#M")) ;
    const std::string &st1ld2_charpos = st1ld2_index==-1 ?  "##" : item->subwordstart(st1ld2_index) ==  item->subwordend(st1ld2_index) ? "#S" :
            ( item->subwordstart(st1ld2_index) ==  st1ld2_index ? "#B" : (item->subwordend(st1ld2_index) == st1ld2_index ? "#E" : "#M")) ;
    const std::string &st1rd2_charpos = st1rd2_index==-1 ?  "##" : item->subwordstart(st1rd2_index) ==  item->subwordend(st1rd2_index) ? "#S" :
            ( item->subwordstart(st1rd2_index) ==  st1rd2_index ? "#B" : (item->subwordend(st1rd2_index) == st1rd2_index ? "#E" : "#M")) ;
*/

    const CWord &st0ld0in_word = st0ld0in_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st0ld0in_index, st0_index));
    //const CWord &st0ld0in_word = st0rd0in_index == -1 && st0ld0in_index == -1 ?  g_emptyWord
    //        : (st0ld0in_index == -1 || (st0rd0in_index != -1 && st0_index - st0ld0in_index > st0rd0in_index - st0_index) ?  CWord(find_or_replace_word_cache(st0_index, st0rd0in_index))
    //               :  CWord(find_or_replace_word_cache(st0ld0in_index, st0_index)));
    const CWord &st0rd0in_word = st0rd0in_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st0_index, st0rd0in_index));
    const CWord &st1ld0in_word = st1ld0in_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st1ld0in_index, st1_index));
    const CWord &st1rd0in_word = st1rd0in_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(st1_index, st1rd0in_index));
    //const CWord &st1ld0in_word = st1rd0in_index == -1 && st1ld0in_index == -1 ?  g_emptyWord
    //        : (st1ld0in_index == -1 || (st1rd0in_index != -1 && st1_index - st1ld0in_index > st1rd0in_index - st1_index) ?  CWord(find_or_replace_word_cache(st1_index, st1rd0in_index))
    //               :  CWord(find_or_replace_word_cache(st1ld0in_index, st1_index)));

    const CWord &st0ld1in_word = st0ld1in_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st0ld1in_index), item->subwordend(st0ld1in_index)));
    const CWord &st0rd1in_word = st0rd1in_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st0rd1in_index), item->subwordend(st0rd1in_index)));
    const CWord &st1ld1in_word = st1ld1in_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st1ld1in_index), item->subwordend(st1ld1in_index)));
    const CWord &st1rd1in_word = st1rd1in_index == -1 ?  g_emptyWord : CWord(find_or_replace_word_cache(item->subwordstart(st1rd1in_index), item->subwordend(st1rd1in_index)));

    const CWord &p1_word = p1_index_start==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(p1_index_start, p1_index_end));
    const CWord &p2_word = p2_index_start==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(p2_index_start, p2_index_end));
    const CWord &n0_char = n0_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(n0_index, n0_index));
    const CWord &n1_char = n1_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(n1_index, n1_index));
    const CWord &n2_char = n2_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(n2_index, n2_index));
    const CWord &n3_char = n3_index==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(n3_index, n3_index));

    const CWord &p1_firstchar = p1_index_start==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(p1_index_start, p1_index_start));
    const CWord &p1_lastchar = p1_index_start==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(p1_index_end, p1_index_end));
    const CWord &p2_firstchar = p2_index_start==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(p2_index_start, p2_index_start));
    const CWord &p2_lastchar = p2_index_start==-1 ?  g_emptyWord : CWord(find_or_replace_word_cache(p2_index_end, p2_index_end));



    const CTag &st0_tag = st0_index==-1 ?  g_noneTag : CTag(item->pos(st0_index));
    const CTag &st1_tag = st1_index==-1 ?  g_noneTag : CTag(item->pos(st1_index));
    const CTag &st2_tag = st2_index==-1 ?  g_noneTag : CTag(item->pos(st2_index));

    const CTag &st0r1_tag = st0r1_index==-1||st0r1_index>=n0_index?  g_noneTag : CTag(item->pos(st0r1_index));
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

    unsigned long long st0_charcat = cast_weights->m_mapCharTagDictionary.lookup(st0_char) ;
    unsigned long long st1_charcat = cast_weights->m_mapCharTagDictionary.lookup(st1_char) ;

    unsigned long long p1_lastcharcat = cast_weights->m_mapCharTagDictionary.lookup(p1_lastchar) ;
    unsigned long long n0_charcat = cast_weights->m_mapCharTagDictionary.lookup(n0_char) ;
    unsigned long long n1_charcat = cast_weights->m_mapCharTagDictionary.lookup(n1_char) ;
    unsigned long long n2_charcat = cast_weights->m_mapCharTagDictionary.lookup(n2_char) ;
    unsigned long long n3_charcat = cast_weights->m_mapCharTagDictionary.lookup(n3_char) ;

    const CTag &p1_tag = p1_index_start==-1 ?  g_noneTag : CTag(item->pos(p1_index_start));
    const CTag &p2_tag = p2_index_start==-1 ?  g_noneTag : CTag(item->pos(p2_index_start));

    const unsigned long long p1_length = p1_index_start==-1 ? 99999 : p1_index_end - p1_index_start + 1;
    const unsigned long long p2_length = p2_index_start==-1 ? 99999 : p2_index_end - p2_index_start + 1;

    const unsigned long long p1_nlength = p1_index_start==-1 ? 99999 : (p1_length > 5 ? 5 : p1_length);
    const unsigned long long p2_nlength = p2_index_start==-1 ? 99999 : (p2_length > 5 ? 5 : p2_length);



    const unsigned long long st0st1_dist  = (item->m_lLabelTypes[st0_index] && item->m_lLabelTypes[st1_index]) ? encodeLinkDistance(item->wordindex(st0_index), item->wordindex(st1_index)) :
                                            ( (!item->m_lLabelTypes[st0_index] && !item->m_lLabelTypes[st1_index])  ?  encodeLinkDistance(st0_index, st1_index) : 9999);

    const unsigned long long st0_rarity = st0_index==-1?0:(item->rightarity(st0_index)-item->rightinnerarity(st0_index));
    const unsigned long long st0_larity = st0_index==-1?0:(item->leftarity(st0_index)-item->leftinnerarity(st0_index));
    const unsigned long long st1_rarity = st1_index==-1?0:(item->rightarity(st1_index)-item->rightinnerarity(st1_index));
    const unsigned long long st1_larity = st1_index==-1?0:(item->leftarity(st1_index)-item->leftinnerarity(st1_index));


    static CTuple2<CWord, unsigned long long> word_ulong;
    static CTuple2<unsigned long long, unsigned long long> ulong_ulong;
    static CTuple2<CWord, CWord> word_word;
    static CTuple2<CTag, CTag> tag_tag;
    static CTuple2<CTag, unsigned long long> tag_ulong;
    static CTuple3<CWord, CTag, CTag> word_tag_tag;
    static CTuple3<CTag, CTag, CTag> tag_tag_tag;
    static CTuple3<CWord, CWord, CTag> word_word_tag;
    static CTuple3<CWord, CWord, CWord> word_word_word;
    static CTuple3<unsigned long long, unsigned long long, unsigned long long> ulong_ulong_ulong;
    static CTuple4<CWord, CWord, CTag, CTag> word_word_tag_tag;
    static CTuple3<CWord, CWord, unsigned long long> word_word_ulong;
    static CTuple3<CWord, CTag, unsigned long long> word_tag_ulong;
    static CTuple3<CTag, CTag, unsigned long long> tag_tag_ulong;
    static CTuple2<CWord, CSetOfTags<CDependencyLabel> > word_tagset;
    static CTuple2<CTag, CSetOfTags<CDependencyLabel> > tag_tagset;


    //t:postag; w:word; c:head char; a: head char attriabute
    //shared features
    if(action != action::POP_WORD) {
        CWeight* curweights = amount == 0 ? static_cast<CWeight*>(m_weights) : static_cast<CWeight*>(m_delta_dep);
        //normal features
        {
            //S0
            if (st0_index != -1) {
                curweights->m_mapST0w.getOrUpdateScore( retval, st0_word, action, m_nScoreIndex, amount, round) ;
                curweights->m_mapST0t.getOrUpdateScore( retval, st0_tag, action, m_nScoreIndex, amount, round ) ;
                curweights->m_mapST0wt.getOrUpdateScore( retval, std::make_pair(st0_word, st0_tag), action, m_nScoreIndex, amount, round) ;
            }

            //S1
            if (st1_index != -1) {
                curweights->m_mapST1w.getOrUpdateScore( retval, st1_word, action, m_nScoreIndex, amount, round) ;
                curweights->m_mapST1t.getOrUpdateScore( retval, st1_tag, action, m_nScoreIndex, amount, round ) ;
                curweights->m_mapST1wt.getOrUpdateScore( retval, std::make_pair(st1_word, st1_tag), action, m_nScoreIndex, amount, round) ;

            }


            //N0
            if (n0_index != -1) {
                curweights->m_mapN0c.getOrUpdateScore( retval, n0_char, action, m_nScoreIndex, amount, round ) ;
                //curweights->m_mapN0a.getOrUpdateScore( retval, n0_charcat, action, m_nScoreIndex, amount, round ) ;
            }



            //S0S1
            if (st1_index != -1) {
                refer_or_allocate_tuple2(word_word, &st0_word, &st1_word);
                curweights->m_mapST0wST1w.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple2(tag_tag, &st0_tag, &st1_tag);
                curweights->m_mapST0tST1t.getOrUpdateScore( retval, tag_tag, action, m_nScoreIndex, amount, round ) ;
                refer_or_allocate_tuple3(word_tag_tag, &st0_word, &st0_tag, &st1_tag);
                curweights->m_mapST0wtST1t.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(word_tag_tag, &st1_word, &st0_tag, &st1_tag);
                curweights->m_mapST0tST1wt.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(word_word_tag, &st0_word, &st1_word, &st0_tag);
                curweights->m_mapST0wtST1w.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(word_word_tag, &st0_word, &st1_word, &st1_tag);
                curweights->m_mapST0wST1wt.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple4(word_word_tag_tag, &st0_word, &st1_word, &st0_tag, &st1_tag);
                curweights->m_mapST0wtST1wt.getOrUpdateScore( retval, word_word_tag_tag, action, m_nScoreIndex, amount, round) ;



                //refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st1_tag, &st1l1_tag);
                //curweights->m_mapST0tST1tST1L1t.getOrUpdateScore( retval, tag_tag_tag, action, m_nScoreIndex, amount, round) ;
                //refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st1_tag, &st1r1_tag);
                //curweights->m_mapST0tST1tST1R1t.getOrUpdateScore( retval, tag_tag_tag, action, m_nScoreIndex, amount, round) ;
                //refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st1_tag, &st0l1_tag);
                //curweights->m_mapST0tST1tST0L1t.getOrUpdateScore( retval, tag_tag_tag, action, m_nScoreIndex, amount, round) ;

            }

            //S0N0
            if (st0_index != -1 && n0_index != -1) {
                refer_or_allocate_tuple2(word_word, &st0_word, &n0_char);
                curweights->m_mapST0wN0c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(word_word_tag, &st0_word, &n0_char, &st0_tag);
                curweights->m_mapST0wtN0c.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round) ;
            }


            //S0S1N0
            if (st1_index != -1 && n0_index != -1) {
                refer_or_allocate_tuple3(word_tag_tag, &n0_char, &st0_tag, &st1_tag);
                curweights->m_mapST0tST1tN0c.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(word_word_tag, &n0_char, &st1_word, &st0_tag);
                curweights->m_mapST0tST1wN0c.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(word_word_tag, &n0_char, &st0_word, &st1_tag);
                curweights->m_mapST0wST1tN0c.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round) ;
            }

            //S0S1ST1LD1
            if(st1_index != -1 && st1ld1_index != -1) {
                refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st1_tag, &st1ld1_tag);
                curweights->m_mapST0tST1tST1LD1t.getOrUpdateScore( retval, tag_tag_tag, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(word_tag_tag, &st0_word, &st1_tag, &st1ld1_tag);
                curweights->m_mapST0wST1tST1LD1t.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
            }

            //S0S1ST1RD1
            if(st1_index != -1 && st1rd1_index != -1) {
                refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st1_tag, &st1rd1_tag);
                curweights->m_mapST0tST1tST1RD1t.getOrUpdateScore( retval, tag_tag_tag, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(word_tag_tag, &st0_word, &st1_tag, &st1rd1_tag);
                curweights->m_mapST0wST1tST1RD1t.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
            }

            //S0S1ST0LD1
            if(st1_index != -1 && st0ld1_index != -1) {
                refer_or_allocate_tuple3(tag_tag_tag, &st1_tag, &st0_tag, &st0ld1_tag);
                curweights->m_mapST1tST0tST0LD1t.getOrUpdateScore( retval, tag_tag_tag, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(word_tag_tag, &st1_word, &st0_tag, &st0ld1_tag);
                curweights->m_mapST1wST0tST0LD1t.getOrUpdateScore( retval, word_tag_tag, action, m_nScoreIndex, amount, round) ;
            }

            //ST0LD1
            if(st0_index != -1 && st0ld1_index != -1) {
                curweights->m_mapST0LD1w.getOrUpdateScore( retval, st0ld1_word, action, m_nScoreIndex, amount, round) ;
                curweights->m_mapST0LD1t.getOrUpdateScore( retval, st0ld1_tag, action, m_nScoreIndex, amount, round ) ;
                curweights->m_mapST0LD1wt.getOrUpdateScore( retval, std::make_pair(st0ld1_word, st0ld1_tag), action, m_nScoreIndex, amount, round) ;
            }

            //ST1LD1
            if(st1_index != -1 && st1ld1_index != -1) {
                curweights->m_mapST1LD1w.getOrUpdateScore( retval, st1ld1_word, action, m_nScoreIndex, amount, round) ;
                curweights->m_mapST1LD1t.getOrUpdateScore( retval, st1ld1_tag, action, m_nScoreIndex, amount, round ) ;
                curweights->m_mapST1LD1wt.getOrUpdateScore( retval, std::make_pair(st1ld1_word, st1ld1_tag), action, m_nScoreIndex, amount, round) ;
            }


            //ST1RD1
            if(st1_index != -1 && st1rd1_index != -1) {
                curweights->m_mapST1RD1w.getOrUpdateScore( retval, st1rd1_word, action, m_nScoreIndex, amount, round) ;
                curweights->m_mapST1RD1t.getOrUpdateScore( retval, st1rd1_tag, action, m_nScoreIndex, amount, round ) ;
                curweights->m_mapST1RD1wt.getOrUpdateScore( retval, std::make_pair(st1rd1_word, st1rd1_tag), action, m_nScoreIndex, amount, round) ;
            }


            //ST0ST0LD1ST0LD2
            if(st0_index != -1 && st0ld1_index != -1 && st0ld2_index != -1) {
                refer_or_allocate_tuple3(tag_tag_tag, &st0_tag, &st0ld1_tag, &st0ld2_tag);
                curweights->m_mapST0tST0LD1tST0LD2t.getOrUpdateScore( retval, tag_tag_tag, action, m_nScoreIndex, amount, round) ;
            }

            //ST1ST1LD1ST1LD2
            if(st1_index != -1 && st1ld1_index != -1 && st1ld2_index != -1) {
                refer_or_allocate_tuple3(tag_tag_tag, &st1_tag, &st1ld1_tag, &st1ld2_tag);
                curweights->m_mapST1tST1LD1tST1LD2t.getOrUpdateScore( retval, tag_tag_tag, action, m_nScoreIndex, amount, round) ;
            }

            //ST1ST1RD1ST1RD2
            if(st1_index != -1 && st1rd1_index != -1 && st1rd2_index != -1) {
                refer_or_allocate_tuple3(tag_tag_tag, &st1_tag, &st1rd1_tag, &st1rd2_tag);
                curweights->m_mapST1tST1RD1tST1RD2t.getOrUpdateScore( retval, tag_tag_tag, action, m_nScoreIndex, amount, round) ;
            }


            //S0S1S2
            if(st2_index != -1) {
                refer_or_allocate_tuple3(tag_tag_tag, &st2_tag, &st1_tag, &st0_tag);
                curweights->m_mapST2tST1tST0t.getOrUpdateScore( retval, tag_tag_tag, action, m_nScoreIndex, amount, round) ;
            }


            //stacking features put here, users can define own features here
        }

        /*
        if(action == action::NO_ACTION || action  >= action::POP_ROOT) {
            //S0
            if (st0_index != -1) {
                refer_or_allocate_tuple2(word_ulong, &st0_word, &st0_larity);
                curweights->m_mapST0wLARITY.getOrUpdateScore( retval, word_ulong, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple2(tag_ulong, &st0_tag, &st0_larity);
                curweights->m_mapST0tLARITY.getOrUpdateScore( retval, tag_ulong, action, m_nScoreIndex, amount, round) ;
            }

            //S1
            if (st1_index != -1) {
                refer_or_allocate_tuple2(word_ulong, &st1_word, &st1_larity);
                curweights->m_mapST1wLARITY.getOrUpdateScore( retval, word_ulong, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple2(tag_ulong, &st1_tag, &st1_larity);
                curweights->m_mapST1tLARITY.getOrUpdateScore( retval, tag_ulong, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple2(word_ulong, &st1_word, &st1_rarity);
                curweights->m_mapST1wRARITY.getOrUpdateScore( retval, word_ulong, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple2(tag_ulong, &st1_tag, &st1_rarity);
                curweights->m_mapST1tRARITY.getOrUpdateScore( retval, tag_ulong, action, m_nScoreIndex, amount, round) ;
            }

            //S0S1
            if (st1_index != -1) {
                refer_or_allocate_tuple2(word_ulong, &st0_word, &st0st1_dist);
                curweights->m_mapST0wDist.getOrUpdateScore( retval, word_ulong, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple2(word_ulong, &st1_word, &st0st1_dist);
                curweights->m_mapST1wDist.getOrUpdateScore( retval, word_ulong, action, m_nScoreIndex, amount, round ) ;
                refer_or_allocate_tuple2(tag_ulong, &st0_tag, &st0st1_dist);
                curweights->m_mapST0tDist.getOrUpdateScore( retval, tag_ulong, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple2(tag_ulong, &st1_tag, &st0st1_dist);
                curweights->m_mapST1tDist.getOrUpdateScore( retval, tag_ulong, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(word_word_ulong, &st0_word, &st1_word, &st0st1_dist);
                curweights->m_mapST0wST1wDist.getOrUpdateScore( retval, word_word_ulong, action, m_nScoreIndex, amount, round) ;
                refer_or_allocate_tuple3(tag_tag_ulong, &st0_tag, &st1_tag, &st0st1_dist);
                curweights->m_mapST0tST1tDist.getOrUpdateScore( retval, tag_tag_ulong, action, m_nScoreIndex, amount, round) ;
            }
        }
*/

        if(action == action::NO_ACTION || action  >= action::POP_ROOT) {//character  features
            {

                //S0
                if (st0_index != -1) {
                    curweights->m_mapST0c.getOrUpdateScore( retval, st0_char, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST0ct.getOrUpdateScore( retval, std::make_pair(st0_char, st0_tag), action, m_nScoreIndex, amount, round) ;
                }

                //S1
                if (st1_index != -1) {
                    curweights->m_mapST1c.getOrUpdateScore( retval, st1_char, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST1ct.getOrUpdateScore( retval, std::make_pair(st1_char, st1_tag), action, m_nScoreIndex, amount, round) ;
                }


                //S0S1
                if (st1_index != -1) {
                    refer_or_allocate_tuple2(word_word, &st0_char, &st1_char);
                    curweights->m_mapST0cST1c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st0_word, &st1_char);
                    curweights->m_mapST0wST1c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st0_char, &st1_word);
                    curweights->m_mapST0cST1w.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple3(word_word_tag, &st0_word, &st1_char, &st0_tag);
                    curweights->m_mapST0wtST1c.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple3(word_word_tag, &st0_char, &st1_word, &st1_tag);
                    curweights->m_mapST0cST1wt.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple3(word_word_tag, &st0_word, &st1_char, &st1_tag);
                    curweights->m_mapST0wST1ct.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple3(word_word_tag, &st0_char, &st1_word, &st0_tag);
                    curweights->m_mapST0ctST1w.getOrUpdateScore( retval, word_word_tag, action, m_nScoreIndex, amount, round) ;
                }


                //S0N0
                //if (st0_index != -1 && n0_index != -1) {
                //    refer_or_allocate_tuple2(word_word, &st0_char, &n0_char);
                //    curweights->m_mapST0cN0c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                //}

                //S0S1N0
                //if (st1_index != -1 && n0_index != -1) {
                //    refer_or_allocate_tuple3(word_word_word, &st1_char, &st0_char, &n0_char);
                //    curweights->m_mapST1cST0cN0c.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round) ;
                //}

                //S0S1S2
                if(st2_index != -1) {
                    refer_or_allocate_tuple3(word_word_word, &st2_char, &st1_char, &st0_char);
                    curweights->m_mapST2cST1cST0c.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round) ;
                }


                //S0S1ST1LD1
                if(st1_index != -1 && st1ld1_index != -1) {
                    refer_or_allocate_tuple3(word_word_word, &st0_char, &st1ld1_char, &st1_char);
                    curweights->m_mapST0cST1cST1LD1c.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round) ;
                }

                //S0S1ST1RD1
                if(st1_index != -1 && st1rd1_index != -1) {
                    refer_or_allocate_tuple3(word_word_word, &st0_char, &st1_char, &st1rd1_char);
                    curweights->m_mapST0cST1cST1RD1c.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round) ;
                }

                //S0S1ST0LD1
                if(st1_index != -1 && st0ld1_index != -1) {
                    refer_or_allocate_tuple3(word_word_word, &st1_char, &st0_char, &st0ld1_char);
                    curweights->m_mapST1cST0cST0LD1c.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round) ;
                }

                //ST0LD1
                if(st0_index != -1 && st0ld1_index != -1) {
                    curweights->m_mapST0LD1ct.getOrUpdateScore( retval, std::make_pair(st0ld1_char, st0ld1_tag), action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st0_char, &st0ld1_char);
                    curweights->m_mapST0cST0LD1c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                //ST1LD1
                if(st1_index != -1 && st1ld1_index != -1) {
                    curweights->m_mapST1LD1ct.getOrUpdateScore( retval, std::make_pair(st1ld1_char, st1ld1_tag), action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st1_char, &st1ld1_char);
                    curweights->m_mapST1cST1LD1c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }


                //ST1RD1
                if(st1_index != -1 && st1rd1_index != -1) {
                    curweights->m_mapST1RD1ct.getOrUpdateScore( retval, std::make_pair(st1rd1_char, st1rd1_tag), action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st1_char, &st1rd1_char);
                    curweights->m_mapST1cST1RD1c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }


                //ST0ST0LD1ST0LD2
                if(st0_index != -1 && st0ld1_index != -1 && st0ld2_index != -1) {
                    refer_or_allocate_tuple3(word_word_word, &st0_char, &st0ld1_char, &st0ld2_char);
                    curweights->m_mapST0cST0LD1cST0LD2c.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round) ;
                }

                //ST1ST1LD1ST1LD2
                if(st1_index != -1 && st1ld1_index != -1 && st1ld2_index != -1) {
                    refer_or_allocate_tuple3(word_word_word, &st1_char, &st1ld1_char, &st1ld2_char);
                    curweights->m_mapST1cST1LD1cST1LD2c.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round) ;
                }

                //ST1ST1RD1ST1RD2
                if(st1_index != -1 && st1rd1_index != -1 && st1rd2_index != -1) {
                    refer_or_allocate_tuple3(word_word_word, &st1_char, &st1rd1_char, &st1rd2_char);
                    curweights->m_mapST1cST1RD1cST1RD2c.getOrUpdateScore( retval, word_word_word, action, m_nScoreIndex, amount, round) ;
                }
            }

        //}

        //if(action == action::NO_ACTION || action  >= action::POP_ROOT) {
          /*
            {
                //S0
                if (st0_index != -1) {
                    curweights->m_mapST0sc.getOrUpdateScore( retval, st0_schar, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST0sct.getOrUpdateScore( retval, std::make_pair(st0_schar, st0_tag), action, m_nScoreIndex, amount, round) ;
                }

                //S1
                if (st1_index != -1) {
                    curweights->m_mapST1sc.getOrUpdateScore( retval, st1_schar, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST1sct.getOrUpdateScore( retval, std::make_pair(st1_schar, st1_tag), action, m_nScoreIndex, amount, round) ;
                }

                //S0S1
                if (st1_index != -1) {
                    refer_or_allocate_tuple2(word_word, &st0_schar, &st1_schar);
                    curweights->m_mapST0scST1sc.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                //S0N0
                //if (st0_index != -1 && n0_index != -1) {
                //    refer_or_allocate_tuple2(word_word, &st0_schar, &n0_char);
                //    curweights->m_mapST0scN0c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                //}

                //S0
                if (st0_index != -1) {
                    curweights->m_mapST0ec.getOrUpdateScore( retval, st0_echar, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST0ect.getOrUpdateScore( retval, std::make_pair(st0_echar, st0_tag), action, m_nScoreIndex, amount, round) ;
                }

                //S1
                if (st1_index != -1) {
                    curweights->m_mapST1ec.getOrUpdateScore( retval, st1_echar, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST1ect.getOrUpdateScore( retval, std::make_pair(st1_echar, st1_tag), action, m_nScoreIndex, amount, round) ;
                }

                //S0S1
                if (st1_index != -1) {
                    refer_or_allocate_tuple2(word_word, &st0_echar, &st1_echar);
                    curweights->m_mapST0ecST1ec.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                //S0N0
                //if (st0_index != -1 && n0_index != -1) {
                //    refer_or_allocate_tuple2(word_word, &st0_echar, &n0_char);
                //    curweights->m_mapST0ecN0c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                //}
            }*/

/*
            {
                //S0
                if (st0_index != -1 && st0ld1in_index != -1) {
                    curweights->m_mapST0lsw.getOrUpdateScore( retval, st0ld1in_word, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST0lswt.getOrUpdateScore( retval, std::make_pair(st0ld1in_word, st0_tag), action, m_nScoreIndex, amount, round) ;
                }

                if (st0_index != -1 && st0rd1in_index != -1) {
                    curweights->m_mapST0rsw.getOrUpdateScore( retval, st0rd1in_word, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST0rswt.getOrUpdateScore( retval, std::make_pair(st0rd1in_word, st0_tag), action, m_nScoreIndex, amount, round) ;
                }

                //S1
                if (st1_index != -1 && st1ld1in_index != -1) {
                    curweights->m_mapST1lsw.getOrUpdateScore( retval, st1ld1in_word, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST1lswt.getOrUpdateScore( retval, std::make_pair(st1ld1in_word, st1_tag), action, m_nScoreIndex, amount, round) ;
                }

                if (st1_index != -1 && st1rd1in_index != -1) {
                    curweights->m_mapST1rsw.getOrUpdateScore( retval, st1rd1in_word, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST1rswt.getOrUpdateScore( retval, std::make_pair(st1rd1in_word, st1_tag), action, m_nScoreIndex, amount, round) ;
                }


                //S0S1
                if (st1_index != -1 && st0ld1in_index != -1) {
                    //refer_or_allocate_tuple2(word_word, &st0ld1in_word, &st1_char);
                    //curweights->m_mapST0lswST1c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st0ld1in_word, &st1_word);
                    curweights->m_mapST0lswST1w.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                if (st1_index != -1 && st0rd1in_index != -1) {
                    //refer_or_allocate_tuple2(word_word, &st0rd1in_word, &st1_char);
                    //curweights->m_mapST0rswST1c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st0rd1in_word, &st1_word);
                    curweights->m_mapST0rswST1w.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                if (st1_index != -1 && st1ld1in_index != -1) {
                    //refer_or_allocate_tuple2(word_word, &st1ld1in_word, &st0_char);
                    //curweights->m_mapST0cST1lsw.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st1ld1in_word, &st0_word);
                    curweights->m_mapST0wST1lsw.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                if (st1_index != -1 && st1rd1in_index != -1) {
                    //refer_or_allocate_tuple2(word_word, &st1rd1in_word, &st0_char);
                    //curweights->m_mapST0cST1rsw.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st1rd1in_word, &st0_word);
                    curweights->m_mapST0wST1rsw.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                //S0N0
                //if (st0_index != -1 && n0_index != -1 && st0ld1in_index != -1) {
                //    refer_or_allocate_tuple2(word_word, &st0ld1in_word, &n0_char);
                //    curweights->m_mapST0lswN0c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                //}

                //if (st0_index != -1 && n0_index != -1 && st0rd1in_index != -1) {
                //    refer_or_allocate_tuple2(word_word, &st0rd1in_word, &n0_char);
                //    curweights->m_mapST0rswN0c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                //}
             }
*/


            { 
                //S0
                if (st0_index != -1 && st0ld0in_index != -1) {
                    curweights->m_mapST0l0sw.getOrUpdateScore( retval, st0ld0in_word, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST0l0swt.getOrUpdateScore( retval, std::make_pair(st0ld0in_word, st0_tag), action, m_nScoreIndex, amount, round) ;
                }

                if (st0_index != -1 && st0rd0in_index != -1) {
                    curweights->m_mapST0r0sw.getOrUpdateScore( retval, st0rd0in_word, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST0r0swt.getOrUpdateScore( retval, std::make_pair(st0rd0in_word, st0_tag), action, m_nScoreIndex, amount, round) ;
                }

                //S1
                if (st1_index != -1 && st1ld0in_index != -1) {
                    curweights->m_mapST1l0sw.getOrUpdateScore( retval, st1ld0in_word, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST1l0swt.getOrUpdateScore( retval, std::make_pair(st1ld0in_word, st1_tag), action, m_nScoreIndex, amount, round) ;
                }

                if (st1_index != -1 && st1rd0in_index != -1) {
                    curweights->m_mapST1r0sw.getOrUpdateScore( retval, st1rd0in_word, action, m_nScoreIndex, amount, round) ;
                    curweights->m_mapST1r0swt.getOrUpdateScore( retval, std::make_pair(st1rd0in_word, st1_tag), action, m_nScoreIndex, amount, round) ;
                }


                //S0S1
                if (st1_index != -1 && st0ld0in_index != -1 ) {
                    //refer_or_allocate_tuple2(word_word, &st0ld0in_word, &st1_char);
                    //curweights->m_mapST0l0swST1c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st0ld0in_word, &st1_word);
                    curweights->m_mapST0l0swST1w.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                if (st1_index != -1 && st0rd0in_index != -1) {
                    //refer_or_allocate_tuple2(word_word, &st0rd0in_word, &st1_char);
                    //curweights->m_mapST0r0swST1c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st0rd0in_word, &st1_word);
                    curweights->m_mapST0r0swST1w.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                if (st1_index != -1 && st1ld0in_index != -1) {
                    //refer_or_allocate_tuple2(word_word, &st1ld0in_word, &st0_char);
                    //curweights->m_mapST0cST1l0sw.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st1ld0in_word, &st0_word);
                    curweights->m_mapST0wST1l0sw.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                if (st1_index != -1 && st1rd0in_index != -1) {
                    //refer_or_allocate_tuple2(word_word, &st1rd0in_word, &st0_char);
                    //curweights->m_mapST0cST1r0sw.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                    refer_or_allocate_tuple2(word_word, &st1rd0in_word, &st0_word);
                    curweights->m_mapST0wST1r0sw.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                }

                //S0N0
                //if (st0_index != -1 && n0_index != -1 && st0ld0in_index != -1) {
                //    refer_or_allocate_tuple2(word_word, &st0ld0in_word, &n0_char);
                //    curweights->m_mapST0l0swN0c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                //}

                //if (st0_index != -1 && n0_index != -1 && st0rd0in_index != -1) {
                //    refer_or_allocate_tuple2(word_word, &st0rd0in_word, &n0_char);
                //    curweights->m_mapST0r0swN0c.getOrUpdateScore( retval, word_word, action, m_nScoreIndex, amount, round) ;
                //}
            }



        }
    }





// POS Tagging features
    if(n0_index != -1 && (action == action::NO_ACTION || action  >= action::LABEL_SH_FIRST)) {
        CWeight* curweights = amount == 0 ? static_cast<CWeight*>(m_weights) : static_cast<CWeight*>(m_delta_pos);
        curweights->m_mapLastTagByTag.getOrUpdateScore(retval, p1_tag,  action, m_nScoreIndex , amount , round ) ;
        if (p1_index_start != -1) {
            refer_or_allocate_tuple2(tag_ulong, &(p1_tag), &(p1_nlength));
            curweights->m_mapTag0Tag1Size1.getOrUpdateScore(retval, tag_ulong,  action, m_nScoreIndex , amount , round ) ;
        }
        if (p2_index_start != -1) {
            refer_or_allocate_tuple3(tag_tag_ulong, &(p1_tag), &(p2_tag), &(p1_nlength));
            curweights->m_mapTag0Tag1Tag2Size1.getOrUpdateScore(retval, tag_tag_ulong,  action, m_nScoreIndex , amount , round ) ;
        }

        if (p1_nlength <= 2 ) {
            curweights->m_mapTagByLastWord.getOrUpdateScore(retval, p1_word ,  action, m_nScoreIndex , amount , round ) ;
        }

        if ( p2_index_start != -1 ) {
            refer_or_allocate_tuple2(tag_tag, &p1_tag, &(p2_tag));
            curweights->m_mapLastTwoTagsByTag.getOrUpdateScore(retval, tag_tag,  action, m_nScoreIndex , amount , round ) ;
        }

        curweights->m_mapTagByFirstChar.getOrUpdateScore(retval, n0_char ,  action, m_nScoreIndex , amount , round ) ;
        curweights->m_mapTagByFirstCharCat.getOrUpdateScore(retval, n0_charcat ,  action, m_nScoreIndex , amount , round ) ;
        curweights->m_mapFirstCharBy2Tags.getOrUpdateScore(retval, std::make_pair(n0_char, p1_tag),  action, m_nScoreIndex , amount , round ) ;
        if (p2_index_start != -1) {
            refer_or_allocate_tuple3(word_tag_tag, &(n0_char), &(p1_tag), &(p2_tag));
            curweights->m_mapFirstCharBy3Tags.getOrUpdateScore(retval, word_tag_tag ,  action, m_nScoreIndex , amount , round ) ;
        }

        if (p1_index_start != -1) {
            refer_or_allocate_tuple3(word_word_tag, &(n0_char), &(p1_lastchar), &(p1_tag));
            curweights->m_mapTaggedSeparateChars.getOrUpdateScore(retval, word_word_tag,  action, m_nScoreIndex , amount , round ) ;
        }


        if (p2_index_start != -1) {
            curweights->m_mapTagWordTag.getOrUpdateScore(retval, std::make_pair(p1_word, p2_tag),  action, m_nScoreIndex, amount, round);
        }

        if (p2_index_start != -1) {
            curweights->m_mapWordTagTag.getOrUpdateScore(retval, std::make_pair(p2_word, p1_tag),  action, m_nScoreIndex, amount, round);
        }

    }



    if(item->stacksize() > 1 && action <= action::ARC_RIGHT_IN && !item->m_lLabelTypes[st0_index] && !item->m_lLabelTypes[st1_index])
    {
        CWeight* curweights = amount == 0 ? static_cast<CWeight*>(m_weights) : static_cast<CWeight*>(m_delta_dep);
        const CWord & mergedst0st1_word = CWord(find_or_replace_word_cache(item->subwordstart(st1_index), item->subwordend(st0_index)));
        unsigned long long  mergedst0st1_length = item->subwordend(st0_index) - item->subwordstart(st1_index) > 5 ? 5 : item->subwordend(st0_index) - item->subwordstart(st1_index);
        //curweights->m_mapN1c.getOrUpdateScore( retval, mergedst0st1_word, action, m_nScoreIndex, amount, round );
        if(cast_weights->m_mapSubWordFrequency.find(mergedst0st1_word, 0) > cast_weights->m_nMaxWordFrequency/5000+3)
        {
            curweights->m_mapCurentSubWordInDict.getOrUpdateScore(retval, mergedst0st1_length , action, m_nScoreIndex , amount , round ) ;
            refer_or_allocate_tuple2(tag_ulong, &(st0_tag), &(mergedst0st1_length));
            curweights->m_mapCurentSubWordInDictByTag.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;
            refer_or_allocate_tuple2(word_word, &(mergedst0st1_word), &(st1_char));
            if(cast_weights->m_mapSubWordHeadWordDictionary.find(word_word, 0) > cast_weights->m_nMaxWordFrequency/5000+3)
            {
                curweights->m_mapCurentSubWordInDictRight.getOrUpdateScore(retval, mergedst0st1_length , action, m_nScoreIndex , amount , round ) ;
                refer_or_allocate_tuple2(tag_ulong, &(st0_tag), &(mergedst0st1_length));
                curweights->m_mapCurentSubWordInDictByTagRight.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;
            }
            refer_or_allocate_tuple2(word_word, &(mergedst0st1_word), &(st0_char));
            if(cast_weights->m_mapSubWordHeadWordDictionary.find(word_word, 0) > cast_weights->m_nMaxWordFrequency/5000+3)
            {
                curweights->m_mapCurentSubWordInDictLeft.getOrUpdateScore(retval, mergedst0st1_length , action, m_nScoreIndex , amount , round ) ;
                refer_or_allocate_tuple2(tag_ulong, &(st0_tag), &(mergedst0st1_length));
                curweights->m_mapCurentSubWordInDictByTagLeft.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;
            }
        }
        //else
        //{
        //    curweights->m_mapCurentSubWordOutDict.getOrUpdateScore(retval, mergedst0st1_length , action, m_nScoreIndex , amount , round ) ;
        //    refer_or_allocate_tuple2(tag_ulong, &(st0_tag), &(mergedst0st1_length));
        //    curweights->m_mapCurentSubWordOutDictByTag.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;
        //}
    }


    if( item->stacksize() > 0 && (action == action::NO_ACTION || action == action::POP_WORD)) {
        CWeight* curweights = amount == 0 ? static_cast<CWeight*>(m_weights) : static_cast<CWeight*>(m_delta_pos);
        curweights->m_mapCurentWord.getOrUpdateScore(retval, p1_word , action, m_nScoreIndex , amount , round ) ;
        curweights->m_mapCurentWordTag.getOrUpdateScore(retval, std::make_pair(p1_word, p1_tag), action, m_nScoreIndex , amount , round ) ;
        refer_or_allocate_tuple2(word_word, &(p1_word), &(p2_word));
        curweights->m_mapLastWordByWord.getOrUpdateScore(retval, word_word , action, m_nScoreIndex , amount , round ) ;

        if(cast_weights->m_mapWordFrequency.find(p1_word, 0) > cast_weights->m_nMaxWordFrequency/5000+3)
        {
            curweights->m_mapCurentWordInDict.getOrUpdateScore(retval, p1_nlength , action, m_nScoreIndex , amount , round ) ;
            refer_or_allocate_tuple2(tag_ulong, &(p1_tag), &(p1_nlength));
            curweights->m_mapCurentWordInDictByTag.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;
            if(cast_weights->m_mapWordTagDictionary.lookup(p1_word, p1_tag))
            {
                curweights->m_mapCurentWordInTagDict.getOrUpdateScore(retval, p1_nlength , action, m_nScoreIndex , amount , round ) ;
                refer_or_allocate_tuple2(tag_ulong, &(p1_tag), &(p1_nlength));
                curweights->m_mapCurentWordInTagDictByTag.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;
            }
            else
            {
                curweights->m_mapCurentWordInDictOutTagDict.getOrUpdateScore(retval, p1_nlength , action, m_nScoreIndex , amount , round ) ;
                refer_or_allocate_tuple2(tag_ulong, &(p1_tag), &(p1_nlength));
                curweights->m_mapCurentWordInDictOutTagDictByTag.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;
            }

            /*
            refer_or_allocate_tuple2(word_word, &(p1_word), &(st0_char));
            if(cast_weights->m_mapSubWordHeadWordDictionary.find(word_word, 0) > 0)
            {
                curweights->m_mapCurentSubWordInDictRight.getOrUpdateScore(retval, p1_nlength , action, m_nScoreIndex , amount , round ) ;
                refer_or_allocate_tuple2(tag_ulong, &(p1_tag), &(p1_nlength));
                curweights->m_mapCurentSubWordInDictByTagRight.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;
            }
            else
            {
                curweights->m_mapCurentSubWordOutDict.getOrUpdateScore(retval, p1_nlength , action, m_nScoreIndex , amount , round ) ;
                refer_or_allocate_tuple2(tag_ulong, &(p1_tag), &(p1_nlength));
                curweights->m_mapCurentSubWordOutDictByTag.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;
            }*/
        }
        else
        {
            curweights->m_mapCurentWordOutDict.getOrUpdateScore(retval, p1_nlength , action, m_nScoreIndex , amount , round ) ;
            refer_or_allocate_tuple2(tag_ulong, &(p1_tag), &(p1_nlength));
            curweights->m_mapCurentWordOutDictByTag.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;
        }




        if ( p1_nlength == 1 ) {
            curweights->m_mapOneCharWord.getOrUpdateScore(retval, p1_word , action, m_nScoreIndex , amount , round ) ;
        } else {
            refer_or_allocate_tuple2(word_word, &(p1_firstchar), &(p1_lastchar));
            curweights->m_mapFirstAndLastChars.getOrUpdateScore(retval, word_word , action, m_nScoreIndex , amount , round ) ;
            refer_or_allocate_tuple2(word_ulong, &(p1_firstchar), &(p1_nlength));
            curweights->m_mapLengthByFirstChar.getOrUpdateScore(retval, word_ulong , action, m_nScoreIndex , amount , round ) ;
            refer_or_allocate_tuple2(word_ulong, &(p1_lastchar), &(p1_nlength));
            curweights->m_mapLengthByLastChar.getOrUpdateScore(retval, word_ulong, action, m_nScoreIndex , amount , round ) ;
        }

        if (p2_index_start != -1) {
            refer_or_allocate_tuple2(word_word, &(p1_word), &(p2_lastchar));
            curweights->m_mapCurrentWordLastChar.getOrUpdateScore(retval, word_word, action, m_nScoreIndex , amount , round ) ;
            refer_or_allocate_tuple2(word_word, &(p1_lastchar), &(p2_lastchar));
            curweights->m_mapLastWordByLastChar.getOrUpdateScore(retval, word_word, action, m_nScoreIndex , amount , round ) ;
        }


        if ( p1_nlength <= 2 && p2_index_start != -1) {
            curweights->m_mapLastTagByWord.getOrUpdateScore(retval, std::make_pair(p1_word, p2_tag), action, m_nScoreIndex , amount , round ) ;
        }

        if (p2_index_start != -1) {
            if ( p1_nlength <= 2 ) {
                refer_or_allocate_tuple3(word_word_tag, &(p1_word), &(p2_lastchar), &(p1_tag));
                curweights->m_mapTagByWordAndPrevChar.getOrUpdateScore(retval, word_word_tag, action, m_nScoreIndex , amount , round ) ;
            }
            if ( p1_nlength == 1 && n0_index != -1 ) {
                refer_or_allocate_tuple3(word_word_word, &(p2_lastchar), &(p1_word), &(n0_char));
                curweights->m_mapTagOfOneCharWord.getOrUpdateScore(retval, word_word_word, action, m_nScoreIndex , amount , round ) ;
            }
        }

        curweights->m_mapTagByLastChar.getOrUpdateScore(retval, std::make_pair(p1_lastchar, p1_tag) , action, m_nScoreIndex , amount , round ) ;

        refer_or_allocate_tuple2(tag_ulong, &(p1_tag), &(p1_lastcharcat));
        curweights->m_mapTagByLastCharCat.getOrUpdateScore(retval, tag_ulong , action, m_nScoreIndex , amount , round ) ;

        for(int idx = 1; idx < p1_length-1; idx++) {
            const CWord &p1_inchar = find_or_replace_word_cache(p1_index_start+idx, p1_index_start+idx);
            refer_or_allocate_tuple2(word_word, &(p1_inchar), &(p1_lastchar));
            curweights->m_mapCharByLastChar.getOrUpdateScore(retval, word_word, action, m_nScoreIndex, amount, round) ;
            refer_or_allocate_tuple3(word_word_tag, &(p1_inchar), &(p1_lastchar), &(p1_tag));
            curweights->m_mapTaggedCharByLastChar.getOrUpdateScore(retval, word_word_tag, action, m_nScoreIndex, amount, round) ;
        }


        if (p2_index_start != -1) {
            refer_or_allocate_tuple3(tag_tag_ulong, &(p1_tag), &(p2_tag), &(p1_nlength));
            curweights->m_mapTag1Tag2Size1.getOrUpdateScore(retval, tag_tag_ulong,  action, m_nScoreIndex , amount , round ) ;
        }


        if ( n0_index != -1) {
            if ( p1_index_start != -1 ) {
                refer_or_allocate_tuple2(word_word, &(p1_lastchar), &(n0_char));
                curweights->m_mapSeparateChars.getOrUpdateScore(retval, word_word ,  action, m_nScoreIndex , amount , round ) ;
                refer_or_allocate_tuple2(word_word, &(p1_word), &(n0_char));
                curweights->m_mapLastWordFirstChar.getOrUpdateScore(retval, word_word,  action, m_nScoreIndex , amount , round ) ;
                refer_or_allocate_tuple2(word_word, &(p1_firstchar), &(n0_char));
                curweights->m_mapFirstCharLastWordByWord.getOrUpdateScore(retval, word_word,  action, m_nScoreIndex , amount , round ) ;

                if ( p1_nlength <= 2 ) {
                    refer_or_allocate_tuple3(word_word_tag, &(p1_word), &(n0_char), &(p1_tag));
                    curweights->m_mapTagByWordAndNextChar.getOrUpdateScore(retval, word_word_tag,  action, m_nScoreIndex , amount , round ) ;
                }

            }
        }
    }


    if( action == action::NO_ACTION || action == action::SHIFT_IN) {
        CWeight* curweights = amount == 0 ? static_cast<CWeight*>(m_weights) : static_cast<CWeight*>(m_delta_pos);
        curweights->m_mapAPPTagByChar.getOrUpdateScore(retval, std::make_pair(n0_char, p1_tag), action, m_nScoreIndex , amount , round ) ;

        refer_or_allocate_tuple3(word_word_tag, &(n0_char), &(n1_char), &(p1_tag));
        curweights->m_mapTaggedCharByFirstChar.getOrUpdateScore(retval, word_word_tag, action, m_nScoreIndex, amount, round ) ;

        refer_or_allocate_tuple2(word_word, &(p1_lastchar), &(n0_char));
        curweights->m_mapConsecutiveChars.getOrUpdateScore(retval, word_word, action, m_nScoreIndex, amount, round ) ;

        refer_or_allocate_tuple3(word_word_tag, &(p1_lastchar), &(n0_char), &(p1_tag));
        curweights->m_mapTaggedConsecutiveChars.getOrUpdateScore(retval, word_word_tag, action, m_nScoreIndex, amount, round ) ;

        refer_or_allocate_tuple2(word_word, &(p1_firstchar), &(n0_char));
        curweights->m_mapFirstCharCurrentChar.getOrUpdateScore(retval, word_word, action, m_nScoreIndex, amount, round ) ;

        refer_or_allocate_tuple3(word_word_tag, &(p1_firstchar), &(n0_char), &(p1_tag));
        curweights->m_mapTaggedFirstCharCurrentChar.getOrUpdateScore(retval, word_word_tag, action, m_nScoreIndex, amount, round ) ;

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

inline SCORE_TYPE CPosDepParser::updateScoreForState(const CDependencyParse &tree,   const CStateItem &from, const CStateItem *outout , const SCORE_TYPE &amount ) {
    static CStateItem item(m_nSentSize);
    item.clear();
    item.setsentsize(m_nSentSize);
    static unsigned action;
    static CPackedScoreType<SCORE_TYPE, action::MAX> empty;
    item = from;
    SCORE_TYPE loss = 0;
    //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
    while ( item != *outout ) {
        action = item.FollowMove( outout );
        if(item.m_nActionSize >= outout->m_nActionSize || action != outout->m_Action[item.m_nActionSize]) {
            std::cout << "error" << std::endl;
        }
        loss = loss + 1;
        //std::cout << item.m_nNextWord << " " << item.m_nLastAction << " " << item.m_Stack.size() << " " << item.m_HeadSet.size() << std::endl;
        getOrUpdateStackScore( &item, empty, action, amount, m_nTrainingRound );
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

void CPosDepParser::updateScoresForStates(const CDependencyParse &tree,   const CStateItem *outout , const CStateItem *correct , SCORE_TYPE amount_add, SCORE_TYPE amount_subtract ) {

    // do not update those steps where they are correct
    static CStateItem item;
    static unsigned action, correct_action;
    item.clear();
    item.setsentsize(m_nSentSize);
    while ( item != *outout ) {
        action = item.FollowMove( outout );
        if(item.m_nActionSize >= outout->m_nActionSize || action != outout->m_Action[item.m_nActionSize]) {
            std::cout << "error" << std::endl;
        }
        correct_action = item.FollowMove( correct );
        if(item.m_nActionSize >= correct->m_nActionSize || correct_action != correct->m_Action[item.m_nActionSize]) {
            std::cout << "error" << std::endl;
        }
        if ( action == correct_action )
            item.Move( action );
        else
            break;
    }

    // for the necessary information for the correct and outout burster
    SCORE_TYPE correct_loss = updateScoreForState(tree, item, correct , amount_add ) ;
    SCORE_TYPE outout_loss = updateScoreForState(tree, item, outout , amount_subtract ) ;
    //if(correct_loss > 0)
    //{
    //   std::cout << "error" << std::endl;
    //}

    //SCORE_TYPE pos_loss = outout->postagloss(tree);
    //SCORE_TYPE dep_loss = outout_loss - correct_loss;

    //if(dep_loss > 1e-20)
    //{
    //SCORE_TYPE normalization = m_delta_dep->squareNorm();
    //SCORE_TYPE weightloss = (dep_loss)/(normalization + 0.5);
    //   SCORE_TYPE weightloss = 1;
    //if(pos_loss < 1e-20)weightloss = weightloss * 3;
    //   static_cast<CWeight*>(m_delta_dep)->scaleCurrent(weightloss, m_nTrainingRound);
    cast_weights->addCurrent(m_delta_dep, m_nTrainingRound);
    //}


    //if(pos_loss > 1e-20 )
    //{
    //SCORE_TYPE normalization = m_delta_pos->squareNorm();
    //SCORE_TYPE weightloss = (pos_loss)/(normalization + 0.5);
    //   SCORE_TYPE weightloss = 1;
    static_cast<CWeight*>(m_delta_pos)->scaleCurrent(4, m_nTrainingRound);
    cast_weights->addCurrent(m_delta_pos, m_nTrainingRound);
    // }

    m_delta_pos->clear();
    m_delta_dep->clear();
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
        //const int &n0_index = item->nextword()==m_lCache.size() ? -1 : item->nextword(); // next
        //const CWord &n0_char = n0_index==-1 ?  g_emptyWord : m_lCache[n0_index];
        //if(PENN_TAG_CLOSED[label] && !cast_weights->m_mapTagDictionary.lookup(n0_char, CTag(label)))
        //{
        //   continue;
        //}
        //}
        //if(cast_weights->m_mapWordFrequency.find(n0_char, 0)  < cast_weights->m_nMaxWordFrequency/5000 + 5
        //	   || cast_weights->m_mapTagDictionary.lookup(n0_char, CTag(label))) {
        scoredaction.action = action::encodeAction(action::SHIFT, label);
        scoredaction.score = item->score + scores[scoredaction.action];
        //+scores[action::SHIFT];
        m_Beam->insertItem(&scoredaction);
        //}
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
 * popword - help function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::popword( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
    static action::CScoredAction scoredaction;
    // update stack score
    //const int &st0_index = item->stackempty() ? -1 : item->stacktop(); // stack top
    //const int &st0_tag_code = st0_index==-1 ?  g_noneTag.code() : item->pos(st0_index);
    //unsigned long tagpairindex = g_noneTag.code()*CTag::COUNT + st0_tag_code;
    //unsigned long index = (g_noneTag.code()*CTag::COUNT + st0_tag_code)*CDependencyLabel::COUNT + CDependencyLabel::ROOT;
    //if( cast_weights->m_mapTagPairDictionary.find(tagpairindex, 0) < cast_weights->m_nMaxWordFrequency/5000 + 20
    //	   || cast_weights->m_mapTagPairLabelDictionary.find(index, 0) > 0)
    //{
    scoredaction.action = action::POP_WORD;
    scoredaction.score = item->score + scores[scoredaction.action];
    m_Beam->insertItem(&scoredaction);
    //}
}


/*---------------------------------------------------------------
 *
 * popword - help function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::idle( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
    static action::CScoredAction scoredaction;
    // update stack score
    //const int &st0_index = item->stackempty() ? -1 : item->stacktop(); // stack top
    //const int &st0_tag_code = st0_index==-1 ?  g_noneTag.code() : item->pos(st0_index);
    //unsigned long tagpairindex = g_noneTag.code()*CTag::COUNT + st0_tag_code;
    //unsigned long index = (g_noneTag.code()*CTag::COUNT + st0_tag_code)*CDependencyLabel::COUNT + CDependencyLabel::ROOT;
    //if( cast_weights->m_mapTagPairDictionary.find(tagpairindex, 0) < cast_weights->m_nMaxWordFrequency/5000 + 20
    //	   || cast_weights->m_mapTagPairLabelDictionary.find(index, 0) > 0)
    //{
    scoredaction.action = action::IDLE;
    scoredaction.score = item->score + scores[scoredaction.action];
    m_Beam->insertItem(&scoredaction);
    //}
}


/*---------------------------------------------------------------
 *
 * shiftin - help function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::shiftin( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
    static action::CScoredAction scoredaction;
    // update stack score
    //const int &st0_index = item->stackempty() ? -1 : item->stacktop(); // stack top
    //const int &st0_tag_code = st0_index==-1 ?  g_noneTag.code() : item->pos(st0_index);
    //unsigned long tagpairindex = g_noneTag.code()*CTag::COUNT + st0_tag_code;
    //unsigned long index = (g_noneTag.code()*CTag::COUNT + st0_tag_code)*CDependencyLabel::COUNT + CDependencyLabel::ROOT;
    //if( cast_weights->m_mapTagPairDictionary.find(tagpairindex, 0) < cast_weights->m_nMaxWordFrequency/5000 + 20
    //	   || cast_weights->m_mapTagPairLabelDictionary.find(index, 0) > 0)
    //{
    scoredaction.action = action::SHIFT_IN;
    scoredaction.score = item->score + scores[scoredaction.action];
    m_Beam->insertItem(&scoredaction);
    //}
}


/*---------------------------------------------------------------
 *
 * arcleftin - help function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::arcleftin( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
    static action::CScoredAction scoredaction;
    // update stack score
    //const int &st0_index = item->stackempty() ? -1 : item->stacktop(); // stack top
    //const int &st0_tag_code = st0_index==-1 ?  g_noneTag.code() : item->pos(st0_index);
    //unsigned long tagpairindex = g_noneTag.code()*CTag::COUNT + st0_tag_code;
    //unsigned long index = (g_noneTag.code()*CTag::COUNT + st0_tag_code)*CDependencyLabel::COUNT + CDependencyLabel::ROOT;
    //if( cast_weights->m_mapTagPairDictionary.find(tagpairindex, 0) < cast_weights->m_nMaxWordFrequency/5000 + 20
    //	   || cast_weights->m_mapTagPairLabelDictionary.find(index, 0) > 0)
    //{
    scoredaction.action = action::ARC_LEFT_IN;
    scoredaction.score = item->score + scores[scoredaction.action];
    m_Beam->insertItem(&scoredaction);
    //}
}


/*---------------------------------------------------------------
 *
 * arcrightin - help function
 *
 *--------------------------------------------------------------*/

inline void CPosDepParser::arcrightin( const CStateItem *item, const CPackedScoreType<SCORE_TYPE, action::MAX> &scores ) {
    static action::CScoredAction scoredaction;
    // update stack score
    //const int &st0_index = item->stackempty() ? -1 : item->stacktop(); // stack top
    //const int &st0_tag_code = st0_index==-1 ?  g_noneTag.code() : item->pos(st0_index);
    //unsigned long tagpairindex = g_noneTag.code()*CTag::COUNT + st0_tag_code;
    //unsigned long index = (g_noneTag.code()*CTag::COUNT + st0_tag_code)*CDependencyLabel::COUNT + CDependencyLabel::ROOT;
    //if( cast_weights->m_mapTagPairDictionary.find(tagpairindex, 0) < cast_weights->m_nMaxWordFrequency/5000 + 20
    //	   || cast_weights->m_mapTagPairLabelDictionary.find(index, 0) > 0)
    //{
    scoredaction.action = action::ARC_RIGHT_IN;
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
    static CStateItem pCandidate ;

    // used only for training
    static bool bCorrect ;  // used in learning for early update
    //static bool bContradictsRules;
    static CStateItem correctState ;
    //static CStateItem correctState_next ;
    static CPackedScoreType<SCORE_TYPE, action::MAX> packed_scores;

    ASSERT(length<MAX_SENTENCE_SIZE, "The size of the sentence is larger than the system configuration.");

    TRACE("Initialising the decoding process...") ;
    // initialise word cache
    //bContradictsRules = false;
    m_lCache.clear();
    // m_lCharCache.clear();
    //m_wordIndexs.clear();
    if(!stackfeats.empty()) {
        assert(stackfeats.size() == length);
    }
    m_stackfeats.clear();
    static std::vector< std::string > currentwordchars;
    for ( index=0; index<length; ++index ) {
        // m_lCache.push_back( sentence[index] );
        if(!stackfeats.empty()) {
            m_stackfeats.push_back(stackfeats[index]);
        }
        //currentwordchars.clear();
        //getCharactersFromUTF8String(sentence[index], &currentwordchars);
        //m_wordIndexs.push_back(m_lCharCache.size());

        //for(int idx = 0; idx < currentwordchars.size(); idx++)
        //{
        //  m_lCharCache.push_back(currentwordchars[idx]);
        // }
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

    //m_wordIndexs.push_back(m_lCharCache.size());
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
    pCandidate.setsentsize(m_nSentSize);
    m_Agenda->pushCandidate(&pCandidate);           // and push it back
    m_Agenda->nextRound();                       // as the generator item
    if (bTrain) {
        correctState.clear();
        correctState.setsentsize(m_nSentSize);
        //correctState_next.clear();
        //correctState_next.setsentsize(m_nSentSize);
    }


#ifdef LABELED
    //   unsigned long label;
    //   m_lCacheLabel.clear();
    //   if (bTrain) {
    //      for (index=0; index<length; ++index) {
    //         m_lCacheLabel.push_back(CDependencyLabel(correct[index].label));
    //std::cout << index << ":\t" << correct[index].label << "...." << m_lCacheLabel[index].str() << std::endl;
    //if (m_weights->rules() && !canAssignLabel(m_lCache, correct[index].head, index, m_lCacheLabel[index])) {
    //   TRACE("Rule contradiction: " << correct[index].label << " on link head " << m_lCache[correct[index].head].tag.code() << " dep " << m_lCache[index].tag.code());
    //   bContradictsRules = true;
    //}
    //     }
    //   }
#endif

    // skip the training example if contradicts
    //if (bTrain && m_weights->rules() && bContradictsRules) {
    //    std::cout << "Skipping training example because it contradicts rules..." <<std::endl;
    //    return;
    // }

    TRACE("Decoding started");
    // loop with the next word to process in the sentence
    for (index=0; index<length*3; ++index) {

        if (bTrain) {
            bCorrect = false ;
            //correctState_next.StandardMoveStep(correct, m_lCacheLabel);
        }

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

            if ( pGenerator->canarc() ) {
                arcright(pGenerator, packed_scores) ;
            }

            if(pGenerator->canarc()) {
                if(pGenerator->subwordend(pGenerator->stacktop()) == pGenerator->nextword()-1) {
                    arcleft(pGenerator, packed_scores) ;
                }
            }

            if ( pGenerator->canarcin() ) {
                arcrightin(pGenerator, packed_scores) ;
            }

            if(pGenerator->canarcin()) {
                if(pGenerator->stacktop() == pGenerator->nextword()-1) {
                    arcleftin(pGenerator, packed_scores) ;
                }
            }

            if ( pGenerator->canpoproot()) {
                poproot(pGenerator, packed_scores);
            }

            if ( pGenerator->canpopword()) {
                popword(pGenerator, packed_scores);
            }

            if ( pGenerator->canshift() ) {
                shift(pGenerator, packed_scores) ;
            }

            if ( pGenerator->canshiftin() ) {
                shiftin(pGenerator, packed_scores) ;
            }

            if(pGenerator->IsTerminated()) {
                idle(pGenerator, packed_scores) ;
            }

            // insert item
            //bool bGoldFind = false;
            for (unsigned i=0; i<m_Beam->size(); ++i) {
                pCandidate = *pGenerator;
                pCandidate.score = m_Beam->item(i)->score;
                pCandidate.Move( m_Beam->item(i)->action );
                //if(pCandidate == correctState_next)
                //{
                //	bGoldFind = true;
                //}
                m_Agenda->pushCandidate(&pCandidate);
            }

            //if(!bGoldFind)
            //{
            //	 std::cout << "error" << std::endl;
            // }

            if (bTrain && *pGenerator == correctState) {
                bCorrect = true ;
            }
            pGenerator = m_Agenda->generatorNext() ;

        }

        CStateItem * bestitem = m_Agenda->bestGenerator();
        if(bestitem->IsTerminated()) {
            break;
        }
        // when we are doing training, we need to consider the standard move and update
        if (bTrain) {
#ifdef EARLY_UPDATE
            if (!bCorrect) {
                TRACE("Error at the "<<correctState.nextword()<<"th word; total is "<<correct.size())

                if(*bestitem == correctState) {
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
#else

                correctState.StandardMoveStep(correct);
#endif
                //m_Agenda->clearCandidates();  //correctState_next
                //m_Agenda->pushCandidate(&correctState);
            }
#ifdef LOCAL_LEARNING
            ++m_nTrainingRound; // each training round is one transition-action
#endif

        }

        m_Agenda->nextRound(); // move round
    }

    if (bTrain) {
        //correctState.StandardFinish(); // pop the root that is left
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
            if (scores)
                scores[i] = pGenerator->score;
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
        if (scores)
            scores[i] = 0; //pGenerator->score;
    }
    m_Sentence.clear();
    for(int idx = 0 ;idx < sentence.size(); idx++) {
        m_Sentence.push_back(sentence[idx]);
    }
    m_nSentSize = m_Sentence.size();
    m_lCache.clear();

    work(false, sentence, retval, empty, stackfeats, nBest, scores ) ;

}

/*---------------------------------------------------------------
 *
 * train - train the models with an example
 *
 *---------------------------------------------------------------*/

void CPosDepParser::train( const CDependencyParse &correct, const CSTackFeatsVec  & stackfeats , int round ) {

    static CStringVector sentence ;
    //static CStringVector rawsentence ;
    static CDependencyParse outout ;
    static CTwoStringVector wordtags;
    static CTuple2<CWord, CWord> word_word;

#ifndef FRAGMENTED_TREE

    assert( IsProjectiveDependencyTree(correct) ) ;
#endif

    UnparseDeSegmentedSentenceCharConll(&correct, &m_Sentence );
    m_nSentSize = m_Sentence.size();
    UnparseSentenceCharConll( &correct, &sentence ) ;
    UnparseSentenceCharConll( &correct, &wordtags ) ;
    m_lCacheLabel.clear();
    for(int i = 0; i < m_nSentSize; i++) {
        m_lCacheLabel.push_back(CDependencyLabel(correct[i].label));
    }

    // Updates that are common for all example
    //for ( unsigned i=0; i<wordtags.size(); ++i ) {

    //const CWord &word = wordtags.at(i).first ;
    //unsigned long tag = CTag( wordtags.at(i).second ).code() ;

    //static CStringVector chars;
    //static unsigned j;
    //static unsigned local_size;
    //chars.clear();
    //getCharactersFromUTF8String(wordtags.at(i).first, &chars);
    //local_size = chars.size();

    //std::cout << "complete word\t" << word.str() << std::endl;
    //cast_weights->m_mapWordFrequency[word]++;
    //if (cast_weights->m_mapWordFrequency[word] > cast_weights->m_nMaxWordFrequency)
    //cast_weights->m_nMaxWordFrequency = cast_weights->m_mapWordFrequency[word];

    //cast_weights->m_mapTagDictionary.add(word, tag);
    //for ( j=0 ; j<local_size; ++j ) {
    //cast_weights->m_mapCharTagDictionary.add(CWord(chars[j]), tag) ;
    //  cast_weights->m_mapCharFrequency[CWord(chars[j])]++;
    //}

    //int head = correct.at(i).head;
    //int label = CDependencyLabel(correct.at(i).label).code();

    //unsigned long headtag = head != -1 ? CTag( wordtags.at(head).second ).code() : g_noneTag.code();

    // label = ivalue % CDependencyLabel::COUNT; tag = (ivalue / CDependencyLabel::COUNT) % CTag::COUNT
    // headtag = (ivalue / CDependencyLabel::COUNT) / CTag::COUNT
    //cast_weights->m_mapTagPairLabelDictionary[(headtag*CTag::COUNT + tag)*CDependencyLabel::COUNT + label]++;
    //cast_weights->m_mapTagPairDictionary[headtag*CTag::COUNT + tag]++;

    //}


    static CStateItem item;
    item.setsentsize(m_nSentSize);

    unsigned action;

    m_lCache.clear();
    item.clear();
    for (int i=0; i<m_nSentSize * 3; ++i) {
#ifdef LABELED
        item.StandardMoveStep(correct, m_lCacheLabel);
#else

        item.StandardMoveStep(correct);
#endif
        /*
        if(item.m_nLastAction == action::ARC_LEFT_IN || item.m_nLastAction == action::ARC_RIGHT_IN)
        {
            int curHead = item.stacktop();
            CWord curHeadChar;
            curHeadChar.load(m_lCache.replace(curHead, curHead, &m_Sentence));
            CWord curSubWord;

            int start_word = item.subwordstart(curHead);
            int end_word = item.subwordend(curHead);

            CTag curTag = CTag(item.m_lPOSs[curHead]);

            curSubWord.load(m_lCache.replace(start_word, end_word, &m_Sentence));
            cast_weights->m_mapSubWordFrequency[curSubWord]++;
            cast_weights->m_mapSubWordTagDictionary.add(curSubWord, curTag);
            if(start_word != end_word)
            {
                word_word.allocate(&curSubWord, &curHeadChar);
                cast_weights->m_mapSubWordHeadWordDictionary[word_word]++;
            }
            if (cast_weights->m_mapSubWordFrequency[curSubWord] > cast_weights->m_nMaxSubWordFrequency)
                cast_weights->m_nMaxSubWordFrequency = cast_weights->m_mapSubWordFrequency[curSubWord];
        }*/
        if(item.IsTerminated()) {
            break;
        }
    }


    int wordcount = 0;
    for(int idx = 0; idx < m_nSentSize; idx++) {
        int start_word = item.subwordstart(idx);
        int end_word = item.subwordend(idx);
        CTag curTag = CTag(item.m_lPOSs[idx]);
        CWord curChar;
        curChar.load(m_lCache.replace(idx, idx, &m_Sentence));

        cast_weights->m_mapCharFrequency[curChar]++;
        cast_weights->m_mapCharTagDictionary.add(curChar, curTag);
        if (cast_weights->m_mapCharFrequency[curChar] > cast_weights->m_nMaxCharFrequency)
            cast_weights->m_nMaxCharFrequency = cast_weights->m_mapCharFrequency[curChar];

        if(item.m_lLabelTypes[idx]) {
            wordcount++;
            CWord curWord;
            curWord.load(m_lCache.replace(start_word, end_word, &m_Sentence));
            cast_weights->m_mapWordFrequency[curWord]++;
            cast_weights->m_mapWordTagDictionary.add(curWord, curTag);
            if (cast_weights->m_mapWordFrequency[curWord] > cast_weights->m_nMaxWordFrequency)
                cast_weights->m_nMaxWordFrequency = cast_weights->m_mapWordFrequency[curWord];
            //cast_weights->m_mapSubWordFrequency[curWord]++;
            //cast_weights->m_mapSubWordTagDictionary.add(curWord, curTag);
            //if(start_word != end_word)
            //{
            //    word_word.allocate(&curWord, &curChar);
            //    cast_weights->m_mapSubWordHeadWordDictionary[word_word]++;
            //}
            //if (cast_weights->m_mapSubWordFrequency[curWord] > cast_weights->m_nMaxSubWordFrequency)
            //    cast_weights->m_nMaxSubWordFrequency = cast_weights->m_mapSubWordFrequency[curWord];
        }
        else
        {

            int curHead = item.m_lHeads[idx];
            CWord curHeadChar;
            curHeadChar.load(m_lCache.replace(curHead, curHead, &m_Sentence));
            CWord curSubWord;
            if(curHead > idx)
            {
                start_word = item.subwordstart(idx);
                end_word = item.subwordend(curHead);
            }
            else
            {
                start_word = item.subwordstart(curHead);
                end_word = item.subwordend(idx);
            }

            curSubWord.load(m_lCache.replace(start_word, end_word, &m_Sentence));
            cast_weights->m_mapSubWordFrequency[curSubWord]++;
            cast_weights->m_mapSubWordTagDictionary.add(curSubWord, curTag);
            if(start_word != end_word)
            {
                word_word.allocate(&curSubWord, &curHeadChar);
                cast_weights->m_mapSubWordHeadWordDictionary[word_word]++;
            }
            if (cast_weights->m_mapSubWordFrequency[curSubWord] > cast_weights->m_nMaxSubWordFrequency)
                cast_weights->m_nMaxSubWordFrequency = cast_weights->m_mapSubWordFrequency[curSubWord];

        }


    }




    // The following code does update for each processing stage
#ifndef LOCAL_LEARNING
    ++m_nTrainingRound;
    ASSERT(m_nTrainingRound == round, "Training round error") ;
#endif

    work( true , m_Sentence , &outout , correct , stackfeats, 1 , 0 ) ;

};

/*---------------------------------------------------------------
 *
 * extract_features - extract features from an example (counts recorded to parser model as weights)
 *
 *---------------------------------------------------------------*/

void CPosDepParser::extract_features(const CDependencyParse &input, const CSTackFeatsVec  & stackfeats) {

    THROW("posdepparser.cpp: extract_features unsupported");
    /*
      CStateItem item(m_nSentSize);
      CStateItem tmp(m_nSentSize);
      unsigned action;
      CPackedScoreType<SCORE_TYPE, action::MAX> empty;

      // word and pos
      m_lCache.clear();
    #ifdef LABELED
      m_lCacheLabel.clear();
    #endif
      m_stackfeats.clear();
     // m_lCharCache.clear();
      static std::vector< std::string > currentwordchars;

      for (int i=0; i<input.size(); ++i) {
         //m_lCache.push_back(CWord(input[i].word));
    #ifdef LABELED
      m_lCacheLabel.push_back(CDependencyLabel(input[i].label));
    #endif

       if(!stackfeats.empty())
       {
     	  m_stackfeats.push_back(stackfeats[i]);
       }
       currentwordchars.clear();
       getCharactersFromUTF8String(input[i].word, &currentwordchars);
       //m_wordIndexs.push_back(m_lCharCache.size());

       //for(int idx = 0; idx < currentwordchars.size(); idx++)
       //{
     	//  m_lCharCache.push_back(currentwordchars[idx]);
       //}
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
      */
}


