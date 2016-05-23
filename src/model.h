#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <cmath>

#include "vocabulary.h"
#include "fileparser.h"
using std::string;
using std::vector;

class Model 
{
public:
  Vocabulary word_counts;
  string topic;

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
      double prob = word_counts.computeProb(word);
      if (prob == 0.0)
        result += log(1/word_size());
      else
        result += log(prob);
    }
    return result;
  }

  unsigned long long word_size()
  {
    return word_counts.word_size;
  }
};

#endif
