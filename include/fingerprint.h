/**********************************************************************
fingerprint.h - filter-it
 
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



#ifndef __FINGERPRINT_H__
#define __FINGERPRINT_H__


#include <set>
#include <vector>
#include <algorithm>

#include <openbabel/atom.h>
#include <openbabel/bond.h>
#include <openbabel/mol.h>



class Fingerprint
{
	protected:
   
      	unsigned int                        _bitsPerInt;
      	std::set<std::vector<int> >         _fragset;
      	std::set<std::vector<int> >         _ringset;
      
      	void  _getFragments(std::vector<int>, std::vector<int>, int,
                          OpenBabel::OBAtom*, OpenBabel::OBBond*);
      	void  _doRings(void);
      	void  _doReverses(void);
      	unsigned int _calcHash(const std::vector<int>&);
      	void  _setBit(std::vector<unsigned int>&, const unsigned int);

	public:
   
      	Fingerprint(void);
      	virtual ~Fingerprint(void);
      	Fingerprint(const Fingerprint&);
      	Fingerprint& operator=(const Fingerprint&);

      	virtual void CalculateFP(OpenBabel::OBMol* mol, std::vector<unsigned int> &);
		double Tanimoto(const std::vector<unsigned int>&, const std::vector<unsigned int>&);
};







#endif
