最后一步：
以 Release 模式构建项目，生成可执行文件 SharedLibUser.exe。将动态库文件 MySharedLib.dll
复制到可执行文件 SharedLibUser.exe 所在的文件夹，才可以正常运行项目，否则提示找不到 DLL 文件。