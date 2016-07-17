#pragma once
#include "Statment.h"
#include "StatmentVisitor.h"

namespace bluemei{

class SimpleStatment : public Statment
{
public:
	SimpleStatment(Expression* expr=nullptr){
		this->expr=expr;
	}
	virtual ~SimpleStatment(){
		delete expr;
	}
public:
	virtual bool acceptStmt(StatmentVisitor* visitor)
	{
		checkNullPtr(visitor);
		return visitor->visitStmt(this);
	}
	virtual String getText() const
	{
		if (expr!=nullptr)
		{
			String str=expr->getText();
			StringBuilder sb(str.length()*1.20);

			//String::format("%s;",str.c_str());
			sb.append(str);
			sb.append(STR_SEMI);
			sb.append(STR_BR);

			return sb.toString();
		}
		return STR_NULL;
	}
public:
	virtual LanguageNode* getLeftNode() const { return getExpression(); }
	virtual void setLeftNode(LanguageNode* val) { setExpression(dcast<Expression>(val)); }

	virtual bool hasLeft() const { return expr!=nullptr; }
public:
	Expression* getExpression() const { return expr; }
	void setExpression(Expression* val) { expr = val; }
protected:
	Expression* expr;
};

}//end of namespace bluemei

