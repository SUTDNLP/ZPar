#!/usr/bin/python

import sys

#===================================
# English application
#===================================
#english postagger: collins(default)
ENGLISH_TAGGER = "collins"

#english constituency parser: jiangming, muhua(default), cad, cad-mvt, lin, miguel, srnew
ENGLISH_CONSTITUENCY_PARSER = "muhua"

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

def check(l):
	if len(l) != 2:
		return False
	if l[0] == "english":
		if not l[1] in ["standard", "postagger", "conparser", "depparser", "deplabeler", "posdepparser", "converter"]:
			return False
	if l[0] == "chinese":
		if not l[1] in ["standard", "segmentor", "postagger", "conparser", "depparser", "deplabeler", "posdepparser", "doc2snt"]:
			return False
	if l[0] == "generic":
		if not l[1] in ["standard", "ccgparser", "postagger", "conparser", "depparser", "deplabeler"]:
			return False
	if l[0] == "spanish":
		if not l[1] in ["standard", "postagger", "depparser", "deplabeler"]:
			return False
	return True

def add_libs(out,name,libs):
	out.write("target_link_libraries ("+name+"\n")
	for item in libs:
		out.write("\t"+item+"\n")
	out.write(")\n")

if check(sys.argv[1:]) == False:
	sys.stderr.write("./configure.py [language] [app]\n")
	sys.stderr.write("\t[language]\n")
	sys.stderr.write("\t\tenglish [app]\n")
	sys.stderr.write("\t\t\tstandard|postagger|conparser|depparser|deplabeler|posdepparser|converter\n")
	sys.stderr.write("\t\tchinese [app]\n")
	sys.stderr.write("\t\t\tstandard|segmentor|postagger|conparser|depparser|deplabeler|posdepparser\n")
	sys.stderr.write("\t\tgeneric [app]\n")
	sys.stderr.write("\t\t\tstandard|ccgparser|postagger|conparser|depparser|deplabeler\n")
	sys.stderr.write("\t\tspanish [app]\n")
	sys.stderr.write("\t\t\tstandard|postagger|depparser|deplabeler\n")
	sys.stderr.write("example: ./configure.py english postagger\n")
	exit(1)

libs=list()
for line in open("lib.config"):
	if sys.argv[2] == "standard":
		break;

	line = line.strip()
	if line == "":
		continue
	if line[0] == "#":
		continue
	line = line.split()
	if line[0] == "libs":
		libs = line[2:]
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


out = open("CMakeLists.txt","w")

out.write("cmake_minimum_required (VERSION 2.8.0)\n")
out.write('project ("ZPar - A collections of sentence parsing tools")\n')
out.write("set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)\n")
out.write("set (SOURCE_DIR             ${PROJECT_SOURCE_DIR}/src)\n")
out.write("include_directories (${SOURCE_DIR} ${SOURCE_DIR}/include)\n")
out.write("include_directories (${SOURCE_DIR}/"+sys.argv[1]+")\n")
out.write("link_directories (${PROJECT_SOURCE_DIR}/libmake/libs)\n")
if sys.argv[1] == "english":
	if sys.argv[2] == "standard":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3  -DPERCEPTRON_FOR_DECODING -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/collins)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/muhua)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/arceager)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/naive)\n")
		
		out.write("add_executable (zpar.en\n")
		out.write("${SOURCE_DIR}/english/zpar.en.cpp\n")
		out.write(")\n")
		add_libs(out, "zpar.en", ["english.postagger.collins", "english.conparser.muhua.decode",
									   "english.depparser.arceager.decode", "english.deplabeler.naive"])

	elif sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/"+ENGLISH_TAGGER+")\n")

		out.write("add_executable (english.postagger.tagger\n")
		out.write("${SOURCE_DIR}/common/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out, "english.postagger.tagger", ["english.postagger."+ENGLISH_TAGGER])
		out.write("add_executable (english.postagger.train\n")
		out.write("${SOURCE_DIR}/common/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out, "english.postagger.train", ["english.postagger."+ENGLISH_TAGGER])

	elif sys.argv[2] == "conparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3  -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_CONSTITUENCY_PARSER+")\n")

		out.write("add_executable (english.conparser.parser\n")
		if ENGLISH_CONSTITUENCY_PARSER == "jiangming_phrase":
			out.write("${SOURCE_DIR}/common/conparser/main_phrase.cpp\n")
		elif ENGLISH_CONSTITUENCY_PARSER == "jiangming_joint" or ENGLISH_CONSTITUENCY_PARSER == "jiangming_base_joint":
			out.write("${SOURCE_DIR}/common/conparser/main_joint.cpp\n")
		else:
			out.write("${SOURCE_DIR}/common/conparser/main.cpp\n")
		out.write(")\n")
		out.write('set_target_properties(english.conparser.parser PROPERTIES COMPILE_FLAGS "-DPERCEPTRON_FOR_DECODING")\n')
		add_libs(out, "english.conparser.parser", ["english.conparser."+ENGLISH_CONSTITUENCY_PARSER+".decode"])

		out.write("add_executable (english.conparser.train\n")
		if ENGLISH_CONSTITUENCY_PARSER == "jiangming_phrase":
			out.write("${SOURCE_DIR}/common/conparser/train_phrase.cpp\n")
		elif ENGLISH_CONSTITUENCY_PARSER == "jiangming_joint" or ENGLISH_CONSTITUENCY_PARSER == "jiangming_base_joint":
			out.write("${SOURCE_DIR}/common/conparser/train_joint.cpp\n")
		else:
			out.write("${SOURCE_DIR}/common/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out, "english.conparser.train", ["english.conparser."+ENGLISH_CONSTITUENCY_PARSER+".train"])

	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+ENGLISH_DEPENDENCY_PARSER+")\n")

		out.write("add_executable (english.depparser.parser\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		out.write('set_target_properties(english.depparser.parser PROPERTIES COMPILE_FLAGS "-DPERCEPTRON_FOR_DECODING")\n')
		add_libs(out, "english.depparser.parser", ["english.depparser."+ENGLISH_DEPENDENCY_PARSER+".decode"])
		out.write("add_executable (english.depparser.train\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out, "english.depparser.train", ["english.depparser."+ENGLISH_DEPENDENCY_PARSER+".train"])

	elif sys.argv[2] == "posdepparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/posdepparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/posdepparser/implementations/"+ENGLISH_POSDEPENDENCY_PARSER+")\n")

		out.write("add_executable (english.posdepparser.parser\n")
		out.write("${SOURCE_DIR}/common/posdepparser/main.cpp\n")
		out.write(")\n")
		out.write('set_target_properties(english.posdepparser.parser PROPERTIES COMPILE_FLAGS "-DPERCEPTRON_FOR_DECODING")\n')
		add_libs(out,"english.posdepparser.parser",["english.posdepparser."+ENGLISH_POSDEPENDENCY_PARSER+".decode"])
		out.write("add_executable (english.posdepparser.train\n")
		out.write("${SOURCE_DIR}/common/posdepparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"english.posdepparser.train",["english.posdepparser."+ENGLISH_POSDEPENDENCY_PARSER+".train"])

	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+ENGLISH_DEPENDENCY_LABELER+")\n")

		out.write("add_executable (english.deplabeler.labeler\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"english.deplabeler.labeler",["english.deplabeler."+ENGLISH_DEPENDENCY_LABELER])
		out.write("add_executable (english.deplabeler.train\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"english.deplabeler.train",["english.deplabeler."+ENGLISH_DEPENDENCY_LABELER])

	elif sys.argv[2] == "converter":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_STANFORD_CONVERTER+")\n")

		out.write("add_executable (english.conparser.converter\n")
		out.write("${SOURCE_DIR}/common/conparser/implementations/"+ENGLISH_STANFORD_CONVERTER+"/main.cpp\n")
		out.write(")\n")
		add_libs(out,"english.conparser.converter",["english.conparser.stanford_arc"])

elif sys.argv[1] == "chinese":
	if sys.argv[2] == "standard":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DLABELED -DTARGET_LANGUAGE=chinese")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/doc2snt)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/tagger/implementations/agenda)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/conparser/implementations/acl13)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/arceager)\n")

		out.write("add_executable (zpar.zh\n")
		out.write("${SOURCE_DIR}/chinese/zpar.cpp\n")
		out.write(")\n")
		add_libs(out,"zpar.zh", ["chinese.segmentor.agenda", "chinese.postagger.agenda",
									  "chinese.conparser.acl13.decode", "chinese.depparser.arceager.decode",
									  "chinese.doc2snt"])

	elif sys.argv[2] == "segmentor":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/segmentor)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/segmentor/implementations/"+CHINESE_SEGMENTOR+")\n")

		out.write("add_executable (chinese.segmentor.segment\n")
		out.write("${SOURCE_DIR}/chinese/segmentor/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.segmentor.segment",["chinese.segmentor."+CHINESE_SEGMENTOR])

		out.write("add_executable (chinese.segmentor.train\n")
		out.write("${SOURCE_DIR}/chinese/segmentor/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.segmentor.train",["chinese.segmentor."+CHINESE_SEGMENTOR])

	if sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/tagger/implementations/"+CHINESE_TAGGER+")\n")

		out.write("add_executable (chinese.postagger.tagger\n")
		out.write("${SOURCE_DIR}/chinese/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.postagger.tagger",["chinese.postagger."+CHINESE_TAGGER])

		out.write("add_executable (chinese.postagger.train\n")
		out.write("${SOURCE_DIR}/chinese/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.postagger.train",["chinese.postagger."+CHINESE_TAGGER])

	elif sys.argv[2] == "conparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/conparser/implementations/"+CHINESE_CONSTITUENCY_PARSER+")\n")

		out.write("add_executable (chinese.conparser.parser\n")
		out.write("${SOURCE_DIR}/chinese/conparser/main.cpp\n")
		out.write(")\n")
		out.write('set_target_properties(chinese.conparser.parser PROPERTIES COMPILE_FLAGS "-DPERCEPTRON_FOR_DECODING")\n')
		add_libs(out,"chinese.conparser.parser",["chinese.conparser."+CHINESE_CONSTITUENCY_PARSER+".decode"])
		out.write("add_executable (chinese.conparser.train\n")
		out.write("${SOURCE_DIR}/chinese/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.conparser.train",["chinese.conparser."+CHINESE_CONSTITUENCY_PARSER+".train"])
	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+CHINESE_DEPENDENCY_PARSER+")\n")

		out.write("add_executable (chinese.depparser.parser\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		out.write('set_target_properties(chinese.depparser.parser PROPERTIES COMPILE_FLAGS "-DPERCEPTRON_FOR_DECODING")\n')
		add_libs(out,"chinese.depparser.parser",["chinese.depparser."+CHINESE_DEPENDENCY_PARSER+".decode"])
		out.write("add_executable (chinese.depparser.train\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.depparser.train",["chinese.depparser."+CHINESE_DEPENDENCY_PARSER+".train"])
	elif sys.argv[2] == "posdepparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/chinese/posdepparser)\n")
		out.write("include_directories (${SOURCE_DIR}/chinese/posdepparser/implementations/"+CHINESE_POSDEPENDENCY_PARSER+")\n")

		out.write("add_executable (chinese.posdepparser.parser\n")
		out.write("${SOURCE_DIR}/chinese/posdepparser/main.cpp\n")
		out.write(")\n")
		out.write('set_target_properties(chinese.posdepparser.parser PROPERTIES COMPILE_FLAGS "-DPERCEPTRON_FOR_DECODING")\n')
		add_libs(out,"chinese.posdepparser.parser",["chinese.posdepparser."+CHINESE_POSDEPENDENCY_PARSER+".decode"])
		out.write("add_executable (chinese.posdepparser.train\n")
		out.write("${SOURCE_DIR}/chinese/posdepparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.posdepparser.train",["chinese.posdepparser."+CHINESE_POSDEPENDENCY_PARSER+".train"])
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+CHINESE_DEPENDENCY_LABELER+")\n")

		out.write("add_executable (chinese.deplabeler.labeler\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.deplabeler.labeler",["chinese.deplabeler."+CHINESE_DEPENDENCY_LABELER])
		out.write("add_executable (chinese.deplabeler.train\n")
		out.write("${SOURCE_DIR}/common/deplabeler/train.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.deplabeler.train",["chinese.deplabeler."+CHINESE_DEPENDENCY_LABELER])
	elif sys.argv[2] == "doc2snt":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG")\n')
		
		out.write("add_executable (chinese.doc2snt.do\n")
		out.write("${SOURCE_DIR}/chinese/doc2snt/main.cpp\n")
		out.write(")\n")
		add_libs(out,"chinese.doc2snt.do",["chinese.doc2snt"])

elif sys.argv[1] == "generic":
	if sys.argv[2] == "standard":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/collins)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/srnew)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/arceager)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/naive)\n")

		out.write("add_executable (zpar\n")
		out.write("${SOURCE_DIR}/generic/zpar.ge.cpp\n")
		out.write(")\n")
		add_libs(out, "zpar", ["generic.postagger.collins", "generic.conparser.srnew",
									   "generic.depparser.arceager", "generic.deplabeler.naive"])

	elif sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/"+GENERIC_TAGGER+")\n")

		out.write("add_executable (generic.postagger.tagger\n")
		out.write("${SOURCE_DIR}/common/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.postagger.tagger",["generic.postagger."+GENERIC_TAGGER])
		out.write("add_executable (generic.postagger.train\n")
		out.write("${SOURCE_DIR}/common/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.postagger.train",["generic.postagger."+GENERIC_TAGGER])
	elif sys.argv[2] == "conparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DGENERIC_CONLABEL_SIZE=12 -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+")\n")

		out.write("add_executable (generic.conparser.parser\n")
		out.write("${SOURCE_DIR}/common/conparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.conparser.parser",["generic.conparser."+GENERIC_CONSTITUENCY_PARSER])
		out.write("add_executable (generic.conparser.train\n")
		out.write("${SOURCE_DIR}/common/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.conparser.train",["generic.conparser."+GENERIC_CONSTITUENCY_PARSER])
	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+GENERIC_DEPENDENCY_PARSER+")\n")

		out.write("add_executable (generic.depparser.parser\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.depparser.parser",["generic.depparser."+GENERIC_DEPENDENCY_PARSER])
		out.write("add_executable (generic.depparser.train\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.depparser.train",["generic.depparser."+GENERIC_DEPENDENCY_PARSER])
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+GENERIC_DEPENDENCY_LABELER+")\n")

		out.write("add_executable (generic.deplabeler.labeler\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.deplabeler.labeler",["generic.deplabeler."+GENERIC_DEPENDENCY_LABELER])
		out.write("add_executable (generic.deplabeler.train\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.deplabeler.train",["generic.deplabeler."+GENERIC_DEPENDENCY_LABELER])
	elif sys.argv[2] == "ccgparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DNO_TEMP_CONSTITUENT -DGENERIC_CONLABEL_SIZE=12 -DFRAGMENTED_TREE -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/conparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/conparser/implementations/"+GENERIC_CONSTITUENCY_PARSER+")\n")

		out.write("add_executable (generic.ccgparser.parser\n")
		out.write("${SOURCE_DIR}/common/conparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.ccgparser.parser",["generic.ccg."+GENERIC_CONSTITUENCY_PARSER])
		out.write("add_executable (generic.ccgparser.train\n")
		out.write("${SOURCE_DIR}/common/conparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"generic.ccgparser.train",["generic.ccg."+GENERIC_CONSTITUENCY_PARSER])
elif sys.argv[1] == "spanish":
	if sys.argv[2] == "standard":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DES09_DEPENDENCIES -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/collins)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/arceager)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/naive)\n")

		out.write("add_executable (zpar.es\n")
		out.write("${SOURCE_DIR}/spanish/zpar.es.cpp\n")
		out.write(")\n")
		add_libs(out, "zpar.es", ["spanish.postagger.collins", "spanish.depparser.arceager", "spanish.deplabeler.naive"])


	elif sys.argv[2] == "postagger":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DES09_DEPENDENCIES -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/tagger)\n")
		out.write("include_directories (${SOURCE_DIR}/common/tagger/implementations/"+SPANISH_TAGGER+")\n")

		out.write("add_executable (spanish.postagger.tagger\n")
		out.write("${SOURCE_DIR}/common/tagger/main.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.postagger.tagger",["spanish.postagger."+SPANISH_TAGGER])
		out.write("add_executable (spanish.postagger.train\n")
		out.write("${SOURCE_DIR}/common/tagger/train.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.postagger.train",["spanish.postagger."+SPANISH_TAGGER])

	elif sys.argv[2] == "depparser":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DES09_DEPENDENCIES -DLABELED -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/depparser)\n")
		out.write("include_directories (${SOURCE_DIR}/common/depparser/implementations/"+SPANISH_DEPENDENCY_PARSER+")\n")

		out.write("add_executable (spanish.depparser.parser\n")
		out.write("${SOURCE_DIR}/common/depparser/main.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.depparser.parser",["spanish.depparser."+SPANISH_DEPENDENCY_PARSER])
		out.write("add_executable (spanish.depparser.train\n")
		out.write("${SOURCE_DIR}/common/depparser/train.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.depparser.train",["spanish.depparser."+SPANISH_DEPENDENCY_PARSER])
	elif sys.argv[2] == "deplabeler":
		out.write('set (CMAKE_CXX_FLAGS "-std=c++11 -g -w -W -O3   -DNDEBUG -DES09_DEPENDENCIES -DTARGET_LANGUAGE='+sys.argv[1]+'")\n')
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler)\n")
		out.write("include_directories (${SOURCE_DIR}/common/deplabeler/implementations/"+SPANISH_DEPENDENCY_LABELER+")\n")

		out.write("add_executable (spanish.deplabeler.labeler\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.deplabeler.labeler",["spanish.deplabeler."+SPANISH_DEPENDENCY_LABELER])
		out.write("add_executable (spanish.deplabeler.train\n")
		out.write("${SOURCE_DIR}/common/deplabeler/main.cpp\n")
		out.write(")\n")
		add_libs(out,"spanish.deplabeler.train",["spanish.deplabeler."+SPANISH_DEPENDENCY_LABELER])
	
