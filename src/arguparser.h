#include <cstring>
#include <cstdlib>
#include <string>
using std::string;

class Arguparser {

public:
  Arguparser(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
      if (0 == strcmp(argv[i], "-i"))
        data_dir = string(argv[i + 1]);
      else if (0 == strcmp(argv[i], "-o"))
        output_file = string(argv[i + 1]);
      else if (0 == strcmp(argv[i], "-n"))
        label_size = atoi(argv[i + 1]);
    }
  }

  string getDataDir() {
    return data_dir;
  }

  string getOutputFile() {
    return output_file;
  }

  int getLabelSize() {
    return label_size;
  }

  bool isLabelSizeSet() {
    return label_size >= 0;
  }

private:
  string data_dir;
  string output_file;
  int label_size = -1;
};
