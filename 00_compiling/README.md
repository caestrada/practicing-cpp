# Compiling C++

This example shows how to compile using two different versions of gcc.
* Default in Mac
* Latest version [gcc](https://formulae.brew.sh/formula/gcc) from Homebrew

Compiling example:
* `g++ 00_cppver.cpp -o default-cppcpmpiler` - Default 
* `g++-10 00_cppver.cpp -o brew-ver-cppcpmpiler` - Latest Version

Running code
* `./default-cppcpmpiler` - Default 
* `./brew-ver-cppcpmpiler` - Latest Version

**Note**: versions may vary over time. In my case I use `g++-10`. To know which version make sure to check in the **Cellar** directory.
`/usr/local/Cellar/gcc/<your_version>/bin/c++-xx --version`