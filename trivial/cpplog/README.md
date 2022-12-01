# Cpp Log

一个使用无锁队列的前后端分离日志库

## Example

示例文件：

```cpp
#include "log.h"

int main() {
  LOG_INFO() << "This is Info.";
  LOG_WARN() << "This is Warn.";
}
```

控制台输出：

```bash
[22:53:46] [7313] [info]  This is Info.
[22:53:46] [7313] [warn]  This is Warn.
```

## Todo

- [ ] 更自由的输出格式配置
- [ ] 更多的日志输出方式
- [ ] ...
