#pragma once
#include "Statment.h"
#include "LinkedList.h"
#include "StatmentVisitor.h"

namespace bluemei{

class SequenceStatment : public Statment
{
public:
	SequenceStatment(){
		;
	}
	virtual ~SequenceStatment(){
		clear();
	}
public:
	virtual bool acceptStmt(StatmentVisitor* visitor)
	{
		checkNullPtr(visitor);
		return visitor->visitStmt(this);
	}
	virtual String getText() const
	{
		LinkedList<Statment*> list=getStmtList();

		StringBuilder sb(list.size()*32);

		sb.append(STR_LBRACE);
		sb.append(STR_BR);

		auto i=list.iterator();
		while (i->hasNext())
		{
			Statment* stmt=i->next();

			String str=stmt->getText();
			sb.append(str);
		}
		list.releaseIterator(i);
		
		sb.append(STR_RBRACE);
		sb.append(STR_BR);

		return sb.toString();
	}
public:
	LinkedList<Statment*> getStmtList() const { return stmtList; }
	void setStmtList(const LinkedList<Statment*>& val) { 
		clear();
		stmtList = val; 
	}

	void addStmt(Statment* val) { stmtList.addToLast(val); }
	void clear() { 
		auto i=stmtList.iterator();
		while (i->hasNext())
		{
			delete i->next();
		}
		stmtList.releaseIterator(i);
		stmtList.clear();
	}
protected:
	LinkedList<Statment*> stmtList;
};

}//end of namespace bluemei

