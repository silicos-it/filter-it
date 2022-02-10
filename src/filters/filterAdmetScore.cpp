/**********************************************************************
filterAdmetScore.cpp - filter-it
 
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



#include <filters/filterAdmetScore.h>



FilterAdmetScore::FilterAdmetScore(void)
{
   _keyword = "ADMET_SCORE";
}



FilterAdmetScore::~FilterAdmetScore(void)
{
}



FilterAdmetScore::FilterAdmetScore(const FilterAdmetScore& f)
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
   
   // Own members
   _logp = f._logp;
}



FilterAdmetScore&
FilterAdmetScore::operator=(const FilterAdmetScore& f)
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
  
   // Own members
   _logp = f._logp;

   // Return
   return *this;
}



void
FilterAdmetScore::Calculate(OpenBabel::OBMol* mol)
{
   	_result = 0.0;
   
   	// Molwt
	double mw = mol->GetMolWt(true);
   	if (mw < 330.0)
   	{
		mw = 0.0;
   	}
	_result = fabs(330.0 - mw) / 120.0;
   
   	// Logp
   	_logp.Calculate(mol); 
	double logp = _logp.Result();
    _result += (fabs(2.5 - logp) / 2.0);
   
    if ((_minLimit && (_result < _min)) || (_maxLimit && (_result > _max)))
    {
       _passed = false;
    }
    else
    {
       _passed = true;
    }
}



