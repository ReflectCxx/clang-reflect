
#include <iostream>
#include <algorithm>

#include "ParamVarDeclsVisitor.h"


namespace clang_reflect
{
	using namespace clang;

	bool ParmVarDeclsVisitor::VisitTypedefType(clang::TypedefType* pTypeDefType)
	{
		return true;
	}
}