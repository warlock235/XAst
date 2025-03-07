### XAst
#### This code was originally written to find compiler syntax bugs and floating point errors. It plays a mean game of classic Asteroids, aleit a silent one.

### Build XAsteroids and AutoRepeatON
sudo apt-get install --upgrade libx11-dev libxt-dev libmotif-dev  
make clean all  

### If XAsteroids is too small for your setup/screen then it can be scaled in Ubuntu by installing the following.

####---- in Ubuntu starting in the XAst build dir ---

sudo apt-get install --upgrade git  

git clone https://github.com/Xpra-org/xpra-html5  
cd xpra-html5  
sudo ./setup.py install  
cd ..  

git clone https://github.com/Xpra-org/xpra  

sudo apt-get install --upgrade xvfb x11-xserver-utils python3-setuptools build-essential python3-dev libxxhash-dev libxdamage-dev  
sudo apt-get install --upgrade libxkbfile-dev libxrandr-dev libxtst-dev libxcomposite-dev libxres-dev libgtk-3-dev  
sudo apt-get install --upgrade libgdk3.0-cil-dev python3-cairo-dev python-gi-dev liblz4-dev libvpx-dev libx264-dev xterm  

sudo apt-get install --upgrade python3-pip  

### If Ubuntu version < 24.xx
  sudo pip install --upgrade Cython  
  sudo pip install --upgrade PyOpenGL  
### I think this is optional if it just doesn't work.
  sudo pip install --upgrade PyOpenGL-accelerate  
### If Ubuntu version >= 24.xx
  sudo pip install --upgrade --break-system-packages Cython  
### Try the next two lines first
  sudo pip install --upgrade --break-system-packages PyOpenGL  
  sudo pip install --upgrade --break-system-packages PyOpenGL-accelerate  
### If either line fails then try the following two lines. If neither above line fails, skip the next two lines.
  sudo pip install --break-system-packages PyOpengl==3.1.9a2  
### I think this is optional if it just doesn't work.
  sudo pip install --break-system-packages PyOpenGL-accelerate==3.1.9a2  

cd xpra  
sudo ./setup.py install-repo  
### Made a couple of code changes so ..XAst/xpra/setup.py would recognize Linux Mint 21.3 as Ubuntu "jammy" and Mint 22 as Ubuntu "noble".
###   If it barfs on Linux version, change setup.py. The necessary change should be obvious.
sudo ./setup.py install --prefix=/usr --install-layout=deb  
cd ..  

sudo chmod a+x XAstRunScaled.sh  
### Run Xasteroids scaled. 2 is the default scale factor. <scaleFactor> can be fractional (i.e. 1.75).
./XAstRunScaled.sh <scaleFactor>  
