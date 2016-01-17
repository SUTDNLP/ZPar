#!/usr/bin/python

import sys

#===================================
# English application
#===================================
#english postagger: collins(default)
ENGLISH_TAGGER_IMPL = "collins"

#english constituency parser: jiangming, muhua(default), cad, cad-mvt, lin, miguel, srnew
ENGLISH_CONPARSER_IMPL = "muhua"

#english dependency parser: arceager(default), arcstandard, choi, choibasic
# 							emnlp08, liu, morphparser, punct, uppsala
ENGLISH_DEPPARSER_IMPL = "arceager"

#english character-based dependency parser:	arceager(default), arcstandard, arcstandard-loc
#											arcstandardfilter
ENGLISH_POSDEPPARSER_IMPL = "arceager"

#english dependency labeler: naive(default)
ENGLISH_DEPLABELER_IMPL = "naive"

#english constituency to stanford arc: jiangming_convert(default)
ENGLISH_STANFORD_CONVERTER = "jiangming_convert"


#===================================
# Chinese application
#===================================
#chinese postagger: agenda(default), agenda_mvt,segmented
CHINESE_TAGGER_IMPL = "agenda"

#chinese segmentor: agenda(default)
SEGMENTOR_IMPL = "agenda"

#chinese constituency parser: acl13(default), jcad
CHINESE_CONPARSER_IMPL = "acl13"

#chinese dependency parser: arceager(default), arceager-mvt, arceager-mvt-origin
#							arcstandard, choi, choibasic, emnlp08, liu, uppsala
CHINESE_DEPPARSER_IMPL = "arceager"

#chinese character-based dependency parser:	jcad, jcadeager
CHINESE_POSDEPPARSER_IMPL = "jcadeager"

#chinese dependency labeler: naive(default)
CHINESE_DEPLABELER_IMPL = "naive"

#===================================
# Generic applicatin
#===================================
#generic postagger: collins(default)
TAGGER_IMPL = "collins"

#generic constituency parser: srnew(default)
CONPARSER_IMPL = "srnew"

#generic dependency parser: arceager(default)
DEPPARSER_IMPL = "arceager"

#generic dependency labeler: naive(default)
DEPPARSER_IMPL = "naive"

#generic ccg parser: srnew(default)
CCGPARSER_IMPL = "srnew"

#===================================
# Spanish application
#===================================
#spanish postagger: collins(default)
SPANISH_TAGGER_IMPL = "collins"

#spanish dependency parser: arceager(default)
SPANISH_DEPPARSER_IMPL = "arceager"

#spanish depedndency labeler: naive(default)
SPANISH_DEPLABELER_IMPL = "naive"

def write_common_thing(cout):
	cout.write("${SOURCE_DIR}/libs/reader.cpp\n")
	cout.write("${SOURCE_DIR}/libs/writer.cpp\n")
	cout.write("${SOURCE_DIR}/libs/options.cpp\n")
	cout.write("${SOURCE_DIR}/libs/linguistics/lemma.cpp\n")
	cout.write("${SOURCE_DIR}/libs/linguistics/conll.cpp\n")
	cout.write("${SOURCE_DIR}/libs/learning/dbn.cpp\n")

def add_libs(cout, name, libs):
	if len(libs) != 0:
		cout.write("add_link_libraries ("+name+"\n")
		for lib in libs:
			cout.write(lib+"\n")
		cout.write(")\n")

def check(l):
	if len(l) != 2:
		return False
	if l[0] == "english":
		if not l[1] in ["tokenizer", "postagger", "conparser", "depparser", "deplabeler", "posdepparser", "converter"]:
			return False
	if l[0] == "chinese":
		if not l[1] in ["segmentor", "postagger", "conparser", "depparser", "deplabeler", "posdepparser"]:
			return False
	if l[0] == "generic":
		if not l[1] in ["ccgparser", "postagger", "conparser", "depparser", "deplabeler"]:
			return False
	if l[0] == "spanish":
		if not l[1] in ["postagger", "depparser", "deplabeler"]:
			return False
	return True

if check(sys.argv[1:]) == False:
	sys.stderr.write("./configure.py [language] [app]\n")
	sys.stderr.write("\t[language]\n")
	sys.stderr.write("\t\tenglish [app]\n")
	sys.stderr.write("\t\t\tpostagger|conparser|depparser|deplabeler|posdepparser|converter\n")
	sys.stderr.write("\t\tchinese [app]\n")
	sys.stderr.write("\t\t\tsegmentor|postagger|conparser|depparser|deplabeler|posdepparser\n")
	sys.stderr.write("\t\tgeneric [app]\n")
	sys.stderr.write("\t\t\tccgparser|postagger|conparser|depparser|deplabeler\n")
	sys.stderr.write("\t\tspanish [app]\n")
	sys.stderr.write("\t\t\tpostagger|depparser|deplabeler\n")
	sys.stderr.write("example: ./configure.py english postagger\n")
	exit(1)
out = open("CMakeLists.txt","w")

out.write("cmake_minimum_required (VERSION 2.8.0)\n")
out.write('project ("ZPar - A collections of sentence parsing tools")\n')
out.write("set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../dist/"+sys.argv[1]+"."+sys.argv[2]+")\n")
out.write("set (SOURCE_DIR             ${PROJECT_SOURCE_DIR}/src)\n")

libs=list()
for line in open("CMake.config"):
	line = line.strip()
	if line == "":
		continue
	if line[0] == "#":
		continue
	line = line.split()
	if line[0] == "libs":
		libs = line[1:]
	elif line[0] == "ENGLISH_TAGGER_IMPL":
		ENGLISH_TAGGER_IMPL = line[2]
	elif line[0] == "ENGLISH_CONPARSER_IMPL":
		ENGLISH_CONPARSER_IMPL = line[2]
	elif line[0] == "ENGLISH_DEPPARSER_IMPL":
		ENGLISH_DEPPARSER_IMPL = line[2]
	elif line[0] == "ENGLISH_POSDEPPARSER_IMPL":
		ENGLISH_POSDEPPARSER_IMPL = line[2]
	elif line[0] == "ENGLISH_DEPLABELER_IMPL":
		ENGLISH_DEPLABELER_IMPL = line[2]
	elif line[0] == "ENGLISH_STANFORD_CONVERTER":
		ENGLISH_STANFORD_CONVERTER = line[2];
	elif line[0] == "SEGMENTOR_IMPL":
		SEGMENTOR_IMPL = line[2]
	elif line[0] == "CHINESE_TAGGER_IMPL":
		CHINESE_TAGGER_IMPL = line[2]
	elif line[0] == "CHINESE_CONPARSER_IMPL":
		CHINESE_CONPARSER_IMPL = line[2]
	elif line[0] == "CHINESE_DEPPARSER_IMPL":
		CHINESE_DEPPARSER_IMPL = line[2]
	elif line[0] == "CHINESE_POSDEPPARSER_IMPL":
		CHINESE_POSDEPPARSER_IMPL = line[2]
	elif line[0] == "CHINESE_DEPLABELER_IMPL":
		CHINESE_DEPLABELER_IMPL = line[2]
	elif line[0] == "TAGGER_IMPL":
		TAGGER_IMPL = line[2]
	elif line[0] == "CONPARSER_IMPL":
		CONPARSER_IMPL = line[2]
	elif line[0] == "DEPPARSER_IMPL":
		DEPPARSER_IMPL = line[2]
	elif line[0] == "DEPPARSER_IMPL":
		DEPPARSER_IMPL = line[2]
	elif line[0] == "CCGPARSER_IMPL":
		CCGPARSER_IMPL = line[2]
	elif line[0] == "SPANISH_TAGGER_IMPL":
		SPANISH_TAGGER_IMPL = line[2]
	elif line[0] == "SPANISH_DEPPARSER_IMPL":
		SPANISH_DEPPARSER_IMPL = line[2]
	elif line[0] == "SPANISH_DEPLABELER_IMPL":
		SPANISH_DEPLABELER_IMPL = line[2]

out.write("include_directories (${SOURCE_DIR} ${SOURCE_DIR}/include)\n")
out.write("include_directories (${SOURCE_DIR}/"+sys.argv[1]+")\n")

if sys.argv[1] == "english":
	if sys.argv[2] == "tokenizer":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (tokenizer\n")
		out.write("${SOURCE_DIR}/english/tokenizer/tokenizer.cpp\n")
		out.write(")\n")

	elif sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER_IMPL+")\n")

		out.write("add_executable (tagger\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER_IMPL+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER_IMPL+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"tagger",libs)

		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER_IMPL+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER_IMPL+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)

	elif sys.argv[2] == "conparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONPARSER_IMPL+")\n")

		out.write("add_executable (conparser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONPARSER_IMPL+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONPARSER_IMPL+"/weight.cpp\n")
		if ENGLISH_CONPARSER_IMPL == "jiangming_phrase":
			out.write("${SOURCE_DIR}/common/conparser/main_phrase.cpp\n")
		elif ENGLISH_CONPARSER_IMPL == "jiangming_joint" or ENGLISH_CONPARSER_IMPL == "jiangming_base_joint":
			out.write("${SOURCE_DIR}/common/conparser/main_joint.cpp\n")
		else:
			out.write("${SOURCE_DIR}/common/conparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"conparser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONPARSER_IMPL+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONPARSER_IMPL+"/weight.cpp\n")
		if ENGLISH_CONPARSER_IMPL == "jiangming_phrase":
			out.write("${SOURCE_DIR}/common/conparser/train_phrase.cpp\n")
		elif ENGLISH_CONPARSER_IMPL == "jiangming_joint" or ENGLISH_CONPARSER_IMPL == "jiangming_base_joint":
			out.write("${SOURCE_DIR}/common/conparser/train_joint.cpp\n")
		else:
			out.write("${SOURCE_DIR}/common/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPPARSER_IMPL+")\n")

		out.write("add_executable (depparser\n")
		write_common_thing(out)
		if ENGLISH_DEPPARSER_IMPL == "morphparser":
			out.write("${SOURCE_DIR}/english/morph/morph.cpp\n")
			out.write("${SOURCE_DIR}/english/morph/penn_lexicon.cpp\n")
			out.write("${SOURCE_DIR}/english/morph/aux_lexicon.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPPARSER_IMPL+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPPARSER_IMPL+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"depparser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (train\n")
		if ENGLISH_DEPPARSER_IMPL == "morphparser":
			out.write("${SOURCE_DIR}/english/morph/morph.cpp\n")
			out.write("${SOURCE_DIR}/english/morph/penn_lexicon.cpp\n")
			out.write("${SOURCE_DIR}/english/morph/aux_lexicon.cpp\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPPARSER_IMPL+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPPARSER_IMPL+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "posdepparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/posdepparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPPARSER_IMPL+")\n")

		out.write("add_executable (posdepparser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPPARSER_IMPL+"/posdepparser.cpp\n")
		out.write("${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPPARSER_IMPL+"/posdepparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/posdepparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"posdepparser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPPARSER_IMPL+"/posdepparser.cpp\n")
		out.write("${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPPARSER_IMPL+"/posdepparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/posdepparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPLABELER_IMPL+")\n")

		out.write("add_executable (deplabeler\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPLABELER_IMPL+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPLABELER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"deplabeler",libs)

		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPLABELER_IMPL+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPLABELER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "converter":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_STANFORD_CONVERTER+")\n")

		out.write("add_executable (converter\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_STANFORD_CONVERTER+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_STANFORD_CONVERTER+"/main.cpp\n")
		out.write(")\n")
		add_libs(out,"converter",libs)

elif sys.argv[1] == "chinese":
	if sys.argv[2] == "segmentor":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/segmentor)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/segmentor/implementations/"+SEGMENTOR_IMPL+")\n")

		out.write("add_executable (segmentor\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/segmentor/"+SEGMENTOR_IMPL+".cpp\n")
		out.write("${SOURCE_DIR}/chinese/segmentor/main.cpp\n")
		out.write(")\n")
		add_libs(out,"segmentor",libs)

		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/segmentor/"+SEGMENTOR_IMPL+".cpp\n")
		out.write("${SOURCE_DIR}/chinese/segmentor/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	
	if sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER_IMPL+")\n")

		out.write("add_executable (tagger\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER_IMPL+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"tagger",libs)

		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER_IMPL+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "conparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONPARSER_IMPL+")\n")

		out.write("add_executable (conparser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/jointconstituent.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONPARSER_IMPL+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONPARSER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"conparser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/jointconstituent.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONPARSER_IMPL+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONPARSER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPPARSER_IMPL+")\n")

		out.write("add_executable (depparser\n")
		write_common_thing(out)
		if CHINESE_DEPPARSER_IMPL == "morphparser":
			out.write("${SOURCE_DIR}/chinese/morph/morph.cpp\n")
			out.write("${SOURCE_DIR}/chinese/morph/penn_lexicon.cpp\n")
			out.write("${SOURCE_DIR}/chinese/morph/aux_lexicon.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPPARSER_IMPL+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPPARSER_IMPL+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"depparser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (train\n")
		write_common_thing(out)
		if CHINESE_DEPPARSER_IMPL == "morphparser":
			out.write("${SOURCE_DIR}/chinese/morph/morph.cpp\n")
			out.write("${SOURCE_DIR}/chinese/morph/penn_lexicon.cpp\n")
			out.write("${SOURCE_DIR}/chinese/morph/aux_lexicon.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPPARSER_IMPL+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPPARSER_IMPL+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "posdepparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/posdepparser)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPPARSER_IMPL+")\n")

		out.write("add_executable (posdepparser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPPARSER_IMPL+"/posdepparser.cpp\n")
		out.write("${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPPARSER_IMPL+"/posdepparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/posdepparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"posdepparser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (chinese.posdepparser.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPPARSER_IMPL+"/posdepparser.cpp\n")
		out.write("${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPPARSER_IMPL+"/posdepparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/posdepparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPLABELER_IMPL+")\n")

		out.write("add_executable (deplabeler\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPLABELER_IMPL+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPLABELER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"deplabeler",libs)

		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPLABELER_IMPL+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPLABELER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "doc2snt":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG")\n')
		
		out.write("add_executable (doc2snt\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/doc2snt/doc2snt.cpp\n")
		out.write("${SOURCE_DIR}/chinese/doc2snt/main.cpp\n")
		out.write(")\n")

elif sys.argv[1] == "generic":
	if sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+")\n")

		out.write("add_executable (tagger\n")
		write_common_thing(out)
		if TAGGER_IMPL == "tweb":
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/tweb_wrapper.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/BaseExtractor.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Tagging.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/NNScorer.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/ChExtractor.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Sentence.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Config.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Analysis.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/EasyFirstPOS.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/EnExtractor.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/GlobalMap.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Pool.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Train.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Template.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/util.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"tagger",libs)

		out.write("add_executable (train\n")
		write_common_thing(out)
		if TAGGER_IMPL == "tweb":
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/tweb_wrapper.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/BaseExtractor.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Tagging.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/NNScorer.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/ChExtractor.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Sentence.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Config.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Analysis.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/EasyFirstPOS.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/EnExtractor.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/GlobalMap.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Pool.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Train.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/Template.cpp\n")
			out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/TWeb/src/util.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+TAGGER_IMPL+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "conparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DGENERIC_CONLABEL_SIZE=12 -DPERCEPTRON_FOR_DECODING -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+CONPARSER_IMPL+")\n")

		out.write("add_executable (conparser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/cfg/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+CONPARSER_IMPL+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+CONPARSER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"conparser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DGENERIC_CONLABEL_SIZE=12 -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/cfg/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+CONPARSER_IMPL+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+CONPARSER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+DEPPARSER_IMPL+")\n")

		out.write("add_executable (depparser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+DEPPARSER_IMPL+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+DEPPARSER_IMPL+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"depparser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+DEPPARSER_IMPL+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+DEPPARSER_IMPL+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+DEPPARSER_IMPL+")\n")

		out.write("add_executable (deplabeler\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+DEPPARSER_IMPL+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+DEPPARSER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"deplabeler",libs)

		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+DEPPARSER_IMPL+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+DEPPARSER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "ccgparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DNO_TEMP_CONSTITUENT -DGENERIC_CONLABEL_SIZE=12 -DFRAGMENTED_TREE -DPERCEPTRON_FOR_DECODING -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+CONPARSER_IMPL+")\n")

		out.write("add_executable (ccgparser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/cfg/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+CONPARSER_IMPL+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+CONPARSER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"ccgparser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DNO_TEMP_CONSTITUENT -DGENERIC_CONLABEL_SIZE=12 -DFRAGMENTED_TREE -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/cfg/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+CONPARSER_IMPL+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+CONPARSER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
elif sys.argv[1] == "spanish":
	if sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DES09_DEPENDENCIES -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER_IMPL+")\n")

		out.write("add_executable (tagger\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER_IMPL+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER_IMPL+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"tagger",libs)

		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER_IMPL+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER_IMPL+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)

	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DES09_DEPENDENCIES -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPPARSER_IMPL+")\n")

		out.write("add_executable (depparser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPPARSER_IMPL+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPPARSER_IMPL+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"depparser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DES09_DEPENDENCIES -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPPARSER_IMPL+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPPARSER_IMPL+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DES09_DEPENDENCIES -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPLABELER_IMPL+")\n")

		out.write("add_executable (deplabeler\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPLABELER_IMPL+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPLABELER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"deplabeler",libs)

		out.write("add_executable (train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPLABELER_IMPL+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPLABELER_IMPL+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"train",libs)
	
