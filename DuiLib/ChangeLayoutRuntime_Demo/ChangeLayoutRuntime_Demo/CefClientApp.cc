#include "CefHeaders.h"
#include "CefClientApp.h"

CCefClientApp::CCefClientApp()
{
	v8Handler_ = new CCEFV8HandlerEx;

}

CCefClientApp::~CCefClientApp()
{
}


CefRefPtr<CefBrowserProcessHandler> CCefClientApp::GetBrowserProcessHandler()
{
	return this;
}

void CCefClientApp::OnBeforeCommandLineProcessing(const CefString & process_type, CefRefPtr<CefCommandLine> command_line)
{
	//加载flash插件
	//command_line->AppendSwitchWithValue("--ppapi-flash-path", "ppflash/18_0_0_209/pepflashplayer32_18_0_0_209.dll");
	//manifest.json中的version
	//command_line->AppendSwitchWithValue("--ppapi-flash-version", "18.0.0.209");
	//command_line->AppendSwitch("--disable-extensions");
}


void CCefClientApp::OnContextInitialized()
{

}


//CefRefPtr<CefRenderProcessHandler> CCefClientApp::GetRenderProcessHandler()
//{
//	return this;	
//}

void CCefClientApp::OnWebKitInitialized()
{
	std::string app_code =
		//-----------------------------------
		//声明JavaScript里要调用的Cpp方法
		"var CApp = CApp || {};"
		"if (!CApp)"
		"  CApp = {};"
		"(function() {"

		//Native Function: cOpenMedia;
		"  CApp.cOpenMedia = function(v1, v2) {"
		"    native function cOpenMedia();"
		"    return cOpenMedia(v1, v2);"
		"  };"

		//Native Function: cTagMsgRead;
		"  CApp.cTagMsgRead = function(v1) {"
		"    native function cTagMsgRead();"
		"    return cTagMsgRead(v1);"
		"  };"

		"  CApp.cSendEmail = function(v1, v2, v3) {"
		"    native function cSendEmail ();"
		"    return cSendEmail (v1,v2,v3);"
		"  };"

		"  CApp.cSelectAttach = function(v1, v2, v3) {"
		"    native function cSelectAttach ();"
		"    return cSelectAttach (v1,v2,v3);"
		"  };"

		"  CApp.cSaveDraft = function(v1, v2, v3) {"
		"    native function cSaveDraft ();"
		"    return cSaveDraft (v1,v2,v3);"
		"  };"

		"  CApp.cSelectInsertImg = function(v1, v2, v3) {"
		"    native function cSelectInsertImg ();"
		"    return cSelectInsertImg (v1, v2, v3);"
		"  };"

		"})();";


	// Register app extension module

	// JavaScript里调用app.jsInvokeCPlusPlus时，就会去通过CefRegisterExtension注册的CefV8Handler列表里查找
	// 找到"v8/app"对应的CCEFV8HandlerEx，就调用它的Execute方法
	// 假设v8Handler_是CCefClientApp的一个成员变量
	//v8Handler_ = new CCEFV8HandlerEx();

	CefRegisterExtension("v8/CApp", app_code, v8Handler_);
}

void CCefClientApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	CefRefPtr<CefV8Value> object = context->GetGlobal();// 获取到window  
	CefRefPtr<CefV8Value> str = CefV8Value::CreateString("C++ created Value!");
	object->SetValue("jsValue", str, V8_PROPERTY_ATTRIBUTE_NONE);

	CefRefPtr<CefV8Accessor> accessor = new MyV8Accessor;
	CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(accessor);

	obj->SetValue("myval", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);

	object->SetValue("myobject", obj, V8_PROPERTY_ATTRIBUTE_NONE);
}


void CCefClientApp::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	v8Handler_ = nullptr;
}
