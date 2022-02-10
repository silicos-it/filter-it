/**********************************************************************
counter.cpp - filter-it
 
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



#include <counter.h>



Counter::Counter(void)
: _totalMol(0)
, _failedMol(0)
, _passedMol(0)
{
}



Counter::~Counter(void)
{
}



Counter::Counter(const Counter& f)
{
   _totalMol = f._totalMol;
   _failedMol = f._failedMol;
   _passedMol = f._passedMol;
}



Counter&
Counter::operator=(const Counter& f)
{
   _totalMol = f._totalMol;
   _failedMol = f._failedMol;
   _passedMol = f._passedMol;
   return *this;
}



void
Counter::MolHasPassed(void)
{
   ++_passedMol;
   ++_totalMol;
}



void
Counter::MolHasFailed(void)
{
   ++_failedMol;
   ++_totalMol;
}



unsigned int
Counter::GetTotalMol(void) const
{
   return _totalMol;
}



unsigned int
Counter::GetFailedMol(void) const
{
   return _failedMol;
}



unsigned int
Counter::GetPassedMol(void) const
{
   return _passedMol;
}



std::string
Counter::Results(void) const
{
   std::ostringstream os;
   os << "MOLECULE COUNTS:" << std::endl;
   os << std::endl;
   os << " -> Passed: " << _passedMol << std::endl;
   os << " -> Failed: " << _failedMol << std::endl;
   os << " -> Total:  " << _totalMol << std::endl;
   os << std::endl;
   
   std::string out = os.str();
   return out;
}

