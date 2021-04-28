#I Spy a Fake

I Spy a Fake is a multiplayer web application that runs on a local web server (raspberry pi)

## Usage

In order to run this application, the user needs Raspberry Pi Desktop on Oracle VM VirtualBox Manager. Make sure
to unzip group58 in /usr/lib/cgi-bin

Before starting the Raspberry Pi, go into Settings -> Network and set Attached to: Bridged Adapter.

###Installing Apache:
'''bash
sudo apt update
sudo apt install apache2 -y
sudo apt install php libapache2-mod-php -y
'''

###Installing WT:
'''bash
sudo apt-get install gcc g++ libboost -all-dev cmake
sudo apt-get install doxygen libgraphicsmagick3 libssl-dev libpq-dev libssl-dev libfcgi-dev
'''

Download version 3.7.0 in the link below
http://www.webtoolkit.eu/wt/download

Build Wt from sourses
'''bash
cd wt-3.7.0
mkdir build
cd build
cmake ..
make
make -C examples
'''

Install wt in /usr/local (this part takes about 30 minutes to complete)
'''bash
sudo make install
sudo ldconfig
'''

###Setting up CGI:

'''bash
cd /usr/lib/cgi-bin
sudo a2enmod
cgi sudo a2enmod cgid
sudo service apache2 restart
cd /etc/apache2 
cd sites-available
sudo nano 000-default.conf
'''

Replace what we currently have for 000-default.conf in this file.

'''bash
sudo service apache2 restart
'''

###Running Application:

'''bash
g++ -std=c++14 -o ISpyAFakeApplication WaitingRoomWidget.cpp CategoryImageWidget.cpp ISAFGames.cpp Player.cpp GameRoom.cpp ISpyAFakeApplication.cpp JsonObj.cpp Category.cpp CategoryAssignment.cpp votingScreenWidget.cpp HostOrJoinGameWidget.cpp leadershipWidget.cpp -lwtdbo -lwtdbosqlite3 -lwthttp -lwt
sudo chmod -R 755 /usr/lib/cgi-bin
sudo chown root.root /usr/lib/cgi-bin
'''

Open on your raspberry pi ispyafake/cgi-bin/ISpyAFakeApplication or on your local machine http://192.168.0.42/

The main class is ISpyAFakeApplication.cpp

