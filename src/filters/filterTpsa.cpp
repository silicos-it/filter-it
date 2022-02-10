/**********************************************************************
filterTpsa.cpp - filter-it
 
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



#include <filters/filterTpsa.h>



FilterTpsa::FilterTpsa(void)
{
   _keyword = "TPSA";    

   _s.push_back("[$([NH0;X3;!-;!+]([!#1])([!#1])[!#1]);!$([NH0;X3;!-;!+]1([!#1])[!#1][!#1]1)]");
   _v.push_back(3.24);
   
   _s.push_back("[NH0;X2;!-;!+]([!#1])=[!#1]");
   _v.push_back(12.36);
   
   _s.push_back("[NH0;X1;!-;!+]#[!#1]");
   _v.push_back(23.79);
   
   _s.push_back("[NH0;X3;+]([!#1])([O;-])=O");   // Nitro N
   _v.push_back(11.68);
   
   _s.push_back("[NH0;X2;+](=[!#1;-])=[!#1]");   // Middle N of azide
   _v.push_back(13.60);
   
   _s.push_back("[NH0;X3;!-;!+]1([!#1])[!#1][!#1]1");  // 3-Membered N ring
   _v.push_back(3.01);
   
   _s.push_back("[$([NH1;X3;!-;!+]([!#1])[!#1]);!$([NH1;X3;!-;!+]1[!#1][!#1]1)]");
   _v.push_back(12.03);
   
   _s.push_back("[NH1;X3;!-;!+]1[!#1][!#1]1");         // 3-Membered N ring
   _v.push_back(21.94);

   _s.push_back("[NH1;X2;!-;!+]=[!#1]");
   _v.push_back(23.85);

   _s.push_back("[NH2;X3;!-;!+][!#1]");
   _v.push_back(26.02);

   _s.push_back("[NH0;X4;+]([!#1])([!#1])([!#1])[!#1]");
   _v.push_back(0.00);

   _s.push_back("[$([NH0;X3;+]([!#1])([!#1])=[!#1]);!$([NH0;X3;+]([!#1])([O;-])=O)]");
   _v.push_back(3.01);

   _s.push_back("[NH0;X2;+]([!#1])#[!#1]");     // Isocyano N
   _v.push_back(4.36);

   _s.push_back("[NH1;X4;+]([!#1])([!#1])[!#1]");
   _v.push_back(4.44);

   _s.push_back("[NH1;X3;+]([!#1])=[!#1]");
   _v.push_back(13.97);

   _s.push_back("[NH2;X4;+]([!#1])[!#1]");
   _v.push_back(16.61);

   _s.push_back("[NH2;X3;+]=[!#1]");
   _v.push_back(25.59);

   _s.push_back("[NH3;X4;+][!#1]");
   _v.push_back(27.64);

   _s.push_back("[nH0;X2;!-;!+](:[!#1]):[!#1]");
   _v.push_back(12.89);

   _s.push_back("[nH0;X3;!-;!+](:[!#1])(:[!#1]):[!#1]");
   _v.push_back(4.41);

   _s.push_back("[nH0;X3;!-;!+](-[!#1])(:[!#1]):[!#1]");
   _v.push_back(4.93);

   _s.push_back("[nH0;X3;!-;!+](=[!#1])(:[!#1]):[!#1]");
   _v.push_back(8.39);

   _s.push_back("[nH1;X3;!-;!+](:[!#1]):[!#1]");
   _v.push_back(15.79);

   _s.push_back("[nH0;X3;+](:[!#1])(:[!#1]):[!#1]");
   _v.push_back(4.10);

   _s.push_back("[nH0;X3;+](-[!#1])(:[!#1]):[!#1]");
   _v.push_back(3.88);

   _s.push_back("[nH1;X3;+](:[!#1]):[!#1]");
   _v.push_back(14.14);

   _s.push_back("[$([OH0;X2;!-;!+]([!#1])[!#1]);!$([OH0;X2;!-;!+]1[!#1][!#1]1)]");
   _v.push_back(9.23);

   _s.push_back("[OH0;X2;!-;!+]1[!#1][!#1]1");
   _v.push_back(12.53);

   _s.push_back("[OH0;X1;!-;!+]=[!#1]");
   _v.push_back(17.07);

   _s.push_back("[OH1;X2;!-;!+][!#1]");
   _v.push_back(20.23);

   _s.push_back("[OH0;X1;-][!#1]");
   _v.push_back(23.06);

   _s.push_back("[oH0;X2;!-;!+](:[!#1]):[!#1]");
   _v.push_back(13.14);

   _s.push_back("[SH0;X2;!-;!+]([!#1])[!#1]");
   _v.push_back(25.30);

   _s.push_back("[SH0;X1;!-;!+]=[!#1]");
   _v.push_back(32.09);

   _s.push_back("[$([SH0;X3;!-;!+]([!#1])([!#1])=[!#1]);!$(S([!#1])([!#1])=O)]");
   _v.push_back(19.21);

   _s.push_back("[$([SH0;X4;!-;!+]([!#1])([!#1])(=[!#1])=[!#1]);!$(S([!#1])([!#1])(=O)=O)]");
   _v.push_back(8.38);

   _s.push_back("[SH1;X2;!-;!+][!#1]");
   _v.push_back(38.80);

   _s.push_back("[sH0;X2;!-;!+](:[!#1]):[!#1]");
   _v.push_back(28.24);

   _s.push_back("[sH0;X3;!-;!+](=[!#1])(:[!#1]):[!#1]");
   _v.push_back(21.70);

   _s.push_back("[PH0;X3;!-;!+]([!#1])([!#1])[!#1]");
   _v.push_back(13.59);

   _s.push_back("[$([PH0;X2;!-;!+]([!#1])=[!#1]);!$(P([!#1])=O)]");
   _v.push_back(34.14);

   _s.push_back("[$([PH0;X4;!-;!+]([!#1])([!#1])([!#1])=[!#1]);!$(P([!#1])([!#1])([!#1])=O)]");
   _v.push_back(9.81);

   _s.push_back("[PH1;X4;!-;!+]([!#1])([!#1])=[!#1]");
   _v.push_back(23.47);
   
   for (unsigned int i = 0; i < _s.size(); ++i)
   {
	  _p.push_back(new OpenBabel::OBSmartsPattern());
	  _p[i]->Init(_s[i]);
   }  
}



FilterTpsa::~FilterTpsa(void)
{
   for (unsigned int i = 0; i < _p.size(); ++i)
   {
      delete _p[i];
      _p[i] = NULL;
   }
}



FilterTpsa::FilterTpsa(const FilterTpsa& f)
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
   _s = f._s;
   _v = f._v;
   for (unsigned int i = 0; i < _s.size(); ++i)
   {
      _p.push_back(new OpenBabel::OBSmartsPattern());
      _p[i]->Init(_s[i]);
   }
}



FilterTpsa&
FilterTpsa::operator=(const FilterTpsa& f)
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
   _s = f._s;
   _v = f._v;
   for (unsigned int i = 0; i < _s.size(); ++i)
   {
      _p.push_back(new OpenBabel::OBSmartsPattern());
      _p[i]->Init(_s[i]);
   }

   // Return
   return *this;
}



void
FilterTpsa::Calculate(OpenBabel::OBMol* mol)
{
   _result = 0.0;
   std::vector< std::vector< int > > matches;
   for (unsigned int i = 0; i < _p.size(); ++i)
   {
      _p[i]->Match(*mol, false);
      matches = _p[i]->GetUMapList();
      _result += (_v[i] * matches.size());
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




