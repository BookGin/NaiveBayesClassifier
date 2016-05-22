#include <iostream>

#include "model.h"
#include "filelistparser.h"
using std::vector;
using std::string;

int main()
{
  FileList file_list;
  parseFileList("./filelist", file_list);

  vector<Model> models;
  for (auto each: file_list) {
    const string& topic = each.first;
    const vector<string>& file_paths = each.second;
    models.push_back(Model(topic, file_paths));
  }

  for (Model model: models)
    for (auto each: model.word_counts.word_counts)
      std::cout << each.first << " " << each.second << std::endl;
}

