/*
   Copyright (C) 2005 A. Bram Neijt <bneijt@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*/


#include "alternatives.ih"

//Using the conrtol sequence, globstring the additions to the current pwd and recurse in them.
//When hitting the end of control, add the value tot the list of known values
namespace
{
//Return true if they match, keeping in mind the case that is needed
bool match(bool caseIn, char const &rvalue, char const &lvalue)
{
	if(caseIn)
		return tolower(rvalue) == tolower(lvalue);
	return rvalue == lvalue;
}

}//namspace

//This is a recursive function, it's either done or delegates a small piece of the puzzle to itself.
void Alternatives::recurse(string::size_type index, string const &control, string pwd, GlobContext &context)
{
    bool d_caseIn = true;
	msg() << "Recursing pattern `" << pwd << "' with '" << control << "' at " << index << info;
	
	//Done
	if(index == control.size())
	{
		//Add pwd, we made it to the end
		globFilter(pwd.c_str(), context);
		return;
	}

	//Leave slashes
	if(control[index] == '/')
	{
		//Slash will be atomatically added in recurse
		return recurse(++index, control, pwd, context);
	}
	
	//Delegate
	vector<string> *list = new vector<string>();
	
	if(d_caseIn)
	{
		//Case insensitive globbing...
		Glob globLower(pwd + '/' + static_cast<char>(tolower(control[index]))+ '*');
		for(char const *const *i = globLower.begin(); i != globLower.end(); ++i)
		    list->push_back(*i);

		
		Glob globUpper(pwd + '/' + static_cast<char>(toupper(control[index]))+ '*');
		for(char const *const *i = globUpper.begin(); i != globUpper.end(); ++i)
		    list->push_back(*i);
		
	}
	else
	{
		Glob glob(pwd + '/' + static_cast<char>(toupper(control[index]))+ '*');
		for(char const *const * i = glob.begin(); i != glob.end(); ++i)
		    list->push_back(*i);
	}
	
	for(vector<string>::iterator i = list->begin();
			i != list->end();
			++i)
	{
		//Recurse the first letter
		recurse(index + 1, control, *i, context);//string::size_type index, string const &control, string pwd, GlobContext &context
		
		//Recurse according to basename match
		string bn = basename((*i).c_str());
		for(unsigned off = 1;
				match(d_caseIn, bn[off], control[index + off]);
				++off)
			recurse(index + off + 1, control, *i, context);
	}
	
	
	delete list;
}
