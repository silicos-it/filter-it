/**********************************************************************
filterDistance.cpp - filter-it
 
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



#include <filters/filterDistance.h>



FilterDistance::FilterDistance(void)
: _result(false)
{
   _keyword = "DISTANCE";
   _msg = "";
   _patterns.clear();
   _distances.clear();
}



FilterDistance::~FilterDistance(void)
{
}



FilterDistance::FilterDistance(const FilterDistance& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterPharmacophore class members
   _result = f._result;
   _patterns = f._patterns;
   _distances = f._distances;
   _msg = f._msg;
}



FilterDistance&
FilterDistance::operator=(const FilterDistance& f)
{
   // Filter class members
   _initialised = f._initialised;
   _whiteSpace = f._whiteSpace;
   _passed = f._passed;
   _keyword = f._keyword;
   
   // FilterFragment class members
   _result = f._result;
   _patterns = f._patterns;
   _distances = f._distances;
   _msg = f._msg;

   return *this;
}



bool
FilterDistance::DistanceWithinLimits(Distance* d, unsigned int m1, unsigned int m2)
{
   bool passed;
   
   // Distance
   double r;
   Pattern* p1 = d->bPattern;
   Pattern* p2 = d->ePattern;
   r = sqrt((p1->x[m1] - p2->x[m2]) * (p1->x[m1] - p2->x[m2]) +
            (p1->y[m1] - p2->y[m2]) * (p1->y[m1] - p2->y[m2]) +
            (p1->z[m1] - p2->z[m2]) * (p1->z[m1] - p2->z[m2]));
            
   // Check if within limits
   if ((d->minLimit && (r < d->min)) || (d->maxLimit && (r > d->max)))
   {
      passed = false;
   }
   else
   {
      passed = true;
   }
   return passed;
}



std::string
FilterDistance::FailMessage(const OpenBabel::OBMol* mol) const
{
   std::ostringstream os;
   std::string title = mol->GetTitle();
   os << title;
   os << " >> failed ";
   os << _keyword;
   os << " filter criterion";
   if (_msg != "")
   {
      os << _msg;
   }
   title = os.str();
   return title;
}



bool
FilterDistance::Result(void) const
{
   return _result;
}



bool
FilterDistance::Initialise(const std::string& parameters, const bool tabulate)
{
   std::string line(parameters);
   std::string keyword = parameters.substr(0, line.find_first_of("\n\t \r", 0));
   
   // Check if not in tabulate mode
   if (tabulate)
   {
      std::cerr << " -> Warning: " << keyword << " filters are not run when in tabulate mode";
      std::cerr << std::endl;
      _initialised = false;
      return false;
   }

   std::vector<std::string> data;
   std::cerr << "  -> " << keyword << " ";
   line = parameters;
   line.erase(0, line.find_first_not_of(_whiteSpace, 0));
   data.clear();
   line += " ";
   std::size_t b(0);
   std::size_t e(line.find_first_of(_whiteSpace, b));
   while ( (e <= line.size()) && (b != std::string::npos) )
   {
      data.push_back(line.substr(b, e - b));
      b = line.find_first_not_of(_whiteSpace, e);
      e = line.find_first_of(_whiteSpace, b);
   }
   for_each(data[0].begin(), data[0].end(), toupper);

   
   // "PATTERN" KEYWORD
   if (keyword == "PATTERN")
   {
      if (data.size() == 1)
      {
         std::cerr << "ERROR: " << keyword << " entry is missing name and smarts pattern";
         std::cerr << std::endl;
         exit(1);
      }
      else if (data.size() == 2)
      {
         std::cerr << "ERROR: " << keyword << " entry is missing smarts pattern";
         std::cerr << std::endl;
         exit(1);
      }
      else
      {
         // Name
         std::string name = data[1];
         std::cerr << " " << name;
      
         // Smarts
         std::string smarts = data[2];
         OpenBabel::OBSmartsPattern ss;
         if (ss.Init(smarts))
         {
            std::cerr << " " << smarts;
         }
         else
         {
            std::cerr << name << " \"" << smarts << "\": ";
            std::cerr << "Failed parsing" << std::endl;
            exit(1);
         }
         
         // Center of pattern indices
         std::vector<unsigned int> indices;
         unsigned int ind;
         if (data.size() > 3)
         {
            for (unsigned int i = 3; i < data.size(); ++i)
            {
               ind = (unsigned int) atoi(data[i].c_str());
               if (ind < 1)
               {
                  std::cerr << "ERROR: PATTERN" << name << ": index " << i - 2;
                  std::cerr << " (" << ind << ") should be > 0" << std::endl;
                  exit(1);
               }
               if (ind > ss.NumAtoms())
               {
                  std::cerr << "ERROR: PATTERN" << name << ": index " << i - 2;
                  std::cerr << " (" << ind << ") should be <= ";
                  std::cerr << ss.NumAtoms() << std::endl;
                  exit(1);
               }
               indices.push_back(ind - 1);
               std::cerr << " " << ind;
            }
         }
         else
         {
            unsigned int maxIdx = ss.NumAtoms();
            for (unsigned int i(0); i < maxIdx; ++i)
            {
               indices.push_back(i);
            }
         }
         
         // Create new pattern
         Pattern* p = new Pattern;
         p->name = name;
         p->smartsName = smarts;
         p->smarts = ss;
         for (unsigned int i = 0; i < indices.size(); ++i)
         {
            p->indices.push_back(indices[i]);
         }
         p->nMatches = 0;
         p->x.clear();
         p->y.clear();
         p->z.clear();
         p->foundConnections.clear();
         p->maxConnections = 0;
         _patterns.insert(p);
      }
   }
      
            
   // "DISTANCE" KEYWORD
   else
   {
      if (data.size() == 1)
      {
         std::cerr << "ERROR: " << keyword << " entry is missing the two patterns and both distances";
         std::cerr << std::endl;
         exit(1);
      }
      else if (data.size() == 2)
      {
         std::cerr << "ERROR: " << keyword << " entry is missing the second pattern and both distances";
         std::cerr << std::endl;
         exit(1);
      }
      else if (data.size() == 3)
      {
         std::cerr << "ERROR: " << keyword << " entry is missing the min and max distance limits";
         std::cerr << std::endl;
         exit(1);
      }
      else if (data.size() == 4)
      {
         std::cerr << "ERROR: " << keyword << " entry is missing the max distance limit";
         std::cerr << std::endl;
         exit(1);
      }
      else
      {
         // Pattern 1
         std::string p1 = data[1];
         std::cerr << " " << p1;
      
         // Pattern 2
         std::string p2 = data[2];
         std::cerr << " " << p2;
      
         // Min distance limit
         bool minLimit;
         double min;
         if (data[3] == "*")
         {
            minLimit = false;
            min = 0.0;
            std::cerr << " *";
         }
         else
         {
            minLimit = true;
            min = atof(data[3].c_str());
            std::cerr << " " << min;
         }
         if (min < 0.0)
         {
            std::cerr << "ERROR: " << _keyword << ": min distance should be >= 0 ";
            std::cerr << std::endl;
            exit(1);
         }
      
         // Max distance limit
         bool maxLimit;
         double max;
         if (data[4] == "*")
         {
            maxLimit = false;
            max = 0.0;
            std::cerr << " *";
         }
         else
         {
            maxLimit = true;
            max = atof(data[4].c_str());
            std::cerr << " " << max;
         }
         if (max < 0.0)
         {
            std::cerr << "ERROR: " << _keyword << ": max distance should be >= 0 ";
            std::cerr << std::endl;
            exit(1);
         }
         if (maxLimit && (max < min))
         {
            std::cerr << "ERROR: " << _keyword << ": max distance should be >= min ";
            std::cerr << std::endl;
            exit(1);
         }
         
         // Create new distance
         Distance* d = new Distance;
         d->bPatternName = p1;
         d->ePatternName = p2;
         d->min = min;
         d->max = max;
         d->minLimit = minLimit;
         d->maxLimit = maxLimit;
         d->bPattern = NULL;
         d->ePattern = NULL;
         _distances.push_back(d);
      }
   }
   
   std::cerr << std::endl;
   _initialised = true;
   return true;
}



void
FilterDistance::PostProcess(void)
{
   // Check for duplicates in terms of the used pattern names
   std::map<std::string, Pattern*> patterns;
   patterns.clear();
   std::set<Pattern*>::iterator pi;
   Pattern* p;
   for (pi = _patterns.begin(); pi != _patterns.end(); ++pi)
   {
      p = *pi;
      if (patterns.count(p->name))
      {
         std::cerr << "ERROR: " << _keyword << " is using duplicate name " << p->name;
         std::cerr << std::endl;
         exit(1);
      }
      else
      {
         patterns.insert(std::make_pair<std::string, Pattern*>(p->name, p));
      }
   }
   
   // Update distances
   for (unsigned int i(0); i < _distances.size(); ++i)
   {
      if (!patterns.count(_distances[i]->bPatternName))
      {
         std::cerr << "ERROR: " << _keyword << " line with undeclared pattern name 1: ";
         std::cerr << _distances[i]->bPatternName;
         std::cerr << std::endl;
         exit(1);
      }
      else if (!patterns.count(_distances[i]->ePatternName))
      {
         std::cerr << "ERROR: " << _keyword << " line with undeclared pattern name 2: ";
         std::cerr << _distances[i]->ePatternName;
         std::cerr << std::endl;
         exit(1);
      }
      else
      {
         _distances[i]->bPattern = patterns[_distances[i]->bPatternName];
         _distances[i]->ePattern = patterns[_distances[i]->ePatternName];
      }
   }
   
   // Make sure that all distances are initiated and different
   for (unsigned int i(0); i < _distances.size(); ++i)
   {
      if (_distances[i]->bPattern == NULL)
      {
         std::cerr << "ERROR: " << _keyword << " line with undeclared pattern name 1: ";
         std::cerr << _distances[i]->bPatternName;
         std::cerr << std::endl;
         exit(1);
      }
      if (_distances[i]->ePattern == NULL)
      {
         std::cerr << "ERROR: " << _keyword << " line with undeclared pattern name 2: ";
         std::cerr << _distances[i]->ePatternName;
         std::cerr << std::endl;
         exit(1);
      }
      if (_distances[i]->bPattern == _distances[i]->ePattern)
      {
         std::cerr << "ERROR: " << _keyword << " line with duplicate pattern names (1 == 2): ";
         std::cerr << _distances[i]->bPatternName << " ";
         std::cerr << _distances[i]->ePatternName;
         std::cerr << std::endl;
         exit(1);
      }
   }
   
   // Update the maximal connections variable of the patterns
   for (unsigned int i(0); i < _distances.size(); ++i)
   {
      ++_distances[i]->bPattern->maxConnections;
      ++_distances[i]->ePattern->maxConnections;
   }
}



void
FilterDistance::Calculate(OpenBabel::OBMol* mol)
{
   std::set<Pattern*>::iterator pi;
   Pattern* p;
   
   // Make sure that all patterns can be matched
   _msg.clear();
   for (pi = _patterns.begin(); pi != _patterns.end(); ++pi)
   {
      p = *pi;
      if (!p->smarts.Match(*mol, true))
      {
         _passed = false;
         _msg = " (no match for pattern \"" + p->name + "\")";
         return;
      }
   }

   // Match patterns and calculate center coordinates
   std::vector<std::vector<int> > matches;
   OpenBabel::OBAtom* atom;
   for (pi = _patterns.begin(); pi != _patterns.end(); ++pi)
   {
      p = *pi;
      p->nMatches = 0;
      p->x.clear();
      p->y.clear();
      p->z.clear();
      p->foundConnections.clear();
      p->smarts.Match(*mol, false);
      matches = p->smarts.GetUMapList();
      std::vector<int> match;
      for (unsigned int i(0); i < matches.size(); ++i)
      {
         match = matches[i];
         
         // Increase vector sizes
         p->x.push_back(0.0);
         p->y.push_back(0.0);
         p->z.push_back(0.0);
         p->foundConnections.push_back(0);
         
         // Calculate center
         for (unsigned int a(0); a < p->indices.size(); ++a)
         {
            atom = mol->GetAtom(match[p->indices[a]]);
            p->x[p->nMatches] += atom->GetX();
            p->y[p->nMatches] += atom->GetY();
            p->z[p->nMatches] += atom->GetZ();
         }
         p->x[p->nMatches] /= (double) p->indices.size();
         p->y[p->nMatches] /= (double) p->indices.size();
         p->z[p->nMatches] /= (double) p->indices.size();
      
         // Update number of pattern matches
         ++p->nMatches;
      }
   }
 
   // Check the distances
   Pattern* p1;
   Pattern* p2;
   for (unsigned int i(0); i < _distances.size(); ++i)
   {
      p1 = _distances[i]->bPattern;
      p2 = _distances[i]->ePattern;
      std::vector<bool> h1(p1->nMatches, false);
      std::vector<bool> h2(p1->nMatches, false);
      
      for (unsigned int m1(0); m1 < p1->nMatches; ++m1)
      {
         for (unsigned int m2(0); m2 < p2->nMatches; ++m2)
         {
            if (DistanceWithinLimits(_distances[i], m1, m2))
            {
               h1[m1] = true;
               h2[m2] = true;
            }
         }
      }
      
      for (unsigned int m1(0); m1 < p1->nMatches; ++m1)
      {
         if (h1[m1])
         {
            ++_distances[i]->bPattern->foundConnections[m1];
            break;
         }
      }
      
      for (unsigned int m2(0); m2 < p2->nMatches; ++m2)
      {
         if (h2[m2])
         {
            ++_distances[i]->ePattern->foundConnections[m2];
            break;
         }
      }
   }
   
   // Check if there is a global match
   unsigned int result(0);
   for (pi = _patterns.begin(); pi != _patterns.end(); ++pi)
   {
      p = *pi;
      for (unsigned int m(0); m < p->nMatches; ++m)
      {
         if (p->foundConnections[m] == p->maxConnections)
         {
            ++result;
            break;
         }
      }
   }
   if (result < _patterns.size())_passed = false;
   else _passed = true;
}



