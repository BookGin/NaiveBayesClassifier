#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>

using std::string;
using std::vector;
using std::unordered_map;

typedef unordered_map<string, vector<string>> FileList;

static FileList& build(std::ifstream &input_file, FileList &paths)
{
  string topic;
  string buf;
  input_file >> buf;
  while (!input_file.eof()) {
    if (buf.at(0) == ':') {
      topic = buf;
      topic.erase(topic.begin());
      assert(paths.find(topic) == paths.end());
      paths.insert({ topic, vector<string>()});
    } else {
      paths.at(topic).push_back(buf);
    }
    input_file >> buf;
  }
  return paths;
}

FileList& parseFileList(const string& path, FileList& file_list)
{
  std::ifstream input_file(path);
  if (!input_file) {
    perror(path.c_str());
    exit(EXIT_FAILURE);
  }
  
  file_list = build(input_file, file_list);
  input_file.close();
  return file_list;
}
