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

#define ID(x) x
#define ID_LRB (
#define ID_RRB )
#define ID_COMMA ,


#define iterate_templates(left, right) \
	left(m_mapLengthByLastChar)right\
	left(m_mapFirstCharBy2Tags)right\
	left(m_mapST0wLARITY)right\
	left(m_mapST0tLARITY)right\
	left(m_mapConsecutiveChars)right\
	left(m_mapST0wST1wDist)right\
	left(m_mapST0wN0c)right\
	left(m_mapST0aN0a)right\
	left(m_mapST1LD1t)right\
	left(m_mapST1LD1w)right\
	left(m_mapST0wtST1t)right\
	left(m_mapST0wtST1w)right\
	left(m_mapN3a)right\
	left(m_mapST0tST1tST1R1t)right\
	left(m_mapN3c)right\
	left(m_mapST1tST0tST0LD1t)right\
	left(m_mapN0aN1aN2a)right\
	left(m_mapTagByFirstChar)right\
	left(m_mapST0tST1w)right\
	left(m_mapST0wST1tST1RD1t)right\
	left(m_mapST0tST1t)right\
	left(m_mapN0cN1cN2c)right\
	left(m_mapST0aST1a)right\
	left(m_mapST1tST1LD1tST1LD2t)right\
	left(m_mapLastTagByWord)right\
	left(m_mapTaggedCharByLastChar)right\
	left(m_mapST0tST1c)right\
	left(m_mapST0tN0c)right\
	left(m_mapSeparateChars)right\
	left(m_mapTaggedConsecutiveChars)right\
	left(m_mapST1tDist)right\
	left(m_mapST0tST1tST1L1t)right\
	left(m_mapST1w)right\
	left(m_mapTag0Tag1Tag2Size1)right\
	left(m_mapST0wtST1wt)right\
	left(m_mapST1wLARITY)right\
	left(m_mapTagByFirstCharCat)right\
	left(m_mapST1wt)right\
	left(m_mapTag1Tag2Size1)right\
	left(m_mapST1LD1wt)right\
	left(m_mapST2tST1tST0t)right\
	left(m_mapST0LD1w)right\
	left(m_mapST1t)right\
	left(m_mapST0LD1t)right\
	left(m_mapST0tST1tST1RD1t)right\
	left(m_mapST0cN0c)right\
	left(m_mapTagByLastWord)right\
	left(m_mapST1tST1RD1tST1RD2t)right\
	left(m_mapST0wt)right\
	left(m_mapLastWordFirstChar)right\
	left(m_mapFirstAndLastChars)right\
	left(m_mapCurentWordTag)right\
	left(m_mapTaggedFirstCharCurrentChar)right\
	left(m_mapTagByWordAndNextChar)right\
	left(m_mapAPPTagByChar)right\
	left(m_mapTagByWordAndPrevChar)right\
	left(m_mapTag0Tag1Size1)right\
	left(m_mapST0tST1tST0L1t)right\
	left(m_mapLastTagByTag)right\
	left(m_mapST0wDist)right\
	left(m_mapN0cN1c)right\
	left(m_mapFirstCharLastWordByWord)right\
	left(m_mapST0t)right\
	left(m_mapST1tLARITY)right\
	left(m_mapCharByLastChar)right\
	left(m_mapLastWordByWord)right\
	left(m_mapLengthByFirstChar)right\
	left(m_mapST0tST1tN0c)right\
	left(m_mapN0aN1a)right\
	left(m_mapST0wST1tST1LD1t)right\
	left(m_mapST1c)right\
	left(m_mapST1a)right\
	left(m_mapLastWordByLastChar)right\
	left(m_mapST0tST1tDist)right\
	left(m_mapST0tST0LD1tST0LD2t)right\
	left(m_mapST0w)right\
	left(m_mapST1ct)right\
	left(m_mapST0wST1tN0c)right\
	left(m_mapST0LD1wt)right\
	left(m_mapTaggedSeparateChars)right\
	left(m_mapST0tST1wt)right\
	left(m_mapCurentWord)right\
	left(m_mapTaggedCharByFirstChar)right\
	left(m_mapST1wDist)right\
	left(m_mapST0tST1wN0c)right\
	left(m_mapST1wST0tST0LD1t)right\
	left(m_mapST0c)right\
	left(m_mapLastTwoTagsByTag)right\
	left(m_mapST1RD1w)right\
	left(m_mapST0a)right\
	left(m_mapN0c)right\
	left(m_mapN0a)right\
	left(m_mapST1RD1t)right\
	left(m_mapTagOfOneCharWord)right\
	left(m_mapWordTagTag)right\
	left(m_mapTagByLastCharCat)right\
	left(m_mapST0cST1c)right\
	left(m_mapST0wST1wt)right\
	left(m_mapST1tRARITY)right\
	left(m_mapCurrentWordLastChar)right\
	left(m_mapN1a)right\
	left(m_mapST1wRARITY)right\
	left(m_mapN1c)right\
	left(m_mapST0ct)right\
	left(m_mapST0tDist)right\
	left(m_mapTagByLastChar)right\
	left(m_mapST0tST1tST1LD1t)right\
	left(m_mapFirstCharCurrentChar)right\
	left(m_mapFirstCharBy3Tags)right\
	left(m_mapST0wST1w)right\
	left(m_mapST0wtN0c)right\
	left(m_mapST0wST1t)right\
	left(m_mapST1RD1wt)right\
	left(m_mapTagWordTag)right\
	left(m_mapST0cST1t)right\
	left(m_mapN2c)right\
	left(m_mapN2a)right\
	left(m_mapOneCharWord)right


#define iterate_double_templates(left, middle, right)\
	left	m_mapST0w  middle  m_mapST0w  right\
	left	m_mapST0t  middle  m_mapST0t  right\
	left	m_mapST0wt  middle  m_mapST0wt  right\
	left	m_mapST1w  middle  m_mapST1w  right\
	left	m_mapST1t  middle  m_mapST1t  right\
	left	m_mapST1wt  middle  m_mapST1wt  right\
	left	m_mapN0w  middle  m_mapN0w  right\
	left	m_mapN1w  middle  m_mapN1w  right\
	left	m_mapST0wST1w  middle  m_mapST0wST1w  right\
	left	m_mapST0tST1t  middle  m_mapST0tST1t  right\
	left	m_mapST0wST1t  middle  m_mapST0wST1t  right\
	left	m_mapST0tST1w  middle  m_mapST0tST1w  right\
	left	m_mapST0wN0w  middle  m_mapST0wN0w  right\
	left	m_mapST0tN0w  middle  m_mapST0tN0w  right\
	left	m_mapST0wLARITY  middle  m_mapST0wLARITY  right\
	left	m_mapST0tLARITY  middle  m_mapST0tLARITY  right\
	left	m_mapST1wLARITY  middle  m_mapST1wLARITY  right\
	left	m_mapST1tLARITY  middle  m_mapST1tLARITY  right\
	left	m_mapST1wRARITY  middle  m_mapST1wRARITY  right\
	left	m_mapST1tRARITY  middle  m_mapST1tRARITY  right\
	left	m_mapST0wtST1t  middle  m_mapST0wtST1t  right\
	left	m_mapST0tST1wt  middle  m_mapST0tST1wt  right\
	left	m_mapST0wtST1w  middle  m_mapST0wtST1w  right\
	left	m_mapST0wST1wt  middle  m_mapST0wST1wt  right\
	left	m_mapST0wtST1wt  middle  m_mapST0wtST1wt  right\
	left	m_mapST0wDist  middle  m_mapST0wDist  right\
	left	m_mapST1wDist  middle  m_mapST1wDist  right\
	left	m_mapST0tDist  middle  m_mapST0tDist  right\
	left	m_mapST1tDist  middle  m_mapST1tDist  right\
	left	m_mapST0wtDist  middle  m_mapST0wtDist  right\
	left	m_mapST1wtDist  middle  m_mapST1wtDist  right\
	left	m_mapST0wtN0w  middle  m_mapST0wtN0w  right\
	left	m_mapST0wN1w  middle  m_mapST0wN1w  right\
	left	m_mapST0tN1w  middle  m_mapST0tN1w  right\
	left	m_mapST0wtN1w  middle  m_mapST0wtN1w  right\
	left	m_mapST1wN0w  middle  m_mapST1wN0w  right\
	left	m_mapST1tN0w  middle  m_mapST1tN0w  right\
	left	m_mapST1wtN0w  middle  m_mapST1wtN0w  right\
	left	m_mapST1wN1w  middle  m_mapST1wN1w  right\
	left	m_mapST1tN1w  middle  m_mapST1tN1w  right\
	left	m_mapST1wtN1w  middle  m_mapST1wtN1w  right\
	left	m_mapN0wN1w  middle  m_mapN0wN1w  right\
	left	m_mapST0tST1tN0w  middle  m_mapST0tST1tN0w  right\
	left	m_mapST0tST1wN0w  middle  m_mapST0tST1wN0w  right\
	left	m_mapST0wST1tN0w  middle  m_mapST0wST1tN0w  right\
	left	m_mapST0tST1tST1LD1t  middle  m_mapST0tST1tST1LD1t  right\
	left	m_mapST0wST1tST1LD1t  middle  m_mapST0wST1tST1LD1t  right\
	left	m_mapST0tST1tST1RD1t  middle  m_mapST0tST1tST1RD1t  right\
	left  m_mapST0wST1tST1RD1t  middle  m_mapST0wST1tST1RD1t  right\
	left  m_mapST1tST0tST0LD1t  middle  m_mapST1tST0tST0LD1t  right\
	left  m_mapST1wST0tST0LD1t  middle  m_mapST1wST0tST0LD1t  right\
	left  m_mapST0LD1w  middle  m_mapST0LD1w  right\
	left  m_mapST0LD1t  middle  m_mapST0LD1t  right\
	left  m_mapST0LD1wt  middle  m_mapST0LD1wt  right\
	left  m_mapST1LD1w  middle  m_mapST1LD1w  right\
	left  m_mapST1LD1t  middle  m_mapST1LD1t  right\
	left  m_mapST1LD1wt  middle  m_mapST1LD1wt  right\
	left  m_mapST1RD1w  middle  m_mapST1RD1w  right\
	left  m_mapST1RD1t  middle  m_mapST1RD1t  right\
	left  m_mapST1RD1wt  middle  m_mapST1RD1wt  right\
	left  m_mapST0tST0LD1tST0LD2t  middle  m_mapST0tST0LD1tST0LD2t  right\
	left  m_mapST1tST1LD1tST1LD2t  middle  m_mapST1tST1LD1tST1LD2t  right\
	left  m_mapST1tST1RD1tST1RD2t  middle  m_mapST1tST1RD1tST1RD2t  right\
	left  m_mapST1wtRARITY  middle  m_mapST1wtRARITY  right\
	left  m_mapST0wtLARITY  middle  m_mapST0wtLARITY  right\
	left  m_mapST1wtLARITY  middle  m_mapST1wtLARITY  right\
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
	left  m_mapST2w  middle  m_mapST2w  right\
	left  m_mapST2t  middle  m_mapST2t  right\
	left  m_mapST2wt  middle  m_mapST2wt  right\
	left  m_mapST0wST0LD1l  middle  m_mapST0wST0LD1l  right\
	left  m_mapST1wST1LD1l  middle  m_mapST1wST1LD1l  right\
	left  m_mapST1wST1RD1l  middle  m_mapST1wST1RD1l  right\
	left  m_mapST0wST1wDist  middle  m_mapST0wST1wDist  right\
	left  m_mapST0tST1tDist  middle  m_mapST0tST1tDist  right\
	left  m_mapPrefixChar1  middle  m_mapPrefixChar1  right\
	left  m_mapPrefixChar2  middle  m_mapPrefixChar2  right\
	left  m_mapPrefixChar3  middle  m_mapPrefixChar3  right\
	left  m_mapSuffixChar1  middle  m_mapSuffixChar1  right\
	left  m_mapSuffixChar2  middle  m_mapSuffixChar2  right\
	left  m_mapSuffixChar3  middle  m_mapSuffixChar3  right\
	left  m_mapWordLabelInDict  middle  m_mapWordLabelInDict  right\
	left  m_mapFirstCharLabelInDict  middle  m_mapFirstCharLabelInDict  right\
	left  m_mapLastCharLabelInDict  middle  m_mapLastCharLabelInDict  right\
	left  m_mapPOSST0w  middle  m_mapPOSST0w  right\
	left  m_mapPOSST0t  middle  m_mapPOSST0t  right\
	left  m_mapPOSST0wt  middle  m_mapPOSST0wt  right\
	left  m_mapPOSST0tCurWord  middle  m_mapPOSST0tCurWord  right\
	left  m_mapPOSST0wCurWord  middle  m_mapPOSST0wCurWord  right\
	left  m_mapPOSST0fcCurWord  middle  m_mapPOSST0fcCurWord  right\
	left  m_mapPOSST0lcCurWord  middle  m_mapPOSST0lcCurWord  right\
	left  m_mapPOSST0tST0LD1t  middle  m_mapPOSST0tST0LD1t  right\
	left  m_mapPOSST0wtST0LD1t  middle  m_mapPOSST0wtST0LD1t  right\
	left  m_mapPOSST0tST0RD1t  middle  m_mapPOSST0tST0RD1t  right\
	left  m_mapPOSST0wtST0RD1t  middle  m_mapPOSST0wtST0RD1t  right\
	left  m_mapST0wST0LDlset  middle  m_mapST0wST0LDlset  right\
	left  m_mapST0tST0LDlset  middle  m_mapST0tST0LDlset  right\
	left  m_mapST1wST1LDlset  middle  m_mapST1wST1LDlset  right\
	left  m_mapST1tST1LDlset  middle  m_mapST1tST1LDlset  right\
	left  m_mapST1wST1RDlset  middle  m_mapST1wST1RDlset  right\
	left  m_mapST1tST1RDlset  middle  m_mapST1tST1RDlset  right\
	left  m_mapST0tST1tST1L1t  middle  m_mapST0tST1tST1L1t  right\
	left  m_mapST0tST1tST1R1t  middle  m_mapST0tST1tST1R1t  right\
	left  m_mapST0tST1tST0L1t  middle  m_mapST0tST1tST0L1t  right\
	left  m_mapST2tST1tST0t  middle  m_mapST2tST1tST0t  right\
	left  m_mapST0tST0LD1l  middle  m_mapST0tST0LD1l  right\
	left  m_mapST1tST1LD1l  middle  m_mapST1tST1LD1l  right\
	left  m_mapST1tST1RD1l  middle  m_mapST1tST1RD1l  right\
	left  m_mapN0t  middle  m_mapN0t  right\
	left  m_mapN0wt  middle  m_mapN0wt  right\
	left  m_mapN1t  middle  m_mapN1t  right\
	left  m_mapN1wt  middle  m_mapN1wt  right\
	left  m_mapST0tN0t  middle  m_mapST0tN0t  right\
	left  m_mapST0tN0tN1t  middle  m_mapST0tN0tN1t  right\
	left  m_mapST0wN0tN1t  middle  m_mapST0wN0tN1t  right\
	left  m_mapST0tST1tN0t  middle  m_mapST0tST1tN0t  right\
	left  m_mapST1wST0tN0t  middle  m_mapST1wST0tN0t  right\
	left  m_mapPOSST1w  middle  m_mapPOSST1w  right\
	left  m_mapPOSST1t  middle  m_mapPOSST1t  right\
	left  m_mapPOSST1wt  middle  m_mapPOSST1wt  right\
	left  m_mapPOSST1tCurWord  middle  m_mapPOSST1tCurWord  right\
	left  m_mapPOSST1wCurWord  middle  m_mapPOSST1wCurWord  right\
	left  m_mapPOSST1fcCurWord  middle  m_mapPOSST1fcCurWord  right\
	left  m_mapPOSST1lcCurWord  middle  m_mapPOSST1lcCurWord  right\
	left  m_mapPOSST1tST1LD1t  middle  m_mapPOSST1tST1LD1t  right\
	left  m_mapPOSST1wtST1LD1t  middle  m_mapPOSST1wtST1LD1t  right\
	left  m_mapPOSST1tST1RD1t  middle  m_mapPOSST1tST1RD1t  right\
	left  m_mapPOSST1wtST1RD1t  middle  m_mapPOSST1wtST1RD1t  right\
	left  m_mapPOSST0wST1w  middle  m_mapPOSST0wST1w  right\
	left  m_mapPOSST0tST1t  middle  m_mapPOSST0tST1t  right\
	left  m_mapPOSST0wST1t  middle  m_mapPOSST0wST1t  right\
	left  m_mapPOSST0tST1w  middle  m_mapPOSST0tST1w  right\
	left  m_mapPOSST0wtST1t  middle  m_mapPOSST0wtST1t  right\
	left  m_mapPOSST0tST1wt  middle  m_mapPOSST0tST1wt  right\
	left  m_mapPOSST0wtST1w  middle  m_mapPOSST0wtST1w  right\
	left  m_mapPOSST0wST1wt  middle  m_mapPOSST0wST1wt  right\
	left  m_mapPOSST0wtST1wt  middle  m_mapPOSST0wtST1wt  right\
	left  m_mapST0wN0t  middle  m_mapST0wN0t  right\
	left  m_mapST0wtN0t  middle  m_mapST0wtN0t  right\
	left  m_mapST0wN0wt  middle  m_mapST0wN0wt  right\
	left  m_mapST0tN0wt  middle  m_mapST0tN0wt  right\
	left  m_mapST0wtN0wt  middle  m_mapST0wtN0wt  right\
	left  m_mapST0wN1t  middle  m_mapST0wN1t  right\
	left  m_mapST0wtN1t  middle  m_mapST0wtN1t  right\
	left  m_mapST0wN1wt  middle  m_mapST0wN1wt  right\
	left  m_mapST0tN1wt  middle  m_mapST0tN1wt  right\
	left  m_mapST0wtN1wt  middle  m_mapST0wtN1wt  right\
	left  m_mapST0tN1t  middle  m_mapST0tN1t  right\
	left  m_mapST1wN0t  middle  m_mapST1wN0t  right\
	left  m_mapST1wtN0t  middle  m_mapST1wtN0t  right\
	left  m_mapST1wN0wt  middle  m_mapST1wN0wt  right\
	left  m_mapST1tN0wt  middle  m_mapST1tN0wt  right\
	left  m_mapST1wtN0wt  middle  m_mapST1wtN0wt  right\
	left  m_mapST1tN0t  middle  m_mapST1tN0t  right\
	left  m_mapN0tN1w  middle  m_mapN0tN1w  right\
	left  m_mapN0wN1t  middle  m_mapN0wN1t  right\
	left  m_mapN0wtN1w  middle  m_mapN0wtN1w  right\
	left  m_mapN0wN1wt  middle  m_mapN0wN1wt  right\
	left  m_mapN0wtN1t  middle  m_mapN0wtN1t  right\
	left  m_mapN0tN1wt  middle  m_mapN0tN1wt  right\
	left  m_mapN0wtN1wt  middle  m_mapN0wtN1wt  right\
	left  m_mapST1tST0wN0t  middle  m_mapST1tST0wN0t  right\
	left  m_mapST0tN0wN1w  middle  m_mapST0tN0wN1w  right\
	left  m_mapST0tN0tN1w  middle  m_mapST0tN0tN1w  right\
	left  m_mapST0wN0tN1w  middle  m_mapST0wN0tN1w  right\
	left  m_mapST0tN0wN1t  middle  m_mapST0tN0wN1t  right






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


	   CTagMap	m_mapN0t;
	   CWordTagMap	m_mapN0wt;
	   CTagMap	m_mapN1t;
	   CWordTagMap	m_mapN1wt;
	   CTagTagMap	m_mapST0tN0t;
	   CTagTagTagMap	m_mapST0tN0tN1t;
	   CWordTagTagMap	m_mapST0wN0tN1t;
	   CTagTagTagMap	m_mapST0tST1tN0t;
	   CWordTagTagMap	m_mapST1wST0tN0t;

	   CWordMap	m_mapPOSST1w;
	   CTagMap	m_mapPOSST1t;
	   CWordTagMap	m_mapPOSST1wt;
	   CWordTagMap	m_mapPOSST1tCurWord;
	   CWordWordMap	m_mapPOSST1wCurWord;
	   CWordWordMap	m_mapPOSST1fcCurWord;
	   CWordWordMap	m_mapPOSST1lcCurWord;
	   CTagTagMap	m_mapPOSST1tST1LD1t;
	   CWordTagTagMap	m_mapPOSST1wtST1LD1t;
	   CTagTagMap	m_mapPOSST1tST1RD1t;
	   CWordTagTagMap	m_mapPOSST1wtST1RD1t;
	   CWordWordMap	m_mapPOSST0wST1w;
	   CTagTagMap	m_mapPOSST0tST1t;
	   CWordTagMap	m_mapPOSST0wST1t;
	   CWordTagMap	m_mapPOSST0tST1w;
	   CWordTagTagMap	m_mapPOSST0wtST1t;
	   CWordTagTagMap	m_mapPOSST0tST1wt;
	   CWordWordTagMap	m_mapPOSST0wtST1w;
	   CWordWordTagMap	m_mapPOSST0wST1wt;
	   CWordWordTagTagMap	m_mapPOSST0wtST1wt;

	   CWordTagMap	m_mapST0wN0t;
	   CWordTagTagMap	m_mapST0wtN0t;
	   CWordWordTagMap	m_mapST0wN0wt;
	   CWordTagTagMap	m_mapST0tN0wt;
	   CWordWordTagTagMap	m_mapST0wtN0wt;
	   CWordTagMap	m_mapST0wN1t;
	   CWordTagTagMap	m_mapST0wtN1t;
	   CWordWordTagMap	m_mapST0wN1wt;
	   CWordTagTagMap	m_mapST0tN1wt;
	   CWordWordTagTagMap	m_mapST0wtN1wt;
	   CTagTagMap	m_mapST0tN1t;
	   CWordTagMap	m_mapST1wN0t;
	   CWordTagTagMap	m_mapST1wtN0t;
	   CWordWordTagMap	m_mapST1wN0wt;
	   CWordTagTagMap	m_mapST1tN0wt;
	   CWordWordTagTagMap	m_mapST1wtN0wt;
	   CTagTagMap	m_mapST1tN0t;
	   CWordTagMap	m_mapN0tN1w;
	   CWordTagMap	m_mapN0wN1t;
	   CWordWordTagMap	m_mapN0wtN1w;
	   CWordWordTagMap	m_mapN0wN1wt;
	   CWordTagTagMap	m_mapN0wtN1t;
	   CWordTagTagMap	m_mapN0tN1wt;
	   CWordWordTagTagMap	m_mapN0wtN1wt;
	   CWordTagTagMap	m_mapST1tST0wN0t;
	   CWordWordTagMap	m_mapST0tN0wN1w;
	   CWordTagTagMap	m_mapST0tN0tN1w;
	   CWordWordTagMap	m_mapST0wN0tN1w;
	   CWordTagTagMap	m_mapST0tN0wN1t;









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


										   m_mapST0w("ST0w", dep_table_size),
										   m_mapST0t("ST0t", dep_table_size),
										   m_mapST0wt("ST0wt", dep_table_size),
										   m_mapST1w("ST1w", dep_table_size),
										   m_mapST1t("ST1t", dep_table_size),
										   m_mapST1wt("ST1wt", dep_table_size),
										   m_mapN0w("N0w", dep_table_size),
										   m_mapN1w("N1w", dep_table_size),
										   m_mapST0wST1w("ST0wST1w", dep_table_size),
										   m_mapST0tST1t("ST0tST1t", dep_table_size),
										   m_mapST0wST1t("ST0wST1t", dep_table_size),
										   m_mapST0tST1w("ST0tST1w", dep_table_size),
										   m_mapST0wN0w("ST0wN0w", dep_table_size),
										   m_mapST0tN0w("ST0tN0w", dep_table_size),
										   m_mapST0wLARITY("ST0wLARITY", dep_table_size),
										   m_mapST0tLARITY("ST0tLARITY", dep_table_size),
										   m_mapST1wLARITY("ST1wLARITY", dep_table_size),
										   m_mapST1tLARITY("ST1tLARITY", dep_table_size),
										   m_mapST1wRARITY("ST1wRARITY", dep_table_size),
										   m_mapST1tRARITY("ST1tRARITY", dep_table_size),
										   m_mapST0wtST1t("ST0wtST1t", dep_table_size),
										   m_mapST0tST1wt("ST0tST1wt", dep_table_size),
										   m_mapST0wtST1w("ST0wtST1w", dep_table_size),
										   m_mapST0wST1wt("ST0wST1wt", dep_table_size),
										   m_mapST0wtST1wt("ST0wtST1wt", dep_table_size),
										   m_mapST0wDist("ST0wDist", dep_table_size),
										   m_mapST1wDist("ST1wDist", dep_table_size),
										   m_mapST0tDist("ST0tDist", dep_table_size),
										   m_mapST1tDist("ST1tDist", dep_table_size),
										   m_mapST0wtDist("ST0wtDist", dep_table_size),
										   m_mapST1wtDist("ST1wtDist", dep_table_size),
										   m_mapST0wtN0w("ST0wtN0w", dep_table_size),
										   m_mapST0wN1w("ST0wN1w", dep_table_size),
										   m_mapST0tN1w("ST0tN1w", dep_table_size),
										   m_mapST0wtN1w("ST0wtN1w", dep_table_size),
										   m_mapST1wN0w("ST1wN0w", dep_table_size),
										   m_mapST1tN0w("ST1tN0w", dep_table_size),
										   m_mapST1wtN0w("ST1wtN0w", dep_table_size),
										   m_mapST1wN1w("ST1wN1w", dep_table_size),
										   m_mapST1tN1w("ST1tN1w", dep_table_size),
										   m_mapST1wtN1w("ST1wtN1w", dep_table_size),
										   m_mapN0wN1w("N0wN1w", dep_table_size),
										   m_mapST0tST1tN0w("ST0tST1tN0w", dep_table_size),
										   m_mapST0tST1wN0w("ST0tST1wN0w", dep_table_size),
										   m_mapST0wST1tN0w("ST0wST1tN0w", dep_table_size),
										   m_mapST0tST1tST1LD1t("ST0tST1tST1LD1t", dep_table_size),
										   m_mapST0wST1tST1LD1t("ST0wST1tST1LD1t", dep_table_size),
										   m_mapST0tST1tST1RD1t("ST0tST1tST1RD1t", dep_table_size),
										   m_mapST0wST1tST1RD1t("ST0wST1tST1RD1t", dep_table_size),
										   m_mapST1tST0tST0LD1t("ST1tST0tST0LD1t", dep_table_size),
										   m_mapST1wST0tST0LD1t("ST1wST0tST0LD1t", dep_table_size),
										   m_mapST0LD1w("ST0LD1w", dep_table_size),
										   m_mapST0LD1t("ST0LD1t", dep_table_size),
										   m_mapST0LD1wt("ST0LD1wt", dep_table_size),
										   m_mapST1LD1w("ST1LD1w", dep_table_size),
										   m_mapST1LD1t("ST1LD1t", dep_table_size),
										   m_mapST1LD1wt("ST1LD1wt", dep_table_size),
										   m_mapST1RD1w("ST1RD1w", dep_table_size),
										   m_mapST1RD1t("ST1RD1t", dep_table_size),
										   m_mapST1RD1wt("ST1RD1wt", dep_table_size),
										   m_mapST0tST0LD1tST0LD2t("ST0tST0LD1tST0LD2t", dep_table_size),
										   m_mapST1tST1LD1tST1LD2t("ST1tST1LD1tST1LD2t", dep_table_size),
										   m_mapST1tST1RD1tST1RD2t("ST1tST1RD1tST1RD2t", dep_table_size),
										   m_mapST1wtRARITY("ST1wtRARITY", dep_table_size),
										   m_mapST0wtLARITY("ST0wtLARITY", dep_table_size),
										   m_mapST1wtLARITY("ST1wtLARITY", dep_table_size),
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
										   m_mapST2w("ST2w", dep_table_size),
										   m_mapST2t("ST2t", dep_table_size),
										   m_mapST2wt("ST2wt", dep_table_size),
										   m_mapST0wST0LD1l("ST0LD1l", dep_table_size),
										   m_mapST1wST1LD1l("ST1LD1l", dep_table_size),
										   m_mapST1wST1RD1l("ST1RD1l", dep_table_size),
										   m_mapST0wST1wDist("ST0wST1wDist", dep_table_size),
										   m_mapST0tST1tDist("ST0tST1tDist", dep_table_size),
										   m_mapPrefixChar1("PrefixChar1", dep_table_size),
										   m_mapPrefixChar2("PrefixChar2", dep_table_size),
										   m_mapPrefixChar3("PrefixChar3", dep_table_size),
										   m_mapSuffixChar1("SuffixChar1", dep_table_size),
										   m_mapSuffixChar2("SuffixChar2", dep_table_size),
										   m_mapSuffixChar3("SuffixChar3", dep_table_size),
										   m_mapWordLabelInDict("WordLabelInDict", dep_table_size),
										   m_mapFirstCharLabelInDict("FirstCharLabelInDict", dep_table_size),
										   m_mapLastCharLabelInDict("LastCharLabelInDict", dep_table_size),
										   m_mapPOSST0w("POSST0w", dep_table_size),
										   m_mapPOSST0t("POSST0t", dep_table_size),
										   m_mapPOSST0wt("POSST0wt", dep_table_size),
										   m_mapPOSST0tCurWord("POSST0tCurWord", dep_table_size),
										   m_mapPOSST0wCurWord("POSST0wCurWord", dep_table_size),
										   m_mapPOSST0fcCurWord("POSST0fcCurWord", dep_table_size),
										   m_mapPOSST0lcCurWord("POSST0lcCurWord", dep_table_size),
										   m_mapPOSST0tST0LD1t("POSST0tST0LD1t", dep_table_size),
										   m_mapPOSST0wtST0LD1t("POSST0wtST0LD1t", dep_table_size),
										   m_mapPOSST0tST0RD1t("POSST0tST0RD1t", dep_table_size),
										   m_mapPOSST0wtST0RD1t("POSST0wtST0RD1t", dep_table_size),
										   m_mapST0wST0LDlset("ST0wST0LDlset", dep_table_size),
										   m_mapST0tST0LDlset("ST0tST0LDlset", dep_table_size),
										   m_mapST1wST1LDlset("ST1wST1LDlset", dep_table_size),
										   m_mapST1tST1LDlset("ST1tST1LDlset", dep_table_size),
										   m_mapST1wST1RDlset("ST1wST1RDlset", dep_table_size),
										   m_mapST1tST1RDlset("ST1tST1RDlset", dep_table_size),
										   m_mapST0tST1tST1L1t("ST0tST1tST1L1t", dep_table_size),
										   m_mapST0tST1tST1R1t("ST0tST1tST1R1t", dep_table_size),
										   m_mapST0tST1tST0L1t("ST0tST1tST0L1t", dep_table_size),
										   m_mapST2tST1tST0t("ST2tST1tST0t", dep_table_size),
										   m_mapST0tST0LD1l("ST0tST0LD1l", dep_table_size),
										   m_mapST1tST1LD1l("ST1tST1LD1l", dep_table_size),
										   m_mapST1tST1RD1l("ST1tST1RD1l", dep_table_size),
										   m_mapN0t("N0t", dep_table_size),
										   m_mapN0wt("N0wt", dep_table_size),
										   m_mapN1t("N1t", dep_table_size),
										   m_mapN1wt("N1wt", dep_table_size),
										   m_mapST0tN0t("ST0tN0t", dep_table_size),
										   m_mapST0tN0tN1t("ST0tN0tN1t", dep_table_size),
										   m_mapST0wN0tN1t("ST0wN0tN1t", dep_table_size),
										   m_mapST0tST1tN0t("ST0tST1tN0t", dep_table_size),
										   m_mapST1wST0tN0t("ST1wST0tN0t", dep_table_size),
										   m_mapPOSST1w("POSST1w", dep_table_size),
										   m_mapPOSST1t("POSST1t", dep_table_size),
										   m_mapPOSST1wt("POSST1wt", dep_table_size),
										   m_mapPOSST1tCurWord("POSST1tCurWord", dep_table_size),
										   m_mapPOSST1wCurWord("POSST1wCurWord", dep_table_size),
										   m_mapPOSST1fcCurWord("POSST1fcCurWord", dep_table_size),
										   m_mapPOSST1lcCurWord("POSST1lcCurWord", dep_table_size),
										   m_mapPOSST1tST1LD1t("POSST1tST1LD1t", dep_table_size),
										   m_mapPOSST1wtST1LD1t("POSST1wtST1LD1t", dep_table_size),
										   m_mapPOSST1tST1RD1t("POSST1tST1RD1t", dep_table_size),
										   m_mapPOSST1wtST1RD1t("POSST1wtST1RD1t", dep_table_size),
										   m_mapPOSST0wST1w("POSST0wST1w", dep_table_size),
										   m_mapPOSST0tST1t("POSST0tST1t", dep_table_size),
										   m_mapPOSST0wST1t("POSST0wST1t", dep_table_size),
										   m_mapPOSST0tST1w("POSST0tST1w", dep_table_size),
										   m_mapPOSST0wtST1t("POSST0wtST1t", dep_table_size),
										   m_mapPOSST0tST1wt("POSST0tST1wt", dep_table_size),
										   m_mapPOSST0wtST1w("POSST0wtST1w", dep_table_size),
										   m_mapPOSST0wST1wt("POSST0wST1wt", dep_table_size),
										   m_mapPOSST0wtST1wt("POSST0wtST1wt", dep_table_size),
										   m_mapST0wN0t("ST0wN0t", dep_table_size),
										   m_mapST0wtN0t("ST0wtN0t", dep_table_size),
										   m_mapST0wN0wt("ST0wN0wt", dep_table_size),
										   m_mapST0tN0wt("ST0tN0wt", dep_table_size),
										   m_mapST0wtN0wt("ST0wtN0wt", dep_table_size),
										   m_mapST0wN1t("ST0wN1t", dep_table_size),
										   m_mapST0wtN1t("ST0wtN1t", dep_table_size),
										   m_mapST0wN1wt("ST0wN1wt", dep_table_size),
										   m_mapST0tN1wt("ST0tN1wt", dep_table_size),
										   m_mapST0wtN1wt("ST0wtN1wt", dep_table_size),
										   m_mapST0tN1t("ST0tN1t", dep_table_size),
										   m_mapST1wN0t("ST1wN0t", dep_table_size),
										   m_mapST1wtN0t("ST1wtN0t", dep_table_size),
										   m_mapST1wN0wt("ST1wN0wt", dep_table_size),
										   m_mapST1tN0wt("ST1tN0wt", dep_table_size),
										   m_mapST1wtN0wt("ST1wtN0wt", dep_table_size),
										   m_mapST1tN0t("ST1tN0t", dep_table_size),
										   m_mapN0tN1w("N0tN1w", dep_table_size),
										   m_mapN0wN1t("N0wN1t", dep_table_size),
										   m_mapN0wtN1w("N0wtN1w", dep_table_size),
										   m_mapN0wN1wt("N0wN1wt", dep_table_size),
										   m_mapN0wtN1t("N0wtN1t", dep_table_size),
										   m_mapN0tN1wt("N0tN1wt", dep_table_size),
										   m_mapN0wtN1wt("N0wtN1wt", dep_table_size),
										   m_mapST1tST0wN0t("ST1tST0wN0t", dep_table_size),
										   m_mapST0tN0wN1w("ST0tN0wN1w", dep_table_size),
										   m_mapST0tN0tN1w("ST0tN0tN1w", dep_table_size),
										   m_mapST0wN0tN1w("ST0wN0tN1w", dep_table_size),
										   m_mapST0tN0wN1t("ST0tN0wN1t", dep_table_size)

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
