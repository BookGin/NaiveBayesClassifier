#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#include "vocabulary.h"
#include "fileparser.h"
using std::string;
using std::vector;

const string STOPWORD_LIST[] = {
"the",
"to",
"of",
"a",
"and",
"I",
"is",
"in",
"that",
"for",
"it",
"you",
"on",
"be",
"have",
"with",
"are",
"this",
"not",
"The"
};

class Model 
{
public:
  Vocabulary word_counts;
  int label_data_size = 0;
  vector<double> unlabel_probs;
  string topic;
  double theta = 0.05; // 20 News set

  Model(const string& model_topic, const vector<string>& paths) {
    topic = model_topic;
    build(paths);
  }

  void build(const vector<string>& paths)
  {
    vector<string> words;
    for (string path: paths) {
      words = parseFile(path, words);
      insert(words);
      label_data_size ++;
    }
  }

  void insert(const vector<string>& words)
  {
    for (string word: words)
      word_counts.insert(word);
  }

  double computeProb(vector<string>& words)
  {
    double result = 0.0;
    for (string& word: words) {
      //if (isStopword(word))
      // continue;
      double prob = word_counts.computeProb(word);
      result += log(prob);
    }
    result += log(theta);
    return result;
  }

  unsigned long long word_size()
  {
    return word_counts.word_size;
  }

  int getDataSize()
  {
    return label_data_size + unlabel_probs.size();
  }

  bool isStopword(string& word) 
  {
    for (unsigned int i = 0; i < sizeof(STOPWORD_LIST) / sizeof(STOPWORD_LIST[0]); i++)
      if (word == STOPWORD_LIST[i])
        return true;

    return false;
  }

  void resetUnlabel()
  {
    unlabel_probs.clear();
  }

  void addUnlabel(double prob)
  {
    unlabel_probs.push_back(prob);
  }

  double getExpectation()
  {
    double expectation = 0.0;
    for (double& prob: unlabel_probs)
      expectation += prob;
    expectation += log(theta);
    return expectation;
  }

  void maximizeTheta(int total_docs)
  {
    theta = double(label_data_size + unlabel_probs.size()) / double(total_docs);
  }
};

#endif
