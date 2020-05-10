#ifndef PY_COMMON_H
#define PY_COMMON_H


#define PYTHON_IMPORT_SYS			"import sys\n"
#define PYTHON_IMPORT_DIR_PREF		"sys.path.append('"
#define PYTHON_IMPORT_DIR_SUF		"')\n"


using CustomType = std::list<std::string>;


#endif