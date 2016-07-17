#pragma once
#include "InstructionVisitor.h"
#include "Expression.h"
#include "Method.h"

namespace bluemei{

//²Ù×÷·ûÉùÃ÷
class SimpleStatment			  ;
class SequenceStatment			  ;

class IfElseStatment			  ;
class SwitchCaseStatment		  ;
class WhileStatment				  ;
class DoWhileStatment			  ;
class ForStatment				  ;

class ReturnStatment			  ;
class BreakStatment				  ;
class ContinueStatment			  ;


class StatmentVisitor : public InstructionVisitor
{
public:
	StatmentVisitor(){}
	virtual ~StatmentVisitor(){}
public:
	virtual bool visit(Method* node)
	{
		bool success=false; 
		if(node!=nullptr && node->getStatment())
		{
			success=node->getStatment()->accept(this);
		}
		return success;
	}
	virtual bool visit(Statment* node)
	{
		bool success=false;
		if (node!=nullptr)
		{
			success=node->acceptStmt(this);			
		}
		return success;
	}	
public:
	virtual bool visitStmt(SimpleStatment			* node)=0;
	virtual bool visitStmt(SequenceStatment			* node)=0;

	virtual bool visitStmt(IfElseStatment	   		* node)=0;
	virtual bool visitStmt(SwitchCaseStatment  		* node)=0;
	virtual bool visitStmt(WhileStatment	   		* node)=0;
	virtual bool visitStmt(DoWhileStatment	   		* node)=0;
	virtual bool visitStmt(ForStatment	   			* node)=0;
	
	virtual bool visitStmt(ReturnStatment	   		* node)=0;
	virtual bool visitStmt(BreakStatment	   		* node)=0;
	virtual bool visitStmt(ContinueStatment	   		* node)=0;
};

}//end of namespace bluemei