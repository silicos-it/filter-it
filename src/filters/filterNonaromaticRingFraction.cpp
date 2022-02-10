/**********************************************************************
filterNonaromaticRingFraction.cpp - filter-it
 
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



#include <filters/filterNonaromaticRingFraction.h>



FilterNonaromaticRingFraction::FilterNonaromaticRingFraction(void)
{
   _keyword = "NONAROMATIC_RING_FRACTION";
}



FilterNonaromaticRingFraction::~FilterNonaromaticRingFraction(void)
{
}



FilterNonaromaticRingFraction::FilterNonaromaticRingFraction(const FilterNonaromaticRingFraction& f)
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



FilterNonaromaticRingFraction&
FilterNonaromaticRingFraction::operator=(const FilterNonaromaticRingFraction& f)
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
FilterNonaromaticRingFraction::Calculate(OpenBabel::OBMol* mol)
{
   // Are there atoms and rings?
   unsigned int rings(0);
   unsigned int natoms(0);
   OpenBabel::OBAtom* atom;
   std::vector<OpenBabel::OBAtom*>::iterator i;
   for (atom = mol->BeginAtom(i); atom; atom = mol->NextAtom(i))
   {
      if (atom->IsHydrogen()) continue;
      if (atom->IsInRing()) ++rings;
      ++natoms;
   }
   if (!natoms)
   {
      _result = 0.0;
      _passed = false;
      return;
   }
   
   std::set<int> uniqRingIdx;
   if (rings)
   {
      std::vector<OpenBabel::OBRing*> nrings = mol->GetSSSR();
      uniqRingIdx.clear();
      std::vector<int>::iterator path;
      std::vector<OpenBabel::OBRing*>::iterator ri;
      for (ri = nrings.begin(); ri != nrings.end(); ++ri)
      {
         if (!(*ri)->IsAromatic())
         {
            for (path = (*ri)->_path.begin(); path != (*ri)->_path.end(); ++path)
            {
               uniqRingIdx.insert(*path);
            }
         }
      }
   }
   unsigned int ar(uniqRingIdx.size());
   if (ar)
   {
      _result = (double) ar / (double) natoms;
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




