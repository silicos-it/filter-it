/**********************************************************************
filterRealProperty.h - filter-it
 
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



#include <filters/filterRealProperty.h>



FilterRealProperty::FilterRealProperty(void)
: _min(0.0)
, _max(0.0)
, _minLimit(true)
, _maxLimit(true)
, _result(0.0)
{
}



FilterRealProperty::~FilterRealProperty(void)
{
}



FilterRealProperty::FilterRealProperty(const FilterRealProperty& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterRealProperty class members
   _min = f._min;
   _max = f._max;
   _minLimit = f._minLimit;
   _maxLimit = f._maxLimit;
   _result = f._result;
}



FilterRealProperty&
FilterRealProperty::operator=(const FilterRealProperty& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterRealProperty class members
   _min = f._min;
   _max = f._max;
   _minLimit = f._minLimit;
   _maxLimit = f._maxLimit;
   _result = f._result;

   // Return
   return *this;
}



std::string
FilterRealProperty::FailMessage(const OpenBabel::OBMol* mol) const
{
   std::ostringstream os;
   std::string title = mol->GetTitle();
   os << title;
   os << " >> failed ";
   os << _keyword;
   os << " filter criterion (";
   os << _result;
   os << ")";
   
   return os.str();
}



double
FilterRealProperty::Result(void) const
{
   return _result;
}



bool
FilterRealProperty::Initialise(const std::string& parameters, const bool tabulate)
{
   // Variables
   std::istringstream is;
   
   // Write message
   std::cerr << "  -> " << _keyword << " ";

   // Make a copy of the input line
   std::string line(parameters);
   line.erase(0, line.find_first_not_of(_whiteSpace, 0));
   
   // Process the parameters
   std::vector<std::string> data;
   data.clear();
   line += " ";
   std::size_t b(0);
   std::size_t e(line.find_first_of(_whiteSpace, b));
   while ( (e <= line.size()) && (b != std::string::npos) )
   {
      data.push_back(line.substr(b, e - b));
      b = line.find_first_not_of(_whiteSpace, e);
      e = line.find_first_of(_whiteSpace, b);
   }
   
   for_each(data[0].begin(), data[0].end(), toupper);
   if (data[0] != _keyword)
   {
      std::cerr << "ERROR: Invalid " << _keyword << " entry: " << data[0];
      std::cerr << std::endl;
      exit(1);
   }
   
   if (!tabulate)
   {
      if (data.size() == 1)
      {
         std::cerr << "ERROR: " << _keyword << " entry is missing min and max limits";
         std::cerr << std::endl;
         exit(1);
      }
      else if(data.size() == 2)
      {
         std::cerr << "ERROR: " << _keyword << " entry is missing max limit";
         std::cerr << std::endl;
         exit(1);
      }
      else
      {
         if (data[1] == "*")
         {
            _minLimit = false;
            _min = 0;
            std::cerr << " *";
         }
         else
         {
            _minLimit = true;
            _min = atof(data[1].c_str());
            std::cerr << " " << _min;
         }
   
         if (data[2] == "*")
         {
            _maxLimit = false;
            _max = 0;
            std::cerr << " *";
         }
         else
         {
            _maxLimit = true;
            _max = atof(data[2].c_str());
            std::cerr << " " << _max;
         }
         if (_maxLimit && (_max < _min))
         {
            std::cerr << "ERROR: " << _keyword << ": max limit should be >= min ";
            std::cerr << std::endl;
            exit(1);
         }
      } 
   }
   
   std::cerr << std::endl;
   _initialised = true;
   return true;
}



