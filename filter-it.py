#!/usr/bin/env python


import argparse




################################################################################
#
# Argument parsing
#
################################################################################

parser = argparse.ArgumentParser(description="Filter-it")

# Required arguments

flags = parser.add_argument_group("required arguments")

flags.add_argument("--input",
	type=str,
	required=True,
	help="""
	Name of the file containing the input molecules. The extension determines the
	file format, unless the --inputFormat option is provided which overrides
	the extension definition.
	""")

# Optional arguments

flags = parser.add_argument_group("optional arguments")

#flags.add_argument('-h', '--help', action='help')

flags.add_argument("--inputFormat",
	choices=['sd', 'sdf', 'smi', 'smiles'],
	required=False,
	help="""
	Specifies the format of the input file. Accepted values are indicated. 
	If this option is not provided, then the input file format is extracted 
	from the filename extension (if possible; otherwise an error is given).
	""")

args = parser.parse_args()

