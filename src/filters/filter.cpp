/**********************************************************************
filter.cpp - filter-it
 
Copyright 2012-213 by Silicos-it, a division of Imacosi BVBA
 
This file is part of Filter-it.

	Filter-it is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published 
	by the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Filter-it is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Filter-it.  If not, see <http://www.gnu.org/licenses/>.

Filter-it is linked against OpenBabel version 2.

	OpenBabel is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation version 2 of the License.

***********************************************************************/



#include <filters/filter.h>



Filter::Filter(void)
: _initialised(false)
, _whiteSpace("\n\t \r")
, _passed(false)
, _keyword("")
{
}



Filter::~Filter(void)
{
}



Filter::Filter(const Filter& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
}



Filter&
Filter::operator=(const Filter& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;

   return *this;
}



std::string
Filter::Keyword(void) const
{
   return _keyword;
}



bool
Filter::IsInitialised(void) const
{
   return _initialised;
}



bool
Filter::HasPassed(void) const
{
   return _passed;
}



bool
Filter::HasFailed(void) const
{
   return !_passed;
}

