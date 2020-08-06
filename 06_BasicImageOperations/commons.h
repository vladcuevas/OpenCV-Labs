#include <string>   // std::string, std::to_string

using namespace std;

class commons {
public:
  std::string GetCurrentWorkingDir(void);
  std::string GetImageDataPath(string path);
};