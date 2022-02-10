/**********************************************************************
filterAtomsInLargestRingsystem.cpp - filter-it
 
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



#include <filters/filterAtomsInLargestRingsystem.h>



FilterAtomsInLargestRingsystem::FilterAtomsInLargestRingsystem(void)
{
   _keyword = "ATOMS_IN_LARGEST_RINGSYSTEM";
}



FilterAtomsInLargestRingsystem::~FilterAtomsInLargestRingsystem(void)
{
}



FilterAtomsInLargestRingsystem::FilterAtomsInLargestRingsystem(const FilterAtomsInLargestRingsystem& f)
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



FilterAtomsInLargestRingsystem&
FilterAtomsInLargestRingsystem::operator=(const FilterAtomsInLargestRingsystem& f)
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
FilterAtomsInLargestRingsystem::Calculate(OpenBabel::OBMol* mol)
{
   // Are there rings?
   bool rings = false;
   OpenBabel::OBAtom* atom;
   std::vector<OpenBabel::OBAtom*>::iterator i;
   for (atom = mol->BeginAtom(i); atom; atom = mol->NextAtom(i))
   {
      if (atom->IsInRing())
      {
         rings = true;
         break;
      }
   }
   
   if (rings)
   {
      // Make workcopy of original mol
      OpenBabel::OBMol m = *mol; m.DeleteHydrogens();
   
      // Remove all atoms that are not part of ring
      std::vector<OpenBabel::OBAtom*> nonRings;
      nonRings.clear();
      for (atom = m.BeginAtom(i); atom; atom = m.NextAtom(i))
      {
         if (!atom->IsInRing()) nonRings.push_back(atom);
      }
      for (unsigned int i(0); i < nonRings.size(); ++i)
      {
         m.DeleteAtom(nonRings[i]);
      }
      
      // Remove all bonds that are not part of a ring
      std::vector<OpenBabel::OBBond*> nonRingBonds;
      nonRingBonds.clear();
      OpenBabel::OBBond* bond;
      std::vector<OpenBabel::OBBond*>::iterator j;
      for (bond = m.BeginBond(j); bond; bond = m.NextBond(j))
      {
         if (!bond->IsInRing()) nonRingBonds.push_back(bond);
      }
      for (unsigned int i(0); i < nonRingBonds.size(); ++i)
      {
         m.DeleteBond(nonRingBonds[i]);
      }
      
      // Count atoms
      std::vector<std::vector<int > > ringsystems;
      m.ContigFragList(ringsystems);
      _result = ringsystems[0].size();
      for (unsigned int i(1); i < ringsystems.size(); ++i)
      {
         if (ringsystems[i].size() > _result) _result = ringsystems[i].size();
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
   else
   {
      _result = 0;
      _passed = true;
   }
}




