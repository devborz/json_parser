#include <iomanip>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

int main() {
  ifstream in("file.json");
  json obj = json::parse(in);
  in.close();
  if (obj.size() == 3) {
    auto arr1 = obj[0];
    auto arr2 = obj[1];
    auto arr3 = obj[2];

    std::ofstream o("file2.json");
    nlohmann::json arr =  nlohmann::json::array();
    for (size_t i = 0; i < 3; ++i) {
      nlohmann::json obj_ = nlohmann::json::object({
        {"ticker", arr1[i]},
        {"id", arr2[i]},
        {"description", arr3[i]}
      });
      arr.push_back(obj_);
    }
    o << std::setw(4) << arr;
    o.close();
    ifstream in1("file2.json");
    json new_obj;
    in1 >> new_obj;
    in1.close();
    cout << new_obj.dump(5);
    return 0;
  }
}
