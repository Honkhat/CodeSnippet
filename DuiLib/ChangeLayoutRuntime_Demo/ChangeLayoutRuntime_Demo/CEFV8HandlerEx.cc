#include "CefHeaders.h"
#include "CEFV8HandlerEx.h"
#include <strsafe.h>


CCEFV8HandlerEx::TCppCallbackMap CCEFV8HandlerEx::g_mapCppCb;

CCEFV8HandlerEx::CCEFV8HandlerEx()
{

}

CCEFV8HandlerEx::~CCEFV8HandlerEx()
{
}


bool CCEFV8HandlerEx::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
	bool bRet = false;

	TCppCallbackMap::iterator it1 = g_mapCppCb.find(name.ToString());
	if(it1 != g_mapCppCb.end())
	{
		int iRet = 0;
		if(it1->second)
			iRet = (it1->second)(arguments);
		
		retval = CefV8Value::CreateInt(iRet);
		bRet = true;
	}
	
	return bRet;
}

void CCEFV8HandlerEx::RegisterCppCallback(std::string sName, TCppCallback oFunc)
{
	TCppCallbackMap::iterator it1 = g_mapCppCb.find(sName);
	if(it1 == g_mapCppCb.end())
		g_mapCppCb.insert(TCppCallbackMap::value_type(sName, oFunc));
}