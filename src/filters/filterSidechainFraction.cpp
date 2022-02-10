/**********************************************************************
filterSidechainFraction.cpp - filter-it
 
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



#include <filters/filterSidechainFraction.h>



FilterSidechainFraction::FilterSidechainFraction(void)
{
   _keyword = "SIDECHAIN_FRACTION";
}



FilterSidechainFraction::~FilterSidechainFraction(void)
{
}



FilterSidechainFraction::FilterSidechainFraction(const FilterSidechainFraction& f)
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



FilterSidechainFraction&
FilterSidechainFraction::operator=(const FilterSidechainFraction& f)
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



void
FilterSidechainFraction::Calculate(OpenBabel::OBMol* mol)
{
   // Check if rings are present
   bool rings(false);
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
   
   // Make working copy of mol
   if (rings)
   {
      OpenBabel::OBMol m1 = *mol; m1.DeleteHydrogens();
      OpenBabel::OBMol m2 = *mol; m2.DeleteHydrogens();
      unsigned int natoms = m1.NumAtoms();
      if (!natoms)
      {
         _result = 0.0;
         _passed = false;
         return;
      }

      // Create a mapping of the atoms to recover the sidechains back
      std::map<OpenBabel::OBAtom*, OpenBabel::OBAtom*> m1_2_m2;
      OpenBabel::OBAtom* a1;
      OpenBabel::OBAtom* a2;
      std::vector<OpenBabel::OBAtom*>::iterator i1;
      std::vector<OpenBabel::OBAtom*>::iterator i2;
      a1 = m1.BeginAtom(i1);
      a2 = m2.BeginAtom(i2);
      while (a1 && a2)
      {
         m1_2_m2[a1] = a2;
         a1 = m1.NextAtom(i1);
         a2 = m2.NextAtom(i2);
      }

      // Remove all endstanding atoms in m1
      std::set<OpenBabel::OBAtom*> sidechainAtoms;
      sidechainAtoms.clear();
      bool endstanding(true);
      while (endstanding)
      {
         endstanding = false;
         for (a1 = m1.BeginAtom(i1); a1; a1 = m1.NextAtom(i1))
         {
            if (a1->GetValence() < 2)
            {
               endstanding = true;
               sidechainAtoms.insert(m1_2_m2[a1]);
               m1.DeleteAtom(a1);
               break;
            }
         }
      }

      // Now remove the non-sidechain atoms of m2
      std::set<OpenBabel::OBAtom*> nonSidechainAtoms;
      nonSidechainAtoms.clear();
      for (a2 = m2.BeginAtom(i2); a2; a2 = m2.NextAtom(i2))
      {
         if (!sidechainAtoms.count(a2)) nonSidechainAtoms.insert(a2);
      }
      std::set<OpenBabel::OBAtom*>::iterator i;
      for (i = nonSidechainAtoms.begin(); i != nonSidechainAtoms.end(); ++i)
      {
         m2.DeleteAtom(*i);
      }
      
      // Count
      _result = (double) m2.NumAtoms() / (double) natoms;
   }
   else
   {
      _result = 0.0;
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





