// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * train.cpp - the training of the general dependency parser.   *
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

using namespace TARGET_LANGUAGE;

/*===============================================================
 *
 * auto_train - train by the parser itself, black-box training
 *
 *===============================================================*/

void auto_train(const std::string &sOutputFile, const std::string &sFeatureFile, const bool &bRules, const bool &bExtract, const std::string &sStackingPath) {

   std::cout << "Training iteration is started..." << std::endl ; std::cout.flush();

   CPosDepParser parser(sFeatureFile, true);
   parser.setRules(bRules);

   std::ifstream is(sOutputFile.c_str());
   assert(is.is_open());

   CDependencyParse ref_sent; 

   CSTackFeatsVec  stackfeats;

   std::ifstream isstack;
   if(!sStackingPath.empty())
   {
	   isstack.open(sStackingPath.c_str());
	   assert(isstack.is_open());
   }




   int nCount=0;
 
   while(  is>>ref_sent ) {

      TRACE("Sentence " << nCount);
      ++ nCount ; 


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

      /*
      std::cout << stackfeats.size() << std::endl;
      for(int idx = 0; idx < stackfeats.size(); idx++)
      {
    	  std::cout << stackfeats[idx].getsize() << ":\t";
    	  for(int idy = 0; idy < stackfeats[idx].getsize(); idy++)
    	  {
    		  std::cout << stackfeats[idx].getfeat(idy) << "\t";
    	  }
    	  std::cout << std::endl;
      }*/
      // example
      if (bExtract) {
#ifdef SUPPORT_FEATURE_EXTRACTION
         parser.extract_features( ref_sent , stackfeats );
#else
         ASSERT(false, "Internal error: feature extract not allowed but option set.");
#endif
      }
      else {
            parser.train( ref_sent , stackfeats, nCount );
      }
 
   }

   parser.finishtraining();

   std::cout << "Done. " << std::endl;

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
      configurations.defineConfiguration("e", "path", "external features for stacking", "");
      configurations.defineConfiguration("r", "", "use rules", "");
#ifdef SUPPORT_FEATURE_EXTRACTION
      configurations.defineConfiguration("f", "", "extract features only: weights will be counts", "");
#endif

      if (options.args.size() != 4) {
         std::cout << "\nUsage: " << argv[0] << " training_data model num_iterations" << std::endl ;
         std::cout << configurations.message() << std::endl;
         return 1;
      } 
      configurations.loadConfigurations(options.opts);
   
      int training_rounds;
      if (!fromString(training_rounds, options.args[3])) {
         std::cerr << "Error: the number of training iterations must be an integer." << std::endl;
         return 1;
      }
   
      bool bRules = configurations.getConfiguration("r").empty() ? false : true;
      bool bExtract = false;
#ifdef SUPPORT_FEATURE_EXTRACTION
      bExtract = configurations.getConfiguration("f").empty() ? false : true;
#endif

      std::string sStackingPath = configurations.getConfiguration("e");

      std::cout << "Training started" << std::endl;
      int time_start = clock();
      for (int i=0; i<training_rounds; ++i) 
         auto_train(options.args[1], options.args[2], bRules, bExtract, sStackingPath);
      std::cout << "Training has finished successfully. Total time taken is: " << double(clock()-time_start)/CLOCKS_PER_SEC << std::endl;
   
      return 0;
   } catch (const std::string &e) {
      std::cerr << std::endl << "Error: " << e << std::endl;
      return 1;
   }

}

