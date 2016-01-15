include lib.config

DEBUG = -DNDEBUG

#================================================================
#
# directory configurations
#
#================================================================

BASE_DIR = .

SRC_DIR = $(BASE_DIR)/src
SRC_INCLUDES = $(SRC_DIR)/include
SRC_LIBS = $(SRC_DIR)/libs
SRC_COMMON = $(SRC_DIR)/common
SRC_CHINESE = $(SRC_DIR)/chinese
SRC_ENGLISH = $(SRC_DIR)/english
SRC_SPANISH = $(SRC_DIR)/spanish
SRC_GENERIC = $(SRC_DIR)/generic
SRC_JNI = $(SRC_DIR)/jni

OBJECT_DIR = $(BASE_DIR)/obj
OBJECT_INCLUDES = $(OBJECT_DIR)/include
OBJECT_LIBS = $(OBJECT_DIR)/libs
OBJECT_COMMON = $(OBJECT_DIR)/common
OBJECT_CHINESE = $(OBJECT_DIR)/chinese
OBJECT_ENGLISH = $(OBJECT_DIR)/english
OBJECT_SPANISH = $(OBJECT_DIR)/spanish
OBJECT_GENERIC = $(OBJECT_DIR)/generic
OBJECT_JNI = $(OBJECT_DIR)/jni

DIST_DIR = $(BASE_DIR)/dist
LIBS_DIR = $(BASE_DIR)/libs
#================================================================
#
# cross platform configurations
# 
#================================================================

ifeq ($(OS),Windows_NT)
#use good old GNU mkdir instead of MSDOS mkdir on Windows
MKDIR=gmkdir -p
else
MKDIR=mkdir -p
endif

#================================================================
#
# compiler commands
# 
#================================================================

INCLUDES = -I$(SRC_INCLUDES)
CXX = g++
CXXFLAGS = -w -W -O3 -fPIC $(INCLUDES) $(DEBUG)


$(OBJECT_LIBS)/reader.o: $(SRC_LIBS)/reader.cpp
	$(MKDIR) $(OBJECT_LIBS)
	$(MKDIR) $(OBJECT_LIBS)/linguistics
	$(MKDIR) $(OBJECT_LIBS)/learning
	$(CXX) $(CXXFLAGS) -c $(SRC_LIBS)/reader.cpp -o $(OBJECT_LIBS)/reader.o
$(OBJECT_LIBS)/writer.o: $(SRC_LIBS)/writer.cpp
	$(MKDIR) $(OBJECT_LIBS)
	$(MKDIR) $(OBJECT_LIBS)/linguistics
	$(MKDIR) $(OBJECT_LIBS)/learning
	$(CXX) $(CXXFLAGS) -c $(SRC_LIBS)/writer.cpp -o $(OBJECT_LIBS)/writer.o
$(OBJECT_LIBS)/options.o: $(SRC_LIBS)/options.cpp
	$(MKDIR) $(OBJECT_LIBS)
	$(MKDIR) $(OBJECT_LIBS)/linguistics
	$(MKDIR) $(OBJECT_LIBS)/learning
	$(CXX) $(CXXFLAGS) -c $(SRC_LIBS)/options.cpp -o $(OBJECT_LIBS)/options.o
$(OBJECT_LIBS)/linguistics/lemma.o: $(SRC_LIBS)/linguistics/lemma.cpp
	$(MKDIR) $(OBJECT_LIBS)
	$(MKDIR) $(OBJECT_LIBS)/linguistics
	$(MKDIR) $(OBJECT_LIBS)/learning
	$(CXX) $(CXXFLAGS) -c $(SRC_LIBS)/linguistics/lemma.cpp -o $(OBJECT_LIBS)/linguistics/lemma.o
$(OBJECT_LIBS)/linguistics/conll.o: $(SRC_LIBS)/linguistics/conll.cpp
	$(MKDIR) $(OBJECT_LIBS)
	$(MKDIR) $(OBJECT_LIBS)/linguistics
	$(MKDIR) $(OBJECT_LIBS)/learning
	$(CXX) $(CXXFLAGS) -c $(SRC_LIBS)/linguistics/conll.cpp -o $(OBJECT_LIBS)/linguistics/conll.o
$(OBJECT_LIBS)/learning/dbn.o: $(SRC_LIBS)/learning/dbn.cpp
	$(MKDIR) $(OBJECT_LIBS)
	$(MKDIR) $(OBJECT_LIBS)/linguistics
	$(MKDIR) $(OBJECT_LIBS)/learning
	$(CXX) $(CXXFLAGS) -c $(SRC_LIBS)/learning/dbn.cpp -o $(OBJECT_LIBS)/learning/dbn.o

english: english.postagger.${ENGLISH_TAGGER_IMPL} english.conparser.${ENGLISH_CONPARSER_IMPL} english.depparser.${ENGLISH_DEPPARSER_IMPL} english.deplabeler.${ENGLISH_DEPLABELER_IMPL} english.conparser.stanford_arc english.posdepparser.${ENGLISH_POSDEPPARSER_IMPL}

include Makefile.English.postagger

include Makefile.English.conparser

include Makefile.English.depparser

include Makefile.English.posdepparser

include Makefile.English.deplabeler

include Makefile.English.conparser.stanford_arc

chinese: chinese.segmentor.${CHINESE_SEGMENTOR} chinese.postagger.${CHINESE_TAGGER_IMPL} chinese.conparser.${CHINESE_CONPARSER_IMPL} chinese.depparser.${CHINESE_DEPPARSER_IMPL} chinese.deplabeler.${CHINESE_DEPLABELER_IMPL} chinese.posdepparser.${CHINESE_POSDEPPARSER_IMPL} chinese.doc2snt

include Makefile.Chinese.segmentor

include Makefile.Chinese.postagger

include Makefile.Chinese.conparser

include Makefile.Chinese.depparser

include Makefile.Chinese.posdepparser

include Makefile.Chinese.deplabeler

include Makefile.Chinese.doc2snt

generic: generic.postagger.${TAGGER_IMPL} generic.conparser.${CONPARSER_IMPL} generic.depparser.${DEPPARSER_IMPL} generic.deplabeler.${DEPLABELER_IMPL} generic.ccgparser.${CCG_PARSER}

include Makefile.Generic.ccgparser

include Makefile.Generic.postagger

include Makefile.Generic.conparser

include Makefile.Generic.depparser

include Makefile.Generic.deplabeler

spanish: spanish.postagger.${SPANISH_TAGGER_IMPL} spanish.depparser.${SPANISH_DEPPARSER_IMPL} spanish.deplabeler.${SPANISH_DEPLABELER_IMPL} 
include Makefile.Spanish.postagger

include Makefile.Spanish.depparser

include Makefile.Spanish.deplabeler
