- [ ] Xcode调试：Xcode内置了基于LLDB的完整图形化调试洁面
- [ ] 使用VS Code
```c++
通过 ​VS Code + LLDB 插件实现可视化调试，适合非 Xcode 项目（如 CMake、Makefile）。
​配置步骤​：

​安装扩展​：
C/C++
CodeLLDB
​配置 launch.json​：
在 VS Code 中按 ⌘ + ⇧ + P，输入 Debug: Add Configuration，选择 ​LLDB，示例配置：
json
复制
{
  "type": "lldb",
  "request": "launch",
  "name": "Debug with LLDB",
  "program": "${workspaceFolder}/build/your_executable",
  "args": [],
  "cwd": "${workspaceFolder}"
}
​开始调试​：
按 F5 启动调试，使用 VS Code 的调试界面（变量查看、调用栈、断点管理等）。
```
- [ ] try GDB and DDD if possible.