// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * main.cpp - main app of the general constituent parser.       *
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
#include "stdlib.h"
#include <strstream>

using namespace TARGET_LANGUAGE;

/*===============================================================
 *
 * decode
 *
 *==============================================================*/

void process(const std::string &sInputFile, const std::string &sOutputFile, const std::string &sFeatureFile, const std::string &sExtraFile,
const char cInputFormat,
#ifdef CONLL_OUTPUT
const char cOutputFormat,
#endif
int nBest, const bool bScores, const bool bBinary) {

   std::cerr << "Parsing started" << std::endl;
   int totaltime = 0;
   int time_start = clock();
   
   CConParser parser(sFeatureFile, false) ;
   CSentenceReader *input_reader=0;
   std::ifstream *is=0;
   if (cInputFormat=='c')
      is = new std::ifstream(sInputFile.c_str());
   else
      input_reader = new CSentenceReader(sInputFile);
   std::ofstream os(sOutputFile.c_str());
   std::ofstream *os_scores=0;
   conparser::SCORE_TYPE *scores=0;
   assert(os.is_open());
   static CTwoStringVector raw_input;
   static CSentenceMultiCon<CConstituent> con_input;
   CSentenceParsed *output_sent;
#ifdef CONLL_OUTPUT
   CCoNLLOutput* o_conll;
#endif

   int nCount=0;
   bool bReadSuccessful;

   if (bScores) {
      scores = new conparser::SCORE_TYPE[nBest];
      os_scores = new std::ofstream(std::string(sOutputFile+".scores").c_str());
   }
   output_sent = new CSentenceParsed[nBest];
#ifdef CONLL_OUTPUT 
   o_conll = new CCoNLLOutput[nBest];
#endif
   // Read the next exampl
   int size = -1;
   if (cInputFormat=='c') {
      bReadSuccessful = (bool)((*is)>>con_input);
   	  size = con_input.words.size();
   }
   else{
      bReadSuccessful = input_reader->readTaggedSentence(&raw_input, false, TAG_SEPARATOR);
   	  size = raw_input.size();
   }
   std::ifstream ifs(sExtraFile.c_str());
   parser.fire = 0;
   parser.extra_fire = 0;
   parser.parse_time = 0;
   parser.extra_parse_time = 0;
   while( bReadSuccessful ) {

	  std::string line;
	  std::vector< std::vector<std::string> > extra;
	  std::vector<std::string> extra_one;
	  getline(ifs,line);
	  std::istrstream istr(line.c_str());
	  std::string tmp;
	  while(istr>>tmp){
		if( tmp == "|||"){
			extra.push_back(extra_one);
			extra_one.clear();
			continue;
		}
		extra_one.push_back(tmp);
	  }
	  parser.setExtra(extra);
	  
	  ++nCount;
	  if(nCount%1000 == 0)
      std::cerr << "Sentence " << nCount << "...";
	  // Find decoder output
      int parse_time = clock();
#ifdef CONLL_OUTPUT
      if (cInputFormat=='c')
         parser.parse( con_input , output_sent , cOutputFormat=='b'?0:o_conll , nBest , scores ) ;
      else
         parser.parse( raw_input , output_sent , cOutputFormat=='b'?0:o_conll , nBest , scores ) ;
#else
      if (cInputFormat=='c')
         parser.parse( con_input , output_sent , nBest , scores ) ;
      else
         parser.parse( raw_input , output_sent , nBest , scores ) ;
#endif
      totaltime += clock() - parse_time;
      // Ouptut sent
      for (int i=0; i<nBest; ++i) {
#ifdef CONLL_OUTPUT
         if (cOutputFormat == 'b' || cOutputFormat == 'a') {
#endif
         if (bBinary)
            os << output_sent[i] ;
         else
            os << output_sent[i].str_unbinarized() << std::endl;
//		 if (bStanford)
//			save_stanford_relation(output_sent[i], os);
#ifdef CONLL_OUTPUT
         }
         if (cOutputFormat == 'c' || cOutputFormat == 'a')
            os << o_conll[i];
#endif
         if (bScores) *os_scores << scores[i] << std::endl;
      }
	  if(nBest != 1){
	  	os<< std::endl;
		if(bScores) *os_scores<<std::endl;
	  }
		if(nCount%1000 ==0)
      std::cerr << "done. " << std::endl;

      // Read the next example
      if (cInputFormat=='c') {
         bReadSuccessful = (bool)((*is)>>con_input);
		 size = con_input.words.size();
	  }
      else{
         bReadSuccessful = input_reader->readTaggedSentence(&raw_input, false, TAG_SEPARATOR);
   		 size = raw_input.size();
	  }
   }

   delete [] output_sent ;
#ifdef CONLL_OUTPUT
   delete [] o_conll;
#endif
   if (input_reader) delete input_reader;
   if (is) {is->close(); delete is;}
   os.close();

   if (bScores) {
      os_scores->close();
      delete os_scores;
      delete []scores;
   }
   std::cerr << "feature fire: "<< parser.fire + parser.extra_fire <<", extra feature fire: " << parser.extra_fire <<"\n";
   std::cerr << "Parsing has finished successfully. Total time taken is: " << double(clock()-time_start)/CLOCKS_PER_SEC << std::endl;
   std::cerr << "feature time: " << parser.parse_time << ", extra feature time: " << parser.extra_parse_time<< std::endl;
   std::cerr << "Parsing time: " << double(totaltime)/CLOCKS_PER_SEC << std::endl;
}

/*===============================================================
 *
 * main
 *
 *==============================================================*/

int main(int argc, char* argv[]) {
   try {
      COptions options(argc, argv);
      CConfigurations configurations;
      configurations.defineConfiguration("i", "r/c", "input format: r - pos-tagged sentence; c - pos-tagged and a list of constituents for each word", "r");
      configurations.defineConfiguration("b", "", "output binarized parse trees", "");
      configurations.defineConfiguration("n", "N", "N best list output", "1");
      configurations.defineConfiguration("s", "", "output scores to output_file.scores", "");
#ifdef CONLL_OUTPUT
      configurations.defineConfiguration("o", "b/c/a", "output format: b - bracked sentence; c - conll dependencies; a - both", "b");
#endif
      // check arguments
      if (options.args.size() != 5) {
         std::cout << "Usage: " << argv[0] << " input_file output_file model_file extra_soft_feature_file" << std::endl;
         std::cout << configurations.message() << std::endl;
         return 1;
      }
      configurations.loadConfigurations(options.opts);

      unsigned long nBest = 1;
      if (!fromString(nBest, configurations.getConfiguration("n"))) {
         std::cout << "The N best specification must be an integer." << std::endl;
         return 1;
      }
      bool bScores = configurations.getConfiguration("s").empty() ? false : true;
      bool bBinary = configurations.getConfiguration("b").empty() ? false : true;
	  char cInputFormat = configurations.getConfiguration("i") == "c" ? 'c' : 'r';
#ifdef CONLL_OUTPUT
      char cOutputFormat = configurations.getConfiguration("o").at(0);
#endif
      process(options.args[1], options.args[2], options.args[3], options.args[4],
              cInputFormat,
#ifdef CONLL_OUTPUT
              cOutputFormat,
#endif
              nBest, bScores, bBinary);
	  
   }
   catch (const std::string &e) {
      std::cerr << "Error: " << e << std::endl;
      exit(1);
   }

   return 0;
}

