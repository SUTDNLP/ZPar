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
   int m_Stack[MAX_SENTENCE_SIZE];                     // stack of words that are currently  processed
   int m_nStackSize;
   int m_HeadStack[MAX_SENTENCE_SIZE];                     // stack of words that are currently  processed
   int m_nHeadStackSize;
   int m_Buffer[MAX_SENTENCE_SIZE];                     // buffer of words that are currently  processed
   int m_nBufferSize;
   bool m_HeadSet[MAX_SENTENCE_SIZE];                     // stack of words that already have heads
   int m_nHeadSetSize;
   int m_Action[3*MAX_SENTENCE_SIZE];
   int m_nActionSize;
   //std::vector<int> m_Actions;                     // history actions
   int m_nNextWord;                         // index for the next buffer word
   int m_nQNextWord;                         // index for the next queue word
   int m_lHeads[MAX_SENTENCE_SIZE];         // the lexical head for each word
   int m_lDepsL[MAX_SENTENCE_SIZE];         // the leftmost dependency for each word (just for cache, temporary info)
   int m_lDepsR[MAX_SENTENCE_SIZE];         // the rightmost dependency for each word (just for cache, temporary info)
   int m_lDepNumL[MAX_SENTENCE_SIZE];       // the number of left dependencies
   int m_lDepNumR[MAX_SENTENCE_SIZE];       // the number of right dependencies
   CSetOfTags<CDependencyLabel> m_lDepTagL[MAX_SENTENCE_SIZE]; // the set of left tags
   CSetOfTags<CDependencyLabel> m_lDepTagR[MAX_SENTENCE_SIZE]; // the set of right tags
   int m_lSibling[MAX_SENTENCE_SIZE];       // the sibling towards head
#ifdef LABELED
   unsigned long m_lLabels[MAX_SENTENCE_SIZE];   // the label of each dependency link
#endif
   unsigned long m_nLastAction;                  // the last stack action
   const std::vector <CWord>* m_lCache;
   unsigned long m_lPOSs[MAX_SENTENCE_SIZE];
   bool m_bLossCounted[MAX_SENTENCE_SIZE];

public:
   SCORE_TYPE score;                        // score of stack - predicting how potentially this is the correct one
   SCORE_TYPE score_pos;
   SCORE_TYPE score_dep;

public:
   // constructors and destructor
   CStateItem(const std::vector <CWord>*cache=0) : m_lCache(cache) { clear(); }
   ~CStateItem() { }
   CStateItem(CStateItem& item) : m_lCache(0) { std::cerr<<"CStateItem does not support copy constructor!"; std::cerr.flush(); assert(1==0); }

public:
   // comparison
   inline bool operator < (const CStateItem &item) const { return score < item.score; }
   inline bool operator > (const CStateItem &item) const { return score > item.score; }
   inline bool operator == (const CStateItem &item) const {
      int i;
      if ( m_nNextWord != item.m_nNextWord )
         return false;
      if ( m_nQNextWord != item.m_nQNextWord )
         return false;
      for ( i=0; i<=m_nQNextWord; ++i ) {
         if ( m_lPOSs[i] != item.m_lPOSs[i])
            return false;
      }
      if ( m_nStackSize != item.m_nStackSize )
         return false;
      if ( m_nStackSize>0 )
      {
    	  for( i = 0; i <= m_nStackSize; i++)
    	  {
    		  if (m_Stack[i] != item.m_Stack[i])
    		  {
    			  return false;
    		  }
    	  }
      }

      if ( m_nHeadStackSize != item.m_nHeadStackSize )
         return false;
      if ( m_nHeadStackSize>0 )
      {
    	  for( i = 0; i <= m_nHeadStackSize; i++)
    	  {
    		  if (m_HeadStack[i] != item.m_HeadStack[i])
    		  {
    			  return false;
    		  }
    	  }
      }

      if ( m_nBufferSize != item.m_nBufferSize )
         return false;
      if ( m_nBufferSize>0 )
      {
    	  for( i = 0; i <= m_nBufferSize; i++)
    	  {
    		  if (m_Buffer[i] != item.m_Buffer[i])
    		  {
    			  return false;
    		  }
    	  }
      }

      if ( m_nActionSize != item.m_nActionSize )
         return false;
      if ( m_nActionSize > 0 )
      {
    	  for(i = 0; i <= m_nActionSize; i++)
    	  {
    		  if (m_Action[i] != item.m_Action[i])
    		  {
    			  return false;
    		  }
    	  }
      }

      if ( m_nHeadSetSize != item.m_nHeadSetSize )
         return false;
	  for(int i = 0; i <= m_nNextWord; i++)
	  {
		  if (m_HeadSet[i] != item.m_HeadSet[i])
		  {
			  return false;
		  }
		  if(m_lHeads[i] != item.m_lHeads[i])
		  {
			  return false;
		  }

#ifdef LABELED
		 if ( m_lLabels[i] != item.m_lLabels[i] )
		 {
			return false;
		 }
#endif
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
   inline int stacktop() const { assert(m_nStackSize>0); return m_Stack[m_nStackSize-1]; }
   inline int stackbottom() const { assert(m_nStackSize>0); return m_Stack[0]; }
   inline int stackitem( const unsigned &index ) const { assert(index<m_nStackSize); return m_Stack[index]; }

   inline int buffersize() const { return m_nBufferSize; }
   inline bool bufferempty() const { return m_nBufferSize<=0; }
   inline int buffertop() const { assert(m_nBufferSize>0); return m_Buffer[m_nBufferSize-1]; }
   inline int bufferbottom() const { assert(m_nBufferSize>0); return m_Buffer[0]; }
   inline int bufferitem( const unsigned &index ) const { assert(index<m_nBufferSize); return m_Buffer[index]; }


   inline int headstacksize() const { return m_nHeadStackSize; }
   inline bool headstackempty() const { return m_nHeadStackSize<=0; }
   inline int headstacktop() const { assert(m_nHeadStackSize>0); return m_HeadStack[m_nHeadStackSize-1]; }
   inline int headstackbottom() const { assert(m_nHeadStackSize>0); return m_HeadStack[0]; }
   inline int headstackitem( const unsigned &index ) const { assert(index<m_nHeadStackSize); return m_HeadStack[index]; }



   inline bool afterreduce() const {
#ifdef LABELED
      return action::getUnlabeledAction(m_nLastAction)==action::REDUCE;
#else
      return m_nLastAction==action::REDUCE;
#endif
}


   inline bool canDEPOperation() const
   {
	   if( m_nBufferSize == action::max_buffer_size ||  m_nQNextWord == m_lCache->size())
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }

   inline bool canPOSOperation() const
   {
	   if( m_nBufferSize < action::max_buffer_size &&  m_nQNextWord < m_lCache->size())
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }



   inline int headsetsize() const { return m_nHeadSetSize; }
   inline bool headsetempty() const { return m_nHeadSetSize <= 0; }

   inline int actionsize() const { return m_nActionSize; }
   inline bool actionempty() const { return m_nActionSize <= 0; }



   inline int head( const int &index ) const {
	   if(index <= m_nNextWord && m_HeadSet[index] && index >= 0)
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
	   if(index<=m_nQNextWord && index >= 0)
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

   inline int nextbufferword( ) const { return m_nNextWord ; }
   inline int nextqueueword( ) const { return m_nQNextWord ; }
#ifdef LABELED
   inline int label( const int &index ) const {
	   if(index < m_nNextWord && m_HeadSet[index] && index >= 0)
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

   inline int leftarity( const int &index ) const
   {
	   if( index<=m_nNextWord  && index >= 0)
	   {
		   return m_lDepNumL[index];
	   }
	   else
	   {
		   return -1;
	   }
   }
   inline int rightarity( const int &index ) const
   {
	   if(index<=m_nNextWord  && index >= 0)
	   {
		   return m_lDepNumR[index];
	   }
	   else
	   {
		   return -1;
	   }
   }

   inline const CSetOfTags<CDependencyLabel> &lefttagset( const int &index ) const {
	   if(index<=m_nNextWord  && index >= 0)
	   {
		   return m_lDepTagL[index];
	   }
	   else
	   {
		   return CSetOfTags<CDependencyLabel>();
	   }
   }
   inline const CSetOfTags<CDependencyLabel> &righttagset( const int &index ) const {
	   if(index<=m_nNextWord   && index >= 0){
		   return m_lDepTagR[index];
	   }
	   else
	   {
		   return CSetOfTags<CDependencyLabel>();
	   }
   }

   void clear() { 
      m_nNextWord = 0;
      m_nQNextWord = 0;
      m_nStackSize = 0;
      m_nHeadStackSize = 0;
      m_nBufferSize = 0;
      m_nHeadSetSize = 0;
      m_nActionSize = 0;
      //m_Actions.clear();
      score = 0; 
      score_dep = 0;
      score_pos = 0;
      m_nLastAction = action::NO_ACTION;

	  m_Stack[m_nStackSize] = -1;
	  m_HeadStack[m_nHeadStackSize] = -1;
	  m_Buffer[m_nBufferSize] = -1;
	  m_Action[m_nActionSize] = -1;
	  m_HeadSet[m_nNextWord] = false;
      m_lHeads[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lPOSs[m_nQNextWord] = 0 ;
      m_lDepsL[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepsR[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepNumL[m_nNextWord] = 0 ;
      m_lDepTagL[m_nNextWord].clear() ;
      m_lDepNumR[m_nNextWord] = 0 ;
      m_lDepTagR[m_nNextWord].clear() ;
      m_lSibling[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
#ifdef LABELED
      m_lLabels[m_nNextWord] = CDependencyLabel::NONE;
#endif

      for(int i = 0; i < MAX_SENTENCE_SIZE; i++)
    	  m_bLossCounted[i] = false;
   }

   void operator = ( const CStateItem &item ) {
      m_nStackSize = item.m_nStackSize;

      for(int i = 0; i <= m_nStackSize; i++)
      {
    	  m_Stack[i] = item.m_Stack[i];
      }

      m_nHeadStackSize = item.m_nHeadStackSize;

      for(int i = 0; i <= m_nHeadStackSize; i++)
      {
    	  m_HeadStack[i] = item.m_HeadStack[i];
      }

      m_nBufferSize = item.m_nBufferSize;

      for(int i = 0; i <= m_nBufferSize; i++)
      {
    	  m_Buffer[i] = item.m_Buffer[i];
      }

      m_nActionSize = item.m_nActionSize;

      for(int i = 0; i <= m_nActionSize; i++)
      {
    	  m_Action[i] = item.m_Action[i];
      }

      m_nHeadSetSize = item.m_nHeadSetSize;
      m_nNextWord = item.m_nNextWord;
      m_nQNextWord = item.m_nQNextWord;

      m_nLastAction = item.m_nLastAction;
      m_lCache = item.m_lCache;
      score = item.score; 
      score_pos = item.score_pos;
      score_dep = item.score_dep;
      for ( int i=0; i<=m_nNextWord; ++i ){ // only copy active word (including m_nNext)
    	 m_HeadSet[i] = item.m_HeadSet[i];
    	 //if(m_HeadSet[i])
    	 {
    		 m_lHeads[i] = item.m_lHeads[i];
#ifdef LABELED
    		 m_lLabels[i] = item.m_lLabels[i];
#endif
    	 }
         m_lDepsL[i] = item.m_lDepsL[i]; 
         m_lDepsR[i] = item.m_lDepsR[i];
         m_lDepNumL[i] = item.m_lDepNumL[i];
         m_lDepNumR[i] = item.m_lDepNumR[i];
         m_lDepTagL[i] = item.m_lDepTagL[i];
         m_lDepTagR[i] = item.m_lDepTagR[i];
         m_lSibling[i] = item.m_lSibling[i];
      }

      for ( int i=0; i<=m_nQNextWord; ++i ){
    	  m_lPOSs[i] = item.m_lPOSs[i];
      }

      for(int i = 0; i < MAX_SENTENCE_SIZE; i++)
    	  m_bLossCounted[i] = item.m_bLossCounted[i];

      //ClearNext();
      //if(m_nHeadSetSize + m_nStackSize != m_nNextWord)
      //{
     //	 std::cout << "error:\t" << m_nHeadSetSize  << " + " << m_nStackSize << " != " << m_nNextWord << std::endl;
      //}
   }

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

public:

   double precision( const CDependencyParse &reference) {
      double correct = 0;
     for (int i=0; i<reference.size(); ++i)
         if (m_lHeads[i] == reference[i].head)
            ++correct;
      return correct/reference.size();
   }


   int hammingloss(const CDependencyParse &reference, unsigned long nNextAction)
   {
	   unsigned long unLabelAction = nNextAction;
	   unsigned label = 0;


	   unLabelAction = action::getUnlabeledAction(nNextAction);
	   label = action::getLabel(nNextAction);


	   int stack_top = -1;
	   if(m_nStackSize > 0)stack_top = m_Stack[m_nStackSize-1] ;
	   int queue_top = m_nNextWord;

	   int loss = 0;
	   if(unLabelAction == action::ARC_LEFT)
	   {
		   TRACE_WORD("ARC_LEFT ");
#ifdef LABELED
		   TRACE_WORD(CDependencyLabel(label).str() << " ");
#endif

		   if(reference[stack_top].head > queue_top || reference[stack_top].head == DEPENDENCY_LINK_NO_HEAD
#ifdef LABELED
			|| (reference[stack_top].head == queue_top
			&& CDependencyLabel(reference[stack_top].label) != label)
#endif
				   )
		   {
			   assert(!m_bLossCounted[stack_top]);
			   {
				   loss++;
				   m_bLossCounted[stack_top] = true;
			   }
		   }
		   for(int qIndex = queue_top + 1; qIndex < reference.size(); qIndex++)
		   {
			   if(reference[qIndex].head == stack_top)
			   {
				   assert(!m_bLossCounted[qIndex]);
				   {
					   loss++;
					   m_bLossCounted[qIndex] = true;
				   }
			   }
		   }
	   }
	   else if(unLabelAction == action::ARC_RIGHT)
	   {
		   TRACE_WORD("ARC_RIGHT ");
#ifdef LABELED
		   TRACE_WORD(CDependencyLabel(label).str() << " ");
#endif

		   if(reference[queue_top].head != stack_top
#ifdef LABELED
		   	|| CDependencyLabel(reference[queue_top].label) != label
#endif
		   )
		   {
			   for(int sIndex = 0; sIndex < m_nStackSize -1; sIndex++)
			   {
				   int wordIndex = m_Stack[sIndex];

				   if(reference[wordIndex].head == queue_top
					&&	m_lHeads[wordIndex]  == DEPENDENCY_LINK_NO_HEAD)
				   {
					   assert(!m_bLossCounted[wordIndex]);
					   {
						   loss++;
						   m_bLossCounted[wordIndex] = true;
					   }
				   }

				   if(reference[queue_top].head == wordIndex)
				   {
					   assert(!m_bLossCounted[queue_top]);
					   {
						   loss++;
						   m_bLossCounted[queue_top] = true;
					   }
				   }
			   }

			   if(reference[queue_top].head > queue_top || reference[queue_top].head == DEPENDENCY_LINK_NO_HEAD
#ifdef LABELED
				|| reference[queue_top].head == stack_top
#endif
					   )
			   {
				   assert(!m_bLossCounted[queue_top]);
				   {
					   loss++;
					   m_bLossCounted[queue_top] = true;
				   }
			   }
		   }

	   }
	   else if(unLabelAction == action::REDUCE)
	   {
		   TRACE_WORD("REDUCE ");

		   for(int qIndex = queue_top; qIndex < reference.size(); qIndex++)
		   {
			   if(reference[qIndex].head == stack_top)
			   {
				   assert(!m_bLossCounted[qIndex]);
				   {
					   loss++;
					   m_bLossCounted[qIndex] = true;
				   }
			   }
		   }
	   }
	   else if(unLabelAction == action::SHIFT && label == 0)
	   {
		   TRACE_WORD("SHIFT ");

		   for(int sIndex = 0; sIndex < m_nStackSize; sIndex++)
		   {
			   int wordIndex = m_Stack[sIndex];

			   if(reference[queue_top].head == wordIndex)
			   {
				   assert(!m_bLossCounted[queue_top]);
				   {
					   loss++;
					   m_bLossCounted[queue_top] = true;
				   }
			   }

			   if(reference[wordIndex].head == queue_top
				&&	m_lHeads[wordIndex]  == DEPENDENCY_LINK_NO_HEAD)
			   {
				   assert(!m_bLossCounted[wordIndex]);
				   {
					   loss++;
					   m_bLossCounted[wordIndex] = true;
				   }
			   }
		   }
	   }
	   else if(unLabelAction == action::SHIFT && label > 0)
	   {
		   // pos tagging errors are not counted here
	   }
	   else if(unLabelAction == action::POP_ROOT)
	   {
		   TRACE_WORD("POP_ROOT ");

		   if(reference[stack_top].head != DEPENDENCY_LINK_NO_HEAD)
		   {
			   if(!m_bLossCounted[stack_top]);
			   {
				   loss++;
				   m_bLossCounted[stack_top] = true;
			   }
		   }
	   }
	   else
	   {
		   TRACE_WORD("OTHER ");
	   }
	   TRACE_WORD(" loss:" << loss);
	   return loss;
   }



   SCORE_TYPE postagloss(const CDependencyParse &tree) const
   {
 	  SCORE_TYPE loss = 0;
 	  for(int idx = 0; idx < m_nQNextWord; idx++)
 	  {
 		  if(CTag(tree[idx].tag).code() != m_lPOSs[idx])
 		  {
 			  loss = loss +1;
 		  }
 	  }

 	  return loss;
   }


   // the arc left action links the current stack top to the next word with popping
#ifdef LABELED
   void ArcLeft(unsigned long lab) {
#else
   void ArcLeft() { 
#endif
	  assert( m_nStackSize > 0  && m_nNextWord == m_Buffer[0] && (m_nBufferSize == action::max_buffer_size || m_nQNextWord == m_lCache->size())) ;
      assert( m_lHeads[m_Stack[m_nStackSize-1]] == DEPENDENCY_LINK_NO_HEAD ) ;
      static int left ;
      left = m_Stack[m_nStackSize-1] ;
      m_nStackSize-- ;
      m_nHeadStackSize--;
      m_HeadSet[left] = true;
      m_nHeadSetSize++;
      m_lHeads[left] = m_nNextWord;
#ifdef LABELED
      m_lLabels[left] = lab;
      m_lDepTagL[m_nNextWord].add(lab) ;
#endif
      m_lSibling[left] = m_lDepsL[m_nNextWord];
      m_lDepsL[m_nNextWord] = left ;
      m_lDepNumL[m_nNextWord] ++ ;
#ifdef LABELED
      m_nLastAction=action::encodeAction(action::ARC_LEFT, lab);
#else
      m_nLastAction=action::encodeAction(action::ARC_LEFT);
#endif
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;

	  m_Stack[m_nStackSize] = -1;
	  m_HeadStack[m_nHeadStackSize] = -1;
	  m_Buffer[m_nBufferSize] = -1;
	  m_Action[m_nActionSize] = -1;
	  m_HeadSet[m_nNextWord] = false;
      m_lHeads[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lPOSs[m_nQNextWord] = 0 ;
      m_lDepsL[m_nNextWord+1] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepsR[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepNumL[m_nNextWord+1] = 0 ;
      m_lDepTagL[m_nNextWord+1].clear() ;
      m_lDepNumR[m_nNextWord] = 0 ;
      m_lDepTagR[m_nNextWord].clear() ;
      m_lSibling[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
#ifdef LABELED
      m_lLabels[m_nNextWord] = CDependencyLabel::NONE;
#endif
   }

   // the arc right action links the next word to the current stack top with pushing
#ifdef LABELED
   void ArcRight(unsigned long lab) {
#else
   void ArcRight() { 
#endif
      assert( m_nStackSize > 0  && m_nNextWord == m_Buffer[0] && (m_nBufferSize == action::max_buffer_size || m_nQNextWord == m_lCache->size())) ;
      assert( m_lHeads[m_nNextWord] == DEPENDENCY_LINK_NO_HEAD ) ;
      static int left ;
      left = m_Stack[m_nStackSize-1] ;
	  m_nStackSize++;
      m_Stack[m_nStackSize-1] = m_nNextWord;
      m_lHeads[m_nNextWord] = left ;
      m_HeadSet[m_nNextWord] = true;
      m_nHeadSetSize++;
#ifdef LABELED
      m_lLabels[m_nNextWord] = lab ;
      m_lDepTagR[left].add(lab) ;
#endif
      m_lSibling[m_nNextWord] = m_lDepsR[left];
      m_lDepsR[left] = m_nNextWord ;
      m_lDepNumR[left] ++ ;
      m_Buffer[0] = -1;
 	  for(int idx = 0; idx < m_nBufferSize -1; idx++)
 	  {
 		  m_Buffer[idx] = m_Buffer[idx+1];
 	  }
 	  m_nBufferSize--;
      m_nNextWord ++;

#ifdef LABELED
      m_nLastAction=action::encodeAction(action::ARC_RIGHT, lab);
#else
      m_nLastAction=action::encodeAction(action::ARC_RIGHT);
#endif
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;

	  m_Stack[m_nStackSize] = -1;
	  m_HeadStack[m_nHeadStackSize] = -1;
	  m_Buffer[m_nBufferSize] = -1;
	  m_Action[m_nActionSize] = -1;
	  m_HeadSet[m_nNextWord] = false;
      m_lHeads[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lPOSs[m_nQNextWord] = 0 ;
      m_lDepsL[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepsR[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepNumL[m_nNextWord] = 0 ;
      m_lDepTagL[m_nNextWord].clear() ;
      m_lDepNumR[m_nNextWord] = 0 ;
      m_lDepTagR[m_nNextWord].clear() ;
      m_lSibling[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
#ifdef LABELED
      m_lLabels[m_nNextWord] = CDependencyLabel::NONE;
#endif
   }

   // the shift action does pushing
   void Shift(unsigned long lab) {
      if(lab == 0)
      {
    	  assert( (m_nNextWord == m_Buffer[0] || m_nBufferSize == 0) && (m_nBufferSize == action::max_buffer_size || m_nQNextWord == m_lCache->size())) ;
    	  m_nStackSize++;
          m_Stack[m_nStackSize-1] = m_nNextWord;
    	  m_nHeadStackSize++;
          m_HeadStack[m_nHeadStackSize-1] = m_nNextWord;
          m_Buffer[0] = -1;
      	  for(int idx = 0; idx < m_nBufferSize -1; idx++)
      	  {
      		  m_Buffer[idx] = m_Buffer[idx+1];
      	  }
      	  m_nBufferSize--;
		  m_nNextWord ++ ;

		  m_nLastAction=action::encodeAction(action::SHIFT);
	      m_Action[m_nActionSize] = m_nLastAction;
	      m_nActionSize++;

		  m_Stack[m_nStackSize] = -1;
		  m_HeadStack[m_nHeadStackSize] = -1;
		  m_Buffer[m_nBufferSize] = -1;
		  m_Action[m_nActionSize] = -1;
		  m_HeadSet[m_nNextWord] = false;
	      m_lHeads[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
	      m_lPOSs[m_nQNextWord] = 0 ;
	      m_lDepsL[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
	      m_lDepsR[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
	      m_lDepNumL[m_nNextWord] = 0 ;
	      m_lDepTagL[m_nNextWord].clear() ;
	      m_lDepNumR[m_nNextWord] = 0 ;
	      m_lDepTagR[m_nNextWord].clear() ;
	      m_lSibling[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
	#ifdef LABELED
	      m_lLabels[m_nNextWord] = CDependencyLabel::NONE;
	#endif
      }
      else
      {
    	  assert( (m_nNextWord == m_Buffer[0] || m_nBufferSize == 0) && m_nBufferSize < action::max_buffer_size && m_nQNextWord < m_lCache->size()) ;
		  m_nBufferSize++;
		  m_Buffer[m_nBufferSize-1] = m_nQNextWord;
		  m_lPOSs[m_nQNextWord] = lab ;
		  m_nQNextWord ++ ;
		  m_nLastAction=action::encodeAction(action::SHIFT, lab);
	      m_Action[m_nActionSize] = m_nLastAction;
	      m_nActionSize++;

		  m_Stack[m_nStackSize] = -1;
		  m_HeadStack[m_nHeadStackSize] = -1;
		  m_Buffer[m_nBufferSize] = -1;
		  m_Action[m_nActionSize] = -1;
	      m_lHeads[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
	      m_lPOSs[m_nQNextWord] = 0 ;
	      m_lSibling[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
	#ifdef LABELED
	      m_lLabels[m_nNextWord] = CDependencyLabel::NONE;
	#endif
      }
   }
 
   // the reduce action does popping
   void Reduce() {
      assert( m_lHeads[m_Stack[m_nStackSize-1]] != DEPENDENCY_LINK_NO_HEAD ) ;
      m_nStackSize-- ;
      m_nLastAction=action::encodeAction(action::REDUCE);
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;

	  m_Stack[m_nStackSize] = -1;
	  m_HeadStack[m_nHeadStackSize] = -1;
	  m_Buffer[m_nBufferSize] = -1;
	  m_Action[m_nActionSize] = -1;
      m_lHeads[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lPOSs[m_nQNextWord] = 0 ;
      m_lSibling[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
#ifdef LABELED
      m_lLabels[m_nNextWord] = CDependencyLabel::NONE;
#endif
   }

   // this is used for the convenience of scoring and updating
   void PopRoot() {

      assert( m_nStackSize == 1 && m_lHeads[m_Stack[m_nStackSize-1]] == DEPENDENCY_LINK_NO_HEAD );  // make sure only one root item in stack
      assert( m_nHeadSetSize == m_nNextWord -1 && m_nNextWord == m_nQNextWord && m_nNextWord == m_lCache->size());
#ifdef LABELED
      m_lLabels[m_Stack[m_nStackSize-1]] = CDependencyLabel::ROOT;
#endif
      m_nLastAction = action::encodeAction(action::POP_ROOT);
      m_HeadSet[m_Stack[m_nStackSize-1]] = true;
      m_nHeadSetSize++;
      m_nStackSize-- ; // pop it
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;

	  m_Stack[m_nStackSize] = -1;
	  m_HeadStack[m_nHeadStackSize] = -1;
	  m_Buffer[m_nBufferSize] = -1;
	  m_Action[m_nActionSize] = -1;
	  m_HeadSet[m_nNextWord] = false;
      m_lHeads[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lPOSs[m_nQNextWord] = 0 ;
      m_lDepsL[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepsR[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lDepNumL[m_nNextWord] = 0 ;
      m_lDepTagL[m_nNextWord].clear() ;
      m_lDepNumR[m_nNextWord] = 0 ;
      m_lDepTagR[m_nNextWord].clear() ;
      m_lSibling[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
#ifdef LABELED
      m_lLabels[m_nNextWord] = CDependencyLabel::NONE;
#endif
   }


   // the move action is a simple call to do action according to the action code
   void Move ( const unsigned long &ac ) {
#ifdef LABELED
      switch (action::getUnlabeledAction(ac)) {
#else
      switch (ac) {
#endif
      case action::NO_ACTION:
         return;
      case action::SHIFT:
    	 Shift(action::getLabel(ac));
         return;
      case action::REDUCE:
         Reduce();
         return;
      case action::ARC_LEFT:
#ifdef LABELED
         ArcLeft(action::getLabel(ac));
#else
         ArcLeft();
#endif
         return;
      case action::ARC_RIGHT:
#ifdef LABELED
         ArcRight(action::getLabel(ac));
#else
         ArcRight();
#endif
         return;
      case action::POP_ROOT:
         PopRoot();
         return;
      default:
         THROW("unknown action: " << ac << '.');
      }
   }

//-----------------------------------------------------------------------------

public:

   // returns true is the next word advances -- by shift or arcright. 
#ifdef LABELED
   bool StandardMoveStep( const CDependencyParse &tree, const std::vector<CDependencyLabel>&m_lCacheLabel ) {
#else
   bool StandardMoveStep( const CDependencyParse &tree ) {
#endif
      static int top;
      // when the next word is tree.size() it means that the sentence is done already
      if(m_nBufferSize == action::max_buffer_size || m_nQNextWord == m_lCache->size())
      {
		  if ( m_nNextWord == static_cast<int>(tree.size()) ) {
			 assert( m_nStackSize > 0 );
			 if ( m_nStackSize > 1 ) {
				Reduce();
				return false;
			 }
			 else {
				PopRoot();
				return false;
			 }
		  }
		  // the first case is that there is some words on the stack linking to nextword
		  if ( m_nStackSize > 0 ) {
			 top = m_Stack[m_nStackSize-1];
			 while ( !(m_lHeads[top] == DEPENDENCY_LINK_NO_HEAD) )
				top = m_lHeads[top];
			 if ( tree[top].head == m_nNextWord ) {    // if a local head deps on nextword first
				if ( top == m_Stack[m_nStackSize-1] ) {
	#ifdef LABELED
				   assert(m_lCacheLabel[top].str() == tree[top].label);
				   ArcLeft(m_lCacheLabel[top].code()); // link it to the next word
	#else
				   ArcLeft();                          // link it to the next word
	#endif
				   return false;
				}
				else {
				   Reduce();
				   return false;
				}
			 }
		  }
		  // the second case is that no words on the stack links nextword, and nextword does not link to stack word
		  if ( tree[m_nNextWord].head == DEPENDENCY_LINK_NO_HEAD || // the root or
			   tree[m_nNextWord].head > m_nNextWord ) { // head on the right
			 Shift(CTag::NONE);
			 return true;
		  }
		  // the last case is that the next words links to stack word
		  else {                                        // head on the left
			 assert( m_nStackSize > 0 );
			 top = m_Stack[m_nStackSize-1];
			 if ( tree[m_nNextWord].head == top ) {     // the next word deps on stack top
	#ifdef LABELED
				assert(m_lCacheLabel[m_nNextWord].str()==tree[m_nNextWord].label);
				ArcRight(m_lCacheLabel[m_nNextWord].code());
	#else
				ArcRight();
	#endif
				return true;
			 }
			 else {                                     // must depend on non-immediate h
				Reduce();
				return false;
			 }
		  }
      }
	  else
	  {
		  Shift(CTag(tree[m_nQNextWord].tag).code());
		  return false;
	  }
   }

   // we want to pop the root item after the whole tree done
   // on the one hand this seems more natural
   // on the other it is easier to score
   void StandardFinish() {
	   assert( m_nStackSize == 0 && m_nNextWord == m_lCache->size() && m_nNextWord == m_nQNextWord);
   }

   unsigned FollowMove( const CStateItem *item ) {
      static int top;

      if(m_nBufferSize == action::max_buffer_size || m_nQNextWord == m_lCache->size())
      {
		  // if the next words are same then don't check head because it might be a finished sentence (m_nNextWord==sentence.sz)
		  if ( m_nNextWord == item->m_nNextWord ) {
	//std::cout << "this" << std::endl; for (int i=0; i<m_nStackSize; ++i) std::cout << m_Stack[i] << " "; std::cout << std::endl;
	//std::cout << "that" << std::endl; for (int i=0; i<item->m_nStackSize; ++i) std::cout << item->m_Stack[i] << " "; std::cout << std::endl;
	//         if ( m_nStackSize == item->m_nStackSize ) {
	//std::cout << "this heads" << std::endl; for (int i=0; i<=m_nNextWord; ++i) std::cout << m_lHeads[i] << " "; std::cout << std::endl;
	//std::cout << "that heads" << std::endl; for (int i=0; i<=item->m_nNextWord; ++i) std::cout << item->m_lHeads[i] << " "; std::cout << std::endl;
	//std::cout << "this dtags" << std::endl; for (int i=0; i<=m_nNextWord; ++i) std::cout << m_lLabels[i] << " "; std::cout << std::endl;
	//std::cout << "that dtags" << std::endl; for (int i=0; i<=item->m_nNextWord; ++i) std::cout << item->m_lLabels[i] << " "; std::cout << std::endl;
	//         }
			 assert( m_nStackSize > item->m_nStackSize );
			 top = m_Stack[m_nStackSize-1];
			 if ( item->m_lHeads[top] == m_nNextWord )
	#ifdef LABELED
				return action::encodeAction(action::ARC_LEFT, item->m_lLabels[top]);
	#else
				return action::ARC_LEFT;
	#endif
			 else if ( item->m_lHeads[top] != DEPENDENCY_LINK_NO_HEAD )
				return action::encodeAction(action::REDUCE);
			 else
				return action::encodeAction(action::POP_ROOT);
		  }
		  // the first case is that there is some words on the stack linking to nextword
		  if ( m_nStackSize > 0 ) {
			 top = m_Stack[m_nStackSize-1];
			 while ( !(m_lHeads[top] == DEPENDENCY_LINK_NO_HEAD) )
				top = m_lHeads[top];
			 if ( item->head(top) == m_nNextWord ) {    // if a local head deps on nextword first
				if ( top == m_Stack[m_nStackSize-1] ) {
	#ifdef LABELED
				   return action::encodeAction(action::ARC_LEFT, item->m_lLabels[top]);
	#else
				   return action::ARC_LEFT;
	#endif
				}
				else {
				   return action::encodeAction(action::REDUCE);
				}
			 }
		  }
		  // the second case is that no words on the stack links nextword, and nextword does not link to stack word
		  if ( item->head(m_nNextWord) == DEPENDENCY_LINK_NO_HEAD || // the root or
			   item->head(m_nNextWord) > m_nNextWord ) { // head on the right
			 return action::encodeAction(action::SHIFT);
		  }
		  // the last case is that the next words links to stack word
		  else {                                        // head on the left
			 assert( m_nStackSize > 0 );
			 top = m_Stack[m_nStackSize-1];
			 if ( item->head(m_nNextWord) == top ) {    // the next word deps on stack top
	#ifdef LABELED
				return action::encodeAction(action::ARC_RIGHT, item->m_lLabels[m_nNextWord]);
	#else
				return action::ARC_RIGHT;
	#endif
			 }
			 else {                                     // must depend on non-immediate h
				return action::encodeAction(action::REDUCE);
			 }
		  }
      }
      else if ( m_nQNextWord < item->m_nQNextWord )
      {
    	  return action::encodeAction(action::SHIFT, item->m_lPOSs[m_nQNextWord]);
      }
      else
      {
    	  // this is an error
    	  return action::NO_ACTION;
      }
   }

   void GenerateTree( const CStringVector &input, CDependencyParse &output ) const {
      output.clear();
      for ( int i=0; i<nextbufferword(); ++i )
#ifdef LABELED
         output.push_back( CLabeledDependencyTreeNode( input.at(i) , CTag(m_lPOSs[i]).str() , m_lHeads[i] , CDependencyLabel(m_lLabels[i]).str() ) ) ;
#else
         output.push_back( CDependencyTreeNode( input.at(i) , CTag(m_lPOSs[i]) , m_lHeads[i] ) ) ;
#endif
   }



};

#endif
