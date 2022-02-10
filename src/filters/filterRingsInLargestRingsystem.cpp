/**********************************************************************
filterRingsInLargestRingsystem.cpp - filter-it
 
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



#include <filters/filterRingsInLargestRingsystem.h>



FilterRingsInLargestRingsystem::FilterRingsInLargestRingsystem(void)
{
   _keyword = "RINGS_IN_LARGEST_RINGSYSTEM";
}



FilterRingsInLargestRingsystem::~FilterRingsInLargestRingsystem(void)
{
}



FilterRingsInLargestRingsystem::FilterRingsInLargestRingsystem(const FilterRingsInLargestRingsystem& f)
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



FilterRingsInLargestRingsystem&
FilterRingsInLargestRingsystem::operator=(const FilterRingsInLargestRingsystem& f)
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
FilterRingsInLargestRingsystem::Calculate(OpenBabel::OBMol* mol)
{
   // Are there rings?
   bool rings = false;
   OpenBabel::OBAtom* atom;
   std::vector<OpenBabel::OBAtom*>::iterator ai;
   for (atom = mol->BeginAtom(ai); atom; atom = mol->NextAtom(ai))
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
      OpenBabel::OBMol m = *mol;
      m.DeleteHydrogens();
   
      // Remove all atoms that are not part of ring
      std::vector<OpenBabel::OBAtom*> nonRingAtoms;
      nonRingAtoms.clear();
      for (atom = m.BeginAtom(ai); atom; atom = m.NextAtom(ai))
      {
         if (!atom->IsInRing()) nonRingAtoms.push_back(atom);
      }
      for (unsigned int i(0); i < nonRingAtoms.size(); ++i)
      {
         m.DeleteAtom(nonRingAtoms[i]);
      }
      
      // Remove all bonds that are not part of a ring
      std::vector<OpenBabel::OBBond*> nonRingBonds;
      nonRingBonds.clear();
      OpenBabel::OBBond* bond;
      std::vector<OpenBabel::OBBond*>::iterator bi;
      for (bond = m.BeginBond(bi); bond; bond = m.NextBond(bi))
      {
         if (!bond->IsInRing()) nonRingBonds.push_back(bond);
      }
      for (unsigned int i(0); i < nonRingBonds.size(); ++i)
      {
         m.DeleteBond(nonRingBonds[i]);
      }
      
       // Chop into ringsystems
      std::vector<std::vector<int> > ringsystems;
      ringsystems.clear();
      m.ContigFragList(ringsystems);
      unsigned int nringsystems = ringsystems.size();
      OpenBabel::OBMol fragment;
      unsigned int largestRingsystem(0);
      for (unsigned int rs(0); rs < nringsystems; ++rs)
      {
         OpenBabel::OBMol* fragment = new OpenBabel::OBMol;
         *fragment = m;
         ringsystems.clear();
         fragment->ContigFragList(ringsystems);
         for (unsigned int a(0); a < ringsystems[rs].size(); ++a)
         {
            fragment->GetAtom(ringsystems[rs][a])->SetId(rs);
         }
         
         // Delete all atoms not belonging to ringsystem
         bool notFinished(true);
         while (notFinished && fragment->NumAtoms())
         {
            notFinished = false;
            for (atom = fragment->BeginAtom(ai); atom; atom = fragment->NextAtom(ai))
            {
               if (atom->GetId() != rs)
               {
                  if (fragment->DeleteAtom(atom))
                  {
                     notFinished = true;
                     break;
                  }
               }
            }
         }

         // Count rings in fragment
         if (fragment->GetSSSR().size() > largestRingsystem)
         {
            largestRingsystem = fragment->GetSSSR().size();
         }

         delete fragment; fragment = NULL;
      }
      _result = largestRingsystem;
      
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




