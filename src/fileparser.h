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

vector<string>& parseFile(const string& path, vector<string> &terms)
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
      terms.push_back(buf);
    input_file >> buf;
    buf = removeSymbol(buf);
  }
  input_file.close();

  return terms;
}
