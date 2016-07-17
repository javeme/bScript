#pragma once
#include "Object.h"
#include "RuntimeException.h"

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

}//end of namespace bluemei