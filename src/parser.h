#include <algorithm>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>


using std::string;
using std::vector;

bool deleteChars(const char c)
{
  return not isalnum(c);
}

string& removeSymbol(string &buf)
{
  buf.erase(std::remove_if(buf.begin(), buf.end(), deleteChars), buf.end());
  return buf;
}

vector<string> &parse(const char *path, vector<string> &terms)
{
  std::ifstream input_file(path);
  if (!input_file)
    perror("fail");

  string buf;
  input_file >> buf;
  while (!input_file.eof()) {
    terms.push_back(buf);
    input_file >> buf;
    buf = removeSymbol(buf);
  }
  input_file.close();

  return terms;
}
