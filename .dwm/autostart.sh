#! /bin/bash

if [ $(pgrep qbittorrent) =" " ]; then
	qbittorrent
fi

if [ $(pgrep mullvad-vpn) =" " ]; then
	mullvad-vpn
fi

if [ $(pgrep nm-applet) =" " ]; then
	nm-applet
fi
