# Json Parser

一个简单的 json 解析器。支持 json 解析，生成，序列化，反序列化等功能

## 设计思路

一个 json 文件可以看作一棵由键值对组成的树

```json
{
  "name": "Joe",
  "age": 17,
  "address": "New York",
  "hobbies": ["basketball", "baseball", "music"],
  "circumlation": [
    {
      "subject": "Math",
      "grade": 80
    },
    {
      "subject": "English",
      "grade": 87
    }
  ]
}
```