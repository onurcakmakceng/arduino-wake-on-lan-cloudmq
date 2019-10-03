# PC WakeOnLAN with Remote Controlled Arduino
Wake on LAN (WoL) your PC with remote controlled Arduino (Cloud MQ)

<img src="/doc-files/arduino-1.jpg" height="300" alt="arduino-1">  <img src="/doc-files/arduino-2.jpg" width="300" alt="arduino-2">  

P.S.: Do not buy Arduino Ethernet module (Esp32) or ethernet Shield (w5100) ref: issue [#1](/../../issues/1) (closed) it is repentance


# Setup

## Ubuntu


- Install `ethtool`

```
$ sudo apt install ethtool
```

- Check Wake-on is on with network interface. You can check network interface with `ifconfig` command.

```
$ NETWORK_INTERFACE=enp24s0
$ sudo ethtool $NETWORK_INTERFACE | grep Wake-on
```

- Make sure that, Wake-on is `g`. If not, run:

```
$ NETWORK_INTERFACE=enp24s0
$ sudo ethtool -s $NETWORK_INTERFACE wol g
```

- Create `wol.service` for system. This service enables wake-on service for network interface.

```
$ sudo vim /etc/systemd/system/wol.service
```

- Paste these to `/etc/systemd/system/wol.service` file:

```
[Unit]
Description=Configure Wake-up on LAN

[Service]
Type=oneshot
ExecStart=/sbin/ethtool -s enp35s0 wol g

[Install]
WantedBy=basic.target
```


- Enable and run service.

```
$ systemctl daemon-reload
$ systemctl enable wol.service
$ systemctl start wol.service
```

- Done

# Client

## Send Magic Packet Using Python

- Set Broadcast IP

```
$ BROADCAST_IP=192.168.1.255
```

- Set MAC address of the target machine.

```
$ MAC_ADDRESS=00:11:22:33:44:55
```

- Send magic packet:

```
$ python3 client/send_magic_packet.py $BROADCAST_IP $MAC_ADDRESS
```
