#include <string>
#include <unordered_map>
using std::string;

class Vocabulary
{
public:
  std::unordered_map<string, int> word_counts;
  unsigned long long word_size = 0;

  Vocabulary() {}

  double computeProb(const string &word) 
  {
    if (word_counts.find(word) == word_counts.end())
      return 0.0;
    else
      return double(word_counts.at(word)) / double(word_size);
  }

  void insert(const string &word)
  {
    if (word_counts.find(word) == word_counts.end())
      word_counts.insert({word, 1});
    else
      word_counts.at(word) ++;

    word_size ++;
  }
};
