#pragma once
#include "LanguageNode.h"
#include "BString.h"

/*
�߽����߽��ڵ���,ͬʱ,�����������������ռ�,���ӵ��ֲ�(ȫ��)����map��ȥ,�Ѿ�����ı������Ա�����ı��ʽ����;
ֻ���ں������ô��κͷ���ֵ��ʱ�����Ҫ�õ�ջ;
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

