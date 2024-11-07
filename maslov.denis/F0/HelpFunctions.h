#ifndef RGR_HELPFUNCTIONS_H
#define RGR_HELPFUNCTIONS_H
#include "Dictionary.h"

namespace dnlx
{
  bool isNormalStr(std::string& str);
  void makeNormalStr(std::string& str);
  bool lineInsert(Dictionary& dict, std::string& line);

  void printTranslations(std::ostream& out, const std::set<std::string>& set);
  void printDictionary(std::ostream& out, const Dictionary& dict);
  void help(std::ostream& out);
}
#endif
