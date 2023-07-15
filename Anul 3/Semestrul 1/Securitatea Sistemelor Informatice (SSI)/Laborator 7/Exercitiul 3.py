import requests
import hashlib

api_url = 'https://www.virustotal.com/api/v3/files'
path_to_file = "C:\Facultate\Securitatea Informatiei\Laborator 7\Fisier_test.txt"

headers = {'x-apikey': '3747c9a40ef7d6fcf2f2dd781890ea795d5cf2069662a7b295f546195b44b6ff'}
with open(path_to_file, 'rb') as file:
    files = {'file': ('Fisier_test.txt', file)}
    # print(files)
    response = requests.post(api_url, headers=headers, files=files)  # Sending the file to be scanned

    if response.status_code == 200:  # If it was scanned succesfully
        # print("File scanned")
        file_identifier = hashlib.sha256(file.read()).hexdigest()
        url = f"https://www.virustotal.com/api/v3/files/{file_identifier}"
        response2 = requests.request("GET", url, headers=headers)  # We get the response of the scan
        if response2.status_code == 200:
            response2 = response2.json()
            print(response2['data']['attributes']['total_votes'])  # We filter through the JSON and only print
                                                                   # the number of vendors who returned it as harmless / malicious
        else:
            print(response2.status_code)
