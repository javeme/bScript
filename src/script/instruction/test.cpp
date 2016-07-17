#include "stdafx.h"
#include "ErrorHandler.h"

#include "SimpleStatment.h"
#include "Operator.h"
#include "Operand.h"
#include "Method.h"

#include "BScript.h"
#include "StandardEvaluateVisitor.h"

namespace bluemei{

struct NumberTester
{
	NumberTester()
	{
		testNumber();
	}
	void testNumber()
	{
		Integer i(5);
		Long l(10);
		Float f(1.25);
		Double d(3.25);

		String str=d.toString();

		Short s(2);
		str=s.toString();

		Boolean b(true);
		str=b.toString();

		Number* r=testAdd(&i,&f);
		delete r;

		r=testAdd(&l,&i);
		delete r;

		r=testAdd(&l,&f);
		delete r;

		r=testAdd(&l,&d);
		delete r;

		NumberAndVisiter and;
		NumberNegativeVisiter neg;

		f.accept(&and,&l);
		r=and.getResult();

		i.accept(&and,&l);
		r=and.getResult();

		f.accept(&neg,nullptr);
		r=neg.getResult();

		NumberAssignVisiter assignment;
		i.accept(&assignment,&l);
		d.accept(&assignment,r);

		NumberAssignMulVisiter assignmentMul;
		i.accept(&assignmentMul,&l);

		NumberDivForFloatVisiter fdivi;
		l.accept(&fdivi,&i);
		r=fdivi.getResult();
	}
	Number* testAdd(Number* num1,Number* num2)
	{
		NumberAddVisiter addVisiter;

		Number* r=nullptr;
		if (num1->precedence()>=num2->precedence())
		{
			//Number* numLow=num1->toThisType(num2);
			num1->accept(&addVisiter,num2);
			r=addVisiter.getResult();
		}
		else
		{
			std::auto_ptr<Number> numHigh=std::auto_ptr<Number>(num2->toThisType(num1));
			numHigh->accept(&addVisiter,num2);
			r=addVisiter.getResult();
		}
		return addVisiter.detachResult();
	}
};
static NumberTester testNm;

struct MethodTester : public ExpressionVisitor
{
	MethodTester()
	{
		OperatorAdd* add=new OperatorAdd();
		int pd=add->precedence();
		String str=add->getOperatorText();
		add->setLeftOperand(new OperandNumber(10));
		add->setRightOperand(new OperandNumber(12.8f));

		OperandNumber* result=new OperandNumber(0);
		result->setVarName("result");
		OperatorAssign* assign=new OperatorAssign();
		assign->setLeftOperand(result);
		assign->setRightOperand(add);

		Statment* stmt=new SimpleStatment(assign);

		Method method("function test()");
		method.setStatment(stmt);

		try
		{
			str=method.getText();
			method.accept(this);
			str=method.getText();
		}
		catch (Exception& e)
		{
			ErrorHandler::handle(e);
		}
	}
protected:	
	void checkOperandNumberNull(OperandNumber* operand)throw(NullPointerException)
	{
		if (operand==nullptr || operand->getNumber()==nullptr)
			throwpe(NullPointerException("evaluate number is null"));
	}
	void checkOperandNull(Expression* operand)throw(NullPointerException)
	{
		if (operand==nullptr)
			throwpe(NullPointerException("evaluate operand is null"));
	}
	OperandNumber* evaluateNumber(OperandNumber* operand1,OperandNumber* operand2,NumberVisiter& visitor)
	{
		checkOperandNumberNull(operand1);

		Number* num1=operand1->getNumber();
		Number* num2=(operand2==nullptr)?nullptr:operand2->getNumber();

		//比较优先级
		if(num2==nullptr || num1->precedence()>=num2->precedence()){
			//Number* numLow=num1->toThisType(num2);
			num1->accept(&visitor,num2);
		}
		else{
			std::auto_ptr<Number> numHigh(num2->toThisType(num1));
			numHigh->accept(&visitor,num2);
		}
		return new OperandNumber(visitor.detachResult());		
	}
	OperandNumber* evaluateAssign(OperandNumber* operand1,OperandNumber* operand2,NumberVisiter& visitor)
	{
		checkOperandNumberNull(operand1);
		checkOperandNumberNull(operand2);

		Number* num1=operand1->getNumber();
		Number* num2=operand2->getNumber();

		//赋值语句不需要比较优先级
		num1->accept(&visitor,num2);		
		return new OperandNumber(visitor.detachResult());		
	}
public:
	virtual bool visitStmt(SimpleStatment			* node){ return false; }
	virtual bool visitStmt(SequenceStatment			* node){ return false; }

	virtual bool visitStmt(IfElseStatment	   		* node){ return false; }
	virtual bool visitStmt(SwitchCaseStatment  		* node){ return false; }
	virtual bool visitStmt(WhileStatment	   		* node){ return false; }
	virtual bool visitStmt(DoWhileStatment	   		* node){ return false; }
	virtual bool visitStmt(ForStatment	   			* node){ return false; }

	virtual bool visitStmt(ReturnStatment	   		* node){ return false; }
	virtual bool visitStmt(BreakStatment	   		* node){ return false; }
	virtual bool visitStmt(ContinueStatment	   		* node){ return false; }
public:
	virtual Expression* visitExpr(OperatorAdd			* node){ 
		String t=node->getText();
		Expression* op1=node->getLeftOperand();
		Expression* op2=node->getRightOperand();
		checkOperandNull(op1);
		checkOperandNull(op2);		
		op1=op1->evaluate(this);//计算左子结果(共用this访问)
		op2=op2->evaluate(this);//计算右子结果(共用this访问)
		checkOperandNull(op1);
		checkOperandNull(op2);	
		OperandNumber* operand1=dynamic_cast<OperandNumber*>(op1);
		OperandNumber* operand2=dynamic_cast<OperandNumber*>(op2);		
		checkOperandNumberNull(operand1);
		checkOperandNumberNull(operand2);
		NumberAddVisiter add;
		OperandNumber* result=evaluateNumber(operand1,operand2,add);//运算
		return result;
	}
	virtual Expression* visitExpr(OperatorSub			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorMul			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorDiv			* node){ return nullptr; }

	virtual Expression* visitExpr(OperatorLessThan		* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorGreaterThan	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorLessThanEq	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorGreaterThanEq	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorEqual			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorNotEqual		* node){ return nullptr; }

	virtual Expression* visitExpr(OperatorLeftShift		* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorRightShift	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAnd			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorOr			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorMod			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorBitAnd		* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorBitOr			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorBitXor		* node){ return nullptr; }

	virtual Expression* visitExpr(OperatorAssign		* node){
		Expression* op1=node->getLeftOperand();
		Expression* op2=node->getRightOperand();
		checkOperandNull(op1);
		checkOperandNull(op2);		
		//op1=op1->evaluate(this);//计算左子结果(共用this访问)
		op2=op2->evaluate(this);//计算右子结果(共用this访问)
		checkOperandNull(op1);
		checkOperandNull(op2);	
		OperandNumber* operand1=dynamic_cast<OperandNumber*>(op1);
		OperandNumber* operand2=dynamic_cast<OperandNumber*>(op2);			
		NumberAssignVisiter assign;
		OperandNumber* result=evaluateAssign(operand1,operand2,assign);//运算
		return result;
	}
	virtual Expression* visitExpr(OperatorAssignAdd	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignSub	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignMul	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignDiv	* node){ return nullptr; }

	virtual Expression* visitExpr(OperatorAssignMod		* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignRShift	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignLShift	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignBAnd	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignBXor	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignBOr		* node){ return nullptr; }

	virtual Expression* visitExpr(OperatorNegative		* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorNot			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorBitNot		* node){ return nullptr; }

	virtual Expression* visitExpr(OperandNumber			* node){ return node; }
	virtual Expression* visitExpr(OperandRefrence		* node){ return nullptr; }
};
static MethodTester testerMh;


class ScriptTester
{
public:
	ScriptTester(){
		OperatorAdd* add=new OperatorAdd();
		int pd=add->precedence();
		String str=add->getOperatorText();
		add->setLeftOperand(new OperandNumber(10));
		add->setRightOperand(new OperandNumber(12.8f));

		OperandNumber* result=new OperandNumber(0);
		result->setVarName("result");
		OperatorAssign* assign=new OperatorAssign();
		assign->setLeftOperand(result);
		assign->setRightOperand(add);

		Statment* stmt=new SimpleStatment(assign);

		Method* method=new Method("function test()");
		method->setStatment(stmt);

		try
		{
			EvaluateContext ctx;
			ctx.setVisitor(new StandardEvaluateVisitor(&ctx));
			ctx.setStackFrame(new StackFrame());

			BScript sc(method);
			BSVar* rs=sc.evaluate(&ctx);
			delete rs;
		}
		catch (Exception& e)
		{
			ErrorHandler::handle(e);
		}

	}
};
/*
解析:
1.字符流FileReader->符号Token;
2.判断Token类型:
 2.1如果是表达式节点:利用栈方法解析出表达式树(expression);
 2.2如果是其他节点:利用递归方法解析出语句(program,statement,declareFun,declareVar,);
3.返回最顶端树根节点;
4.建立BScript准备执行.

*/

}//end of namespace bluemei
