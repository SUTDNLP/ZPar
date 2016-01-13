#!/usr/bin/python

import sys

#===================================
# English application
#===================================
#english postagger: collins(default)
ENGLISH_TAGGER = "collins"

#english constituency parser: jiangming, muhua(default), cad, cad-mvt, lin, miguel, srnew
ENGLISH_CONSTITUENCY_PARSER = "muhuan"

#english dependency parser: arceager(default), arcstandard, choi, choibasic
# 							emnlp08, liu, morphparser, punct, uppsala
ENGLISH_DEPENDENCY_PARSER = "arceager"

#english character-based dependency parser:	arceager(default), arcstandard, arcstandard-loc
#											arcstandardfilter
ENGLISH_POSDEPENDENCY_PARSER = "arceager"

#english dependency labeler: naive(default)
ENGLISH_DEPENDENCY_LABELER = "naive"

#english constituency to stanford arc: jiangming_convert(default)
ENGLISH_STANFORD_CONVERTER = "jiangming_convert"


#===================================
# Chinese application
#===================================
#chinese postagger: agenda(default), agenda_mvt,segmented
CHINESE_TAGGER = "agenda"

#chinese segmentor: agenda(default)
CHINESE_SEGMENTOR = "agenda"

#chinese constituency parser: acl13(default), jcad
CHINESE_CONSTITUENCY_PARSER = "acl13"

#chinese dependency parser: arceager(default), arceager-mvt, arceager-mvt-origin
#							arcstandard, choi, choibasic, emnlp08, liu, uppsala
CHINESE_DEPENDENCY_PARSER = "arceager"

#chinese character-based dependency parser:	jcad, jcadeager
CHINESE_POSDEPENDENCY_PARSER = "jcadeager"

#chinese dependency labeler: naive(default)
CHINESE_DEPENDENCY_LABELER = "naive"

#===================================
# Generic applicatin
#===================================
#generic postagger: collins(default)
GENERIC_TAGGER = "collins"

#generic constituency parser: srnew(default)
GENERIC_CONSTITUENCY_PARSER = "srnew"

#generic dependency parser: arceager(default)
GENERIC_DEPENDENCY_PARSER = "arceager"

#generic dependency labeler: naive(default)
GENERIC_DEPENDENCY_LABELER = "naive"

#generic ccg parser: srnew(default)
GENERIC_CCG_PARSER = "srnew"

#===================================
# Spanish application
#===================================
#spanish postagger: collins(default)
SPANISH_TAGGER = "collins"

#spanish dependency parser: arceager(default)
SPANISH_DEPENDENCY_PARSER = "arceager"

#spanish depedndency labeler: naive(default)
SPANISH_DEPENDENCY_LABELER = "naive"

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
		if not l[1] in ["postagger", "conparser", "depparser", "deplabeler", "posdepparser", "converter"]:
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
out.write("set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../dist)\n")
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
	elif line[0] == "ENGLISH_TAGGER":
		ENGLISH_TAGGER = line[2]
	elif line[0] == "ENGLISH_CONSTITUENCY_PARSER":
		ENGLISH_CONSTITUENCY_PARSER = line[2]
	elif line[0] == "ENGLISH_DEPENDENCY_PARSER":
		ENGLISH_DEPENDENCY_PARSER = line[2]
	elif line[0] == "ENGLISH_POSDEPENDENCY_PARSER":
		ENGLISH_POSDEPENDENCY_PARSER = line[2]
	elif line[0] == "ENGLISH_DEPENDENCY_LABELER":
		ENGLISH_DEPENDENCY_LABELER = line[2]
	elif line[0] == "ENGLISH_STANFORD_CONVERTER":
		ENGLISH_STANFORD_CONVERTER = line[2];
	elif line[0] == "CHINESE_SEGMENTOR":
		CHINESE_SEGMENTOR = line[2]
	elif line[0] == "CHINESE_TAGGER":
		CHINESE_TAGGER = line[2]
	elif line[0] == "CHINESE_CONSTITUENCY_PARSER":
		CHINESE_CONSTITUENCY_PARSER = line[2]
	elif line[0] == "CHINESE_DEPENDENCY_PARSER":
		CHINESE_DEPENDENCY_PARSER = line[2]
	elif line[0] == "CHINESE_POSDEPENDENCY_PARSER":
		CHINESE_POSDEPENDENCY_PARSER = line[2]
	elif line[0] == "CHINESE_DEPENDENCY_LABELER":
		CHINESE_DEPENDENCY_LABELER = line[2]
	elif line[0] == "GENERIC_TAGGER":
		GENERIC_TAGGER = line[2]
	elif line[0] == "GENERIC_CONSTITUENCY_PARSER":
		GENERIC_CONSTITUENCY_PARSER = line[2]
	elif line[0] == "GENERIC_DEPENDENCY_PARSER":
		GENERIC_DEPENDENCY_PARSER = line[2]
	elif line[0] == "GENERIC_DEPENDENCY_LABELER":
		GENERIC_DEPENDENCY_LABELER = line[2]
	elif line[0] == "GENERIC_CCG_PARSER":
		GENERIC_CCG_PARSER = line[2]
	elif line[0] == "SPANISH_TAGGER":
		SPANISH_TAGGER = line[2]
	elif line[0] == "SPANISH_DEPENDENCY_PARSER":
		SPANISH_DEPENDENCY_PARSER = line[2]
	elif line[0] == "SPANISH_DEPENDENCY_LABELER":
		SPANISH_DEPENDENCY_LABELER = line[2]

out.write("include_directories (${SOURCE_DIR} ${SOURCE_DIR}/include)\n")
out.write("include_directories (${SOURCE_DIR}/"+sys.argv[1]+")\n")

if sys.argv[1] == "english":
	if sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER+")\n")

		out.write("add_executable (english.postagger.tagger\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"english.postagger.tagger",libs)

		out.write("add_executable (english.postagger.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"english.postagger.train",libs)

	elif sys.argv[2] == "conparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONSTITUENCY_PARSER+")\n")

		out.write("add_executable (english.conparser.parser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONSTITUENCY_PARSER+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONSTITUENCY_PARSER+"/weight.cpp\n")
		if ENGLISH_CONSTITUENCY_PARSER == "jiangming_phrase":
			out.write("${SOURCE_DIR}/common/conparser/main_phrase.cpp\n")
		elif ENGLISH_CONSTITUENCY_PARSER == "jiangming_joint" or ENGLISH_CONSTITUENCY_PARSER == "jiangming_base_joint":
			out.write("${SOURCE_DIR}/common/conparser/main_joint.cpp\n")
		else:
			out.write("${SOURCE_DIR}/common/conparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"english.conparser.parser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (english.conparser.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONSTITUENCY_PARSER+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONSTITUENCY_PARSER+"/weight.cpp\n")
		if ENGLISH_CONSTITUENCY_PARSER == "jiangming_phrase":
			out.write("${SOURCE_DIR}/common/conparser/train_phrase.cpp\n")
		elif ENGLISH_CONSTITUENCY_PARSER == "jiangming_joint" or ENGLISH_CONSTITUENCY_PARSER == "jiangming_base_joint":
			out.write("${SOURCE_DIR}/common/conparser/train_joint.cpp\n")
		else:
			out.write("${SOURCE_DIR}/common/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"english.conparser.train",libs)
	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPENDENCY_PARSER+")\n")

		out.write("add_executable (english.depparser.parser\n")
		write_common_thing(out)
		if ENGLISH_DEPENDENCY_PARSER == "morphparser":
			out.write("${SOURCE_DIR}/english/morph/morph.cpp\n")
			out.write("${SOURCE_DIR}/english/morph/penn_lexicon.cpp\n")
			out.write("${SOURCE_DIR}/english/morph/aux_lexicon.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPENDENCY_PARSER+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPENDENCY_PARSER+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"english.depparser.parser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (english.depparser.train\n")
		if ENGLISH_DEPENDENCY_PARSER == "morphparser":
			out.write("${SOURCE_DIR}/english/morph/morph.cpp\n")
			out.write("${SOURCE_DIR}/english/morph/penn_lexicon.cpp\n")
			out.write("${SOURCE_DIR}/english/morph/aux_lexicon.cpp\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPENDENCY_PARSER+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPENDENCY_PARSER+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"english.depparser.train",libs)
	elif sys.argv[2] == "posdepparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/posdepparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPENDENCY_PARSER+")\n")

		out.write("add_executable (english.posdepparser.parser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPENDENCY_PARSER+"/posdepparser.cpp\n")
		out.write("${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPENDENCY_PARSER+"/posdepparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/posdepparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"english.posdepparser.parser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (english.posdepparser.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPENDENCY_PARSER+"/posdepparser.cpp\n")
		out.write("${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPENDENCY_PARSER+"/posdepparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/posdepparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"english.posdepparser.train",libs)
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPENDENCY_LABELER+")\n")

		out.write("add_executable (english.deplabeler.labeler\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPENDENCY_LABELER+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPENDENCY_LABELER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"english.deplabeler.labeler",libs)

		out.write("add_executable (english.deplabeler.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPENDENCY_LABELER+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPENDENCY_LABELER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"english.deplabeler.train",libs)
	elif sys.argv[2] == "converter":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_STANFORD_CONVERTER+")\n")

		out.write("add_executable (english.conparser.converter\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_STANFORD_CONVERTER+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_STANFORD_CONVERTER+"/main.cpp\n")
		out.write(")\n")
		add_libs(out,"english.conparser.converter",libs)

elif sys.argv[1] == "chinese":
	if sys.argv[2] == "segmentor":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/segmentor)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/segmentor/implementations/"+CHINESE_SEGMENTOR+")\n")

		out.write("add_executable (chinese.segmentor.segment\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/segmentor/"+CHINESE_SEGMENTOR+".cpp\n")
		out.write("${SOURCE_DIR}/chinese/segmentor/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.segmentor.segment",libs)

		out.write("add_executable (chinese.segmentor.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/segmentor/"+CHINESE_SEGMENTOR+".cpp\n")
		out.write("${SOURCE_DIR}/chinese/segmentor/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.segmentor.train",libs)
	
	if sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER+")\n")

		out.write("add_executable (chinese.postagger.tagger\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.postagger.tagger",libs)

		out.write("add_executable (chinese.postagger.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.postagger.train",libs)
	elif sys.argv[2] == "conparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONSTITUENCY_PARSER+")\n")

		out.write("add_executable (chinese.conparser.parser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/jointconstituent.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONSTITUENCY_PARSER+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONSTITUENCY_PARSER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.conparser.parser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (chinese.conparser.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/jointconstituent.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONSTITUENCY_PARSER+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONSTITUENCY_PARSER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.conparser.train",libs)
	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPENDENCY_PARSER+")\n")

		out.write("add_executable (chinese.depparser.parser\n")
		write_common_thing(out)
		if CHINESE_DEPENDENCY_PARSER == "morphparser":
			out.write("${SOURCE_DIR}/chinese/morph/morph.cpp\n")
			out.write("${SOURCE_DIR}/chinese/morph/penn_lexicon.cpp\n")
			out.write("${SOURCE_DIR}/chinese/morph/aux_lexicon.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPENDENCY_PARSER+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPENDENCY_PARSER+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.depparser.parser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (chinese.depparser.train\n")
		write_common_thing(out)
		if CHINESE_DEPENDENCY_PARSER == "morphparser":
			out.write("${SOURCE_DIR}/chinese/morph/morph.cpp\n")
			out.write("${SOURCE_DIR}/chinese/morph/penn_lexicon.cpp\n")
			out.write("${SOURCE_DIR}/chinese/morph/aux_lexicon.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPENDENCY_PARSER+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPENDENCY_PARSER+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.depparser.train",libs)
	elif sys.argv[2] == "posdepparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/posdepparser)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPENDENCY_PARSER+")\n")

		out.write("add_executable (chinese.posdepparser.parser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPENDENCY_PARSER+"/posdepparser.cpp\n")
		out.write("${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPENDENCY_PARSER+"/posdepparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/posdepparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.posdepparser.parser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (chinese.posdepparser.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPENDENCY_PARSER+"/posdepparser.cpp\n")
		out.write("${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPENDENCY_PARSER+"/posdepparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/chinese/posdepparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.posdepparser.train",libs)
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPENDENCY_LABELER+")\n")

		out.write("add_executable (chinese.deplabeler.labeler\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPENDENCY_LABELER+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPENDENCY_LABELER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.deplabeler.labeler",libs)

		out.write("add_executable (chinese.deplabeler.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPENDENCY_LABELER+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPENDENCY_LABELER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.deplabeler.train",libs)
	elif sys.argv[2] == "doc2snt":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG")\n')
		
		out.write("add_executable (chinese.doc2snt\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/chinese/doc2snt/doc2snt.cpp\n")
		out.write("${SOURCE_DIR}/chinese/doc2snt/main.cpp\n")
		out.write(")\n")

elif sys.argv[1] == "generic":
	if sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/"+GENERIC_TAGGER+")\n")

		out.write("add_executable (generic.postagger.tagger\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+GENERIC_TAGGER+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+GENERIC_TAGGER+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.postagger.tagger",libs)

		out.write("add_executable (generic.postagger.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+GENERIC_TAGGER+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+GENERIC_TAGGER+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.postagger.train",libs)
	elif sys.argv[2] == "conparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DGENERIC_CONLABEL_SIZE=12 -DPERCEPTRON_FOR_DECODING -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+")\n")

		out.write("add_executable (generic.conparser.parser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/cfg/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.conparser.parser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DGENERIC_CONLABEL_SIZE=12 -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (generic.conparser.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/cfg/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.conparser.train",libs)
	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DPERCEPTRON_FOR_DECODING -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+GENERIC_DEPENDENCY_PARSER+")\n")

		out.write("add_executable (generic.depparser.parser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+GENERIC_DEPENDENCY_PARSER+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+GENERIC_DEPENDENCY_PARSER+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.depparser.parser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (generic.depparser.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+GENERIC_DEPENDENCY_PARSER+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+GENERIC_DEPENDENCY_PARSER+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.depparser.train",libs)
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+GENERIC_DEPENDENCY_LABELER+")\n")

		out.write("add_executable (generic.deplabeler.labeler\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+GENERIC_DEPENDENCY_LABELER+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+GENERIC_DEPENDENCY_LABELER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.deplabeler.labeler",libs)

		out.write("add_executable (generic.deplabeler.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/generic/dependency/label/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+GENERIC_DEPENDENCY_LABELER+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+GENERIC_DEPENDENCY_LABELER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.deplabeler.train",libs)
	elif sys.argv[2] == "ccgparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DNO_TEMP_CONSTITUENT -DGENERIC_CONLABEL_SIZE=12 -DFRAGMENTED_TREE -DPERCEPTRON_FOR_DECODING -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+")\n")

		out.write("add_executable (generic.ccgparser.parser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/cfg/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.ccgparser.parser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DNO_TEMP_CONSTITUENT -DGENERIC_CONLABEL_SIZE=12 -DFRAGMENTED_TREE -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (generic.ccgparser.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/libs/linguistics/constituent.cpp\n")
		out.write("${SOURCE_DIR}/libs/linguistics/cfg/generic.cpp\n")
		out.write("${SOURCE_DIR}/generic/pos/generic.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+"/conparser.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.ccgparser.train",libs)
elif sys.argv[1] == "spanish":
	if sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DES09_DEPENDENCIES -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER+")\n")

		out.write("add_executable (spanish.postagger.tagger\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.postagger.tagger",libs)

		out.write("add_executable (spanish.postagger.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER+"/tagger.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER+"/tagger_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.postagger.train",libs)

	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DES09_DEPENDENCIES -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPENDENCY_PARSER+")\n")

		out.write("add_executable (spanish.depparser.parser\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPENDENCY_PARSER+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPENDENCY_PARSER+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.depparser.parser",libs)

		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DES09_DEPENDENCIES -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("add_executable (spanish.depparser.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPENDENCY_PARSER+"/depparser.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPENDENCY_PARSER+"/depparser_weight.cpp\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.depparser.train",libs)
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3 -DNDEBUG -DES09_DEPENDENCIES -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPENDENCY_LABELER+")\n")

		out.write("add_executable (spanish.deplabeler.labeler\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPENDENCY_LABELER+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPENDENCY_LABELER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.deplabeler.labeler",libs)

		out.write("add_executable (spanish.deplabeler.train\n")
		write_common_thing(out)
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPENDENCY_LABELER+"/deplabeler.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPENDENCY_LABELER+"/weight.cpp\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.deplabeler.train",libs)
	
