// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * weight.cpp - the weight definition method                    *
 *                                                              *
 * Part of the dependency parser of english                     *
 *                                                              *
 * Yue Zhang                                                    *
 * 2007.8                                                       *
 *                                                              *
 ****************************************************************/

#include "posdepparser_weight.h"

using namespace TARGET_LANGUAGE;
using namespace TARGET_LANGUAGE::posdepparser;

/*---------------------------------------------------------------
 *
 * loadScores - load scores from the file specified at constructor
 *              currently this uses database, but it can be modified
 *         
 * Affects: m_bScoreModified, clearing it. 
 *
 *--------------------------------------------------------------*/

void TARGET_LANGUAGE::posdepparser::CWeight::loadScores() {
   clock_t time_start = clock();
   std::cout<<"Loading scores..."; std::cout.flush();
   std::ifstream file ; 
   std::string s;
   file.open(m_sRecordPath.c_str()) ;

   if (!file.is_open()) {
      std::cout << " empty." << std::endl; return;
   }

#ifdef LABELED
   getline(file, s);
   ASSERT(s=="Dependency labels:", "Dependency labels not found in model file") ;
   getline(file, s);
   std::istringstream iss(s);
   CDependencyLabel label;
   while(iss >> label);
   getline(file, s);
   ASSERT(s=="", "No empty line after the dependency labels") ;
#endif
   iterate_templates(file >>,;);

   getline(file, s);
   if (s=="Rules=1") {
      setRules(true);
   }
   else {
      ASSERT(s=="Rules=0", "Rules flag not found from the model file");
      setRules(false);
   }


   getline(file, s);
   ASSERT(s=="Word frequency", "Word frequency not found from model.");
   file >> m_mapWordFrequency;

   getline(file, s);
   ASSERT(s=="Char frequency", "Char frequency not found from model.");
   file >> m_mapCharFrequency;

   getline(file, s);
   ASSERT(s=="Maximum frequency", "Maximum frequency not found from model.");
   getline(file, s);
   std::istringstream iss_f(s);
//   iss.str(s);
   iss_f >> m_nMaxWordFrequency;

   getline(file, s);
   ASSERT(s=="Tag dictionary", "Tag dictionary not found from model.");
   file >>m_mapTagDictionary;

	getline(file, s);
	ASSERT(s=="Char tag dictionary", "Char tag dictionary not found from model.");
	file >>m_mapCharTagDictionary;

	getline(file, s);
	ASSERT(s=="Tag pair label dictionary", "Tag pair label dictionary not found from model.");
	file >>m_mapTagPairLabelDictionary;

	getline(file, s);
	ASSERT(s=="Tag pair dictionary", "Tag pair dictionary not found from model.");
	file >>m_mapTagPairDictionary;

   file.close() ;
   std::cout << " done. (" << double(clock()-time_start)/CLOCKS_PER_SEC << "s)" << std::endl;
}

/*---------------------------------------------------------------
 *
 * saveScores - save scores back to database
 *
 * This method is called by the destructor is m_bScoreModified
 * is true.
   std::cout<<"done."<<std::endl;
 *
 *--------------------------------------------------------------*/

void TARGET_LANGUAGE::posdepparser::CWeight::saveScores() {
   std::cout<<"Saving scores..."; std::cout.flush();
   std::ofstream file ;
   file.open(m_sRecordPath.c_str()) ;

#ifdef LABELED
   file << "Dependency labels:" << std::endl;
   for (unsigned label=CDependencyLabel::FIRST; label<CDependencyLabel::COUNT; ++label)
      file << CDependencyLabel(label) << ' ';
   file << std::endl << std::endl;
#endif
   iterate_templates(file<<,;)
#ifdef DEBUG
   iterate_templates(,.trace(););
#endif
   if (m_bRules) file << "Rules=1" << std::endl;
   else file << "Rules=0" << std::endl;

   file << "Word frequency" << std::endl;
   file << m_mapWordFrequency;
   file << "Char frequency" << std::endl;
   file << m_mapCharFrequency;
   file << "Maximum frequency" << std::endl;
   file << m_nMaxWordFrequency << std::endl;

   file <<"Tag dictionary" << std::endl;
   file <<m_mapTagDictionary;
   file <<"Char tag dictionary" << std::endl;
   file <<m_mapCharTagDictionary;
   file <<"Tag pair label dictionary" << std::endl;
   file <<m_mapTagPairLabelDictionary;
   file <<"Tag pair dictionary" << std::endl;
   file <<m_mapTagPairDictionary;

   file.close();
   std::cout<<" done."<<std::endl;
}

/*--------------------------------------------------------------
 *
 * computeAverageFeatureWeights - compute average feature weights
 *
 *-------------------------------------------------------------*/

void TARGET_LANGUAGE::posdepparser::CWeight::computeAverageFeatureWeights(int round) {
   std::cout<<"Computing averaged (total) feature vector..."; std::cout.flush();
   iterate_templates(,.computeAverage(round);) ;

   std::cout<<"done."<<std::endl;
}

