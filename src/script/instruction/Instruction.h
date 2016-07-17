#pragma once
#include "LanguageNode.h"
#include "BString.h"

/*
边解析边建节点树,同时,遇到变量则分配变量空间,并加到局部(全局)变量map中去,已经分配的变量可以被后面的表达式引用;
只有在函数调用传参和返回值的时候才需要用到栈;
*/

namespace bluemei{

class InstructionVisitor;

class Instruction : public LanguageNode
{
public:
	Instruction(){}
	virtual ~Instruction(){}
public:
	virtual String toString() const{
		return getText();
	}
public:
	virtual bool accept(InstructionVisitor* visitor)=0;

	virtual String getText() const =0;
};

}//end of namespace bluemei

