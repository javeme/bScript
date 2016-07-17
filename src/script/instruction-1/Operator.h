#pragma once
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Operand.h"

namespace bluemei{

//������
class Operator : public Expression
{
public:
	Operator(){}
	virtual ~Operator(){}
public:
	virtual String getOperatorText() const=0;
/*public:
	virtual Operand* getResult() const { return result; }
	virtual void setResult(Operand* val) { result = val; }

	virtual Operand* detachResult() {
		Operand* tmp=result; 
		result=nullptr;
		return tmp; 
	}
protected:
	Operand* result; */
};

//һԪ������
class OperatorUnary : public Operator
{
public:
	OperatorUnary(){
		operand=nullptr;
	}
	virtual ~OperatorUnary(){
		delete operand;
	}
public:
	virtual String getText() const
	{
		if (operand!=nullptr)
		{
			return getOperatorText()+operand->getText();
		}
		return STR_NULL;
	}
public:
	virtual LanguageNode* getRightNode() const { return getOperand(); }
	virtual void setRightNode(LanguageNode* val) { setOperand(dcast<Expression>(val)); }
	
	virtual bool hasRight() const { return operand!=nullptr; }
public:
	Expression* getOperand() const { return operand; }
	void setOperand(Expression* val) { operand = val; }
protected:
	Expression* operand;
};

//��Ԫ������
class OperatorBinary : public Operator
{
public:
	OperatorBinary(){
		leftOperand=nullptr;
		rightOperand=nullptr;
	}
	virtual ~OperatorBinary(){
		delete leftOperand;
		delete rightOperand;
	}
public:
	virtual String getText() const
	{
		String s1=leftOperand!=nullptr?leftOperand->getText():STR_NULL;
		String s2=rightOperand!=nullptr?rightOperand->getText():STR_NULL;
		return (s1+getOperatorText()+s2);
	}
public:
	virtual LanguageNode* getLeftNode() const { return getLeftOperand(); }
	virtual void setLeftNode(LanguageNode* val) { setLeftOperand(dcast<Expression>(val)); }

	virtual LanguageNode* getRightNode() const { return getRightOperand(); }
	virtual void setRightNode(LanguageNode* val) { setRightOperand(dcast<Expression>(val)); }

	virtual bool hasLeft() const { return leftOperand!=nullptr; }
	virtual bool hasRight() const { return rightOperand!=nullptr; }
public:
	Expression* getLeftOperand() const { return leftOperand; }
	void setLeftOperand(Expression* val) { leftOperand = val; }

	Expression* getRightOperand() const { return rightOperand; }
	void setRightOperand(Expression* val) { rightOperand = val; }

	//void setLeftOperand(Number* val) { leftOperand = new OperandNumber(val); }
	//void setRightOperand(Number* val) { rightOperand = new OperandNumber(val); }
protected:
	Expression* leftOperand;
	Expression* rightOperand;
};

/*************************************************************************************************************/

#define ADD_OperatorUnary(className,opText,opPrecedence)				 \
	class className : public OperatorUnary								 \
	{																	 \
	public:																 \
		virtual Expression* acceptExpr(ExpressionVisitor* visitor)		 \
		{																 \
			return visitor->visitExpr(this);							 \
		}																 \
		virtual String getOperatorText() const							 \
		{																 \
			return CODE2STRING(opText);									 \
		}																 \
		virtual int precedence() const { 								 \
			return opPrecedence; 										 \
		}																 \
	};

#define ADD_OperatorBinary(className,opText,opPrecedence)				 \
	class className : public OperatorBinary								 \
	{																	 \
	public:																 \
		virtual Expression* acceptExpr(ExpressionVisitor* visitor)		 \
		{																 \
			return visitor->visitExpr(this);							 \
		}																 \
		virtual String getOperatorText() const							 \
		{																 \
			return CODE2STRING(opText);									 \
		}																 \
		virtual int precedence() const { 								 \
			return opPrecedence; 										 \
		}																 \
	};
/*
class OperatorAdd : public OperatorBinary
{
public:
	virtual bool acceptExpr(ExpressionVisitor* visitor)
	{
		return visitor->visitExpr(this);
	}
	virtual String getOperatorText() const
	{										
		return "+";	
	}										
};
*/
enum OpPrecedence{
	PD_OP_BEGIN			= PD_OPERTOR	,
	PD_OP_COMMA			= PD_OPERTOR+100,//�������ȼ�
	PD_OP_ASSIGN		= PD_OPERTOR+200,//��ֵ�Ⱥ����ȼ�(����+=֮���)

	PD_OP_OR							,//��
	PD_OP_AND							,//��
	PD_OP_BOR							,//λ��
	PD_OP_XOR							,//λ���
	PD_OP_BAND							,//λ��
	
	PD_OP_EQ							,//�ж��Ƿ�(��)����(==,!=)
	PD_OP_COMP							,//�Ƚϴ�С(<,<=,>,>=)

	PD_OP_SHIFT							,//��λ

	PD_OP_ADD							,//�Ӽ�
	PD_OP_MUL							,//�˳�ģ

	PD_OP_NEG							,//����
	PD_OP_BNOT							,//λ��
	PD_OP_NOT							,//��

	PD_OP_PARN							,//����
};

ADD_OperatorBinary(OperatorAdd			, +  , PD_OP_ADD	);
ADD_OperatorBinary(OperatorSub			, -  , PD_OP_ADD	);
ADD_OperatorBinary(OperatorMul			, *  , PD_OP_MUL	);
ADD_OperatorBinary(OperatorDiv			, /  , PD_OP_MUL	);
											  	
ADD_OperatorBinary(OperatorLessThan		, <  , PD_OP_COMP	);
ADD_OperatorBinary(OperatorGreaterThan	, >  , PD_OP_COMP	);
ADD_OperatorBinary(OperatorLessThanEq	, <= , PD_OP_COMP	);
ADD_OperatorBinary(OperatorGreaterThanEq, >= , PD_OP_COMP	);
ADD_OperatorBinary(OperatorEqual		, == , PD_OP_EQ		);
ADD_OperatorBinary(OperatorNotEqual		, != , PD_OP_EQ		);
											  	
ADD_OperatorBinary(OperatorLeftShift	, << , PD_OP_SHIFT	);
ADD_OperatorBinary(OperatorRightShift	, >> , PD_OP_SHIFT	);
ADD_OperatorBinary(OperatorAnd			, && , PD_OP_AND	);
ADD_OperatorBinary(OperatorOr			, || , PD_OP_OR		);
ADD_OperatorBinary(OperatorMod			, %  , PD_OP_MUL	);
ADD_OperatorBinary(OperatorBitAnd		, &  , PD_OP_BAND	);
ADD_OperatorBinary(OperatorBitOr		, |  , PD_OP_BOR	);
ADD_OperatorBinary(OperatorBitXor		, ^  , PD_OP_XOR	);
											  	
ADD_OperatorBinary(OperatorAssign		, =	 , PD_OP_ASSIGN	);
ADD_OperatorBinary(OperatorAssignAdd	, += , PD_OP_ASSIGN	);
ADD_OperatorBinary(OperatorAssignSub	, -= , PD_OP_ASSIGN	);
ADD_OperatorBinary(OperatorAssignMul	, *= , PD_OP_ASSIGN	);
ADD_OperatorBinary(OperatorAssignDiv	, /= , PD_OP_ASSIGN	);
											 		 
ADD_OperatorBinary(OperatorAssignMod	, %= , PD_OP_ASSIGN	);
ADD_OperatorBinary(OperatorAssignRShift	, >>=, PD_OP_ASSIGN	);
ADD_OperatorBinary(OperatorAssignLShift	, <<=, PD_OP_ASSIGN	);
ADD_OperatorBinary(OperatorAssignBAnd	, &= , PD_OP_ASSIGN	);
ADD_OperatorBinary(OperatorAssignBXor	, ^= , PD_OP_ASSIGN	);
ADD_OperatorBinary(OperatorAssignBOr	, |= , PD_OP_ASSIGN	);
											  	
											  	
ADD_OperatorUnary (OperatorNegative		, -  , PD_OP_NEG	);				  
ADD_OperatorUnary (OperatorNot			, !  , PD_OP_NOT	);
ADD_OperatorUnary (OperatorBitNot		, ~  , PD_OP_BNOT	);

}//end of namespace bluemei

