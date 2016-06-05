#include <iostream>
#include <cmath>
#include <cassert>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <unistd.h>
#include "model.h"
#include "filelistparser.h"
#include "fileparser.h"

#define ERROR_RANGE (0.001)

using std::vector;
using std::string;

typedef vector<Model> Models;

Models& buildModels(Models& models, FileList file_list)
{
  for (auto& each: file_list) {
    const string& topic = each.first;
    const vector<string>& file_paths = each.second;
    models.push_back(Model(topic, file_paths));
  }
  return models;
}

std::pair<string, double> label(vector<string>& query_words, Models& models) 
{
  double max_prob = - std::numeric_limits<double>::infinity();
  string max_prob_topic("UNDEFINED");
  for (Model& model: models) {
    double result = model.computeProb(query_words);
    if (result > max_prob) {
      max_prob = result;
      max_prob_topic = model.topic;
    }
  }
  assert(max_prob_topic != "UNDEFINED");
  return {max_prob_topic, max_prob};
}

std::pair<string, double> label(string& query_path, Models& models) 
{
  vector<string> query_words;
  query_words = parseFile(query_path, query_words);

  return label(query_words, models);
}


bool cmp(std::pair<string, int>& a, std::pair<string, int>& b)
{
  return a.second > b.second;
}

int getTotalDocNum(Models& models)
{
  int total = 0;
  for (Model& model: models)
    total += model.getDataSize();
  return total;
}

double getExpectation(Models& models) 
{
  double expectation = 0.0;
  for (Model& model: models)
    expectation += model.getExpectation();
  return expectation;
}

void maximizeTheta(Models& models) 
{
  int total_docs = getTotalDocNum(models);
  for (Model& model: models) 
    model.maximizeTheta(total_docs);
}

void resetUnlabel(Models& models) 
{
  for (Model& model: models)
    model.resetUnlabel();
}

void rebuildModel(Models& models, vector<vector<string>>& unlabel_words_set)
{
  resetUnlabel(models);
  for (vector<string>& unlabel_words: unlabel_words_set) {
    std::pair<string, double> result = label(unlabel_words, models);
    string& topic = result.first;
    double& prob = result.second;
    // TODO: optimize, needn't traverse models to find the corresponding topic
    for (Model& model: models)
      if (model.topic == topic)
        model.addUnlabel(prob);
  }
}

int main(int argc, char *argv[])
{
  FileList file_list;
  file_list = parseFileList(argv[1], file_list);

  Models models;
  models = buildModels(models, file_list);

  vector<string> unlabel_paths;
  unlabel_paths = parseRawFile(argv[3], unlabel_paths);
  vector<vector<string>> unlabel_words;
  for (string& path: unlabel_paths) {
    unlabel_words.push_back(vector<string>());
    unlabel_words.at(unlabel_words.size() - 1) = parseFile(path, unlabel_words.at(unlabel_words.size() - 1));
  }
  // label the unlabels 
  rebuildModel(models, unlabel_words);

  // E-step
  double expectation = getExpectation(models);
  double last_expectation = expectation - ERROR_RANGE * 10;

  while (expectation - last_expectation >= ERROR_RANGE) {
    last_expectation = expectation;
    // M-step
    maximizeTheta(models);

    // E-step
    // label the unlabels 
    rebuildModel(models, unlabel_words);

    expectation = getExpectation(models);
  }
  vector<string> query_paths;
  query_paths = parseRawFile(argv[2], query_paths);

  int query_index = 1;
  for (string& query_path: query_paths) {
    std::cout << query_index << " " << label(query_path, models).first << std::endl;
    query_index ++;
  }
/*
  for (Model& model: models)
    for (auto each: model.word_counts.word_counts)
      std::cout << each.first << " " << each.second << std::endl;
      */
}

