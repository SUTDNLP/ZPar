// Copyright (C) University of Oxford 2010
/***************************************************************
 *
 * weight.h - the dependency parser weights 
 *
 * Yue Zhang, 2007.8 - 2008.1
 *
 ***************************************************************/

#ifndef _POSDEPPARSER_WEIGHTS_H
#define _POSDEPPARSER_WEIGHTS_H

#include "posdepparser_weight_base.h"

#define ID(x) x
#define ID_LRB (
#define ID_RRB )
#define ID_COMMA ,

#define iterate_templates(left, right) \
   left(m_mapSTw)right\
   left(m_mapSTt)right\
   left(m_mapSTwt)right\
   left(m_mapN0w)right\
   left(m_mapN0t)right\
   left(m_mapN0wt)right\
   left(m_mapN1w)right\
   left(m_mapN1t)right\
   left(m_mapN1wt)right\
   left(m_mapN2w)right\
   left(m_mapN2t)right\
   left(m_mapN2wt)right\
   left(m_mapSTHw)right\
   left(m_mapSTHt)right\
   left(m_mapSTi)right\
   left(m_mapSTHHw)right\
   left(m_mapSTHHt)right\
   left(m_mapSTHi)right\
   left(m_mapSTLDw)right\
   left(m_mapSTLDt)right\
   left(m_mapSTLDi)right\
   left(m_mapSTRDw)right\
   left(m_mapSTRDt)right\
   left(m_mapSTRDi)right\
   left(m_mapN0LDw)right\
   left(m_mapN0LDt)right\
   left(m_mapN0LDi)right\
   left(m_mapSTL2Dw)right\
   left(m_mapSTL2Dt)right\
   left(m_mapSTL2Di)right\
   left(m_mapSTR2Dw)right\
   left(m_mapSTR2Dt)right\
   left(m_mapSTR2Di)right\
   left(m_mapN0L2Dw)right\
   left(m_mapN0L2Dt)right\
   left(m_mapN0L2Di)right\
   left(m_mapHTw)right\
   left(m_mapHTt)right\
   left(m_mapHTwt)right\
\
   left(m_mapSTwtN0wt)right\
   left(m_mapSTwtN0w)right\
   left(m_mapSTwN0wt)right\
   left(m_mapSTtN0wt)right\
   left(m_mapSTwtN0t)right\
   left(m_mapSTwN0w)right\
   left(m_mapSTtN0t)right\
\
   left(m_mapN0tN1t)right\
   left(m_mapN0tN1tN2t)right\
   left(m_mapSTtN0tN1t)right\
   left(m_mapSTtN0tN0LDt)right\
   left(m_mapN0tN0LDtN0L2Dt)right\
   left(m_mapSTHtSTtN0t)right\
   left(m_mapHTtHT2tN0t)right\
   left(m_mapSTHHtSTHtSTt)right\
   left(m_mapSTtSTLDtN0t)right\
   left(m_mapSTtSTLDtSTL2Dt)right\
   left(m_mapSTtSTRDtN0t)right\
   left(m_mapSTtSTRDtSTR2Dt)right\
\
   left(m_mapSTwd)right\
   left(m_mapSTtd)right\
   left(m_mapN0wd)right\
   left(m_mapN0td)right\
   left(m_mapSTwN0wd)right\
   left(m_mapSTtN0td)right\
\
   left(m_mapSTwra)right\
   left(m_mapSTtra)right\
   left(m_mapSTwla)right\
   left(m_mapSTtla)right\
   left(m_mapN0wla)right\
   left(m_mapN0tla)right\
\
   left(m_mapSTwrp)right\
   left(m_mapSTtrp)right\
   left(m_mapSTwlp)right\
   left(m_mapSTtlp)right\
   left(m_mapN0wlp)right\
   left(m_mapN0tlp)right\
\
	left(m_mapCurrentWord)right\
	left(m_mapLastTag)right\
	left(m_mapLastTwoTags)right\
	left(m_mapLastWord)right\
	left(m_mapLastTagCurrentWord)right\
	left(m_mapCurentWordPrevChar)right\
	left(m_mapLastWordFirstChar)right\
	left(m_mapNextWord)right\
	left(m_mapCurentWordNextChar)right\
	left(m_mapNextWordLastChar)right\
	left(m_mapOneCharWordTriChar)right\
	left(m_mapFirstChar)right\
	left(m_mapLastChar)right\
	left(m_mapFirstCharCat)right\
	left(m_mapLastCharCat)right\
	left(m_mapCharInWord)right\
	left(m_mapCharInWordByFirstChar)right\
	left(m_mapRepeatedChar)right\
	left(m_mapRepeated2Char)right\
	left(m_mapCharInWordByLastChar)right\
	left(m_mapNormalizedLength)right\
	left(m_mapPOSSTw)right\
	left(m_mapPOSSTt)right\
	left(m_mapPOSSTwt)right\
	left(m_mapPOSSTwCurWord)right\
	left(m_mapPOSSTfcCurWord)right\
	left(m_mapPOSSTlcCurWord)right\
	left(m_mapPOSSTtSTLDt)right\
	left(m_mapPOSSTwtSTLDt)right\
	left(m_mapPOSSTtSTRDt)right\
	left(m_mapPOSSTwtSTRDt)right\
	left(m_mapPOSN0w)right\
	left(m_mapPOSN0t)right\
	left(m_mapPOSN0wt)right\
	left(m_mapPOSN0wCurWord)right\
	left(m_mapPOSN0fcCurWord)right\
	left(m_mapPOSN0lcCurWord)right\
	left(m_mapPOSN0tN0LDt)right\
	left(m_mapPOSN0wtN0LDt)right\
	left(m_mapPrefixChar1)right\
	left(m_mapPrefixChar2)right\
	left(m_mapPrefixChar3)right\
	left(m_mapSuffixChar1)right\
	left(m_mapSuffixChar2)right\
	left(m_mapSuffixChar3)right\
	left(m_mapWordLabelInDict)right\
	left(m_mapFirstCharLabelInDict)right\
	left(m_mapLastCharLabelInDict)right




#define iterate_double_templates(left, middle, right)\
	left  m_mapSTw  middle  m_mapSTw  right\
	left  m_mapSTt  middle  m_mapSTt  right\
	left  m_mapSTwt  middle  m_mapSTwt  right\
	left  m_mapN0w  middle  m_mapN0w  right\
	left  m_mapN0t  middle  m_mapN0t  right\
	left  m_mapN0wt  middle  m_mapN0wt  right\
	left  m_mapN1w  middle  m_mapN1w  right\
	left  m_mapN1t  middle  m_mapN1t  right\
	left  m_mapN1wt  middle  m_mapN1wt  right\
	left  m_mapN2w  middle  m_mapN2w  right\
	left  m_mapN2t  middle  m_mapN2t  right\
	left  m_mapN2wt  middle  m_mapN2wt  right\
	left  m_mapSTHw  middle  m_mapSTHw  right\
	left  m_mapSTHt  middle  m_mapSTHt  right\
	left  m_mapSTi  middle  m_mapSTi  right\
	left  m_mapSTHHw  middle  m_mapSTHHw  right\
	left  m_mapSTHHt  middle  m_mapSTHHt  right\
	left  m_mapSTHi  middle  m_mapSTHi  right\
	left  m_mapSTLDw  middle  m_mapSTLDw  right\
	left  m_mapSTLDt  middle  m_mapSTLDt  right\
	left  m_mapSTLDi  middle  m_mapSTLDi  right\
	left  m_mapSTRDw  middle  m_mapSTRDw  right\
	left  m_mapSTRDt  middle  m_mapSTRDt  right\
	left  m_mapSTRDi  middle  m_mapSTRDi  right\
	left  m_mapN0LDw  middle  m_mapN0LDw  right\
	left  m_mapN0LDt  middle  m_mapN0LDt  right\
	left  m_mapN0LDi  middle  m_mapN0LDi  right\
	left  m_mapSTL2Dw  middle  m_mapSTL2Dw  right\
	left  m_mapSTL2Dt  middle  m_mapSTL2Dt  right\
	left  m_mapSTL2Di  middle  m_mapSTL2Di  right\
	left  m_mapSTR2Dw  middle  m_mapSTR2Dw  right\
	left  m_mapSTR2Dt  middle  m_mapSTR2Dt  right\
	left  m_mapSTR2Di  middle  m_mapSTR2Di  right\
	left  m_mapN0L2Dw  middle  m_mapN0L2Dw  right\
	left  m_mapN0L2Dt  middle  m_mapN0L2Dt  right\
	left  m_mapN0L2Di  middle  m_mapN0L2Di  right\
	left  m_mapHTw  middle  m_mapHTw  right\
	left  m_mapHTt  middle  m_mapHTt  right\
	left  m_mapHTwt  middle  m_mapHTwt  right\
	left  m_mapSTwtN0wt  middle  m_mapSTwtN0wt  right\
	left  m_mapSTwtN0w  middle  m_mapSTwtN0w  right\
	left  m_mapSTwN0wt  middle  m_mapSTwN0wt  right\
	left  m_mapSTtN0wt  middle  m_mapSTtN0wt  right\
	left  m_mapSTwtN0t  middle  m_mapSTwtN0t  right\
	left  m_mapSTwN0w  middle  m_mapSTwN0w  right\
	left  m_mapSTtN0t  middle  m_mapSTtN0t  right\
	left  m_mapN0tN1t  middle  m_mapN0tN1t  right\
	left  m_mapN0tN1tN2t  middle  m_mapN0tN1tN2t  right\
	left  m_mapSTtN0tN1t  middle  m_mapSTtN0tN1t  right\
	left  m_mapSTtN0tN0LDt  middle  m_mapSTtN0tN0LDt  right\
	left  m_mapN0tN0LDtN0L2Dt  middle  m_mapN0tN0LDtN0L2Dt  right\
	left  m_mapSTHtSTtN0t  middle  m_mapSTHtSTtN0t  right\
	left  m_mapHTtHT2tN0t  middle  m_mapHTtHT2tN0t  right\
	left  m_mapSTHHtSTHtSTt  middle  m_mapSTHHtSTHtSTt  right\
	left  m_mapSTtSTLDtN0t  middle  m_mapSTtSTLDtN0t  right\
	left  m_mapSTtSTLDtSTL2Dt  middle  m_mapSTtSTLDtSTL2Dt  right\
	left  m_mapSTtSTRDtN0t  middle  m_mapSTtSTRDtN0t  right\
	left  m_mapSTtSTRDtSTR2Dt  middle  m_mapSTtSTRDtSTR2Dt  right\
	left  m_mapSTwd  middle  m_mapSTwd  right\
	left  m_mapSTtd  middle  m_mapSTtd  right\
	left  m_mapN0wd  middle  m_mapN0wd  right\
	left  m_mapN0td  middle  m_mapN0td  right\
	left  m_mapSTwN0wd  middle  m_mapSTwN0wd  right\
	left  m_mapSTtN0td  middle  m_mapSTtN0td  right\
	left  m_mapSTwra  middle  m_mapSTwra  right\
	left  m_mapSTtra  middle  m_mapSTtra  right\
	left  m_mapSTwla  middle  m_mapSTwla  right\
	left  m_mapSTtla  middle  m_mapSTtla  right\
	left  m_mapN0wla  middle  m_mapN0wla  right\
	left  m_mapN0tla  middle  m_mapN0tla  right\
	left  m_mapSTwrp  middle  m_mapSTwrp  right\
	left  m_mapSTtrp  middle  m_mapSTtrp  right\
	left  m_mapSTwlp  middle  m_mapSTwlp  right\
	left  m_mapSTtlp  middle  m_mapSTtlp  right\
	left  m_mapN0wlp  middle  m_mapN0wlp  right\
	left  m_mapN0tlp  middle  m_mapN0tlp  right\
\
	left  m_mapCurrentWord  middle  m_mapCurrentWord  right\
	left  m_mapLastTag  middle  m_mapLastTag  right\
	left  m_mapLastTwoTags  middle  m_mapLastTwoTags  right\
	left  m_mapLastWord  middle  m_mapLastWord  right\
	left  m_mapLastTagCurrentWord  middle  m_mapLastTagCurrentWord  right\
	left  m_mapCurentWordPrevChar  middle  m_mapCurentWordPrevChar  right\
	left  m_mapLastWordFirstChar  middle  m_mapLastWordFirstChar  right\
	left  m_mapNextWord  middle  m_mapNextWord  right\
	left  m_mapCurentWordNextChar  middle  m_mapCurentWordNextChar  right\
	left  m_mapNextWordLastChar  middle  m_mapNextWordLastChar  right\
	left  m_mapOneCharWordTriChar  middle  m_mapOneCharWordTriChar  right\
	left  m_mapFirstChar  middle  m_mapFirstChar  right\
	left  m_mapLastChar  middle  m_mapLastChar  right\
	left  m_mapFirstCharCat  middle  m_mapFirstCharCat  right\
	left  m_mapLastCharCat  middle  m_mapLastCharCat  right\
	left  m_mapCharInWord  middle  m_mapCharInWord  right\
	left  m_mapCharInWordByFirstChar  middle  m_mapCharInWordByFirstChar  right\
	left  m_mapRepeatedChar  middle  m_mapRepeatedChar  right\
	left  m_mapRepeated2Char  middle  m_mapRepeated2Char  right\
	left  m_mapCharInWordByLastChar  middle  m_mapCharInWordByLastChar  right\
	left  m_mapNormalizedLength  middle  m_mapNormalizedLength  right\
	left  m_mapPOSSTw  middle  m_mapPOSSTw  right\
	left  m_mapPOSSTt  middle  m_mapPOSSTt  right\
	left  m_mapPOSSTwt  middle  m_mapPOSSTwt  right\
	left  m_mapPOSSTwCurWord  middle  m_mapPOSSTwCurWord  right\
	left  m_mapPOSSTfcCurWord  middle  m_mapPOSSTfcCurWord  right\
	left  m_mapPOSSTlcCurWord  middle  m_mapPOSSTlcCurWord  right\
	left  m_mapPOSSTtSTLDt  middle  m_mapPOSSTtSTLDt  right\
	left  m_mapPOSSTwtSTLDt  middle  m_mapPOSSTwtSTLDt  right\
	left  m_mapPOSSTtSTRDt  middle  m_mapPOSSTtSTRDt  right\
	left  m_mapPOSSTwtSTRDt  middle  m_mapPOSSTwtSTRDt  right\
	left  m_mapPOSN0w  middle  m_mapPOSN0w  right\
	left  m_mapPOSN0t  middle  m_mapPOSN0t  right\
	left  m_mapPOSN0wt  middle  m_mapPOSN0wt  right\
	left  m_mapPOSN0wCurWord  middle  m_mapPOSN0wCurWord  right\
	left  m_mapPOSN0fcCurWord  middle  m_mapPOSN0fcCurWord  right\
	left  m_mapPOSN0lcCurWord  middle  m_mapPOSN0lcCurWord  right\
	left  m_mapPOSN0tN0LDt  middle  m_mapPOSN0tN0LDt  right\
	left  m_mapPOSN0wtN0LDt  middle  m_mapPOSN0wtN0LDt  right\
	left  m_mapPrefixChar1  middle  m_mapPrefixChar1  right\
	left  m_mapPrefixChar2  middle  m_mapPrefixChar2  right\
	left  m_mapPrefixChar3  middle  m_mapPrefixChar3  right\
	left  m_mapSuffixChar1  middle  m_mapSuffixChar1  right\
	left  m_mapSuffixChar2  middle  m_mapSuffixChar2  right\
	left  m_mapSuffixChar3  middle  m_mapSuffixChar3  right\
	left  m_mapWordLabelInDict  middle  m_mapWordLabelInDict  right\
	left  m_mapFirstCharLabelInDict  middle  m_mapFirstCharLabelInDict  right\
	left  m_mapLastCharLabelInDict  middle  m_mapLastCharLabelInDict  right




namespace TARGET_LANGUAGE {

namespace posdepparser {

const static unsigned DEP_TABLE_SIZE = (1<<17);//1000121;

//
// TYPE DEFINITIONS
//
typedef CPackedScoreMap<CWord, SCORE_TYPE, action::MAX> CWordMap;
typedef CPackedScoreMap<CTag, SCORE_TYPE, action::MAX> CTagMap;
typedef CPackedScoreMap<int, SCORE_TYPE, action::MAX> CIntMap;
typedef CPackedScoreMap<CTagSet<CTag, 2>,  SCORE_TYPE, action::MAX> CTagSet2Map;
typedef CPackedScoreMap<CTagSet<CTag, 3>, SCORE_TYPE, action::MAX> CTagSet3Map;
typedef CPackedScoreMap<CTagSet<CTag, 4>, SCORE_TYPE, action::MAX> CTagSet4Map;
typedef CPackedScoreMap<CTuple3<CWord, CTag, CTag>, SCORE_TYPE, action::MAX> CWordTagTagMap;
typedef CPackedScoreMap<CTuple3<CWord, CWord, CTag>, SCORE_TYPE, action::MAX> CWordWordTagMap;
typedef CPackedScoreMap<CTaggedWord<CTag, TAG_SEPARATOR>, SCORE_TYPE, action::MAX> CTaggedWordMap;
typedef CPackedScoreMap<CTwoWords, SCORE_TYPE, action::MAX> CTwoWordsMap;
typedef CPackedScoreMap<CTwoTaggedWords, SCORE_TYPE, action::MAX> CTwoTaggedWordsMap;
typedef CPackedScoreMap<CTuple2<CWord, int>, SCORE_TYPE, action::MAX> CWordIntMap;
typedef CPackedScoreMap<CTuple2<CTag, int>, SCORE_TYPE, action::MAX> CTagIntMap;
typedef CPackedScoreMap<CTuple3<CTag, CTag, int>, SCORE_TYPE, action::MAX> CTagTagIntMap;
typedef CPackedScoreMap<CTuple3<CWord, CWord, int>, SCORE_TYPE, action::MAX> CWordWordIntMap;
typedef CPackedScoreMap<CTuple2< CWord, CSetOfTags<CDependencyLabel> >, SCORE_TYPE, action::MAX> CWordSetOfLabelsMap;
typedef CPackedScoreMap<CTuple2< CTag, CSetOfTags<CDependencyLabel> >, SCORE_TYPE, action::MAX> CTagSetOfLabelsMap;

typedef CPackedScoreMap<CTuple2<CTag, CTag>, SCORE_TYPE, action::MAX> CTagTagMap;
typedef CPackedScoreMap<CTuple2<CWord, CWord>, SCORE_TYPE, action::MAX> CWordWordMap;
typedef CPackedScoreMap<CTuple3<CWord, CWord, CWord>, SCORE_TYPE, action::MAX> CWordWordWordMap;
typedef CPackedScoreMap<unsigned long long, SCORE_TYPE, action::MAX> CLongIntMap;


typedef CHashMap<CWord, unsigned long> CWordToIntMap;
typedef CHashMap<unsigned long, unsigned long> CIntToIntMap;

/*===============================================================
 *
 * CWeight - the definition of weights, in feature
 *
 *==============================================================*/

class CWeight : public CWeightBase {

public:

   CWordMap m_mapSTw;
   CTagMap m_mapSTt;
   CTaggedWordMap m_mapSTwt;

   CWordMap m_mapN0w;
   CTagMap m_mapN0t;
   CTaggedWordMap m_mapN0wt;

   CWordMap m_mapN1w;
   CTagMap m_mapN1t;
   CTaggedWordMap m_mapN1wt;

   CWordMap m_mapN2w;
   CTagMap m_mapN2t;
   CTaggedWordMap m_mapN2wt;

   CWordMap m_mapSTHw;
   CTagMap m_mapSTHt;
   CIntMap m_mapSTi;

   CWordMap m_mapSTHHw;
   CTagMap m_mapSTHHt;
   CIntMap m_mapSTHi;

   CWordMap m_mapSTLDw;
   CTagMap m_mapSTLDt;
   CIntMap m_mapSTLDi;

   CWordMap m_mapSTRDw;
   CTagMap m_mapSTRDt;
   CIntMap m_mapSTRDi;

   CWordMap m_mapN0LDw;
   CTagMap m_mapN0LDt;
   CIntMap m_mapN0LDi;

   CWordMap m_mapSTL2Dw;
   CTagMap m_mapSTL2Dt;
   CIntMap m_mapSTL2Di;

   CWordMap m_mapSTR2Dw;
   CTagMap m_mapSTR2Dt;
   CIntMap m_mapSTR2Di;

   CWordMap m_mapN0L2Dw;
   CTagMap m_mapN0L2Dt;
   CIntMap m_mapN0L2Di;

   CWordMap m_mapHTw;
   CTagMap m_mapHTt;
   CTaggedWordMap m_mapHTwt;

   CTwoTaggedWordsMap m_mapSTwtN0wt;
   CWordWordTagMap m_mapSTwtN0w;
   CWordWordTagMap m_mapSTwN0wt;
   CWordTagTagMap m_mapSTtN0wt;
   CWordTagTagMap m_mapSTwtN0t;
   CTwoWordsMap m_mapSTwN0w;
   CTagSet2Map m_mapSTtN0t;

   CTagSet2Map m_mapN0tN1t;
   CTagSet3Map m_mapN0tN1tN2t;
   CTagSet3Map m_mapSTtN0tN1t;
   CTagSet3Map m_mapSTtN0tN0LDt;
   CTagSet3Map m_mapN0tN0LDtN0L2Dt;
   CTagSet3Map m_mapSTHtSTtN0t;
   CTagSet3Map m_mapHTtHT2tN0t;
   CTagSet3Map m_mapSTHHtSTHtSTt;
   CTagSet3Map m_mapSTtSTLDtN0t;
   CTagSet3Map m_mapSTtSTLDtSTL2Dt;
   CTagSet3Map m_mapSTtSTRDtN0t;
   CTagSet3Map m_mapSTtSTRDtSTR2Dt;

   CWordIntMap m_mapSTwd;
   CTagIntMap m_mapSTtd;
   CWordIntMap m_mapN0wd;
   CTagIntMap m_mapN0td;
   CWordWordIntMap m_mapSTwN0wd;
   CTagTagIntMap m_mapSTtN0td;

   CWordIntMap m_mapSTwra;
   CTagIntMap m_mapSTtra;
   CWordIntMap m_mapSTwla;
   CTagIntMap m_mapSTtla;
   CWordIntMap m_mapN0wla;
   CTagIntMap m_mapN0tla;

   CWordSetOfLabelsMap m_mapSTwrp;
   CTagSetOfLabelsMap m_mapSTtrp;
   CWordSetOfLabelsMap m_mapSTwlp;
   CTagSetOfLabelsMap m_mapSTtlp;
   CWordSetOfLabelsMap m_mapN0wlp;
   CTagSetOfLabelsMap m_mapN0tlp;



   CWordMap	m_mapCurrentWord;
   CTagMap	m_mapLastTag;
   CTagTagMap	m_mapLastTwoTags;
   CWordMap	m_mapLastWord;
   CTaggedWordMap	m_mapLastTagCurrentWord;
   CWordWordMap	m_mapCurentWordPrevChar;
   CWordWordMap	m_mapLastWordFirstChar;
   CWordMap	m_mapNextWord;
   CWordWordMap	m_mapCurentWordNextChar;
   CWordWordMap	m_mapNextWordLastChar;
   CWordWordWordMap	m_mapOneCharWordTriChar;
   CWordMap	m_mapFirstChar;
   CWordMap	m_mapLastChar;
   CLongIntMap	m_mapFirstCharCat;
   CLongIntMap	m_mapLastCharCat;
   CWordMap	m_mapCharInWord;
   CWordWordMap	m_mapCharInWordByFirstChar;
   CWordMap	m_mapRepeatedChar;
   CWordMap	m_mapRepeated2Char;
   CWordWordMap	m_mapCharInWordByLastChar;
   CLongIntMap	m_mapNormalizedLength;
   CWordMap	m_mapPOSSTw;
   CTagMap	m_mapPOSSTt;
   CTaggedWordMap	m_mapPOSSTwt;
   CWordWordMap	m_mapPOSSTwCurWord;
   CWordWordMap	m_mapPOSSTfcCurWord;
   CWordWordMap	m_mapPOSSTlcCurWord;
   CTagTagMap	m_mapPOSSTtSTLDt;
   CWordTagTagMap	m_mapPOSSTwtSTLDt;
   CTagTagMap	m_mapPOSSTtSTRDt;
   CWordTagTagMap	m_mapPOSSTwtSTRDt;
   CWordMap	m_mapPOSN0w;
   CTagMap	m_mapPOSN0t;
   CTaggedWordMap	m_mapPOSN0wt;
   CWordWordMap	m_mapPOSN0wCurWord;
   CWordWordMap	m_mapPOSN0fcCurWord;
   CWordWordMap	m_mapPOSN0lcCurWord;
   CTagTagMap	m_mapPOSN0tN0LDt;
   CWordTagTagMap	m_mapPOSN0wtN0LDt;
   CWordMap	m_mapPrefixChar1;
   CWordWordMap	m_mapPrefixChar2;
   CWordWordWordMap	m_mapPrefixChar3;
   CWordMap	m_mapSuffixChar1;
   CWordWordMap	m_mapSuffixChar2;
   CWordWordWordMap	m_mapSuffixChar3;
   CLongIntMap	m_mapWordLabelInDict;
   CLongIntMap	m_mapFirstCharLabelInDict;
   CLongIntMap	m_mapLastCharLabelInDict;








   unsigned long m_nMaxWordFrequency;
   CWordToIntMap m_mapWordFrequency;
   CWordToIntMap m_mapCharFrequency;

   CTagDict<CWord, CTag> m_mapTagDictionary;
   CTagDict<CWord, CTag> m_mapCharTagDictionary;
   CIntToIntMap m_mapTagPairLabelDictionary;
   CIntToIntMap m_mapTagPairDictionary;

public:

   CWeight(const std::string &sPath, bool bTrain, int dep_table_size) : CWeightBase(sPath, bTrain) ,

											   m_nMaxWordFrequency(0) ,
											   m_mapWordFrequency(65537),
											   m_mapCharFrequency(65537),
											   m_mapTagDictionary(CTag::COUNT),
											   m_mapCharTagDictionary(CTag::COUNT),
											   m_mapTagPairLabelDictionary(CTag::COUNT*CTag::COUNT*CDependencyLabel::COUNT+1),
											   m_mapTagPairDictionary(CTag::COUNT*CTag::COUNT+1),

                                               m_mapSTw("StackWord", dep_table_size),
                                               m_mapSTt("StackTag", dep_table_size),
                                               m_mapSTwt("StackWordTag", dep_table_size),

                                               m_mapN0w("NextWord", dep_table_size),
                                               m_mapN0t("NextTag", dep_table_size),
                                               m_mapN0wt("NextWordTag", dep_table_size),

                                               m_mapN1w("Next+1Word", dep_table_size),
                                               m_mapN1t("Next+1Tag", dep_table_size),
                                               m_mapN1wt("Next+1WordTag", dep_table_size),

                                               m_mapN2w("Next+2Word", dep_table_size),
                                               m_mapN2t("Next+2Tag", dep_table_size),
                                               m_mapN2wt("Next+2WordTag", dep_table_size),

                                               m_mapSTHw("StackHeadWord", dep_table_size),
                                               m_mapSTHt("StackHeadTag", dep_table_size),
                                               m_mapSTi("StackLabel", dep_table_size),

                                               m_mapSTHHw("StackHeadHeadWord", dep_table_size),
                                               m_mapSTHHt("StackHeadHeadTag", dep_table_size),
                                               m_mapSTHi("StackLabel", dep_table_size),

                                               m_mapSTLDw("StackLDWord", dep_table_size),
                                               m_mapSTLDt("StackLDTag", dep_table_size),
                                               m_mapSTLDi("StackLDLabel", dep_table_size),

                                               m_mapSTRDw("StackRDWord", dep_table_size),
                                               m_mapSTRDt("StackRDTag", dep_table_size),
                                               m_mapSTRDi("StackRDLabel", dep_table_size),

                                               m_mapN0LDw("NextLDWord", dep_table_size),
                                               m_mapN0LDt("NextLDTag", dep_table_size),
                                               m_mapN0LDi("NextLDLabel", dep_table_size),

                                               m_mapSTL2Dw("StackL2DWord", dep_table_size),
                                               m_mapSTL2Dt("StackL2DTag", dep_table_size),
                                               m_mapSTL2Di("StackL2DLabel", dep_table_size),

                                               m_mapSTR2Dw("StackR2DWord", dep_table_size),
                                               m_mapSTR2Dt("StackR2DTag", dep_table_size),
                                               m_mapSTR2Di("StackR2DLabel", dep_table_size),

                                               m_mapN0L2Dw("NextL2DWord", dep_table_size),
                                               m_mapN0L2Dt("NextL2DTag", dep_table_size),
                                               m_mapN0L2Di("NextL2DLabel", dep_table_size),

                                               m_mapHTw("HeadStackWord", dep_table_size),
                                               m_mapHTt("HeadStackTag", dep_table_size),
                                               m_mapHTwt("HeadStackWordTag", dep_table_size),

                                               m_mapSTwtN0wt("StackWordTagNextWordTag", dep_table_size),
                                               m_mapSTwtN0w("StackWordTagNextWord", dep_table_size),
                                               m_mapSTwN0wt("StackWordNextWordTag", dep_table_size),
                                               m_mapSTtN0wt("StackTagNextWordTag", dep_table_size),
                                               m_mapSTwtN0t("StackWordTagNextTag", dep_table_size),
                                               m_mapSTwN0w("StackWordNextWord", dep_table_size),
                                               m_mapSTtN0t("StackTagNextTag", dep_table_size),

                                               m_mapN0tN1t("NextTagNext+1Tag", dep_table_size),
                                               m_mapN0tN1tN2t("NextTagTrigram", dep_table_size),
                                               m_mapSTtN0tN1t("StackTagNextTagNext+1Tag", dep_table_size),
                                               m_mapSTtN0tN0LDt("StackTagNextTagNextLDTag", dep_table_size),
                                               m_mapN0tN0LDtN0L2Dt("StackTagNextTagNextLDTagNextTagNextL2DTag", dep_table_size),
                                               m_mapSTHtSTtN0t("StackHeadTagStackTagNextTag", dep_table_size),
                                               m_mapHTtHT2tN0t("HeadStackTagHeadStack2TagNextTag", dep_table_size),
                                               m_mapSTHHtSTHtSTt("StackHeadHeadTagStackHeadTagStackTag", dep_table_size),
                                               m_mapSTtSTLDtN0t("StackTagStackLDTagNextTag", dep_table_size),
                                               m_mapSTtSTLDtSTL2Dt("StackTagStackLDTagStackL2DTag", dep_table_size),
                                               m_mapSTtSTRDtN0t("StackTagStackRDTagNextTag", dep_table_size),
                                               m_mapSTtSTRDtSTR2Dt("StackTagStackRDTagStackR2DTag", dep_table_size),

                                               m_mapSTwd("StackWordDist", dep_table_size),
                                               m_mapSTtd("StackTagDist", dep_table_size),
                                               m_mapN0wd("NextWordDist", dep_table_size),
                                               m_mapN0td("NextTagDist", dep_table_size),
                                               m_mapSTwN0wd("StackWordNextWordDist", dep_table_size),
                                               m_mapSTtN0td("StackTagNextTagDist", dep_table_size),

                                               m_mapSTwra("StackWordRightArity", dep_table_size),
                                               m_mapSTtra("StackTagRightArity", dep_table_size),
                                               m_mapSTwla("StackWordLeftArity", dep_table_size),
                                               m_mapSTtla("StackTagLeftArity", dep_table_size),
                                               m_mapN0wla("NextWordRightArity", dep_table_size),
                                               m_mapN0tla("NextTagRightArity", dep_table_size),

                                               m_mapSTwrp("StackWordRightSetoftags", dep_table_size),
                                               m_mapSTtrp("StackTagRightSetoftags", dep_table_size),
                                               m_mapSTwlp("StackWordLeftSetoftags", dep_table_size),
                                               m_mapSTtlp("StackTagLeftSetoftags", dep_table_size),
                                               m_mapN0wlp("Next0WordLeftSetoftags", dep_table_size),
                                               m_mapN0tlp("Next0TagLeftSetoftags", dep_table_size),
                                               m_mapCurrentWord("CurrentWord", dep_table_size),
                                               m_mapLastTag("LastTag", dep_table_size),
                                               m_mapLastTwoTags("LastTwoTags", dep_table_size),
                                               m_mapLastWord("LastWord", dep_table_size),
                                               m_mapLastTagCurrentWord("LastTagCurrentWord", dep_table_size),
                                               m_mapCurentWordPrevChar("CurentWordPrevChar", dep_table_size),
                                               m_mapLastWordFirstChar("LastWordFirstChar", dep_table_size),
                                               m_mapNextWord("NextWord", dep_table_size),
                                               m_mapCurentWordNextChar("CurentWordNextChar", dep_table_size),
                                               m_mapNextWordLastChar("NextWordLastChar", dep_table_size),
                                               m_mapOneCharWordTriChar("OneCharWordTriChar", dep_table_size),
                                               m_mapFirstChar("FirstChar", dep_table_size),
                                               m_mapLastChar("LastChar", dep_table_size),
                                               m_mapFirstCharCat("FirstCharCat", dep_table_size),
                                               m_mapLastCharCat("LastCharCat", dep_table_size),
                                               m_mapCharInWord("CharInWord", dep_table_size),
                                               m_mapCharInWordByFirstChar("CharInWordByFirstChar", dep_table_size),
                                               m_mapRepeatedChar("RepeatedChar", dep_table_size),
                                               m_mapRepeated2Char("Repeated2Char", dep_table_size),
                                               m_mapCharInWordByLastChar("CharInWordByLastChar", dep_table_size),
                                               m_mapNormalizedLength("NormalizedLength", dep_table_size),
                                               m_mapPOSSTw("POSSTw", dep_table_size),
                                               m_mapPOSSTt("POSSTt", dep_table_size),
                                               m_mapPOSSTwt("POSSTwt", dep_table_size),
                                               m_mapPOSSTwCurWord("POSSTwCurWord", dep_table_size),
                                               m_mapPOSSTfcCurWord("POSSTfcCurWord", dep_table_size),
                                               m_mapPOSSTlcCurWord("POSSTlcCurWord", dep_table_size),
                                               m_mapPOSSTtSTLDt("POSSTtSTLDt", dep_table_size),
                                               m_mapPOSSTwtSTLDt("POSSTwtSTLDt", dep_table_size),
                                               m_mapPOSSTtSTRDt("POSSTtSTRDt", dep_table_size),
                                               m_mapPOSSTwtSTRDt("POSSTwtSTRDt", dep_table_size),
                                               m_mapPOSN0w("POSN0w", dep_table_size),
                                               m_mapPOSN0t("POSN0t", dep_table_size),
                                               m_mapPOSN0wt("POSN0wt", dep_table_size),
                                               m_mapPOSN0wCurWord("POSN0wCurWord", dep_table_size),
                                               m_mapPOSN0fcCurWord("POSN0fcCurWord", dep_table_size),
                                               m_mapPOSN0lcCurWord("POSN0lcCurWord", dep_table_size),
                                               m_mapPOSN0tN0LDt("POSN0tN0LDt", dep_table_size),
                                               m_mapPOSN0wtN0LDt("POSN0wtN0LDt", dep_table_size),
                                               m_mapPrefixChar1("PrefixChar1", dep_table_size),
                                               m_mapPrefixChar2("PrefixChar2", dep_table_size),
                                               m_mapPrefixChar3("PrefixChar3", dep_table_size),
                                               m_mapSuffixChar1("SuffixChar1", dep_table_size),
                                               m_mapSuffixChar2("SuffixChar2", dep_table_size),
                                               m_mapSuffixChar3("SuffixChar3", dep_table_size),
                                               m_mapWordLabelInDict("WordLabelInDict", dep_table_size),
                                               m_mapFirstCharLabelInDict("FirstCharLabelInDict", dep_table_size),
                                               m_mapLastCharLabelInDict("LastCharLabelInDict", dep_table_size)
   { loadScores(); }

   virtual ~CWeight() {
//      iterate_templates(,.freePoolMemory(););
//      CPackedScore<SCORE_TYPE, action::MAX>::freePoolMemory();
   }

   // MEHTODS
   virtual void loadScores();
   virtual void saveScores();
   void computeAverageFeatureWeights(int round);

   void clear() {
      iterate_templates(,.clear(););
   }

   SCORE_TYPE squareNorm() {
      static SCORE_TYPE retval;
      retval = 0;
      iterate_templates(retval+=,.squareNorm(););
      return retval;
   }

   void scaleCurrent(const SCORE_TYPE &scale, const int &round) {
      iterate_templates(,ID(.scaleCurrent(scale, round);));
   }

   void addCurrent(CWeight*w, int round);
   void subtractCurrent(CWeight*w, int round);
 
};

};
};

#endif
