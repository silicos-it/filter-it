/**********************************************************************
filterElementsExcluded.cpp - filter-it
 
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



#include <filters/filterElementsExcluded.h>



FilterElementsExcluded::FilterElementsExcluded(void)
{
   _keyword = "EXCLUDED_ELEMENTS";
}



FilterElementsExcluded::~FilterElementsExcluded(void)
{
}



FilterElementsExcluded::FilterElementsExcluded(const FilterElementsExcluded& f)
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
   
   // FilterElementsOnly class members
}



FilterElementsExcluded&
FilterElementsExcluded::operator=(const FilterElementsExcluded& f)
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
   
   // FilterElementsOnly class members

   // Return
   return *this;
}



void
FilterElementsExcluded::Calculate(OpenBabel::OBMol* mol)
{
   // Store the molecular formula as result
   _result = mol->GetFormula();
   
   // Molecule is empty -> passes
   if (!mol->NumAtoms())
   {
      _result = "NA";
      _passed = true;
      return;
   }
   else
   {
      unsigned int number;
      for(OpenBabel::OBMolAtomIter atom(mol); atom; ++atom)
      {
         number = atom->GetAtomicNum();
         if (_elements.count(_number2symbol[number]))
         {
            _passed = false;
            return;
         }
      }
      
      // Take care of implicit hydrogens
      if (_elements.count("H"))
      {
         for(OpenBabel::OBMolAtomIter atom(mol); atom; ++atom)
         {
            if (atom->ImplicitHydrogenCount())
            {
               _passed = false;
               return;
            }
         }
      }
   }
   
   // Molecule passes
   _passed = true;
}
