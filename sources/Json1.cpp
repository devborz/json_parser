
#include "Json.h"

Json::Json(const string& s) {
    int i = 0;
    miss_spaces(i, s);
    if (s[i] == '{') {
        _is_object = true;
       create_map(s);
    }
    else if (s[i] == '[') {
        _is_array = true;
        create_vector(s);
    }
}
bool Json::is_array() const{
    return _is_array;
}
bool Json::is_object() const{
    return _is_object;
}

std::any& Json::operator[](const string& key) {
    if (Json::is_object()) {
        return _map[key];
    } else {
        throw std::logic_error("is not an object");
    }
}
std::any& Json::operator[](int index) {
    if (is_array()) {
        return this->_arr[index];
    } else {
        throw std::logic_error("is not an array");
    }
}
string Json::conv(string text) {
    string result="";
    for(const auto& c : text)
	    if (c != '\n')
		    result += c;
    return result;
} 
Json Json::parse(const std::string& s) {
    Json obj(s);
    return obj;
}
Json Json::parseFile(const std::string& path_to_file){
	    Json obj(path_to_file);
	        return obj;

}
void Json::create_vector(string s) {
    int i = 1;
    while (i < (int) s.length() - 1) {
        miss_spaces(i, s);
        if (s[i] == '{') {
            std::string s1;
            s1 = s.substr(i, find_end(i, s) - i + 1);
            Json obj(s1);
            this->_arr.emplace_back(obj._map);
            i += s1.length();
        }
        else if (s[i] == '\"') {
            std::string word;
            word = read_key(i, s);
            miss_spaces(i, s);
            this->_arr.emplace_back(word);
        }
        else if ((s[i] == 't' && s[i+1] == 'r' && s[i+2] == 'u' && s[i+3] == 'e') ||
                 (s[i] == 'f' && s[i+1] == 'a' &&s[i+2] == 'l' && s[i+3] == 's' && s[i+4] == 'e')) {
            bool x;
            if(s[i] == 't') {
                i += 4;
                x = true;
            }
            else {
                i += 5;
                x = false;
            }
            this->_arr.emplace_back(x);
        }
        else if(s[i] == '[') {
            std::string s1;
            s1 = s.substr(i, find_end(i, s) - i + 1);
            Json obj(s1);
            this->_arr.emplace_back(obj._arr);
            i += s1.length();
        }
        else if(s[i] >= 48 && s[i] < 58) {
            std::string num = cut_num(i, s);
            i += num.length();
            double d = stod(num);
            if (d - (int) d == 0) {
                int n = (int)d;
                this->_arr.emplace_back(n);
            } else {
                this->_arr.emplace_back(d);
            }
        }
        miss_spaces(i, s);
    }
}

void Json::miss_spaces(int &i, string s) {
    while(s[i] == ' ' || s[i] == ',') {
        i++;
    }
}
int Json::find_end(int i, string s) {
    int cnt_open = 1 , cnt_close = 0;
    char key1, key2;
    key2 = '}';
    key1 = '{';
    if (s[i] == '[') {
        key1 = '[';
        key2 = ']';
    }

    while(cnt_close != cnt_open) {
        i++;
        if (s[i] == key1) cnt_open++;
        else if (s[i] == key2) cnt_close++;
    }
    return i;
}
void Json::create_map(string s) {
    int i = 1;
    while (i < (int) s.length() - 1) {
        string key;
        miss_spaces(i, s);
        key = read_key(i, s);
        miss_spaces(i, s);
        if (s[i] != ':') throw std::logic_error("3");
        i++;
        miss_spaces(i, s);
        if (s[i] == '{') {
            string s1;
            s1 = s.substr(i, find_end(i, s) - i + 1);
            Json obj(s1);
            this->_map[key] = obj._map;
            i += s1.length();
        }
        else if (s[i] == '\"') {
            string word;
            word = read_key(i, s);
            miss_spaces(i, s);
            this->_map[key] = word;
        }
        else if ((s[i] == 't' && s[i+1] == 'r' && s[i+2] == 'u' && s[i+3] == 'e') ||
        (s[i] == 'f' && s[i+1] == 'a' &&s[i+2] == 'l' && s[i+3] == 's' && s[i+4] == 'e')) {
            bool x;
            if(s[i] == 't') {
                i += 4;
                x = true;
            }
            else {
                i += 5;
                x = false;
            }
            this->_map[key] = x;
        }
        else if(s[i] == '[') {
            string s1;
            s1 = s.substr(i, find_end(i, s) - i + 1);
            Json obj(s1);
            this->_map[key] = obj._arr;
            i += s1.length();
        }
        else if(s[i] >= 48 && s[i] < 58) {
            string num = cut_num(i, s);
            i += num.length();
            double d = stod(num);
            if (d - (int) d == 0) {
                int n = (int)d;
                this->_map[key] = n;
            } else
                this->_map[key] = d;
        }
        miss_spaces(i, s);
    }
}
string Json::cut_num(int i, string s) {
    int st = i;
    string num;
    while (s[i] >= 48 && s[i] < 58) i++;
    num = s.substr(st, i - st);
    return num;
}
string Json::read_key(int &i, string s) {
    int st;
    string key;
    miss_spaces(i, s);
    if (s[i] == '\"') {
        i++;
        st = i;
    }
    else throw std::logic_error("string isn't valid!");
    while (s[i] != '"') i++;
    key = s.substr(st, i - st);
    i++;
    return key;
}
   void Json::print_map() {
    for(const auto& p  : this->_map) {
        cout << p.first << " : ";
        print(p.second);
        cout << std::endl;
    }
}
void Json::print(any _data) {
    string type = _data.type().name();
    try {
        if (type == "i") {
            cout << any_cast<int> (_data);
        }
        else if (type == "d") {
            cout << any_cast<double> (_data);
        }
        else if (type == "b") {
            if (any_cast<bool> (_data)) std::cout << "true";
            else cout << "false";
        }
        else if (type == "Ss" ) {
            cout << any_cast<string> (_data);
        }
        else if (type.find("St6vector") < type.length()) {
            std::vector <std::any> vec;
            vec = any_cast<vector<any>>(_data);
            int iter = 0;
            cout << "[ ";
            for(const auto& c: vec) {
                iter++;
                if (iter > 1) std::cout << " , ";
                print(c);
            }
            cout << " ]";
        }
        else if (type.find("St3map") < type.length()) {
            map <string, any> _map;
            _map = std::any_cast<map <string, any>>(_data);
            cout << "{\n" ;
            int iter = 0;
            for(const auto& c: _map) {
                iter++;
                if (iter > 1) cout << " ,\n";
                cout << "\t" << c.first << " : ";
                print(c.second);
            }
            cout << "\n\t}";
        }
    }
    catch(const std::bad_any_cast& e) {
        cout << e.what() << '\n';
    }
}
void Json::print_vector() {
    int iter = 0;
    cout << "[ ";
    for(const auto& c: this->_arr) {
        iter++;
        if (iter > 1) cout << " , ";
        print(c);
    }
    cout << " ]";
}
