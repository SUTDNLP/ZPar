// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * main.cpp - main app of the general dependency parser.        *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 * Computing Laboratory, Oxford. 2007.8                         *
 *                                                              *
 ****************************************************************/

#include "definitions.h"
#include "posdepparser.h"
#include "reader.h"
#include "writer.h"
#include "stdlib.h"

using namespace TARGET_LANGUAGE;

/*===============================================================
 *
 * decode
 *
 *==============================================================*/

void process(const std::string sInputFile, const std::string sOutputFile, const std::string sFeatureFile, unsigned long nBest, const bool bScores, const std::string &sStackingPath) {

   std::cout << "Parsing started" << std::endl;

   int time_start = clock();

   CPosDepParser parser(sFeatureFile, false) ;
#ifdef SUPPORT_META_FEATURE_DEFINITION
   if (!sMetaPath.empty() )
      parser.loadMeta(sMetaPath);
#endif
   CSentenceReader *input_reader;
   std::ofstream os(sOutputFile.c_str());
   std::ofstream *os_scores=0;
   posdepparser::SCORE_TYPE *scores=0;
   assert(os.is_open());
   CStringVector input_sent;
   CDependencyParse *outout_sent; 

   input_reader = new CSentenceReader(sInputFile);


   CSTackFeatsVec  stackfeats;
   std::ifstream isstack;
   if(!sStackingPath.empty())
   {
	   isstack.open(sStackingPath.c_str());
	   assert(isstack.is_open());
   }

   int nCount=0;

   if (bScores) {
      scores = new posdepparser::SCORE_TYPE[nBest];
      os_scores = new std::ofstream(std::string(sOutputFile+".scores").c_str());
   }


   outout_sent = new CDependencyParse[nBest];
 
   // Read the next example
   bool  bReadSuccessful = input_reader->readSegmentedSentence(&input_sent, false);
   while( bReadSuccessful ) {

      TRACE("Sentence " << nCount);
      ++ nCount;

      if(isstack.is_open())
      {
    	   stackfeats.clear();
    	   std::string line;
    	   getline(isstack, line);

    	   while(isstack && !line.empty())
    	   {
    		   posdepparser::CStackFeats node;
    		   std::istringstream iss(rstrip(line));
    		   iss >> node ;
    		   stackfeats.push_back( node );
    		   getline(isstack, line);
    	   }
      }

      // check size
      if ( input_sent.size() > posdepparser::MAX_SENTENCE_SIZE ) {
         WARNING("The sentence is longer than system limitation, skipping it.");
         for (unsigned i=0; i<nBest; ++i) {
            outout_sent[i].clear();
            if (bScores) scores[i]=0;
         }
      }
      else {
          parser.parse( input_sent, outout_sent , stackfeats, nBest , scores ) ;
      }
      
      // Ouptut sent
      for (unsigned i=0; i<nBest; ++i) {
         os << outout_sent[i] ;
         if (bScores) *os_scores << scores[i] << std::endl;
      }
      
      // Read the next example
      bReadSuccessful = input_reader->readSegmentedSentence(&input_sent, false);
   }

   delete [] outout_sent ;
   os.close();

   if (bScores) {
      os_scores->close();
      delete os_scores;
      delete []scores;
   }

   delete input_reader;

   if(!sStackingPath.empty())
   {
	   isstack.close();
   }

   std::cout << "Parsing has finished successfully. Total time taken is: " << double(clock()-time_start)/CLOCKS_PER_SEC << std::endl;
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
      configurations.defineConfiguration("n", "N", "N best list outout", "1");
      configurations.defineConfiguration("s", "", "outout scores to outout_file.scores", "");
      configurations.defineConfiguration("e", "path", "external features for stacking", "");
      // check arguments
      if (options.args.size() != 4) {
         std::cout << "Usage: " << argv[0] << " input_file outout_file model_file" << std::endl;
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
      std::string sStackingPath = configurations.getConfiguration("e");

   
//      if (bCoNLL)
//         process_conll(options.args[1], options.args[2], options.args[3], nBest, bScores, sSuperPath);
//      else
      process(options.args[1], options.args[2], options.args[3], nBest, bScores, sStackingPath);
      return 0;
   } catch (const std::string &e) {
      std::cerr << "Error: " << e << std::endl;
      return 1;
   }
}

