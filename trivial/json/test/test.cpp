#include "test.h"

#include "json.h"

std::string listStr = R"(
{
  "list" : [ 1, "item1", null, true, {"str" : "string"}, ["temp"] ]
}
)";

std::string numberStr = R"(
{
  "num1": 0,
  "num2": 1,
  "num3": 1.3e3,
  "num4": -0.1e5,
  "num5": -3.57e-2
}
)";

std::string valueStr = R"(
{
  "string": "string",
  "number": 1,
  "null": null,
  "bool": true,
  "list": ["list1", "list2"],
  "object": {
    "object.string": "object.string"
  }
}
)";

TEST(Node, Basic) {
  json::Node        json;
  json::Node::Value value;
  value.setNumber(111);
  json.addNode("num", value);
  value.setString("Hello World");
  json.addNode("str", value);
  json::Node json2;
  value.setBool(false);
  json2.addNode("bool", value);
  value.setJson(json2);
  json.addNode("subjson", value);
  EXPECT_EQ(json["num"].getNumber(), 111);
  EXPECT_STREQ(json["str"].getString().c_str(), "Hello World");
  EXPECT_EQ(json["subjson"]["bool"].getBool(), false);
}

TEST(Json, Morden) {
  json::Node json;
  json["number"] = 2;
  json["string"] = "string";
  json["temp"]   = 4;
  EXPECT_EQ(json["number"].getNumber(), 2);
  EXPECT_STREQ(json["string"].getString().c_str(), "string");
  EXPECT_EQ(json["temp"].getNumber(), 4);
  json["temp"] = "temp";
  EXPECT_STREQ(json["temp"].getString().c_str(), "temp");
  json["bool"].setBool(false);
  EXPECT_EQ(json["bool"].getBool(), false);
}

TEST(Parse, Number) {
  json::Node json = json::parse(numberStr);
  EXPECT_EQ(json["num1"].getNumber(), 0);
  EXPECT_EQ(json["num2"].getNumber(), 1);
  EXPECT_EQ(json["num3"].getNumber(), 1.3e3);
  EXPECT_EQ(json["num4"].getNumber(), -0.1e5);
  EXPECT_EQ(json["num5"].getNumber(), -3.57e-2);
}

TEST(Parse, ValueType) {
  json::Node json = json::parse(valueStr);
  EXPECT_EQ(json["string"].getType(), json::Type::String);
  EXPECT_EQ(json["number"].getType(), json::Type::Number);
  EXPECT_EQ(json["null"].getType(), json::Type::Null);
  EXPECT_EQ(json["bool"].getType(), json::Type::Bool);
  EXPECT_EQ(json["list"].getType(), json::Type::List);
  for (auto& item : json["list"].getList()) {
    EXPECT_EQ(item.getType(), json::Type::String);
  }
  EXPECT_EQ(json["object"].getType(), json::Type::Object);
  EXPECT_EQ(json["object"]["object.string"].getType(), json::Type::String);
}

TEST(Parse, List) {
  json::Node json = json::parse(listStr);
  auto       vec  = json["list"].getList();
  EXPECT_EQ(vec[0].getNumber(), 1);
  EXPECT_STREQ(vec[1].getString().c_str(), "item1");
  EXPECT_EQ(vec[2].getType(), json::Type::Null);
  EXPECT_EQ(vec[3].getBool(), true);
  EXPECT_STREQ(vec[4]["str"].getString().c_str(), "string");
  EXPECT_STREQ(vec[5].getList()[0].getString().c_str(), "temp");
}