#pragma once

#ifdef PYTHON_3
PyMODINIT_FUNC PyInit_dbg(void);
#else
void initdbg();
#endif
