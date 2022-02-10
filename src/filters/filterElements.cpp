/**********************************************************************
filterElements.cpp - filter-it
 
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



#include <filters/filterElements.h>



FilterElements::FilterElements(void)
{
   _elements.clear();
   _result.clear();

   _validElements.clear();
   _validElements.insert("Ac");
   _validElements.insert("Al");
   _validElements.insert("Am");
   _validElements.insert("Sb");
   _validElements.insert("Ar");
   _validElements.insert("As");
   _validElements.insert("At");
   _validElements.insert("Ba");
   _validElements.insert("Bk");
   _validElements.insert("Be");
   _validElements.insert("Bi");
   _validElements.insert("Bh");
   _validElements.insert("B");
   _validElements.insert("Br");
   _validElements.insert("Cd");
   _validElements.insert("Ca");
   _validElements.insert("Cf");
   _validElements.insert("C");
   _validElements.insert("Ce");
   _validElements.insert("Cs");
   _validElements.insert("Cl");
   _validElements.insert("Cr");
   _validElements.insert("Co");
   _validElements.insert("Cu");
   _validElements.insert("Cm");
   _validElements.insert("D");
   _validElements.insert("Ds");
   _validElements.insert("Db");
   _validElements.insert("Dy");
   _validElements.insert("Es");
   _validElements.insert("Er");
   _validElements.insert("Eu");
   _validElements.insert("Fm");
   _validElements.insert("F");
   _validElements.insert("Fr");
   _validElements.insert("Gd");
   _validElements.insert("Ga");
   _validElements.insert("Ge");
   _validElements.insert("Au");
   _validElements.insert("Hf");
   _validElements.insert("Hs");
   _validElements.insert("He");
   _validElements.insert("Ho");
   _validElements.insert("H");
   _validElements.insert("In");
   _validElements.insert("I");
   _validElements.insert("Ir");
   _validElements.insert("Fe");
   _validElements.insert("Kr");
   _validElements.insert("La");
   _validElements.insert("Lr");
   _validElements.insert("Pb");
   _validElements.insert("Li");
   _validElements.insert("Lu");
   _validElements.insert("Mg");
   _validElements.insert("Mn");
   _validElements.insert("Mt");
   _validElements.insert("Md");
   _validElements.insert("Hg");
   _validElements.insert("Mo");
   _validElements.insert("Nd");
   _validElements.insert("Ne");
   _validElements.insert("Np");
   _validElements.insert("Ni");
   _validElements.insert("Nb");
   _validElements.insert("N");
   _validElements.insert("No");
   _validElements.insert("Os");
   _validElements.insert("O");
   _validElements.insert("Pd");
   _validElements.insert("P");
   _validElements.insert("Pt");
   _validElements.insert("Pu");
   _validElements.insert("Po");
   _validElements.insert("K");
   _validElements.insert("Pr");
   _validElements.insert("Pm");
   _validElements.insert("Pa");
   _validElements.insert("Ra");
   _validElements.insert("Rn");
   _validElements.insert("Re");
   _validElements.insert("Rh");
   _validElements.insert("Rb");
   _validElements.insert("Ru");
   _validElements.insert("Rf");
   _validElements.insert("Sm");
   _validElements.insert("Sc");
   _validElements.insert("Sg");
   _validElements.insert("Se");
   _validElements.insert("Si");
   _validElements.insert("Ag");
   _validElements.insert("Na");
   _validElements.insert("Sr");
   _validElements.insert("S");
   _validElements.insert("T");
   _validElements.insert("Ta");
   _validElements.insert("Tc");
   _validElements.insert("Te");
   _validElements.insert("Tb");
   _validElements.insert("Tl");
   _validElements.insert("Th");
   _validElements.insert("Tm");
   _validElements.insert("Sn");
   _validElements.insert("Ti");
   _validElements.insert("W");
   _validElements.insert("U");
   _validElements.insert("V");
   _validElements.insert("Xe");
   _validElements.insert("Yb");
   _validElements.insert("Y");
   _validElements.insert("Zn");
   _validElements.insert("Zr");

   _number2symbol.clear();
   _number2symbol.push_back("X"); // Reserve space for number 0
   _number2symbol.push_back("H");
   _number2symbol.push_back("He");
   _number2symbol.push_back("Li");
   _number2symbol.push_back("Be");
   _number2symbol.push_back("B");
   _number2symbol.push_back("C");
   _number2symbol.push_back("N");
   _number2symbol.push_back("O");
   _number2symbol.push_back("F");
   _number2symbol.push_back("Ne");
   _number2symbol.push_back("Na");
   _number2symbol.push_back("Mg");
   _number2symbol.push_back("Al");
   _number2symbol.push_back("Si");
   _number2symbol.push_back("P");
   _number2symbol.push_back("S");
   _number2symbol.push_back("Cl");
   _number2symbol.push_back("Ar");
   _number2symbol.push_back("K");
   _number2symbol.push_back("Ca");
   _number2symbol.push_back("Sc");
   _number2symbol.push_back("Ti");
   _number2symbol.push_back("V");
   _number2symbol.push_back("Cr");
   _number2symbol.push_back("Mn");
   _number2symbol.push_back("Fe");
   _number2symbol.push_back("Co");
   _number2symbol.push_back("Ni");
   _number2symbol.push_back("Cu");
   _number2symbol.push_back("Zn");
   _number2symbol.push_back("Ga");
   _number2symbol.push_back("Ge");
   _number2symbol.push_back("As");
   _number2symbol.push_back("Se");
   _number2symbol.push_back("Br");
   _number2symbol.push_back("Kr");
   _number2symbol.push_back("Rb");
   _number2symbol.push_back("Sr");
   _number2symbol.push_back("Y");
   _number2symbol.push_back("Zr");
   _number2symbol.push_back("Nb");
   _number2symbol.push_back("Mo");
   _number2symbol.push_back("Tc");
   _number2symbol.push_back("Ru");
   _number2symbol.push_back("Rh");
   _number2symbol.push_back("Pd");
   _number2symbol.push_back("Ag");
   _number2symbol.push_back("Cd");
   _number2symbol.push_back("In");
   _number2symbol.push_back("Sn");
   _number2symbol.push_back("Sb");
   _number2symbol.push_back("Te");
   _number2symbol.push_back("I");
   _number2symbol.push_back("Xe");
   _number2symbol.push_back("Cs");
   _number2symbol.push_back("Ba");
   _number2symbol.push_back("La");
   _number2symbol.push_back("Ce");
   _number2symbol.push_back("Pr");
   _number2symbol.push_back("Nd");
   _number2symbol.push_back("Pm");
   _number2symbol.push_back("Sm");
   _number2symbol.push_back("Eu");
   _number2symbol.push_back("Gd");
   _number2symbol.push_back("Tb");
   _number2symbol.push_back("Dy");
   _number2symbol.push_back("Ho");
   _number2symbol.push_back("Er");
   _number2symbol.push_back("Tm");
   _number2symbol.push_back("Yb");
   _number2symbol.push_back("Lu");
   _number2symbol.push_back("Hf");
   _number2symbol.push_back("Ta");
   _number2symbol.push_back("W");
   _number2symbol.push_back("Re");
   _number2symbol.push_back("Os");
   _number2symbol.push_back("Ir");
   _number2symbol.push_back("Pt");
   _number2symbol.push_back("Au");
   _number2symbol.push_back("Hg");
   _number2symbol.push_back("Tl");
   _number2symbol.push_back("Pb");
   _number2symbol.push_back("Bi");
   _number2symbol.push_back("Po");
   _number2symbol.push_back("At");
   _number2symbol.push_back("Rn");
   _number2symbol.push_back("Fr");
   _number2symbol.push_back("Ra");
   _number2symbol.push_back("Ac");
   _number2symbol.push_back("Th");
   _number2symbol.push_back("Pa");
   _number2symbol.push_back("U");
   _number2symbol.push_back("Np");
   _number2symbol.push_back("Pu");
   _number2symbol.push_back("Am");
   _number2symbol.push_back("Cm");
   _number2symbol.push_back("Bk");
   _number2symbol.push_back("Cf");
   _number2symbol.push_back("Es");
   _number2symbol.push_back("Fm");
   _number2symbol.push_back("Md");
   _number2symbol.push_back("No");
   _number2symbol.push_back("Lr");
   _number2symbol.push_back("Rf");
   _number2symbol.push_back("Db");
   _number2symbol.push_back("Sg");
   _number2symbol.push_back("Bh");
   _number2symbol.push_back("Hs");
   _number2symbol.push_back("Mt");
   _number2symbol.push_back("Ds");
   _number2symbol.push_back("Rg");
   _number2symbol.push_back("Cn");
   _number2symbol.push_back("Uut");
   _number2symbol.push_back("Uuq");
   _number2symbol.push_back("Uup");
   _number2symbol.push_back("Uuh");
   _number2symbol.push_back("Uus");
   _number2symbol.push_back("Uuo");
}



FilterElements::~FilterElements(void)
{
}



FilterElements::FilterElements(const FilterElements& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterElements class members
   _elements = f._elements;
   _validElements = f._validElements;
   _result = f._result;
   _number2symbol = f._number2symbol;
}



FilterElements&
FilterElements::operator=(const FilterElements& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterElements class members
   _elements = f._elements;
   _validElements = f._validElements;
   _result = f._result;
   _number2symbol = f._number2symbol;

   // Return
   return *this;
}



std::string
FilterElements::FailMessage(const OpenBabel::OBMol* mol) const
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
FilterElements::Result(void) const
{
   return _result;
}



bool
FilterElements::Initialise(const std::string& parameters, const bool tabulate)
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
   
   if (!tabulate)
   {
      if (data.size() < 2)
      {
         std::cerr << "ERROR: No elements specified in " << _keyword << " entry";
         std::cerr << std::endl;
         exit(1);
      }
      for (unsigned int i = 1; i < data.size(); ++i)
      {
         std::string tmp = data[i];
         tmp[0] = toupper(tmp[0]);
         for (unsigned int c = 1; c < tmp.length(); ++c)
         {
            tmp[c] = tolower(tmp[c]);
         }
         if (_validElements.count(tmp) < 1)
         {
            std::cerr << "ERROR: Invalid element " << data[i];
            std::cerr << " in " << _keyword << " entry";
            std::cerr << std::endl;
            exit(1);
         }
         else
         {
            _elements.insert(tmp);
            std::cerr << " " << tmp;
         }
      }
   }
   
   std::cerr << std::endl;
   _initialised = true;
   return true;
}

