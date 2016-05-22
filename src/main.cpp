#include <iostream>

#include "model.h"
using std::vector;
using std::string;

int main()
{
  vector<string> paths;
  paths.push_back("./20news/Train/comp.windows.x/");
  paths.push_back("./20news/Train/comp.windows.x/66398");
  paths.push_back("./20news/Train/comp.windows.x/66400");
  paths.push_back("./20news/Train/comp.windows.x/66404");
  paths.push_back("./20news/Train/comp.windows.x/66428");
  Model model(string("windows"), paths);

  for (auto each: model.word_counts.word_counts) 
    std::cout << each.first << " " << each.second << std::endl;

  std::cout << model.computeProb(string("to")) << std::endl;
  std::cout << model.computeProb(string("Step")) << std::endl;
  std::cout << model.computeProb(string("n")) << std::endl;
  std::cout << model.computeProb(string("nWDAWDSGSGFSEF")) << std::endl;
}

