// Copyright (C) University of Oxford 2010
#ifndef _ENGLISH_POSDEPENDENCY_PARSER_STATEITEM
#define _ENGLISH_POSDEPENDENCY_PARSER_STATEITEM

/*===============================================================
 *
 * CStateItem - the search state item, representing a partial
 *              candidate with shift reduce. 
 *
 * Note about members: there are two types of item properties;
 * The first is the stack, which changes during the process; 
 * The second is the incoming sentence, including m_lHeads, 
 * m_lDepsL and m_lDepsR, m_lDepNumL, m_lDepNumR etc, which 
 * records the properties of each input word so far.
 *
 * A state item is partial and do not include information about
 * all words from the input sentence. Though m_lHeads, m_lDepsL 
 * and m_lDepsR are fixed arrays with MAX_SENTENCE_SIZE length, 
 * not all the elements from the arrays are used. The ACTIVE 
 * elements are from the input index 0 to m_nNextWord, inclusive. 
 * And a state item only captures information about the active 
 * sub section from input.
 *
 * The property for each input word need to be initialised. 
 * m_lHeads m_lDepsL etc could be initialised within the 
 * clear() method. However, because the parsing process is
 * incremental, they can also be initialised lasily. 
 * Apart from the avoidance of unecessary assignments, one 
 * benefit of lazy initialisation is that we only need to copy
 * the active indexies when doing a copy operation. Therefore, 
 * this implementation takes the approach. 
 * The initialisation of these values are in clear(), shift()
 * and arcright()
 *
 *==============================================================*/

class CStateItem {

public:
    enum STACK_STATUS
    {
        OFF_STACK = 0, ON_STACK_SHIFT, ON_STACK_ARCRIGHT
    };

public:
    int m_Stack[MAX_SENTENCE_SIZE]; // stack of words that are currently processed
    int m_nStackSize;
    int m_HeadStack[MAX_SENTENCE_SIZE];                     // stack of words that are currently  processed
    int m_nHeadStackSize;

    bool m_HeadSet[MAX_SENTENCE_SIZE]; // stack of words that already have heads
    int m_nHeadSetSize;
    int m_Action[4 * MAX_SENTENCE_SIZE];
    int m_nActionSize;
    int m_nNextWord;                         // index for the next word
    int m_lHeads[MAX_SENTENCE_SIZE];         // the lexical head for each word
    int m_lDepsL[MAX_SENTENCE_SIZE]; // the leftmost dependency for each word (just for cache, temporary info), if have outer dep, always point outer dep
    int m_lDepsR[MAX_SENTENCE_SIZE]; // the rightmost dependency for each word (just for cache, temporary info), if have outer dep, always point outer dep
    int m_lInDepsL[MAX_SENTENCE_SIZE];         // the leftmost inner dependency for each word (just for cache, temporary info)
    int m_lInDepsR[MAX_SENTENCE_SIZE];         // the rightmost inner dependency for each word (just for cache, temporary info)
    int m_lDepNumL[MAX_SENTENCE_SIZE];       // the number of left dependencies
    int m_lDepNumR[MAX_SENTENCE_SIZE];       // the number of right dependencies
    int m_lInDepNumL[MAX_SENTENCE_SIZE]; // the number of left inner dependencies
    int m_lInDepNumR[MAX_SENTENCE_SIZE]; // the number of right inner dependencies
    CSetOfTags<CDependencyLabel> m_lDepTagL[MAX_SENTENCE_SIZE]; // the set of left tags, only for head char of words (we do not have inner dep labels)
    CSetOfTags<CDependencyLabel> m_lDepTagR[MAX_SENTENCE_SIZE]; // the set of right tags, only for head char of words (we do not have inner dep labels)
    int m_lSibling[MAX_SENTENCE_SIZE]; // the sibling towards head, word-level sibling is always prior
    unsigned long m_lLabels[MAX_SENTENCE_SIZE]; // the label of each dependency link
    //false denotes inner word, true denotes outer word
    bool m_lLabelTypes[MAX_SENTENCE_SIZE];  // the label of each dependency link
    unsigned long m_nLastAction;                  // the last stack action
    int m_nSentLen;
    unsigned long m_lPOSs[MAX_SENTENCE_SIZE];
    //true denotes word start, otherwise false
    bool m_lPOSTypes[MAX_SENTENCE_SIZE];

    int m_Buffer[MAX_SENTENCE_SIZE]; // stack of words that are currently processed
    int m_nBufferSize;
    int m_HeadBuffer[MAX_SENTENCE_SIZE];                     // stack of characters that are currently  processed
    int m_nHeadBufferSize;
    int m_nQNextWord;
    int m_nBufferWordSize;

public:
    SCORE_TYPE score; // score of stack - predicting how potentially this is the correct one

public:
    // constructors and destructor
    CStateItem(int nSentLen = 0) :
    m_nSentLen(nSentLen) {
        clear();
    }
    ~CStateItem() {}
    CStateItem(CStateItem& item) :
    m_nSentLen(0) {
        std::cerr << "CStateItem does not support copy constructor!";
        std::cerr.flush();
        assert(1 == 0);
    }

public:
    // comparison
    inline bool operator <(const CStateItem &item) const {
        return score < item.score;
    }
    inline bool operator >(const CStateItem &item) const {
        return score > item.score;
    }
    inline bool operator ==(const CStateItem &item) const {
        int i;
        if (m_nNextWord != item.m_nNextWord)
            return false;
        if (m_nQNextWord != item.m_nQNextWord)
            return false;
        for (i = 0; i < m_nQNextWord; ++i) {
            if (m_lPOSs[i] != item.m_lPOSs[i])
                return false;
            if (m_lPOSTypes[i] != item.m_lPOSTypes[i])
                return false;
        }

        if (m_nStackSize != item.m_nStackSize)
            return false;
        if (m_nStackSize > 0) {
            for (int i = 0; i < m_nStackSize; i++) {
                if (m_Stack[i] != item.m_Stack[i]) {
                    return false;
                }
            }
        }

        if (m_nHeadStackSize != item.m_nHeadStackSize)
            return false;
        if (m_nHeadStackSize > 0) {
            for (int i = 0; i < m_nHeadStackSize; i++) {
                if (m_HeadStack[i] != item.m_HeadStack[i]) {
                    return false;
                }
            }
        }


        if (m_nBufferWordSize != item.m_nBufferWordSize)
            return false;
        if (m_nBufferSize != item.m_nBufferSize)
            return false;
        if (m_nBufferSize > 0) {
            for (int i = 0; i < m_nBufferSize; i++) {
                if (m_Buffer[i] != item.m_Buffer[i]) {
                    return false;
                }
            }
        }

        if (m_nHeadBufferSize != item.m_nHeadBufferSize)
            return false;
        if (m_nHeadBufferSize > 0) {
            for (int i = 0; i < m_nHeadBufferSize; i++) {
                if (m_HeadBuffer[i] != item.m_HeadBuffer[i]) {
                    return false;
                }
            }
        }

        if (m_nActionSize != item.m_nActionSize)
            return false;
        if (m_nActionSize > 0) {
            for (int i = 0; i < m_nActionSize; i++) {
                if (m_Action[i] != item.m_Action[i]) {
                    return false;
                }
            }
        }

        if (m_nHeadSetSize != item.m_nHeadSetSize)
            return false;
        if (m_nHeadSetSize > 0) {
            for (int i = 0; i <= m_nQNextWord; i++) {
                if (m_HeadSet[i] != item.m_HeadSet[i]) {
                    return false;
                }
                if (m_HeadSet[i]) {
                    if (m_lHeads[i] != item.m_lHeads[i]) {
                        return false;
                    }

                    if (m_lLabels[i] != item.m_lLabels[i]) {
                        return false;
                    }
                    if (m_lLabelTypes[i] != item.m_lLabelTypes[i]) {
                        return false;
                    }

                } else {
                    if (m_lHeads[i] != item.m_lHeads[i]) {
                        return false;
                    }

                    if (m_lLabels[i] != item.m_lLabels[i]) {
                        return false;
                    }
                    if (m_lLabelTypes[i] != item.m_lLabelTypes[i]) {
                        return false;
                    }

                }
            }
        }

        // I think that the stacks don't have to be compared
        // might be proved by translating tree to stack
        //assert( m_Stack == item.m_Stack );
        return true;
    }

    inline bool operator !=(const CStateItem &item) const {
        return !((*this) == item);
    }

    // propty
    inline int stacksize() const {
        return m_nStackSize;
    }
    inline bool stackempty() const {
        return m_nStackSize <= 0;
    }
    inline int stacktop() const {
        if (m_nStackSize <= 0) {
            std::cout << "stacktop error" << std::endl;
        }
        return m_Stack[m_nStackSize - 1];
    }
    inline int stackbottom() const {
        assert(m_nStackSize > 0);
        return m_Stack[0];
    }
    inline int stackitem(const unsigned &index) const {
        assert(index < m_nStackSize);
        return m_Stack[index];
    }

    inline int buffersize() const {
        return m_nBufferSize;
    }
    inline int bufferwordsize() const {
        return m_nBufferWordSize;
    }
    inline bool bufferempty() const {
        return m_nBufferSize <= 0;
    }
    inline int buffertop() const {
        if (m_nBufferSize <= 0) {
            std::cout << "buffertop error" << std::endl;
        }
        return m_Buffer[m_nBufferSize - 1];
    }
    inline int bufferbottom() const {
        assert(m_nBufferSize > 0);
        return m_Buffer[0];
    }
    inline int bufferitem(const unsigned &index) const {
        assert(index < m_nBufferSize);
        return m_Buffer[index];
    }

    inline int headstacksize() const {
        return m_nHeadStackSize;
    }
    inline bool headstackempty() const {
        return m_nHeadStackSize <= 0;
    }
    inline int headstacktop() const {
        if (m_nHeadStackSize <= 0) {
            std::cout << "headstacktop error" << std::endl;
        }
        return m_HeadStack[m_nHeadStackSize - 1];
    }
    inline int headstackbottom() const {
        assert(m_nHeadStackSize > 0);
        return m_HeadStack[0];
    }
    inline int headstackitem(const unsigned &index) const {
        assert(index < m_nHeadStackSize);
        return m_HeadStack[index];
    }

    inline int headbuffersize() const {
        return m_nHeadBufferSize;
    }
    inline bool headbufferempty() const {
        return m_nHeadBufferSize <= 0;
    }
    inline int headbuffertop() const {
        if (m_nHeadBufferSize <= 0) {
            std::cout << "headbuffertop error" << std::endl;
        }
        return m_HeadBuffer[m_nHeadBufferSize - 1];
    }
    inline int headbufferbottom() const {
        assert(m_nHeadBufferSize > 0);
        return m_HeadBuffer[0];
    }
    inline int headbufferitem(const unsigned &index) const {
        assert(index < m_nHeadBufferSize);
        return m_HeadBuffer[index];
    }

    inline int headsetsize() const {
        return m_nHeadSetSize;
    }
    inline bool headsetempty() const {
        return m_nHeadSetSize <= 0;
    }

    inline int actionsize() const {
        return m_nActionSize;
    }
    inline bool actionempty() const {
        return m_nActionSize <= 0;
    }

    inline void setsentsize(int nSentLen) {
        m_nSentLen = nSentLen;
    }

    inline int wordstart(int index) const {
        if (index < m_nQNextWord && index >= 0) {
            int curIndex = index;
            while (!m_lPOSTypes[curIndex] && curIndex >= 0) {
                curIndex--;
            }
            return curIndex;
        } else {
            return -1;
        }
    }

    inline int wordend(int index) const {
        if (index < m_nQNextWord && index >= 0) {
            int curIndex = index + 1;
            while (!m_lPOSTypes[curIndex] && curIndex < m_nQNextWord) {
                curIndex++;
            }
            return curIndex - 1;
        } else {
            return -1;
        }
    }

    //the input index should be a word's end position
    //inline int wordhead(int index) const {
    //    if (index < m_nQNextWord && index >= 0) {
    //        int curIndex = index;
    //        while (!m_lLabelTypes[curIndex] && curIndex >= 0) {
    //            curIndex--;
    //        }
    //        return curIndex;
    //    } else {
    //        return -1;
    //    }
    // }

    inline int subwordstart(int index) const {
        if (index < m_nQNextWord && index >= 0) {
            if (m_lLabelTypes[index]) {
                int curIndex = index;
                while (!m_lPOSTypes[curIndex] && curIndex >= 0) {
                    curIndex--;
                }
                return curIndex;
            } else if (m_lDepsL[index] == -1) {
                return index;
            } else {
                return subwordstart(m_lDepsL[index]);
            }
        } else if(index == m_nQNextWord) {
            if (m_lDepsL[index] == -1) {
                return index;
            } else {
                return subwordstart(m_lDepsL[index]);
            }
        } else {
            return -1;
        }
    }

    inline int subwordend(int index) const {
        if (index < m_nQNextWord && index >= 0) {
            if (m_lLabelTypes[index]) {
                int curIndex = index + 1;
                while (!m_lPOSTypes[curIndex] && curIndex < m_nQNextWord) {
                    curIndex++;
                }
                return curIndex - 1;
            } else if (m_lDepsR[index] == -1) {
                return index;
            } else {
                return subwordend(m_lDepsR[index]);
            }
        } else if(index == m_nQNextWord) {
            return index;
        } else {
            return -1;
        }
    }


    inline int leftinnerfirstchild(int index) const{
         if(index<m_nQNextWord && index >= 0 && m_lInDepsL[index] != -1)
         {
             int curIndex = index-1;
             while( (!m_HeadSet[curIndex] || m_lHeads[curIndex] != index) && curIndex >= m_lInDepsL[index])
             {
                 curIndex--;
             }
             return curIndex;
         }
         else
         {
             return -1;
         }
    }


    inline int rightinnerfirstchild(int index) const{
         if(index<m_nQNextWord && index >= 0 && m_lInDepsR[index] != -1)
         {
             int curIndex = index+1;
             while((!m_HeadSet[curIndex] || m_lHeads[curIndex] != index) && curIndex <= m_lInDepsR[index])
             {
                 curIndex++;
             }
             return curIndex;
         }
         else
         {
             return -1;
         }
    }


    inline int wordindex(int index) const {
        if (index < m_nQNextWord && index >= 0) {
            int count = 0;
            for(int idx = 0; idx <= index; idx++) {
                if(m_lPOSTypes[idx]) {
                    count++;
                }
            }
            return count-1;
        } else {
            return -1;
        }
    }

    inline int head(const int &index) const {
        if (index < m_nQNextWord && index >= 0 && m_HeadSet[index]) {
            return m_lHeads[index];
        } else {
            // this is an error
            return -1;
        }
    }

    inline int pos(const int &index) const {
        if (index <= m_nQNextWord && index >= 0) {
            return m_lPOSs[index];
        } else {
            // this is an error
            return -1;
        }
    }

    inline int leftdep(const int &index) const {
        if (index <= m_nQNextWord && index >= 0) {
            return m_lDepsL[index];
        } else {
            // this is an error
            return -1;
        }
    }
    inline int rightdep(const int &index) const {
        if (index <= m_nQNextWord && index >= 0) {
            return m_lDepsR[index];
        } else {
            // this is an error
            return -1;
        }
    }

    inline int leftindep( const int &index ) const {
        if(index<=m_nQNextWord && index >= 0)
        {
            return m_lInDepsL[index];
        }
        else
        {
            // this is an error
            return -1;
        }
    }
    inline int rightindep( const int &index ) const {
        if(index<=m_nQNextWord && index >= 0)
        {
            return m_lInDepsR[index];
        }
        else
        {
            // this is an error
            return -1;
        }
    }

    inline int sibling(const int &index) const {
        if (index <= m_nQNextWord && index >= 0) {
            return m_lSibling[index];
        } else {
            // this is an error
            return -1;
        }
    }

    inline int nextword() const {
        return m_nNextWord;
    }
    inline int nextqword() const {
        return m_nQNextWord;
    }


    inline int label(const int &index) const {
        if (index < m_nQNextWord && index >= 0 && m_HeadSet[index]) {
            return m_lLabels[index];
        } else {
            // this is an error
            return -1;
        }
    }


    inline int leftarity(const int &index) const {
        assert(index <= m_nQNextWord);
        return m_lDepNumL[index];
    }
    inline int rightarity(const int &index) const {
        assert(index <= m_nQNextWord);
        return m_lDepNumR[index];
    }

    inline int leftinnerarity(const int &index) const {
        assert(index <= m_nQNextWord);
        return m_lInDepNumL[index];
    }
    inline int rightinnerarity(const int &index) const {
        assert(index <= m_nQNextWord);
        return m_lInDepNumR[index];
    }

    inline int leftouterarity(const int &index) const {
        assert(index <= m_nQNextWord && m_lDepNumL[index] >= m_lInDepNumL[index]);
        return m_lDepNumL[index] - m_lInDepNumL[index];
    }

    inline int rightouterarity(const int &index) const {
        assert(index <= m_nQNextWord && m_lDepNumR[index] >= m_lInDepNumR[index]);
        return m_lDepNumR[index] - m_lInDepNumR[index];
    }

    inline const CSetOfTags<CDependencyLabel> & lefttagset(const int &index) const {
        assert(index <= m_nQNextWord);
        return m_lDepTagL[index];
    }

    inline const CSetOfTags<CDependencyLabel> & righttagset(const int &index) const {
        assert(index <= m_nQNextWord);
        return m_lDepTagR[index];
    }

    void clear() {
        m_nNextWord = 0;
        m_nQNextWord = 0;
        m_nStackSize = 0;
        m_nHeadStackSize = 0;
        m_nBufferSize = 0;
        m_nHeadBufferSize = 0;
        m_nBufferWordSize = 0;
        m_nHeadSetSize = 0;
        m_nActionSize = 0;
        score = 0;
        m_nLastAction = action::NO_ACTION;

        ClearNext();
    }


    void ClearNext() {
        m_Stack[m_nStackSize] = -1;
        m_HeadStack[m_nHeadStackSize] = -1;
        m_Buffer[m_nBufferSize] = -1;
        m_HeadBuffer[m_nHeadBufferSize] = -1;
        m_Action[m_nActionSize] = -1;
        m_HeadSet[m_nQNextWord] = false;
        m_lHeads[m_nQNextWord] = CHARDEPENDENCY_LINK_NO_HEAD;
        m_lPOSs[m_nQNextWord] = false;
        m_lPOSTypes[m_nQNextWord] = 0;
        m_lDepsL[m_nQNextWord] = CHARDEPENDENCY_LINK_NO_HEAD;
        m_lDepsR[m_nQNextWord] = CHARDEPENDENCY_LINK_NO_HEAD;
        m_lInDepsL[m_nQNextWord] = CHARDEPENDENCY_LINK_NO_HEAD;
        m_lInDepsR[m_nQNextWord] = CHARDEPENDENCY_LINK_NO_HEAD;
        m_lDepNumL[m_nQNextWord] = 0;
        m_lInDepNumL[m_nQNextWord] = 0;
        m_lDepTagL[m_nQNextWord].clear();
        m_lDepNumR[m_nQNextWord] = 0;
        m_lInDepNumR[m_nQNextWord] = 0;
        m_lDepTagR[m_nQNextWord].clear();
        m_lSibling[m_nQNextWord] = CHARDEPENDENCY_LINK_NO_HEAD;
        m_lLabels[m_nQNextWord] = CDependencyLabel::NONE;
        m_lLabelTypes[m_nQNextWord] = false;
    }



    void operator =(const CStateItem &item) {
        m_nStackSize = item.m_nStackSize;

        for (int i = 0; i < m_nStackSize; i++) {
            m_Stack[i] = item.m_Stack[i];
        }

        m_nHeadStackSize = item.m_nHeadStackSize;

        for (int i = 0; i < m_nHeadStackSize; i++) {
            m_HeadStack[i] = item.m_HeadStack[i];
        }

        m_nBufferSize = item.m_nBufferSize;
        m_nBufferWordSize = item.m_nBufferWordSize;

        for (int i = 0; i < m_nBufferSize; i++) {
            m_Buffer[i] = item.m_Buffer[i];
        }

        m_nHeadBufferSize = item.m_nHeadBufferSize;

        for (int i = 0; i < m_nHeadBufferSize; i++) {
            m_HeadBuffer[i] = item.m_HeadBuffer[i];
        }

        m_nActionSize = item.m_nActionSize;

        for (int i = 0; i < m_nActionSize; i++) {
            m_Action[i] = item.m_Action[i];
        }

        m_nHeadSetSize = item.m_nHeadSetSize;
        m_nNextWord = item.m_nNextWord;
        m_nQNextWord = item.m_nQNextWord;

        m_nLastAction = item.m_nLastAction;
        m_nSentLen = item.m_nSentLen;
        score = item.score;
        for (int i = 0; i <= m_nQNextWord+1; ++i) { // only copy active word (including m_nNext)
            m_HeadSet[i] = item.m_HeadSet[i];
            {
                m_lHeads[i] = item.m_lHeads[i];
                m_lLabels[i] = item.m_lLabels[i];
                m_lLabelTypes[i] = item.m_lLabelTypes[i];
            }
            m_lPOSs[i] = item.m_lPOSs[i];
            m_lPOSTypes[i] = item.m_lPOSTypes[i];
            m_lDepsL[i] = item.m_lDepsL[i];
            m_lDepsR[i] = item.m_lDepsR[i];
            m_lInDepsL[i] = item.m_lInDepsL[i];
            m_lInDepsR[i] = item.m_lInDepsR[i];
            m_lDepNumL[i] = item.m_lDepNumL[i];
            m_lDepNumR[i] = item.m_lDepNumR[i];
            m_lInDepNumL[i] = item.m_lInDepNumL[i];
            m_lInDepNumR[i] = item.m_lInDepNumR[i];
            m_lDepTagL[i] = item.m_lDepTagL[i];
            m_lDepTagR[i] = item.m_lDepTagR[i];
            m_lSibling[i] = item.m_lSibling[i];
        }

    }

    //-----------------------------------------------------------------------------

public:

    bool BeNextStepDep() const {
        if ( m_nBufferWordSize == action::max_buffer_size
                || (m_nQNextWord == m_nSentLen && (m_nBufferSize == 0 || m_lLabelTypes[m_Buffer[m_nBufferSize - 1]]))) {
            assert(m_nBufferWordSize == m_nBufferSize);
            return true;
        } else {
            return false;
        }
    }


    bool CanArcOut() const {
        if (BeNextStepDep()
                && m_nStackSize > 0 && m_nBufferWordSize > 0
                && m_lLabelTypes[m_Stack[m_nStackSize - 1]] && m_lLabelTypes[m_Buffer[0]] ) // buffer all words
        {
            return true;
        } else {
            return false;
        }
    }

    bool CanArcRightOut() const {
        if(CanArcOut() && (m_nHeadStackSize == 1  || wordend(m_nNextWord) < m_nSentLen-1)) {
            return true;
        } else {
            return false;
        }
    }

    bool CanArcLeftOut() const {
        if(CanArcOut() && !m_HeadSet[m_Stack[m_nStackSize-1]]) {
            return true;
        } else {
            return false;
        }
    }

    bool CanReduceOut() const {
        if( BeNextStepDep() && m_nStackSize > 0 && m_HeadSet[m_Stack[m_nStackSize-1]]
                && ( m_nNextWord < m_nSentLen
                     || (m_nNextWord == m_nSentLen && m_nStackSize > 1) ) ) {
            return true;
        } else {
            return false;
        }
    }


    bool CanArcIn() const {
        if (!BeNextStepDep()
                && m_nBufferSize > 0 && m_nQNextWord < m_nSentLen
                && !m_lLabelTypes[m_Buffer[m_nBufferSize - 1]]) {
            return true;
        } else {
            return false;
        }
    }

    bool CanArcRightIn() const {
        if(CanArcIn() && (m_nHeadBufferSize == 1  || m_nQNextWord < m_nSentLen-1)) {
            return true;
        } else {
            return false;
        }
    }

    bool CanArcLeftIn() const {
        if(CanArcIn() && !m_HeadSet[m_Buffer[m_nBufferSize-1]]) {
            return true;
        } else {
            return false;
        }
    }

    bool CanReduceIn() const {
        if( !BeNextStepDep() && m_nBufferSize > 0 && m_HeadSet[m_Buffer[m_nBufferSize-1]]
                && ( m_nQNextWord < m_nSentLen
                     || (m_nQNextWord == m_nSentLen && m_nBufferSize > 1) ) ) {
            return true;
        } else {
            return false;
        }
    }

    bool CanShiftIn() const {
        if (!BeNextStepDep() && m_nQNextWord < m_nSentLen && (m_nBufferSize == 0 || m_nQNextWord < m_nSentLen-1 || m_lLabelTypes[m_Buffer[m_nBufferSize - 1]])
                && m_nActionSize > 0
                && m_nLastAction != action::REDUCE_IN && m_nLastAction != action::POP_WORD && !action::isDepOperation(m_nLastAction)) {
            return true;
        } else {
            return false;
        }
    }


    bool CanShiftPos() const {
        if (!BeNextStepDep() && m_nQNextWord < m_nSentLen && m_lInDepNumL[m_nQNextWord] == 0
                && (m_nBufferSize == 0 || m_nQNextWord < m_nSentLen-1|| m_lLabelTypes[m_Buffer[m_nBufferSize - 1]])
                && (m_nActionSize == 0 || m_nLastAction == action::POP_WORD || action::isDepOperation(m_nLastAction))) {
            return true;
        } else {
            return false;
        }
    }

    bool CanShiftOut() const {
        if (BeNextStepDep() && m_nLastAction != action::REDUCE && m_nBufferWordSize > 0 && (m_nStackSize == 0 || wordend(m_nNextWord) < m_nSentLen-1) )
            // buffersize > 0 and all words are formed
        {
            return true;
        } else {
            return false;
        }
    }

    bool CanPopWord() const {
        if (!BeNextStepDep() && m_nBufferSize > 0 && !m_lLabelTypes[m_Buffer[m_nBufferSize - 1]]
                && (m_nQNextWord == m_nSentLen || m_lInDepNumL[m_nQNextWord] == 0)
                && (m_nBufferSize == 1 || m_lLabelTypes[m_Buffer[m_nBufferSize - 2]])) {
            return true;
        } else {
            return false;
        }
    }

    bool CanPopRoot() const {
        if (m_nBufferSize == 0 && m_nStackSize == 1 && m_nNextWord == m_nQNextWord && m_nHeadSetSize == m_nNextWord - 1 && m_lLabelTypes[m_Stack[m_nStackSize - 1]] && m_nNextWord == m_nSentLen) {
            return true;
        } else {
            return false;
        }
    }


    // the arc left action links the current stack top to the next word with popping
    void ArcLeftOut(unsigned long lab) {
        assert( CanArcLeftOut()) ;
        static int left, right ;
        left = m_Stack[m_nStackSize-1] ;
        right = m_Buffer[0];
        m_nStackSize-- ;
        m_nHeadStackSize--;
        m_HeadSet[left] = true;
        m_nHeadSetSize++;
        m_lHeads[left] = right;
        m_lLabels[left] = lab;
        m_lDepTagL[right].add(lab) ;
        m_lSibling[left] = m_lDepsL[right];
        m_lDepsL[right] = left ;
        m_lDepNumL[right] ++ ;
        m_nLastAction=action::encodeAction(action::ARC_LEFT, lab);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;

        m_Stack[m_nStackSize] = -1;
        m_HeadStack[m_nHeadStackSize] = -1;
        m_Action[m_nActionSize] = -1;
    }

    // the arc right action links the next word to the current stack top with pushing
    void ArcRightOut(unsigned long lab) {
        assert( CanArcRightOut()) ;
        static int left , right;
        left = m_Stack[m_nStackSize-1] ;
        right = m_Buffer[0];
        m_nStackSize++;
        m_Stack[m_nStackSize-1] = right;
        m_lHeads[right] = left ;
        m_HeadSet[right] = true;
        m_nHeadSetSize++;
        m_lLabels[right] = lab ;
        m_lDepTagR[left].add(lab) ;
        m_lSibling[right] = m_lDepsR[left];
        m_lDepsR[left] = right ;
        m_lDepNumR[left] ++ ;
        m_Buffer[0] = -1;
        for(int idx = 0; idx < m_nBufferSize -1; idx++) {
            m_Buffer[idx] = m_Buffer[idx+1];
        }
        m_nBufferSize--;
        m_nBufferWordSize--;
        m_nNextWord  = wordend(right) + 1;

        m_nLastAction=action::encodeAction(action::ARC_RIGHT, lab);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;

        m_Stack[m_nStackSize] = -1;
        m_Buffer[m_nBufferSize] = -1;
        m_Action[m_nActionSize] = -1;
    }

    // the shift action does pushing
    void ShiftOut(unsigned long lab) {
        assert( CanShiftOut()) ;
        m_nStackSize++;
        m_Stack[m_nStackSize-1] = m_Buffer[0];
        m_nHeadStackSize++;
        m_HeadStack[m_nHeadStackSize-1] = m_Buffer[0];
        m_nNextWord = wordend(m_Buffer[0])+1;
        m_Buffer[0] = -1;
        for(int idx = 0; idx < m_nBufferSize -1; idx++) {
            m_Buffer[idx] = m_Buffer[idx+1];
        }
        m_nBufferSize--;
        m_nBufferWordSize--;


        m_nLastAction=action::encodeAction(action::SHIFT);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;

        m_Stack[m_nStackSize] = -1;
        m_HeadStack[m_nHeadStackSize] = -1;
        m_Buffer[m_nBufferSize] = -1;
        m_Action[m_nActionSize] = -1;
    }

    // the reduce action does popping
    void ReduceOut(unsigned long lab) {
        if( !CanReduceOut() ) {
            std::cout << "ReduceOut Error" << std::endl;
        }
        m_nStackSize-- ;
        m_nLastAction=action::encodeAction(action::REDUCE);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;

        m_Stack[m_nStackSize] = -1;
        m_Action[m_nActionSize] = -1;

    }

    // the arc left action links the current stack top to the next word with popping
    void ArcLeftIn(unsigned long lab) {
        assert( CanArcLeftIn() && lab == 0) ;
        static int left, right ;
        left = m_Buffer[m_nBufferSize-1] ;
        right = m_nQNextWord;
        m_nBufferSize-- ;
        m_nHeadBufferSize--;
        m_HeadSet[left] = true;
        m_nHeadSetSize++;
        m_lHeads[left] = right;
        m_lLabels[left] = lab;
        m_lDepTagL[right].add(lab) ;
        m_lSibling[left] = m_lDepsL[right];
        m_lDepsL[right] = left ;
        m_lInDepsL[right] = left ;
        m_lInDepNumL[right]++;
        m_lDepNumL[right] ++ ;
        m_nLastAction=action::encodeAction(action::ARC_LEFT_IN, lab);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;

        m_Buffer[m_nBufferSize] = -1;
        m_HeadBuffer[m_nHeadBufferSize] = -1;
        m_Action[m_nActionSize] = -1;
    }


    // the arc right action links the next word to the current stack top with pushing
    void ArcRightIn(unsigned long lab) {
        assert( CanArcRightIn()) ;
        static int left , right;
        left = m_Buffer[m_nBufferSize-1] ;
        right = m_nQNextWord;
        m_nBufferSize++;
        m_Buffer[m_nBufferSize-1] = right;
        m_lHeads[right] = left ;
        m_HeadSet[right] = true;
        m_nHeadSetSize++;
        m_lLabels[right] = lab ;
        m_lDepTagR[left].add(lab) ;
        m_lSibling[right] = m_lDepsR[left];
        m_lDepsR[left] = right ;
        m_lInDepsR[left] = right ;
        m_lInDepNumR[left] ++ ;
        m_lDepNumR[left] ++ ;

        m_lPOSs[m_nQNextWord] = m_lPOSs[m_nQNextWord-1];
        m_lPOSTypes[m_nQNextWord] = false;
        m_nQNextWord++;

        m_nLastAction=action::encodeAction(action::ARC_RIGHT_IN, lab);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;

        ClearNext();
    }


    // the shift action does pushing
    void ShiftIn(unsigned long lab) {
        assert( CanShiftIn() && lab == 0) ;
        m_nBufferSize++;
        m_Buffer[m_nBufferSize-1] = m_nQNextWord;
        m_nHeadBufferSize++;
        m_HeadBuffer[m_nHeadBufferSize-1] = m_nQNextWord;
        m_lPOSs[m_nQNextWord] = m_lPOSs[m_nQNextWord-1];
        m_lPOSTypes[m_nQNextWord] = false;
        m_nQNextWord ++;

        m_nLastAction=action::encodeAction(action::SHIFT_IN);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;
        ClearNext();

    }

    // the shift action does pushing
    void ShiftPos(unsigned long lab) {
        if (!CanShiftPos()) {
            std::cout << "ShiftPos error" << std::endl;
        }
        assert(lab > 0);
        m_nBufferSize++;
        m_Buffer[m_nBufferSize - 1] = m_nQNextWord;
        m_nHeadBufferSize++;
        m_HeadBuffer[m_nHeadBufferSize-1] = m_nQNextWord;
        m_lPOSs[m_nQNextWord] = lab;
        m_lPOSTypes[m_nQNextWord] = true;
        m_nQNextWord++;
        m_nLastAction = action::encodeAction(action::SHIFT, lab);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;
        ClearNext();
    }


    // the reduce action does popping
    void ReduceIn(unsigned long lab) {
        if( !CanReduceIn() ) {
            std::cout << "ReduceIn Error" << std::endl;
        }
        m_nBufferSize-- ;
        m_nLastAction=action::encodeAction(action::REDUCE_IN);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;

        m_Buffer[m_nBufferSize] = -1;
        m_Action[m_nActionSize] = -1;

    }

    // this is used for the convenience of scoring and updating
    void PopWord() {
        //do nothing
        if (!CanPopWord()) {
            std::cout << "PopWord error" << std::endl;
        }
        static int top0, top1;
        top0 = m_Buffer[m_nBufferSize - 1];
        m_nBufferWordSize++;
        m_nHeadBufferSize = 0;
        m_lLabelTypes[top0] = true;
        m_nLastAction = action::encodeAction(action::POP_WORD);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;
        ClearNext();
    }

    // this is used for the convenience of scoring and updating
    void PopRoot() {
        if (!CanPopRoot()) {
            std::cout << "PopRoot error" << std::endl;
        }
        m_lLabels[m_Stack[m_nStackSize - 1]] = CDependencyLabel::ROOT;
        m_nLastAction = action::encodeAction(action::POP_ROOT);
        m_HeadSet[m_Stack[m_nStackSize - 1]] = true;
        m_nHeadSetSize++;
        //m_nStackSize-- ; // pop it
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;
        ClearNext();
    }

    void Idle() {
        assert(IsTerminated());
        m_nLastAction = action::encodeAction(action::IDLE);
        m_Action[m_nActionSize] = m_nLastAction;
        m_nActionSize++;
        ClearNext();
    }



    // the move action is a simple call to do action according to the action code
    void Move(const unsigned long &ac) {
        static unsigned long lab;
        lab = action::getLabel(ac);
        switch (action::getUnlabeledAction(ac)) {
        case action::NO_ACTION:
            return;
        case action::SHIFT:
            if (lab == 0) {
                ShiftOut(0);
            } else if (lab > 0) {
                ShiftPos(lab);
            }
            return;
        case action::ARC_LEFT:
            ArcLeftOut(lab);
            return;
        case action::ARC_RIGHT:
            ArcRightOut(lab);
            return;
        case action::REDUCE:
            ReduceOut(0);
            return;
        case action::POP_ROOT:
            PopRoot();
            return;
        case action::IDLE:
            Idle();
            return;
        case action::POP_WORD:
            PopWord();
            return;
        case action::SHIFT_IN:
            ShiftIn(0);
            return;
        case action::ARC_LEFT_IN:
            ArcLeftIn(0);
            return;
        case action::ARC_RIGHT_IN:
            ArcRightIn(0);
            return;
        case action::REDUCE_IN:
            ReduceIn(0);
            return;
        default:
            THROW("unknown action: " << ac << '.');
        }
    }

    //-----------------------------------------------------------------------------

public:

    // returns true is the next word advances -- by shift or arcright.

    bool StandardMoveStep(const CDependencyParse &tree, const std::vector<
                          CDependencyLabel>&m_lCacheLabel) {
        static int left, right;
        //if(this->m_nActionSize == 21)
        //{
        //    std::cout << "start debug" << std::endl;
        //}
        if (IsTerminated()) {
            Idle();
            return false;
        } else if (BeNextStepDep()) {
            if ( m_nNextWord == static_cast<int>(tree.size()) ) {
                assert( m_nStackSize > 0 );
                if ( m_nStackSize > 1 ) {
                    ReduceOut(0);
                    return false;
                } else {
                    PopRoot();
                    return false;
                }
            }

            if(m_nBufferSize > 0) {}
            else {
                std::cout << "assert error:  m_nBufferSize > 0 " << std::endl;
            }
            right = m_Buffer[0];
            // the first case is that there is some words on the stack linking to nextword
            if ( m_nStackSize > 0 ) {
                left = m_Stack[m_nStackSize-1];
                while (m_HeadSet[left])
                    left = m_lHeads[left];
                if ( tree[left].head == right ) {    // if a local head deps on nextword first
                    if ( left == m_Stack[m_nStackSize-1] ) {
                        assert(m_lCacheLabel[left].str() == tree[left].label);
                        ArcLeftOut(m_lCacheLabel[left].code()); // link it to the next word
                        return false;
                    } else {
                        ReduceOut(0);
                        return false;
                    }
                }
            }
            // the second case is that no words on the stack links nextword, and nextword does not link to stack word
            if ( tree[right].head == CHARDEPENDENCY_LINK_NO_HEAD || // the root or
                    tree[right].head > right ) { // head on the right
                ShiftOut(0);
                return true;
            }
            // the last case is that the next words links to stack word
            else {                                        // head on the left
                assert( m_nStackSize > 0 );
                left = m_Stack[m_nStackSize-1];
                if ( tree[right].head == left ) {     // the next word deps on stack left
                    assert(m_lCacheLabel[right].str()==tree[right].label);
                    ArcRightOut(m_lCacheLabel[right].code());
                    return true;
                } else {                                     // must depend on non-immediate h
                    ReduceOut(0);
                    return false;
                }
            }

        } else {

            if ( m_nQNextWord == static_cast<int>(tree.size()) || tree[m_nQNextWord].tagtype.compare("b") == 0) {
                if( (m_nBufferSize == 0 || m_lLabelTypes[m_Buffer[m_nBufferSize-1]])
                        && m_nQNextWord < static_cast<int>(tree.size())) {
                    ShiftPos(CTag(tree[m_nQNextWord].tag).code());
                    return true;
                } else {
                    // the buffer tree number that belong to current word exceeds one
                    if ( m_nBufferSize > 1 && !m_lLabelTypes[m_Buffer[m_nBufferSize-2]]) {
                        ReduceIn(0);
                        return false;
                    } else {
                        PopWord();
                        return false;
                    }
                }
            }
            right = m_nQNextWord;
            // the first case is that there is some words on the stack linking to nextword
            if ( m_nBufferSize > 0 && !m_lLabelTypes[m_Buffer[m_nBufferSize-1]]) {
                left = m_Buffer[m_nBufferSize-1];
                while (m_HeadSet[left])
                    left = m_lHeads[left];
                if ( tree[left].head == right ) {    // if a local head deps on nextword first
                    if ( left == m_Buffer[m_nBufferSize-1] ) {
                        assert(m_lCacheLabel[left].str() == tree[left].label);
                        ArcLeftIn(m_lCacheLabel[left].code()); // link it to the next word
                        return false;
                    } else {
                        ReduceIn(0);
                        return false;
                    }
                }
            }
            // the second case is that no words on the stack links nextword, and nextword does not link to stack word
            if ( tree[right].labeltype.compare("out") == 0 || // the root or
                    tree[right].head > right ) { // head on the right
                ShiftIn(0);
                return true;
            }
            // the last case is that the next words links to stack word
            else {                                        // head on the left
                if( m_nBufferSize > 0  && !m_lLabelTypes[m_Buffer[m_nBufferSize-1]]) {}
                else {
                    std::cout << "assert error:  m_nBufferSize > 0  && !m_lLabelTypes[m_Buffer[m_nBufferSize-1]]"  << std::endl;
                }
                left = m_Buffer[m_nBufferSize-1];
                if ( tree[right].head == left ) {     // the next word deps on stack left
                    assert(m_lCacheLabel[right].str()==tree[right].label);
                    ArcRightIn(m_lCacheLabel[right].code());
                    return true;
                } else {                                     // must depend on non-immediate h
                    ReduceIn(0);
                    return false;
                }
            }

        }
    }

    // we want to pop the root item after the whole tree done
    // on the one hand this seems more natural
    // on the other it is easier to score
    //bool StandardFinish() {
    //   return ( m_nStackSize == 0 && m_nNextWord == m_nSentLen);
    //}

    bool IsTerminated() const {
        return m_nLastAction == action::POP_ROOT or m_nLastAction == action::IDLE;
    }

    bool IsIdle() const {
        return m_nLastAction == action::IDLE;
    }

    unsigned FollowMove(const CStateItem *item) {
        //if(m_nSentLen == 66 && m_nActionSize == 11)
        //{
        //    std::cout << "start debug...." << std::endl;
        //}
        static int left, right;
        // if the next words are same then don't check head because it might be a finished sentence (m_nNextWord==sentence.sz)
        if (IsTerminated()) {
            return action::encodeAction(action::IDLE);
        } else if (BeNextStepDep()) {
            if ( m_nNextWord == item->m_nNextWord ) {
                left = m_Stack[m_nStackSize-1];
                right = m_Buffer[0];
                if(item->m_lHeads[left] == CHARDEPENDENCY_LINK_NO_HEAD) {
                    return action::encodeAction(action::POP_ROOT);
                } else {
                    assert( m_nStackSize > item->m_nStackSize );
                    if ( item->m_lHeads[left] == right )
                        return action::encodeAction(action::ARC_LEFT, item->m_lLabels[left]);
                    else
                        return action::encodeAction(action::REDUCE);
                }

            }
            // the first case is that there is some words on the stack linking to nextword
            assert(m_nBufferSize > 0);
            right = m_Buffer[0];
            if ( m_nStackSize > 0 ) {
                left = m_Stack[m_nStackSize-1];
                while (m_HeadSet[left])
                    left = m_lHeads[left];
                if ( item->head(left) == right ) {    // if a local head deps on nextword first
                    if ( left == m_Stack[m_nStackSize-1] ) {
                        return action::encodeAction(action::ARC_LEFT, item->m_lLabels[left]);
                    } else {
                        return action::encodeAction(action::REDUCE);
                    }
                }
            }
            // the second case is that no words on the stack links nextword, and nextword does not link to stack word
            if ( item->head(right) == CHARDEPENDENCY_LINK_NO_HEAD || // the root or
                    item->head(right) > right ) { // head on the right
                return action::encodeAction(action::SHIFT);
            }
            // the last case is that the next words links to stack word
            else {                                        // head on the left
                if( m_nStackSize > 0 ) {}
                else {
                    std::cout << "assert error:  m_nStackSize > 0"  << std::endl;
                }
                left = m_Stack[m_nStackSize-1];
                if ( item->head(right) == left ) {    // the next word deps on stack left
                    return action::encodeAction(action::ARC_RIGHT, item->m_lLabels[right]);
                } else {                                     // must depend on non-immediate h
                    return action::encodeAction(action::REDUCE);
                }
            }
        } else {
            if (m_nQNextWord == m_nSentLen || item->m_lPOSTypes[m_nQNextWord]) {
                if( (m_nBufferSize == 0 || m_lLabelTypes[m_Buffer[m_nBufferSize-1]])
                        && m_nQNextWord < m_nSentLen) {
                    return action::encodeAction(action::SHIFT, item->m_lPOSs[m_nQNextWord]);
                } else {
                    if ( m_nBufferSize > 1 && !m_lLabelTypes[m_Buffer[m_nBufferSize-2]]) {
                        return action::encodeAction(action::REDUCE_IN);
                    } else {
                        return action::encodeAction(action::POP_WORD);
                    }
                }
            }
            right = m_nQNextWord;
            if ( m_nQNextWord == item->m_nQNextWord ) {

                //assert( m_nBufferSize > item->m_nBufferSize );
                left = m_Buffer[m_nBufferSize-1];
                if (item->m_lLabelTypes[left]) {
                    return action::encodeAction(action::POP_WORD);
                } else {
                    if ( item->m_lHeads[left] == right ) {
                        return action::encodeAction(action::ARC_LEFT_IN);
                    } else {
                        assert(item->m_HeadSet[left]);
                        return action::encodeAction(action::REDUCE_IN);
                    }
                }
            }
            // the first case is that there is some words on the stack linking to nextword
            if ( m_nBufferSize > 0 && !m_lLabelTypes[m_Buffer[m_nBufferSize-1]]) {
                left = m_Buffer[m_nBufferSize-1];
                while (m_HeadSet[left])
                    left = m_lHeads[left];
                if ( item->head(left) == right ) {    // if a local head deps on nextword first
                    if ( left == m_Buffer[m_nBufferSize-1] ) {
                        return action::encodeAction(action::ARC_LEFT_IN);
                    } else {
                        return action::encodeAction(action::REDUCE_IN);
                    }
                }
            }
            // the second case is that no words on the stack links nextword, and nextword does not link to stack word
            if ( item->m_lLabelTypes[right] || item->head(right) == CHARDEPENDENCY_LINK_NO_HEAD || // the root or
                    item->head(right) > right ) { // head on the right
                return action::encodeAction(action::SHIFT_IN);
            }
            // the last case is that the next words links to stack word
            else {                                        // head on the left
                if( m_nBufferSize > 0 && !m_lLabelTypes[m_Buffer[m_nBufferSize-1]]) {}
                else {
                    std::cout << "assert error:  m_nBufferSize > 0 && !m_lLabelTypes[m_Buffer[m_nBufferSize-1]]"  << std::endl;
                }
                left = m_Buffer[m_nBufferSize-1];
                if ( item->head(right) == left ) {    // the next word deps on stack left
                    return action::encodeAction(action::ARC_RIGHT_IN);
                } else {                                     // must depend on non-immediate h
                    return action::encodeAction(action::REDUCE_IN);
                }
            }
        }

    }

    void GenerateTree(const CStringVector &input, CDependencyParse &output) const {
        output.clear();
        for (int i = 0; i < nextword(); ++i)
            output.push_back(CCharDependencyTreeNode(input.at(i), CTag(m_lPOSs[i]).str(),
                             m_lPOSTypes[i] ? "b" : "i", m_lHeads[i], CDependencyLabel(m_lLabels[i]).str(),
                             m_lLabelTypes[i] ? "out" : "in"));
    }

};

inline std::ostream & operator << (std::ostream &os, const CStateItem &item) {
    os << "m_nStackSize:" << item.m_nStackSize << std::endl;

    os << "m_Stack:" << std::endl;
    for (int i = 0; i < item.m_nStackSize; i++) {
        os << i << ":" << item.m_Stack[i] << " ";
    }
    os << std::endl;

    os << "m_nHeadStackSize:" << item.m_nStackSize << std::endl;

    os << "m_HeadStack:" << std::endl;

    for (int i = 0; i < item.m_nHeadStackSize; i++) {
        os << i << ":" << item.m_HeadStack[i] << " ";
    }
    os << std::endl;

    os << "m_nBufferSize:" << item.m_nBufferSize << std::endl;
    os << "m_nBufferWordSize:" << item.m_nBufferWordSize << std::endl;

    for (int i = 0; i < item.m_nBufferSize; i++) {
        os << i << ":" << item.m_Buffer[i] << " ";
    }
    os << std::endl;

    os << "m_nHeadBufferSize:" << item.m_nHeadBufferSize << std::endl;

    for (int i = 0; i < item.m_nHeadBufferSize; i++) {
        os << i << ":" << item.m_HeadBuffer[i] << " ";
    }
    os << std::endl;

    os << "m_nActionSize:" << item.m_nActionSize << std::endl;

    for (int i = 0; i < item.m_nActionSize; i++) {
        os << i << ":" << item.m_Action[i] << " ";
    }
    os << std::endl;

    os << "m_nHeadSetSize:" << item.m_nHeadSetSize << std::endl;
    os << "m_nNextWord:" << item.m_nNextWord << std::endl;
    os << "m_nQNextWord:" << item.m_nQNextWord << std::endl;

    os << "m_nLastAction:" << item.m_nLastAction << std::endl;
    os << "m_nSentLen:" << item.m_nSentLen << std::endl;
    os << "score:" << item.score << std::endl;
    for (int i = 0; i <= item.m_nQNextWord+1; ++i) { // only copy active word (including m_nNext)
        os << i  << " m_HeadSet:" << item.m_HeadSet[i] << " ";
        {
            os << " m_lHeads:" << item.m_lHeads[i] << " ";
            os << " m_lLabels:" << item.m_lLabels[i] << " ";
            os << " m_lLabelTypes:" << item.m_lLabelTypes[i] << " ";
        }
        os << "m_lPOSs:" << item.m_lPOSs[i] << " ";
        os << "m_lPOSTypes:" << item.m_lPOSTypes[i] << " ";
        os << "m_lDepsL:" << item.m_lDepsL[i] << " ";
        os << "m_lDepsR:" << item.m_lDepsR[i] << " ";
        os << "m_lDepNumL:" << item.m_lDepNumL[i] << " ";
        os << "m_lDepNumR:" << item.m_lDepNumR[i] << " ";
        os << "m_lInDepNumL:" << item.m_lInDepNumL[i] << " ";
        os << "m_lInDepNumR:" << item.m_lInDepNumR[i] << " ";
        os << "m_lDepTagL:" << item.m_lDepTagL[i] << " ";
        os << "m_lDepTagR:" << item.m_lDepTagR[i] << " ";
        os << "m_lSibling:" << item.m_lSibling[i] << std::endl;;
    }

}

#endif
