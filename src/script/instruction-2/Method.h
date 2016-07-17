#pragma once
#include "ComplexInstruction.h"
#include "HashMap.h"

namespace bluemei{

class Operand;
class EvaluateContext;

typedef Operand BSVar;

class Method : public Instruction
{
public:
	Method(cstring name);
	virtual ~Method();
public:
	virtual bool accept(InstructionVisitor* visitor);
	virtual String getText() const;
public:
	virtual LanguageNode* getRightNode() const { return getStatment(); }
	virtual void setRightNode(LanguageNode* val) { setStatment(dcast<Statment>(val)); }

	virtual bool hasRight() const { return stmt!=nullptr; }

	virtual int precedence() const { return PD_METHOD; }
public:
	virtual BSVar* evaluate(EvaluateContext* ctx);
public:
	Statment* getStatment() const { return stmt; }
	void setStatment(Statment* val) { stmt = val; }
protected:
	Statment* stmt;

	//方法名称
	String methodName;
	//访问属性
	int accessProp;
	//返回值类型
	BSVar* m_returnType;
	//传入参数
	HashMap<String,BSVar*> m_incomingVarMap;
	//局部变量
	HashMap<String,BSVar*> m_varMap;
};


}//end of namespace bluemei

