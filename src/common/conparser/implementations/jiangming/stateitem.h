// Copyright (C) University of Oxford 2010
#ifndef _COMMON_CON_PARSER_STATEITEM
#define _COMMON_CON_PARSER_STATEITEM

#include "action.h"

//static copulateVerbs({"be", "being", "been", "am", "are", "r", "is", "ai", "was", "were", "'m", "'re", "'s", "s", "seem", "seems", "seemed", "appear", "appears", "appeared", "stay", "stays", "stayed", "remain", "remains", "remained", "resemble", "resembles", "resembled", "become", "becomes", "became"};
//
////Miguel

static CWord g_word_here("here");
static CWord g_word_there("there");
static CWord g_word_mondays("Mondays");
static CWord g_word_monday("Monday");
static CWord g_word_tuesdays("Tuesdays");
static CWord g_word_tuesday("Tuesday");
static CWord g_word_wednesdays("Wednesdays");
static CWord g_word_wednesday("Wednesday");
static CWord g_word_thursdays("Thursdays");
static CWord g_word_thursday("Thursday");
static CWord g_word_fridays("Fridays");
static CWord g_word_friday("Friday");
static CWord g_word_saturdays("Saturdays");
static CWord g_word_saturday("Saturday");
static CWord g_word_sundays("Sundays");
static CWord g_word_sunday("Sunday");
static CWord g_word_years("years");
static CWord g_word_year("year");
static CWord g_word_months("months");
static CWord g_word_month("month");
static CWord g_word_weeks("weeks");
static CWord g_word_week("week");
static CWord g_word_days("days");
static CWord g_word_day("day");
static CWord g_word_mornings("mornings");
static CWord g_word_morning("morning");
static CWord g_word_evenings("evenings");
static CWord g_word_evening("evening");
static CWord g_word_nights("nights");
static CWord g_word_night("night");
static CWord g_word_january("January");
static CWord g_word_jan("Jan."); //...Jan+something
static CWord g_word_february("February");
static CWord g_word_feb("Feb.");//... Feb+something
static CWord g_word_march("March");
static CWord g_word_mar("Mar.");//... Mar+something
static CWord g_word_april("April");
static CWord g_word_apr("Apr.");//... Apr+something
static CWord g_word_may("May");
static CWord g_word_june("June");
static CWord g_word_july("July");
static CWord g_word_august("August");
static CWord g_word_aug("Aug.");//... Apr+something
static CWord g_word_september("September");
static CWord g_word_sept("Sept.");//... Apr+something
static CWord g_word_october("October");
static CWord g_word_oct("Oct.");//... Apr+something
static CWord g_word_november("November");
static CWord g_word_nov("Nov.");//... Apr+something
static CWord g_word_december("December");
static CWord g_word_dec("Dec.");//... Apr+something
static CWord g_word_today("today");
static CWord g_word_yesterday("yesteday");
static CWord g_word_tomorrow("tomorrow");
static CWord g_word_spring("spring");
static CWord g_word_summer("summer");
static CWord g_word_fall("fall");
static CWord g_word_autumn("autumn");
static CWord g_word_winter("winter");

static CWord g_word_lot("lot");


  /*private static final String beAuxiliaryRegex =
   *     "/^(?i:am|is|are|r|be|being|'s|'re|'m|was|were|been|s|ai)$/";*/

//Miguel
static CWord g_word_am("am");
static CWord g_word_is("is");
static CWord g_word_are("are");
static CWord g_word_r("r");
static CWord g_word_be("be");
static CWord g_word_being("being");
static CWord g_word_aps("'s");
static CWord g_word_apre("'re");
static CWord g_word_apm("m");
static CWord g_word_was("was");
static CWord g_word_were("were");
static CWord g_word_been("been");
static CWord g_word_s("s");
static CWord g_word_ai("ai");
//private static final String passiveAuxWordRegex =
//    //"/^(?i:am|is|are|r|be|being|'s|'re|'m|was|were|been|s|ai|seem|seems|seemed|seeming|appear|appears|appeared|become|becomes|became|becoming|get|got|getting|gets|gotten|remains|remained|remain)$/";
//
//
//    //private static final String copularWordRegex =
//    //    "/^(?i:am|is|are|r|be|being|'s|'re|'m|was|were|been|s|ai|seem|seems|seemed|seeming|appear|appears|
//    //appeared|stay|stays|stayed|remain|remains|remained|resemble|resembles|resembled|resembling|become|becomes|became|becoming)$/";
//    //the first ones are already above. Miguel
static CWord g_word_seem("seem");
static CWord g_word_seems("seems");
static CWord g_word_seemed("seemed");
static CWord g_word_seeming("seeming");
static CWord g_word_appear("appear");
static CWord g_word_appears("appears");
static CWord g_word_appeared("appeared");
static CWord g_word_stay("stay");
static CWord g_word_stays("stays");
static CWord g_word_stayed("stayed");
static CWord g_word_remain("remain");
static CWord g_word_remains("remains");
static CWord g_word_remained("remained");
static CWord g_word_resemble("resemble");
static CWord g_word_resembles("resembles");
static CWord g_word_resembled("resembled");
static CWord g_word_resembling("resembling");
static CWord g_word_become("become");
static CWord g_word_becomes("becomes");
static CWord g_word_became("became");
static CWord g_word_becoming("becoming");

static CWord g_word_get("get");
static CWord g_word_got("got");
static CWord g_word_getting("getting");
static CWord g_word_gets("gets");
static CWord g_word_gotten("gotten");

/*private static final String haveRegex =
 *     "/^(?i:have|had|has|having)$/";*/
 //Miguel
static CWord g_word_have("have");
static CWord g_word_had("had");
static CWord g_word_has("has");
static CWord g_word_having("having");
   /*private static final String stopKeepRegex =
	*     "/^(?i:stop|stops|stopped|stopping|keep|keeps|kept|keeping)$/";*/

static CWord g_word_stop("stop");
static CWord g_word_stops("stops");
static CWord g_word_stopped("stopped");
static CWord g_word_stopping("stopping");
static CWord g_word_keep("keep");
static CWord g_word_keeps("keeps");
static CWord g_word_kept("kept");
static CWord g_word_keeping("keeping");
//extras
static CWord g_word_either("either");
static CWord g_word_neither("neither");
static CWord g_word_both("both");

static CWord g_word_all("all");
static CWord g_word_each("each");

static CWord g_word_only("only");
static CWord g_word_just("just");
static CWord g_word_merely("merely");

static CWord g_word_not("not");
static CWord g_word_nt("n't");

static CWord g_word_comma(",");
static CWord g_word_as("as");
static CWord g_word_that("that");
static CWord g_word_how("how");
static CWord g_word_whether("whether");

static CWord g_word_order("order");

static CWord g_word_two_dots(":");
static CWord g_word_slash("/");

static CWord g_word_dot(".");
static CWord g_word_dollar("$");
static CWord g_word_hash("#");

static CWord g_word_asterisc("*");
static CWord g_word_hyphen("-");
static CWord g_word_hyphen2("--");
static CWord g_word_lowhyphen("_");
static CWord g_word_perc("%");

static CWord g_word_at("at");
static CWord g_word_in("in");
static CWord g_word_In("In");

static CWord g_word_to("to");
static CWord g_word_addition("addition");
static CWord g_word_so("so");

static CWord g_word_quote("'");
static CWord g_word_quotes("``");
static CWord g_word_squotes("''");

static CWord g_word_where("where");
static CWord g_word_why("why");
static CWord g_word_when("when");
static CWord g_word_notwithstanding("notwithstanding");

static CWord g_word_old("old");
static CWord g_word_well("well");
static CWord g_word_rather("rather");
static CWord g_word_instead("instead");
static CWord g_word_than("than");
static CWord g_word_of("of");

static CWord g_word_such("such");
static CWord g_word_because("because");
static CWord g_word_Because("because");
static CWord g_word_least("least");
static CWord g_word_due("due");
static CWord g_word_Due("Due");

//miguel
class CConstituentList {
	public:
		CConstituent current;
		CConstituentList* next;

		CConstituentList() : current(0), next(0) {}
		virtual ~CConstituentList() {}
		void clear() {current=0; next=0;}

		void addAux(CConstituent new_node) {
			if (current==0){
				this->current=new_node;
				this->next=0;
			}
			else {
				CConstituentList* temp=this;
				while(temp->next!=0) {
					temp=temp->next;  //we iterate just until the very last node.
				}
				CConstituentList* list_new=new CConstituentList();
				list_new->current=new_node;
				temp->next=list_new;
			}
		}
		bool empty(){
			return (current==0 && next==0);
		}

		static void add(CConstituentList*& list, CConstituent node) {
			if (list==0){
				list=new CConstituentList();
				list->current=node;
			}
			else {
				list->addAux(node);
			}
		}
};


//miguel
#include "linkclass.h"
class CStateNode;

class CStateNodeList {
	public:
		const CStateNode* node;
		CStateNodeList* next;
	   	CStateNodeList* previous;

		CStateNodeList() : node(0), next(0), previous(0) {}
		virtual ~CStateNodeList() {}
		void clear() {node=0; next=0; previous=0;}

		void addAux(const CStateNode* new_node) {
			if (node==0){
				this->node=new_node;
				this->next=0;
				this->previous=0;
			}
			else {
				CStateNodeList* temp=this;
				while(temp->next!=0) {
						temp=temp->next;  //we iterate just until the very last node.
				}
				CStateNodeList* list_new=new CStateNodeList();
				list_new->node=new_node;
				temp->next=list_new;
				list_new->previous=temp;
			}
		}
		void addAux(CStateNodeList* list) {
			CStateNodeList* temp=this;
			while(temp->next!=0) {
				temp=temp->next;  //we iterate just until the very last node.
			}
			temp->next=list;
			list->previous=temp;
		}

		bool empty(){
			return (node==0 && next==0 && previous==0);
		}

		static void add(CStateNodeList*& list, const CStateNode* node) {
			if (list==0){
				list=new CStateNodeList();
				list->node=node;
			}
			else {
				list->addAux(node);
			}
		}
		static void add(CStateNodeList*& list, CStateNodeList* newList) {
			if (list==0){
				list=new CStateNodeList();
				list=newList;
			}
			else {
				list->addAux(newList);
			}
		}
};

/*===============================================================
 *
 * CStateNode - tree nodes
 *
 *==============================================================*/

#include "bitarray.h"

class CStateNode {
public:
   enum NODE_TYPE {LEAF=0, SINGLE_CHILD, HEAD_LEFT, HEAD_RIGHT};
public:
   int id;
   NODE_TYPE type;
   bool temp;
   // fields for constituents
   CConstituent constituent;
   const CStateNode* left_child;
   const CStateNode* right_child;
   // fields for tokens and constituents

   CStateNodeList* m_umbinarizedSubNodes;//miguel
   CBitArray linkedNodes;//miguel

   int lexical_head;
   int lexical_start;
   int lexical_end;

   //Stanford link
   CLink* stfLinksCollapsed;//miguel
   CLink* stfLinks;//miguel

public:
   inline bool head_left() const { return type==HEAD_LEFT; }
   inline bool single_child() const { return type==SINGLE_CHILD; }
   inline bool is_constituent() const { return type!=LEAF; }

public:
   CStateNode(const int &id, const NODE_TYPE &type, const bool &temp, const unsigned long &constituent, CStateNode *left_child, CStateNode *right_child, const int &lexical_head, const int &lexical_start, const int &lexical_end) : id(id), type(type), temp(temp), constituent(constituent), left_child(left_child), right_child(right_child), lexical_head(lexical_head), lexical_start(lexical_start), lexical_end(lexical_end), stfLinksCollapsed(0), stfLinks(0), m_umbinarizedSubNodes(0), linkedNodes(MAX_SENTENCE_SIZE) {
   //miguel
   linkedNodes.clearandsize(MAX_SENTENCE_SIZE);
   }

   CStateNode() : id(-1), type(), temp(0), constituent(), left_child(0), right_child(0), lexical_head(0), lexical_start(0), lexical_end(0),stfLinksCollapsed(0), stfLinks(0), m_umbinarizedSubNodes(0), linkedNodes(MAX_SENTENCE_SIZE) {
   		linkedNodes.clearandsize(MAX_SENTENCE_SIZE);
   }
   virtual ~CStateNode() {
   //miguel
   	 CLink* tmp = stfLinks;
	 while(tmp!=0){
	 	CLink* next = tmp->next;
		delete tmp;
		tmp = next;
	 }
   }
public:
   bool valid() const { return id!=-1; }
   void clear() {
      this->id = -1;
      this->type = static_cast<NODE_TYPE>(0);
      this->temp = 0;
      this->constituent.clear();
      this->left_child = 0;
      this->right_child = 0;
      this->lexical_head = 0;
      this->lexical_start = 0;
      this->lexical_end = 0;

	  //miguel
	  this->stfLinks = 0;
	  this->stfLinksCollapsed = 0;
	  this->m_umbinarizedSubNodes = 0;
   }
   void set(const int &id, const NODE_TYPE &type, const bool &temp, const unsigned long &constituent, const CStateNode *left_child, const CStateNode *right_child, const int &lexical_head, const int &lexical_start, const int &lexical_end) {
      this->id = id;
      this->type = type;
      this->temp = temp;
      this->constituent = constituent;
      this->left_child = left_child;
      this->right_child = right_child;
      this->lexical_head = lexical_head;
      this->lexical_start = lexical_start;
      this->lexical_end = lexical_end;

	  //miguel
	  this->stfLinks = 0;
	  //this->stfLinksCollapsed = 0;
	  this->m_umbinarizedSubNodes = 0;
   }//{}
   bool operator == (const CStateNode &nd) const {
      return id == nd.id &&
             type == nd.type &&
             temp == nd.temp &&
             constituent == nd.constituent &&
             left_child == nd.left_child &&
             right_child == nd.right_child &&
             lexical_head == nd.lexical_head;
             lexical_start == nd.lexical_start;
             lexical_end == nd.lexical_end;
   }
   void operator = (const CStateNode &nd) {
      id = nd.id;
      type = nd.type;
      temp = nd.temp;
      constituent.copy(nd.constituent);
      left_child = nd.left_child;
      right_child = nd.right_child;
      lexical_head = nd.lexical_head;
      lexical_start = nd.lexical_start;
      lexical_end = nd.lexical_end;
   }
public:
   void toCCFGTreeNode(CCFGTreeNode &node) const {
//      node.parent = parent->id;
      node.is_constituent = is_constituent();
      node.temp = temp;
#ifdef NO_TEMP_CONSTITUENT
      ASSERT(!node.temp, "Internal error: this version does not temporary constituents but state items have them.")
      node.constituent = constituent.code();
#else
      node.constituent = constituent.extractConstituentCode();
#endif
      node.single_child = single_child();
      node.head_left = head_left();
      node.left_child = left_child ? left_child->id : -1;
      node.right_child = right_child ? right_child->id : -1;
      node.token = lexical_head;
   }
};

/*===============================================================
 *
 * CStateItem - the search state item, representing a partial
 *              candidate with shift reduce.
 *
 *==============================================================*/

class CContext;

class CStateItem {
public:
   const std::vector<CTaggedWord<CTag, TAG_SEPARATOR> > *words; //miguel

   SCORE_TYPE score;
   CStateNode node;

   const CStateItem *statePtr;
   const CStateItem *stackPtr;
   int current_word;
   CAction action;
#ifdef TRAIN_LOSS
   CStack<CLabeledBracket> gold_lb;
   unsigned correct_lb;
   unsigned plost_lb;
   unsigned rlost_lb;
   bool bTrain;
#endif
#ifdef SCALE
   unsigned size;
#endif
   int m_lHeads[MAX_SENTENCE_SIZE];
   unsigned m_lLabels[MAX_SENTENCE_SIZE];

public:
#ifdef TRAIN_LOSS
#define LOSS_CON , correct_lb(0), plost_lb(0), rlost_lb(0), bTrain(false)
#else
#define LOSS_CON
#endif
#ifdef SCALE
#define SCALE_CON , size(0)
#else
#define SCALE_CON
#endif
   CStateItem() : current_word(0), score(0), action(), stackPtr(0), statePtr(0), node() LOSS_CON SCALE_CON {}
   virtual ~CStateItem() {}
public:
   void clear() {
      words = 0;
	  statePtr = 0;
      stackPtr = 0;
      current_word = 0;
      node.clear();
      score = 0;
      action.clear();
#ifdef TRAIN_LOSS
      gold_lb.clear();
      correct_lb=0;
      plost_lb=0;
      rlost_lb=0;
      bTrain = false;
#endif
#ifdef SCALE
      size = 0;
#endif
	  std::memset(m_lHeads, -1, MAX_SENTENCE_SIZE*sizeof(int)); //miguel
	  std::memset(m_lLabels, 0, MAX_SENTENCE_SIZE*sizeof(unsigned)); //miguel
   }
   bool empty() const {
      if (current_word==0) {
         assert(stackPtr == 0 && statePtr == 0 && score==0);
         return true;
      }
      return false;
   }
   unsigned stacksize() const {
      unsigned retval = 0;
      const CStateItem *current = this;
      while (current) {
         if (current->node.valid()) ++retval;// no node -> start/fini
         current = current->stackPtr;
      }
      return retval;
   }
   unsigned unaryreduces() const {
      unsigned retval = 0;
      const CStateItem *current = this;
      while (current) {
         if (current->action.type() == CActionType::REDUCE_UNARY)
            ++retval;
         else
            return retval;
         current = current->statePtr;
      }
      return retval;
   }
   int newNodeIndex() const { return node.id+1; }

public:
   bool operator < (const CStateItem &st) const { return score < st.score; }
   bool operator > (const CStateItem &st) const { return score > st.score; }
   bool operator == (const CStateItem &st) const {
      THROW("State items are not comparable with each other");
   }
   bool operator != (const CStateItem &st) const { return !( (*this) == st ); }

protected:
   // now this actions MUST BE called by Move
   void shift(CStateItem *retval, const unsigned long &constituent = CConstituent::NONE) const {
      //TRACE("shift");
      assert(!IsTerminated());
      retval->node.set(node.id+1, CStateNode::LEAF, false, constituent, 0, 0, current_word, current_word, current_word);
      retval->current_word = current_word+1;
      retval->stackPtr = this; ///
#ifdef TRAIN_LOSS
      retval->bTrain = this->bTrain;
      computeShiftLB(&(retval->gold_lb), retval->correct_lb, retval->plost_lb, retval->rlost_lb);
#endif
      assert(!retval->IsTerminated());
   }
   //jm
   void shift_arc(CStateItem *retval, const unsigned long &constituent = CConstituent::NONE) const {
      //TRACE("shift");
      assert(!IsTerminated());
      retval->node.set(node.id+1, CStateNode::LEAF, false, constituent, 0, 0, current_word, current_word, current_word);
      retval->current_word = current_word+1;
      retval->stackPtr = this; ///
#ifdef TRAIN_LOSS
      retval->bTrain = this->bTrain;
      computeShiftLB(&(retval->gold_lb), retval->correct_lb, retval->plost_lb, retval->rlost_lb);
#endif
      assert(!retval->IsTerminated());

	  assert(retval->node.m_umbinarizedSubNodes==0);//miguel
	  retval->node.linkedNodes.clearandsize(words->size());//miguel
   }

   void reduce(CStateItem *retval, const unsigned long &constituent, const bool &single_child, const bool &head_left, const bool &temporary) const {
      //TRACE("reduce");
      assert(!IsTerminated());
      const static CStateNode *l, *r;
      assert(stackPtr!=0);
      if (single_child) {
         assert(head_left == false);
         assert(temporary == false);
         l = &node;
         retval->node.set(node.id+1, CStateNode::SINGLE_CHILD, false, constituent, l, 0, l->lexical_head, l->lexical_start, l->lexical_end);
         retval->stackPtr = stackPtr;
#ifdef TRAIN_LOSS
         retval->bTrain = this->bTrain;
         computeReduceUnaryLB(&(retval->gold_lb), retval->correct_lb, retval->plost_lb, retval->rlost_lb, constituent);
#endif
      }
      else {

         static unsigned long fullconst;
         assert(stacksize()>=2);
         r = &node;
         l = &(stackPtr->node);
#ifdef NO_TEMP_CONSTITUENT
         fullconst = constituent;
#else
         fullconst = CConstituent::encodeTmp(constituent, temporary);
#endif
         retval->node.set(node.id+1, (head_left?CStateNode::HEAD_LEFT:CStateNode::HEAD_RIGHT), temporary, fullconst, l, r, (head_left?l->lexical_head:r->lexical_head), l->lexical_start, r->lexical_end);
         retval->stackPtr = stackPtr->stackPtr;
#ifdef TRAIN_LOSS
         retval->bTrain = this->bTrain;
         computeReduceBinaryLB(&(retval->gold_lb), retval->correct_lb, retval->plost_lb, retval->rlost_lb, fullconst);
#endif
      }
      retval->current_word = current_word;
      assert(!IsTerminated());
   }
   //jm
   void reduce_arc(CStateItem *retval, const unsigned long &constituent, const bool &single_child, const bool &head_left, const bool &temporary) const {
      //TRACE("reduce");
      assert(!IsTerminated());
      const static CStateNode *l, *r;
      assert(stackPtr!=0);
	  retval->current_word = current_word;
      if (single_child) {
         assert(head_left == false);
         assert(temporary == false);
         l = &node;
         retval->node.set(node.id+1, CStateNode::SINGLE_CHILD, false, constituent, l, 0, l->lexical_head, l->lexical_start, l->lexical_end);
         retval->stackPtr = stackPtr;

		 CStateNodeList::add(retval->node.m_umbinarizedSubNodes,l); //miguel
		 retval->node.linkedNodes.copy(l->linkedNodes); //miguel
#ifdef TRAIN_LOSS
         retval->bTrain = this->bTrain;
         computeReduceUnaryLB(&(retval->gold_lb), retval->correct_lb, retval->plost_lb, retval->rlost_lb, constituent);
#endif
      }
      else {
		 const CStateNode *h,*m;
         unsigned long fullconst;
         assert(stacksize()>=2);
         r = &node;
         l = &(stackPtr->node);
		 if (head_left){
		 	h = l;
			m = r;
		 }
		 else{
		 	h = r;
			m = l;
		 }
#ifdef NO_TEMP_CONSTITUENT
         fullconst = constituent;
#else
         fullconst = CConstituent::encodeTmp(constituent, temporary);
#endif
         retval->node.set(node.id+1, (head_left?CStateNode::HEAD_LEFT:CStateNode::HEAD_RIGHT), temporary, fullconst, l, r, h->lexical_head, l->lexical_start, r->lexical_end);
         retval->stackPtr = stackPtr->stackPtr;
#ifdef TRAIN_LOSS
         retval->bTrain = this->bTrain;
         computeReduceBinaryLB(&(retval->gold_lb), retval->correct_lb, retval->plost_lb, retval->rlost_lb, fullconst);
#endif
		if (l->temp) {
	 		CStateNodeList::add(retval->node.m_umbinarizedSubNodes,l->m_umbinarizedSubNodes);
		}
		else {
			CStateNodeList::add(retval->node.m_umbinarizedSubNodes,l);
		}
		if (r->temp) {
			CStateNodeList::add(retval->node.m_umbinarizedSubNodes,r->m_umbinarizedSubNodes);
		}
		else {
				CStateNodeList::add(retval->node.m_umbinarizedSubNodes,r);
		}
		retval->node.linkedNodes.clearandsize(words->size());
		for (int i=0;i<words->size();++i){
			if (l->linkedNodes.isset(i) || r->linkedNodes.isset(i))
				retval->node.linkedNodes.set(i);
		}//MIguel Thu 18
		retval->generateStanfordLinks();

		if (retval->m_lHeads[m->lexical_head]==DEPENDENCY_LINK_NO_HEAD) {
			retval->buildStanfordLink(STANFORD_DEP_DEP, m->lexical_head, h->lexical_head);
		}
      }
      assert(!IsTerminated());
   }

   void terminate(CStateItem *retval) const {
      //TRACE("terminate");
//      assert(IsComplete());
      assert(!IsTerminated());
      retval->node = this->node;
      retval->stackPtr=this->stackPtr;
      retval->current_word = current_word;
      // compute loss
#ifdef TRAIN_LOSS
      retval->bTrain = this->bTrain;
      computeTerminateLoss(&(retval->gold_lb), retval->correct_lb, retval->plost_lb, retval->rlost_lb);
#endif
      assert(retval->IsTerminated());
   }
   void noact(CStateItem *retval) const {
      //TRACE("noact");
      assert(IsTerminated());
      retval->node = this->node;
      retval->stackPtr=this->stackPtr;
      retval->current_word = current_word;
      // compute loss
#ifdef TRAIN_LOSS
      retval->bTrain = this->bTrain;
      computeIdleLoss(&(retval->gold_lb), retval->correct_lb, retval->plost_lb, retval->rlost_lb);
#endif
   }

protected:

#ifdef TRAIN_LOSS
   void computeShiftLB( CStack<CLabeledBracket> *gold, unsigned &correct, unsigned &plost, unsigned &rlost) const {
      // compute shift
      if (gold) gold->clear();
      correct = correct_lb;
      plost = plost_lb;
      rlost = rlost_lb;
      if (!bTrain) return;
      static CStack< CLabeledBracket >::const_iterator it;
      it = gold_lb.begin();
      while ( it != gold_lb.end() ) {
         if ( node.valid() && (*it).end == node.lexical_end ) {
            ++ (rlost);
         }
         else {
            if (gold) gold->push( *it );
         }
         ++it;
      } // while
   }

   void computeReduceUnaryLB(CStack<CLabeledBracket> *gold, unsigned &correct, unsigned &plost, unsigned &rlost, const unsigned long &constituent) const {
      static CStack< CLabeledBracket >::const_iterator it;
      static bool bCorrect;
      if (gold) gold->clear();
      plost = plost_lb;
      rlost = rlost_lb;
      correct = correct_lb;
      if (!bTrain) return;
      // loop
      it = gold_lb.begin();
      bCorrect = false;
      while ( it != gold_lb.end() ) {
         if ( (*it).begin == node.lexical_start &&
              (*it).end == node.lexical_end &&
              (*it).constituent == constituent ) {
            bCorrect = true;
            ++correct;
         }
         else {
            if (gold) gold->push(*it);
         }
         ++it;
      } //while
      if (!bCorrect)
         ++(plost);
   }

   void computeReduceBinaryLB(CStack<CLabeledBracket> *gold, unsigned &correct, unsigned &plost, unsigned &rlost, const unsigned long &constituent) const {
      const static CStateNode *l, *r;
      static CStack< CLabeledBracket >::const_iterator it;
      static bool bCorrect;
      if (gold) gold->clear();
      correct = correct_lb;
      plost = plost_lb;
      rlost = rlost_lb;
      if (!bTrain) return;
      r = &node;
      l = &(stackPtr->node);
      // loop
      bCorrect = false;
      it=gold_lb.begin();
      while ( it != gold_lb.end() ) {
         if ( (*it).begin == l->lexical_start &&
              (*it).end == r->lexical_end &&
              (*it).constituent == constituent ) {
            bCorrect=true;
            ++correct;
         }
         else if ( (*it).begin == r->lexical_start ) {
            ++(rlost);
         }
         else {
            if (gold) gold->push(*it);
         }
         ++it;
      } // while
      if (!bCorrect)
         ++(plost);
   }
   void computeTerminateLoss(CStack<CLabeledBracket> *gold, unsigned &correct, unsigned &plost, unsigned &rlost) const {
      if (gold) gold->clear();
      correct = correct_lb;
      plost = plost_lb;
      rlost = rlost_lb;
      if (!bTrain) return;
      static CStack< CLabeledBracket >::const_iterator it;
      it = gold_lb.begin();
      while ( it != gold_lb.end() ) {
         assert( (*it).begin == node.lexical_start && (*it).end == node.lexical_end);
         ++(rlost);
         ++it;
      }//while
   }
   void computeIdleLoss(CStack<CLabeledBracket> *gold, unsigned &correct, unsigned &plost, unsigned &rlost) const {
      if (gold) gold->clear();
      correct = correct_lb;
      plost = plost_lb;
      rlost = rlost_lb;
      if (!bTrain) return;
   }
#endif

public:

   void NextMove(const CCFGTree &snt, CAction &retval) const {
      int s = node.id;
      const CCFGTreeNode &nd = snt.nodes[s];
      const CCFGTreeNode &hd = snt.nodes[snt.parent(s)];
      assert(!hd.constituent.empty()); // so that reduce and reduce_root are not same
      bool single_child;
      bool head_left;
      bool temporary;
      // stack top single child ? reduce unary
      if (hd.single_child) {
         single_child = true;
         head_left = false; assert(hd.head_left==false);
         temporary = false; assert(hd.temp==false);
      }
      else {
         // stack top left child ? shift
         if (s == hd.left_child) {
            retval.encodeShift(snt.nodes[newNodeIndex()].constituent.code()); return;
         }
         // stack top right child ? reduce bin
         assert(s==hd.right_child);
         single_child = false;
         head_left = hd.head_left;
         temporary = hd.temp;
#ifdef NO_TEMP_CONSTITUENT
         ASSERT(!temporary, "This version does not accept temporary constituents, but the training data give them.");
#endif
      }
      retval.encodeReduce(hd.constituent.code(), single_child, head_left, temporary);
   }

   void StandardMove(const CCFGTree &tr, CAction &retval) const {
      if (IsTerminated()) {
         retval.encodeIdle();
         return;
      }
      // stack empty?shift
      if (stacksize()==0) {
         retval.encodeShift(tr.nodes[newNodeIndex()].constituent.code());
         return;
      }
      if (tr.parent(node.id) == -1) {
         assert(IsComplete(tr.words.size()));
         retval.encodeReduceRoot();
         return;
      }
      NextMove(tr, retval);
   }

   void Move(CStateItem *retval, const CAction &action) const {
      retval->action = action; // this makes it necessary for the actions to
      retval->statePtr = this; // be called by Move
      if (action.isIdle()) {
         noact(retval);
#ifdef SCALE
         retval->size = this->size;
#endif
      }
      else {
         if (action.isShift())
            { shift(retval, action.getConstituent()); }
         else if (action.isReduceRoot())
            { terminate(retval); }
         else
            { reduce(retval, action.getConstituent(), action.singleChild(), action.headLeft(), action.isTemporary()); }
#ifdef SCALE
         retval->size = this->size + 1;
#endif
      }
   }
   //jm
   void Move_arc(CStateItem *retval, const CAction &action) const {
      retval->action = action; // this makes it necessary for the actions to
      retval->statePtr = this; // be called by Move

	  std::memcpy(retval->m_lHeads, m_lHeads, MAX_SENTENCE_SIZE*sizeof(int));
	  std::memcpy(retval->m_lLabels, m_lLabels, MAX_SENTENCE_SIZE*sizeof(unsigned));

	  retval->words = this->words; // Miguel
	  if (action.isIdle()) {
         noact(retval);
#ifdef SCALE
         retval->size = this->size;
#endif
      }
      else {
         if (action.isShift())
            { shift_arc(retval, action.getConstituent()); }
         else if (action.isReduceRoot())
            { terminate(retval); }
         else
            { reduce_arc(retval, action.getConstituent(), action.singleChild(), action.headLeft(), action.isTemporary()); }
#ifdef SCALE
         retval->size = this->size + 1;
#endif
      }
   }


   bool IsComplete(const int &nWords) const {
#ifdef FRAGMENTED_TREE
      return current_word == nWords; // allow multiple-rt.
#else
      return current_word == nWords && stacksize() == 1;
#endif
   }

   bool IsTerminated() const {
      return action.type() == CActionType::POP_ROOT or action.type() == CActionType::IDLE;
   }

   bool IsIdle() const {
      return action.type() == CActionType::IDLE;
   }

   void GenerateTree(const CTwoStringVector &tagged, CSentenceParsed &out) const {
      // assert(IsTerminated()); // no need to check for this because it is being checked below
      // assert(tagged.size()==sent->size());
      out.clear();
#ifdef FRAGMENTED_TREE
      if (stacksize()>1) {
         static const CStateItem *item;
         item = statePtr;
         assert(item==stackPtr);
         static CStateItem *tmp;
         tmp = new CStateItem[stacksize()];
         static CStateItem *current;
         current = tmp;
         static CAction action;
         action.encodeReduce(CConstituent::NONE, false, false, false);
         while (item->stacksize()>1) {
            // form NONE nodes
            item->Move(current, action);
            item = current;
            ++ current;
         }
         action.encodeReduceRoot();
         item->Move(current, action);
         item = current;
         item->GenerateTree(tagged, out);
         delete [] tmp;
         return;
      }
#else
      if (stacksize()>1) { WARNING("Parser failed.");return; }
#endif
      // generate nothing if the input is empty
      if (tagged.size() == 0)
         return;

      // generate nodes for out
      static int i,j;
      // first words
      for (i=0; i<tagged.size(); ++i)
         out.newWord(tagged[i].first, tagged[i].second);
      // second constituents
      static const CStateNode* nodes[MAX_SENTENCE_SIZE*(2+UNARY_MOVES)+2];
      static int count;
      count = 0;
      const static CStateItem *current;
      current = this;
      while (current) {
         if (!current->IsTerminated() && current->node.valid()) {
            nodes[count] = &current->node;
            ++count;
         }
         current = current->statePtr;
      }
      for (i=count-1; i>=0; --i) {
         j = out.newNode();
         // copy node
         assert(j==nodes[i]->id);
         nodes[i]->toCCFGTreeNode(out.nodes[j]);
      }
      out.root = nodes[0]->id;
   }

   //jm
   void GenerateStanford(const CTwoStringVector &tagged, CCoNLLOutput *out) const {
	   if (out) {
		   out->clear();
		   for (int i=0; i<tagged.size(); ++i) {
			   unsigned label = m_lLabels[i];
			   if (label == STANFORD_DEP_NONE)
				   label = STANFORD_DEP_ROOT;
			   out->push_back(CCoNLLOutputNode(i+1, tagged.at(i).first, "_", "_", tagged.at(i).second, "_", m_lHeads[i]+1, CDependencyLabel(label).str(), DEPENDENCY_LINK_NO_HEAD, "_"));
		   }
	   }
   }

   //===============================================================================

   void trace(const CTwoStringVector *s=0) const {
      static const CStateItem* states[MAX_SENTENCE_SIZE*(2+UNARY_MOVES)+2];
      static int count;
      const static CStateItem *current;
      count = 0;
      current = this;
      while (current->statePtr) {
         states[count] = current;
         ++count ; //updating
         current = current->statePtr;
      }
      TRACE("State item score == " << score);
#ifdef SCALE
      TRACE("State item size == " << size);
#endif
#ifdef TRAIN_LOSS
      TRACE("cor = " << correct_lb << ", plo = " << plost_lb << ", rlo = " << rlost_lb << ", Loss = " << FLoss());
#endif
      --count;
      while (count>=0) {
         if (s) {
            TRACE(states[count]->action.str()<<" ["<<(states[count]->stacksize()>0?s->at(states[count]->node.lexical_head).first:"")<<"]");
         }
         else {
            TRACE(states[count]->action.str());
         }
         --count;
      }
      TRACE("");
   }
    //Miguel
    //this method generates the stanford links that are available for the current node.
    void generateStanfordLinks() {
        // remove temporary sign
        unsigned long cons = CConstituent::clearTmp(node.constituent.code());
        //nsubj
        //S < (NP=target $+ NP|ADJP) > VP
        buildNsubj1(cons);
        //SQ|PRN < (NP=target !< EX $++ VP)
        buildNsubj2(cons);
        //"S < ((NP|WHNP=target !< EX !<# (/^NN/ < (" + timeWordRegex + "))) $++ VP)"
        buildNsubj3(cons);
        //"S < ( NP=target <# (/^NN/ < " + timeWordRegex + ") !$++ NP $++VP)",
        buildNsubj4(cons);
        //"S < (NP < EX) <+(VP) (VP < NP=target)"
        buildNsubj5(cons);
        //"SQ < ((NP=target !< EX) $- /^(?:VB|AUX)/ !$++ VP)",
        buildNsubj6(cons);
        //"SQ < ((NP=target !< EX) $- (RB $- /^(?:VB|AUX)/) ![$++ VP])",
        buildNsubj7(cons);
        //"SBARQ < WHNP=target < (SQ < (VP ![$-- NP]))",
        buildNsubj8(cons);
        //"SBARQ < (SQ=target < /^(?:VB|AUX)/ !< VP)",
        buildNsubj9(cons);
        //"SINV < (NP|WHNP=target [ $- VP|VBZ|VBD|VBP|VB|MD|AUX | $- (@RB|ADVP $- VP|VBZ|VBD|VBP|VB|MD|AUX) | !$- __ !$ @NP] )",
        buildNsubj10(cons);
        //"SBAR < WHNP=target [ < (S < (VP !$-- NP) !< SBAR) | < (VP !$-- NP) !< S ]"
        buildNsubj11(cons); //REVISE
        //"SBAR !< WHNP < (S !< (NP $++ VP)) > (VP > (S $- WHNP=target))",
        buildNsubj12(cons);
        //"SQ < ((NP < EX) $++ NP=target)",
        buildNsubj13(cons);

		buildAux1(cons);
        buildAux2(cons);
        buildAux3(cons);
        buildAux4(cons);
        
        cc1(cons);
        cc2(cons);
        
        csubj1(cons);
        
        buildNsubjpass1(cons);
        
        buildExpl1(cons);
        
        buildDobj1(cons);
        buildDobj2(cons);
        buildDobj3(cons);
        buildDobj4(cons);
        buildDobj5(cons);
        buildDobj6(cons);
        buildDobj7(cons);
        buildDobj8(cons);
        
        builIObj1(cons);
        builIObj2(cons);
        
		buildAttr1(cons);
        buildAttr2(cons);
        buildAttr3(cons);
        buildAttr4(cons);
        
        buildCComp1(cons);
        buildCComp2(cons);
        buildCComp3(cons);
        buildCComp4(cons);
        buildCComp5(cons);
        buildCComp6(cons);
        buildCComp7(cons);
        buildCComp8(cons);
        buildCComp9(cons);
        buildCComp10(cons);
        buildCComp11(cons);
        
        buildXComp1(cons);
        buildXComp2(cons);
        buildXComp3(cons);
        buildXComp4(cons);
        buildXComp5(cons);
        buildXComp6(cons);
        buildXComp7(cons);
        
        buildPunct1(cons);
        //buildPunct2(cons);
        
        buildPobj1(cons);
        buildPobj2(cons);
        buildPobj3(cons);
        buildPobj4(cons);
        buildPobj5(cons);
        buildPobj6(cons);
        buildPobj7(cons);
        
        buildPComp1(cons);
        buildPComp2(cons);
        buildPComp3(cons);
        
        buildConj1(cons);
        buildConj2(cons);
        buildConj3(cons);
        buildConj4(cons);
        buildConj5(cons);
        buildConj6(cons);
        buildConj7(cons);
        buildConj8(cons);
        
        buildAComp1(cons);
        buildAComp2(cons);
        
        advcl1(cons);
        advcl2(cons);
        advcl3(cons);
        advcl4(cons);
        advcl5(cons);
        advcl6(cons);
        advcl7(cons);
        advcl8(cons);
        advcl9(cons);
        
        neg1(cons);
        neg2(cons);
        neg3(cons);
        nn1(cons);
        nn2(cons);
        nn3(cons);
        nn4(cons);
        
        advmod1(cons);
        advmod2(cons);
        advmod3(cons);
        advmod31(cons);
        //advmod32(cons);
        advmod4(cons);
        advmod5(cons);
        advmod6(cons);
        
        amod1(cons);
        amod2(cons);
        amod3(cons);
        
        appos1(cons);
        appos2(cons);
        appos3(cons);
        appos4(cons);
        appos5(cons);
        
        auxpass1(cons);
        auxpass2(cons);
        auxpass3(cons);
        auxpass4(cons);
        
        cop1(cons);
        cop2(cons);
        
        csubjpass1(cons);
        csubjpass2(cons);
        
        det1(cons);
        det2(cons);
        det3(cons);
        det4(cons);
        det5(cons);
        det6(cons);
        det7(cons);
        
        /*discourse1(cons);
         discourse2(cons);
         discourse3(cons);*/
        
        //goesWith(cons);
        
        infmod1(cons);
        infmod2(cons);
        
        mark1(cons);
        mark2(cons);
        
        mwe1(cons);
        mwe2(cons);
        mwe3(cons);
        mwe4(cons);
        mwe5(cons);
        mwe6(cons);
        
        npadvmod1(cons);
        npadvmod2(cons);
        //npadvmod3(cons);
        //npadvmod4(cons);
        //npadvmod5(cons);
        
        num1(cons);
        num2(cons);
        
        number1(cons);
        
        parataxis1(cons);
        parataxis2(cons);
        parataxis3(cons);
        parataxis4(cons);
        
        partmod1(cons);
        partmod2(cons);
        partmod3(cons);
        partmod4(cons);
        
        poss1(cons);
        poss2(cons);
        poss21(cons);
        poss3(cons);
        
        possessive1(cons);
        possessive2(cons);
        
        preconj1(cons);
        preconj2(cons);
        preconj3(cons);
        preconj4(cons);
        preconj5(cons);
        
        predet1(cons);
        predet2(cons);
        predet3(cons);
        
        prep1(cons);
        prep2(cons);
        prep3(cons);
        prep4(cons);
        
        //prt1(cons);
        prt2(cons);
        
        quantmod1(cons);
        
        rcmod1(cons);
        rcmod2(cons);
        rcmod3(cons);
        rcmod4(cons);
        rcmod5(cons);
        
        rel1(cons);
        
        tmod1(cons);
        tmod2(cons);
        tmod3(cons);
        tmod4(cons);
        tmod5(cons);
        tmod6(cons);
        tmod7(cons);
        tmod8(cons);
        tmod9(cons);
    }
    
    //==============================================================================
    //this->compareToTimeWordRegex((*words)[npLeftSister->lexical_head].word);
    bool compareWordToTimeWordRegex(CWord a) {
        
        if (a==g_word_mondays) return true;
        if (a==g_word_monday) return true;
        if (a==g_word_tuesdays) return true;
        if (a==g_word_tuesday) return true;
        if (a==g_word_wednesdays) return true;
        if (a==g_word_wednesday) return true;
        if (a==g_word_thursdays) return true;
        if (a==g_word_thursday) return true;
        if (a==g_word_friday) return true;
        if (a==g_word_fridays) return true;
        if (a==g_word_saturdays) return true;
        if (a==g_word_saturday) return true;
        if (a==g_word_sundays) return true;
        if (a==g_word_sunday) return true;
        if (a==g_word_days) return true;
        if (a==g_word_day) return true;
        if (a==g_word_morning) return true;
        if (a==g_word_mornings) return true;
        if (a==g_word_evenings) return true;
        if (a==g_word_evening) return true;
        if (a==g_word_nights) return true;
        if (a==g_word_night) return true;
        //...
        if (a==g_word_january) return true;
        if (a==g_word_jan) return true;
        
        if (a==g_word_february) return true;
        if (a==g_word_feb) return true;
        
        if (a==g_word_march) return true;
        if (a==g_word_mar) return true;
        
        if (a==g_word_april) return true;
        if (a==g_word_apr) return true;
        
        if (a==g_word_may) return true;
        if (a==g_word_june) return true;
        if (a==g_word_july) return true;
        if (a==g_word_august) return true;
        if (a==g_word_aug) return true;
        if (a==g_word_september) return true;
        if (a==g_word_sept) return true;
        if (a==g_word_october) return true;
        if (a==g_word_oct) return true;
        if (a==g_word_november) return true;
        if (a==g_word_nov) return true;
        if (a==g_word_december) return true;
        if (a==g_word_dec) return true;
        if (a==g_word_today) return true;
        if (a==g_word_yesterday) return true;
        if (a==g_word_tomorrow) return true;
        if (a==g_word_spring) return true;
        if (a==g_word_summer) return true;
        if (a==g_word_fall) return true;
        if (a==g_word_autumn) return true;
        if (a==g_word_winter) return true;
        
        //fix that....
        return false;
    }
    
    bool compareWordToTimeLotWordRegex(CWord a) {
        
        if (a==g_word_mondays) return true;
        if (a==g_word_monday) return true;
        if (a==g_word_tuesdays) return true;
        if (a==g_word_tuesday) return true;
        if (a==g_word_wednesdays) return true;
        if (a==g_word_wednesday) return true;
        if (a==g_word_thursdays) return true;
        if (a==g_word_thursday) return true;
        if (a==g_word_friday) return true;
        if (a==g_word_fridays) return true;
        if (a==g_word_saturdays) return true;
        if (a==g_word_saturday) return true;
        if (a==g_word_sundays) return true;
        if (a==g_word_sunday) return true;
        if (a==g_word_days) return true;
        if (a==g_word_day) return true;
        if (a==g_word_morning) return true;
        if (a==g_word_mornings) return true;
        if (a==g_word_evenings) return true;
        if (a==g_word_evening) return true;
        if (a==g_word_nights) return true;
        if (a==g_word_night) return true;
        //...
        if (a==g_word_january) return true;
        if (a==g_word_jan) return true;
        
        if (a==g_word_february) return true;
        if (a==g_word_feb) return true;
        
        if (a==g_word_march) return true;
        if (a==g_word_mar) return true;
        
        if (a==g_word_april) return true;
        if (a==g_word_apr) return true;
        
        if (a==g_word_may) return true;
        if (a==g_word_june) return true;
        if (a==g_word_july) return true;
        if (a==g_word_august) return true;
        if (a==g_word_aug) return true;
        if (a==g_word_september) return true;
        if (a==g_word_sept) return true;
        if (a==g_word_october) return true;
        if (a==g_word_oct) return true;
        if (a==g_word_november) return true;
        if (a==g_word_nov) return true;
        if (a==g_word_december) return true;
        if (a==g_word_dec) return true;
        if (a==g_word_today) return true;
        if (a==g_word_yesterday) return true;
        if (a==g_word_tomorrow) return true;
        if (a==g_word_spring) return true;
        if (a==g_word_summer) return true;
        if (a==g_word_fall) return true;
        if (a==g_word_autumn) return true;
        if (a==g_word_winter) return true;
        
        if (a==g_word_lot) return true;
        
        //fix that....
        
        return false;
    }
    
    //"/^(?i:am|isorder|are|r|be|being|'s|'re|'m|was|were|been|s|ai|seem|seems|seemed|
    //seeming|appear|appears|appeared|stay|stays|stayed|remain|remains|remained|resemble|resembles|resembled|resembling|become|becomes|became|becoming)$/";
    bool compareWordToCopularWordRegex(CWord a) {
        
        if (a==g_word_am) return true;
        if (a==g_word_is) return true;
        if (a==g_word_are) return true;
        if (a==g_word_r) return true;
        if (a==g_word_be) return true;
        if (a==g_word_being) return true;
        if (a==g_word_aps) return true;
        if (a==g_word_apre) return true;
        if (a==g_word_apm) return true;
        if (a==g_word_was) return true;
        if (a==g_word_were) return true;
        if (a==g_word_been) return true;
        if (a==g_word_s) return true;
        if (a==g_word_ai) return true;
        if (a==g_word_seem) return true;
        if (a==g_word_seems) return true;
        if (a==g_word_seemed) return true;
        if (a==g_word_seeming) return true;
        if (a==g_word_appear) return true;
        if (a==g_word_appears) return true;
        if (a==g_word_appeared) return true;
        if (a==g_word_stay) return true;
        //...
        if (a==g_word_stay) return true;
        if (a==g_word_stays) return true;
        
        if (a==g_word_stayed) return true;
        if (a==g_word_remain) return true;
        if (a==g_word_remains) return true;
        if (a==g_word_remained) return true;
        
        if (a==g_word_resemble) return true;
        if (a==g_word_resembles) return true;
        
        if (a==g_word_resembled) return true;
        if (a==g_word_resembling) return true;
        if (a==g_word_become) return true;
        if (a==g_word_becomes) return true;
        if (a==g_word_became) return true;
        if (a==g_word_becoming) return true;
        
        return false;
    }
    
    //private static final String passiveAuxWordRegex =
    //"/^(?i:am|is|are|r|be|being|'s|'re|'m|was|were|been|s|ai|seem|seems|seemed|seeming|appear|appears|appeared|become|becomes|became|becoming|get|got|getting|gets|gotten|remains|remained|remain)$/";
    bool compareWordToPassiveAuxWordRegex(CWord a) {
        
        if (a==g_word_am) return true;
        if (a==g_word_is) return true;
        if (a==g_word_are) return true;
        if (a==g_word_r) return true;
        if (a==g_word_be) return true;
        if (a==g_word_being) return true;
        if (a==g_word_aps) return true;
        if (a==g_word_apre) return true;
        if (a==g_word_apm) return true;
        if (a==g_word_was) return true;
        if (a==g_word_were) return true;
        if (a==g_word_been) return true;
        if (a==g_word_s) return true;
        if (a==g_word_ai) return true;
        if (a==g_word_seem) return true;
        if (a==g_word_seems) return true;
        if (a==g_word_seemed) return true;
        if (a==g_word_seeming) return true;
        if (a==g_word_appear) return true;
        if (a==g_word_appears) return true;
        if (a==g_word_appeared) return true;
        if (a==g_word_become) return true;
        //...
        if (a==g_word_becomes) return true;
        if (a==g_word_became) return true;
        if (a==g_word_becoming) return true;
        if (a==g_word_get) return true;
        if (a==g_word_got) return true;
        if (a==g_word_getting) return true;
        
        if (a==g_word_gets) return true;
        if (a==g_word_gotten) return true;
        
        if (a==g_word_remains) return true;
        if (a==g_word_remained) return true;
        if (a==g_word_remain) return true;
        
        return false;
    }
    
    
    //"/^(?i:am|is|are|r|be|being|'s|'re|'m|was|were|been|s|ai)$/";
    bool compareWordToBeAuxiliaryWordRegex(CWord a) {
        
        if (a==g_word_am) return true;
        if (a==g_word_is) return true;
        if (a==g_word_are) return true;
        if (a==g_word_r) return true;
        if (a==g_word_be) return true;
        if (a==g_word_being) return true;
        if (a==g_word_aps) return true;
        if (a==g_word_apre) return true;
        if (a==g_word_apm) return true;
        if (a==g_word_was) return true;
        if (a==g_word_were) return true;
        if (a==g_word_been) return true;
        if (a==g_word_s) return true;
        if (a==g_word_ai) return true;
        return false;
    }
    
    //"/^(?i:have|had|has|having)$/"
    bool compareWordToHaveWordRegex(CWord a) {
        
        if (a==g_word_have) return true;
        if (a==g_word_had) return true;
        if (a==g_word_has) return true;
        if (a==g_word_having) return true;
        return false;
    }
    
    
    //"/^(?i:stop|stops|stopped|stopping|keep|keeps|kept|keeping)$/";
    bool compareWordToStopWordRegex(CWord a) {
        
        if (a==g_word_stop) return true;
        if (a==g_word_stops) return true;
        if (a==g_word_stopped) return true;
        if (a==g_word_stopping) return true;
        if (a==g_word_keep) return true;
        if (a==g_word_keeps) return true;
        if (a==g_word_kept) return true;
        if (a==g_word_keeping) return true;
        return false;
    }
    
    
    bool compareWordToEitherNeitherBoth(CWord a) {
        
        if (a==g_word_either) return true;
        if (a==g_word_neither) return true;
        if (a==g_word_both) return true;
        return false;
    }
    
    bool compareWordToOnlyJustMerely(CWord a) {
        
        if (a==g_word_only) return true;
        if (a==g_word_just) return true;
        if (a==g_word_merely) return true;
        return false;
    }
    
    
    //==============================================================================
    
    
    //S <+ (VP) (VP < .. sthing)
    //it returns the first node that "breaks the chain" of VPs or another thing. In this case:S <+ (VP) (VP < NP), it would return the last NP
    
    //The chain cannot be temporal (vp*) because we are using m_umbinarized_subnodes.
    void findChain(CConstituent via_category, CConstituent target_category, const CStateNode* head, CStateNodeList*& candidates) {
        CStateNodeList* headChilds=head->m_umbinarizedSubNodes;
        while(headChilds) {
            const CStateNode* node=headChilds->node;
            if (CConstituent::clearTmp(node->constituent.code())==CConstituent::clearTmp(target_category.code())) {
                //candidates->add(node);
                CStateNodeList::add(candidates,node);
            }
            if (CConstituent::clearTmp(node->constituent.code())==CConstituent::clearTmp(via_category.code())) {
                findChain(via_category,target_category,node,candidates);
            }
            headChilds=headChilds->next;
        }
    }
    
    
    void findChainMultiCategory(CConstituentList* via_category, CConstituent target_category, const CStateNode* head, CStateNodeList*& candidates) {
        CStateNodeList* headChilds=head->m_umbinarizedSubNodes;
        while(headChilds) {
            const CStateNode* node=headChilds->node;
            if (CConstituent::clearTmp(node->constituent.code())==CConstituent::clearTmp(target_category.code())) {
                //candidates->add(node);
                CStateNodeList::add(candidates,node);
            }
            bool catCoincident=false;
            while(via_category!=0){
                if (CConstituent::clearTmp(node->constituent.code())==CConstituent::clearTmp(via_category->current.code())) {
                    catCoincident=true;
                }
                via_category=via_category->next;
            }
            if (catCoincident) {
                findChainMultiCategory(via_category,target_category,node,candidates);
            }
            headChilds=headChilds->next;
        }
    }
    
    void findChainTargetPos(CConstituent via_category, unsigned long target_category, const CStateNode* head, CStateNodeList*& candidates) {
        CStateNodeList* headChilds=head->m_umbinarizedSubNodes;
        while(headChilds) {
            const CStateNode* node=headChilds->node;
            if ((*words)[node->lexical_head].tag.code()==target_category){
                //candidates->add(node);
                CStateNodeList::add(candidates,node);
            }
            if (node->constituent==via_category) {
                findChainTargetPos(via_category,target_category,node,candidates);
            }
            headChilds=headChilds->next;
        }
    }
    
    void findChainViaPos(unsigned long via_category, CConstituent target_category, const CStateNode* head, CStateNodeList*& candidates) {
        CStateNodeList* headChilds=head->m_umbinarizedSubNodes;
        while(headChilds) {
            const CStateNode* node=headChilds->node;
            if (CConstituent::clearTmp(node->constituent.code())==CConstituent::clearTmp(target_category.code())) {
                //candidates->add(node);
                CStateNodeList::add(candidates,node);
            }
            if ((*words)[node->lexical_head].tag.code()==via_category){
                findChainViaPos(via_category,target_category,node,candidates);
            }
            headChilds=headChilds->next;
        }
    }
    
    
    
    
    
    void searchRecursivelyConst(CStateNodeList* childs, CConstituent constituent, CStateNodeList*& candidates){
        while(childs!=0){
            if (CConstituent::clearTmp(childs->node->constituent.code())==CConstituent::clearTmp(constituent.code())){
                CStateNodeList::add(candidates,childs->node);
            }
            searchRecursivelyConst(childs->node->m_umbinarizedSubNodes, constituent, candidates);
            //if (cs!=0) return cs;
            childs=childs->next;
        }
    }
    
    void listDescendants (CStateNodeList* childs, CStateNodeList*& candidates){
        while(childs!=0){
            CStateNodeList::add(candidates,childs->node);
            listDescendants(childs->node->m_umbinarizedSubNodes, candidates);
            //if (cs!=0) return cs;
            childs=childs->next;
        }
    }
    
    void listRightMostDescendants(CStateNodeList* childs, CStateNodeList*& candidates){
        while(childs!=0){
            if (childs->next==0){ //there is nothing more to the right, because it is the last one.
                CStateNodeList::add(candidates,childs->node);
                listRightMostDescendants(childs->node->m_umbinarizedSubNodes, candidates);
                //if (cs!=0) return cs;
            }
            childs=childs->next;
        }
    }
    
    void listLeftMostDescendants(CStateNodeList* childs, CStateNodeList*& candidates){
        if(childs!=0){ //it is the first, hence it is the leftmost.
            CStateNodeList::add(candidates,childs->node);
            listLeftMostDescendants(childs->node->m_umbinarizedSubNodes, candidates);
            //if (cs!=0) return cs;
        }
    }
    
    const CStateNode* findParent(const CStateNode* antecessor, const CStateNode* child){
        CStateNodeList* childsAnt=antecessor->m_umbinarizedSubNodes;
        while(childsAnt!=0){
            const CStateNode* parentCand=findParent(childsAnt->node,child);
            if (parentCand!=0) {
                return parentCand;
            }
            else {
                if (childsAnt->node==child){
                    return antecessor;
                }
            }
            childsAnt=childsAnt->next;
        }
        return 0;
    }
    
    //==================================================================================================
    //LEGEND
    //A << B:  A dominates B  m_subnodes
    //A < B: A immediately dominates B  m_umbinarizedsubnodes.
    //A $+ B: A is the immediately left sister of B
    //A $++ B: A is a left sister of B
    //A $- B: A is the immediately right sister of B.
    //A $-- B: A is the right sister of B
    //A <+(C) B: A dominates B via an unbroken chain of (zero or more) nodes matching description C
    //===================================================================================================
    
    /*bool isDangling(const CStateNode* head, const CStateNode* child){
     CStateNodeList* danglings=head->danglingSubNodes;
     while(danglings!=0){
     //std::cout<<"is dangling..."<<(*words)[danglings->node->lexical_head].word;
     if (danglings->node==child) return true;
     danglings=danglings->next;
     }
     return false;
     }*/
    
    bool isLinked(const CStateNode* head, const CStateNode* child) const {
        return head->linkedNodes.isset(child->lexical_head);
    }//Miguel
    
    void addLinked(CStateNode* head, const CStateNode* child){
        head->linkedNodes.set(child->lexical_head);
    }//Miguel
    
    /*void addLinkedConst(const CStateNode* head, const CStateNode* child){
     head->linkedNodes.set(child->lexical_head);
     }//Miguel*/
    
    
    /*void addDangling(const CStateNode* head, const CStateNode* child){
     CStateNodeList* danglings=head->danglingSubNodes;
     //danglings->add(child);
     //CStateNodeList::add(head->danglingSubNodes,child);
     CStateNodeList::add(danglings,child);
     }*/
    
    
    
    
#include "rules/acomp.cpp"
#include "rules/advcl.cpp"
#include "rules/advmod.cpp"
#include "rules/appos.cpp"
#include "rules/auxpass.cpp"
#include "rules/cop.cpp"
#include "rules/csubjpass.cpp"
#include "rules/det.cpp"
#include "rules/discourse.cpp"
#include "rules/goeswith.cpp"
#include "rules/infmod.cpp"
#include "rules/mark.cpp"
#include "rules/mwe.cpp"
#include "rules/neg.cpp"
#include "rules/nn.cpp"
#include "rules/npadvmod.cpp"
#include "rules/nsubj.cpp"
#include "rules/nsubjpass.cpp"
#include "rules/csubj.cpp"
#include "rules/auxi.cpp"
#include "rules/cc.cpp"
#include "rules/expl.cpp"
#include "rules/dobj.cpp"
#include "rules/iobj.cpp"
#include "rules/attr.cpp"
#include "rules/ccomp.cpp"
#include "rules/xcomp.cpp"
#include "rules/punct.cpp"
#include "rules/pobj.cpp"
#include "rules/pcomp.cpp"
#include "rules/conj.cpp"
#include "rules/amod.cpp"
#include "rules/num.cpp"
#include "rules/number.cpp"
#include "rules/parataxis.cpp"
#include "rules/partmod.cpp"
#include "rules/poss.cpp"
#include "rules/possessive.cpp"
#include "rules/preconj.cpp"
#include "rules/predet.cpp"
#include "rules/prep.cpp"
#include "rules/prt.cpp"
#include "rules/quantmod.cpp"
#include "rules/rcmod.cpp"
#include "rules/rel.cpp"
#include "rules/tmod.cpp"
    
    
    
    
    
    //"VP|S|SBAR|SBARQ|SINV|SQ=root < (CC|CONJP $-- !/^(?:``|-LRB-|PRN|PP|ADVP|RB)/) < (/^(?:PRN|``|''|-[LR]RB-|,|:|\\.)$/ $+ (/^S|SINV$|^(?:A|N|V|PP|PRP|J|W|R)/=target $-- (/^CC|CONJP|:|,$/ $-- (__ ># =root))) )",
    /*bool buildConj3(const unsigned long &cons){
        if (cons==PENN_CON_VP || cons==PENN_CON_S || cons==PENN_CON_SBAR || cons==PENN_CON_SBARQ || cons==PENN_CON_SINV || cons==PENN_CON_SQ) {
            
        }
        return false;
    }*///jm
    
    //"/^(?:ADJP|PP|(?:WH)?NP(?:-TMP|-ADV)?|ADVP|UCP(?:-TMP|-ADV)?|NX|NML)$/ < (CC|CONJP $-- !/^(?:``|-LRB-|PRN)$/) < (/^(?:PRN|``|''|-[LR]RB-|,|:|\\.)$/ $+ /^S|SINV$|^(?:A|N|V|PP|PRP|J|W|R)/=target)",
    // content phrase to the left of a comma for at least NX
    /*bool buildConj7(const unsigned long &cons){}*///jm
    
    //compareWordToHaveWordRegex
    // PENN_TAG_VERB, PENN_TAG_VERB_PAST, PENN_TAG_VERB_PROG, PENN_TAG_VERB_PAST_PARTICIPATE, PENN_TAG_VERB_PRES, PENN_TAG_VERB_THIRD_SINGLE
    
    //SEE MORE QUESTIONS TO JOHN IN CONJ1 and CONJ8 and APPOS5 (below)
    
    //CONJ1
    //"VP|S|SBAR|SBARQ|SINV|SQ < (CC|CONJP $-- !/^(?:``|-LRB-|PRN|PP|ADVP|RB)/ $+ !/^(?:PRN|``|''|-[LR]RB-|,|:|\\.)$/=target)",
    
    //"NX|NML < (CC|CONJP $- __) < (/^,$/ $- /^(?:A|N|V|PP|PRP|J|W|R|S)/=target)",
    // to take the conjunct in a preconjunct structure "either X or Y"
    /*bool buildConj8(const unsigned long &cons){
        if (cons==PENN_CON_NX){
            bool firstCond=false;
            CStateNodeList* childs=node.m_umbinarizedSubNodes;
            while(childs!=0){
                if (CConstituent::clearTmp(childs->node->constituent.code())==PENN_CON_CONJP || (*words)[childs->node->lexical_head].tag.code()==PENN_TAG_CC){
                    if (childs->previous!=0){
                        firstCond=true;
                    }
                }
                childs=childs->next;
            }
            
            if (firstCond){
                childs=node.m_umbinarizedSubNodes;
                while(childs!=0){
                    if ((*words)[childs->node->lexical_head].word==g_word_comma){
                        if (childs->previous!=0){
                            const CStateNode* targ=childs->previous->node;
                            ///^(?:A|N|V|PP|PRP|J|W|R|S)/=target)", ??
                            if ((CConstituent::clearTmp(targ->constituent.code())==PENN_CON_S
                                 ||CConstituent::clearTmp(targ->constituent.code())==PENN_CON_PP
                                 //||CConstituent::clearTmp(targ->constituent.code())==PENN_CON_PRP
                                 //||CConstituent::clearTmp(targ->constituent.code())==PENN_CON_S
                                 //||CConstituent::clearTmp(targ->constituent.code())==PENN_CON_S
                                 //||CConstituent::clearTmp(targ->constituent.code())==PENN_CON_S
                                 ||CConstituent::clearTmp(targ->constituent.code())==PENN_CON_S) && !isLinked(&node,targ)){
                                //    							  CDependencyLabel* label=new CDependencyLabel(STANFORD_DEP_CONJ);
                                if (buildStanfordLink(STANFORD_DEP_CONJ, targ->lexical_head, node.lexical_head)) {
                                    addLinked(&node,targ);
                                    return true;
                                }
                            }
                        }
                    }
                    childs=childs->next;
                }
            }
        }
        return false;
    }*///jm
    
    
    
    //"WHNP|WHNP-TMP|WHNP-ADV|NP|NP-TMP|NP-ADV < (PRN=target <, /^-LRB-$/ <- /^-RRB-$/ !<< /^(?:POS|(?:WP|PRP)\\$|[,$#]|CC|RB|CD)$/ <+(NP) (NNP|NN < /^(?:[A-Z]\\.?){2,}/) )"
    
   /* 
    bool appos5(const unsigned long &cons){
        if (cons==PENN_CON_WHNP || cons==PENN_CON_NP){
            CStateNodeList* childs=node.m_umbinarizedSubNodes;
            while(childs!=0){
                const CStateNode* targ=childs->node;
                if (CConstituent::clearTmp(targ->constituent.code())==PENN_CON_PRN && !isLinked(&node,targ)){
                    bool firstCond=false; //<, /^-LRB-$/
                    bool secondCond=false; // <- /^-RRB-$/
                    bool thirdCond=true; //!<< /^(?:POS|(?:WP|PRP)\\$|[,$#]|CC|RB|CD)$/
                    bool fourthCond=true; //<+(NP) (NNP|NN < /^(?:[A-Z]\\.?){2,}/)
                    
                    CStateNodeList* childsT=targ->m_umbinarizedSubNodes;
                    if (childsT!=0){
                        if ((*words)[childsT->node->lexical_head].tag.code()==PENN_TAG_L_BRACKET){
                            firstCond=true;
                        }
                    }
                    while(childsT!=0){
                        if ((*words)[childsT->node->lexical_head].tag.code()==PENN_TAG_R_BRACKET && childsT->next==0){
                            secondCond=true;
                        }
                        childsT=childsT->next;
                    }
                    
                    //void listDescendants (CStateNodeList* childs, CStateNodeList*& candidates){
                    if (firstCond && secondCond){
                        CStateNodeList* descendants=new CStateNodeList();
                        listDescendants(targ->m_umbinarizedSubNodes,descendants);
                        if (descendants->node==0){
                            descendants->clear();
                            descendants=0;
                        }
                        while(descendants!=0){
                            if (((*words)[descendants->node->lexical_head].tag.code()==PENN_TAG_POS)|| ((*words)[descendants->node->lexical_head].tag.code()==PENN_TAG_PRP)
                                || ((*words)[descendants->node->lexical_head].tag.code()==PENN_TAG_CC) || ((*words)[descendants->node->lexical_head].tag.code()==PENN_TAG_ADVERB)||
                                ((*words)[descendants->node->lexical_head].tag.code()==PENN_TAG_CD)){ //??????
                                thirdCond=false;
                            }
                            descendants=descendants->next;
                        }
                        if (thirdCond){
                            //<+(NP) (NNP|NN < /^(?:[A-Z]\\.?){2,}/)
                            CStateNodeList* chain=new CStateNodeList();
                            findChainTargetPos(PENN_CON_NP, PENN_TAG_NOUN, targ, chain);
                            findChainTargetPos(PENN_CON_NP, PENN_TAG_NOUN_PROPER, targ, chain);
                            if (chain->node==0){
                                chain->clear();
                                chain=0;
                            }
                            while(chain!=0){
                                //while(childsNN!=0){
                                if (false){
                                    fourthCond=true;
                                    //ASK JOHN ABOUT < /^(?:[A-Z]\\.?){2,}/
                                }
                                //childsNN=childsNN->next;
                                //}
                                chain=chain->next;
                            }
                        }
                    }
                    
                    if (firstCond && secondCond && thirdCond && fourthCond){
                        //             					 CDependencyLabel* label=new CDependencyLabel(STANFORD_DEP_APPOS);
                        if (buildStanfordLink(STANFORD_DEP_APPOS, targ->lexical_head, node.lexical_head)) {
                            addLinked(&node,targ);
                            return true;
                        }
                    }
                }
                childs=childs->next;
            }
        }
        return false;
    }*///jm
    
    
    
    //===============================================================================
    
    //conj rules. There are
    //(stf comment) this is more ugly, but the first 3 patterns are now duplicated and for clausal things, that daughter to the left of the CC/CONJP can't be a PP or RB or ADVP either
    
    //(stf comment) non-parenthetical or comma in suitable phrase with conjunction to left
    //"VP|S|SBAR|SBARQ|SINV|SQ < (CC|CONJP $-- !/^(?:``|-LRB-|PRN|PP|ADVP|RB)/ $+ !/^(?:PRN|``|''|-[LR]RB-|,|:|\\.)$/=target)",
    // non-parenthetical or comma in suitable phrase with conj then adverb to left
    //"VP|S|SBAR|SBARQ|SINV|SQ < (CC|CONJP $-- !/^(?:``|-LRB-|PRN|PP|ADVP|RB)/ $+ (ADVP $+ !/^(?:PRN|``|''|-[LR]RB-|,|:|\\.)$/=target))",
    // content phrase to the right of a comma or a parenthetical
    // The test at the end is to make sure that a conjunction or
    // comma etc actually show up between the target of the conj
    
    // dependency and the head of the phrase.  Otherwise, a
    // different relationship is probably more appropriate.
    //"VP|S|SBAR|SBARQ|SINV|SQ=root < (CC|CONJP $-- !/^(?:``|-LRB-|PRN|PP|ADVP|RB)/) < (/^(?:PRN|``|''|-[LR]RB-|,|:|\\.)$/ $+ (/^S|SINV$|^(?:A|N|V|PP|PRP|J|W|R)/=target $-- (/^CC|CONJP|:|,$/ $-- (__ ># =root))) )",
    // non-parenthetical or comma in suitable phrase with conjunction to left
    //"/^(?:ADJP|JJP|PP|QP|(?:WH)?NP(?:-TMP|-ADV)?|ADVP|UCP(?:-TMP|-ADV)?|NX|NML)$/ < (CC|CONJP $-- !/^(?:``|-LRB-|PRN)$/ $+ !/^(?:PRN|``|''|-[LR]RB-|,|:|\\.)$/=target)",
    // non-parenthetical or comma in suitable phrase with conj then adverb to left
    //"/^(?:ADJP|PP|(?:WH)?NP(?:-TMP|-ADV)?|ADVP|UCP(?:-TMP|-ADV)?|NX|NML)$/ < (CC|CONJP $-- !/^(?:``|-LRB-|PRN)$/ $+ (ADVP $+ !/^(?:PRN|``|''|-[LR]RB-|,|:|\\.)$/=target))",
    // content phrase to the right of a comma or a parenthetical
    //"/^(?:ADJP|PP|(?:WH)?NP(?:-TMP|-ADV)?|ADVP|UCP(?:-TMP|-ADV)?|NX|NML)$/ < (CC|CONJP $-- !/^(?:``|-LRB-|PRN)$/) < (/^(?:PRN|``|''|-[LR]RB-|,|:|\\.)$/ $+ /^S|SINV$|^(?:A|N|V|PP|PRP|J|W|R)/=target)",
    // content phrase to the left of a comma for at least NX
    //"NX|NML < (CC|CONJP $- __) < (/^,$/ $- /^(?:A|N|V|PP|PRP|J|W|R|S)/=target)",
    // to take the conjunct in a preconjunct structure "either X or Y"
    //"/^(?:VP|S|SBAR|SBARQ|SINV|ADJP|PP|QP|(?:WH)?NP(?:-TMP|-ADV)?|ADVP|UCP(?:-TMP|-ADV)?|NX|NML)$/ < (CC $++ (CC|CONJP $+ !/^(?:PRN|``|''|-[LR]RB-|,|:|\\.)$/=target))",
    
    
    
    //===============================================================================
    
    //cc coordination. THere is one rule.
    
    //"__ [ < (CC=target !< /^(?i:either|neither|both)$/ ) | < (CONJP=target !< (RB < /^(?i:not)$/ $+ (RB|JJ < /^(?i:only|just|merely)$/))) ]"
    
    //===============================================================================
    
    //punct punctuation. There are 2 rules.
    
    //"__ < /^(?:\\.|:|,|''|``|\\*|-LRB-|-RRB-|HYPH)$/=target",
    //"__ < (NFP=target !< /^(?:[<>]?[:;=8][\\-o\\*']?(?:-RRB-|-LRB-|[DPdpO\\/\\\\\\:}{@\\|\\[\\]])|(?:-RRB-|-LRB-|[DPdpO\\/\\\\\\:}{@\\|\\[\\]])[\\-o\\*']?[:;=8][<>]?)$/"
    //              + "!< /^(?:-LRB-)?[\\-\\^x=~<>'][_.]?[\\-\\^x=~<>'](?:-RRB-)?$/)"
    
    
    //===============================================================================
    
    //nsubjpass. THere is one rule.
    
    //"S|SQ < (WHNP|NP=target !< EX) < (VP < (/^(?:VB|AUX)/ < " + passiveAuxWordRegex + ")  < (VP < VBN|VBD))",
    //===============================================================================
    
    //csubj. Clausal subject. there is one rule.
    
    //"S < (SBAR|S=target !$+ /^,$/ $++ (VP !$-- NP))"
    
    //===============================================================================
    //csubjpass. There are 2 rules.
    
    //"S < (SBAR|S=target !$+ /^,$/ $++ (VP < (VP < VBN|VBD) < (/^(?:VB|AUXG?)/ < " + passiveAuxWordRegex + ") !$-- NP))",
    //"S < (SBAR|S=target !$+ /^,$/ $++ (VP <+(VP) (VP < VBN|VBD > (VP < (/^(?:VB|AUX)/ < " + passiveAuxWordRegex + "))) !$-- NP))"
    
    //===============================================================================
    //dobj, direct object. There are 8 rules.
    
    //"VP < (NP $+ (NP|WHNP=target !< (/^NN/ < " + timeWordLotRegex + "))) !<(/^(?:VB|AUX)/ < " + copularWordRegex + ")",  // this time one also included "lot"
    // match "give it next week"
    //"VP < (NP < (NP $+ (/^(NP|WHNP)$/=target !< (/^NN/ < " + timeWordLotRegex + "))))!< (/^(?:VB|AUX)/ < " + copularWordRegex + ")",  // this time one also included "lot"
    // basic direct object cases
    //"VP !<(/^(?:VB|AUX)/ < " + copularWordRegex + ") < (NP|WHNP=target [ [ !<# (/^NN/ < " + timeWordRegex + ") !$+ NP ] | $+ NP-TMP | $+ (NP <# (/^NN/ < " + timeWordRegex + ")) ] )",
    // cdm Jul 2010: No longer require WHNP as first child of SBARQ below: often not because of adverbials, quotes, etc., and removing restriction does no harm
    // this next pattern used to assume no empty NPs. Corrected.  If you adjust this pattern, also adjust the corresponding one for attr!
    //"SBARQ < (WHNP=target !< WRB !<# (/^NN/ < " + timeWordRegex + ")) <+(SQ|SINV|S|VP) (VP !< NP|TO !< (S < (VP < TO)) !< (/^(?:VB|AUX)/ < " + copularWordRegex + " $++ (VP < VBN|VBD)) !<- PRT !<- (PP <: IN) $-- (NP !< /^-NONE-$/))",
    // matches direct object in relative clauses "I saw the book that you bought"
    //"SBAR < (WHNP=target !< WRB) < (S < NP < (VP !< SBAR !<+(VP) (PP <- IN) !< (S < (VP < TO))))",
    // matches direct object in relative clauses "I saw the book that you said you bought"
    //"SBAR !< WHNP|WHADVP < (S < (@NP $++ (VP !$++ NP))) > (VP > (S < NP $- WHNP=target))",
    // matches direct object for long dependencies in relative clause without explicit relative pronouns
    //"SBAR !< (WHPP|WHNP|WHADVP) < (S < (@NP $+ (VP !< (/^(?:VB|AUX)/ < " + copularWordRegex + " !$+ VP)  !<+(VP) (/^(?:VB|AUX)/ < " + copularWordRegex + " $+ (VP < VBN|VBD)) !<+(VP) NP !< SBAR !<+(VP) (PP <- IN)))) !$-- CC $-- NP > NP=target",
    //"SBAR !< (WHPP|WHNP|WHADVP) < (S < (@NP $+ (ADVP $+ (VP !< (/^(?:VB|AUX)/ < " + copularWordRegex + " !$+ VP) !<+(VP) (/^(?:VB|AUX)/ < " + copularWordRegex + " $+ (VP < VBN|VBD)) !<+(VP) NP !< SBAR !<+(VP) (PP <- IN))))) !$-- CC $-- NP > NP=target"
    //===============================================================================
    //iobj, indirect object. There are 2 rules.
    
    //"VP < (NP=target !< /\\$/ !<# (/^NN/ < " + timeWordRegex + ") $+ (NP !<# (/^NN/ < " + timeWordRegex + ")))",
    // this next one was meant to fix common mistakes of our parser, but is perhaps too dangerous to keep
    //"VP < (NP=target < (NP !< /\\$/ $++ (NP !< (/^NN/ < " + timeWordLotRegex + ")) !$ CC|CONJP !$ /^,$/ !$++ /^:$/))",
    
    //===============================================================================
    //pobj, prepositional object. There are 8 rules.
    
    //"/^(?:PP(?:-TMP)?|(?:WH)?(?:PP|ADVP))$/ < (IN|VBG|TO|FW|RB|RBR $++ (/^(?:WH)?(?:NP|ADJP)(?:-TMP|-ADV)?$/=target !$- @NP))",
    // We allow ADVP with NP objects for cases like (ADVP earlier this year)
    //"/^PP(?:-TMP)?$/ < (/^(?:IN|VBG|TO)$/ $+ (ADVP=target [ < (RB < /^(?i:here|there)$/) | < (ADVP < /^NP(?:-TMP)?$/) ] ))",
    // second disjunct is weird ADVP, only matches 1 tree in 2-21
    // to deal with preposition stranding in questions (e.g., "Which city do you live in?") -- the preposition is sometimes treated as a particle by the parser (works well but doesn't preserve the tree structure!)
    //"PRT >- (VP !< (S < (VP < TO)) >+(SQ|SINV|S|VP) (SBARQ <, (WHNP=target !< WRB)) $-- (NP !< /^-NONE-$/))",
    //"(PP <: IN|TO) >- (VP !< (S < (VP < TO)) >+(SQ|SINV|S|VP) (SBARQ <, (WHNP=target !< WRB)) $-- (NP !< /^-NONE-$/))",
    //"(PP <: IN|TO) $- (NP $-- (VBZ|VBD) !$++ VP) >+(SQ) (SBARQ <, (WHNP=target !< WRB)) $-- (NP !< /^-NONE-$/)",
    // to deal with preposition stranding in relative clause (works well but doesn't preserve the tree structure!)
    //"(PP <- IN|TO) >+(@VP|S|SINV|SBAR) (SBAR !< (WHPP|WHNP) < (S < (NP $+ (VP !<(/^(?:VB|AUX)/ < " + copularWordRegex + " !$+ VP) !<+(VP) NP !< SBAR ))) $-- NP > NP=target)",
    //"XS|ADVP < (IN < /^(?i:at)$/) < JJS|DT=target", // at least, at most, at best, at worst, at all
    //"PP < (CC < less) < NP"
    
    //===============================================================================
    //pcomp, prepositional complement. There are 3 rules.
    
    //"@PP|WHPP < (IN|VBG|VBN|TO $+ @SBAR|S|PP|ADVP=target)", // no intervening NP; VBN is for "compared with"
    //"@PP|WHPP < (RB $+ @SBAR|S=target)", // RB is for weird tagging like "after/RB adjusting for inflation"
    //"@PP|WHPP !< IN|TO < (SBAR=target <, (IN $+ S))",
    
    
    //===============================================================================
    //attr attributive. There are 4 rules.
    
    //"VP < NP=target <(/^(?:VB|AUX)/ < " + copularWordRegex + ") !$ (NP < EX)",
    // "What is that?"
    //"SBARQ < (WHNP|WHADJP=target $+ (SQ < (/^(?:VB|AUX)/ < " + copularWordRegex + " !$++ VP) !< (VP <- (PP <:IN)) !<- (PP <: IN)))",
    //"SBARQ <, (WHNP|WHADJP=target !< WRB) <+(SQ|SINV|S|VP) (VP !< (S < (VP < TO)) < (/^(?:VB|AUX)/ < " + copularWordRegex + " $++ (VP < VBN|VBD)) !<- PRT !<- (PP <: IN) $-- (NP !< /^-NONE-$/))",
    //"Is he the man?"
    //"SQ <, (/^(?:VB|AUX)/ < " + copularWordRegex + ") < (NP=target $-- (NP !< EX))"
    
    //===============================================================================
    //ccomp clausal complement
    
    //"VP < (S=target < (VP !<, TO|VBG|VBN) !$-- NP)",
    //"VP < (SBAR=target < (S <+(S) VP) <, (IN|DT < /^(?i:that|whether)$/))",
    //"VP < (SBAR=target < (SBAR < (S <+(S) VP) <, (IN|DT < /^(?i:that|whether)$/)) < CC|CONJP)",
    //"VP < (SBAR=target < (S < VP) !$-- NP !<, (IN|WHADVP))",
    //"VP < (SBAR=target < (S < VP) !$-- NP <, (WHADVP < (WRB < /^(?i:how)$/)))",
    //"VP < (/^VB/ < " + haveRegex + ") < (S=target < @NP < VP)",
    //// to find "...", he said or "...?" he asked.
    //"S|SINV < (S|SBARQ=target $+ /^(,|\\.|'')$/ !$- /^(?:CC|:)$/ !< (VP < TO|VBG|VBN))",
    //"ADVP < (SBAR=target < (IN < /^(?i:as|that)/) < (S < (VP !< TO)))", // ADVP is things like "As long as they spend ..."
    //"ADJP < (SBAR=target !< (IN < as) < S)", // ADJP is things like "sure (that) he'll lose" or for/to ones or object of comparison with than "than we were led to expect"; Leave aside as in "as clever as we thought.
    // That ... he know
    //"S <, (SBAR=target <, (IN < /^(?i:that|whether)$/) !$+ VP)",
    // JJ catches a couple of funny NPs with heads like "enough"
    // Note that we eliminate SBAR which also match an infmod pattern
    //"@NP < JJ|NN|NNS < (SBAR=target [ !<(S < (VP < TO )) | !$-- NP|NN|NNP|NNS ] )"
    
    //===============================================================================
    //xcomp xclausal complement
    
    //"VP < (S=target !$- (NN < order) < (VP < TO))",    // used to have !> (VP < (VB|AUX < be))
    //"ADJP < (S=target <, (VP <, TO))",
    //"VP < (S=target !$- (NN < order) < (NP $+ NP|ADJP))",
    // to find "help sustain ...
    //"VP < (/^(?:VB|AUX)/ $+ (VP=target < VB < NP))",
    //"VP < (SBAR=target < (S !$- (NN < order) < (VP < TO))) !> (VP < (VB|AUX < be)) ",
    //"VP < (S=target !$- (NN < order) <: NP) > VP",
    // stop eating
    // note that we eliminate parentheticals and clauses that could match a partmod
    //"(VP < (S=target < (VP < VBG ) !< NP !$- (/^,$/ [$- @NP  |$- (@PP $-- @NP ) |$- (@ADVP $-- @NP)]) !$-- /^:$/))",
    
    //===============================================================================
    //rel, relative
    
    //"SBAR <, WHNP|WHPP|WHADJP=target > /^NP/ [ !<, /^WHNP/ | < (S < (VP $-- (/^NP/ !< /^-NONE-$/)))]"
    
    //===============================================================================
    
    //expl, expletitive
    
    //"S|SQ|SINV < (NP=target <+(NP) EX)"
    
    //===============================================================================
    
    //acomp adjectival complement
    
    //"VP [ < (ADJP=target !$-- NP) |  < (/^VB/ $+ (@S=target < (@ADJP < /^JJ/ ! $-- @NP|S))) ]",
    
    //===============================================================================
    
    //advcl, adverbial clause modifier
    
    //"VP < (@SBAR=target [ < (IN !< /^(?i:that|whether)$/) | <: (SINV <1 /^(?:VB|MD|AUX)/) | < (IN < that) < (RB|IN < so) ] )",
    //"S|SQ|SINV < (SBAR|SBAR-TMP=target <, (IN !< /^(?i:that|whether)$/ !$+ (NN < order)) !$-- /^(?!CC|CONJP|``|,|INTJ|PP(-.*)?).*$/ !$+ VP)",
    // to get "rather than"
    // "S|SQ|SINV < (SBAR|SBAR-TMP=target <2 (IN !< /^(?i:that|whether)$/ !$+ (NN < order)) !$-- /^(?!CC|CONJP|``|,|INTJ|PP(-.*)?$).*$/)",
    // "S|SQ|SINV < (SBAR|SBAR-TMP=target <, (IN !< /^(?i:that|whether)$/ !$+ (NN < order)) !$+ @VP $+ /^,$/ $++ @NP)", // this one might just be better, but at any rate license one with quotation marks or a conjunction beforehand
    // "SBARQ < (SBAR|SBAR-TMP|SBAR-ADV=target <, (IN !< /^(?i:that|whether)$/ !$+ (NN < order)) $+ /^,$/ $++ @SQ|S|SBARQ)", // the last part should probably only be @SQ, but this captures some strays at no cost
    // "VP < (SBAR|SBAR-TMP=target <, (WHADVP|WHNP < (WRB !< /^(?i:how)$/)) !< (S < (VP < TO)))", // added the (S < (VP <TO)) part so that "I tell them how to do so" doesn't get a wrong advcl
    // "S|SQ < (SBAR|SBAR-TMP=target <, (WHADVP|WHNP < (WRB !< /^(?i:how)$/)) !< (S < (VP < TO)))",
    
    //"@S < (@SBAR=target $++ @NP $++ @VP)",  // fronted adverbial clause
    //"@S < (@S=target < (VP < TO) $+ (/^,$/ $++ @NP))"
    
    
    
    
    //===============================================================================
    //"rcmod", "relative clause modifier",
    
    //"NP|WHNP|NML $++ (SBAR=target <+(SBAR) WHPP|WHNP) !$-- NP|WHNP|NML > @NP|WHNP",
    //"NP|WHNP|NML $++ (SBAR=target <: (S !<, (VP <, TO))) !$-- NP|WHNP|NLP > @NP|WHNP",
    // this next pattern is restricted to where and why because
    //"when" is usually incorrectly parsed: temporal clauses
    // are put inside the NP; 2nd is for case of relative
    // clauses with no relativizer (it doesn't distinguish
    // whether actually gapped).
    //"NP|NML $++ (SBAR=target < (WHADVP < (WRB </^(?i:where|why|when)/))) !$-- NP|NML > @NP",
    //"NP|WHNP|NML $++ RRC=target !$-- NP|WHNP|NML",
    //"@ADVP < (@ADVP < (RB < /where$/)) < @SBAR=target",
    
    //===============================================================================
    //mark marker.
    
    //"SBAR|SBAR-TMP < (IN|DT=target $++ S|FRAG)",
    //"SBAR < (IN|DT=target < that|whether) [ $-- /^(?:VB|AUX)/ | $- NP|NN|NNS | > ADJP|PP | > (@NP|UCP|SBAR < CC|CONJP $-- /^(?:VB|AUX)/) ]",
    
    //===============================================================================
    
    //amod, adjectival modifier
    
    // "/^(?:NP(?:-TMP|-ADV)?|NX|NML|NAC|WHNP)$/ < (ADJP|WHADJP|JJ|JJR|JJS|JJP|VBN|VBG|VBD|IN=target !< QP !$- CC)",
    // IN above is needed for "next" in "next week" etc., which is often tagged IN.
    //"ADJP !< CC|CONJP < (JJ|NNP $ JJ|NNP=target)",
    // Cover the case of "John, 34, works at Stanford" - similar to an expression for appos
    //"WHNP|WHNP-TMP|WHNP-ADV|NP|NP-TMP|NP-ADV < (NP=target <: CD $- /^,$/ $-- /^(?:WH)?NP/ !$ CC|CONJP)",
    //===============================================================================
    
    
    
    //===============================================================================
    
    
    
    bool buildStanfordLink(const unsigned long &label, int dependent, int head) {
        if (head==dependent) return false;
        
        CLink* newNode=new CLink(label, dependent, head, 0);
        newNode->next=this->node.stfLinks;
        node.stfLinks=newNode; //the new node (with the arc and label is added to the list)
        
        //      assert(m_lHeads[dependent] == DEPENDENCY_LINK_NO_HEAD);
        m_lHeads[dependent] = head;
        m_lLabels[dependent] = label;
        
        return true;
    }
    
    
    bool buildStanfordLinkForDebug(const unsigned long &label, int dependent, int head, int nsubjrule) {
        if (head==dependent) return false;
        
        CLink* newNode=new CLink(label, dependent, head, 0);
        newNode->next=this->node.stfLinks;
        node.stfLinks=newNode; //the new node (with the arc and label is added to the list)
        
        //      assert(m_lHeads[dependent] == DEPENDENCY_LINK_NO_HEAD);
        m_lHeads[dependent] = head;
        m_lLabels[dependent] = label;
        
        return true;
    }
    
    

   //===============================================================================
#ifdef TRAIN_LOSS
public:
   SCORE_TYPE actionLoss(const CAction &action, unsigned &correct, unsigned &plost, unsigned &rlost) const {
      static unsigned long constituent;
      if (action.isShift()) {
         computeShiftLB(0, correct, plost, rlost);
      }
      else if (action.isReduceRoot()) {
         computeTerminateLoss(0, correct, plost, rlost);
      }
      else if (action.isIdle()) {
         computeIdleLoss(0, correct, plost, rlost);
      }
      else if (action.singleChild()) {
         computeReduceUnaryLB(0, correct, plost, rlost, action.getConstituent());
      }
      else {
#ifdef NO_TEMP_CONSTITUENT
         constituent = action.getConstituent();
#else
         constituent = CConstituent::encodeTmp(action.getConstituent(), action.isTemporary());
#endif
         computeReduceBinaryLB(0, correct, plost, rlost, constituent);
      }
   }
   SCORE_TYPE actionFLoss(const CAction &action) const {
      static unsigned correct, plost, rlost;
      actionLoss(action, correct, plost, rlost);
      return FLoss(correct, plost, rlost);
   }
   SCORE_TYPE FLoss(const unsigned &correct, const unsigned &plost, const unsigned &rlost) const {
      static SCORE_TYPE p, r, f;
      if (correct == 0) {
         if (plost == 0 && rlost == 0) {
            return static_cast<SCORE_TYPE>(0);
         }
         else {
            return static_cast<SCORE_TYPE>(1);
         }
      }
      p = static_cast<SCORE_TYPE>(correct) / (correct + plost);
      r = static_cast<SCORE_TYPE>(correct) / (correct + rlost);
      f = 2*static_cast<SCORE_TYPE>(p)*r / (p + r);
      return 1-f;
   }
   SCORE_TYPE FLoss() const {
      return FLoss(correct_lb, plost_lb, rlost_lb);
   }
   SCORE_TYPE HammingLoss() const {
      return plost_lb + rlost_lb;
   }
   SCORE_TYPE stepHammingLoss() const {
      if (statePtr == 0)
         return 0;
      return plost_lb-statePtr->plost_lb + rlost_lb-statePtr->rlost_lb;
   }
   SCORE_TYPE actionHammingLoss(const CAction &action) const {
      static unsigned correct, plost, rlost;
      actionLoss(action, correct, plost, rlost);
      return plost + rlost;
   }
   SCORE_TYPE actionStepHammingLoss(const CAction &action) const {
      static unsigned correct, plost, rlost;
      actionLoss(action, correct, plost, rlost);
      return plost-plost_lb + rlost-rlost_lb;
   }
#endif
};

/*===============================================================
 *
 * scored actions
 *
 *==============================================================*/

class CScoredStateAction {

public:
   CAction action;
   const CStateItem *item;
   SCORE_TYPE score;

public:
   CScoredStateAction() : item(0), action(), score(0) {}
   void load(const CAction &action, const CStateItem *item, const SCORE_TYPE &score) {
      SCORE_TYPE item_sc;
      this->action = action;
      this->item = item;
      item_sc = item->score;
#ifdef SCALE
      item_sc *= item->size;
#endif
#ifdef TRAIN_LOSS
#define LOSS_ADD + item->actionStepHammingLoss(action)
//#define LOSS_ADD -std::sqrt(item->HammingLoss()) + std::sqrt(item->actionHammingLoss(action))
#else
#define LOSS_ADD
#endif
      this->score = item_sc + score LOSS_ADD;
#ifdef SCALE
      this->score /= (item->size + 1);
#endif
   }

public:
   bool operator < (const CScoredStateAction &a1) const { return score < a1.score; }
   bool operator > (const CScoredStateAction &a1) const { return score > a1.score; }
   bool operator <= (const CScoredStateAction &a1) const { return score <= a1.score; }
   bool operator >= (const CScoredStateAction &a1) const { return score >= a1.score; }

};

#endif
