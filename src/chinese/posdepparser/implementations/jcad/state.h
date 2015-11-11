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
   enum STACK_STATUS { OFF_STACK=0, ON_STACK_SHIFT, ON_STACK_ARCRIGHT } ;

public:
   int m_Stack[MAX_SENTENCE_SIZE];                     // stack of words that are currently processed
   int m_nStackSize;
   bool m_HeadSet[MAX_SENTENCE_SIZE];                     // stack of words that already have heads
   int m_nHeadSetSize;
   int m_Action[3*MAX_SENTENCE_SIZE];
   int m_nActionSize;
   int m_nNextWord;                         // index for the next word
   int m_lHeads[MAX_SENTENCE_SIZE];         // the lexical head for each word
   int m_lDepsL[MAX_SENTENCE_SIZE];         // the leftmost dependency for each word (just for cache, temporary info), if have outer dep, always point outer dep
   int m_lDepsR[MAX_SENTENCE_SIZE];         // the rightmost dependency for each word (just for cache, temporary info), if have outer dep, always point outer dep
   int m_lInDepsL[MAX_SENTENCE_SIZE];         // the leftmost dependency for each word (just for cache, temporary info), if have outer dep, always point outer dep
   int m_lInDepsR[MAX_SENTENCE_SIZE];         // the rightmost dependency for each word (just for cache, temporary info), if have outer dep, always point outer dep
   int m_lDepNumL[MAX_SENTENCE_SIZE];       // the number of left dependencies
   int m_lDepNumR[MAX_SENTENCE_SIZE];       // the number of right dependencies
   int m_lInDepNumL[MAX_SENTENCE_SIZE];       // the number of left inner dependencies
   int m_lInDepNumR[MAX_SENTENCE_SIZE];       // the number of right inner dependencies
   CSetOfTags<CDependencyLabel> m_lDepTagL[MAX_SENTENCE_SIZE]; // the set of left tags, only for head char of words (we do not have inner dep labels)
   CSetOfTags<CDependencyLabel> m_lDepTagR[MAX_SENTENCE_SIZE]; // the set of right tags, only for head char of words (we do not have inner dep labels)
   int m_lSibling[MAX_SENTENCE_SIZE];       // the sibling towards head, word-level sibling is always prior
   unsigned long m_lLabels[MAX_SENTENCE_SIZE];   // the label of each dependency link
   //false denotes inner word, true denotes outer word
   bool m_lLabelTypes[MAX_SENTENCE_SIZE];   // the label of each dependency link
   unsigned long m_nLastAction;                  // the last stack action
   int m_nSentLen;
   unsigned long m_lPOSs[MAX_SENTENCE_SIZE];
   //true denotes word start, otherwise false
   bool m_lPOSTypes[MAX_SENTENCE_SIZE];

public:
   SCORE_TYPE score;                        // score of stack - predicting how potentially this is the correct one

public:
   // constructors and destructor
   CStateItem(int nSentLen = 0) : m_nSentLen(nSentLen) { clear(); }
   ~CStateItem() { }
   CStateItem(CStateItem& item) : m_nSentLen(0) { std::cerr<<"CStateItem does not support copy constructor!"; std::cerr.flush(); assert(1==0); }

public:
   // comparison
   inline bool operator < (const CStateItem &item) const { return score < item.score; }
   inline bool operator > (const CStateItem &item) const { return score > item.score; }
   inline bool operator == (const CStateItem &item) const {
      int i;
      if ( m_nNextWord != item.m_nNextWord )
         return false;
      for ( i=0; i<m_nNextWord; ++i ) {
         if ( m_lPOSs[i] != item.m_lPOSs[i])
            return false;
         if ( m_lPOSTypes[i] != item.m_lPOSTypes[i])
            return false;
      }

      if ( m_nStackSize != item.m_nStackSize )
         return false;
      if ( m_nStackSize>0 )
      {
    	  for( int i = 0; i < m_nStackSize; i++)
    	  {
    		  if (m_Stack[i] != item.m_Stack[i])
    		  {
    			  return false;
    		  }
    	  }
      }

      if ( m_nActionSize != item.m_nActionSize )
         return false;
      if ( m_nActionSize>0 )
      {
    	  for( int i = 0; i < m_nActionSize; i++)
    	  {
    		  if (m_Action[i] != item.m_Action[i])
    		  {
    			  return false;
    		  }
    	  }
      }

      if ( m_nHeadSetSize != item.m_nHeadSetSize )
         return false;
      if ( m_nHeadSetSize>0 )
      {
    	  for(int i = 0; i < m_nNextWord; i++)
    	  {
    		  if (m_HeadSet[i] != item.m_HeadSet[i])
    		  {
    			  return false;
    		  }
    		  if(m_HeadSet[i])
    		  {
				  if(m_lHeads[i] != item.m_lHeads[i])
				  {
					  return false;
				  }

#ifdef LABELED
				 if ( m_lLabels[i] != item.m_lLabels[i] )
				 {
					return false;
				 }
				 if ( m_lLabelTypes[i] != item.m_lLabelTypes[i] )
				 {
					return false;
				 }
#endif
    		  }
    		  else
    		  {
				  if(m_lHeads[i] != item.m_lHeads[i])
				  {
					  return false;
				  }

#ifdef LABELED
				 if ( m_lLabels[i] != item.m_lLabels[i] )
				 {
					return false;
				 }
				 if ( m_lLabelTypes[i] != item.m_lLabelTypes[i] )
				 {
					return false;
				 }
#endif
    		  }
    	  }
      }

      // I think that the stacks don't have to be compared
      // might be proved by translating tree to stack
      //assert( m_Stack == item.m_Stack );
      return true;
   }

   inline bool operator != (const CStateItem &item) const {
      return ! ((*this)==item);
   }

   // propty
   inline int stacksize() const { return m_nStackSize; }
   inline bool stackempty() const { return m_nStackSize<=0; }
   inline int stacktop() const {
	   if(m_nStackSize<=0)
	   {
		   std::cout << "error" << std::endl;
	   }
	   return m_Stack[m_nStackSize-1];
   }
   inline int stackbottom() const { assert(m_nStackSize>0); return m_Stack[0]; }
   inline int stackitem( const unsigned &index ) const { assert(index<m_nStackSize); return m_Stack[index]; }

   inline int headsetsize() const { return m_nHeadSetSize; }
   inline bool headsetempty() const { return m_nHeadSetSize <= 0; }

   inline int actionsize() const { return m_nActionSize; }
   inline bool actionempty() const { return m_nActionSize <= 0; }

   inline void setsentsize(int nSentLen)
   {
	   m_nSentLen = nSentLen;
   }

   inline int wordstart(int index) const {
	   if(index<m_nNextWord && index >= 0)
	   {
		   int curIndex = index;
		   while(!m_lPOSTypes[curIndex] && curIndex >= 0)
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

   inline int wordend(int index) const {
	   if(index<m_nNextWord && index >= 0)
	   {
		   int curIndex = index + 1;
		   while(!m_lPOSTypes[curIndex] && curIndex < m_nNextWord)
		   {
			   curIndex++;
		   }
		   return curIndex-1;
	   }
	   else
	   {
		   return -1;
	   }
   }


   inline int wordindex(int index) const {
       if (index < m_nNextWord && index >= 0) {
           int count = 0;
           for(int idx = 0; idx <= index; idx++)
           {
               if(m_lPOSTypes[idx])
               {
                   count++;
               }
           }
           return count-1;
       }
       else
       {
           return -1;
       }
   }

   //the input index should be a word's end position
   inline int wordhead(int index) const{
	   if(index<m_nNextWord && index >= 0)
	   {
		   int curIndex = index;
		   while(!m_lLabelTypes[curIndex] && curIndex >= 0)
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


   inline int subwordstart(int index) const {
	   if(index<m_nNextWord && index >= 0)
	   {
		   if(m_lLabelTypes[index])
		   {
			   int curIndex = index;
			   while(!m_lPOSTypes[curIndex] && curIndex >= 0)
			   {
				   curIndex--;
			   }
			   return curIndex;
		   }
		   else if (m_lDepsL[index] == -1)
		   {
			   return  index ;
		   }
		   else
		   {
			   return subwordstart(m_lDepsL[index]);
		   }
	   }
	   else
	   {
		   return -1;
	   }
   }

   inline int subwordend(int index) const {
	   if(index<m_nNextWord && index >= 0)
	   {
		   if(m_lLabelTypes[index])
		   {
			   int curIndex = index +1;
			   while(!m_lPOSTypes[curIndex] && curIndex < m_nNextWord)
			   {
				   curIndex++;
			   }
			   return curIndex-1;
		   }
		   else if (m_lDepsR[index] == -1)
		   {
			   return  index ;
		   }
		   else
		   {
			   return subwordend(m_lDepsR[index]);
		   }
	   }
	   else
	   {
		   return -1;
	   }
   }


   inline int leftinnerfirstchild(int index) const{
        if(index<m_nNextWord && index >= 0 && m_lInDepsL[index] != -1)
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
        if(index<m_nNextWord && index >= 0 && m_lInDepsR[index] != -1)
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


   inline int head( const int &index ) const {
	   if(index < m_nNextWord && index >= 0 && m_HeadSet[index])
	   {
		   return m_lHeads[index];
	   }
	   else
	   {
		   // this is an error
		   return -1;
	   }
   }

   inline int pos( const int &index ) const {
	   if(index<=m_nNextWord && index >= 0)
	   {
		   return m_lPOSs[index];
	   }
	   else{
		   // this is an error
		   return -1;
	   }
   }

   inline int leftdep( const int &index ) const {
	   if(index<=m_nNextWord && index >= 0)
	   {
		   return m_lDepsL[index];
	   }
	   else
	   {
		   // this is an error
		   return -1;
	   }
   }
   inline int rightdep( const int &index ) const {
	   if(index<=m_nNextWord && index >= 0)
	   {
		   return m_lDepsR[index];
	   }
	   else
	   {
		   // this is an error
		   return -1;
	   }
   }

   inline int leftindep( const int &index ) const {
       if(index<=m_nNextWord && index >= 0)
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
       if(index<=m_nNextWord && index >= 0)
       {
           return m_lInDepsR[index];
       }
       else
       {
           // this is an error
           return -1;
       }
   }

   inline int sibling( const int &index ) const {
	   if(index<=m_nNextWord && index >= 0)
	   {
		   return m_lSibling[index];
	   }
	   else
	   {
		   // this is an error
		   return -1;
	   }
   }



   inline int nextword( ) const { return m_nNextWord ; }

#ifdef LABELED
   inline int label( const int &index ) const {
	   if(index < m_nNextWord && index >= 0 && m_HeadSet[index])
	   {
		   return m_lLabels[index];
	   }
	   else
	   {
		   // this is an error
		   return -1;
	   }
   }
#endif

   inline int leftarity( const int &index ) const { assert(index<=m_nNextWord); return m_lDepNumL[index]; }
   inline int rightarity( const int &index ) const { assert(index<=m_nNextWord); return m_lDepNumR[index]; }

   inline int leftinnerarity( const int &index ) const { assert(index<=m_nNextWord); return m_lInDepNumL[index]; }
   inline int rightinnerarity( const int &index ) const { assert(index<=m_nNextWord); return m_lInDepNumR[index]; }

   inline int leftouterarity( const int &index ) const { assert(index<=m_nNextWord&&m_lDepNumL[index]>=m_lInDepNumL[index]); return m_lDepNumL[index]- m_lInDepNumL[index]; }
   inline int rightouterarity( const int &index ) const { assert(index<=m_nNextWord&&m_lDepNumR[index]>=m_lInDepNumR[index]); return m_lDepNumR[index]-m_lInDepNumR[index]; }

   inline const CSetOfTags<CDependencyLabel> &lefttagset( const int &index ) const { assert(index<=m_nNextWord); return m_lDepTagL[index]; }
   inline const CSetOfTags<CDependencyLabel> &righttagset( const int &index ) const { assert(index<=m_nNextWord); return m_lDepTagR[index]; }

   void clear() { 
      m_nNextWord = 0;
      m_nStackSize = 0;
      m_nHeadSetSize = 0;
      m_nActionSize = 0;
      //m_Actions.clear();
      score = 0; 
      m_nLastAction = action::NO_ACTION;
      ClearNext();
   }

   void operator = ( const CStateItem &item ) {
      m_nStackSize = item.m_nStackSize;

      for(int i = 0; i < m_nStackSize; i++)
      {
    	  m_Stack[i] = item.m_Stack[i];
      }

      m_nActionSize = item.m_nActionSize;

      for(int i = 0; i < m_nActionSize; i++)
      {
    	  m_Action[i] = item.m_Action[i];
      }

      m_nHeadSetSize = item.m_nHeadSetSize;
      m_nNextWord = item.m_nNextWord;

      m_nLastAction = item.m_nLastAction;
      m_nSentLen = item.m_nSentLen;
      score = item.score; 
      for ( int i=0; i<=m_nNextWord; ++i ){ // only copy active word (including m_nNext)
    	 m_HeadSet[i] = item.m_HeadSet[i];
    	 //if(m_HeadSet[i])
    	 {
    		 m_lHeads[i] = item.m_lHeads[i];
#ifdef LABELED
    		 m_lLabels[i] = item.m_lLabels[i];
    		 m_lLabelTypes[i] = item.m_lLabelTypes[i];
#endif
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

      ClearNext();
      if(m_nHeadSetSize + m_nStackSize != m_nNextWord && m_nLastAction != action::POP_ROOT &&  m_nLastAction != action::IDLE )
      {
     	 std::cout << "error:\t" << m_nHeadSetSize  << " + " << m_nStackSize << " != " << m_nNextWord << std::endl;
      }
   }

//-----------------------------------------------------------------------------

public:

   bool canarc() const
   {
	   if(m_nStackSize > 1 && m_lLabelTypes[m_Stack[m_nStackSize-1]] && m_lLabelTypes[m_Stack[m_nStackSize-2]])
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }

   bool canarcin() const
   {
	   if(m_nStackSize > 1 && !m_lLabelTypes[m_Stack[m_nStackSize-1]] && !m_lLabelTypes[m_Stack[m_nStackSize-2]])
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }

   bool canshiftin() const
   {
	   if(m_nStackSize > 0 && !m_lLabelTypes[m_Stack[m_nStackSize-1]] && m_nNextWord < m_nSentLen)
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }

   bool canshift() const
   {
	   if(m_nStackSize ==0 || m_lLabelTypes[m_Stack[m_nStackSize-1]] && m_nNextWord < m_nSentLen)
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }

   bool canpopword() const
   {
	   if(m_nStackSize > 0 && !m_lLabelTypes[m_Stack[m_nStackSize-1]] && (m_nStackSize == 1 || m_lLabelTypes[m_Stack[m_nStackSize-2]]))
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }


   bool canpoproot() const
   {
	   if(m_nStackSize >= 1 && m_nHeadSetSize == m_nNextWord -1 && m_lLabelTypes[m_Stack[m_nStackSize-1]] && m_nNextWord == m_nSentLen)
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }


   // the arc left action links the current stack top to the next word with popping

   void ArcLeft(unsigned long lab) {
      if( m_nStackSize <= 1 )
      {
    	  std::cout << "error" << std::endl;
      }
      static int top0, top1;
      top0 = m_Stack[m_nStackSize-1];
      top1 = m_Stack[m_nStackSize-2];
      if(((m_lLabelTypes[top0]) && (m_lLabelTypes[top1]) && (lab > 0)) || ( (!m_lLabelTypes[top0]) && (!m_lLabelTypes[top1]) && (lab == 0)) )
      {

      }
      else
      {
    	  std::cout << "error" << std::endl;
      }
      m_nStackSize--;
      m_Stack[m_nStackSize-1] = top0;
      m_lHeads[top1] = top0;
      m_HeadSet[top1] = true;
      m_nHeadSetSize++;
      if(lab == 0)
      {
          m_lInDepsL[top0] = top1;
    	  m_lInDepNumL[top0] ++ ;
      }
      //else
      {
    	  m_lDepTagL[top0].add(lab) ;
      }

      m_lLabels[top1] = lab;
      m_lSibling[top1] = m_lDepsL[top0];
      m_lDepsL[top0] = top1;
      m_lDepNumL[top0] ++ ;
      if(lab > 0)
      {
    	  m_nLastAction=action::encodeAction(action::ARC_LEFT, lab);
      }
      else
      {
    	  m_nLastAction = action::encodeAction(action::ARC_LEFT_IN);
      }
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;
      ClearNext();
   }

   // the arc right action links the next word to the current stack top with pushing

   void ArcRight(unsigned long lab) {
	  if( m_nStackSize <= 1 )
	  {
		  std::cout << "error" << std::endl;
	  }
	  static int top0, top1;
      top0 = m_Stack[m_nStackSize-1];
      top1 = m_Stack[m_nStackSize-2];
      if( ((m_lLabelTypes[top0]) && (m_lLabelTypes[top1]) && (lab > 0)) || ((!m_lLabelTypes[top0]) && (!m_lLabelTypes[top1]) && (lab == 0)))
      {

      }
      else
      {
    	  std::cout << "error" << std::endl;
      }
      m_nStackSize--;
      m_Stack[m_nStackSize-1] = top1;
	  m_lHeads[top0] = top1;
	  m_HeadSet[top0] = true;
	  m_nHeadSetSize++;
	  if(lab == 0)
	  {
	      m_lInDepsR[top1] = top0 ;
    	  m_lInDepNumR[top1] ++ ;
	  }
	  //else
	  {
		  m_lDepTagR[top1].add(lab) ;
	  }
      m_lLabels[top0] = lab ;
      m_lSibling[top0] = m_lDepsR[top1];
      m_lDepsR[top1] = top0 ;
      m_lDepNumR[top1] ++ ;
      if(lab > 0)
      {
    	  m_nLastAction=action::encodeAction(action::ARC_RIGHT, lab);
      }
      else
      {
    	  m_nLastAction = action::encodeAction(action::ARC_RIGHT_IN);
      }
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;
      ClearNext();
   }

   // the shift action does pushing
   void Shift(unsigned long lab) {
	  if(m_nStackSize > 0)
	  {
		  if( ((m_lLabelTypes[m_Stack[m_nStackSize-1]]) && (lab > 0) ) || ((!m_lLabelTypes[m_Stack[m_nStackSize-1]]) && (lab == 0) ) )
		  {

		  }
		  else
		  {
			  std::cout << "error" << std::endl;
		  }
	  }
	  m_nStackSize++;
      m_Stack[m_nStackSize-1] = m_nNextWord;

      if(lab == 0)
      {
    	  assert(m_nNextWord>0);
    	  m_lPOSs[m_nNextWord] = m_lPOSs[m_nNextWord-1] ;
    	  m_lPOSTypes[m_nNextWord] = false ;
      }
      else
      {
    	  m_lPOSs[m_nNextWord] = lab ;
    	  m_lPOSTypes[m_nNextWord] = true ;
      }
      m_nNextWord ++ ;
      if(lab > 0)
      {
    	  m_nLastAction=action::encodeAction(action::SHIFT, lab);
      }
      else
      {
    	  m_nLastAction=action::encodeAction(action::SHIFT_IN);
      }
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;
      ClearNext();
   }


   // this is used for the convenience of scoring and updating
   void PopWord() {
	  //do nothing
	  assert( m_nStackSize > 0 ) ;
	  static int top0, top1;
	  top0 = m_Stack[m_nStackSize-1];
	  top1 = -1;
	  if(m_nStackSize > 1) top1 = m_Stack[m_nStackSize-2];
	  if(!m_lLabelTypes[top0] && (top1 == -1 || m_lLabelTypes[top1]))
	  {

	  }
	  else
	  {
		  std::cout << "error" << std::endl;
	  }
	  m_lLabelTypes[top0] = true;
      m_nLastAction = action::encodeAction(action::POP_WORD);
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;
      ClearNext();
   }
 


   // this is used for the convenience of scoring and updating
   void PopRoot() {
      if( m_nStackSize >= 1 && m_nHeadSetSize == m_nNextWord -1 && m_lLabelTypes[m_Stack[m_nStackSize-1]])
      {

      }
      else
      {
    	  std::cout << "error" << std::endl;
      }
      m_lLabels[m_Stack[m_nStackSize-1]] = CDependencyLabel::ROOT;
      m_nLastAction = action::encodeAction(action::POP_ROOT);
      m_HeadSet[m_Stack[m_nStackSize-1]] = true;
      m_nHeadSetSize++;
      //m_nStackSize-- ; // pop it
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;
      ClearNext();
   }


   void Idle()
   {
	   assert(IsTerminated());
	   m_nLastAction = action::encodeAction(action::IDLE);
	   m_Action[m_nActionSize] = m_nLastAction;
	   m_nActionSize++;
	   ClearNext();
   }

   // the clear next action is used to clear the next word, used with forwarding the next word index
   void ClearNext() {
	  m_Stack[m_nStackSize] = -1;
	  m_Action[m_nActionSize] = -1;
	  m_HeadSet[m_nNextWord] = false;
      m_lHeads[m_nNextWord] = CHARDEPENDENCY_LINK_NO_HEAD ;
      m_lPOSs[m_nNextWord] = false ;
      m_lPOSTypes[m_nNextWord] = 0 ;
      m_lDepsL[m_nNextWord] = CHARDEPENDENCY_LINK_NO_HEAD ;
      m_lDepsR[m_nNextWord] = CHARDEPENDENCY_LINK_NO_HEAD ;
      m_lInDepsL[m_nNextWord] = CHARDEPENDENCY_LINK_NO_HEAD ;
      m_lInDepsR[m_nNextWord] = CHARDEPENDENCY_LINK_NO_HEAD ;
      m_lDepNumL[m_nNextWord] = 0 ;
      m_lInDepNumL[m_nNextWord] = 0 ;
      m_lDepTagL[m_nNextWord].clear() ;
      m_lDepNumR[m_nNextWord] = 0 ;
      m_lInDepNumR[m_nNextWord] = 0 ;
      m_lDepTagR[m_nNextWord].clear() ;
      m_lSibling[m_nNextWord] = CHARDEPENDENCY_LINK_NO_HEAD ;
      m_lLabels[m_nNextWord] = CDependencyLabel::NONE;
      m_lLabelTypes[m_nNextWord] = false;
   }

   // the move action is a simple call to do action according to the action code
   void Move ( const unsigned long &ac ) {
      switch (action::getUnlabeledAction(ac)) {
      case action::NO_ACTION:
         return;
      case action::SHIFT:
         Shift(action::getLabel(ac));
         return;
      case action::ARC_LEFT:
         ArcLeft(action::getLabel(ac));
         return;
      case action::ARC_RIGHT:
         ArcRight(action::getLabel(ac));
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
         Shift(0);
         return;
      case action::ARC_LEFT_IN:
         ArcLeft(0);
         return;
      case action::ARC_RIGHT_IN:
         ArcRight(0);
         return;
      default:
         THROW("unknown action: " << ac << '.');
      }
   }

//-----------------------------------------------------------------------------

public:

   // returns true is the next word advances -- by shift or arcright. 

   bool StandardMoveStep( const CDependencyParse &tree, const std::vector<CDependencyLabel>&m_lCacheLabel ) {
      static int top0, top1;
      if(IsTerminated())
      {
    	  Idle();
    	  return false;
      }
      else if(m_nStackSize == 0)
      {
    	  assert( m_nNextWord == 0 && tree[m_nNextWord].tagtype.compare("b") == 0);
    	  Shift(CTag(tree[m_nNextWord].tag).code());
    	  return true;
      }
      else if(m_nStackSize == 1)
      {
    	  if(m_nNextWord == static_cast<int>(tree.size()))
    	  {
    		  if(m_lLabelTypes[m_Stack[m_nStackSize-1]])
    		  {
    			  PopRoot();
    			  return false;
    		  }
    		  else
    		  {
				  PopWord();
				  return false;
    		  }
    	  }
    	  else
    	  {
    		  if(tree[m_nNextWord].tagtype.compare("b") == 0)
    		  {
    			  if(m_lLabelTypes[m_Stack[m_nStackSize-1]])
    			  {
    				  Shift(CTag(tree[m_nNextWord].tag).code());
    				  return true;
    			  }
    			  else
    			  {
    				  PopWord();
    				  return false;
    			  }
    		  }
    		  else
    		  {
    			  Shift(0);
    		  }
    		  return true;
    	  }
      }
      // when the next word is tree.size() it means that the sentence is done already
      else {
         assert( m_nStackSize > 1 );
         top0 = m_Stack[m_nStackSize-1];
         top1 = m_Stack[m_nStackSize-2];
         bool bTop0HasRightChild = false;
		 for(int i = m_nNextWord; i < tree.size(); i++)
		 {
			 if(tree[i].head == top0)
			 {
				 bTop0HasRightChild = true;
				 break;
			 }
		 }
         if(tree[top0].head == top1 && !bTop0HasRightChild)
         {
        	if(m_lCacheLabel[top0].str()!=tree[top0].label)
        	{
        		std::cout << m_lCacheLabel[top0].str() << "assert error " << tree[top0].label << std::endl;
        	}
        	if(tree[top0].labeltype.compare("out") == 0)
        	{
        		assert(m_lCacheLabel[top0].str()==tree[top0].label);
        		if(m_lLabelTypes[top0])
        		{
        			ArcRight(m_lCacheLabel[top0].code());
        		}
        		else if(m_nNextWord == m_nSentLen || tree[m_nNextWord].tagtype.compare("b") == 0)
        		{
        			PopWord();
        		}
        		else
        		{
        			Shift(0);
        		}
        	}
        	else
        	{
        		ArcRight(0);
        	}
        	return false;
         }
         else if(tree[top1].head == top0)
         {
            if(m_lCacheLabel[top1].str()!=tree[top1].label)
            {
            	std::cout << m_lCacheLabel[top1].str() << "assert error " << tree[top1].label << std::endl;
            }
            if(tree[top1].labeltype.compare("out") == 0)
            {
            	assert(m_lCacheLabel[top1].str()==tree[top1].label);
            	if(m_lLabelTypes[top0])
            	{
            		ArcLeft(m_lCacheLabel[top1].code());
            	}
        		else if(m_nNextWord == m_nSentLen || tree[m_nNextWord].tagtype.compare("b") == 0)
        		{
        			PopWord();
        		}
        		else
        		{
        			Shift(0);
        		}
            }
            else
            {
            	ArcLeft(0);
            }
            return false;
         }
         else
         {
			  if(tree[m_nNextWord].tagtype.compare("b") == 0)
			  {
				  if(m_lLabelTypes[top0])
				  {
					  Shift(CTag(tree[m_nNextWord].tag).code());
				  }
				  else
				  {
					  PopWord();
				  }
			  }
			  else
			  {
				  Shift(0);
			  }
			  return true;
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

   unsigned FollowMove( const CStateItem *item ) {
	   static int top0, top1;
      // if the next words are same then don't check head because it might be a finished sentence (m_nNextWord==sentence.sz)
	  if(IsTerminated())
	  {
		  return action::encodeAction(action::IDLE);
	  }
	  else if ( m_nNextWord == item->m_nNextWord ) {
//std::cout << "this" << std::endl; for (int i=0; i<m_nStackSize; ++i) std::cout << m_Stack[i] << " "; std::cout << std::endl;
//std::cout << "that" << std::endl; for (int i=0; i<item->m_nStackSize; ++i) std::cout << item->m_Stack[i] << " "; std::cout << std::endl;
//         if ( m_nStackSize == item->m_nStackSize ) {
//std::cout << "this heads" << std::endl; for (int i=0; i<=m_nNextWord; ++i) std::cout << m_lHeads[i] << " "; std::cout << std::endl;
//std::cout << "that heads" << std::endl; for (int i=0; i<=item->m_nNextWord; ++i) std::cout << item->m_lHeads[i] << " "; std::cout << std::endl;
//std::cout << "this dtags" << std::endl; for (int i=0; i<=m_nNextWord; ++i) std::cout << m_lLabels[i] << " "; std::cout << std::endl;
//std::cout << "that dtags" << std::endl; for (int i=0; i<=item->m_nNextWord; ++i) std::cout << item->m_lLabels[i] << " "; std::cout << std::endl;
//         }
         if( m_nStackSize < item->m_nStackSize )
         {
        	 std::cout << m_nStackSize << " " << item->m_nStackSize << std::endl;
         }
         if( m_nStackSize > 1 )
         {
        	 top0 = m_Stack[m_nStackSize-1];
        	 top1 = m_Stack[m_nStackSize-2];


        	 if ( item->m_HeadSet[top1] && item->m_lHeads[top1] == top0 )
        	 {
        		 if(m_lLabelTypes[top0] && m_lLabelTypes[top1])
        		 {
        			 return action::encodeAction(action::ARC_LEFT, item->m_lLabels[top1]);
        		 }
        		 else if(!m_lLabelTypes[top0] && !m_lLabelTypes[top1])
        		 {
        			 return action::encodeAction(action::ARC_LEFT_IN);
        		 }
        		 else if(!m_lLabelTypes[top0] && m_lLabelTypes[top1])
        		 {
        			 return action::encodeAction(action::POP_WORD);
        		 }
        		 else
        		 {
        			 std::cout << "error" << std::endl;
        		 }
        	 }
        	 else if ( item->m_HeadSet[top0] && item->m_lHeads[top0] == top1 )
        	 {
        		 if(m_lLabelTypes[top0] && m_lLabelTypes[top1])
        		 {
        			 return action::encodeAction(action::ARC_RIGHT, item->m_lLabels[top0]);
        		 }
        		 else if(!m_lLabelTypes[top0] && !m_lLabelTypes[top1])
        		 {
        			 return action::encodeAction(action::ARC_RIGHT_IN);
        		 }
        		 else if(!m_lLabelTypes[top0] && m_lLabelTypes[top1])
        		 {
        			 return action::encodeAction(action::POP_WORD);
        		 }
        		 else
        		 {
        			 std::cout << "error" << std::endl;
        		 }

        	 }
        	 else if(!m_lLabelTypes[top0] && item->m_lLabelTypes[top0])
			 {
        		 return action::encodeAction(action::POP_WORD);
			 }
        	 else
        	 {
        		 return action::NO_ACTION;
        	 }

         }
         else if(!m_lLabelTypes[m_Stack[m_nStackSize-1]])
         {
        	 return action::encodeAction(action::POP_WORD);
         }
         else
         {
        	 if(m_nNextWord != m_nSentLen)
        	 {
        		 std::cout << "error" << std::endl;
        	 }
        	 return action::encodeAction(action::POP_ROOT);
         }
      }
      else
      {
    	  assert( m_nNextWord < item->m_nNextWord );
          if( m_nStackSize > 1 )
          {
         	 top0 = m_Stack[m_nStackSize-1];
         	 top1 = m_Stack[m_nStackSize-2];

             bool bTop0HasRightChild = false;
    		 for(int i = m_nNextWord; i < item->m_nNextWord; i++)
    		 {
    			 if(item->head(i) == top0)
    			 {
    				 bTop0HasRightChild = true;
    				 break;
    			 }
    		 }

         	 if ( item->m_HeadSet[top1] && item->m_lHeads[top1] == top0 )
         	 {
        		 if(m_lLabelTypes[top0] && m_lLabelTypes[top1])
        		 {
        			 return action::encodeAction(action::ARC_LEFT, item->m_lLabels[top1]);
        		 }
        		 else if(!m_lLabelTypes[top0] && !m_lLabelTypes[top1])
        		 {
        			 return action::encodeAction(action::ARC_LEFT_IN);
        		 }
        		 else if(m_lLabelTypes[top0] && !m_lLabelTypes[top1])
        		 {
        			 std::cout << "error" << std::endl;
        		 }
        		 else if(item->m_lPOSTypes[m_nNextWord])
        		 {
        			 return action::encodeAction(action::POP_WORD);
        		 }
        		 else
        		 {
        			 return action::encodeAction(action::SHIFT_IN, 0);
        		 }
         	 }
         	 else if ( item->m_HeadSet[top0] && item->m_lHeads[top0] == top1 && !bTop0HasRightChild)
         	 {
        		 if(m_lLabelTypes[top0] && m_lLabelTypes[top1])
        		 {
        			 return action::encodeAction(action::ARC_RIGHT, item->m_lLabels[top0]);
        		 }
        		 else if(!m_lLabelTypes[top0] && !m_lLabelTypes[top1])
        		 {
        			 return action::encodeAction(action::ARC_RIGHT_IN);
        		 }
        		 else if(m_lLabelTypes[top0] && !m_lLabelTypes[top1])
        		 {
        			 std::cout << "error" << std::endl;
        		 }
        		 else if(item->m_lPOSTypes[m_nNextWord])
        		 {
        			 return action::encodeAction(action::POP_WORD);
        		 }
        		 else
        		 {
        			 return action::encodeAction(action::SHIFT, 0);
        		 }
         	 }
         	 else if(item->m_lPOSTypes[m_nNextWord])
         	 {
         		if(m_lLabelTypes[top0])
         		{
         			return action::encodeAction(action::SHIFT, item->m_lPOSs[m_nNextWord]);
         		}
         		else
         		{
         			return action::encodeAction(action::POP_WORD);
         		}
         	 }
         	 else
         	 {
         		return action::encodeAction(action::SHIFT_IN, 0);
         	 }

          }
          else if(item->m_lPOSTypes[m_nNextWord])
          {
        	  if(m_nStackSize == 0 || m_lLabelTypes[m_Stack[m_nStackSize-1]])
        	  {
        		  return action::encodeAction(action::SHIFT, item->m_lPOSs[m_nNextWord]);
        	  }
        	  else
        	  {
        		  return action::encodeAction(action::POP_WORD);
        	  }
          }
          else
          {
        	  return action::encodeAction(action::SHIFT_IN, 0);
          }
      }
   }

   void GenerateTree( const CStringVector &input, CDependencyParse &output ) const {
      output.clear();
      for ( int i=0; i<nextword(); ++i )
         output.push_back( CCharDependencyTreeNode( input.at(i) , CTag(m_lPOSs[i]).str() ,
        		 m_lPOSTypes[i]?"b":"i", m_lHeads[i] , CDependencyLabel(m_lLabels[i]).str() , m_lLabelTypes[i]?"out":"in") ) ;
   }


};

#endif
