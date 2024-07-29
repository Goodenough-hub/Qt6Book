#ifndef MYSHAREDLIB_GLOBAL_H
#define MYSHAREDLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYSHAREDLIB_LIBRARY)
#define MYSHAREDLIB_EXPORT Q_DECL_EXPORT // 声明为导出，共享库中有效
#else
#define MYSHAREDLIB_EXPORT Q_DECL_IMPORT // 声明为导入，使用库的项目中有效
#endif

#endif // MYSHAREDLIB_GLOBAL_H
