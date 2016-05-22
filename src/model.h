#include <string>
#include <vector>

#include "vocabulary.h"
#include "parser.h"
using std::string;
using std::vector;

class Model 
{
public:
  Vocabulary word_counts;
  string topic;
  string dir_path;

  Model(const string& model_topic, const vector<string>& paths) {
    topic = model_topic;
    dir_path = paths.at(0);
    build(paths);
  }

  void build(const vector<string>& paths)
  {
    vector<string> words;
    for (int i = 1; i < paths.size(); i++) {
      words = parse(paths.at(i), words);
      insert(words);
    }
  }

  void insert(const vector<string>& words)
  {
    for (string word: words)
      word_counts.insert(word);
  }

  double computeProb(const string &word) 
  {
    return word_counts.computeProb(word);
  }
};
