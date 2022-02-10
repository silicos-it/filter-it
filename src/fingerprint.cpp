/**********************************************************************
fingerprint.cpp - filter-it
 
Copyright 2012-213 by Silicos-it, a division of Imacosi BVBA
 
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



#include <fingerprint.h>



Fingerprint::Fingerprint(void)
{
   _bitsPerInt = 1024 / (8 * sizeof(unsigned int));
}



Fingerprint::~Fingerprint(void)
{
}



Fingerprint::Fingerprint(const Fingerprint& f)
{
   _bitsPerInt = f._bitsPerInt;
}



Fingerprint&
Fingerprint::operator=(const Fingerprint& f)
{
   _bitsPerInt = f._bitsPerInt;
   return *this;
}



void
Fingerprint::_getFragments(std::vector<int> levels, std::vector<int>curfrag, 
int level, OpenBabel::OBAtom* patom, OpenBabel::OBBond* pbond)
{
   const int MaxFragSize = 7;
   int bo(0);
   if (pbond) bo = pbond->IsAromatic() ? 5 : pbond->GetBondOrder();

   curfrag.push_back(bo);
   curfrag.push_back(patom->GetAtomicNum());
   levels[patom->GetIdx()] = level;

   std::vector<OpenBabel::OBBond*>::iterator i;
   OpenBabel::OBBond* pnewbond;
   for (pnewbond = patom->BeginBond(i); pnewbond; pnewbond = patom->NextBond(i))
   {
      if (pnewbond == pbond)
      {
         continue;
      }
      OpenBabel::OBAtom* pnxtat = pnewbond->GetNbrAtom(patom);
      int atlevel = levels[pnxtat->GetIdx()];
      if (atlevel)
      {
         if (atlevel == 1)
         {
            curfrag[0] = bo;
            _ringset.insert(curfrag);
         }
      }
      else
      {
         if (level < MaxFragSize)
         {
            _getFragments(levels, curfrag, level + 1, pnxtat, pnewbond);
         }
      }
   }
   
   if ((curfrag[0] == 0) &&
      ((level > 1) || (patom->GetAtomicNum() > 8) || (patom->GetAtomicNum() < 6)))
   {
      _fragset.insert(curfrag);
   }
}



void
Fingerprint::_doRings(void)
{
   std::set<std::vector<int> >::iterator itr;
   for (itr = _ringset.begin(); itr != _ringset.end(); ++itr)
   {
      std::vector<int> t1(*itr);
      std::vector<int> maxring(*itr);
      for (unsigned int i = 0; i < t1.size() / 2; ++i)
      {
         rotate(t1.begin(), t1.begin() + 2, t1.end());
         if (t1 > maxring)
         {
            maxring = t1;
         }
         
         int tmp = t1[0];
         t1[0] = 0;
         _fragset.insert(t1);
         t1[0] = tmp;
         
         std::vector<int> t2(t1);
         reverse(t2.begin() + 1, t2.end());
         if (t2 > maxring)
         {
            maxring = t2;
         }
      }
      _fragset.insert(maxring);
   }
}



void
Fingerprint::_doReverses(void)
{
   std::set<std::vector<int> >::iterator itr;
   for (itr = _fragset.begin(); itr != _fragset.end(); )
   {
      std::set<std::vector<int> >::iterator titr = itr++;
      std::vector<int> t1(*titr);
      reverse(t1.begin() + 1, t1.end());
      if (t1 != *titr)
      {
         if (t1 > *titr)
         {
            _fragset.erase(titr);
            _fragset.insert(t1);
         }
         else
         {
            _fragset.erase(t1);
         }
      }
   }
}



unsigned int
Fingerprint::_calcHash(const std::vector<int>& frag)
{
   unsigned int hash(0);
   for (unsigned int i = 0; i < frag.size(); ++i)
   {
      hash = (hash * 108 + (frag[i] % 1021)) % 1021;
   }
   return hash;
}



void
Fingerprint::_setBit(std::vector<unsigned int>& vec, const unsigned int n)
{
   vec[n/_bitsPerInt] |= (1 << (n % _bitsPerInt));
}




void
Fingerprint::CalculateFP(OpenBabel::OBMol* mol, std::vector<unsigned int> & _fp) 
{
   _fp.clear();
   _fp.resize(1024 / _bitsPerInt, 0);
   _fragset.clear();
   _ringset.clear();

   OpenBabel::OBAtom* atom;
   std::vector<OpenBabel::OBAtom*>::iterator i;
   for (atom = mol->BeginAtom(i); atom; atom = mol->NextAtom(i))
   {
      std::vector<int> curfrag;
      std::vector<int> levels(mol->NumAtoms() + 1, 0);
      _getFragments(levels, curfrag, 1, atom, NULL);
   }
   
   _doRings();
   _doReverses();
   
   // Hash into fingerprint
   std::set<std::vector<int> >::iterator itr;
   for (itr = _fragset.begin(); itr != _fragset.end(); ++itr)
   {
      unsigned int hash = _calcHash(*itr);
      _setBit(_fp, hash);
   }
}



double
Fingerprint::Tanimoto(const std::vector<unsigned int>& vec1, const std::vector<unsigned int>& vec2)
{
   const unsigned int _bitsPerInt = 1024 / (8 * sizeof(unsigned int));

   if (vec1.size() != vec2.size())
   {
      return -1.0;
   }
   
   unsigned int c;
   unsigned int xa;
   unsigned int xb;
   unsigned int r;
   unsigned int na(0);
   unsigned int nb(0);
   unsigned int nab(0);
   for (unsigned int i = 0; i < vec1.size(); ++i)
   {
      c = vec1[i] & vec2[i];
      xa = vec1[i] ^ c;
      xb = vec2[i] ^ c;
      r = 1;
      for (unsigned int n = 0; n < _bitsPerInt; ++n)
      {
         if (xa & r) ++na;
         if (xb & r) ++nb;
         if (c & r) ++nab;
         r = r << 1;
      }
   }

   double res = (double) nab / (double) (na + nb + nab);
   return res;
}













