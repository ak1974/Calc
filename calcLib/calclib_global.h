#ifndef CALCLIB_GLOBAL_H
#define CALCLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CALCLIB_LIBRARY)
#  define CALCLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CALCLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CALCLIB_GLOBAL_H
