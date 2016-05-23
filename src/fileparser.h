#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <algorithm>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>


using std::string;
using std::vector;

static bool deleteChars(const char c)
{
  return not isalnum(c);
}

static string& removeSymbol(string &buf)
{
  buf.erase(std::remove_if(buf.begin(), buf.end(), deleteChars), buf.end());
  return buf;
}

static vector<string>& parse(const string& path, vector<string> &words, bool need_remove_symbols)
{
  std::ifstream input_file(path);
  if (!input_file) {
    perror(path.c_str());
    exit(EXIT_FAILURE);
  }

  string buf;
  input_file >> buf;
  while (!input_file.eof()) {
    if (!buf.empty())
      words.push_back(buf);
    input_file >> buf;
    if (need_remove_symbols)
      buf = removeSymbol(buf);
  }
  input_file.close();

  return words;
}

vector<string>& parseFile(const string& path, vector<string> &words)
{
  return parse(path, words, true);
}

vector<string>& parseRawFile(const string& path, vector<string> &words)
{
  return parse(path, words, false);
}



#endif
