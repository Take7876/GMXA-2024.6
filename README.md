# GMXA-2024.6　-　GROMACS Analysis Supporting Library

This program assumes analysis using **GROMACS**.

## How to Compile

GMXA requires the **GROMACS library** to compile.  
Compilation is done using a **Makefile**.  
Please change the Makefile variable to your own directory when compiling, and then run:

`make install` is not intended.

After compilation, a library is created in the `lib` directory by default.  
Object files are created in the `obj` directory.

## Simple Compilation Flow

1. Rewrite the Makefile
2. `make build`
3. `make`

After compiling, you need to declare environment variables when linking your own program.  
This is because the GROMACS library used in this program is a **dynamic library**.

Details are provided in the README located at:

## GROMACS Version Compatibility

`.xtc` file loading has been confirmed to work with:
- GROMACS 2021
- GROMACS 2023

Operation with other GROMACS versions has not been confirmed.

## Platform Notes

Please specify the compiler according to the operating system you are using,  
as the binary format of object files differs between **Linux** and **macOS**.

## Cleaning

To delete the generated object files and libraries:
`make clean`

## How to Use

If you want to combine this program with your own program, you will need the **include path** and **library path** of this program.

## License

This software links to the GROMACS library, which is licensed under the GNU Lesser General Public License (LGPL) version 2.1 or later.
GMXA itself is released under the MIT License.

## Author

**Author:** Taketoshi Kitagawa  
Kansai University Graduate School of Science and Engineering 
Theoretical and Computational Chemistry Laboratory  

**Creation Date:** May 2024
