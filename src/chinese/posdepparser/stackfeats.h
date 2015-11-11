// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              *
 * supertag.h - the supertags for dependency parser in general  *
 *                                                              *
 * Author: Yue Zhang                                            *
 *                                                              *
 ****************************************************************/

#ifndef _POSDEPPARSER_STACKFEAT_H
#define _POSDEPPARSER_STACKFEAT_H



namespace TARGET_LANGUAGE {

namespace posdepparser {

class CStackFeats {

public:
	//neglect the feats "_"
     std::vector<std::string>  m_feats;


public:
     inline int getsize() const { return m_feats.size(); }
     inline bool empty() const { return m_feats.size()<=0; }
     inline std::string getfeat(int index) const { assert(index<m_feats.size()); return m_feats[index]; }


public:
   friend std::istream & operator >> (std::istream &is, CStackFeats &p);
   friend std::ostream & operator << (std::ostream &os, const CStackFeats &p);

};

//==============================================================================

inline std::istream & operator >> (std::istream &is, CStackFeats &p) {
   std::string s ; 
   getline(is, s);
   if (is && !(s.empty())) {
	   std::istringstream iss(s);
	   p.m_feats.clear();
	   std::string line;
	   getline(iss, line, '\t');
	   while (iss && !line.empty()) {
		   p.m_feats.push_back(line);
		   getline(iss, line, '\t');
	   }
   }
   else {
      THROW("No StackFeats read.");
   }
   return is;
}

//std::ostream & operator << (std::ostream &os, const TARGET_LANGUAGE::depparser::CSuperTag &p) {
inline std::ostream & operator << (std::ostream &os, const CStackFeats &p) {
   for (unsigned long i=0; i<p.m_feats.size(); ++i) {
      os << p.m_feats[i] << '\t';
   }
   os << std::endl;
   return os ;
}

} // namespace ddepparser
} // namespace TARGET_LANGUAGE



#endif

