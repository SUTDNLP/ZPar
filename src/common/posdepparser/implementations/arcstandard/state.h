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
   int m_Action[2*MAX_SENTENCE_SIZE];
   int m_nActionSize;
   //std::vector<int> m_Actions;                     // history actions
   int m_nNextWord;                         // index for the next word
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

public:
   SCORE_TYPE score;                        // score of stack - predicting how potentially this is the correct one

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
      for ( i=0; i<m_nNextWord; ++i ) {
         if ( m_lPOSs[i] != item.m_lPOSs[i])
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


   inline bool sametree(const CStateItem &item) const {
      int i;
      if ( m_nNextWord != item.m_nNextWord )
         return false;

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
#endif
    		  }
    	  }
      }

      // I think that the stacks don't have to be compared
      // might be proved by translating tree to stack
      //assert( m_Stack == item.m_Stack );
      return true;
   }

   // propty
   inline int stacksize() const { return m_nStackSize; }
   inline bool stackempty() const { return m_nStackSize<=0; }
   inline int stacktop() const { assert(m_nStackSize>0); return m_Stack[m_nStackSize-1]; }
   inline int stackbottom() const { assert(m_nStackSize>0); return m_Stack[0]; }
   inline int stackitem( const unsigned &index ) const { assert(index<m_nStackSize); return m_Stack[index]; }

   inline int headsetsize() const { return m_nHeadSetSize; }
   inline bool headsetempty() const { return m_nHeadSetSize <= 0; }

   inline int actionsize() const { return m_nActionSize; }
   inline bool actionempty() const { return m_nActionSize <= 0; }



   inline int head( const int &index ) const {
	   if(index < m_nNextWord && m_HeadSet[index])
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
	   if(index<=m_nNextWord)
	   {
		   return m_lPOSs[index];
	   }
	   else{
		   // this is an error
		   return -1;
	   }
   }

   inline int leftdep( const int &index ) const {
	   if(index<=m_nNextWord)
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
	   if(index<=m_nNextWord)
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
	   if(index<=m_nNextWord)
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
	   if(index < m_nNextWord && m_HeadSet[index])
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
      m_lCache = item.m_lCache;
      score = item.score; 
      for ( int i=0; i<=m_nNextWord; ++i ){ // only copy active word (including m_nNext)
    	 m_HeadSet[i] = item.m_HeadSet[i];
    	 //if(m_HeadSet[i])
    	 {
    		 m_lHeads[i] = item.m_lHeads[i];
#ifdef LABELED
    		 m_lLabels[i] = item.m_lLabels[i];
#endif
    	 }
         m_lPOSs[i] = item.m_lPOSs[i];
         m_lDepsL[i] = item.m_lDepsL[i]; 
         m_lDepsR[i] = item.m_lDepsR[i];
         m_lDepNumL[i] = item.m_lDepNumL[i];
         m_lDepNumR[i] = item.m_lDepNumR[i];
         m_lDepTagL[i] = item.m_lDepTagL[i];
         m_lDepTagR[i] = item.m_lDepTagR[i];
         m_lSibling[i] = item.m_lSibling[i];
      }

      ClearNext();
      if(m_nHeadSetSize + m_nStackSize != m_nNextWord)
      {
     	 std::cout << "error:\t" << m_nHeadSetSize  << " + " << m_nStackSize << " != " << m_nNextWord << std::endl;
      }
   }

//-----------------------------------------------------------------------------

public:
   // the arc left action links the current stack top to the next word with popping
#ifdef LABELED
   void ArcLeft(unsigned long lab) {
#else
   void ArcLeft() { 
#endif
      assert( m_nStackSize > 1 ) ;
      static int top0, top1;
      top0 = m_Stack[m_nStackSize-1];
      top1 = m_Stack[m_nStackSize-2];;
      m_nStackSize--;
      m_Stack[m_nStackSize-1] = top0;
      if(m_lHeads[top1] != DEPENDENCY_LINK_NO_HEAD)
      {
    	  std::cout << top1 << " "  << m_nStackSize << " "  << m_nHeadSetSize << " " << m_Stack[m_nStackSize-1] << std::endl;

    	  std::cout << "Stack: ";
		  for(int idx = 0; idx < m_nStackSize; idx++)
		  {
			  std::cout << m_Stack[idx] << " ";
		  }
		  std::cout << std::endl;

    	  std::cout << "HeadSet: ";
    	  for(int idx = 0; idx < m_nNextWord; idx++)
		  {
    		  if(m_HeadSet[idx])
    		  {
    			  std::cout << idx  << "[" << m_lHeads[idx] << "] ";
    		  }
		  }
		  std::cout << std::endl;
      }
      m_lHeads[top1] = top0;
      m_HeadSet[top1] = true;
      m_nHeadSetSize++;
#ifdef LABELED
      m_lLabels[top1] = lab;
      m_lDepTagL[top0].add(lab) ;
#endif
      m_lSibling[top1] = m_lDepsL[top0];
      m_lDepsL[top0] = top1;
      m_lDepNumL[top0] ++ ;
      ClearNext();
#ifdef LABELED
      m_nLastAction=action::encodeAction(action::ARC_LEFT, lab);
#else
      m_nLastAction=action::encodeAction(action::ARC_LEFT);
#endif
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;
   }

   // the arc right action links the next word to the current stack top with pushing
#ifdef LABELED
   void ArcRight(unsigned long lab) {
#else
   void ArcRight() { 
#endif
	  assert( m_nStackSize > 1 ) ;
	  static int top0, top1;
      top0 = m_Stack[m_nStackSize-1];
      top1 = m_Stack[m_nStackSize-2];
      m_nStackSize--;
      m_Stack[m_nStackSize-1] = top1;
      if(m_lHeads[top0] != DEPENDENCY_LINK_NO_HEAD)
      {
    	  std::cout << top0 << " "  << m_nStackSize << " "  << m_nHeadSetSize << " " << m_Stack[m_nStackSize-1] << std::endl;

    	  std::cout << "Stack: ";
		  for(int idx = 0; idx < m_nStackSize; idx++)
		  {
			  std::cout << m_Stack[idx] << " ";
		  }
		  std::cout << std::endl;

    	  std::cout << "HeadSet: ";
    	  for(int idx = 0; idx < m_nNextWord; idx++)
		  {
    		  if(m_HeadSet[idx])
    		  {
    			  std::cout << idx  << "[" << m_lHeads[idx] << "] ";
    		  }
		  }
		  std::cout << std::endl;
      }
	  m_lHeads[top0] = top1;
	  m_HeadSet[top0] = true;
	  m_nHeadSetSize++;
#ifdef LABELED
      m_lLabels[top0] = lab ;
      m_lDepTagR[top1].add(lab) ;
#endif
      m_lSibling[top0] = m_lDepsR[top1];
      m_lDepsR[top1] = top0 ;
      m_lDepNumR[top1] ++ ;
      ClearNext();
#ifdef LABELED
      m_nLastAction=action::encodeAction(action::ARC_RIGHT, lab);
#else
      m_nLastAction=action::encodeAction(action::ARC_RIGHT);
#endif
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;
   }

   // the shift action does pushing
   void Shift(unsigned long lab) {
	  m_nStackSize++;
      m_Stack[m_nStackSize-1] = m_nNextWord;
      m_lPOSs[m_nNextWord] = lab ;
      m_nNextWord ++ ;
      ClearNext();
      m_nLastAction=action::encodeAction(action::SHIFT, lab);
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;
   }
 


   // this is used for the convenience of scoring and updating
   void PopRoot() {

      if( m_nStackSize != 1 || m_lHeads[m_Stack[m_nStackSize-1]] != DEPENDENCY_LINK_NO_HEAD )  // make sure only one root item in stack
      {
    	  std::cout << m_Stack[m_nStackSize-1] << " "  << m_nStackSize << " "  << m_nHeadSetSize << " " << m_Stack[m_nStackSize-1] << std::endl;

    	  std::cout << "Stack: ";
		  for(int idx = 0; idx < m_nStackSize; idx++)
		  {
			  std::cout << m_Stack[idx] << " ";
		  }
		  std::cout << std::endl;

    	  std::cout << "HeadSet: ";
    	  for(int idx = 0; idx < m_nNextWord; idx++)
		  {
    		  if(m_HeadSet[idx])
    		  {
    			  std::cout << idx  << "[" << m_lHeads[idx] << "] ";
    		  }
		  }
		  std::cout << std::endl;
      }
      assert( m_nHeadSetSize == m_nNextWord -1);
#ifdef LABELED
      m_lLabels[m_Stack[m_nStackSize-1]] = CDependencyLabel::ROOT;
#endif
      m_nLastAction = action::encodeAction(action::POP_ROOT);
      m_HeadSet[m_Stack[m_nStackSize-1]] = true;
      m_nHeadSetSize++;
      m_nStackSize-- ; // pop it
      m_Action[m_nActionSize] = m_nLastAction;
      m_nActionSize++;
   }

   // the clear next action is used to clear the next word, used with forwarding the next word index
   void ClearNext() {
	  m_Stack[m_nStackSize] = -1;
	  m_Action[m_nActionSize] = -1;
	  m_HeadSet[m_nNextWord] = false;
      m_lHeads[m_nNextWord] = DEPENDENCY_LINK_NO_HEAD ;
      m_lPOSs[m_nNextWord] = 0 ;
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
      static int top0, top1;
      if(m_nStackSize == 0)
      {
    	  assert( m_nNextWord == 0 );
    	  Shift(CTag(tree[m_nNextWord].tag).code());
    	  return true;
      }
      else if(m_nStackSize == 1)
      {
    	  if(m_nNextWord == static_cast<int>(tree.size()))
    	  {
    		  PopRoot();
    		  return false;
    	  }
    	  else
    	  {
    		  Shift(CTag(tree[m_nNextWord].tag).code());
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
#ifdef LABELED
        	if(m_lCacheLabel[top0].str()!=tree[top0].label)
        	{
        		std::cout << m_lCacheLabel[top0].str() << "assert error " << tree[top0].label << std::endl;
        	}
            assert(m_lCacheLabel[top0].str()==tree[top0].label);
            ArcRight(m_lCacheLabel[top0].code());
#else
            ArcRight();
#endif
            return false;
         }
         else if(tree[top1].head == top0)
         {
#ifdef LABELED
            if(m_lCacheLabel[top1].str()!=tree[top1].label)
            {
            	std::cout << m_lCacheLabel[top1].str() << "assert error " << tree[top1].label << std::endl;
            }
        	assert(m_lCacheLabel[top1].str()==tree[top1].label);
            ArcLeft(m_lCacheLabel[top1].code());
#else            
            ArcLeft();
#endif
            return false;
         }
         else
         {
        	 Shift(CTag(tree[m_nNextWord].tag).code());
        	 return true;
         }
      }
   }

   // we want to pop the root item after the whole tree done
   // on the one hand this seems more natural
   // on the other it is easier to score
   void StandardFinish() {
      assert( m_nStackSize == 0 && m_nNextWord == m_lCache->size());
   }

   unsigned FollowMove( const CStateItem *item ) {
	   static int top0, top1;
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
         if( m_nStackSize < item->m_nStackSize )
         {
        	 std::cout << m_nStackSize << " " << item->m_nStackSize << std::endl;
         }
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
#ifdef LABELED
        		 return action::encodeAction(action::ARC_LEFT, item->m_lLabels[top1]);
#else
        	 	 return action::ARC_LEFT;
#endif
        	 }
        	 else if ( item->m_HeadSet[top0] && item->m_lHeads[top0] == top1  && !bTop0HasRightChild)
        	 {
#ifdef LABELED
        		 return action::encodeAction(action::ARC_RIGHT, item->m_lLabels[top0]);
#else
        		 return action::ARC_RIGHT;
#endif
        	 }
        	 else
        	 {
        		 // this is an error
        		 return action::NO_ACTION;
        	 }

         }
         else
         {
        	 assert(m_nNextWord == m_lCache->size());
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
 #ifdef LABELED
         		 return action::encodeAction(action::ARC_LEFT, item->m_lLabels[top1]);
 #else
         	 	 return action::ARC_LEFT;
 #endif
         	 }
         	 else if ( item->m_HeadSet[top0] && item->m_lHeads[top0] == top1 && !bTop0HasRightChild)
         	 {
 #ifdef LABELED
         		 return action::encodeAction(action::ARC_RIGHT, item->m_lLabels[top0]);
 #else
         		 return action::ARC_RIGHT;
 #endif
         	 }
         	 else
         	 {
         		return action::encodeAction(action::SHIFT, item->m_lPOSs[m_nNextWord]);
         	 }

          }
          else
          {
         	 return action::encodeAction(action::SHIFT, item->m_lPOSs[m_nNextWord]);
          }
      }
   }

   void GenerateTree( const CStringVector &input, CDependencyParse &output ) const {
      output.clear();
      for ( int i=0; i<nextword(); ++i )
#ifdef LABELED
         output.push_back( CLabeledDependencyTreeNode( input.at(i) , CTag(m_lPOSs[i]).str() , m_lHeads[i] , CDependencyLabel(m_lLabels[i]).str() ) ) ;
#else
         output.push_back( CDependencyTreeNode( input.at(i) , CTag(m_lPOSs[i]) , m_lHeads[i] ) ) ;
#endif
   }




};

#endif
