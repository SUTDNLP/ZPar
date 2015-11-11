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
    left(m_mapN2w)right\
    left(m_mapN1wN2w)right\
    left(m_mapSTHtSTtN0t)right\
    left(m_mapN0wSTwt)right\
    left(m_mapSTtSTRDtN0t)right\
    left(m_mapN1wN2t)right\
    left(m_mapConsecutiveChars)right\
    left(m_mapSTtla)right\
    left(m_mapN1cN2t)right\
    left(m_mapN2t)right\
    left(m_mapN0wtSTw)right\
    left(m_mapN0wtSTt)right\
    left(m_mapN0tlp)right\
    left(m_mapN0tN1tN2t)right\
    left(m_mapSTwDist)right\
    left(m_mapSTL2Dt)right\
    left(m_mapN1cN2c)right\
    left(m_mapSTL2Dw)right\
    left(m_mapTagByFirstChar)right\
    left(m_mapN0wlp)right\
\
    left(m_mapN0L2Di)right\
    left(m_mapN0wla)right\
    left(m_mapN0LDi)right\
    left(m_mapSTtSTLDtSTL2Dt)right\
    left(m_mapLastTagByWord)right\
    left(m_mapSTtDist)right\
    left(m_mapTaggedCharByLastChar)right\
    left(m_mapN2wt)right\
    left(m_mapN0wSTwN1t)right\
    left(m_mapN0tN0LDtN0L2Dt)right\
    left(m_mapN0LDw)right\
    left(m_mapN0LDt)right\
    left(m_mapSeparateChars)right\
    left(m_mapSTtlp)right\
    left(m_mapTaggedConsecutiveChars)right\
    left(m_mapSTHHtSTHtSTt)right\
    left(m_mapN0tSTc)right\
    left(m_mapTag0Tag1Tag2Size1)right\
    left(m_mapSTHHw)right\
    left(m_mapSTHHt)right\
    left(m_mapN1wt)right\
    left(m_mapTagByFirstCharCat)right\
    left(m_mapTag1Tag2Size1)right\
    left(m_mapN0wN1wt)right\
    left(m_mapN0L2Dt)right\
    left(m_mapTagByLastWord)right\
    left(m_mapN0L2Dw)right\
    left(m_mapLastWordFirstChar)right\
    left(m_mapFirstAndLastChars)right\
    left(m_mapN0tla)right\
    left(m_mapCurentWordTag)right\
    left(m_mapTaggedFirstCharCurrentChar)right\
    left(m_mapN0cN1t)right\
    left(m_mapTagByWordAndNextChar)right\
    left(m_mapAPPTagByChar)right\
    left(m_mapTagByWordAndPrevChar)right\
\
    left(m_mapTag0Tag1Size1)right\
    left(m_mapN1tN2w)right\
    left(m_mapLastTagByTag)right\
    left(m_mapN0tSTw)right\
    left(m_mapN1tN2t)right\
    left(m_mapN0tSTt)right\
    left(m_mapN0cN1c)right\
    left(m_mapN0tSTtN1w)right\
    left(m_mapFirstCharLastWordByWord)right\
    left(m_mapCharByLastChar)right\
    left(m_mapLengthByFirstChar)right\
    left(m_mapLastWordByWord)right\
    left(m_mapSTHi)right\
    left(m_mapN1tN2c)right\
    left(m_mapSTHw)right\
    left(m_mapN0tN1w)right\
    left(m_mapSTwrp)right\
    left(m_mapN0tN1t)right\
    left(m_mapLastWordByLastChar)right\
    left(m_mapN0wDist)right\
    left(m_mapSTHt)right\
    left(m_mapN0wSTw)right\
    left(m_mapN0wtSTwt)right\
    left(m_mapN0wSTt)right\
    left(m_mapN2ct)right\
    left(m_mapTaggedSeparateChars)right\
    left(m_mapCurentWord)right\
    left(m_mapTaggedCharByFirstChar)right\
    left(m_mapSTwra)right\
    left(m_mapN0tN1c)right\
    left(m_mapSTtN0tN0LDt)right\
    left(m_mapSTwt)right\
    left(m_mapN0tSTwN1w)right\
    left(m_mapN0tSTwN1t)right\
    left(m_mapN1ct)right\
    left(m_mapN0cSTt)right\
    left(m_mapLastTwoTagsByTag)right\
\
    left(m_mapSTtSTLDtN0t)right\
    left(m_mapTagOfOneCharWord)right\
    left(m_mapWordTagTag)right\
    left(m_mapTagByLastCharCat)right\
    left(m_mapN0wN1w)right\
    left(m_mapSTR2Dw)right\
    left(m_mapSTLDi)right\
    left(m_mapSTR2Dt)right\
    left(m_mapSTi)right\
    left(m_mapN0wt)right\
    left(m_mapN0t)right\
    left(m_mapSTR2Di)right\
    left(m_mapN0wN1t)right\
    left(m_mapN0tDist)right\
    left(m_mapN0w)right\
    left(m_mapCurrentWordLastChar)right\
    left(m_mapN0wSTtN1t)right\
    left(m_mapSTLDt)right\
    left(m_mapSTtN0tN1t)right\
    left(m_mapN1c)right\
    left(m_mapN0wtN1w)right\
    left(m_mapSTtra)right\
    left(m_mapSTLDw)right\
    left(m_mapN0tSTtDist)right\
    left(m_mapN0wSTtN1w)right\
    left(m_mapN0cSTcN1c)right\
    left(m_mapN0wSTwDist)right\
    left(m_mapTagByLastChar)right\
    left(m_mapFirstCharCurrentChar)right\
    left(m_mapFirstCharBy3Tags)right\
    left(m_mapN1t)right\
    left(m_mapSTL2Di)right\
    left(m_mapSTRDi)right\
    left(m_mapSTtSTRDtSTR2Dt)right\
\
    left(m_mapSTtrp)right\
    left(m_mapTagWordTag)right\
    left(m_mapN1w)right\
    left(m_mapSTwla)right\
    left(m_mapSTRDw)right\
    left(m_mapSTt)right\
    left(m_mapN2c)right\
    left(m_mapOneCharWord)right\
    left(m_mapSTw)right\
    left(m_mapN0tSTwt)right\
    left(m_mapSTwlp)right\
    left(m_mapSTRDt)right\
\
    left(m_mapN0rsw)right\
    left(m_mapN0ctSTw)right\
    left(m_mapSTcN0cN0LD1c)right\
    left(m_mapSTRD1ct)right\
    left(m_mapN0rswt)right\
    left(m_mapSTlswt)right\
    left(m_mapSTrswt)right\
    left(m_mapCurentWordOutDict)right\
    left(m_mapN0rswSTc)right\
    left(m_mapN0r0swt)right\
    left(m_mapN0wSTr0sw)right\
    left(m_mapCurentWordInDictOutTagDict)right\
    left(m_mapN0cSTl0sw)right\
    left(m_mapN0cSTrsw)right\
    left(m_mapSTct)right\
    left(m_mapN0cSTr0sw)right\
    left(m_mapSTr0swt)right\
    left(m_mapSTHcSTcN0c)right\
    left(m_mapCurentWordInDictByTag)right\
    left(m_mapN0wSTl0sw)right\
    left(m_mapN0lswSTw)right\
    left(m_mapN0wtSTc)right\
    left(m_mapSTLD1ct)right\
    left(m_mapN0l0sw)right\
    left(m_mapN0ct)right\
    left(m_mapN0cSTw)right\
    left(m_mapCurentWordInTagDictByTag)right\
    left(m_mapCurentWordInDictOutTagDictByTag)right\
    left(m_mapCurentWordOutDictByTag)right\
    left(m_mapCurentSubWordInDictLeft)right\
    left(m_mapN0c)right\
    left(m_mapCurentSubWordInDict)right\
    left(m_mapN0cSTc)right\
    left(m_mapN0r0sw)right\
    left(m_mapN0cSTwt)right\
    left(m_mapSTl0swt)right\
\
    left(m_mapN0wSTct)right\
    left(m_mapSTc)right\
    left(m_mapCurentWordInTagDict)right\
    left(m_mapSTcSTRD1c)right\
    left(m_mapN0cN0LD1cN0LD2c)right\
    left(m_mapN0lswSTc)right\
    left(m_mapSTr0sw)right\
    left(m_mapN0l0swSTw)right\
    left(m_mapN0r0swSTc)right\
    left(m_mapN0cSTlsw)right\
    left(m_mapN0wSTc)right\
    left(m_mapSTlsw)right\
    left(m_mapN0cN0LD1c)right\
    left(m_mapCurentWordInDict)right\
    left(m_mapN0lsw)right\
    left(m_mapCurentSubWordInDictByTagLeft)right\
    left(m_mapN0cSTcSTRD1c)right\
    left(m_mapN0lswt)right\
    left(m_mapN0cSTcSTLD1c)right\
    left(m_mapN0r0swSTw)right\
    left(m_mapCurentSubWordInDictRight)right\
    left(m_mapCurentSubWordInDictByTagRight)right\
    left(m_mapSTcSTLD1cSTLD2c)right\
    left(m_mapSTcSTLD1c)right\
    left(m_mapSTcSTRD1cSTRD2c)right\
    left(m_mapN0LD1ct)right\
    left(m_mapN0wSTlsw)right\
    left(m_mapN0l0swSTc)right\
    left(m_mapN0rswSTw)right\
    left(m_mapCurentSubWordInDictByTag)right\
    left(m_mapSTl0sw)right\
    left(m_mapN0l0swt)right\
    left(m_mapN0wSTrsw)right\
    left(m_mapSTrsw)right


#define iterate_double_templates(left, middle, right)\
    left m_mapLengthByLastChar middle m_mapLengthByLastChar right\
    left m_mapFirstCharBy2Tags middle m_mapFirstCharBy2Tags right\
    left m_mapN2w middle m_mapN2w right\
    left m_mapN1wN2w middle m_mapN1wN2w right\
    left m_mapSTHtSTtN0t middle m_mapSTHtSTtN0t right\
    left m_mapN0wSTwt middle m_mapN0wSTwt right\
    left m_mapSTtSTRDtN0t middle m_mapSTtSTRDtN0t right\
    left m_mapN1wN2t middle m_mapN1wN2t right\
    left m_mapConsecutiveChars middle m_mapConsecutiveChars right\
    left m_mapSTtla middle m_mapSTtla right\
    left m_mapN1cN2t middle m_mapN1cN2t right\
    left m_mapN2t middle m_mapN2t right\
    left m_mapN0wtSTw middle m_mapN0wtSTw right\
    left m_mapN0wtSTt middle m_mapN0wtSTt right\
    left m_mapN0tlp middle m_mapN0tlp right\
    left m_mapN0tN1tN2t middle m_mapN0tN1tN2t right\
    left m_mapSTwDist middle m_mapSTwDist right\
    left m_mapSTL2Dt middle m_mapSTL2Dt right\
    left m_mapN1cN2c middle m_mapN1cN2c right\
    left m_mapSTL2Dw middle m_mapSTL2Dw right\
    left m_mapTagByFirstChar middle m_mapTagByFirstChar right\
    left m_mapN0wlp middle m_mapN0wlp right\
    left m_mapN0L2Di middle m_mapN0L2Di right\
    left m_mapN0wla middle m_mapN0wla right\
    left m_mapN0LDi middle m_mapN0LDi right\
    left m_mapSTtSTLDtSTL2Dt middle m_mapSTtSTLDtSTL2Dt right\
    left m_mapLastTagByWord middle m_mapLastTagByWord right\
    left m_mapSTtDist middle m_mapSTtDist right\
    left m_mapTaggedCharByLastChar middle m_mapTaggedCharByLastChar right\
\
    left m_mapN2wt middle m_mapN2wt right\
    left m_mapN0wSTwN1t middle m_mapN0wSTwN1t right\
    left m_mapN0tN0LDtN0L2Dt middle m_mapN0tN0LDtN0L2Dt right\
    left m_mapN0LDw middle m_mapN0LDw right\
    left m_mapN0LDt middle m_mapN0LDt right\
    left m_mapSeparateChars middle m_mapSeparateChars right\
    left m_mapSTtlp middle m_mapSTtlp right\
    left m_mapTaggedConsecutiveChars middle m_mapTaggedConsecutiveChars right\
    left m_mapSTHHtSTHtSTt middle m_mapSTHHtSTHtSTt right\
    left m_mapN0tSTc middle m_mapN0tSTc right\
    left m_mapTag0Tag1Tag2Size1 middle m_mapTag0Tag1Tag2Size1 right\
    left m_mapSTHHw middle m_mapSTHHw right\
    left m_mapSTHHt middle m_mapSTHHt right\
    left m_mapN1wt middle m_mapN1wt right\
    left m_mapTagByFirstCharCat middle m_mapTagByFirstCharCat right\
    left m_mapTag1Tag2Size1 middle m_mapTag1Tag2Size1 right\
    left m_mapN0wN1wt middle m_mapN0wN1wt right\
    left m_mapN0L2Dt middle m_mapN0L2Dt right\
    left m_mapTagByLastWord middle m_mapTagByLastWord right\
    left m_mapN0L2Dw middle m_mapN0L2Dw right\
    left m_mapLastWordFirstChar middle m_mapLastWordFirstChar right\
    left m_mapFirstAndLastChars middle m_mapFirstAndLastChars right\
    left m_mapN0tla middle m_mapN0tla right\
    left m_mapCurentWordTag middle m_mapCurentWordTag right\
    left m_mapTaggedFirstCharCurrentChar middle m_mapTaggedFirstCharCurrentChar right\
    left m_mapN0cN1t middle m_mapN0cN1t right\
    left m_mapTagByWordAndNextChar middle m_mapTagByWordAndNextChar right\
    left m_mapAPPTagByChar middle m_mapAPPTagByChar right\
    left m_mapTagByWordAndPrevChar middle m_mapTagByWordAndPrevChar right\
    left m_mapTag0Tag1Size1 middle m_mapTag0Tag1Size1 right\
    left m_mapN1tN2w middle m_mapN1tN2w right\
    left m_mapLastTagByTag middle m_mapLastTagByTag right\
    left m_mapN0tSTw middle m_mapN0tSTw right\
    left m_mapN1tN2t middle m_mapN1tN2t right\
    left m_mapN0tSTt middle m_mapN0tSTt right\
    left m_mapN0cN1c middle m_mapN0cN1c right\
    left m_mapN0tSTtN1w middle m_mapN0tSTtN1w right\
    left m_mapFirstCharLastWordByWord middle m_mapFirstCharLastWordByWord right\
\
    left m_mapCharByLastChar middle m_mapCharByLastChar right\
    left m_mapLengthByFirstChar middle m_mapLengthByFirstChar right\
    left m_mapLastWordByWord middle m_mapLastWordByWord right\
    left m_mapSTHi middle m_mapSTHi right\
    left m_mapN1tN2c middle m_mapN1tN2c right\
    left m_mapSTHw middle m_mapSTHw right\
    left m_mapN0tN1w middle m_mapN0tN1w right\
    left m_mapSTwrp middle m_mapSTwrp right\
    left m_mapN0tN1t middle m_mapN0tN1t right\
    left m_mapLastWordByLastChar middle m_mapLastWordByLastChar right\
    left m_mapN0wDist middle m_mapN0wDist right\
    left m_mapSTHt middle m_mapSTHt right\
    left m_mapN0wSTw middle m_mapN0wSTw right\
    left m_mapN0wtSTwt middle m_mapN0wtSTwt right\
    left m_mapN0wSTt middle m_mapN0wSTt right\
    left m_mapN2ct middle m_mapN2ct right\
    left m_mapTaggedSeparateChars middle m_mapTaggedSeparateChars right\
    left m_mapCurentWord middle m_mapCurentWord right\
    left m_mapTaggedCharByFirstChar middle m_mapTaggedCharByFirstChar right\
    left m_mapSTwra middle m_mapSTwra right\
    left m_mapN0tN1c middle m_mapN0tN1c right\
    left m_mapSTtN0tN0LDt middle m_mapSTtN0tN0LDt right\
    left m_mapSTwt middle m_mapSTwt right\
    left m_mapN0tSTwN1w middle m_mapN0tSTwN1w right\
    left m_mapN0tSTwN1t middle m_mapN0tSTwN1t right\
    left m_mapN1ct middle m_mapN1ct right\
    left m_mapN0cSTt middle m_mapN0cSTt right\
    left m_mapLastTwoTagsByTag middle m_mapLastTwoTagsByTag right\
    left m_mapSTtSTLDtN0t middle m_mapSTtSTLDtN0t right\
    left m_mapTagOfOneCharWord middle m_mapTagOfOneCharWord right\
    left m_mapWordTagTag middle m_mapWordTagTag right\
    left m_mapTagByLastCharCat middle m_mapTagByLastCharCat right\
    left m_mapN0wN1w middle m_mapN0wN1w right\
    left m_mapSTR2Dw middle m_mapSTR2Dw right\
    left m_mapSTLDi middle m_mapSTLDi right\
    left m_mapSTR2Dt middle m_mapSTR2Dt right\
    left m_mapSTi middle m_mapSTi right\
\
    left m_mapN0wt middle m_mapN0wt right\
    left m_mapN0t middle m_mapN0t right\
    left m_mapSTR2Di middle m_mapSTR2Di right\
    left m_mapN0wN1t middle m_mapN0wN1t right\
    left m_mapN0tDist middle m_mapN0tDist right\
    left m_mapN0w middle m_mapN0w right\
    left m_mapCurrentWordLastChar middle m_mapCurrentWordLastChar right\
    left m_mapN0wSTtN1t middle m_mapN0wSTtN1t right\
    left m_mapSTLDt middle m_mapSTLDt right\
    left m_mapSTtN0tN1t middle m_mapSTtN0tN1t right\
    left m_mapN1c middle m_mapN1c right\
    left m_mapN0wtN1w middle m_mapN0wtN1w right\
    left m_mapSTtra middle m_mapSTtra right\
    left m_mapSTLDw middle m_mapSTLDw right\
    left m_mapN0tSTtDist middle m_mapN0tSTtDist right\
    left m_mapN0wSTtN1w middle m_mapN0wSTtN1w right\
    left m_mapN0cSTcN1c middle m_mapN0cSTcN1c right\
    left m_mapN0wSTwDist middle m_mapN0wSTwDist right\
    left m_mapTagByLastChar middle m_mapTagByLastChar right\
    left m_mapFirstCharCurrentChar middle m_mapFirstCharCurrentChar right\
    left m_mapFirstCharBy3Tags middle m_mapFirstCharBy3Tags right\
    left m_mapN1t middle m_mapN1t right\
    left m_mapSTL2Di middle m_mapSTL2Di right\
    left m_mapSTRDi middle m_mapSTRDi right\
    left m_mapSTtSTRDtSTR2Dt middle m_mapSTtSTRDtSTR2Dt right\
    left m_mapSTtrp middle m_mapSTtrp right\
    left m_mapTagWordTag middle m_mapTagWordTag right\
\
    left m_mapN1w middle m_mapN1w right\
    left m_mapSTwla middle m_mapSTwla right\
    left m_mapSTRDw middle m_mapSTRDw right\
    left m_mapSTt middle m_mapSTt right\
    left m_mapN2c middle m_mapN2c right\
    left m_mapOneCharWord middle m_mapOneCharWord right\
    left m_mapSTw middle m_mapSTw right\
    left m_mapN0tSTwt middle m_mapN0tSTwt right\
    left m_mapSTwlp middle m_mapSTwlp right\
    left m_mapSTRDt middle m_mapSTRDt right\
\
    left m_mapN0rsw middle m_mapN0rsw right\
    left m_mapN0ctSTw middle m_mapN0ctSTw right\
    left m_mapSTcN0cN0LD1c middle m_mapSTcN0cN0LD1c right\
    left m_mapSTRD1ct middle m_mapSTRD1ct right\
    left m_mapN0rswt middle m_mapN0rswt right\
    left m_mapSTlswt middle m_mapSTlswt right\
    left m_mapSTrswt middle m_mapSTrswt right\
    left m_mapCurentWordOutDict middle m_mapCurentWordOutDict right\
    left m_mapN0rswSTc middle m_mapN0rswSTc right\
    left m_mapN0r0swt middle m_mapN0r0swt right\
    left m_mapN0wSTr0sw middle m_mapN0wSTr0sw right\
    left m_mapCurentWordInDictOutTagDict middle m_mapCurentWordInDictOutTagDict right\
    left m_mapN0cSTl0sw middle m_mapN0cSTl0sw right\
    left m_mapN0cSTrsw middle m_mapN0cSTrsw right\
    left m_mapSTct middle m_mapSTct right\
    left m_mapN0cSTr0sw middle m_mapN0cSTr0sw right\
    left m_mapSTr0swt middle m_mapSTr0swt right\
    left m_mapSTHcSTcN0c middle m_mapSTHcSTcN0c right\
    left m_mapCurentWordInDictByTag middle m_mapCurentWordInDictByTag right\
    left m_mapN0wSTl0sw middle m_mapN0wSTl0sw right\
    left m_mapN0lswSTw middle m_mapN0lswSTw right\
    left m_mapN0wtSTc middle m_mapN0wtSTc right\
    left m_mapSTLD1ct middle m_mapSTLD1ct right\
    left m_mapN0l0sw middle m_mapN0l0sw right\
    left m_mapN0ct middle m_mapN0ct right\
    left m_mapN0cSTw middle m_mapN0cSTw right\
    left m_mapCurentWordInTagDictByTag middle m_mapCurentWordInTagDictByTag right\
    left m_mapCurentWordInDictOutTagDictByTag middle m_mapCurentWordInDictOutTagDictByTag right\
    left m_mapCurentWordOutDictByTag middle m_mapCurentWordOutDictByTag right\
    left m_mapCurentSubWordInDictLeft middle m_mapCurentSubWordInDictLeft right\
    left m_mapN0c middle m_mapN0c right\
    left m_mapCurentSubWordInDict middle m_mapCurentSubWordInDict right\
    left m_mapN0cSTc middle m_mapN0cSTc right\
    left m_mapN0r0sw middle m_mapN0r0sw right\
    left m_mapN0cSTwt middle m_mapN0cSTwt right\
    left m_mapSTl0swt middle m_mapSTl0swt right\
\
    left m_mapN0wSTct middle m_mapN0wSTct right\
    left m_mapSTc middle m_mapSTc right\
    left m_mapCurentWordInTagDict middle m_mapCurentWordInTagDict right\
    left m_mapSTcSTRD1c middle m_mapSTcSTRD1c right\
    left m_mapN0cN0LD1cN0LD2c middle m_mapN0cN0LD1cN0LD2c right\
    left m_mapN0lswSTc middle m_mapN0lswSTc right\
    left m_mapSTr0sw middle m_mapSTr0sw right\
    left m_mapN0l0swSTw middle m_mapN0l0swSTw right\
    left m_mapN0r0swSTc middle m_mapN0r0swSTc right\
    left m_mapN0cSTlsw middle m_mapN0cSTlsw right\
    left m_mapN0wSTc middle m_mapN0wSTc right\
    left m_mapSTlsw middle m_mapSTlsw right\
    left m_mapN0cN0LD1c middle m_mapN0cN0LD1c right\
    left m_mapCurentWordInDict middle m_mapCurentWordInDict right\
    left m_mapN0lsw middle m_mapN0lsw right\
    left m_mapCurentSubWordInDictByTagLeft middle m_mapCurentSubWordInDictByTagLeft right\
    left m_mapN0cSTcSTRD1c middle m_mapN0cSTcSTRD1c right\
    left m_mapN0lswt middle m_mapN0lswt right\
    left m_mapN0cSTcSTLD1c middle m_mapN0cSTcSTLD1c right\
    left m_mapN0r0swSTw middle m_mapN0r0swSTw right\
    left m_mapCurentSubWordInDictRight middle m_mapCurentSubWordInDictRight right\
    left m_mapCurentSubWordInDictByTagRight middle m_mapCurentSubWordInDictByTagRight right\
    left m_mapSTcSTLD1cSTLD2c middle m_mapSTcSTLD1cSTLD2c right\
    left m_mapSTcSTLD1c middle m_mapSTcSTLD1c right\
    left m_mapSTcSTRD1cSTRD2c middle m_mapSTcSTRD1cSTRD2c right\
    left m_mapN0LD1ct middle m_mapN0LD1ct right\
    left m_mapN0wSTlsw middle m_mapN0wSTlsw right\
    left m_mapN0l0swSTc middle m_mapN0l0swSTc right\
    left m_mapN0rswSTw middle m_mapN0rswSTw right\
    left m_mapCurentSubWordInDictByTag middle m_mapCurentSubWordInDictByTag right\
    left m_mapSTl0sw middle m_mapSTl0sw right\
    left m_mapN0l0swt middle m_mapN0l0swt right\
    left m_mapN0wSTrsw middle m_mapN0wSTrsw right\
    left m_mapSTrsw middle m_mapSTrsw right



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
        CWordMap    m_mapN2w;
        CWordWordMap    m_mapN1wN2w;
        CTagTagTagMap    m_mapSTHtSTtN0t;
        CWordWordTagMap    m_mapN0wSTwt;
        CTagTagTagMap    m_mapSTtSTRDtN0t;
        CWordTagMap    m_mapN1wN2t;
        CWordWordMap    m_mapConsecutiveChars;
        CTagUlongMap    m_mapSTtla;
        CWordTagMap    m_mapN1cN2t;
        CTagMap    m_mapN2t;
        CWordWordTagMap    m_mapN0wtSTw;
        CWordTagMap    m_mapSTct;
        CWordTagTagMap    m_mapN0wtSTt;
        CTagUlongMap    m_mapN0tlp;
        CTagTagTagMap    m_mapN0tN1tN2t;
        CWordUlongMap    m_mapSTwDist;
        CTagMap    m_mapSTL2Dt;
        CWordWordMap    m_mapN1cN2c;
        CWordMap    m_mapSTL2Dw;
        CWordMap    m_mapTagByFirstChar;
        CWordUlongMap    m_mapN0wlp;
        CUlongMap    m_mapN0L2Di;
        CWordUlongMap    m_mapN0wla;
        CUlongMap    m_mapN0LDi;
        CTagTagTagMap    m_mapSTtSTLDtSTL2Dt;
        CWordTagMap    m_mapLastTagByWord;
        CTagUlongMap    m_mapSTtDist;
        CWordWordTagMap    m_mapTaggedCharByLastChar;
        CWordTagMap    m_mapN2wt;
        CWordWordTagMap    m_mapN0wSTwN1t;
        CTagTagTagMap    m_mapN0tN0LDtN0L2Dt;
        CWordMap    m_mapN0LDw;
        CTagMap    m_mapN0LDt;
        CWordWordMap    m_mapSeparateChars;
        CTagUlongMap    m_mapSTtlp;
        CWordWordTagMap    m_mapTaggedConsecutiveChars;
        CTagTagTagMap    m_mapSTHHtSTHtSTt;
        CWordTagMap    m_mapN0tSTc;
        CTagTagUlongMap    m_mapTag0Tag1Tag2Size1;
        CWordMap    m_mapSTHHw;
        CTagMap    m_mapSTHHt;
        CWordTagMap    m_mapN1wt;
        CUlongMap    m_mapTagByFirstCharCat;
        CTagTagUlongMap    m_mapTag1Tag2Size1;
        CWordWordTagMap    m_mapN0wN1wt;
        CTagMap    m_mapN0L2Dt;
        CWordMap    m_mapTagByLastWord;
        CWordMap    m_mapN0L2Dw;
        CWordWordMap    m_mapLastWordFirstChar;
        CWordWordMap    m_mapFirstAndLastChars;
        CTagUlongMap    m_mapN0tla;
        CWordTagMap    m_mapCurentWordTag;
        CWordWordTagMap    m_mapTaggedFirstCharCurrentChar;
        CWordTagMap    m_mapN0cN1t;
        CWordWordTagMap    m_mapTagByWordAndNextChar;
        CWordTagMap    m_mapAPPTagByChar;
        CWordWordTagMap    m_mapTagByWordAndPrevChar;
        CTagUlongMap    m_mapTag0Tag1Size1;
        CWordTagMap    m_mapN1tN2w;
        CTagMap    m_mapLastTagByTag;
        CWordTagMap    m_mapN0tSTw;
        CTagTagMap    m_mapN1tN2t;
        CTagTagMap    m_mapN0tSTt;
        CWordWordMap    m_mapN0cN1c;
        CWordTagTagMap    m_mapN0tSTtN1w;
        CWordWordMap    m_mapFirstCharLastWordByWord;
        CWordWordMap    m_mapCharByLastChar;
        CWordUlongMap    m_mapLengthByFirstChar;
        CWordWordMap    m_mapLastWordByWord;
        CUlongMap    m_mapSTHi;
        CWordTagMap    m_mapN1tN2c;
        CWordMap    m_mapSTHw;
        CWordTagMap    m_mapN0tN1w;
        CWordUlongMap    m_mapSTwrp;
        CTagTagMap    m_mapN0tN1t;
        CWordWordMap    m_mapLastWordByLastChar;
        CWordUlongMap    m_mapN0wDist;
        CTagMap    m_mapSTHt;
        CWordWordMap    m_mapN0wSTw;
        CWordWordTagTagMap    m_mapN0wtSTwt;
        CWordTagMap    m_mapN0wSTt;
        CWordTagMap    m_mapN2ct;
        CWordWordTagMap    m_mapTaggedSeparateChars;
        CWordMap    m_mapCurentWord;
        CWordWordTagMap    m_mapTaggedCharByFirstChar;
        CWordUlongMap    m_mapSTwra;
        CWordTagMap    m_mapN0tN1c;
        CTagTagTagMap    m_mapSTtN0tN0LDt;
        CWordTagMap    m_mapN0ct;
        CWordTagMap    m_mapSTwt;
        CWordWordTagMap    m_mapN0tSTwN1w;
        CWordTagTagMap    m_mapN0tSTwN1t;
        CWordTagMap    m_mapN1ct;
        CWordTagMap    m_mapN0cSTt;
        CTagTagMap    m_mapLastTwoTagsByTag;
        CTagTagTagMap    m_mapSTtSTLDtN0t;
        CWordMap    m_mapN0c;
        CWordWordMap    m_mapN0cSTc;
        CWordWordWordMap    m_mapTagOfOneCharWord;
        CWordTagMap    m_mapWordTagTag;
        CWordMap    m_mapSTc;
        CTagUlongMap    m_mapTagByLastCharCat;
        CWordWordMap    m_mapN0wN1w;
        CWordMap    m_mapSTR2Dw;
        CUlongMap    m_mapSTLDi;
        CTagMap    m_mapSTR2Dt;
        CUlongMap    m_mapSTi;
        CWordTagMap    m_mapN0wt;
        CTagMap    m_mapN0t;
        CUlongMap    m_mapSTR2Di;
        CWordTagMap    m_mapN0wN1t;
        CTagUlongMap    m_mapN0tDist;
        CWordMap    m_mapN0w;
        CWordWordMap    m_mapCurrentWordLastChar;
        CWordTagTagMap    m_mapN0wSTtN1t;
        CTagMap    m_mapSTLDt;
        CTagTagTagMap    m_mapSTtN0tN1t;
        CWordMap    m_mapN1c;
        CWordWordTagMap    m_mapN0wtN1w;
        CTagUlongMap    m_mapSTtra;
        CWordMap    m_mapSTLDw;
        CTagTagUlongMap    m_mapN0tSTtDist;
        CWordWordTagMap    m_mapN0wSTtN1w;
        CWordWordWordMap    m_mapN0cSTcN1c;
        CWordWordUlongMap    m_mapN0wSTwDist;
        CWordTagMap    m_mapTagByLastChar;
        CWordWordMap    m_mapFirstCharCurrentChar;
        CWordTagTagMap    m_mapFirstCharBy3Tags;
        CTagMap    m_mapN1t;
        CUlongMap    m_mapSTL2Di;
        CUlongMap    m_mapSTRDi;
        CTagTagTagMap    m_mapSTtSTRDtSTR2Dt;
        CTagUlongMap    m_mapSTtrp;
        CWordTagMap    m_mapTagWordTag;
        CWordMap    m_mapN1w;
        CWordUlongMap    m_mapSTwla;
        CWordMap    m_mapSTRDw;
        CTagMap    m_mapSTt;
        CWordMap    m_mapN2c;
        CWordMap    m_mapOneCharWord;
        CWordMap    m_mapSTw;
        CWordTagTagMap    m_mapN0tSTwt;
        CWordUlongMap    m_mapSTwlp;
        CTagMap    m_mapSTRDt;
        CWordMap    m_mapN0rsw;
        CWordWordTagMap    m_mapN0ctSTw;
        CWordWordWordMap    m_mapSTcN0cN0LD1c;
        CWordTagMap    m_mapSTRD1ct;
        CWordTagMap    m_mapN0rswt;
        CWordTagMap    m_mapSTlswt;
        CWordTagMap    m_mapSTrswt;
        CUlongMap    m_mapCurentWordOutDict;
        CWordWordMap    m_mapN0rswSTc;
        CWordTagMap    m_mapN0r0swt;
        CWordWordMap    m_mapN0wSTr0sw;
        CUlongMap    m_mapCurentWordInDictOutTagDict;
        CWordWordMap    m_mapN0cSTl0sw;
        CWordWordMap    m_mapN0cSTrsw;
       // CWordTagMap    m_mapSTct;
        CWordWordMap    m_mapN0cSTr0sw;
        CWordTagMap    m_mapSTr0swt;
        CWordWordWordMap    m_mapSTHcSTcN0c;
        CTagUlongMap    m_mapCurentWordInDictByTag;
        CWordWordMap    m_mapN0wSTl0sw;
        CWordWordMap    m_mapN0lswSTw;
        CWordWordTagMap    m_mapN0wtSTc;
        CWordTagMap    m_mapSTLD1ct;
        CWordMap    m_mapN0l0sw;
        //CWordTagMap    m_mapN0ct;
        CWordWordMap    m_mapN0cSTw;
        CTagUlongMap    m_mapCurentWordInTagDictByTag;
        CTagUlongMap    m_mapCurentWordInDictOutTagDictByTag;
        CTagUlongMap    m_mapCurentWordOutDictByTag;
        CUlongMap    m_mapCurentSubWordInDictLeft;
        //CWordMap    m_mapN0c;
        CUlongMap    m_mapCurentSubWordInDict;
        //CWordWordMap    m_mapN0cSTc;
        CWordMap    m_mapN0r0sw;
        CWordWordTagMap    m_mapN0cSTwt;
        CWordTagMap    m_mapSTl0swt;
        CWordWordTagMap    m_mapN0wSTct;
        //CWordMap    m_mapSTc;
        CUlongMap    m_mapCurentWordInTagDict;
        CWordWordMap    m_mapSTcSTRD1c;
        CWordWordWordMap    m_mapN0cN0LD1cN0LD2c;
        CWordWordMap    m_mapN0lswSTc;
        CWordMap    m_mapSTr0sw;
        CWordWordMap    m_mapN0l0swSTw;
        CWordWordMap    m_mapN0r0swSTc;
        CWordWordMap    m_mapN0cSTlsw;
        CWordWordMap    m_mapN0wSTc;
        CWordMap    m_mapSTlsw;
        CWordWordMap    m_mapN0cN0LD1c;
        CUlongMap    m_mapCurentWordInDict;
        CWordMap    m_mapN0lsw;
        CTagUlongMap    m_mapCurentSubWordInDictByTagLeft;
        CWordWordWordMap    m_mapN0cSTcSTRD1c;
        CWordTagMap    m_mapN0lswt;
        CWordWordWordMap    m_mapN0cSTcSTLD1c;
        CWordWordMap    m_mapN0r0swSTw;
        CUlongMap    m_mapCurentSubWordInDictRight;
        CTagUlongMap    m_mapCurentSubWordInDictByTagRight;
        CWordWordWordMap    m_mapSTcSTLD1cSTLD2c;
        CWordWordMap    m_mapSTcSTLD1c;
        CWordWordWordMap    m_mapSTcSTRD1cSTRD2c;
        CWordTagMap    m_mapN0LD1ct;
        CWordWordMap    m_mapN0wSTlsw;
        CWordWordMap    m_mapN0l0swSTc;
        CWordWordMap    m_mapN0rswSTw;
        CTagUlongMap    m_mapCurentSubWordInDictByTag;
        CWordMap    m_mapSTl0sw;
        CWordTagMap    m_mapN0l0swt;
        CWordWordMap    m_mapN0wSTrsw;
        CWordMap    m_mapSTrsw;






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
										   m_mapN2w("N2w", dep_table_size),
										   m_mapN1wN2w("N1wN2w", dep_table_size),
										   m_mapSTHtSTtN0t("STHtSTtN0t", dep_table_size),
										   m_mapN0wSTwt("N0wSTwt", dep_table_size),
										   m_mapSTtSTRDtN0t("STtSTRDtN0t", dep_table_size),
										   m_mapN1wN2t("N1wN2t", dep_table_size),
										   m_mapConsecutiveChars("ConsecutiveChars", dep_table_size),
										   m_mapSTtla("STtla", dep_table_size),
										   m_mapN1cN2t("N1cN2t", dep_table_size),
										   m_mapN2t("N2t", dep_table_size),
										   m_mapN0wtSTw("N0wtSTw", dep_table_size),
										   m_mapN0wtSTt("N0wtSTt", dep_table_size),
										   m_mapN0tlp("N0tlp", dep_table_size),
										   m_mapN0tN1tN2t("N0tN1tN2t", dep_table_size),
										   m_mapSTwDist("STwDist", dep_table_size),
										   m_mapSTL2Dt("STL2Dt", dep_table_size),
										   m_mapN1cN2c("N1cN2c", dep_table_size),
										   m_mapSTL2Dw("STL2Dw", dep_table_size),
										   m_mapTagByFirstChar("TagByFirstChar", dep_table_size),
										   m_mapN0wlp("N0wlp", dep_table_size),
										   m_mapN0L2Di("N0L2Di", dep_table_size),
										   m_mapN0wla("N0wla", dep_table_size),
										   m_mapN0LDi("N0LDi", dep_table_size),
										   m_mapSTtSTLDtSTL2Dt("STtSTLDtSTL2Dt", dep_table_size),
										   m_mapLastTagByWord("LastTagByWord", dep_table_size),
										   m_mapSTtDist("STtDist", dep_table_size),
										   m_mapTaggedCharByLastChar("TaggedCharByLastChar", dep_table_size),
										   m_mapN2wt("N2wt", dep_table_size),
										   m_mapN0wSTwN1t("N0wSTwN1t", dep_table_size),
										   m_mapN0tN0LDtN0L2Dt("N0tN0LDtN0L2Dt", dep_table_size),
										   m_mapN0LDw("N0LDw", dep_table_size),
										   m_mapN0LDt("N0LDt", dep_table_size),
										   m_mapSeparateChars("SeparateChars", dep_table_size),
										   m_mapSTtlp("STtlp", dep_table_size),
										   m_mapTaggedConsecutiveChars("TaggedConsecutiveChars", dep_table_size),
										   m_mapSTHHtSTHtSTt("STHHtSTHtSTt", dep_table_size),
										   m_mapN0tSTc("N0tSTc", dep_table_size),
										   m_mapTag0Tag1Tag2Size1("Tag0Tag1Tag2Size1", dep_table_size),
										   m_mapSTHHw("STHHw", dep_table_size),
										   m_mapSTHHt("STHHt", dep_table_size),
										   m_mapN1wt("N1wt", dep_table_size),
										   m_mapTagByFirstCharCat("TagByFirstCharCat", dep_table_size),
										   m_mapTag1Tag2Size1("Tag1Tag2Size1", dep_table_size),
										   m_mapN0wN1wt("N0wN1wt", dep_table_size),
										   m_mapN0L2Dt("N0L2Dt", dep_table_size),
										   m_mapTagByLastWord("TagByLastWord", dep_table_size),
										   m_mapN0L2Dw("N0L2Dw", dep_table_size),
										   m_mapLastWordFirstChar("LastWordFirstChar", dep_table_size),
										   m_mapFirstAndLastChars("FirstAndLastChars", dep_table_size),
										   m_mapN0tla("N0tla", dep_table_size),
										   m_mapCurentWordTag("CurentWordTag", dep_table_size),
										   m_mapTaggedFirstCharCurrentChar("TaggedFirstCharCurrentChar", dep_table_size),
										   m_mapN0cN1t("N0cN1t", dep_table_size),
										   m_mapTagByWordAndNextChar("TagByWordAndNextChar", dep_table_size),
										   m_mapAPPTagByChar("APPTagByChar", dep_table_size),
										   m_mapTagByWordAndPrevChar("TagByWordAndPrevChar", dep_table_size),
										   m_mapTag0Tag1Size1("Tag0Tag1Size1", dep_table_size),
										   m_mapN1tN2w("N1tN2w", dep_table_size),
										   m_mapLastTagByTag("LastTagByTag", dep_table_size),
										   m_mapN0tSTw("N0tSTw", dep_table_size),
										   m_mapN1tN2t("N1tN2t", dep_table_size),
										   m_mapN0tSTt("N0tSTt", dep_table_size),
										   m_mapN0cN1c("N0cN1c", dep_table_size),
										   m_mapN0tSTtN1w("N0tSTtN1w", dep_table_size),
										   m_mapFirstCharLastWordByWord("FirstCharLastWordByWord", dep_table_size),
										   m_mapCharByLastChar("CharByLastChar", dep_table_size),
										   m_mapLengthByFirstChar("LengthByFirstChar", dep_table_size),
										   m_mapLastWordByWord("LastWordByWord", dep_table_size),
										   m_mapSTHi("STHi", dep_table_size),
										   m_mapN1tN2c("N1tN2c", dep_table_size),
										   m_mapSTHw("STHw", dep_table_size),
										   m_mapN0tN1w("N0tN1w", dep_table_size),
										   m_mapSTwrp("STwrp", dep_table_size),
										   m_mapN0tN1t("N0tN1t", dep_table_size),
										   m_mapLastWordByLastChar("LastWordByLastChar", dep_table_size),
										   m_mapN0wDist("N0wDist", dep_table_size),
										   m_mapSTHt("STHt", dep_table_size),
										   m_mapN0wSTw("N0wSTw", dep_table_size),
										   m_mapN0wtSTwt("N0wtSTwt", dep_table_size),
										   m_mapN0wSTt("N0wSTt", dep_table_size),
										   m_mapN2ct("N2ct", dep_table_size),
										   m_mapTaggedSeparateChars("TaggedSeparateChars", dep_table_size),
										   m_mapCurentWord("CurentWord", dep_table_size),
										   m_mapTaggedCharByFirstChar("TaggedCharByFirstChar", dep_table_size),
										   m_mapSTwra("STwra", dep_table_size),
										   m_mapN0tN1c("N0tN1c", dep_table_size),
										   m_mapSTtN0tN0LDt("STtN0tN0LDt", dep_table_size),
										   m_mapSTwt("STwt", dep_table_size),
										   m_mapN0tSTwN1w("N0tSTwN1w", dep_table_size),
										   m_mapN0tSTwN1t("N0tSTwN1t", dep_table_size),
										   m_mapN1ct("N1ct", dep_table_size),
										   m_mapN0cSTt("N0cSTt", dep_table_size),
										   m_mapLastTwoTagsByTag("LastTwoTagsByTag", dep_table_size),
										   m_mapSTtSTLDtN0t("STtSTLDtN0t", dep_table_size),
										   m_mapTagOfOneCharWord("TagOfOneCharWord", dep_table_size),
										   m_mapWordTagTag("WordTagTag", dep_table_size),
										   m_mapTagByLastCharCat("TagByLastCharCat", dep_table_size),
										   m_mapN0wN1w("N0wN1w", dep_table_size),
										   m_mapSTR2Dw("STR2Dw", dep_table_size),
										   m_mapSTLDi("STLDi", dep_table_size),
										   m_mapSTR2Dt("STR2Dt", dep_table_size),
										   m_mapSTi("STi", dep_table_size),
										   m_mapN0wt("N0wt", dep_table_size),
										   m_mapN0t("N0t", dep_table_size),
										   m_mapSTR2Di("STR2Di", dep_table_size),
										   m_mapN0wN1t("N0wN1t", dep_table_size),
										   m_mapN0tDist("N0tDist", dep_table_size),
										   m_mapN0w("N0w", dep_table_size),
										   m_mapCurrentWordLastChar("CurrentWordLastChar", dep_table_size),
										   m_mapN0wSTtN1t("N0wSTtN1t", dep_table_size),
										   m_mapSTLDt("STLDt", dep_table_size),
										   m_mapSTtN0tN1t("STtN0tN1t", dep_table_size),
										   m_mapN1c("N1c", dep_table_size),
										   m_mapN0wtN1w("N0wtN1w", dep_table_size),
										   m_mapSTtra("STtra", dep_table_size),
										   m_mapSTLDw("STLDw", dep_table_size),
										   m_mapN0tSTtDist("N0tSTtDist", dep_table_size),
										   m_mapN0wSTtN1w("N0wSTtN1w", dep_table_size),
										   m_mapN0cSTcN1c("N0cSTcN1c", dep_table_size),
										   m_mapN0wSTwDist("N0wSTwDist", dep_table_size),
										   m_mapTagByLastChar("TagByLastChar", dep_table_size),
										   m_mapFirstCharCurrentChar("FirstCharCurrentChar", dep_table_size),
										   m_mapFirstCharBy3Tags("FirstCharBy3Tags", dep_table_size),
										   m_mapN1t("N1t", dep_table_size),
										   m_mapSTL2Di("STL2Di", dep_table_size),
										   m_mapSTRDi("STRDi", dep_table_size),
										   m_mapSTtSTRDtSTR2Dt("STtSTRDtSTR2Dt", dep_table_size),
										   m_mapSTtrp("STtrp", dep_table_size),
										   m_mapTagWordTag("TagWordTag", dep_table_size),
										   m_mapN1w("N1w", dep_table_size),
										   m_mapSTwla("STwla", dep_table_size),
										   m_mapSTRDw("STRDw", dep_table_size),
										   m_mapSTt("STt", dep_table_size),
										   m_mapN2c("N2c", dep_table_size),
										   m_mapOneCharWord("OneCharWord", dep_table_size),
										   m_mapSTw("STw", dep_table_size),
										   m_mapN0tSTwt("N0tSTwt", dep_table_size),
										   m_mapSTwlp("STwlp", dep_table_size),
										   m_mapSTRDt("STRDt", dep_table_size),
										   m_mapN0rsw("N0rsw", dep_table_size),
										   m_mapN0ctSTw("N0ctSTw", dep_table_size),
										   m_mapSTcN0cN0LD1c("STcN0cN0LD1c", dep_table_size),
										   m_mapSTRD1ct("STRD1ct", dep_table_size),
										   m_mapN0rswt("N0rswt", dep_table_size),
										   m_mapSTlswt("STlswt", dep_table_size),
										   m_mapSTrswt("STrswt", dep_table_size),
										   m_mapCurentWordOutDict("CurentWordOutDict", dep_table_size),
										   m_mapN0rswSTc("N0rswSTc", dep_table_size),
										   m_mapN0r0swt("N0r0swt", dep_table_size),
										   m_mapN0wSTr0sw("N0wSTr0sw", dep_table_size),
										   m_mapCurentWordInDictOutTagDict("CurentWordInDictOutTagDict", dep_table_size),
										   m_mapN0cSTl0sw("N0cSTl0sw", dep_table_size),
										   m_mapN0cSTrsw("N0cSTrsw", dep_table_size),
										   m_mapSTct("STct", dep_table_size),
										   m_mapN0cSTr0sw("N0cSTr0sw", dep_table_size),
										   m_mapSTr0swt("STr0swt", dep_table_size),
										   m_mapSTHcSTcN0c("STHcSTcN0c", dep_table_size),
										   m_mapCurentWordInDictByTag("CurentWordInDictByTag", dep_table_size),
										   m_mapN0wSTl0sw("N0wSTl0sw", dep_table_size),
										   m_mapN0lswSTw("N0lswSTw", dep_table_size),
										   m_mapN0wtSTc("N0wtSTc", dep_table_size),
										   m_mapSTLD1ct("STLD1ct", dep_table_size),
										   m_mapN0l0sw("N0l0sw", dep_table_size),
										   m_mapN0ct("N0ct", dep_table_size),
										   m_mapN0cSTw("N0cSTw", dep_table_size),
										   m_mapCurentWordInTagDictByTag("CurentWordInTagDictByTag", dep_table_size),
										   m_mapCurentWordInDictOutTagDictByTag("CurentWordInDictOutTagDictByTag", dep_table_size),
										   m_mapCurentWordOutDictByTag("CurentWordOutDictByTag", dep_table_size),
										   m_mapCurentSubWordInDictLeft("CurentSubWordInDictLeft", dep_table_size),
										   m_mapN0c("N0c", dep_table_size),
										   m_mapCurentSubWordInDict("CurentSubWordInDict", dep_table_size),
										   m_mapN0cSTc("N0cSTc", dep_table_size),
										   m_mapN0r0sw("N0r0sw", dep_table_size),
										   m_mapN0cSTwt("N0cSTwt", dep_table_size),
										   m_mapSTl0swt("STl0swt", dep_table_size),
										   m_mapN0wSTct("N0wSTct", dep_table_size),
										   m_mapSTc("STc", dep_table_size),
										   m_mapCurentWordInTagDict("CurentWordInTagDict", dep_table_size),
										   m_mapSTcSTRD1c("STcSTRD1c", dep_table_size),
										   m_mapN0cN0LD1cN0LD2c("N0cN0LD1cN0LD2c", dep_table_size),
										   m_mapN0lswSTc("N0lswSTc", dep_table_size),
										   m_mapSTr0sw("STr0sw", dep_table_size),
										   m_mapN0l0swSTw("N0l0swSTw", dep_table_size),
										   m_mapN0r0swSTc("N0r0swSTc", dep_table_size),
										   m_mapN0cSTlsw("N0cSTlsw", dep_table_size),
										   m_mapN0wSTc("N0wSTc", dep_table_size),
										   m_mapSTlsw("STlsw", dep_table_size),
										   m_mapN0cN0LD1c("N0cN0LD1c", dep_table_size),
										   m_mapCurentWordInDict("CurentWordInDict", dep_table_size),
										   m_mapN0lsw("N0lsw", dep_table_size),
										   m_mapCurentSubWordInDictByTagLeft("CurentSubWordInDictByTagLeft", dep_table_size),
										   m_mapN0cSTcSTRD1c("N0cSTcSTRD1c", dep_table_size),
										   m_mapN0lswt("N0lswt", dep_table_size),
										   m_mapN0cSTcSTLD1c("N0cSTcSTLD1c", dep_table_size),
										   m_mapN0r0swSTw("N0r0swSTw", dep_table_size),
										   m_mapCurentSubWordInDictRight("CurentSubWordInDictRight", dep_table_size),
										   m_mapCurentSubWordInDictByTagRight("CurentSubWordInDictByTagRight", dep_table_size),
										   m_mapSTcSTLD1cSTLD2c("STcSTLD1cSTLD2c", dep_table_size),
										   m_mapSTcSTLD1c("STcSTLD1c", dep_table_size),
										   m_mapSTcSTRD1cSTRD2c("STcSTRD1cSTRD2c", dep_table_size),
										   m_mapN0LD1ct("N0LD1ct", dep_table_size),
										   m_mapN0wSTlsw("N0wSTlsw", dep_table_size),
										   m_mapN0l0swSTc("N0l0swSTc", dep_table_size),
										   m_mapN0rswSTw("N0rswSTw", dep_table_size),
										   m_mapCurentSubWordInDictByTag("CurentSubWordInDictByTag", dep_table_size),
										   m_mapSTl0sw("STl0sw", dep_table_size),
										   m_mapN0l0swt("N0l0swt", dep_table_size),
										   m_mapN0wSTrsw("N0wSTrsw", dep_table_size),
										   m_mapSTrsw("STrsw", dep_table_size)


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
