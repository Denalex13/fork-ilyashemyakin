#include "Dictionary.h"
#include "HelpFunctions.h"

using namespace dnlx;

int main()
{
  std::system("chcp 1251 > nul");
  setlocale(LC_ALL, "");
  Dictionary dictionary;
  std::cout << "Eng-Rus Dictionary" << std::endl;
  std::cout << "Use HELP to see list of commands" << std::endl;

  while (!std::cin.eof())
  {
    std::cout << "\n$";
    std::string cmd = "";
    std::cin >> cmd;
    if (cmd == "INPUT")
    {
      std::string filename;
      std::cin >> filename;
      std::ifstream file(filename);
      if (!file.is_open())
      {
        std::cerr << "<FSTREAM ERROR>" << std::endl;
        continue;
      }

      std::string line = "";
      while (std::getline(file, line))
      {
        if (!lineInsert(dictionary, line))
        {
          std::cerr << "<READ ERROR>" << std::endl;
          continue;
        }
      }
      file.close();
    }
    else if (cmd == "PRINT")
    {
      printDictionary(std::cout, dictionary);
    }
    else if (cmd == "HELP")
    {
      help(std::cout);
    }
    else if (cmd == "STAT")
    {
      std::cout << "Number of words: " << dictionary.size() << std::endl;
    }
    else if (cmd == "ADD")
    {
      std::string word = "";
      std::getline(std::cin, word);
      std::string translation = "";
      std::cout << "Enter the translation: ";
      std::getline(std::cin, translation);
      if (!dictionary.add(word, translation))
      {
        std::cout << "<INPUT ERROR>" << std::endl;
      }
    }
    else if (cmd == "DELETE")
    {
      std::string word = "";
      std::getline(std::cin, word);
      if (!dictionary.deleteWord(word))
      {
        std::cout << "<WORD DOESN'T EXIST>" << std::endl;
      }
    }
    else if (cmd == "SEARCH")
    {
      std::string word = "";
      std::getline(std::cin, word);
      makeNormalStr(word);
      auto it = dictionary.search(word);
      if (it != dictionary.cend())
      {
        std::cout << it->first << " - ";
        printTranslations(std::cout, it->second);
      }
      else
      {
        std::cout << "<WORD DOESN'T EXIST>" << std::endl;
      }
    }
    else if (cmd != "")
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
