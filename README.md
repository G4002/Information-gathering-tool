# Information Gathering Tool #

# Description

This Python script performs basic reconnaissance on a target domain. It retrieves HTTP response headers, resolves the domain to its IP address, and fetches geographic location details using a public IP information API.

This project demonstrates practical usage of networking, DNS resolution, HTTP requests, and JSON parsing for cybersecurity and information-gathering tasks.



# Features

* Accepts domain name as command-line input
* Sends HTTPS request to target website
* Extracts and prints HTTP response headers
* Resolves domain name to IP address
* Retrieves IP geolocation data
* Parses JSON API responses



# Technologies Used

* Python 3
* requests library
* socket module
* JSON parsing

# Requirements

Install dependency:

pip install requests



# How to Run

python info.py example.com

Example:

python info.py google.com



# Output Includes

* Server headers
* Target IP address
* Geographic coordinates
* Region
* City
* Country



# Use Cases

* Basic cybersecurity reconnaissance
* Network information gathering
* Learning DNS and HTTP inspection
* Security research practice



# Author

Kalamkuntla Girija
