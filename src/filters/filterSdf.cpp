/**********************************************************************
filterSdf.cpp - filter-it
 
Copyright 2012-2013 by Silicos-it, a division of Imacosi BVBA
 
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



#include <filters/filterSdf.h>



FilterSdf::FilterSdf(void)
: _minLimit(true)
, _maxLimit(true)
{
   _keyword = "TAG";
   _tagName.clear();
}



FilterSdf::~FilterSdf(void)
{
}



FilterSdf::FilterSdf(const FilterSdf& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterSdf class members
   _minLimit = f._minLimit;
   _maxLimit = f._maxLimit;
   _tagName = f._tagName;
}



FilterSdf&
FilterSdf::operator=(const FilterSdf& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterSdf class members
   _minLimit = f._minLimit;
   _maxLimit = f._maxLimit;
   _tagName = f._tagName;

   return *this;
}



std::string
FilterSdf::TagName(void) const
{
   return _tagName;
}
