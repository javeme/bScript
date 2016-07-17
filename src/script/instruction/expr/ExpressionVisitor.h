#pragma once
#include "InstructionVisitor.h"
#include "StatmentVisitor.h"


namespace bluemei{

//操作符声明
class OperatorAdd			  ;
class OperatorSub			  ;
class OperatorMul			  ;
class OperatorDiv			  ;

class OperatorLessThan		  ;
class OperatorGreaterThan	  ;
class OperatorLessThanEq	  ;
class OperatorGreaterThanEq	  ;
class OperatorEqual			  ;
class OperatorNotEqual		  ;

class OperatorLeftShift		  ;
class OperatorRightShift	  ;
class OperatorAnd			  ;
class OperatorOr			  ;
class OperatorMod			  ;
class OperatorBitAnd		  ;
class OperatorBitOr			  ;
class OperatorBitXor		  ;

class OperatorAssign		  ;
class OperatorAssignAdd		  ;
class OperatorAssignSub		  ;
class OperatorAssignMul		  ;
class OperatorAssignDiv		  ;

class OperatorAssignMod		  ;
class OperatorAssignRShift	  ;
class OperatorAssignLShift	  ;
class OperatorAssignBAnd	  ;
class OperatorAssignBXor	  ;
class OperatorAssignBOr		  ;

class OperatorNegative		  ;
class OperatorNot			  ;
class OperatorBitNot		  ;

//操作数声明
class OperandNumber			;
class OperandRefrence		;

class ExpressionVisitor : public StatmentVisitor
{
public:
	ExpressionVisitor(){}
	virtual ~ExpressionVisitor(){}
public:
	/*
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
		if (node!=nullptr && node->getSequence())
		{
			success=node->getSequence()->accept(this);			
		}
		return success;
	}
	virtual bool visit(Sequence* node)
	{
		bool success=false;
		if (node!=nullptr && node->getExpression())
		{
			success=node->getExpression()->accept(this);	
			if (node->getNextSequence()!=nullptr)
			{
				success=node->getNextSequence()->accept(this);
			}
		}
		return success;
	}*/
	virtual bool visit(Expression* node)
	{
		bool success=false;
		if (node!=nullptr)
		{
			Expression* rs=node->acceptExpr(this);
			success=(rs!=nullptr);
			delete rs;
		}
		return success;
	}
public:
	virtual Expression* visitExpr(OperatorAdd			* node)=0;
	virtual Expression* visitExpr(OperatorSub			* node)=0;
	virtual Expression* visitExpr(OperatorMul			* node)=0;
	virtual Expression* visitExpr(OperatorDiv			* node)=0;
	
	virtual Expression* visitExpr(OperatorLessThan		* node)=0;
	virtual Expression* visitExpr(OperatorGreaterThan	* node)=0;
	virtual Expression* visitExpr(OperatorLessThanEq	* node)=0;
	virtual Expression* visitExpr(OperatorGreaterThanEq	* node)=0;
	virtual Expression* visitExpr(OperatorEqual			* node)=0;
	virtual Expression* visitExpr(OperatorNotEqual		* node)=0;
	
	virtual Expression* visitExpr(OperatorLeftShift		* node)=0;
	virtual Expression* visitExpr(OperatorRightShift	* node)=0;
	virtual Expression* visitExpr(OperatorAnd			* node)=0;
	virtual Expression* visitExpr(OperatorOr			* node)=0;
	virtual Expression* visitExpr(OperatorMod			* node)=0;
	virtual Expression* visitExpr(OperatorBitAnd		* node)=0;
	virtual Expression* visitExpr(OperatorBitOr			* node)=0;
	virtual Expression* visitExpr(OperatorBitXor		* node)=0;
	
	virtual Expression* visitExpr(OperatorAssign		* node)=0;
	virtual Expression* visitExpr(OperatorAssignAdd		* node)=0;
	virtual Expression* visitExpr(OperatorAssignSub		* node)=0;
	virtual Expression* visitExpr(OperatorAssignMul		* node)=0;
	virtual Expression* visitExpr(OperatorAssignDiv		* node)=0;
	
	virtual Expression* visitExpr(OperatorAssignMod		* node)=0;
	virtual Expression* visitExpr(OperatorAssignRShift	* node)=0;
	virtual Expression* visitExpr(OperatorAssignLShift	* node)=0;
	virtual Expression* visitExpr(OperatorAssignBAnd	* node)=0;
	virtual Expression* visitExpr(OperatorAssignBXor	* node)=0;
	virtual Expression* visitExpr(OperatorAssignBOr		* node)=0;
	
	virtual Expression* visitExpr(OperatorNegative		* node)=0;
	virtual Expression* visitExpr(OperatorNot			* node)=0;
	virtual Expression* visitExpr(OperatorBitNot		* node)=0;	

	virtual Expression* visitExpr(OperandNumber			* node)=0;
	virtual Expression* visitExpr(OperandRefrence		* node)=0;		
};

}//end of namespace bluemei

