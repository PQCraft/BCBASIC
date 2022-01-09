<!----> <br>
<!----> <br>
<p align="center"><a HREF=#?><img src=https://raw.githubusercontent.com/PQCraft/BCBASIC-extras/master/BCBASIC_title.png></a></p>
<!----> <br>

---
### Extras <br>
Extra files: https://github.com/PQCraft/BCBASIC-extras <br>

---
### Required Packages/Programs <br>
#### Linux <br>
Arch (`pacman`): `base-devel`, `readline` <br>
Debian (`apt`): `build-essential`, `libreadline-dev` <br>
Alpine (`apk`): `build-base`, `readline-dev` <br>
#### Windows <br>
NT - 10 (download): [`MinGW`](http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download), [`Make for Windows`](http://gnuwin32.sourceforge.net/packages/make.htm) <br>
7 - 10 (`choco`): `mingw`, `make` <br>
#### MacOS <br>
Mojave - Big Sur (`brew`): `gcc`, `make`, `readline` <br>

---
### Recommended Packages/Programs <br>
#### Linux <br>
Arch (`pacman`): `git` <br>
Debian (`apt`): `git` <br>
Alpine (`apk`): `git` <br>
#### Windows <br>
NT - 10 (download): [`git`](https://git-scm.com/download/win) <br>
7 - 10 (`choco`): `git` <br>
#### MacOS <br>
Mojave - Big Sur (`brew`): `git` <br>

---
### Building and Running <br>
#### Linux/MacOS <br>
To build, use `make build`. <br>
To run, use `make run` or `./bcbasic`. <br>
To build then run, use `make` or `make all`. <br>
#### Windows <br>
Make sure you have downloaded the readline lib folder from [here](https://github.com/PQCraft/clibasic-winrllib).
1. Download the ZIP
2. Go into the .zip file you downloaded
3. Copy the `lib` folder in `clibasic-winrllib-master`
4. Paste the folder into `src` in the source code directory

Make sure the bin folders of MinGW and Make are in the %PATH%. <br>
Type `gcc --version` into CMD and if you received a "Can't recognize" message, MinGW is not in your %PATH%. <br>
Type `make --version` into CMD and if you received a "Can't recognize" message, Make is not in your %PATH%. <br>
How to add MinGW and/or Make to the %PATH%: <br>
1. Navigate to where MinGW or Make is installed
2. <ins>For MinGW</ins>, open the `mingw64` folder
3. Open the `bin` folder
4. Copy the location
5. Add the location you copied to the %PATH% environment variable
    - For Windows 7 and older
        1. Open the Start Menu
        2. Right-click on Computer and click Properties
        3. Click Advanced system settings
        4. Click the Advanced tab
        5. Click Environment Variables
        6. Under System variables, find Path and click Edit
        7. Add the copied location
    - For Windows 8 and newer
        1. Open the Start Menu
        2. Search for and run 'Edit the system environment variables'
        3. Click Environment Variables
        4. Under System variables, find Path and click Edit
        5. Add the copied location

To build, use `make build`. <br>
To run, use `make run` or `.\bcbasic.exe`. <br>
To build then run, use `make` or `make all`. <br>
