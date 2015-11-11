// Copyright (C) University of Oxford 2010
/***************************************************************
 *
 * weight.h - the dependency parser weights 
 *
 * Yue Zhang, 2007.8 - 2008.1
 *
 ***************************************************************/

#ifndef _DEPPARSER_WEIGHTS_H
#define _DEPPARSER_WEIGHTS_H

#include "posdepparser_weight_base.h"

#define iterate_templates(left, right) \
	left(m_mapST0w)right\
	left(m_mapST0t)right\
	left(m_mapST0wt)right\
	left(m_mapST1w)right\
	left(m_mapST1t)right\
	left(m_mapST1wt)right\
	left(m_mapN0w)right\
	left(m_mapN1w)right\
	left(m_mapST0wST1w)right\
	left(m_mapST0tST1t)right\
	left(m_mapST0wST1t)right\
	left(m_mapST0tST1w)right\
	left(m_mapST0wN0w)right\
	left(m_mapST0tN0w)right\
\
	left(m_mapST0wLARITY)right\
	left(m_mapST0tLARITY)right\
	left(m_mapST1wLARITY)right\
	left(m_mapST1tLARITY)right\
	left(m_mapST1wRARITY)right\
	left(m_mapST1tRARITY)right\
	left(m_mapST0wtST1t)right\
	left(m_mapST0tST1wt)right\
	left(m_mapST0wtST1w)right\
	left(m_mapST0wST1wt)right\
	left(m_mapST0wtST1wt)right\
	left(m_mapST0wDist)right\
	left(m_mapST1wDist)right\
	left(m_mapST0tDist)right\
	left(m_mapST1tDist)right\
	left(m_mapST0wtDist)right\
	left(m_mapST1wtDist)right\
	left(m_mapST0wtN0w)right\
	left(m_mapST0wN1w)right\
	left(m_mapST0tN1w)right\
	left(m_mapST0wtN1w)right\
	left(m_mapST1wN0w)right\
	left(m_mapST1tN0w)right\
	left(m_mapST1wtN0w)right\
	left(m_mapST1wN1w)right\
	left(m_mapST1tN1w)right\
	left(m_mapST1wtN1w)right\
	left(m_mapN0wN1w)right\
	left(m_mapST0tST1tN0w)right\
	left(m_mapST0tST1wN0w)right\
	left(m_mapST0wST1tN0w)right\
	left(m_mapST0tST1tST1LD1t)right\
	left(m_mapST0wST1tST1LD1t)right\
	left(m_mapST0tST1tST1RD1t)right\
	left(m_mapST0wST1tST1RD1t)right\
	left(m_mapST1tST0tST0LD1t)right\
	left(m_mapST1wST0tST0LD1t)right\
	left(m_mapST0LD1w)right\
	left(m_mapST0LD1t)right\
	left(m_mapST0LD1wt)right\
	left(m_mapST1LD1w)right\
	left(m_mapST1LD1t)right\
	left(m_mapST1LD1wt)right\
	left(m_mapST1RD1w)right\
	left(m_mapST1RD1t)right\
	left(m_mapST1RD1wt)right\
	left(m_mapST0tST0LD1tST0LD2t)right\
	left(m_mapST1tST1LD1tST1LD2t)right\
	left(m_mapST1tST1RD1tST1RD2t)right\
	left(m_mapST1wtRARITY)right\
	left(m_mapST0wtLARITY)right\
	left(m_mapST1wtLARITY)right\
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
\
	left(m_mapST2w)right\
	left(m_mapST2t)right\
	left(m_mapST2wt)right\
	left(m_mapST0wST0LD1l)right\
	left(m_mapST1wST1LD1l)right\
	left(m_mapST1wST1RD1l)right\
	left(m_mapST0wST1wDist)right\
	left(m_mapST0tST1tDist)right\
	left(m_mapPrefixChar1)right\
	left(m_mapPrefixChar2)right\
	left(m_mapPrefixChar3)right\
	left(m_mapSuffixChar1)right\
	left(m_mapSuffixChar2)right\
	left(m_mapSuffixChar3)right\
	left(m_mapWordLabelInDict)right\
	left(m_mapFirstCharLabelInDict)right\
	left(m_mapLastCharLabelInDict)right\
	left(m_mapPOSST0w)right\
	left(m_mapPOSST0t)right\
	left(m_mapPOSST0wt)right\
	left(m_mapPOSST0tCurWord)right\
	left(m_mapPOSST0wCurWord)right\
	left(m_mapPOSST0fcCurWord)right\
	left(m_mapPOSST0lcCurWord)right\
	left(m_mapPOSST0tST0LD1t)right\
	left(m_mapPOSST0wtST0LD1t)right\
	left(m_mapPOSST0tST0RD1t)right\
	left(m_mapPOSST0wtST0RD1t)right\
	left(m_mapST0wST0LDlset)right\
	left(m_mapST0tST0LDlset)right\
	left(m_mapST1wST1LDlset)right\
	left(m_mapST1tST1LDlset)right\
	left(m_mapST1wST1RDlset)right\
	left(m_mapST1tST1RDlset)right\
	left(m_mapST0tST1tST1L1t)right\
	left(m_mapST0tST1tST1R1t)right\
	left(m_mapST0tST1tST0L1t)right\
	left(m_mapST2tST1tST0t)right\
	left(m_mapST0tST0LD1l)right\
	left(m_mapST1tST1LD1l)right\
	left(m_mapST1tST1RD1l)right\
\
	left(m_mapStackingPOS1)right\
	left(m_mapStackingPOS1CurrentWord)right\
	left(m_mapStackingPOS2)right\
	left(m_mapStackingPOS2CurrentWord)right\
	left(m_mapStackingPOS1and2)right\
	left(m_mapStackingPOS1and2CurrentWord)right\
	left(m_mapStackingLEFT1ST0t)right\
	left(m_mapStackingLEFT1ST1t)right\
	left(m_mapStackingLEFT2ST0t)right\
	left(m_mapStackingLEFT2ST1t)right\
	left(m_mapStackingLEFT1and2ST0t)right\
	left(m_mapStackingLEFT1and2ST1t)right\
	left(m_mapStackingLEFT1ST0tST1t)right\
	left(m_mapStackingLEFT2ST0tST1t)right\
	left(m_mapStackingLEFT1and2ST0tST1t)right\
	left(m_mapStackingRIGHT1ST0t)right\
	left(m_mapStackingRIGHT1ST1t)right\
	left(m_mapStackingRIGHT2ST0t)right\
	left(m_mapStackingRIGHT2ST1t)right\
	left(m_mapStackingRIGHT1and2ST0t)right\
	left(m_mapStackingRIGHT1and2ST1t)right\
	left(m_mapStackingRIGHT1ST0tST1t)right\
	left(m_mapStackingRIGHT2ST0tST1t)right\
	left(m_mapStackingRIGHT1and2ST0tST1t)right\
	left(m_mapStackingPOP1ST0t)right\
	left(m_mapStackingPOP2ST0t)right\
	left(m_mapStackingPOP1and2ST0t)right





namespace TARGET_LANGUAGE {

namespace posdepparser {

const static unsigned DEP_TABLE_SIZE = (1<<17);//1000121;

//
// TYPE DEFINITIONS
//
typedef CPackedScoreMap<CWord, SCORE_TYPE, action::MAX> CWordMap;
typedef CPackedScoreMap<CTag, SCORE_TYPE, action::MAX> CTagMap;
typedef CPackedScoreMap<unsigned long long, SCORE_TYPE, action::MAX> CLongIntMap;
typedef CPackedScoreMap<int, SCORE_TYPE, action::MAX> CIntMap;
typedef CPackedScoreMap<CTagSet<CTag, 2>,  SCORE_TYPE, action::MAX> CTagSet2Map;
typedef CPackedScoreMap<CTagSet<CTag, 3>, SCORE_TYPE, action::MAX> CTagSet3Map;
typedef CPackedScoreMap<CTagSet<CTag, 4>, SCORE_TYPE, action::MAX> CTagSet4Map;
typedef CPackedScoreMap<std::pair<CWord, CTag>, SCORE_TYPE, action::MAX> CWordTagMap;
typedef CPackedScoreMap<CTuple3<CWord, CTag, CTag>, SCORE_TYPE, action::MAX> CWordTagTagMap;
typedef CPackedScoreMap<CTuple3<CWord, CWord, CTag>, SCORE_TYPE, action::MAX> CWordWordTagMap;
typedef CPackedScoreMap<CTuple3<CWord, CWord, CWord>, SCORE_TYPE, action::MAX> CWordWordWordMap;
typedef CPackedScoreMap<CTuple4<CWord, CWord, CTag, CTag>, SCORE_TYPE, action::MAX> CWordWordTagTagMap;
typedef CPackedScoreMap<CTuple3<CTag, CTag, CTag>, SCORE_TYPE, action::MAX> CTagTagTagMap;
typedef CPackedScoreMap<CTuple2<CTag, CTag>, SCORE_TYPE, action::MAX> CTagTagMap;
typedef CPackedScoreMap<CTaggedWord<CTag, TAG_SEPARATOR>, SCORE_TYPE, action::MAX> CTaggedWordMap;
typedef CPackedScoreMap<CTuple2<CWord, CWord>, SCORE_TYPE, action::MAX> CWordWordMap;
typedef CPackedScoreMap<CTwoTaggedWords, SCORE_TYPE, action::MAX> CTwoTaggedWordsMap;
typedef CPackedScoreMap<CTuple2<CWord, int>, SCORE_TYPE, action::MAX> CWordIntMap;
typedef CPackedScoreMap<CTuple2<CTag, int>, SCORE_TYPE, action::MAX> CTagIntMap;
typedef CPackedScoreMap<std::pair<CWord, unsigned long long>, SCORE_TYPE, action::MAX> CWordLongIntMap;
typedef CPackedScoreMap<std::pair<CTag, unsigned long long>, SCORE_TYPE, action::MAX> CTagLongIntMap;
typedef CPackedScoreMap<CTuple3<CTag, CTag, int>, SCORE_TYPE, action::MAX> CTagTagIntMap;
typedef CPackedScoreMap<CTuple3<CWord, CWord, int>, SCORE_TYPE, action::MAX> CWordWordIntMap;
typedef CPackedScoreMap<CTuple3<CWord, CTag, int>, SCORE_TYPE, action::MAX> CWordTagIntMap;



typedef CHashMap<CWord, unsigned long> CWordToIntMap;
typedef CHashMap<unsigned long, unsigned long> CIntToIntMap;

/*===============================================================
 *
 * CWeight - the definition of weights, in feature
 *
 *==============================================================*/

class CWeight : public CWeightBase {

public:
	CWordMap m_mapST0w;
	CTagMap m_mapST0t;
	CWordTagMap m_mapST0wt;
	CWordMap m_mapST1w;
	CTagMap m_mapST1t;
	CWordTagMap m_mapST1wt;
	CWordMap m_mapN0w;
	CWordMap m_mapN1w;
	CWordWordMap m_mapST0wST1w;
	CTagTagMap m_mapST0tST1t;
	CWordTagMap m_mapST0wST1t;
	CWordTagMap m_mapST0tST1w;
	CWordWordMap m_mapST0wN0w;
	CWordTagMap m_mapST0tN0w;

	   CWordIntMap	m_mapST0wLARITY;
	   CTagIntMap	m_mapST0tLARITY;
	   CWordIntMap	m_mapST1wLARITY;
	   CTagIntMap	m_mapST1tLARITY;
	   CWordIntMap	m_mapST1wRARITY;
	   CTagIntMap	m_mapST1tRARITY;
	   CWordTagTagMap	m_mapST0wtST1t;
	   CWordTagTagMap	m_mapST0tST1wt;
	   CWordWordTagMap	m_mapST0wtST1w;
	   CWordWordTagMap	m_mapST0wST1wt;
	   CWordWordTagTagMap	m_mapST0wtST1wt;
	   CWordIntMap	m_mapST0wDist;
	   CWordIntMap	m_mapST1wDist;
	   CTagIntMap	m_mapST0tDist;
	   CTagIntMap	m_mapST1tDist;
	   CWordTagIntMap	m_mapST0wtDist;
	   CWordTagIntMap	m_mapST1wtDist;
	   CWordWordTagMap	m_mapST0wtN0w;
	   CWordWordMap	m_mapST0wN1w;
	   CWordTagMap	m_mapST0tN1w;
	   CWordWordTagMap	m_mapST0wtN1w;
	   CWordWordMap	m_mapST1wN0w;
	   CWordTagMap	m_mapST1tN0w;
	   CWordWordTagMap	m_mapST1wtN0w;
	   CWordWordMap	m_mapST1wN1w;
	   CWordTagMap	m_mapST1tN1w;
	   CWordWordTagMap	m_mapST1wtN1w;
	   CWordWordMap	m_mapN0wN1w;
	   CWordTagTagMap	m_mapST0tST1tN0w;
	   CWordWordTagMap	m_mapST0tST1wN0w;
	   CWordWordTagMap	m_mapST0wST1tN0w;
	   CTagTagTagMap	m_mapST0tST1tST1LD1t;
	   CWordTagTagMap	m_mapST0wST1tST1LD1t;
	   CTagTagTagMap	m_mapST0tST1tST1RD1t;
	   CWordTagTagMap	m_mapST0wST1tST1RD1t;
	   CTagTagTagMap	m_mapST1tST0tST0LD1t;
	   CWordTagTagMap	m_mapST1wST0tST0LD1t;
	   CWordMap	m_mapST0LD1w;
	   CTagMap	m_mapST0LD1t;
	   CWordTagMap	m_mapST0LD1wt;
	   CWordMap	m_mapST1LD1w;
	   CTagMap	m_mapST1LD1t;
	   CWordTagMap	m_mapST1LD1wt;
	   CWordMap	m_mapST1RD1w;
	   CTagMap	m_mapST1RD1t;
	   CWordTagMap	m_mapST1RD1wt;
	   CTagTagTagMap	m_mapST0tST0LD1tST0LD2t;
	   CTagTagTagMap	m_mapST1tST1LD1tST1LD2t;
	   CTagTagTagMap	m_mapST1tST1RD1tST1RD2t;
	   CWordTagIntMap	m_mapST1wtRARITY;
	   CWordTagIntMap	m_mapST0wtLARITY;
	   CWordTagIntMap	m_mapST1wtLARITY;

	   CWordMap	m_mapCurrentWord;
	   CTagMap	m_mapLastTag;
	   CTagTagMap	m_mapLastTwoTags;
	   CWordMap	m_mapLastWord;
	   CWordTagMap	m_mapLastTagCurrentWord;
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

	   CWordMap	m_mapST2w;
	   CTagMap	m_mapST2t;
	   CWordTagMap	m_mapST2wt;
	   CWordLongIntMap	m_mapST0wST0LD1l;
	   CWordLongIntMap	m_mapST1wST1LD1l;
	   CWordLongIntMap	m_mapST1wST1RD1l;
	   CWordWordIntMap	m_mapST0wST1wDist;
	   CTagTagIntMap	m_mapST0tST1tDist;
	   CWordMap	m_mapPrefixChar1;
	   CWordWordMap	m_mapPrefixChar2;
	   CWordWordWordMap	m_mapPrefixChar3;
	   CWordMap	m_mapSuffixChar1;
	   CWordWordMap	m_mapSuffixChar2;
	   CWordWordWordMap	m_mapSuffixChar3;
	   CLongIntMap	m_mapWordLabelInDict;
	   CLongIntMap	m_mapFirstCharLabelInDict;
	   CLongIntMap	m_mapLastCharLabelInDict;
	   CWordMap	m_mapPOSST0w;
	   CTagMap	m_mapPOSST0t;
	   CWordTagMap	m_mapPOSST0wt;
	   CWordTagMap	m_mapPOSST0tCurWord;
	   CWordWordMap	m_mapPOSST0wCurWord;
	   CWordWordMap	m_mapPOSST0fcCurWord;
	   CWordWordMap	m_mapPOSST0lcCurWord;
	   CTagTagMap	m_mapPOSST0tST0LD1t;
	   CWordTagTagMap	m_mapPOSST0wtST0LD1t;
	   CTagTagMap	m_mapPOSST0tST0RD1t;
	   CWordTagTagMap	m_mapPOSST0wtST0RD1t;

	   CWordLongIntMap	m_mapST0wST0LDlset;
	   CTagLongIntMap	m_mapST0tST0LDlset;
	   CWordLongIntMap	m_mapST1wST1LDlset;
	   CTagLongIntMap	m_mapST1tST1LDlset;
	   CWordLongIntMap	m_mapST1wST1RDlset;
	   CTagLongIntMap	m_mapST1tST1RDlset;
	   CTagTagTagMap	m_mapST0tST1tST1L1t;
	   CTagTagTagMap	m_mapST0tST1tST1R1t;
	   CTagTagTagMap	m_mapST0tST1tST0L1t;
	   CTagTagTagMap	m_mapST2tST1tST0t;
	   CTagLongIntMap	m_mapST0tST0LD1l;
	   CTagLongIntMap	m_mapST1tST1LD1l;
	   CTagLongIntMap	m_mapST1tST1RD1l;

	   CTagMap	m_mapStackingPOS1;
	   CWordTagMap	m_mapStackingPOS1CurrentWord;
	   CTagMap	m_mapStackingPOS2;
	   CWordTagMap	m_mapStackingPOS2CurrentWord;
	   CTagMap	m_mapStackingPOS1and2;
	   CWordTagMap	m_mapStackingPOS1and2CurrentWord;
	   CTagIntMap	m_mapStackingLEFT1ST0t;
	   CTagIntMap	m_mapStackingLEFT1ST1t;
	   CTagIntMap	m_mapStackingLEFT2ST0t;
	   CTagIntMap	m_mapStackingLEFT2ST1t;
	   CTagIntMap	m_mapStackingLEFT1and2ST0t;
	   CTagIntMap	m_mapStackingLEFT1and2ST1t;
	   CTagTagIntMap	m_mapStackingLEFT1ST0tST1t;
	   CTagTagIntMap	m_mapStackingLEFT2ST0tST1t;
	   CTagTagIntMap	m_mapStackingLEFT1and2ST0tST1t;
	   CTagIntMap	m_mapStackingRIGHT1ST0t;
	   CTagIntMap	m_mapStackingRIGHT1ST1t;
	   CTagIntMap	m_mapStackingRIGHT2ST0t;
	   CTagIntMap	m_mapStackingRIGHT2ST1t;
	   CTagIntMap	m_mapStackingRIGHT1and2ST0t;
	   CTagIntMap	m_mapStackingRIGHT1and2ST1t;
	   CTagTagIntMap	m_mapStackingRIGHT1ST0tST1t;
	   CTagTagIntMap	m_mapStackingRIGHT2ST0tST1t;
	   CTagTagIntMap	m_mapStackingRIGHT1and2ST0tST1t;
	   CTagIntMap	m_mapStackingPOP1ST0t;
	   CTagIntMap	m_mapStackingPOP2ST0t;
	   CTagIntMap	m_mapStackingPOP1and2ST0t;





	   unsigned long m_nMaxWordFrequency;
	   CWordToIntMap m_mapWordFrequency;
	   CWordToIntMap m_mapCharFrequency;

	   CTagDict<CWord, CTag> m_mapTagDictionary;
	   CTagDict<CWord, CTag> m_mapCharTagDictionary;
	   CIntToIntMap m_mapTagPairLabelDictionary;
	   CIntToIntMap m_mapTagPairDictionary;





public:

   CWeight(const std::string &sPath, bool bTrain) : CWeightBase(sPath, bTrain) ,

										   m_nMaxWordFrequency(0) ,
										   m_mapWordFrequency(65537),
										   m_mapCharFrequency(65537),
										   m_mapTagDictionary(CTag::COUNT),
										   m_mapCharTagDictionary(CTag::COUNT),
										   m_mapTagPairLabelDictionary(CTag::COUNT*CTag::COUNT*CDependencyLabel::COUNT+1),
										   m_mapTagPairDictionary(CTag::COUNT*CTag::COUNT+1),


										   m_mapST0w("ST0w", DEP_TABLE_SIZE),
										   m_mapST0t("ST0t", DEP_TABLE_SIZE),
										   m_mapST0wt("ST0wt", DEP_TABLE_SIZE),
										   m_mapST1w("ST1w", DEP_TABLE_SIZE),
										   m_mapST1t("ST1t", DEP_TABLE_SIZE),
										   m_mapST1wt("ST1wt", DEP_TABLE_SIZE),
										   m_mapN0w("N0w", DEP_TABLE_SIZE),
										   m_mapN1w("N1w", DEP_TABLE_SIZE),
										   m_mapST0wST1w("ST0wST1w", DEP_TABLE_SIZE),
										   m_mapST0tST1t("ST0tST1t", DEP_TABLE_SIZE),
										   m_mapST0wST1t("ST0wST1t", DEP_TABLE_SIZE),
										   m_mapST0tST1w("ST0tST1w", DEP_TABLE_SIZE),
										   m_mapST0wN0w("ST0wN0w", DEP_TABLE_SIZE),
										   m_mapST0tN0w("ST0tN0w", DEP_TABLE_SIZE),
										   m_mapST0wLARITY("ST0wLARITY", DEP_TABLE_SIZE),
										   m_mapST0tLARITY("ST0tLARITY", DEP_TABLE_SIZE),
										   m_mapST1wLARITY("ST1wLARITY", DEP_TABLE_SIZE),
										   m_mapST1tLARITY("ST1tLARITY", DEP_TABLE_SIZE),
										   m_mapST1wRARITY("ST1wRARITY", DEP_TABLE_SIZE),
										   m_mapST1tRARITY("ST1tRARITY", DEP_TABLE_SIZE),
										   m_mapST0wtST1t("ST0wtST1t", DEP_TABLE_SIZE),
										   m_mapST0tST1wt("ST0tST1wt", DEP_TABLE_SIZE),
										   m_mapST0wtST1w("ST0wtST1w", DEP_TABLE_SIZE),
										   m_mapST0wST1wt("ST0wST1wt", DEP_TABLE_SIZE),
										   m_mapST0wtST1wt("ST0wtST1wt", DEP_TABLE_SIZE),
										   m_mapST0wDist("ST0wDist", DEP_TABLE_SIZE),
										   m_mapST1wDist("ST1wDist", DEP_TABLE_SIZE),
										   m_mapST0tDist("ST0tDist", DEP_TABLE_SIZE),
										   m_mapST1tDist("ST1tDist", DEP_TABLE_SIZE),
										   m_mapST0wtDist("ST0wtDist", DEP_TABLE_SIZE),
										   m_mapST1wtDist("ST1wtDist", DEP_TABLE_SIZE),
										   m_mapST0wtN0w("ST0wtN0w", DEP_TABLE_SIZE),
										   m_mapST0wN1w("ST0wN1w", DEP_TABLE_SIZE),
										   m_mapST0tN1w("ST0tN1w", DEP_TABLE_SIZE),
										   m_mapST0wtN1w("ST0wtN1w", DEP_TABLE_SIZE),
										   m_mapST1wN0w("ST1wN0w", DEP_TABLE_SIZE),
										   m_mapST1tN0w("ST1tN0w", DEP_TABLE_SIZE),
										   m_mapST1wtN0w("ST1wtN0w", DEP_TABLE_SIZE),
										   m_mapST1wN1w("ST1wN1w", DEP_TABLE_SIZE),
										   m_mapST1tN1w("ST1tN1w", DEP_TABLE_SIZE),
										   m_mapST1wtN1w("ST1wtN1w", DEP_TABLE_SIZE),
										   m_mapN0wN1w("N0wN1w", DEP_TABLE_SIZE),
										   m_mapST0tST1tN0w("ST0tST1tN0w", DEP_TABLE_SIZE),
										   m_mapST0tST1wN0w("ST0tST1wN0w", DEP_TABLE_SIZE),
										   m_mapST0wST1tN0w("ST0wST1tN0w", DEP_TABLE_SIZE),
										   m_mapST0tST1tST1LD1t("ST0tST1tST1LD1t", DEP_TABLE_SIZE),
										   m_mapST0wST1tST1LD1t("ST0wST1tST1LD1t", DEP_TABLE_SIZE),
										   m_mapST0tST1tST1RD1t("ST0tST1tST1RD1t", DEP_TABLE_SIZE),
										   m_mapST0wST1tST1RD1t("ST0wST1tST1RD1t", DEP_TABLE_SIZE),
										   m_mapST1tST0tST0LD1t("ST1tST0tST0LD1t", DEP_TABLE_SIZE),
										   m_mapST1wST0tST0LD1t("ST1wST0tST0LD1t", DEP_TABLE_SIZE),
										   m_mapST0LD1w("ST0LD1w", DEP_TABLE_SIZE),
										   m_mapST0LD1t("ST0LD1t", DEP_TABLE_SIZE),
										   m_mapST0LD1wt("ST0LD1wt", DEP_TABLE_SIZE),
										   m_mapST1LD1w("ST1LD1w", DEP_TABLE_SIZE),
										   m_mapST1LD1t("ST1LD1t", DEP_TABLE_SIZE),
										   m_mapST1LD1wt("ST1LD1wt", DEP_TABLE_SIZE),
										   m_mapST1RD1w("ST1RD1w", DEP_TABLE_SIZE),
										   m_mapST1RD1t("ST1RD1t", DEP_TABLE_SIZE),
										   m_mapST1RD1wt("ST1RD1wt", DEP_TABLE_SIZE),
										   m_mapST0tST0LD1tST0LD2t("ST0tST0LD1tST0LD2t", DEP_TABLE_SIZE),
										   m_mapST1tST1LD1tST1LD2t("ST1tST1LD1tST1LD2t", DEP_TABLE_SIZE),
										   m_mapST1tST1RD1tST1RD2t("ST1tST1RD1tST1RD2t", DEP_TABLE_SIZE),
										   m_mapST1wtRARITY("ST1wtRARITY", DEP_TABLE_SIZE),
										   m_mapST0wtLARITY("ST0wtLARITY", DEP_TABLE_SIZE),
										   m_mapST1wtLARITY("ST1wtLARITY", DEP_TABLE_SIZE),
										   m_mapCurrentWord("CurrentWord", DEP_TABLE_SIZE),
										   m_mapLastTag("LastTag", DEP_TABLE_SIZE),
										   m_mapLastTwoTags("LastTwoTags", DEP_TABLE_SIZE),
										   m_mapLastWord("LastWord", DEP_TABLE_SIZE),
										   m_mapLastTagCurrentWord("LastTagCurrentWord", DEP_TABLE_SIZE),
										   m_mapCurentWordPrevChar("CurentWordPrevChar", DEP_TABLE_SIZE),
										   m_mapLastWordFirstChar("LastWordFirstChar", DEP_TABLE_SIZE),
										   m_mapNextWord("NextWord", DEP_TABLE_SIZE),
										   m_mapCurentWordNextChar("CurentWordNextChar", DEP_TABLE_SIZE),
										   m_mapNextWordLastChar("NextWordLastChar", DEP_TABLE_SIZE),
										   m_mapOneCharWordTriChar("OneCharWordTriChar", DEP_TABLE_SIZE),
										   m_mapFirstChar("FirstChar", DEP_TABLE_SIZE),
										   m_mapLastChar("LastChar", DEP_TABLE_SIZE),
										   m_mapFirstCharCat("FirstCharCat", DEP_TABLE_SIZE),
										   m_mapLastCharCat("LastCharCat", DEP_TABLE_SIZE),
										   m_mapCharInWord("CharInWord", DEP_TABLE_SIZE),
										   m_mapCharInWordByFirstChar("CharInWordByFirstChar", DEP_TABLE_SIZE),
										   m_mapRepeatedChar("RepeatedChar", DEP_TABLE_SIZE),
										   m_mapRepeated2Char("Repeated2Char", DEP_TABLE_SIZE),
										   m_mapCharInWordByLastChar("CharInWordByLastChar", DEP_TABLE_SIZE),
										   m_mapNormalizedLength("NormalizedLength", DEP_TABLE_SIZE),
										   m_mapST2w("ST2w", DEP_TABLE_SIZE),
										   m_mapST2t("ST2t", DEP_TABLE_SIZE),
										   m_mapST2wt("ST2wt", DEP_TABLE_SIZE),
										   m_mapST0wST0LD1l("ST0LD1l", DEP_TABLE_SIZE),
										   m_mapST1wST1LD1l("ST1LD1l", DEP_TABLE_SIZE),
										   m_mapST1wST1RD1l("ST1RD1l", DEP_TABLE_SIZE),
										   m_mapST0wST1wDist("ST0wST1wDist", DEP_TABLE_SIZE),
										   m_mapST0tST1tDist("ST0tST1tDist", DEP_TABLE_SIZE),
										   m_mapPrefixChar1("PrefixChar1", DEP_TABLE_SIZE),
										   m_mapPrefixChar2("PrefixChar2", DEP_TABLE_SIZE),
										   m_mapPrefixChar3("PrefixChar3", DEP_TABLE_SIZE),
										   m_mapSuffixChar1("SuffixChar1", DEP_TABLE_SIZE),
										   m_mapSuffixChar2("SuffixChar2", DEP_TABLE_SIZE),
										   m_mapSuffixChar3("SuffixChar3", DEP_TABLE_SIZE),
										   m_mapWordLabelInDict("WordLabelInDict", DEP_TABLE_SIZE),
										   m_mapFirstCharLabelInDict("FirstCharLabelInDict", DEP_TABLE_SIZE),
										   m_mapLastCharLabelInDict("LastCharLabelInDict", DEP_TABLE_SIZE),
										   m_mapPOSST0w("POSST0w", DEP_TABLE_SIZE),
										   m_mapPOSST0t("POSST0t", DEP_TABLE_SIZE),
										   m_mapPOSST0wt("POSST0wt", DEP_TABLE_SIZE),
										   m_mapPOSST0tCurWord("POSST0tCurWord", DEP_TABLE_SIZE),
										   m_mapPOSST0wCurWord("POSST0wCurWord", DEP_TABLE_SIZE),
										   m_mapPOSST0fcCurWord("POSST0fcCurWord", DEP_TABLE_SIZE),
										   m_mapPOSST0lcCurWord("POSST0lcCurWord", DEP_TABLE_SIZE),
										   m_mapPOSST0tST0LD1t("POSST0tST0LD1t", DEP_TABLE_SIZE),
										   m_mapPOSST0wtST0LD1t("POSST0wtST0LD1t", DEP_TABLE_SIZE),
										   m_mapPOSST0tST0RD1t("POSST0tST0RD1t", DEP_TABLE_SIZE),
										   m_mapPOSST0wtST0RD1t("POSST0wtST0RD1t", DEP_TABLE_SIZE),
										   m_mapST0wST0LDlset("ST0wST0LDlset", DEP_TABLE_SIZE),
										   m_mapST0tST0LDlset("ST0tST0LDlset", DEP_TABLE_SIZE),
										   m_mapST1wST1LDlset("ST1wST1LDlset", DEP_TABLE_SIZE),
										   m_mapST1tST1LDlset("ST1tST1LDlset", DEP_TABLE_SIZE),
										   m_mapST1wST1RDlset("ST1wST1RDlset", DEP_TABLE_SIZE),
										   m_mapST1tST1RDlset("ST1tST1RDlset", DEP_TABLE_SIZE),
										   m_mapST0tST1tST1L1t("ST0tST1tST1L1t", DEP_TABLE_SIZE),
										   m_mapST0tST1tST1R1t("ST0tST1tST1R1t", DEP_TABLE_SIZE),
										   m_mapST0tST1tST0L1t("ST0tST1tST0L1t", DEP_TABLE_SIZE),
										   m_mapST2tST1tST0t("ST2tST1tST0t", DEP_TABLE_SIZE),
										   m_mapST0tST0LD1l("ST0tST0LD1l", DEP_TABLE_SIZE),
										   m_mapST1tST1LD1l("ST1tST1LD1l", DEP_TABLE_SIZE),
										   m_mapST1tST1RD1l("ST1tST1RD1l", DEP_TABLE_SIZE),
										   m_mapStackingPOS1("StackingPOS1", DEP_TABLE_SIZE),
										   m_mapStackingPOS1CurrentWord("StackingPOS1CurrentWord", DEP_TABLE_SIZE),
										   m_mapStackingPOS2("StackingPOS2", DEP_TABLE_SIZE),
										   m_mapStackingPOS2CurrentWord("StackingPOS2CurrentWord", DEP_TABLE_SIZE),
										   m_mapStackingPOS1and2("StackingPOS1and2", DEP_TABLE_SIZE),
										   m_mapStackingPOS1and2CurrentWord("StackingPOS1and2CurrentWord", DEP_TABLE_SIZE),
										   m_mapStackingLEFT1ST0t("StackingLEFT1ST0t", DEP_TABLE_SIZE),
										   m_mapStackingLEFT1ST1t("StackingLEFT1ST1t", DEP_TABLE_SIZE),
										   m_mapStackingLEFT2ST0t("StackingLEFT2ST0t", DEP_TABLE_SIZE),
										   m_mapStackingLEFT2ST1t("StackingLEFT2ST1t", DEP_TABLE_SIZE),
										   m_mapStackingLEFT1and2ST0t("StackingLEFT1and2ST0t", DEP_TABLE_SIZE),
										   m_mapStackingLEFT1and2ST1t("StackingLEFT1and2ST1t", DEP_TABLE_SIZE),
										   m_mapStackingLEFT1ST0tST1t("StackingLEFT1ST0tST1t", DEP_TABLE_SIZE),
										   m_mapStackingLEFT2ST0tST1t("StackingLEFT2ST0tST1t", DEP_TABLE_SIZE),
										   m_mapStackingLEFT1and2ST0tST1t("StackingLEFT1and2ST0tST1t", DEP_TABLE_SIZE),
										   m_mapStackingRIGHT1ST0t("StackingRIGHT1ST0t", DEP_TABLE_SIZE),
										   m_mapStackingRIGHT1ST1t("StackingRIGHT1ST1t", DEP_TABLE_SIZE),
										   m_mapStackingRIGHT2ST0t("StackingRIGHT2ST0t", DEP_TABLE_SIZE),
										   m_mapStackingRIGHT2ST1t("StackingRIGHT2ST1t", DEP_TABLE_SIZE),
										   m_mapStackingRIGHT1and2ST0t("StackingRIGHT1and2ST0t", DEP_TABLE_SIZE),
										   m_mapStackingRIGHT1and2ST1t("StackingRIGHT1and2ST1t", DEP_TABLE_SIZE),
										   m_mapStackingRIGHT1ST0tST1t("StackingRIGHT1ST0tST1t", DEP_TABLE_SIZE),
										   m_mapStackingRIGHT2ST0tST1t("StackingRIGHT2ST0tST1t", DEP_TABLE_SIZE),
										   m_mapStackingRIGHT1and2ST0tST1t("StackingRIGHT1and2ST0tST1t", DEP_TABLE_SIZE),
										   m_mapStackingPOP1ST0t("StackingRIGHT1ST0t", DEP_TABLE_SIZE),
										   m_mapStackingPOP2ST0t("StackingRIGHT2ST0t", DEP_TABLE_SIZE),
										   m_mapStackingPOP1and2ST0t("StackingRIGHT1and2ST0t", DEP_TABLE_SIZE)

   { loadScores(); }

   virtual ~CWeight() {
//      iterate_templates(,.freePoolMemory(););
//      CPackedScore<SCORE_TYPE, action::MAX>::freePoolMemory();
   }

   // MEHTODS
   virtual void loadScores();
   virtual void saveScores();
   void computeAverageFeatureWeights(int round);
   SCORE_TYPE dotProduct(const CWeight &w);
 
};

};
};

#endif
