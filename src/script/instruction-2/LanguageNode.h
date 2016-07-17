#pragma once
#include "Object.h"
#include "RuntimeException.h"
#include "NullPointerException.h"

namespace bluemei{

//语言二叉树节点接口
class LanguageNode : public Object
{
public:
	LanguageNode(){}
	virtual ~LanguageNode(){}
public:
	virtual LanguageNode* getLeftNode() const { return nullptr/*leftNode*/; }
	virtual void setLeftNode(LanguageNode* val) { throw RuntimeException("setLeftNode not supported");/*leftNode = val;*/ }

	virtual LanguageNode* getRightNode() const { return nullptr/*rightNode*/; }
	virtual void setRightNode(LanguageNode* val) { throw RuntimeException("setRightNode not supported");/*rightNode = val;*/ }

	virtual bool hasLeft() const { return false; }
	virtual bool hasRight() const { return false; }

	virtual int precedence() const { return 0; }
protected:
	//int precedence;
	//LanguageNode* leftNode;
	//LanguageNode* rightNode;
};

template<class ChildType,class SuperType>
inline ChildType* dcast(SuperType* super){ return dynamic_cast<ChildType*>(super); }

template<class T>
inline void checkNullPtr(T* p)throw(NullPointerException)
{
	if (p==nullptr){
		String str=String::format("instance of type %s* is null",CODE2STRING(T));
		throwpe(NullPointerException(str));
	}
}

}//end of namespace bluemei