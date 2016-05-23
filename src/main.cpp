#include <iostream>
#include <cmath>

#include "model.h"
#include "filelistparser.h"
#include "fileparser.h"

using std::vector;
using std::string;

int main()
{
  FileList file_list;
  parseFileList("./filelist", file_list);

  vector<Model> models;
  for (auto& each: file_list) {
    const string& topic = each.first;
    const vector<string>& file_paths = each.second;
    models.push_back(Model(topic, file_paths));
  }
  vector<string> words;
  words = parseFile("./qry", words);

  for (Model& model: models) {
    double result = 0.0;
    for (string& word: words) {
      double prob = model.computeProb(word);
      if (prob == 0.0)
        continue;
      result += log(prob);
    }
    std::cout << model.topic << " " << result << std::endl;
  }

/*
  for (Model& model: models)
    for (auto each: model.word_counts.word_counts)
      std::cout << each.first << " " << each.second << std::endl;
      */
}

