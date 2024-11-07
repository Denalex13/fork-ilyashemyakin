#include "HelpFunctions.h"

namespace dnlx
{
  bool isNormalStr(std::string& str)
  {
    return str.find_first_of("0123456789~!@#$;%:^&?*()-_+=[]{}|/'.,\n") == std::string::npos;
  }

  void makeNormalStr(std::string& str)
  {
    size_t start = str.find_first_not_of(" ");
    if (start == std::string::npos)
    {
      str.clear();
      return;
    }
    size_t end = str.find_last_not_of(" ");
    str = str.substr(start, end - start + 1);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  }

  bool lineInsert(Dictionary& dict, std::string& line)
  {
    std::istringstream iss(line);
    std::string key = "", translation = "";
    if (!std::getline(iss, key, '-'))
    {
      return false;
    }
    while (std::getline(iss, translation, ','))
    {
      dict.add(key, translation);
    }
    return true;
  }

  void printTranslations(std::ostream& out, const std::set<std::string>& set)
  {
    auto it = set.cbegin();
    if (it != set.cend())
    {
      out << *it;
      ++it;
    }
    while (it != set.cend())
    {
      out << ", " << *it;
      ++it;
    }
    out << "\n";
  }

  void printDictionary(std::ostream& out, Dictionary& dict)
  {
    auto it = dict.cbegin();
    while (it != dict.cend())
    {
      out << it->first << " - ";
      printTranslations(out, it->second);
      ++it;
    }
  }

  void printDictionary(std::ostream& out, const Dictionary& dict)
  {
    for (auto it = dict.cbegin(); it != dict.cend(); ++it)
    {
      out << it->first << " - ";
      auto translationsIt = it->second.cbegin();
      if (translationsIt != it->second.cend())
      {
        out << *translationsIt;
        ++translationsIt;
      }
      while (translationsIt != it->second.cend())
      {
        out << ", " << *translationsIt;
        ++translationsIt;
      }
      out << "\n";
    }
  }

  void help(std::ostream& out)
  {
    out << "Commands info: \n";
    out << "INPUT <filename.txt> - Get the dictionary from file.\n";
    out << "ADD <ENG_word> - Add a word to the dictionary.\n";
    out << "DELETE <ENG_word> - Delete a word from the dictionary.\n";
    out << "SEARCH <ENG_word> - Find the word and print it.\n";
    out << "PRINT - Print whole dictionary.\n";
    out << "STAT - Get dictionary info.\n";
    out << "HELP - For help.\n";
  }
}
