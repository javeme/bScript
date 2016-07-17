#pragma once
#include "Statment.h"
#include "ArrayList.h"
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

	int getAccessProp() const { return accessProp; }
	void setAccessProp(int val) { accessProp = val; }

	BSVar* getReturnType() const { return m_returnType; }
	void setReturnType(BSVar* val) { m_returnType = val; }

	ArrayList<BSVar*> getIncomingVarList() const { return m_incomingVarList; }
	void setIncomingVarList(ArrayList<BSVar*> val) { m_incomingVarList = val; }
protected:
	Statment* stmt;

	//方法名称
	String methodName;
	//访问属性
	int accessProp;
	//返回值类型
	BSVar* m_returnType;
	//传入参数
	ArrayList<BSVar*> m_incomingVarList;
	//局部变量(放入Statment好?)
	HashMap<String,BSVar*> m_varMap;
};


}//end of namespace bluemei

