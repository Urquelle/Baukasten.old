/*
    SLB - Simple Lua Binder
    Copyright (C) 2007-2010 Jose L. Hidalgo Valiño (PpluX)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
	
	Jose L. Hidalgo (www.pplux.com)
	pplux@pplux.com
*/



#ifndef __SLB_SCRIPT__
#define __SLB_SCRIPT__

#include "lua.hpp" 
#include "PushGet.hpp"
#include "Type.hpp"
#include<stdexcept>

namespace SLB {

	class ErrorHandler; // #include <SLB/Error.hpp>
	
	class SLB_EXPORT Script
	{	
	public:
		Script(bool loadDefaultLibs = true);
		virtual ~Script();

		void doFile(const std::string &filename) throw (std::exception);

		void doString(
			const std::string &codeChunk,
			const std::string &where_hint ="[SLB]") throw (std::exception);

		 /* ************************* WARNING *********************************
		  * Sometines you need to manually call Garbage Collector(GC), to be sure
		  * that all objects are destroyed. This is mandatory when using smartPointers
		  * be very carefull. GC operations are really expensive, avoid calling GC
		  * too frequently.
		  * ************************* WARNING *********************************/
		void callGC();

		/// Returns the number of Kb of memory used by the script
		size_t memUsage();

		/// Pass a new ErrorHandler, the error handler will be part of the object
		/// and it will be destroyed when the object is destroyed. 
		void setErrorHandler(ErrorHandler *h);

		template<class T>
		void set(const std::string &name, T value)
		{ SLB::setGlobal<T>(getState(), value, name.c_str());}

		template<class T>
		T get(const std::string&name)
		{ return SLB::getGlobal<T>(getState(), name.c_str()); }

	protected:
		virtual void onNewState(lua_State *L) {}
		virtual void onCloseState(lua_State *L) {}
		virtual void onGC(lua_State *L) {}

		lua_State* getState();
		void close(); // will close lua_state

	private:
		Script(const Script &s);
		Script& operator=(const Script&);
		lua_State *_L;
		ErrorHandler *_errorHandler;
		bool _loadDefaultLibs;
	};

}

#endif
