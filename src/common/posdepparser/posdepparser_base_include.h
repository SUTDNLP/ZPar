// Copyright (C) University of Oxford 2010
#define SIMPLE_HASH
#include "definitions.h"
#include "utils.h"
#include "tags.h"
#include "linguistics/word_tokenized.h"
#include "linguistics/taggedword.h"
#include "linguistics/dependency.h"
#include "knowledge/tagdict.h"
#ifdef LABELED
#include "linguistics/dependencylabel.h"
#endif
#ifdef LABELED
   typedef CLabeledDependencyTree CDependencyParse;
#else
   typedef CDependencyTree CDependencyParse;
#endif
#include "dep.h"
namespace TARGET_LANGUAGE { 
namespace posdepparser { 
#include "posdepparser_macros.h" 
}
}

#include "linguistics/conll.h"
#include "posdepparser_impl_inc.h"
#include "linguistics/tagset.h"
#include "options.h"

#include "stackfeats.h"

typedef std::vector< TARGET_LANGUAGE::posdepparser::CStackFeats > CSTackFeatsVec;
