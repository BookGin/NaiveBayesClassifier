#include <string>
#include <vector>

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

  double computeProb(const string &word) 
  {
    return word_counts.computeProb(word);
  }
};
