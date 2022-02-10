/**********************************************************************
filterHbondAcceptors.cpp - filter-it
 
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



#include <filters/filterHbondAcceptors.h>



FilterHbondAcceptors::FilterHbondAcceptors(void)
{
   _keyword = "HBOND_ACCEPTORS";
}



FilterHbondAcceptors::~FilterHbondAcceptors(void)
{
}



FilterHbondAcceptors::FilterHbondAcceptors(const FilterHbondAcceptors& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterIntegerProperty class members
   _min = f._min;
   _max = f._max;
   _minLimit = f._minLimit;
   _maxLimit = f._maxLimit;
   _result = f._result;
}



FilterHbondAcceptors&
FilterHbondAcceptors::operator=(const FilterHbondAcceptors& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterIntegerProperty class members
   _min = f._min;
   _max = f._max;
   _minLimit = f._minLimit;
   _maxLimit = f._maxLimit;
   _result = f._result;

   // Return
   return *this;
}



void
FilterHbondAcceptors::Calculate(OpenBabel::OBMol* mol)
{
   _result = 0;
   for(OpenBabel::OBMolAtomIter atom(mol); atom; ++atom)
   {
      if (atom->IsNitrogen() &&              // Nitrogen
         !atom->IsAromatic() &&              // Aliphatic
         !atom->IsAmideNitrogen() &&         // No amide N
         ((atom->GetImplicitValence() - atom->GetHvyValence()) == 0) &&    // No H
         (atom->GetFormalCharge() <= 0))     // No + charge
      {
         ++_result;
         continue;
      }
      if (atom->IsNitrogen() &&              // Nitrogen
          atom->IsAromatic() &&              // Aromatic
         ((atom->GetImplicitValence() - atom->GetHvyValence()) == 0) &&    // No H
         (atom->GetHvyValence() <= 2) &&     // Maximal two non-H atoms connected
         (atom->GetFormalCharge() <= 0))     // No + charge
      {
         ++_result;
         continue;
      }
      if (atom->IsOxygen() &&                // Oxygen
         (atom->GetFormalCharge() <= 0))     // No + charge
      {
         ++_result;
         continue;
      }
      if (atom->IsSulfur() &&                // Sulfur
         (atom->GetFormalCharge() <= 0) &&   // No + charge
         (atom->GetHyb() == 2))  // sp2
      {
         ++_result;
         continue;
      }
   }
   
   if ((_minLimit && (_result < _min)) || (_maxLimit && (_result > _max)))
   {
      _passed = false;
   }
   else
   {
      _passed = true;
   }
}


