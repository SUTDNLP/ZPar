// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * train.cpp - the training of the general constituent parser.  *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.8                         *
 *                                                              *
 ****************************************************************/

#include "definitions.h"
#include "conparser.h"
#include "reader.h"
#include "writer.h"

using namespace TARGET_LANGUAGE;

/*===============================================================
 *
 * auto_train - train by the parser itself, black-box training
 *
 *===============================================================*/

void process(const std::string &sInputFile, const std::string &sOutputFile){
	std::cerr<<"Converting start ..." << std::endl;

	std::ifstream is(sInputFile.c_str());
	ASSERT(is.is_open(), "The training file is unaccessible.");
	std::ofstream os(sOutputFile.c_str());

	static CSentenceParsed sent;

	int nCount=0;

	CConParser parser;
	CCoNLLOutput o_conll;
	is >> sent;
	while( ! sent.empty() ) {
		std::cerr << "Sentence " << nCount << " ... ";
		nCount ++;
		parser.convert( sent, &o_conll );
		os<<o_conll;
		os.flush();
		std::cerr << "done." << std::endl;
		is >> sent;
	}
	is.close();
	os.close();
	std::cerr << "Done. " << std::endl;
}
/*===============================================================
 *
 * main
 *
 *==============================================================*/

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "\nUsage: " << argv[0] << " input output" << std::endl;
		return 1;
	}
	process(argv[1], argv[2]);
	return 0;
}

