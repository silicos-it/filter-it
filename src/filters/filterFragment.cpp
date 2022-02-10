/**********************************************************************
filterFragment.cpp - filter-it
 
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



#include <filters/filterFragment.h>



FilterFragment::FilterFragment(void)
: _min(0)
, _max(0)
, _minLimit(true)
, _maxLimit(true)
, _result(0)
{
   _smarts.clear();
   _name.clear();
   _keyword = "FRAGMENT";
}



FilterFragment::~FilterFragment(void)
{
}



FilterFragment::FilterFragment(const FilterFragment& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterFragment class members
   _smarts = f._smarts;
   _ss = f._ss;
   _name = f._name;
   _min = f._min;
   _max = f._max;
   _minLimit = f._minLimit;
   _maxLimit = f._maxLimit;
   _result = f._result;
}



FilterFragment&
FilterFragment::operator=(const FilterFragment& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterFragment class members
   _smarts = f._smarts;
   _ss = f._ss;
   _name = f._name;

   _min = f._min;
   _max = f._max;
   _minLimit = f._minLimit;
   _maxLimit = f._maxLimit;
   _result = f._result;

   return *this;
}



std::string
FilterFragment::FailMessage(const OpenBabel::OBMol* mol) const
{
   std::ostringstream os;
   std::string title = mol->GetTitle();
   os << title;
   os << " >> failed ";
   os << _keyword;
   os << " \"";
   os << _name;
   os << "\" filter criterion (";
   os << _result;
   os << ")";
   title = os.str();
   return title;
}



unsigned int
FilterFragment::Result(void) const
{
   return _result;
}



bool
FilterFragment::Initialise(const std::string& parameters, const bool tabulate)
{
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
   
   if (data.size() == 1)
   {
      std::cerr << "ERROR: " << _keyword << " entry is missing fragment name and smarts";
      std::cerr << std::endl;
      exit(1);
   }
   else if (data.size() == 2)
   {
      std::cerr << "ERROR: " << _keyword << " entry is missing smarts";
      std::cerr << std::endl;
      exit(1);
   }
   else
   {
      // Name
      _name = data[1];
      std::cerr << " " << _name;
      
      // Smarts
      _smarts = data[2];
      if (_ss.Init(_smarts))
      {
         std::cerr << " " << _smarts;
      }
      else
      {
         std::cerr << _name << " \"" << _smarts << "\": ";
         std::cerr << "Failed parsing" << std::endl;
         exit(1);
      }
   }
   
   if (!tabulate)
   {
      if (data.size() == 3)
      {
         std::cerr << "ERROR: " << _keyword << " entry is missing min and max limits";
         std::cerr << std::endl;
         exit(1);
      }
      else if(data.size() == 4)
      {
         std::cerr << "ERROR: " << _keyword << " entry is missing max limit";
         std::cerr << std::endl;
         exit(1);
      }
      else
      {
         if (data[3] == "*")
         {
            _minLimit = false;
            _min = 0;
            std::cerr << " *";
         }
         else
         {
            _minLimit = true;
            _min = atoi(data[3].c_str());
            std::cerr << " " << _min;
         }
         if (_min < 0)
         {
            std::cerr << "ERROR: " << _keyword << ": min limit should be >= 0 ";
            std::cerr << std::endl;
            exit(1);
         }
   
         if (data[4] == "*")
         {
            _maxLimit = false;
            _max = 0;
            std::cerr << " *";
         }
         else
         {
            _maxLimit = true;
            _max = atoi(data[4].c_str());
            std::cerr << " " << _max;
         }
         if (_max < 0)
         {
            std::cerr << "ERROR: " << _keyword << ": max limit should be >= 0 ";
            std::cerr << std::endl;
            exit(1);
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



std::string
FilterFragment::Name(void) const
{
   return _name;
}



void
FilterFragment::Calculate(OpenBabel::OBMol* mol)
{
   std::vector< std::vector< int > > matches;
   _ss.Match(*mol, false);
   matches = _ss.GetUMapList();
   _result = matches.size();
   
   if ((_minLimit && (_result < _min)) || (_maxLimit && (_result > _max)))
   {
      _passed = false;
   }
   else
   {
      _passed = true;
   }
}


