/**********************************************************************
filterAndrewsEnergy.cpp - filter-it
 
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



#include <filters/filterAndrewsEnergy.h>



FilterAndrewsEnergy::FilterAndrewsEnergy(void)
: _p(12)
, _s(12)
{
   _keyword = "ANDREWS_ENERGY";

   for (unsigned int i(0); i < _p.size(); ++i)
   {
      _p[i].n = 0;
   }
   _p[0].v  = -14.0;      // Intercept
   _p[1].v  =  -0.7;      // DOF
   _p[2].v  =  +0.7;      // C-sp2
   _p[3].v  =  +0.8;      // C-sp3
   _p[4].v  = +11.5;      // N+
   _p[5].v  =  +1.2;      // N
   _p[6].v  =  +8.2;      // COO(-)
   _p[7].v  = +10.0;      // PO4(2-)
   _p[8].v  =  +2.5;      // OH
   _p[9].v  =  +3.4;      // C=O
   _p[10].v =  +1.1;      // O,S
   _p[11].v =  +1.3;      // Halogen
   
   // Smarts
   _s[2].Init("[#6;X3;v4]");
   _s[3].Init("[#6;X4;v4]");
   _s[4].Init("[$([#7;+]);!$([#7;!+])]");
   _s[5].Init("[$([#7;!+]);!$([#7;+])]");
   _s[6].Init("[$(O=C[O;-]);!$(O=P([O;X2;v2])([O;-])[O;-]);!$([OH;X2;v2]);!$(C=O);!$([$([OH0,X2,v2]),$([SH0,X2,v2])])]");
   _s[7].Init("[!$(O=C[O;-]);$(O=P([O;X2;v2])([O;-])[O;-]);!$([OH;X2;v2]);!$(C=O);!$([$([OH0,X2,v2]),$([SH0,X2,v2])])]");
   _s[8].Init("[!$(O=C[O;-]);!$(O=P([O;X2;v2])([O;-])[O;-]);$([OH;X2;v2]);!$(C=O);!$([$([OH0,X2,v2]),$([SH0,X2,v2])])]");
   _s[9].Init("[!$(O=C[O;-]);!$(O=P([O;X2;v2])([O;-])[O;-]);!$([OH;X2;v2]);$(C=O);!$([$([OH0,X2,v2]),$([SH0,X2,v2])])]");
   _s[10].Init("[!$(O=C[O;-]);!$(O=P([O;X2;v2])([O;-])[O;-]);!$([OH;X2;v2]);!$(C=O);$([$([OH0,X2,v2]),$([SH0,X2,v2])])]");
   _s[11].Init("[F,Cl,Br,I]");
}



FilterAndrewsEnergy::~FilterAndrewsEnergy(void)
{
}



FilterAndrewsEnergy::FilterAndrewsEnergy(const FilterAndrewsEnergy& f)
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
   
   // Own class members
   _p = f._p;
   _s = f._s;
   _rotor = f._rotor;
}



FilterAndrewsEnergy&
FilterAndrewsEnergy::operator=(const FilterAndrewsEnergy& f)
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
   
   // Own class members
   _p = f._p;
   _s = f._s;
   _rotor = f._rotor;

   // Return
   return *this;
}



void
FilterAndrewsEnergy::Calculate(OpenBabel::OBMol* mol)
{
   // Reset to zero
   for (unsigned int i = 0; i < _p.size(); ++i)
   {
      _p[i].n = 0;
   }
   
   // Intercept
   _p[0].n = 1;
   
   // DOF
   _rotor.Calculate(mol);
   _p[1].n = _rotor.Result();
   
   // Add DOF for each hydroxyl
   _s[8].Match(*mol, false);
   _p[1].n += _s[8].GetUMapList().size();

   // Fragments
   for (unsigned int i = 2; i < _p.size(); ++i)
   {
      _s[i].Match(*mol, false);
      _p[i].n += _s[i].GetUMapList().size();
   }

   _result = 0;
   for (unsigned int i = 0; i < _p.size(); ++i)
   {
      _result += (double) _p[i].n * _p[i].v;
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





