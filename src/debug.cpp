#include <iostream>
#include <cmath>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <utility>
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

bool cmp(std::pair<string, int>& a, std::pair<string, int>& b)
{
  return a.second > b.second;
}


int main(int argc, char *argv[])
{
  FileList file_list;
  file_list = parseFileList(argv[1], file_list);

  vector<Model> models;
  models = buildModels(models, file_list);
/*
  for (Model& model: models) {
    std::unordered_map<string, int> & umap = model.word_counts.word_counts;
    std::vector<std::pair<string, int> > vec(umap.begin(), umap.end());
    std::sort(vec.begin(), vec.end(), cmp);
    for (int i = 0; i < 20; i++)
      std::cerr << vec[i].first << std::endl;
  }
  return 0;
  */

  /*
  std::unordered_map<string, int> allmap;

  for (Model& model: models) {
    std::unordered_map<string, int> & umap = model.word_counts.word_counts;
    for (auto& each: umap)
      if (allmap.find(each.first) == allmap.end())
        allmap.insert({each.first, 1});
      else
        allmap.at(each.first) += each.second;
  }
  std::vector<std::pair<string, int> > vec(allmap.begin(), allmap.end());
  std::sort(vec.begin(), vec.end(), cmp);
  for (int i = 0; i < 20; i++)
    std::cerr << vec[i].first << std::endl;
  return 0;
  */
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

