/**********************************************************************
filterAtomsInSmallestSidechain.cpp - filter-it
 
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



#include <filters/filterAtomsInSmallestSidechain.h>



FilterAtomsInSmallestSidechain::FilterAtomsInSmallestSidechain(void)
{
   _keyword = "ATOMS_IN_SMALLEST_SIDECHAIN";
}



FilterAtomsInSmallestSidechain::~FilterAtomsInSmallestSidechain(void)
{
}



FilterAtomsInSmallestSidechain::FilterAtomsInSmallestSidechain(const FilterAtomsInSmallestSidechain& f)
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



FilterAtomsInSmallestSidechain&
FilterAtomsInSmallestSidechain::operator=(const FilterAtomsInSmallestSidechain& f)
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
FilterAtomsInSmallestSidechain::Calculate(OpenBabel::OBMol* mol)
{
   // Rings?
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

   if (rings)
   {
      // Make working copies of mol
      OpenBabel::OBMol m1 = *mol; m1.DeleteHydrogens();
      OpenBabel::OBMol m2 = *mol; m2.DeleteHydrogens();
   
      // Create a mapping of the atoms between m1 and m2
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
      while (endstanding && m1.NumAtoms())
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
      
      // Separate
      if (!m2.NumAtoms())
      {
         _result = 0;
         _passed = true;
         return;
      }
      else
      {
         std::vector<std::vector<int > > sidechains;
         m2.ContigFragList(sidechains);
         _result = sidechains.size();
         if (sidechains.size())
         {
            _result = sidechains[0].size();
            for (unsigned int i(1); i < sidechains.size(); ++i)
            {
               if (sidechains[i].size() < _result) _result = sidechains[i].size();
            }
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
   else
   {
      _result = 0;
      _passed = true;
   }
}






