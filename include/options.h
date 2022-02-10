/**********************************************************************
options.h - filter-it
 
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



#ifndef __OPTIONS_H__
#define __OPTIONS_H__


#include <string>
#include <sstream>

#include <openbabel/obconversion.h>



class Options
{
 	protected:

		std::string             _inputFileName;		// --in
		bool					_inputSet;			// true if --in has been set
		std::string				_inputFormat;

		std::string             _passFileName;		// --pass
		bool					_passSet;			// true if --pass has been set
		std::string				_passFormat;

		std::string             _failFileName;      // --fail
		bool					_failSet;			// true if --fail has been set
		std::string				_failFormat;

		std::string             _filterFileName;  	// --filter
	    bool					_filterSet;  		// true if --filter has been set

		std::string             _tabulateFileName;  // --tab
	    bool					_tabulateSet;  		// true if --tab has been set

		bool                    _salts;           	// --salts
		bool                    _noLog;           	// --noLog
		bool                    _rename;          	// --rename

	public:
      
		Options(void);
		virtual ~Options(void);
		Options(const Options&);
		Options& operator=(const Options&);

		virtual std::string			SetInputFilename(const std::string&);
		virtual bool				HasInputSet(void);
		virtual std::string			GetInputFilename(void);
		virtual std::string			SetInputFormat(const std::string&);
		virtual std::string			GetInputFormat(void);

		virtual std::string			SetFailFilename(const std::string&);
		virtual bool				HasFailSet(void);
		virtual std::string			GetFailFilename(void);
		virtual std::string			SetFailFormat(const std::string&);
		virtual std::string			GetFailFormat(void);

		virtual std::string			SetPassFilename(const std::string&);
		virtual bool				HasPassSet(void);
		virtual std::string			GetPassFilename(void);
		virtual std::string			SetPassFormat(const std::string&);
		virtual std::string			GetPassFormat(void);

		virtual std::string			SetFilterFilename(const std::string&);
		virtual bool				HasFilterSet(void);
		virtual std::string			GetFilterFilename(void);

		virtual std::string			SetTabulateFilename(const std::string&);
		virtual bool				HasTabulateSet(void);
		virtual std::string			GetTabulateFilename(void);

		virtual void				Salts(const bool&);
		virtual bool				Salts(void) const;

		virtual void				NoLog(const bool&);
		virtual bool				NoLog(void) const;
		virtual void				Log(const bool&);
		virtual bool				Log(void) const;

		virtual void				Rename(const bool&);
		virtual bool				Rename(void) const;

		virtual std::string			Print(void) const;     
};




#endif
