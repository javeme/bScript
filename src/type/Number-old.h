#pragma once
#include "Object.h"

namespace bluemei{
	
typedef __int64 lint;

enum NumberPrecedence{
	PRED_LOWEST,
	PRED_BYTE,
	PRED_SHORT,
	PRED_INT,
	PRED_INT64,
	PRED_FLOAT,
	PRED_DOUBLE,
	PRED_HIGHEST
};

class Number;
class Integer;
class Long;
class Float;
class Double;
class NumberVisiter : public Object
{
public:
	NumberVisiter(){}
	virtual ~NumberVisiter(){}
public:
	virtual bool visitInteger(Integer* v,Number* other)=0;
	virtual bool visitLong(Long* v, Number* other)=0;
	virtual bool visitFloat(Float* v,Number* other)=0;	
	virtual bool visitDouble(Double* v, Number* other)=0;
};


class Number : public Object
{
public:
	Number(){}
	virtual ~Number(){}
	virtual Number& operator=(const Number& other)=0;
public:
	virtual int precedence()const=0;

	virtual int toInt()const=0;
	virtual lint toLong()const=0;
	virtual float toFloat()const=0;
	virtual double toDouble()const=0;

	virtual Number* toThisType(const Number* v)const=0;
	
	virtual bool accept(NumberVisiter* visitor,Number* other)=0;
};

template<class T>
class TNumber : public Number
{
public:
	TNumber(T v=0):number(v){}
	virtual ~TNumber(){}
public:
	TNumber(const Number& other){ *this=other; }
	TNumber& setValue(const T& v){ number=v; return *this; }
	operator T()const{ return number; }
public:
	virtual int toInt() const
	{
		return (int)number;
	}

	virtual lint toLong() const
	{
		return (lint)number;
	}

	virtual double toDouble() const
	{
		return (double)number;
	}

	virtual float toFloat() const
	{
		return (float)number;
	}
	
	virtual String toString()const
	{
		return Value2String<T>(number);
	}
protected:
	T number;
};

/*template<> 
class TNumber<int>
{
public:
	TNumber<int>& operator=(const Number& other){
		number=other.toInt();
		return *this;
	}
	virtual int precedence() const
	{
		return PRED_INT;
	}
};
typedef TNumber<int> Integer;*/
class Integer : public TNumber<int>
{
public:
	DECLARE_DCLASS(Integer);
public:
	explicit Integer(int v=0):TNumber(v){}
	Integer& operator=(const Number& other){
		number=other.toInt();
		return *this;
	}

	virtual int precedence() const
	{
		return PRED_INT;
	}

	virtual Number* toThisType(const Number* v) const
	{
		return new Integer(v->toInt());
	}

	virtual bool accept(NumberVisiter* visitor,Number* other)
	{
		return visitor->visitInteger(this,other);
	}
};

class Char : public Integer
{
public:
	DECLARE_DCLASS(Char);
public:
	Char(char v=0):Integer(v){}
	Char& operator=(const Number& other){
		number=other.toInt();
		return *this;
	}

	virtual Number* toThisType(const Number* v) const
	{
		return new Char((char)v->toInt());
	}
	
	operator char()const{ return (char)number; }
};

class Boolean : public Integer
{
public:
	DECLARE_DCLASS(Boolean);
public:
	Boolean(bool v=false):Integer(v){}
	Boolean& operator=(const Number& other){
		number=other.toInt();
		return *this;
	}

	virtual Number* toThisType(const Number* v) const
	{
		return new Boolean((bool)v->toInt());
	}

	operator bool()const{ return (bool)number; }

	virtual String toString()const
	{
		return Value2String<bool>(number);
	}
};

class Short : public Integer
{
public:
	DECLARE_DCLASS(Short);
public:
	Short(short v=0):Integer(v){}
	Short& operator=(const Number& other){
		number=other.toInt();
		return *this;
	}

	virtual Number* toThisType(const Number* v) const
	{
		return new Short((short)v->toInt());
	}

	operator short()const{ return (short)number; }
};

class Long : public TNumber<lint>
{
public:
	DECLARE_DCLASS(Long);
public:
	Long(lint v=0):TNumber(v){}
	Long& operator=(const Number& other){
		number=other.toInt();
		return *this;
	}

	virtual int precedence() const
	{
		return PRED_INT64;
	}

	virtual Number* toThisType(const Number* v) const
	{
		return new Long(v->toInt());
	}

	virtual bool accept(NumberVisiter* visitor,Number* other)
	{
		return visitor->visitLong(this,other);
	}
};

class Float : public TNumber<float>
{
public:
	DECLARE_DCLASS(Float);
public:
	Float(float v=0):TNumber(v){}
	Float& operator=(const Number& other){
		number=other.toFloat();
		return *this;
	}

	virtual int precedence() const
	{
		return PRED_FLOAT;
	}

	virtual Number* toThisType(const Number* v) const
	{
		return new Float(v->toFloat());
	}
	
	virtual bool accept(NumberVisiter* visitor,Number* other)
	{
		return visitor->visitFloat(this,other);
	}
};

class Double : public TNumber<double>
{
public:
	DECLARE_DCLASS(Double);
public:
	Double(double v=0):TNumber(v){}
	Double& operator=(const Number& other){
		number=other.toInt();
		return *this;
	}

	virtual int precedence() const
	{
		return PRED_DOUBLE;
	}

	virtual Number* toThisType(const Number* v) const
	{
		return new Double(v->toInt());
	}

	virtual bool accept(NumberVisiter* visitor,Number* other)
	{
		return visitor->visitDouble(this,other);
	}
};

//保留浮点结果的除法
class NumberDivForFloatVisiter : public NumberVisiter
{
public:
	NumberDivForFloatVisiter(){
		result=nullptr;
	}
	virtual ~NumberDivForFloatVisiter(){
		delete result;
		result=nullptr;
	}
public:
	Number* getResult() const { return result; }
public:
	virtual bool visitInteger(Integer* v,Number* other) 
	{
		delete result;
		result=new Double((int)*v / other->toDouble());
		return true;
	}

	virtual bool visitLong(Long* v, Number* other) 
	{
		delete result;
		result=new Double((lint)*v / other->toDouble());
		return true;
	}

	virtual bool visitFloat(Float* v,Number* other) 
	{
		delete result;
		result=new Float((float)*v / other->toFloat());
		return true;
	}

	virtual bool visitDouble(Double* v, Number* other) 
	{
		delete result;
		result=new Double((double)*v / other->toDouble());
		return true;
	}
	
protected:
	Number* result;
};


//添加一个所有数据类型的访问者(+,-,*,/,>,<...)
#define ADD_ALL_NumberVisiter(className,op)\
	class className : public NumberVisiter								\
	{																	\
	public:																\
		className(){													\
			result=nullptr;												\
		}																\
		virtual ~className(){											\
			delete result;												\
			result=nullptr;												\
		}																\
	public:																\
		Number* getResult() const { return result; }					\
		Number* detachResult() { 										\
			Number* tmp=result; 										\
			result=nullptr; 											\
			return tmp; 												\
		}																\
	public:																\
		virtual bool visitInteger(Integer* v,Number* other) 			\
		{																\
			delete result;												\
			result=new Integer((int)*v op other->toInt());				\
			return true;												\
		}																\
																		\
		virtual bool visitLong(Long* v, Number* other) 					\
		{																\
			delete result;												\
			result=new Long((lint)*v op other->toLong());				\
			return true;												\
		}																\
																		\
		virtual bool visitFloat(Float* v,Number* other) 				\
		{																\
			delete result;												\
			result=new Float((float)*v op other->toFloat());			\
			return true;												\
		}																\
																		\
		virtual bool visitDouble(Double* v, Number* other) 				\
		{																\
			delete result;												\
			result=new Double((double)*v op other->toDouble());			\
			return true;												\
		}																\
																		\
	protected:															\
		Number* result;													\
	};

ADD_ALL_NumberVisiter(NumberAddVisiter			, + );
ADD_ALL_NumberVisiter(NumberSubVisiter			, - );
ADD_ALL_NumberVisiter(NumberMulVisiter			, * );
ADD_ALL_NumberVisiter(NumberDivVisiter			, / );

ADD_ALL_NumberVisiter(NumberLessThanVisiter		, < );
ADD_ALL_NumberVisiter(NumberGreaterThanVisiter	, > );
ADD_ALL_NumberVisiter(NumberLessThanEqVisiter	, <= );
ADD_ALL_NumberVisiter(NumberGreaterThanEqVisiter, >= );
ADD_ALL_NumberVisiter(NumberEqualVisiter		, == );
ADD_ALL_NumberVisiter(NumberNotEqualVisiter		, != );

//添加一个整型数据类型的访问者(<<,>>,&&,||,%,&,|,^)
#define ADD_INT_NumberVisiter(className,op)\
	class className : public NumberVisiter								\
	{																	\
	public:																\
		className(){													\
			result=nullptr;												\
		}																\
		virtual ~className(){											\
			delete result;												\
			result=nullptr;												\
		}																\
	public:																\
		Number* getResult() const { return result; }					\
		Number* detachResult() { 										\
			Number* tmp=result; 										\
			result=nullptr; 											\
			return tmp; 												\
		}																\
	public:																\
		virtual bool visitInteger(Integer* v,Number* other) 			\
		{																\
			delete result;												\
			result=new Integer((int)*v op other->toInt());				\
			return true;												\
		}																\
																		\
		virtual bool visitLong(Long* v, Number* other) 					\
		{																\
			delete result;												\
			result=new Long((lint)*v op other->toLong());				\
			return true;												\
		}																\
																		\
		virtual bool visitFloat(Float* v,Number* other) 				\
		{																\
			return false;												\
		}																\
																		\
		virtual bool visitDouble(Double* v, Number* other) 				\
		{																\
			return false;												\
		}																\
	protected:															\
		Number* result;													\
	};

ADD_INT_NumberVisiter(NumberLeftShiftVisiter	, <<);
ADD_INT_NumberVisiter(NumberRightShiftVisiter	, >>);
ADD_INT_NumberVisiter(NumberAndVisiter			, &&);
ADD_INT_NumberVisiter(NumberOrVisiter			, ||);
ADD_INT_NumberVisiter(NumberModVisiter			, % );
ADD_INT_NumberVisiter(NumberBitAndVisiter		, & );
ADD_INT_NumberVisiter(NumberBitOrVisiter		, | );
ADD_INT_NumberVisiter(NumberBitXorVisiter		, ^ );

//添加一个所有数据类型的单目运算的访问者(-,&,*)
#define ADD_ONE_ALL_NumberVisiter(className,op)\
	class className : public NumberVisiter								\
	{																	\
	public:																\
		className(){													\
			result=nullptr;												\
		}																\
		virtual ~className(){											\
			delete result;												\
			result=nullptr;												\
		}																\
	public:																\
		Number* getResult() const { return result; }					\
		Number* detachResult() { 										\
			Number* tmp=result; 										\
			result=nullptr; 											\
			return tmp; 												\
		}																\
	public:																\
		virtual bool visitInteger(Integer* v,Number* other) 			\
		{																\
			delete result;												\
			result=new Integer(op(int)*v);								\
			return true;												\
		}																\
																		\
		virtual bool visitLong(Long* v, Number* other) 					\
		{																\
			delete result;												\
			result=new Long(op(lint)*v);								\
			return true;												\
		}																\
																		\
		virtual bool visitFloat(Float* v,Number* other) 				\
		{																\
			delete result;												\
			result=new Float(op(float)*v);								\
			return true;												\
		}																\
																		\
		virtual bool visitDouble(Double* v, Number* other) 				\
		{																\
			delete result;												\
			result=new Double(op(double)*v);							\
			return true;												\
		}																\
	protected:															\
		Number* result;													\
	};

ADD_ONE_ALL_NumberVisiter(NumberNegativeVisiter	, - );

//添加一个整型数据类型的单目运算的访问者
#define ADD_ONE_INT_NumberVisiter(className,op)\
	class className : public NumberVisiter								\
	{																	\
	public:																\
		className(){													\
			result=nullptr;												\
		}																\
		virtual ~className(){											\
			delete result;												\
			result=nullptr;												\
		}																\
	public:																\
		Number* getResult() const { return result; }					\
		Number* detachResult() { 										\
			Number* tmp=result; 										\
			result=nullptr; 											\
			return tmp; 												\
		}																\
	public:																\
		virtual bool visitInteger(Integer* v,Number* other) 			\
		{																\
			delete result;												\
			result=new Integer(op(int)*v);								\
			return true;												\
		}																\
																		\
		virtual bool visitLong(Long* v, Number* other) 					\
		{																\
			delete result;												\
			result=new Long(op(lint)*v);								\
			return true;												\
		}																\
																		\
		virtual bool visitFloat(Float* v,Number* other) 				\
		{																\
			return false;												\
		}																\
																		\
		virtual bool visitDouble(Double* v, Number* other) 				\
		{																\
			return false;												\
		}																\
	protected:															\
		Number* result;													\
	};

ADD_ONE_INT_NumberVisiter(NumberNotVisiter		, ! );
ADD_ONE_INT_NumberVisiter(NumberBitNotVisiter	, ~ );

//添加所有数据类型的赋值运算的访问者(=,+=,*=...)
#define ADD_ASSIGN_NumberVisiter(className,op)							 \
	class className : public NumberVisiter								 \
	{																	 \
	public:																 \
		className(){													 \
			result=nullptr;												 \
		}																 \
		virtual ~className(){											 \
			delete result;												 \
			result=nullptr;												 \
		}																 \
	public:																 \
		Number* getResult() const { return result; }					 \
		Number* detachResult() { 										 \
			Number* tmp=result; 										 \
			result=nullptr; 											 \
			return tmp; 												 \
		}																 \
	public:																 \
		virtual bool visitInteger(Integer* v,Number* other) 			 \
		{																 \
			delete result;												 \
			int i=v->toInt();											 \
			i op other->toInt();										 \
			v->setValue(i);												 \
			result=new Integer(i);										 \
			return true;												 \
		}																 \
																		 \
		virtual bool visitLong(Long* v, Number* other) 					 \
		{																 \
			delete result;												 \
			lint i=v->toLong();											 \
			i op other->toLong();										 \
			v->setValue(i);												 \
			result=new Long(i);											 \
			return true;												 \
		}																 \
																		 \
		virtual bool visitFloat(Float* v,Number* other) 				 \
		{																 \
			delete result;												 \
			float f=v->toFloat();										 \
			f op other->toFloat();										 \
			v->setValue(f);												 \
			result=new Float(f);										 \
			return true;												 \
		}																 \
																		 \
		virtual bool visitDouble(Double* v, Number* other) 				 \
		{																 \
			delete result;												 \
			double f=v->toDouble();										 \
			f op other->toDouble();										 \
			v->setValue(f);												 \
			result=new Double(f);										 \
			return true;												 \
		}																 \
	protected:															 \
		Number* result;													 \
	};

ADD_ASSIGN_NumberVisiter(NumberAssignVisiter		, =		);
ADD_ASSIGN_NumberVisiter(NumberAssignAddVisiter		, +=	);
ADD_ASSIGN_NumberVisiter(NumberAssignSubVisiter		, -=	);
ADD_ASSIGN_NumberVisiter(NumberAssignMulVisiter		, *=	);
ADD_ASSIGN_NumberVisiter(NumberAssignDivVisiter		, /=	);

//添加一个整型数据类型的赋值运算的访问者(%=,&=,>>=...)
#define ADD_ASSIGN_INT_NumberVisiter(className,op)						 \
	class className : public NumberVisiter								 \
	{																	 \
	public:																 \
		className(){													 \
			result=nullptr;												 \
		}																 \
		virtual ~className(){											 \
			delete result;												 \
			result=nullptr;												 \
		}																 \
	public:																 \
		Number* getResult() const { return result; }					 \
		Number* detachResult() { 										 \
			Number* tmp=result; 										 \
			result=nullptr; 											 \
			return tmp; 												 \
		}																 \
	public:																 \
		virtual bool visitInteger(Integer* v,Number* other) 			 \
		{																 \
			delete result;												 \
			int i=v->toInt();											 \
			i op other->toInt();										 \
			v->setValue(i);												 \
			result=new Integer(i);										 \
			return true;												 \
		}																 \
																		 \
		virtual bool visitLong(Long* v, Number* other) 					 \
		{																 \
			delete result;												 \
			lint i=v->toLong();											 \
			i op other->toLong();										 \
			v->setValue(i);												 \
			result=new Long(i);											 \
			return true;												 \
		}																 \
																		 \
		virtual bool visitFloat(Float* v,Number* other) 				 \
		{																 \
			return false;												 \
		}																 \
																		 \
		virtual bool visitDouble(Double* v, Number* other) 				 \
		{																 \
			return false;												 \
		}																 \
	protected:															 \
		Number* result;													 \
	};

ADD_ASSIGN_INT_NumberVisiter(NumberAssignModVisiter		, %=	);
ADD_ASSIGN_INT_NumberVisiter(NumberAssignRShiftVisiter	, >>=	);
ADD_ASSIGN_INT_NumberVisiter(NumberAssignLShiftVisiter	, <<=	);
ADD_ASSIGN_INT_NumberVisiter(NumberAssignBAndVisiter	, &=	);
ADD_ASSIGN_INT_NumberVisiter(NumberAssignBXorVisiter	, ^=	);
ADD_ASSIGN_INT_NumberVisiter(NumberAssignBOrVisiter		, |=	);

struct Tester
{
	Tester()
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

static Tester t;
边解析边建节点树,同时,遇到变量则分配变量空间,并加到局部(全局)变量map中去,已经分配的变量可以被后面的表达式引用;
只有在函数调用传参和返回值的时候才需要用到栈;

}//end of namespace bluemei

