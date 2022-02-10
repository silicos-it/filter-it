/**********************************************************************
options.h - filter-it
 
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



#include <options.h>



Options::Options(void)
{
	_inputFileName.clear();
	_inputSet = false;
	_inputFormat.clear();
	
	_passFileName.clear();
	_passSet = false;
	_passFormat.clear();
	
	_failFileName.clear();
	_failSet = false;
	_failFormat.clear();
	
	_filterFileName.clear();
	_filterSet = false;
	
	_tabulateFileName.clear();
	_tabulateSet = false;
	
	_salts = false;
	_noLog = false;
	_rename = false;
}



Options::~Options(void)
{
}



Options::Options(const Options& f)
{
	// Class members
	_inputFileName = f._inputFileName;
	_inputSet = f._inputSet;
	_inputFormat = f._inputFormat;
	
	_passFileName = f._passFileName;
	_passSet = f._passSet;
	_passFormat = f._passFormat;
	
	_failFileName = f._failFileName;
	_failSet = f._failSet;
	_failFormat = f._failFormat;
	
	_filterFileName = f._filterFileName;
	_filterSet = f._filterSet;
	
	_tabulateFileName = f._tabulateFileName;
	_tabulateSet = f._tabulateSet;
	
	_salts = f._salts;
	_noLog = f._noLog;
	_rename = f._rename;
}



Options&
Options::operator=(const Options& f)
{
	// Class members
	_inputFileName = f._inputFileName;
	_inputSet = f._inputSet;
	_inputFormat = f._inputFormat;
	
	_passFileName = f._passFileName;
	_passSet = f._passSet;
	_passFormat = f._passFormat;
	
	_failFileName = f._failFileName;
	_failSet = f._failSet;
	_failFormat = f._failFormat;
	
	_filterFileName = f._filterFileName;
	_filterSet = f._filterSet;
	
	_tabulateFileName = f._tabulateFileName;
	_tabulateSet = f._tabulateSet;
	
	_salts = f._salts;
	_noLog = f._noLog;
	_rename = f._rename;
	
 	return *this;
}



std::string
Options::SetInputFilename(const std::string& f)
{
	_inputFileName = f;
	_inputSet = true;
	return _inputFileName;
}



bool
Options::HasInputSet(void)
{
	return _inputSet;
}



std::string
Options::GetInputFilename(void)
{
	return _inputFileName;
}



std::string
Options::SetInputFormat(const std::string& f)
{
	_inputFormat = f;
	return f;
}



std::string
Options::GetInputFormat(void)
{
	return _inputFormat;
}



std::string
Options::SetFailFilename(const std::string& f)
{
	_failFileName = f;
	_failSet = true;
	return _failFileName;
}



bool
Options::HasFailSet(void)
{
	return _failSet;
}



std::string
Options::GetFailFilename(void)
{
	return _failFileName;
}



std::string
Options::SetFailFormat(const std::string& f)
{
	_failFormat = f;
	return f;
}



std::string
Options::GetFailFormat(void)
{
	return _failFormat;
}



std::string
Options::SetPassFilename(const std::string& f)
{
	_passFileName = f;
	_passSet = true;
	return _passFileName;
}



bool
Options::HasPassSet(void)
{
	return _passSet;
}



std::string
Options::GetPassFilename(void)
{
	return _passFileName;
}



std::string
Options::SetPassFormat(const std::string& f)
{
	_passFormat = f;
	return f;
}



std::string
Options::GetPassFormat(void)
{
	return _passFormat;
}



std::string
Options::SetFilterFilename(const std::string& f)
{
	_filterFileName = f;
	_filterSet = true;
	return _filterFileName;
}



bool
Options::HasFilterSet(void)
{
	return _filterSet;
}



std::string
Options::GetFilterFilename(void)
{
	return _filterFileName;
}



std::string
Options::SetTabulateFilename(const std::string& f)
{
	_tabulateFileName = f;
	_tabulateSet = true;
	return _tabulateFileName;
}



bool
Options::HasTabulateSet(void)
{
	return _tabulateSet;
}



std::string
Options::GetTabulateFilename(void)
{
	return _tabulateFileName;
}



void
Options::Salts(const bool& f)
{
	_salts = f;
}



bool
Options::Salts(void) const
{
	return _salts;
}



void
Options::Rename(const bool& f)
{
	_rename = f;
}



bool
Options::Rename(void) const
{
	return _rename;
}



void
Options::NoLog(const bool& f)
{
	_noLog = f;
}



bool
Options::NoLog(void) const
{
	return _noLog;
}



void
Options::Log(const bool& f)
{
	_noLog = !f;
}



bool
Options::Log(void) const
{
	return !_noLog;
}



std::string
Options::Print(void) const
{
	std::ostringstream os;
	os << std::endl;
	os << "COMMAND_LINE OPTIONS:" << std::endl;
	os << std::endl;
	os << "  -> Strip salts:       " << (_salts ? "no" : "yes") << std::endl;
	os << "  -> Rename titles:     " << (_rename ? "yes" : "no") << std::endl;
	os << "  -> Tabulate mode:     " << (_tabulateSet ? "yes" : "no");

	if (_tabulateSet)
	{
		if (_tabulateFileName.empty()) os << " > std::cout";
		else os << " > " << _tabulateFileName;
	}
	os << std::endl;

	os << "  -> Logging:           " << (_noLog ? "no" : "yes") << std::endl;
	os << "  -> Filter file:       " << _filterFileName << std::endl;
	os << "  -> Input file:        " << _inputFileName << std::endl;
	os << "  -> Input file format: " << _inputFormat << std::endl;
	
	if (_passSet && !_tabulateSet)
	{
		os << "  -> Pass file:         ";
		if (_passFileName.empty()) os << "std::cout";
		else os << _passFileName;
		os << std::endl;

		os << "  -> Pass file format:  ";
		if (_passFormat.empty()) os << "sdf";
		else os << _passFormat;
		os << std::endl;
	}

	if (_failSet && !_tabulateSet)
	{
		os << "  -> Fail file:         ";
		if (_failFileName.empty()) os << "std::cout";
		else os << _failFileName;
		os << std::endl;
		os << "  -> Fail file format:  ";
		if (_failFormat.empty()) os << "sdf";
		else os << _failFormat;
		os << std::endl;
	}

	os << std::endl;
   
	std::string r = os.str();
	return r;
}
