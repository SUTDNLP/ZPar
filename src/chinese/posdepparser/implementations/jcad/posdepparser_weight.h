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
\
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
\
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
	left(m_mapOneCharWord)right\
\
    left(m_mapST0rsw)right\
    left(m_mapST1rsw)right\
    left(m_mapST0cST1rsw)right\
    left(m_mapST0lswST1c)right\
    left(m_mapST0lswt)right\
    left(m_mapST0lswN0c)right\
    left(m_mapST0rswST1c)right\
    left(m_mapST1lswt)right\
    left(m_mapST0tST1rsw)right\
    left(m_mapST0lsw)right\
    left(m_mapST0rswN0c)right\
    left(m_mapST1lsw)right\
    left(m_mapST1rswt)right\
    left(m_mapST0lswST1t)right\
    left(m_mapST0tST1lsw)right\
    left(m_mapST0rswt)right\
    left(m_mapST0cST1lsw)right\
    left(m_mapST0rswST1t)right\
\
    left(m_mapST1cST0cN0c)right\
    left(m_mapST0wST1ct)right\
    left(m_mapST0wtST1c)right\
    left(m_mapST0cST1w)right\
    left(m_mapST0ctST1w)right\
    left(m_mapST0wST1c)right\
    left(m_mapST0cST1wt)right\
    left(m_mapST2cST1cST0c)right\
\
    left(m_mapST0lswtN0c)right\
    left(m_mapST0ctST1rsw)right\
    left(m_mapST0ctST1lsw)right\
    left(m_mapST0lswtST1w)right\
    left(m_mapST0wtST1rsw)right\
    left(m_mapST0rswtST1w)right\
    left(m_mapST0lswST1wt)right\
    left(m_mapST0wST1lswt)right\
    left(m_mapST0lswST1w)right\
    left(m_mapST0lswST1ct)right\
    left(m_mapST0lswtST1c)right\
    left(m_mapST0wST1rswt)right\
    left(m_mapST0wST1lsw)right\
    left(m_mapST0wST1rsw)right\
    left(m_mapST0rswST1w)right\
    left(m_mapST0wtST1lsw)right\
    left(m_mapST0cST1rswt)right\
    left(m_mapST0rswST1ct)right\
    left(m_mapST0cST1lswt)right\
    left(m_mapST0rswtN0c)right\
    left(m_mapST0rswST1wt)right\
    left(m_mapST0rswtST1c)right\
\
    left(m_mapST0cST0LD1cST0LD2c)right\
    left(m_mapST0cST1cST1LD1c)right\
    left(m_mapST1cST1LD1c)right\
    left(m_mapST1LD1ct)right\
    left(m_mapST1RD1ct)right\
    left(m_mapST1cST1RD1cST1RD2c)right\
    left(m_mapST0LD1ct)right\
    left(m_mapST1cST1LD1cST1LD2c)right\
    left(m_mapST1cST1RD1c)right\
    left(m_mapST0cST1cST1RD1c)right\
    left(m_mapST1cST0cST0LD1c)right\
    left(m_mapST0cST0LD1c)right\
    left(m_mapCurentWordInDict)right\
    left(m_mapCurentWordOutDictByTag)right\
    left(m_mapCurentWordOutDict)right\
    left(m_mapCurentWordInDictByTag)right\
    left(m_mapCurentWordInDictOutTagDict)right\
    left(m_mapCurentWordInTagDictByTag)right\
    left(m_mapCurentWordInDictOutTagDictByTag)right\
    left(m_mapCurentWordInTagDict)right\
    left(m_mapCurentSubWordOutDict)right\
    left(m_mapCurentSubWordInDictByTagLeft)right\
    left(m_mapCurentSubWordInDictLeft)right\
    left(m_mapCurentSubWordInDictRight)right\
    left(m_mapCurentSubWordOutDictByTag)right\
    left(m_mapCurentSubWordInDict)right\
    left(m_mapCurentSubWordInDictByTagRight)right\
    left(m_mapCurentSubWordInDictByTag)right\
\
    left(m_mapST0scST1sc)right\
    left(m_mapST0ec)right\
    left(m_mapST1ect)right\
    left(m_mapST1ec)right\
    left(m_mapST0sct)right\
    left(m_mapST0sc)right\
    left(m_mapST0scN0c)right\
    left(m_mapST1sct)right\
    left(m_mapST0ecN0c)right\
    left(m_mapST0ect)right\
    left(m_mapST1sc)right\
    left(m_mapST0ecST1ec)right\
\
    left(m_mapST0l0swN0c)right\
    left(m_mapST0r0swt)right\
    left(m_mapST0wST1l0sw)right\
    left(m_mapST0wST1r0sw)right\
    left(m_mapST0r0swN0c)right\
    left(m_mapST0r0swST1c)right\
    left(m_mapST0l0swST1c)right\
    left(m_mapST1l0sw)right\
    left(m_mapST0r0swST1w)right\
    left(m_mapST0cST1l0sw)right\
    left(m_mapST1r0sw)right\
    left(m_mapST0r0sw)right\
    left(m_mapST0l0sw)right\
    left(m_mapST0cST1r0sw)right\
    left(m_mapST0l0swST1w)right\
    left(m_mapST0l0swt)right\
    left(m_mapST1l0swt)right\
    left(m_mapST1r0swt)right


#define iterate_double_templates(left, middle, right)\
	left m_mapLengthByLastChar middle m_mapLengthByLastChar right\
	left m_mapFirstCharBy2Tags middle m_mapFirstCharBy2Tags right\
	left m_mapST0wLARITY middle m_mapST0wLARITY right\
	left m_mapST0tLARITY middle m_mapST0tLARITY right\
	left m_mapConsecutiveChars middle m_mapConsecutiveChars right\
	left m_mapST0wST1wDist middle m_mapST0wST1wDist right\
	left m_mapST0wN0c middle m_mapST0wN0c right\
	left m_mapST0aN0a middle m_mapST0aN0a right\
	left m_mapST1LD1t middle m_mapST1LD1t right\
	left m_mapST1LD1w middle m_mapST1LD1w right\
	left m_mapST0wtST1t middle m_mapST0wtST1t right\
	left m_mapST0wtST1w middle m_mapST0wtST1w right\
	left m_mapN3a middle m_mapN3a right\
	left m_mapST0tST1tST1R1t middle m_mapST0tST1tST1R1t right\
	left m_mapN3c middle m_mapN3c right\
	left m_mapST1tST0tST0LD1t middle m_mapST1tST0tST0LD1t right\
	left m_mapN0aN1aN2a middle m_mapN0aN1aN2a right\
	left m_mapTagByFirstChar middle m_mapTagByFirstChar right\
	left m_mapST0tST1w middle m_mapST0tST1w right\
	left m_mapST0wST1tST1RD1t middle m_mapST0wST1tST1RD1t right\
	left m_mapST0tST1t middle m_mapST0tST1t right\
	left m_mapN0cN1cN2c middle m_mapN0cN1cN2c right\
	left m_mapST0aST1a middle m_mapST0aST1a right\
	left m_mapST1tST1LD1tST1LD2t middle m_mapST1tST1LD1tST1LD2t right\
	left m_mapLastTagByWord middle m_mapLastTagByWord right\
	left m_mapTaggedCharByLastChar middle m_mapTaggedCharByLastChar right\
	left m_mapST0tST1c middle m_mapST0tST1c right\
	left m_mapST0tN0c middle m_mapST0tN0c right\
	left m_mapSeparateChars middle m_mapSeparateChars right\
	left m_mapTaggedConsecutiveChars middle m_mapTaggedConsecutiveChars right\
	left m_mapST1tDist middle m_mapST1tDist right\
	left m_mapST0tST1tST1L1t middle m_mapST0tST1tST1L1t right\
	left m_mapST1w middle m_mapST1w right\
	left m_mapTag0Tag1Tag2Size1 middle m_mapTag0Tag1Tag2Size1 right\
	left m_mapST0wtST1wt middle m_mapST0wtST1wt right\
	left m_mapST1wLARITY middle m_mapST1wLARITY right\
	left m_mapTagByFirstCharCat middle m_mapTagByFirstCharCat right\
	left m_mapST1wt middle m_mapST1wt right\
	left m_mapTag1Tag2Size1 middle m_mapTag1Tag2Size1 right\
	left m_mapST1LD1wt middle m_mapST1LD1wt right\
	left m_mapST2tST1tST0t middle m_mapST2tST1tST0t right\
	left m_mapST0LD1w middle m_mapST0LD1w right\
	left m_mapST1t middle m_mapST1t right\
	left m_mapST0LD1t middle m_mapST0LD1t right\
	left m_mapST0tST1tST1RD1t middle m_mapST0tST1tST1RD1t right\
	left m_mapST0cN0c middle m_mapST0cN0c right\
	left m_mapTagByLastWord middle m_mapTagByLastWord right\
	left m_mapST1tST1RD1tST1RD2t middle m_mapST1tST1RD1tST1RD2t right\
	left m_mapST0wt middle m_mapST0wt right\
	left m_mapLastWordFirstChar middle m_mapLastWordFirstChar right\
\
	left m_mapFirstAndLastChars middle m_mapFirstAndLastChars right\
	left m_mapCurentWordTag middle m_mapCurentWordTag right\
	left m_mapTaggedFirstCharCurrentChar middle m_mapTaggedFirstCharCurrentChar right\
	left m_mapTagByWordAndNextChar middle m_mapTagByWordAndNextChar right\
	left m_mapAPPTagByChar middle m_mapAPPTagByChar right\
	left m_mapTagByWordAndPrevChar middle m_mapTagByWordAndPrevChar right\
	left m_mapTag0Tag1Size1 middle m_mapTag0Tag1Size1 right\
	left m_mapST0tST1tST0L1t middle m_mapST0tST1tST0L1t right\
	left m_mapLastTagByTag middle m_mapLastTagByTag right\
	left m_mapST0wDist middle m_mapST0wDist right\
	left m_mapN0cN1c middle m_mapN0cN1c right\
	left m_mapFirstCharLastWordByWord middle m_mapFirstCharLastWordByWord right\
	left m_mapST0t middle m_mapST0t right\
	left m_mapST1tLARITY middle m_mapST1tLARITY right\
	left m_mapCharByLastChar middle m_mapCharByLastChar right\
	left m_mapLastWordByWord middle m_mapLastWordByWord right\
	left m_mapLengthByFirstChar middle m_mapLengthByFirstChar right\
	left m_mapST0tST1tN0c middle m_mapST0tST1tN0c right\
	left m_mapN0aN1a middle m_mapN0aN1a right\
	left m_mapST0wST1tST1LD1t middle m_mapST0wST1tST1LD1t right\
	left m_mapST1c middle m_mapST1c right\
	left m_mapST1a middle m_mapST1a right\
	left m_mapLastWordByLastChar middle m_mapLastWordByLastChar right\
	left m_mapST0tST1tDist middle m_mapST0tST1tDist right\
	left m_mapST0tST0LD1tST0LD2t middle m_mapST0tST0LD1tST0LD2t right\
	left m_mapST0w middle m_mapST0w right\
	left m_mapST1ct middle m_mapST1ct right\
	left m_mapST0wST1tN0c middle m_mapST0wST1tN0c right\
	left m_mapST0LD1wt middle m_mapST0LD1wt right\
	left m_mapTaggedSeparateChars middle m_mapTaggedSeparateChars right\
	left m_mapST0tST1wt middle m_mapST0tST1wt right\
	left m_mapCurentWord middle m_mapCurentWord right\
	left m_mapTaggedCharByFirstChar middle m_mapTaggedCharByFirstChar right\
	left m_mapST1wDist middle m_mapST1wDist right\
	left m_mapST0tST1wN0c middle m_mapST0tST1wN0c right\
	left m_mapST1wST0tST0LD1t middle m_mapST1wST0tST0LD1t right\
	left m_mapST0c middle m_mapST0c right\
	left m_mapLastTwoTagsByTag middle m_mapLastTwoTagsByTag right\
	left m_mapST1RD1w middle m_mapST1RD1w right\
	left m_mapST0a middle m_mapST0a right\
	left m_mapN0c middle m_mapN0c right\
	left m_mapN0a middle m_mapN0a right\
	left m_mapST1RD1t middle m_mapST1RD1t right\
	left m_mapTagOfOneCharWord middle m_mapTagOfOneCharWord right\
	left m_mapWordTagTag middle m_mapWordTagTag right\
	left m_mapTagByLastCharCat middle m_mapTagByLastCharCat right\
	left m_mapST0cST1c middle m_mapST0cST1c right\
	left m_mapST0wST1wt middle m_mapST0wST1wt right\
	left m_mapST1tRARITY middle m_mapST1tRARITY right\
	left m_mapCurrentWordLastChar middle m_mapCurrentWordLastChar right\
	left m_mapN1a middle m_mapN1a right\
\
	left m_mapST1wRARITY middle m_mapST1wRARITY right\
	left m_mapN1c middle m_mapN1c right\
	left m_mapST0ct middle m_mapST0ct right\
	left m_mapST0tDist middle m_mapST0tDist right\
	left m_mapTagByLastChar middle m_mapTagByLastChar right\
	left m_mapST0tST1tST1LD1t middle m_mapST0tST1tST1LD1t right\
	left m_mapFirstCharCurrentChar middle m_mapFirstCharCurrentChar right\
	left m_mapFirstCharBy3Tags middle m_mapFirstCharBy3Tags right\
	left m_mapST0wST1w middle m_mapST0wST1w right\
	left m_mapST0wtN0c middle m_mapST0wtN0c right\
	left m_mapST0wST1t middle m_mapST0wST1t right\
	left m_mapST1RD1wt middle m_mapST1RD1wt right\
	left m_mapTagWordTag middle m_mapTagWordTag right\
	left m_mapST0cST1t middle m_mapST0cST1t right\
	left m_mapN2c middle m_mapN2c right\
	left m_mapN2a middle m_mapN2a right\
	left m_mapOneCharWord middle m_mapOneCharWord right\
\
    left m_mapST0rsw middle m_mapST0rsw right\
    left m_mapST1rsw middle m_mapST1rsw right\
    left m_mapST0cST1rsw middle m_mapST0cST1rsw right\
    left m_mapST0lswST1c middle m_mapST0lswST1c right\
    left m_mapST0lswt middle m_mapST0lswt right\
    left m_mapST0lswN0c middle m_mapST0lswN0c right\
    left m_mapST0rswST1c middle m_mapST0rswST1c right\
    left m_mapST1lswt middle m_mapST1lswt right\
    left m_mapST0tST1rsw middle m_mapST0tST1rsw right\
    left m_mapST0lsw middle m_mapST0lsw right\
    left m_mapST0rswN0c middle m_mapST0rswN0c right\
    left m_mapST1lsw middle m_mapST1lsw right\
    left m_mapST1rswt middle m_mapST1rswt right\
    left m_mapST0lswST1t middle m_mapST0lswST1t right\
    left m_mapST0tST1lsw middle m_mapST0tST1lsw right\
    left m_mapST0rswt middle m_mapST0rswt right\
    left m_mapST0cST1lsw middle m_mapST0cST1lsw right\
    left m_mapST0rswST1t middle m_mapST0rswST1t right\
\
    left m_mapST1cST0cN0c middle m_mapST1cST0cN0c right\
    left m_mapST0wST1ct middle m_mapST0wST1ct right\
    left m_mapST0wtST1c middle m_mapST0wtST1c right\
    left m_mapST0cST1w middle m_mapST0cST1w right\
    left m_mapST0ctST1w middle m_mapST0ctST1w right\
    left m_mapST0wST1c middle m_mapST0wST1c right\
    left m_mapST0cST1wt middle m_mapST0cST1wt right\
    left m_mapST2cST1cST0c middle m_mapST2cST1cST0c right\
\
    left m_mapST0lswtN0c middle m_mapST0lswtN0c right\
    left m_mapST0ctST1rsw middle m_mapST0ctST1rsw right\
    left m_mapST0ctST1lsw middle m_mapST0ctST1lsw right\
    left m_mapST0lswtST1w middle m_mapST0lswtST1w right\
    left m_mapST0wtST1rsw middle m_mapST0wtST1rsw right\
    left m_mapST0rswtST1w middle m_mapST0rswtST1w right\
    left m_mapST0lswST1wt middle m_mapST0lswST1wt right\
    left m_mapST0wST1lswt middle m_mapST0wST1lswt right\
    left m_mapST0lswST1w middle m_mapST0lswST1w right\
    left m_mapST0lswST1ct middle m_mapST0lswST1ct right\
    left m_mapST0lswtST1c middle m_mapST0lswtST1c right\
    left m_mapST0wST1rswt middle m_mapST0wST1rswt right\
    left m_mapST0wST1lsw middle m_mapST0wST1lsw right\
    left m_mapST0wST1rsw middle m_mapST0wST1rsw right\
    left m_mapST0rswST1w middle m_mapST0rswST1w right\
    left m_mapST0wtST1lsw middle m_mapST0wtST1lsw right\
    left m_mapST0cST1rswt middle m_mapST0cST1rswt right\
    left m_mapST0rswST1ct middle m_mapST0rswST1ct right\
    left m_mapST0cST1lswt middle m_mapST0cST1lswt right\
    left m_mapST0rswtN0c middle m_mapST0rswtN0c right\
    left m_mapST0rswST1wt middle m_mapST0rswST1wt right\
    left m_mapST0rswtST1c middle m_mapST0rswtST1c right\
\
    left m_mapST0cST0LD1cST0LD2c middle m_mapST0cST0LD1cST0LD2c right\
    left m_mapST0cST1cST1LD1c middle m_mapST0cST1cST1LD1c right\
    left m_mapST1cST1LD1c middle m_mapST1cST1LD1c right\
    left m_mapST1LD1ct middle m_mapST1LD1ct right\
    left m_mapST1RD1ct middle m_mapST1RD1ct right\
    left m_mapST1cST1RD1cST1RD2c middle m_mapST1cST1RD1cST1RD2c right\
    left m_mapST0LD1ct middle m_mapST0LD1ct right\
    left m_mapST1cST1LD1cST1LD2c middle m_mapST1cST1LD1cST1LD2c right\
    left m_mapST1cST1RD1c middle m_mapST1cST1RD1c right\
    left m_mapST0cST1cST1RD1c middle m_mapST0cST1cST1RD1c right\
    left m_mapST1cST0cST0LD1c middle m_mapST1cST0cST0LD1c right\
    left m_mapST0cST0LD1c middle m_mapST0cST0LD1c right\
    left m_mapCurentWordInDict middle m_mapCurentWordInDict right\
    left m_mapCurentWordOutDictByTag middle m_mapCurentWordOutDictByTag right\
    left m_mapCurentWordOutDict middle m_mapCurentWordOutDict right\
    left m_mapCurentWordInDictByTag middle m_mapCurentWordInDictByTag right\
    left m_mapCurentWordInDictOutTagDict middle m_mapCurentWordInDictOutTagDict right\
    left m_mapCurentWordInTagDictByTag middle m_mapCurentWordInTagDictByTag right\
    left m_mapCurentWordInDictOutTagDictByTag middle m_mapCurentWordInDictOutTagDictByTag right\
    left m_mapCurentWordInTagDict middle m_mapCurentWordInTagDict right\
    left m_mapCurentSubWordOutDict middle m_mapCurentSubWordOutDict right\
    left m_mapCurentSubWordInDictByTagLeft middle m_mapCurentSubWordInDictByTagLeft right\
    left m_mapCurentSubWordInDictLeft middle m_mapCurentSubWordInDictLeft right\
    left m_mapCurentSubWordInDictRight middle m_mapCurentSubWordInDictRight right\
    left m_mapCurentSubWordOutDictByTag middle m_mapCurentSubWordOutDictByTag right\
    left m_mapCurentSubWordInDict middle m_mapCurentSubWordInDict right\
    left m_mapCurentSubWordInDictByTagRight middle m_mapCurentSubWordInDictByTagRight right\
    left m_mapCurentSubWordInDictByTag middle m_mapCurentSubWordInDictByTag right\
\
    left m_mapST0scST1sc middle m_mapST0scST1sc right\
    left m_mapST0ec middle m_mapST0ec right\
    left m_mapST1ect middle m_mapST1ect right\
    left m_mapST1ec middle m_mapST1ec right\
    left m_mapST0sct middle m_mapST0sct right\
    left m_mapST0sc middle m_mapST0sc right\
    left m_mapST0scN0c middle m_mapST0scN0c right\
    left m_mapST1sct middle m_mapST1sct right\
    left m_mapST0ecN0c middle m_mapST0ecN0c right\
    left m_mapST0ect middle m_mapST0ect right\
    left m_mapST1sc middle m_mapST1sc right\
    left m_mapST0ecST1ec middle m_mapST0ecST1ec right\
\
    left m_mapST0l0swN0c middle m_mapST0l0swN0c right\
    left m_mapST0r0swt middle m_mapST0r0swt right\
    left m_mapST0wST1l0sw middle m_mapST0wST1l0sw right\
    left m_mapST0wST1r0sw middle m_mapST0wST1r0sw right\
    left m_mapST0r0swN0c middle m_mapST0r0swN0c right\
    left m_mapST0r0swST1c middle m_mapST0r0swST1c right\
    left m_mapST0l0swST1c middle m_mapST0l0swST1c right\
    left m_mapST1l0sw middle m_mapST1l0sw right\
    left m_mapST0r0swST1w middle m_mapST0r0swST1w right\
    left m_mapST0cST1l0sw middle m_mapST0cST1l0sw right\
    left m_mapST1r0sw middle m_mapST1r0sw right\
    left m_mapST0r0sw middle m_mapST0r0sw right\
    left m_mapST0l0sw middle m_mapST0l0sw right\
    left m_mapST0cST1r0sw middle m_mapST0cST1r0sw right\
    left m_mapST0l0swST1w middle m_mapST0l0swST1w right\
    left m_mapST0l0swt middle m_mapST0l0swt right\
    left m_mapST1l0swt middle m_mapST1l0swt right\
    left m_mapST1r0swt middle m_mapST1r0swt right




namespace TARGET_LANGUAGE {

namespace posdepparser {

const static unsigned DEP_TABLE_SIZE = (1<<17);//1000121;

//
// TYPE DEFINITIONS
//
typedef CPackedScoreMap<CWord, SCORE_TYPE, action::MAX> CWordMap;
typedef CPackedScoreMap<CTag, SCORE_TYPE, action::MAX> CTagMap;
typedef CPackedScoreMap<unsigned long long, SCORE_TYPE, action::MAX> CUlongMap;
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
typedef CPackedScoreMap<CTuple2<CWord, unsigned long long>, SCORE_TYPE, action::MAX> CWordUlongMap;
typedef CPackedScoreMap<CTuple2<CTag, unsigned long long>, SCORE_TYPE, action::MAX> CTagUlongMap;
typedef CPackedScoreMap<CTuple3<CTag, CTag, unsigned long long>, SCORE_TYPE, action::MAX> CTagTagUlongMap;
typedef CPackedScoreMap<CTuple3<CWord, CWord, unsigned long long>, SCORE_TYPE, action::MAX> CWordWordUlongMap;
typedef CPackedScoreMap<CTuple3<CWord, CTag, unsigned long long>, SCORE_TYPE, action::MAX> CWordTagUlongMap;
typedef CPackedScoreMap<CTuple3<unsigned long long, unsigned long long, unsigned long long>, SCORE_TYPE, action::MAX> CUlongUlongUlongMap;
typedef CPackedScoreMap<CTuple2<unsigned long long, unsigned long long>, SCORE_TYPE, action::MAX> CUlongUlongMap;



typedef CHashMap<CTuple2<CWord, CWord>, unsigned long> CWordWordToIntMap;
typedef CHashMap<CWord, unsigned long> CWordToIntMap;
typedef CHashMap<unsigned long, unsigned long> CIntToIntMap;

/*===============================================================
 *
 * CWeight - the definition of weights, in feature
 *
 *==============================================================*/

class CWeight : public CWeightBase {

public:
		CWordUlongMap    m_mapLengthByLastChar;
		CWordTagMap    m_mapFirstCharBy2Tags;
		CWordUlongMap    m_mapST0wLARITY;
		CTagUlongMap    m_mapST0tLARITY;
		CWordWordMap    m_mapConsecutiveChars;
		CWordWordUlongMap    m_mapST0wST1wDist;
		CWordWordMap    m_mapST0wN0c;
		CUlongUlongMap    m_mapST0aN0a;
		CTagMap    m_mapST1LD1t;
		CWordMap    m_mapST1LD1w;
		CWordTagTagMap    m_mapST0wtST1t;
		CWordWordTagMap    m_mapST0wtST1w;
		CUlongMap    m_mapN3a;
		CTagTagTagMap    m_mapST0tST1tST1R1t;
		CWordMap    m_mapN3c;
		CTagTagTagMap    m_mapST1tST0tST0LD1t;
		CUlongUlongUlongMap    m_mapN0aN1aN2a;
		CWordMap    m_mapTagByFirstChar;
		CWordTagMap    m_mapST0tST1w;
		CWordTagTagMap    m_mapST0wST1tST1RD1t;
		CTagTagMap    m_mapST0tST1t;
		CWordWordWordMap    m_mapN0cN1cN2c;
		CUlongUlongMap    m_mapST0aST1a;
		CTagTagTagMap    m_mapST1tST1LD1tST1LD2t;
		CWordTagMap    m_mapLastTagByWord;
		CWordWordTagMap    m_mapTaggedCharByLastChar;
		CWordTagMap    m_mapST0tST1c;
		CWordTagMap    m_mapST0tN0c;
		CWordWordMap    m_mapSeparateChars;
		CWordWordTagMap    m_mapTaggedConsecutiveChars;
		CTagUlongMap    m_mapST1tDist;
		CTagTagTagMap    m_mapST0tST1tST1L1t;
		CWordMap    m_mapST1w;
		CTagTagUlongMap    m_mapTag0Tag1Tag2Size1;
		CWordWordTagTagMap    m_mapST0wtST1wt;
		CWordUlongMap    m_mapST1wLARITY;
		CUlongMap    m_mapTagByFirstCharCat;
		CWordTagMap    m_mapST1wt;
		CTagTagUlongMap    m_mapTag1Tag2Size1;
		CWordTagMap    m_mapST1LD1wt;
		CTagTagTagMap    m_mapST2tST1tST0t;
		CWordMap    m_mapST0LD1w;
		CTagMap    m_mapST1t;
		CTagMap    m_mapST0LD1t;
		CTagTagTagMap    m_mapST0tST1tST1RD1t;
		CWordWordMap    m_mapST0cN0c;
		CWordMap    m_mapTagByLastWord;
		CTagTagTagMap    m_mapST1tST1RD1tST1RD2t;
		CWordTagMap    m_mapST0wt;
		CWordWordMap    m_mapLastWordFirstChar;
		CWordWordMap    m_mapFirstAndLastChars;
		CWordTagMap    m_mapCurentWordTag;
		CWordWordTagMap    m_mapTaggedFirstCharCurrentChar;
		CWordWordTagMap    m_mapTagByWordAndNextChar;
		CWordTagMap    m_mapAPPTagByChar;
		CWordWordTagMap    m_mapTagByWordAndPrevChar;
		CTagUlongMap    m_mapTag0Tag1Size1;
		CTagTagTagMap    m_mapST0tST1tST0L1t;
		CTagMap    m_mapLastTagByTag;
		CWordUlongMap    m_mapST0wDist;
		CWordWordMap    m_mapN0cN1c;
		CWordWordMap    m_mapFirstCharLastWordByWord;
		CTagMap    m_mapST0t;
		CTagUlongMap    m_mapST1tLARITY;
		CWordWordMap    m_mapCharByLastChar;
		CWordWordMap    m_mapLastWordByWord;
		CWordUlongMap    m_mapLengthByFirstChar;
		CWordTagTagMap    m_mapST0tST1tN0c;
		CUlongUlongMap    m_mapN0aN1a;
		CWordTagTagMap    m_mapST0wST1tST1LD1t;
		CWordMap    m_mapST1c;
		CUlongMap    m_mapST1a;
		CWordWordMap    m_mapLastWordByLastChar;
		CTagTagUlongMap    m_mapST0tST1tDist;
		CTagTagTagMap    m_mapST0tST0LD1tST0LD2t;
		CWordMap    m_mapST0w;
		CWordTagMap    m_mapST1ct;
		CWordWordTagMap    m_mapST0wST1tN0c;
		CWordTagMap    m_mapST0LD1wt;
		CWordWordTagMap    m_mapTaggedSeparateChars;
		CWordTagTagMap    m_mapST0tST1wt;
		CWordMap    m_mapCurentWord;
		CWordWordTagMap    m_mapTaggedCharByFirstChar;
		CWordUlongMap    m_mapST1wDist;
		CWordWordTagMap    m_mapST0tST1wN0c;
		CWordTagTagMap    m_mapST1wST0tST0LD1t;
		CWordMap    m_mapST0c;
		CTagTagMap    m_mapLastTwoTagsByTag;
		CWordMap    m_mapST1RD1w;
		CUlongMap    m_mapST0a;
		CWordMap    m_mapN0c;
		CUlongMap    m_mapN0a;
		CTagMap    m_mapST1RD1t;
		CWordWordWordMap    m_mapTagOfOneCharWord;
		CWordTagMap    m_mapWordTagTag;
		CTagUlongMap    m_mapTagByLastCharCat;
		CWordWordMap    m_mapST0cST1c;
		CWordWordTagMap    m_mapST0wST1wt;
		CTagUlongMap    m_mapST1tRARITY;
		CWordWordMap    m_mapCurrentWordLastChar;
		CUlongMap    m_mapN1a;
		CWordUlongMap    m_mapST1wRARITY;
		CWordMap    m_mapN1c;
		CWordTagMap    m_mapST0ct;
		CTagUlongMap    m_mapST0tDist;
		CWordTagMap    m_mapTagByLastChar;
		CTagTagTagMap    m_mapST0tST1tST1LD1t;
		CWordWordMap    m_mapFirstCharCurrentChar;
		CWordTagTagMap    m_mapFirstCharBy3Tags;
		CWordWordMap    m_mapST0wST1w;
		CWordWordTagMap    m_mapST0wtN0c;
		CWordTagMap    m_mapST0wST1t;
		CWordTagMap    m_mapST1RD1wt;
		CWordTagMap    m_mapTagWordTag;
		CWordTagMap    m_mapST0cST1t;
		CWordMap    m_mapN2c;
		CUlongMap    m_mapN2a;
		CWordMap    m_mapOneCharWord;

		CWordMap    m_mapST0rsw;
		CWordMap    m_mapST1rsw;
		CWordWordMap    m_mapST0cST1rsw;
		CWordWordMap    m_mapST0lswST1c;
		CWordTagMap    m_mapST0lswt;
		CWordWordMap    m_mapST0lswN0c;
		CWordWordMap    m_mapST0rswST1c;
		CWordTagMap    m_mapST1lswt;
		CWordTagMap    m_mapST0tST1rsw;
		CWordMap    m_mapST0lsw;
		CWordWordMap    m_mapST0rswN0c;
		CWordMap    m_mapST1lsw;
		CWordTagMap    m_mapST1rswt;
		CWordTagMap    m_mapST0lswST1t;
		CWordTagMap    m_mapST0tST1lsw;
		CWordTagMap    m_mapST0rswt;
		CWordWordMap    m_mapST0cST1lsw;
		CWordTagMap    m_mapST0rswST1t;

		CWordWordWordMap    m_mapST1cST0cN0c;
		CWordWordTagMap    m_mapST0wST1ct;
		CWordWordTagMap    m_mapST0wtST1c;
		CWordWordMap    m_mapST0cST1w;
		CWordWordTagMap    m_mapST0ctST1w;
		CWordWordMap    m_mapST0wST1c;
		CWordWordTagMap    m_mapST0cST1wt;
		CWordWordWordMap    m_mapST2cST1cST0c;


		CWordWordTagMap    m_mapST0lswtN0c;
		CWordWordTagMap    m_mapST0ctST1rsw;
		CWordWordTagMap    m_mapST0ctST1lsw;
		CWordWordTagMap    m_mapST0lswtST1w;
		CWordWordTagMap    m_mapST0wtST1rsw;
		CWordWordTagMap    m_mapST0rswtST1w;
		CWordWordTagMap    m_mapST0lswST1wt;
		CWordWordTagMap    m_mapST0wST1lswt;
		CWordWordMap    m_mapST0lswST1w;
		CWordWordTagMap    m_mapST0lswST1ct;
		CWordWordTagMap    m_mapST0lswtST1c;
		CWordWordTagMap    m_mapST0wST1rswt;
		CWordWordMap    m_mapST0wST1lsw;
		CWordWordMap    m_mapST0wST1rsw;
		CWordWordMap    m_mapST0rswST1w;
		CWordWordTagMap    m_mapST0wtST1lsw;
		CWordWordTagMap    m_mapST0cST1rswt;
		CWordWordTagMap    m_mapST0rswST1ct;
		CWordWordTagMap    m_mapST0cST1lswt;
		CWordWordTagMap    m_mapST0rswtN0c;
		CWordWordTagMap    m_mapST0rswST1wt;
		CWordWordTagMap    m_mapST0rswtST1c;


		CWordWordWordMap    m_mapST0cST0LD1cST0LD2c;
		CWordWordWordMap    m_mapST0cST1cST1LD1c;
		CWordWordMap    m_mapST1cST1LD1c;
		CWordTagMap    m_mapST1LD1ct;
		CWordTagMap    m_mapST1RD1ct;
		CWordWordWordMap    m_mapST1cST1RD1cST1RD2c;
		CWordTagMap    m_mapST0LD1ct;
		CWordWordWordMap    m_mapST1cST1LD1cST1LD2c;
		CWordWordMap    m_mapST1cST1RD1c;
		CWordWordWordMap    m_mapST0cST1cST1RD1c;
		CWordWordWordMap    m_mapST1cST0cST0LD1c;
		CWordWordMap    m_mapST0cST0LD1c;

		CUlongMap    m_mapCurentWordInDict;
		CTagUlongMap    m_mapCurentWordOutDictByTag;
		CUlongMap    m_mapCurentWordOutDict;
		CTagUlongMap    m_mapCurentWordInDictByTag;
		CUlongMap    m_mapCurentWordInDictOutTagDict;
		CTagUlongMap    m_mapCurentWordInTagDictByTag;
		CTagUlongMap    m_mapCurentWordInDictOutTagDictByTag;
		CUlongMap    m_mapCurentWordInTagDict;
		CUlongMap    m_mapCurentSubWordOutDict;
		CTagUlongMap    m_mapCurentSubWordInDictByTagLeft;
		CUlongMap    m_mapCurentSubWordInDictLeft;
		CUlongMap    m_mapCurentSubWordInDictRight;
		CTagUlongMap    m_mapCurentSubWordOutDictByTag;
		CUlongMap    m_mapCurentSubWordInDict;
		CTagUlongMap    m_mapCurentSubWordInDictByTagRight;
		CTagUlongMap    m_mapCurentSubWordInDictByTag;

		CWordWordMap    m_mapST0scST1sc;
		CWordMap    m_mapST0ec;
		CWordTagMap    m_mapST1ect;
		CWordMap    m_mapST1ec;
		CWordTagMap    m_mapST0sct;
		CWordMap    m_mapST0sc;
		CWordWordMap    m_mapST0scN0c;
		CWordTagMap    m_mapST1sct;
		CWordWordMap    m_mapST0ecN0c;
		CWordTagMap    m_mapST0ect;
		CWordMap    m_mapST1sc;
		CWordWordMap    m_mapST0ecST1ec;


		CWordWordMap    m_mapST0l0swN0c;
		CWordTagMap    m_mapST0r0swt;
		CWordWordMap    m_mapST0wST1l0sw;
		CWordWordMap    m_mapST0wST1r0sw;
		CWordWordMap    m_mapST0r0swN0c;
		CWordWordMap    m_mapST0r0swST1c;
		CWordWordMap    m_mapST0l0swST1c;
		CWordMap    m_mapST1l0sw;
		CWordWordMap    m_mapST0r0swST1w;
		CWordWordMap    m_mapST0cST1l0sw;
		CWordMap    m_mapST1r0sw;
		CWordMap    m_mapST0r0sw;
		CWordMap    m_mapST0l0sw;
		CWordWordMap    m_mapST0cST1r0sw;
		CWordWordMap    m_mapST0l0swST1w;
		CWordTagMap    m_mapST0l0swt;
		CWordTagMap    m_mapST1l0swt;
		CWordTagMap    m_mapST1r0swt;







	   unsigned long m_nMaxWordFrequency;
	   unsigned long m_nMaxSubWordFrequency;
	   unsigned long m_nMaxCharFrequency;
	   CWordToIntMap m_mapWordFrequency;
	   CWordToIntMap m_mapCharFrequency;
	   CWordToIntMap m_mapSubWordFrequency;

	   CWordWordToIntMap m_mapSubWordHeadWordDictionary;
	   CTagDict<CWord, CTag> m_mapWordTagDictionary;
	   CTagDict<CWord, CTag> m_mapCharTagDictionary;
	   CTagDict<CWord, CTag> m_mapSubWordTagDictionary;






public:

   CWeight(const std::string &sPath, bool bTrain, int dep_table_size) : CWeightBase(sPath, bTrain) ,

										   m_nMaxWordFrequency(0) ,
										   m_nMaxCharFrequency(0) ,
										   m_nMaxSubWordFrequency(0) ,
										   m_mapWordFrequency(65537),
										   m_mapCharFrequency(65537),
										   m_mapSubWordFrequency(65537),
										   m_mapSubWordHeadWordDictionary(65537),
										   m_mapWordTagDictionary(CTag::COUNT),
										   m_mapCharTagDictionary(CTag::COUNT),
										   m_mapSubWordTagDictionary(CTag::COUNT),



										   m_mapLengthByLastChar("LengthByLastChar", dep_table_size),
										   m_mapFirstCharBy2Tags("FirstCharBy2Tags", dep_table_size),
										   m_mapST0wLARITY("ST0wLARITY", dep_table_size),
										   m_mapST0tLARITY("ST0tLARITY", dep_table_size),
										   m_mapConsecutiveChars("ConsecutiveChars", dep_table_size),
										   m_mapST0wST1wDist("ST0wST1wDist", dep_table_size),
										   m_mapST0wN0c("ST0wN0c", dep_table_size),
										   m_mapST0aN0a("ST0aN0a", dep_table_size),
										   m_mapST1LD1t("ST1LD1t", dep_table_size),
										   m_mapST1LD1w("ST1LD1w", dep_table_size),
										   m_mapST0wtST1t("ST0wtST1t", dep_table_size),
										   m_mapST0wtST1w("ST0wtST1w", dep_table_size),
										   m_mapN3a("N3a", dep_table_size),
										   m_mapST0tST1tST1R1t("ST0tST1tST1R1t", dep_table_size),
										   m_mapN3c("N3c", dep_table_size),
										   m_mapST1tST0tST0LD1t("ST1tST0tST0LD1t", dep_table_size),
										   m_mapN0aN1aN2a("N0aN1aN2a", dep_table_size),
										   m_mapTagByFirstChar("TagByFirstChar", dep_table_size),
										   m_mapST0tST1w("ST0tST1w", dep_table_size),
										   m_mapST0wST1tST1RD1t("ST0wST1tST1RD1t", dep_table_size),
										   m_mapST0tST1t("ST0tST1t", dep_table_size),
										   m_mapN0cN1cN2c("N0cN1cN2c", dep_table_size),
										   m_mapST0aST1a("ST0aST1a", dep_table_size),
										   m_mapST1tST1LD1tST1LD2t("ST1tST1LD1tST1LD2t", dep_table_size),
										   m_mapLastTagByWord("LastTagByWord", dep_table_size),
										   m_mapTaggedCharByLastChar("TaggedCharByLastChar", dep_table_size),
										   m_mapST0tST1c("ST0tST1c", dep_table_size),
										   m_mapST0tN0c("ST0tN0c", dep_table_size),
										   m_mapSeparateChars("SeparateChars", dep_table_size),
										   m_mapTaggedConsecutiveChars("TaggedConsecutiveChars", dep_table_size),
										   m_mapST1tDist("ST1tDist", dep_table_size),
										   m_mapST0tST1tST1L1t("ST0tST1tST1L1t", dep_table_size),
										   m_mapST1w("ST1w", dep_table_size),
										   m_mapTag0Tag1Tag2Size1("Tag0Tag1Tag2Size1", dep_table_size),
										   m_mapST0wtST1wt("ST0wtST1wt", dep_table_size),
										   m_mapST1wLARITY("ST1wLARITY", dep_table_size),
										   m_mapTagByFirstCharCat("TagByFirstCharCat", dep_table_size),
										   m_mapST1wt("ST1wt", dep_table_size),
										   m_mapTag1Tag2Size1("Tag1Tag2Size1", dep_table_size),
										   m_mapST1LD1wt("ST1LD1wt", dep_table_size),
										   m_mapST2tST1tST0t("ST2tST1tST0t", dep_table_size),
										   m_mapST0LD1w("ST0LD1w", dep_table_size),
										   m_mapST1t("ST1t", dep_table_size),
										   m_mapST0LD1t("ST0LD1t", dep_table_size),
										   m_mapST0tST1tST1RD1t("ST0tST1tST1RD1t", dep_table_size),
										   m_mapST0cN0c("ST0cN0c", dep_table_size),
										   m_mapTagByLastWord("TagByLastWord", dep_table_size),
										   m_mapST1tST1RD1tST1RD2t("ST1tST1RD1tST1RD2t", dep_table_size),
										   m_mapST0wt("ST0wt", dep_table_size),
										   m_mapLastWordFirstChar("LastWordFirstChar", dep_table_size),
										   m_mapFirstAndLastChars("FirstAndLastChars", dep_table_size),
										   m_mapCurentWordTag("CurentWordTag", dep_table_size),
										   m_mapTaggedFirstCharCurrentChar("TaggedFirstCharCurrentChar", dep_table_size),
										   m_mapTagByWordAndNextChar("TagByWordAndNextChar", dep_table_size),
										   m_mapAPPTagByChar("APPTagByChar", dep_table_size),
										   m_mapTagByWordAndPrevChar("TagByWordAndPrevChar", dep_table_size),
										   m_mapTag0Tag1Size1("Tag0Tag1Size1", dep_table_size),
										   m_mapST0tST1tST0L1t("ST0tST1tST0L1t", dep_table_size),
										   m_mapLastTagByTag("LastTagByTag", dep_table_size),
										   m_mapST0wDist("ST0wDist", dep_table_size),
										   m_mapN0cN1c("N0cN1c", dep_table_size),
										   m_mapFirstCharLastWordByWord("FirstCharLastWordByWord", dep_table_size),
										   m_mapST0t("ST0t", dep_table_size),
										   m_mapST1tLARITY("ST1tLARITY", dep_table_size),
										   m_mapCharByLastChar("CharByLastChar", dep_table_size),
										   m_mapLastWordByWord("LastWordByWord", dep_table_size),
										   m_mapLengthByFirstChar("LengthByFirstChar", dep_table_size),
										   m_mapST0tST1tN0c("ST0tST1tN0c", dep_table_size),
										   m_mapN0aN1a("N0aN1a", dep_table_size),
										   m_mapST0wST1tST1LD1t("ST0wST1tST1LD1t", dep_table_size),
										   m_mapST1c("ST1c", dep_table_size),
										   m_mapST1a("ST1a", dep_table_size),
										   m_mapLastWordByLastChar("LastWordByLastChar", dep_table_size),
										   m_mapST0tST1tDist("ST0tST1tDist", dep_table_size),
										   m_mapST0tST0LD1tST0LD2t("ST0tST0LD1tST0LD2t", dep_table_size),
										   m_mapST0w("ST0w", dep_table_size),
										   m_mapST1ct("ST1ct", dep_table_size),
										   m_mapST0wST1tN0c("ST0wST1tN0c", dep_table_size),
										   m_mapST0LD1wt("ST0LD1wt", dep_table_size),
										   m_mapTaggedSeparateChars("TaggedSeparateChars", dep_table_size),
										   m_mapST0tST1wt("ST0tST1wt", dep_table_size),
										   m_mapCurentWord("CurentWord", dep_table_size),
										   m_mapTaggedCharByFirstChar("TaggedCharByFirstChar", dep_table_size),
										   m_mapST1wDist("ST1wDist", dep_table_size),
										   m_mapST0tST1wN0c("ST0tST1wN0c", dep_table_size),
										   m_mapST1wST0tST0LD1t("ST1wST0tST0LD1t", dep_table_size),
										   m_mapST0c("ST0c", dep_table_size),
										   m_mapLastTwoTagsByTag("LastTwoTagsByTag", dep_table_size),
										   m_mapST1RD1w("ST1RD1w", dep_table_size),
										   m_mapST0a("ST0a", dep_table_size),
										   m_mapN0c("N0c", dep_table_size),
										   m_mapN0a("N0a", dep_table_size),
										   m_mapST1RD1t("ST1RD1t", dep_table_size),
										   m_mapTagOfOneCharWord("TagOfOneCharWord", dep_table_size),
										   m_mapWordTagTag("WordTagTag", dep_table_size),
										   m_mapTagByLastCharCat("TagByLastCharCat", dep_table_size),
										   m_mapST0cST1c("ST0cST1c", dep_table_size),
										   m_mapST0wST1wt("ST0wST1wt", dep_table_size),
										   m_mapST1tRARITY("ST1tRARITY", dep_table_size),
										   m_mapCurrentWordLastChar("CurrentWordLastChar", dep_table_size),
										   m_mapN1a("N1a", dep_table_size),
										   m_mapST1wRARITY("ST1wRARITY", dep_table_size),
										   m_mapN1c("N1c", dep_table_size),
										   m_mapST0ct("ST0ct", dep_table_size),
										   m_mapST0tDist("ST0tDist", dep_table_size),
										   m_mapTagByLastChar("TagByLastChar", dep_table_size),
										   m_mapST0tST1tST1LD1t("ST0tST1tST1LD1t", dep_table_size),
										   m_mapFirstCharCurrentChar("FirstCharCurrentChar", dep_table_size),
										   m_mapFirstCharBy3Tags("FirstCharBy3Tags", dep_table_size),
										   m_mapST0wST1w("ST0wST1w", dep_table_size),
										   m_mapST0wtN0c("ST0wtN0c", dep_table_size),
										   m_mapST0wST1t("ST0wST1t", dep_table_size),
										   m_mapST1RD1wt("ST1RD1wt", dep_table_size),
										   m_mapTagWordTag("TagWordTag", dep_table_size),
										   m_mapST0cST1t("ST0cST1t", dep_table_size),
										   m_mapN2c("N2c", dep_table_size),
										   m_mapN2a("N2a", dep_table_size),
										   m_mapOneCharWord("OneCharWord", dep_table_size),
										   m_mapST0rsw("ST0rsw", dep_table_size),
										   m_mapST1rsw("ST1rsw", dep_table_size),
										   m_mapST0cST1rsw("ST0cST1rsw", dep_table_size),
										   m_mapST0lswST1c("ST0lswST1c", dep_table_size),
										   m_mapST0lswt("ST0lswt", dep_table_size),
										   m_mapST0lswN0c("ST0lswN0c", dep_table_size),
										   m_mapST0rswST1c("ST0rswST1c", dep_table_size),
										   m_mapST1lswt("ST1lswt", dep_table_size),
										   m_mapST0tST1rsw("ST0tST1rsw", dep_table_size),
										   m_mapST0lsw("ST0lsw", dep_table_size),
										   m_mapST0rswN0c("ST0rswN0c", dep_table_size),
										   m_mapST1lsw("ST1lsw", dep_table_size),
										   m_mapST1rswt("ST1rswt", dep_table_size),
										   m_mapST0lswST1t("ST0lswST1t", dep_table_size),
										   m_mapST0tST1lsw("ST0tST1lsw", dep_table_size),
										   m_mapST0rswt("ST0rswt", dep_table_size),
										   m_mapST0cST1lsw("ST0cST1lsw", dep_table_size),
										   m_mapST0rswST1t("ST0rswST1t", dep_table_size),
										   m_mapST1cST0cN0c("ST1cST0cN0c", dep_table_size),
										   m_mapST0wST1ct("ST0wST1ct", dep_table_size),
										   m_mapST0wtST1c("ST0wtST1c", dep_table_size),
										   m_mapST0cST1w("ST0cST1w", dep_table_size),
										   m_mapST0ctST1w("ST0ctST1w", dep_table_size),
										   m_mapST0wST1c("ST0wST1c", dep_table_size),
										   m_mapST0cST1wt("ST0cST1wt", dep_table_size),
										   m_mapST2cST1cST0c("ST2cST1cST0c", dep_table_size),
										   m_mapST0lswtN0c("ST0lswtN0c", dep_table_size),
										   m_mapST0ctST1rsw("ST0ctST1rsw", dep_table_size),
										   m_mapST0ctST1lsw("ST0ctST1lsw", dep_table_size),
										   m_mapST0lswtST1w("ST0lswtST1w", dep_table_size),
										   m_mapST0wtST1rsw("ST0wtST1rsw", dep_table_size),
										   m_mapST0rswtST1w("ST0rswtST1w", dep_table_size),
										   m_mapST0lswST1wt("ST0lswST1wt", dep_table_size),
										   m_mapST0wST1lswt("ST0wST1lswt", dep_table_size),
										   m_mapST0lswST1w("ST0lswST1w", dep_table_size),
										   m_mapST0lswST1ct("ST0lswST1ct", dep_table_size),
										   m_mapST0lswtST1c("ST0lswtST1c", dep_table_size),
										   m_mapST0wST1rswt("ST0wST1rswt", dep_table_size),
										   m_mapST0wST1lsw("ST0wST1lsw", dep_table_size),
										   m_mapST0wST1rsw("ST0wST1rsw", dep_table_size),
										   m_mapST0rswST1w("ST0rswST1w", dep_table_size),
										   m_mapST0wtST1lsw("ST0wtST1lsw", dep_table_size),
										   m_mapST0cST1rswt("ST0cST1rswt", dep_table_size),
										   m_mapST0rswST1ct("ST0rswST1ct", dep_table_size),
										   m_mapST0cST1lswt("ST0cST1lswt", dep_table_size),
										   m_mapST0rswtN0c("ST0rswtN0c", dep_table_size),
										   m_mapST0rswST1wt("ST0rswST1wt", dep_table_size),
										   m_mapST0rswtST1c("ST0rswtST1c", dep_table_size),
										   m_mapST0cST0LD1cST0LD2c("ST0cST0LD1cST0LD2c", dep_table_size),
										   m_mapST0cST1cST1LD1c("ST0cST1cST1LD1c", dep_table_size),
										   m_mapST1cST1LD1c("ST1cST1LD1c", dep_table_size),
										   m_mapST1LD1ct("ST1LD1ct", dep_table_size),
										   m_mapST1RD1ct("ST1RD1ct", dep_table_size),
										   m_mapST1cST1RD1cST1RD2c("ST1cST1RD1cST1RD2c", dep_table_size),
										   m_mapST0LD1ct("ST0LD1ct", dep_table_size),
										   m_mapST1cST1LD1cST1LD2c("ST1cST1LD1cST1LD2c", dep_table_size),
										   m_mapST1cST1RD1c("ST1cST1RD1c", dep_table_size),
										   m_mapST0cST1cST1RD1c("ST0cST1cST1RD1c", dep_table_size),
										   m_mapST1cST0cST0LD1c("ST1cST0cST0LD1c", dep_table_size),
										   m_mapST0cST0LD1c("ST0cST0LD1c", dep_table_size),
										   m_mapCurentWordInDict("CurentWordInDict", dep_table_size),
										   m_mapCurentWordOutDictByTag("CurentWordOutDictByTag", dep_table_size),
										   m_mapCurentWordOutDict("CurentWordOutDict", dep_table_size),
										   m_mapCurentWordInDictByTag("CurentWordInDictByTag", dep_table_size),
										   m_mapCurentWordInDictOutTagDict("CurentWordInDictOutTagDict", dep_table_size),
										   m_mapCurentWordInTagDictByTag("CurentWordInTagDictByTag", dep_table_size),
										   m_mapCurentWordInDictOutTagDictByTag("CurentWordInDictOutTagDictByTag", dep_table_size),
										   m_mapCurentWordInTagDict("CurentWordInTagDict", dep_table_size),
										   m_mapCurentSubWordOutDict("CurentSubWordOutDict", dep_table_size),
										   m_mapCurentSubWordInDictByTagLeft("CurentSubWordInDictByTagLeft", dep_table_size),
										   m_mapCurentSubWordInDictLeft("CurentSubWordInDictLeft", dep_table_size),
										   m_mapCurentSubWordInDictRight("CurentSubWordInDictRight", dep_table_size),
										   m_mapCurentSubWordOutDictByTag("CurentSubWordOutDictByTag", dep_table_size),
										   m_mapCurentSubWordInDict("CurentSubWordInDict", dep_table_size),
										   m_mapCurentSubWordInDictByTagRight("CurentSubWordInDictByTagRight", dep_table_size),
										   m_mapCurentSubWordInDictByTag("CurentSubWordInDictByTag", dep_table_size),
										   m_mapST0scST1sc("ST0scST1sc", dep_table_size),
										   m_mapST0ec("ST0ec", dep_table_size),
										   m_mapST1ect("ST1ect", dep_table_size),
										   m_mapST1ec("ST1ec", dep_table_size),
										   m_mapST0sct("ST0sct", dep_table_size),
										   m_mapST0sc("ST0sc", dep_table_size),
										   m_mapST0scN0c("ST0scN0c", dep_table_size),
										   m_mapST1sct("ST1sct", dep_table_size),
										   m_mapST0ecN0c("ST0ecN0c", dep_table_size),
										   m_mapST0ect("ST0ect", dep_table_size),
										   m_mapST1sc("ST1sc", dep_table_size),
										   m_mapST0ecST1ec("ST0ecST1ec", dep_table_size),
										   m_mapST0l0swN0c("ST0l0swN0c", dep_table_size),
										   m_mapST0r0swt("ST0r0swt", dep_table_size),
										   m_mapST0wST1l0sw("ST0wST1l0sw", dep_table_size),
										   m_mapST0wST1r0sw("ST0wST1r0sw", dep_table_size),
										   m_mapST0r0swN0c("ST0r0swN0c", dep_table_size),
										   m_mapST0r0swST1c("ST0r0swST1c", dep_table_size),
										   m_mapST0l0swST1c("ST0l0swST1c", dep_table_size),
										   m_mapST1l0sw("ST1l0sw", dep_table_size),
										   m_mapST0r0swST1w("ST0r0swST1w", dep_table_size),
										   m_mapST0cST1l0sw("ST0cST1l0sw", dep_table_size),
										   m_mapST1r0sw("ST1r0sw", dep_table_size),
										   m_mapST0r0sw("ST0r0sw", dep_table_size),
										   m_mapST0l0sw("ST0l0sw", dep_table_size),
										   m_mapST0cST1r0sw("ST0cST1r0sw", dep_table_size),
										   m_mapST0l0swST1w("ST0l0swST1w", dep_table_size),
										   m_mapST0l0swt("ST0l0swt", dep_table_size),
										   m_mapST1l0swt("ST1l0swt", dep_table_size),
										   m_mapST1r0swt("ST1r0swt", dep_table_size)

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
