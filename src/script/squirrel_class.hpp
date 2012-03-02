/* $Id: squirrel_class.hpp 20632 2010-08-26 22:01:16Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file squirrel_class.hpp Defines templates for converting C++ classes to Squirrel classes */

#ifndef SQUIRREL_CLASS_HPP
#define SQUIRREL_CLASS_HPP

#include "squirrel_helper.hpp"

/**
 * The template to define classes in Squirrel. It takes care of the creation
 *  and calling of such classes, to make the AI Layer cleaner while having a
 *  powerful script as possible AI language.
 */
template <class CL>
class DefSQClass {
private:
	const char *classname;

public:
	DefSQClass(const char *_classname) :
		classname(_classname)
	{}

	/**
	 * This defines a method inside a class for Squirrel.
	 */
	template <typename Func>
	void DefSQMethod(Squirrel *engine, Func function_proc, const char *function_name)
	{
		using namespace SQConvert;
		engine->AddMethod(function_name, DefSQNonStaticCallback<CL, Func>, 0, NULL, &function_proc, sizeof(function_proc));
	}

	/**
	 * This defines a method inside a class for Squirrel, which has access to the 'engine' (experts only!).
	 */
	template <typename Func>
	void DefSQAdvancedMethod(Squirrel *engine, Func function_proc, const char *function_name)
	{
		using namespace SQConvert;
		engine->AddMethod(function_name, DefSQAdvancedNonStaticCallback<CL, Func>, 0, NULL, &function_proc, sizeof(function_proc));
	}

	/**
	 * This defines a method inside a class for Squirrel with defined params.
	 * @note If you define nparam, make sure that he first param is always 'x',
	 *  which is the 'this' inside the function. This is hidden from the rest
	 *  of the code, but without it calling your function will fail!
	 */
	template <typename Func>
	void DefSQMethod(Squirrel *engine, Func function_proc, const char *function_name, int nparam, const char *params)
	{
		using namespace SQConvert;
		engine->AddMethod(function_name, DefSQNonStaticCallback<CL, Func>, nparam, params, &function_proc, sizeof(function_proc));
	}

	/**
	 * This defines a static method inside a class for Squirrel.
	 */
	template <typename Func>
	void DefSQStaticMethod(Squirrel *engine, Func function_proc, const char *function_name)
	{
		using namespace SQConvert;
		engine->AddMethod(function_name, DefSQStaticCallback<CL, Func>, 0, NULL, &function_proc, sizeof(function_proc));
	}

	/**
	 * This defines a static method inside a class for Squirrel with defined params.
	 * @note If you define nparam, make sure that he first param is always 'x',
	 *  which is the 'this' inside the function. This is hidden from the rest
	 *  of the code, but without it calling your function will fail!
	 */
	template <typename Func>
	void DefSQStaticMethod(Squirrel *engine, Func function_proc, const char *function_name, int nparam, const char *params)
	{
		using namespace SQConvert;
		engine->AddMethod(function_name, DefSQStaticCallback<CL, Func>, nparam, params, &function_proc, sizeof(function_proc));
	}

	template <typename Var>
	void DefSQConst(Squirrel *engine, Var value, const char *var_name)
	{
		engine->AddConst(var_name, value);
	}

	void PreRegister(Squirrel *engine)
	{
		engine->AddClassBegin(this->classname);
	}

	void PreRegister(Squirrel *engine, const char *parent_class)
	{
		engine->AddClassBegin(this->classname, parent_class);
	}

	template <typename Func, int Tnparam>
	void AddConstructor(Squirrel *engine, const char *params)
	{
		using namespace SQConvert;
		engine->AddMethod("constructor", DefSQConstructorCallback<CL, Func, Tnparam>, Tnparam, params);
	}

	void PostRegister(Squirrel *engine)
	{
		engine->AddClassEnd();
	}
};

#endif /* SQUIRREL_CLASS_HPP */
