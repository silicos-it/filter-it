/**********************************************************************
filterTitle.cpp - filter-it
 
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



#include <filters/filterTitle.h>



FilterTitle::FilterTitle(void)
{
   _titles.clear();
   _title.clear();
   _result.clear();
   _keyword = "TITLE";

}



FilterTitle::~FilterTitle(void)
{
}



FilterTitle::FilterTitle(const FilterTitle& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterTitle class members
   _titles = f._titles;
   _title = f._title;
   _result = f._result;
}



FilterTitle&
FilterTitle::operator=(const FilterTitle& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterTitle class members
   _titles = f._titles;
   _title = f._title;
   _result = f._result;

   // Return
   return *this;
}



std::string
FilterTitle::FailMessage(const OpenBabel::OBMol* mol) const
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



std::string
FilterTitle::Result(void) const
{
   return _result;
}



bool
FilterTitle::Initialise(const std::string& parameters, const bool tabulate)
{
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
   
   // Keyword
   std::size_t b(0);
   std::size_t e(line.find_first_of(_whiteSpace, b));
   data.push_back(line.substr(b, e - b));
   line.erase(b, e - b);
   for_each(data[0].begin(), data[0].end(), toupper);
   if (data[0] != _keyword)
   {
      std::cerr << "ERROR: Invalid " << _keyword << " entry: " << data[0];
      std::cerr << std::endl;
      exit(1);
   }
   
   // Title: extract all the content which is between the outermost quotes
   if (!tabulate)
   {
      b = line.find_first_of('\"');
      if (b == std::string::npos)
      {
         std::cerr << "ERROR: No \" token to specify title of " << _keyword << " entry";
         std::cerr << std::endl;
         exit(1);
      }
      ++b;
      e = line.find_last_of('\"');
      if (e == std::string::npos)
      {
         std::cerr << "ERROR: No terminating \" token to specify title of " << _keyword << " entry";
         std::cerr << std::endl;
         exit(1);
      }
      _title = line.substr(b, e - b);
   
      // Replace preceding backslash characters
      while ((e = _title.find("\\\"")) && (e != std::string::npos))
      {
         _title.erase(e, 1);
      }
      std::cerr << _title;
      _titles.insert(_title);
   }
   
   std::cerr << std::endl;
   _initialised = true;
   return true;
}



std::string
FilterTitle::Title(void) const
{
   return _title;
}



void
FilterTitle::Calculate(OpenBabel::OBMol* mol)
{
   std::string line = mol->GetTitle();
   _result = line;
   unsigned int b(0);
   unsigned int e(0);
   
   // Remove leading and trailing whitespace
   b = line.find_first_not_of(_whiteSpace);
   e = line.find_last_not_of(_whiteSpace);
   _result = line.substr(b, e - b + 1);
   
   if (_titles.count(_result))
   {
      _title = _result;
      _passed = true;
   }
   else
   {
      _title = "";
      _passed = false;
   }
}
