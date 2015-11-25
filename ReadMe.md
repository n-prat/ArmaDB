### How to build
***only on windows***
***Boost is required***
* git clone
* mkdir build && cd build
* cmake ..
 * -DWITH_TESTLIB=ON : build test project for VisualStudio
 * -DWITH_A3DLLPROXY=ON : build Dll for use with A3DLLPROXY
* open sln in VS
* build RELEASE (Debug will not work in-game)

### How to use [dev]
* Copy armadb.dll to Arma 3 root **OR** an addon folder  
* You can also use a symlink :  
mklink "D:\Path\to\Arma 3\armadb.dll" "W:\Path\to\Arma_db\build\Release\armadb.dll"
* (You still need to close the game to recompile)  

#### Notes
* SQLite sources from *sqlite-amalgamation-3090200.zip* are included in the *SQLiteDLL* folder
