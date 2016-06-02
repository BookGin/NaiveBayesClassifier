#include <iostream>
#include <cmath>
#include <limits>

#include "model.h"
#include "filelistparser.h"
#include "fileparser.h"

using std::vector;
using std::string;

vector<Model>& buildModels(vector<Model>& models, FileList file_list)
{
  for (auto& each: file_list) {
    const string& topic = each.first;
    const vector<string>& file_paths = each.second;
    models.push_back(Model(topic, file_paths));
  }
  return models;
}

string label(string& query_path, vector<Model>& models) 
{
  vector<string> query_words;
  query_words = parseFile(query_path, query_words);

  double max_prob = - std::numeric_limits<double>::infinity();
  string max_prob_topic("UNDEFINED");
  for (Model& model: models) {
    double result = model.computeProb(query_words);
    if (result > max_prob) {
      max_prob = result;
      max_prob_topic = model.topic;
    }
  }
  return max_prob_topic;
}

int main(int argc, char *argv[])
{
  FileList file_list;
  file_list = parseFileList(argv[1], file_list);

  vector<Model> models;
  models = buildModels(models, file_list);

  vector<string> query_paths;
  query_paths = parseRawFile(argv[2], query_paths);

  int query_index = 1;
  for (string& query_path: query_paths) {
    std::cout << query_index << " " << label(query_path, models) << std::endl;
    query_index ++;
  }
/*
  for (Model& model: models)
    for (auto each: model.word_counts.word_counts)
      std::cout << each.first << " " << each.second << std::endl;
      */
}

