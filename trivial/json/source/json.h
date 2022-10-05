#ifndef __JSON_H__
#define __JSON_H__

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace json {

enum class Type {
  Unknown,
  List,
  Object,
  Number,
  String,
  Bool,
  Null,
};

class Node {
 public:
  class Value {
   public:
    Value() { _type = Type::Unknown; }
    ~Value() {}

    Value& operator[](const std::string& index) {
      return _json_node->operator[](index);
    }

    Type getType() const { return _type; }
    void setType(Type type) { _type = type; }

    void setNumber(double number) {
      setType(Type::Number);
      _number = number;
    }

    void setString(const std::string& str) {
      setType(Type::String);
      _string = str;
    }
    void setBool(bool b) {
      setType(Type::Bool);
      _bool = b;
    }
    void setList(std::vector<Value>& l) {
      setType(Type::List);
      _list = l;
    }
    void setNull() { setType(Type::Null); }

    void setJson(Node& json) {
      auto p = std::make_shared<Node>(json);
      setJson(p);
    }

    void setJson(std::shared_ptr<Node> json) {
      setType(Type::Object);
      _json_node = json;
    }

    double& getNumber() {
      assert(getType() == Type::Number);
      return _number;
    }
    bool& getBool() {
      assert(getType() == Type::Bool);
      return _bool;
    }
    std::string& getString() {
      assert(getType() == Type::String);
      return _string;
    }
    std::vector<Value>& getList() {
      assert(getType() == Type::List);
      return _list;
    }
    std::shared_ptr<Node> getJson() {
      assert(getType() == Type::Object);
      return _json_node;
    }

    Value& operator=(double number) {
      setNumber(number);
      return *this;
    }

    Value& operator=(int number) { return this->operator=((double)number); }

    Value& operator=(const std::string& str) {
      setString(str);
      return *this;
    }

    std::string toString() const {
      switch (getType()) {
        case Type::Number:
          return std::to_string(_number);
        case Type::String:
          return "\"" + _string + "\"";
        case Type::Null:
          return "null";
        case Type::Bool:
          return _bool ? "true" : "false";
        case Type::Object:
          return _json_node->toString();
        case Type::List: {
          std::stringstream ss;
          ss << "[";
          bool isfirst = true;
          for (auto& item : _list) {
            if (isfirst) {
              ss << item.toString();
              isfirst = false;
            } else {
              ss << "," << item.toString();
            }
          }
          ss << "]";
          return ss.str();
        }

        default:
          break;
      }
      return "";
    }

   private:
    Type                  _type;
    double                _number;
    bool                  _bool;
    std::string           _string;
    std::vector<Value>    _list;
    std::shared_ptr<Node> _json_node;
  };

  Node() {}
  ~Node() {}

  void addNode(const std::string& key, const Value& value) {
    _map[key] = value;
  }

  void delNode(const std::string& key) { _map.erase(key); }

  Value& operator[](const std::string& key) {
    auto iter = _map.find(key);
    if (iter != _map.end()) {
      return iter->second;
    }
    // 添加一个 key: value 对
    Value value;
    value.setNull();
    addNode(key, value);
    iter = _map.find(key);
    return iter->second;
  }

  std::string toString() const {
    std::stringstream ss;
    ss << "{";
    bool is_first = true;
    for (auto& item : _map) {
      if (is_first) {
        ss << "\"" << item.first << "\": " << item.second.toString();
        is_first = false;
      } else {
        ss << ",\"" << item.first << "\": " << item.second.toString();
      }
    }
    ss << "}";
    return ss.str();
  }

 private:
  std::map<std::string, Value> _map;
};

namespace detail {

class Parser {
 public:
  Parser(const std::string& source) : _source(source) {}

  Node parse() { return parseObject(); }

 private:
  void skipWhitespace() {
    while (_curr < _source.size() &&
           (_source[_curr] == ' ' || _source[_curr] == '\n' ||
            _source[_curr] == '\t' || _source[_curr] == '\r')) {
      ++_curr;
    }
  }

  std::string parseString() {
    std::stringstream s;
    assert(_source[_curr++] == '"');
    while (_curr < _source.size()) {
      if (_source[_curr] == '\\') {
        _curr++;
        char c = _source[_curr];
        if (c == 'n') {
          s << "\n";
          ++_curr;
        } else if (c == '"') {
          s << '"';
          ++_curr;
        } else if (c == 'r') {
          s << '\r';
          ++_curr;
        }
      } else if (_source[_curr] == '"') {
        _curr++;
        return s.str();
      } else {
        s << _source[_curr];
        _curr++;
      }
    }
    return s.str();
  }

  std::string parseKey() {
    skipWhitespace();
    std::string key = parseString();
    skipWhitespace();
    return key;
  }

  double parseNumber() {
    double result = 0;
    int    flag   = 1;
    // 符号
    if (_source[_curr] == '-') {
      flag = -1;
      ++_curr;
    } else if (_source[_curr] == '+') {
      ++_curr;
    }

    while (isdigit(_source[_curr])) {
      double n = _source[_curr] - '0';
      ++_curr;
      result = n + result * 10.;
    }
    if (_source[_curr] == '.') {
      _curr++;
      double aft = 0.;
      double b   = 1.;
      while (isdigit(_source[_curr])) {
        b /= 10.;
        double n = _source[_curr] - '0';
        _curr++;
        aft += n * b;
      }
      result += aft;
    }
    if (_source[_curr] == 'e' || _source[_curr] == 'E') {
      _curr++;
      int flge = 1;
      if (_source[_curr] == '-') {
        flge = -1;
        _curr++;
      } else if (_source[_curr] == '+') {
        _curr++;
      }
      int val = 0;
      while (isdigit(_source[_curr])) {
        double n = _source[_curr] - '0';
        ++_curr;
        val = n + val * 10.;
      }
      val *= flge;
      val      = abs(val);
      double t = 1;
      for (int i = 0; i < val; ++i) {
        t *= 10;
      }
      if (flge > 0) {
        result *= t;
      } else {
        result /= t;
      }
    }

    return result * flag;
  }

  Node parseObject() {
    // object 内为 key: value 形式的键值对
    // { key1: value1, key2: value2, ... }
    skipWhitespace();
    Node json;
    assert(_source[_curr++] == '{');
    while (true) {
      std::string key = parseKey();
      assert(_source[_curr++] == ':');
      Node::Value value = parseValue();
      json.addNode(key, value);
      if (_source[_curr] != ',') {
        break;
      }
      ++_curr;
    }
    skipWhitespace();
    assert(_source[_curr++] == '}');

    return json;
  }

  Node::Value parseList() {
    Node::Value value;
    assert(_source[_curr] == '[');
    ++_curr;
    std::vector<Node::Value> vec;
    while (_curr < _source.size()) {
      Node::Value val = parseValue();
      vec.push_back(val);
      if (_source[_curr] != ',') {
        if (_source[_curr] == ']') {
          _curr++;
          break;
        } else {
          std::cout << "warn near ]" << std::endl;
          exit(-1);
        }
      } else {
        ++_curr;
      }
    }
    value.setList(vec);

    return value;
  }

  Node::Value parseValue() {
    skipWhitespace();
    Node::Value value;
    switch (_source[_curr]) {
      case '"': {
        value.setString(parseString());
        break;
      }
      case 't':
      case 'f': {
        value.setBool(parseBool());
        break;
      }
      case 'n': {
        parseNull();
        value.setNull();
        break;
      }
      case '{': {
        value.setJson(std::make_shared<Node>(parseObject()));
        break;
      }
      case '[': {
        value = parseList();
        break;
      }
      case '-':
      case '.':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': {
        value.setNumber(parseNumber());
        break;
      }
    }
    skipWhitespace();
    return value;
  }

  bool parseBool() {
    if (_source[_curr] == 'f') {
      assert(_curr + 5 <= _source.size());
      assert(_source[_curr++] == 'f');
      assert(_source[_curr++] == 'a');
      assert(_source[_curr++] == 'l');
      assert(_source[_curr++] == 's');
      assert(_source[_curr++] == 'e');
      return false;
    } else {
      assert(_curr + 4 <= _source.size());
      assert(_source[_curr++] == 't');
      assert(_source[_curr++] == 'r');
      assert(_source[_curr++] == 'u');
      assert(_source[_curr++] == 'e');
      return true;
    }
  }

  void parseNull() {
    assert(_curr + 4 <= _source.size());
    assert(_source[_curr++] == 'n');
    assert(_source[_curr++] == 'u');
    assert(_source[_curr++] == 'l');
    assert(_source[_curr++] == 'l');
  }

 private:
  std::string _source;
  int         _curr = 0;
};

}  // namespace detail

inline Node parse(const std::string& str) {
  detail::Parser parser(str);
  return parser.parse();
}

}  // namespace json

#endif  // __JSON_H__