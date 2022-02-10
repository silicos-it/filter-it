/**********************************************************************
filterLogp.h - filter-it
 
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



#include <filters/filterLogp.h>



FilterLogp::FilterLogp(void)
{
   _keyword = "LOGP";

	_v.push_back(+1.5698368);  // 0
	_v.push_back(+1.6879823);
	_v.push_back(+1.4520422);
	_v.push_back(-1.5305911);
	_v.push_back(-0.3111998);
	_v.push_back(-0.5940829);
	_v.push_back(+0.5454484);
	_v.push_back(-0.8199907);
	_v.push_back(-2.4244810);
	_v.push_back(+1.6861112);
	_v.push_back(-0.0645900);  // 10
	_v.push_back(-1.3565753);
	_v.push_back(+0.2152871);
	_v.push_back(-0.8574482);
   _v.push_back(-0.2137226);
	_v.push_back(+0.6646457);
	_v.push_back(+0.8412987);
	_v.push_back(-0.5466015);
	_v.push_back(-1.6094113);
   _v.push_back(+0.3510570);
	_v.push_back(+0.1278186);  // 20
	_v.push_back(+0.2150506);
	_v.push_back(+0.1315437);
	_v.push_back(+0.0645039);
	_v.push_back(+0.1385249);
   _v.push_back(-0.0799654);
	_v.push_back(-0.1970438);  // 26
   //
	_v.push_back(-0.7170341);  // 27
	_v.push_back(+0.1418753);  // 28
	_v.push_back(-1.6004156);  // 29
	_v.push_back(+0.2463816);  // 30
	_v.push_back(+0.5380801);  // 31
	_v.push_back(+0.0061448);  // 32
	_v.push_back(+1.7356027);  // 33
	_v.push_back(+0.0760867);  // 34


	_s.push_back("F");
	_s.push_back("Cl");
	_s.push_back("[Br,I]");
	_s.push_back("[$([NH2;!+;X3;v3]),$([NH3;+;X4;v4])]");
	_s.push_back("[$([NH1;!+;X3;v3]),$([NH2;+;X4;v4])]");
	_s.push_back("[$([NH1;!+;X2;v3]),$([NH2;+;X3;v4])]");
	_s.push_back("[$([NH0;!+;X2;v3]),$([NH1;+;X3;v4])]");
	_s.push_back("[$([NH0;!+;X1;v3]),$([NH1;+;X2;v4])]");
	_s.push_back("[$([NH0;+]);!$([N+](=O)[O-]);!$([N+]=[N-])]");
	_s.push_back("[N+]=[N-]");
	_s.push_back("[$([n;!+]),$([nH;+])]");
	_s.push_back("[nH0;+]");
	_s.push_back("[OH0;X2;v2]");
	_s.push_back("[$([OH1;!-;X2;v2]),$([OH0;-;X1]);!$([N+](=O)[O-]);!$(C(=O)[OH]);!$(C(=O)[O-])]");
	_s.push_back("[$([OH0;X1;v2]);!$([N+](=O)[O-]);!$(S=O);!$(P=O);!$(C(=O)[OH]);!$(C(=O)[O-])]");
	_s.push_back("O~P(~O)(~O)~O");
	_s.push_back("[$(P);!$(O~P(~O)(~O)~O)]");
	_s.push_back("[SH0;X2;v2]");
	_s.push_back("[$([SH1;X2;v2]),$([SH0;-])]");
	_s.push_back("O=S");
	_s.push_back("[CH3;!R]");
	_s.push_back("[CH2;!R]");
	_s.push_back("[CH1;!R]");
	_s.push_back("[CH0;!R]");
	_s.push_back("[cH0]");
	_s.push_back("[cH1]");
	_s.push_back("[CH1;R]");
   
   for (unsigned int i = 0; i < _s.size(); ++i)
   {
      _p.push_back(new OpenBabel::OBSmartsPattern());
      _p[i]->Init(_s[i]);
   }
}



FilterLogp::~FilterLogp(void)
{
   for (unsigned int i = 0; i < _p.size(); ++i)
   {
      delete _p[i];
      _p[i] = NULL;
   }
}



FilterLogp::FilterLogp(const FilterLogp& f)
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



FilterLogp&
FilterLogp::operator=(const FilterLogp& f)
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
FilterLogp::Calculate(OpenBabel::OBMol* mol)
{
   _result = 0.0;
   std::vector< std::vector< int > > matches;
   for (unsigned int i = 0; i < 27; ++i)
   {
      _p[i]->Match(*mol, false);
      matches = _p[i]->GetUMapList();
      _result += (_v[i] * matches.size());
   }
   
   // 27 INTERCEPT
   _result += _v[27];
   
   // 28 ATOMS
   _result += _v[28] * (double) mol->NumHvyAtoms();
   
   // 29 HETERO_ATOMS
   _heteroAtoms.Calculate(mol);
   _result += _v[29] * (double) _heteroAtoms.Result(); 
      
   // 30 RINGSYSTEMS
   _ringsystems.Calculate(mol);
   _result += _v[30] * (double) _ringsystems.Result(); 
      
   // 31 HETERO_CARBON_RATIO
   _heteroCarbonRatio.Calculate(mol);
   _result += _v[31] * (double) _heteroCarbonRatio.Result(); 
      
   // 32 MOLWT
   _result += _v[32] * (double) mol->GetMolWt(true); 
      
   // 33 RING_FRACTION
   _ringFraction.Calculate(mol);
   _result += _v[33] * (double) _ringFraction.Result(); 
      
   // 34 TPSA
   _tpsa.Calculate(mol);
   _result += _v[34] * (double) _tpsa.Result(); 

   if ((_minLimit && (_result < _min)) || (_maxLimit && (_result > _max)))
   {
      _passed = false;
   }
   else
   {
      _passed = true;
   }

}



